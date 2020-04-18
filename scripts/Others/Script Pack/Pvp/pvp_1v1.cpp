/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Thunderofnl / Orion
 - Complete: 80%
 - ScriptName: '1 VS 1 PvP' 
 - Comment: Old version made by QQrolf aka 'Tommy'
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#include "pvp_system.h"
#include "Language.h"

/* Queue */
vector<const char*> queueList, queueListTwo;
const char * playerOne;
const char * playerTwo;
const char * victimname;
const char * killername;
string PlayerOneName, PlayerTwoName;
const uint32 _points = 10;
const uint32 _rating = 50;
/* Activity */
bool isMatchActive = false;
bool canMatchQueue = true;
bool canstart = true;
int playerOneMap, playerTwoMap;
float playerOnePosX, playerOnePosY, playerOnePosZ, playerOnePosO; //Old player 1 coordinates.
float playerTwoPosX, playerTwoPosY, playerTwoPosZ, playerTwoPosO; //Old player 2 coordinates.

class npc_onevone : public CreatureScript
{
	public: npc_onevone() : CreatureScript("npc_onevone"){}
	
	bool OnGossipHello(Player * player, Creature* creature)
	{
		if(player->isInCombat())
		{
			creature->MonsterWhisper("Stop fighting before you talk to me!", player->GetGUID());
			return false;
		}
		if(!sPvPSystemMgr->GetGUIDFromPlayer(player->GetGUID())) // Yes, after a restart, even if you already are registered in the system
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Join the league.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
		else
		{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I am ready to fight!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Spoils of War(Rewards)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Scoreboard", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);	
		}
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "...Nevermind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}
	
	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
	{
		player->PlayerTalkClass->ClearMenus();
		if(sender != GOSSIP_SENDER_MAIN)
			return false;
		
		switch (actions)
		{
		    case GOSSIP_ACTION_INFO_DEF+1:
				for(vector<const char*>::const_iterator itr = queueList.begin(); itr != queueList.end(); ++itr)
				{
					if(player->GetName() == *itr)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("You're already in the queue!");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					for(vector<const char*>::const_iterator _itr = queueListTwo.begin(); _itr != queueListTwo.end(); ++_itr)
					{
						if(player->GetName() == *itr || player->GetName() == *_itr)
						{
							ChatHandler(player->GetSession()).PSendSysMessage("You're already in the queue!");
							player->PlayerTalkClass->SendCloseGossip();
							return false;
						}
					}
				}

				if(queueList.size() == 0)
				{
					queueList.push_back(player->GetName().c_str()); // This is a list not a db
					ChatHandler(player->GetSession()).PSendSysMessage("Added you to the queue.");
					player->PlayerTalkClass->SendCloseGossip();
					return false;
				}
				else if (queueListTwo.size() == 0)
				{
					queueListTwo.push_back(player->GetName().c_str());
					ChatHandler(player->GetSession()).PSendSysMessage("Added you to the second queue.");
					player->PlayerTalkClass->SendCloseGossip();
					return false;
				}

				if(queueList.size() > queueListTwo.size())
					queueListTwo.push_back(player->GetName().c_str());
				else
					queueList.push_back(player->GetName().c_str());

				if(isMatchActive)
					ChatHandler(player->GetSession()).PSendSysMessage("Added you to the queue. A match is already active, so you'll have to wait.");
				else
					ChatHandler(player->GetSession()).PSendSysMessage("Added you to the queue. No matches are active at this time.");
				player->PlayerTalkClass->SendCloseGossip();
				break;

		    case GOSSIP_ACTION_INFO_DEF+2:
				pvpSystem = new PvPSystem(player, player->GetName(), 0, 0);
				sPvPSystemMgr->SaveToList(pvpSystem);
				ChatHandler(player->GetSession()).PSendSysMessage("You have registered in the 1v1 League!");
				player->PlayerTalkClass->SendCloseGossip();
				break;

		    case GOSSIP_ACTION_INFO_DEF+3:
				/* 
				    Based on the player's rating, you can easily have rewards by doing:
			    */
				pvpSystem = new PvPSystem();
				if(pvpSystem->Rating() >= 1000)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Access Rating 1000+ Rewards", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
				else if (pvpSystem->Rating() >= 2500)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Access Rating 2500+ Rewards", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
				else
				{
					player->GetSession()->SendAreaTriggerMessage("Your rating isn't high enough!");
					player->PlayerTalkClass->SendCloseGossip();
				}
				player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
				break;

		    case GOSSIP_ACTION_INFO_DEF+4:
				pvpSystem = new PvPSystem();
				pvpSystem->ShowScoreBoard(player);
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case GOSSIP_ACTION_INFO_DEF+5:
				creature->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
				player->PlayerTalkClass->SendCloseGossip();
			break;

		    case GOSSIP_ACTION_INFO_DEF+6: // Rating 1000+ Rewards
				break;

		    case GOSSIP_ACTION_INFO_DEF+7: // Rating 2500+ Rewards
				break;
		}
		return true;
	}
	
	struct npc_onevoneAI : public ScriptedAI
	{
		uint32 m_AttackTimer; 
		Player * _qPlayer;
		Player * _qPlayerTwo;
		npc_onevoneAI(Creature * c) : ScriptedAI(c) 
		{
			
			
		}

		void Reset()
		{
			
		}

		void UpdateAI(const uint32 diff)
		{
			if(!isMatchActive && canMatchQueue && queueList.size() > 0 && queueListTwo.size() > 0)
			{
				_qPlayer = sObjectAccessor->FindPlayerByName(queueList.front());
				_qPlayerTwo = sObjectAccessor->FindPlayerByName(queueListTwo.front());
				
				if(_qPlayer && _qPlayerTwo)
				{
					playerOnePosX = _qPlayer->m_positionX;
					playerOnePosY = _qPlayer->m_positionY;
					playerOnePosZ = _qPlayer->m_positionZ;
					playerOnePosO = _qPlayer->GetOrientation();
					playerOneMap = _qPlayer->m_mapId;
					playerTwoPosX = _qPlayerTwo->m_positionX;
					playerTwoPosY = _qPlayerTwo->m_positionY;
					playerTwoPosZ = _qPlayerTwo->m_positionZ;
					playerTwoPosO = _qPlayerTwo->GetOrientation();
					playerTwoMap = _qPlayerTwo->m_mapId;
					PlayerOneName = _qPlayer->GetName();
					PlayerTwoName = _qPlayerTwo->GetName();
					_qPlayer->SetPhaseMask(2, true);
					_qPlayerTwo->SetPhaseMask(2, true);
					_qPlayer->TeleportTo(571, 5830.89f, 590.163f, 571.65f, 2.37108f); // Teleport Player One
					_qPlayerTwo->TeleportTo(571, 5723.53f, 623.611f, 571.553f, 5.59592f); // Teleport Player Two
					//_qPlayer->CastSpell(_qPlayer,27559,true);
					//_qPlayerTwo->CastSpell(_qPlayerTwo,27559,true);
					_qPlayer->SendDuelCountdown(3000);
					_qPlayerTwo->SendDuelCountdown(3000);
					m_AttackTimer = 3000;
					//ChatHandler(_qPlayer->GetSession()).PSendSysMessage(7525, PlayerTwoName);
					//ChatHandler(_qPlayerTwo->GetSession()).PSendSysMessage(7525, PlayerOneName);
					//_qPlayer->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					//_qPlayerTwo->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					isMatchActive = true;
					canMatchQueue = false;
					queueList.erase(queueList.begin(), queueList.begin() + 1);
					queueListTwo.erase(queueListTwo.begin(), queueListTwo.begin() + 1);
				}
				
			}
			
			
			if(canstart)
			{
				if(isMatchActive)
				{
					playerOne : _qPlayer->GetName(); // Retrieving players name for confirmation when killing the other player
					playerTwo :  _qPlayerTwo->GetName(); // Retrieving players name for confirmation when killing the other player		
						if (m_AttackTimer <= diff)
						{
							//_qPlayer->RemoveAura(27559);
							//_qPlayerTwo->RemoveAura(27559);
							canstart = false;
							_qPlayer = NULL;
							_qPlayerTwo = NULL;
						}
						else
						   m_AttackTimer -= diff;
				}
			}
		}
	};

	CreatureAI * GetAI(Creature * pCreature) const
	{
		return new npc_onevoneAI(pCreature);
	}
   private:
	   PvPSystem * pvpSystem;
};
	
class player_onevone : public PlayerScript
{
   public: 
     player_onevone() : PlayerScript("player_onevone"){}
	
	 void OnPVPKill(Player * killer, Player * victim)
	 {
		 if(isMatchActive && !canMatchQueue)
		 {
			 PvPSystem * pvpsystem = new PvPSystem();
			 victimname : victim->GetName();
			 killername : killer->GetName();
			 pvpsystem->UpdateScore(killer->GetGUID());
			 pvpsystem->UpdateRating(killer->GetGUID(), false);
			 pvpsystem->UpdateRating(victim->GetGUID(), true);
			 ChatHandler(killer->GetSession()).PSendSysMessage("Great 1v1! Your points increased by 10.");
			 ChatHandler(victim->GetSession()).PSendSysMessage("|cffff0000[Arena Announcer]:|r Poor %s lost the battle.|r", victim->GetName().c_str());
			 killer->ResurrectPlayer(100, false);
			 victim->ResurrectPlayer(100, false);
			 if(killer->GetName() == PlayerOneName){
				 killer->TeleportTo(playerOneMap, playerOnePosX, playerOnePosY, playerOnePosZ, playerOnePosO);
				 victim->TeleportTo(playerTwoMap, playerTwoPosX, playerTwoPosY, playerTwoPosZ, playerTwoPosO);
			 }else if(victim->GetName() == PlayerOneName){
				 victim->TeleportTo(playerOneMap, playerOnePosX, playerOnePosY, playerOnePosZ, playerOnePosO);
				 killer->TeleportTo(playerTwoMap, playerTwoPosX, playerTwoPosY, playerTwoPosZ, playerTwoPosO);	
				}else{
			 ChatHandler(killer->GetSession()).PSendSysMessage("Something is wrong, you will both be teleported to the mall.");
			 ChatHandler(victim->GetSession()).PSendSysMessage("Something is wrong, you will both be teleported to the mall.");	
				victim->TeleportTo(230, 1380.61f, -822.44f, -92.72f, 4.752445f);
				killer->TeleportTo(230, 1380.61f, -822.44f, -92.72f, 4.752445f);

					}
			 killer->SetPhaseMask(1, true);
			 victim->SetPhaseMask(1, true);
			 PlayerOneName = "";
			 PlayerTwoName = "";
			 isMatchActive = false;
			 canMatchQueue = true;
			 canstart = true;
			 playerOne = "";
			 playerTwo = "";
		 }
	 }

	 void OnLogout(Player * player) // Player could possibly be in the queue.. will crash if this isn't dealt with
	 {
		 for(vector<const char*>::const_iterator itr = queueList.begin(); itr != queueList.end(); ++itr)
		 {
			 if(player->GetName() == *itr)
			 {
				 itr = queueList.erase(itr);
				 playerOne = "";
				 playerTwo = "";
				 canMatchQueue = true;
				 isMatchActive = false;
				 return;
			 }
			 for(vector<const char*>::const_iterator itr = queueListTwo.begin(); itr != queueListTwo.end(); ++itr)
			 {
				 if(player->GetName() == *itr)
				 {
					 itr = queueListTwo.erase(itr);
					 playerOne = "";
					 playerTwo = "";
					 canMatchQueue = true;
					 isMatchActive = false;
					 return;
				 }
			 }
		 }
	 }
};

void AddSC_onevone()
{
	new npc_onevone;
	new player_onevone;
}