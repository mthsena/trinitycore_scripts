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
 - Developer(s): N/A
 - Complete: N/A
 - ScriptName: '' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

// Set USE_TOKEN to 1 if you want to have it use tokens in place of gold
#define USE_TOKEN 	0
#define TOKEN_ID	29434

struct BloodMoneyInfo
{
	uint64 guid;
	uint32 amount;
	bool accepted;
};

typedef std::list<BloodMoneyInfo> BloodMoneyList;
typedef std::map<uint64, BloodMoneyList> BloodMoney;
static BloodMoney m_bloodMoney;

bool HasBloodMoneyChallenger(uint64 playerGUID)
{
	return m_bloodMoney.find(playerGUID) != m_bloodMoney.end();
}

bool HasBloodMoneyChallenger(uint64 targetGUID, uint64 playerGUID)
{
	if (!HasBloodMoneyChallenger(targetGUID))
		return false;
	BloodMoneyList bml = m_bloodMoney[targetGUID];
	for (BloodMoneyList::const_iterator itr = bml.begin(); itr != bml.end(); ++itr)
		if (itr->guid == playerGUID)
			return true;
	return false;
}

void AddBloodMoneyEntry(uint64 targetGUID, uint64 playerGUID, uint32 amount)
{
	BloodMoneyInfo bmi;
	bmi.guid = playerGUID;
	bmi.amount = amount;
	bmi.accepted = false;
	m_bloodMoney[targetGUID].push_back(bmi);
}

void RemoveBloodMoneyEntry(uint64 targetGUID, uint64 playerGUID)
{
	if (!HasBloodMoneyChallenger(targetGUID, playerGUID))
		return;
	BloodMoneyList &list = m_bloodMoney[targetGUID];
    	BloodMoneyList::iterator itr;
    	for (itr = list.begin(); itr != list.begin(); ++itr)
        	if (itr->guid == playerGUID)
            		break;
    	list.erase(itr);
}

void SetChallengeAccepted(uint64 targetGUID, uint64 playerGUID)
{
	if (!HasBloodMoneyChallenger(targetGUID, playerGUID))
		return;
	BloodMoneyList &list = m_bloodMoney[targetGUID];
	BloodMoneyList::iterator itr;
	for (itr = list.begin(); itr != list.end(); ++itr)
	{
		if (itr->guid == playerGUID)
		{
			itr->accepted = true;
			break;
		}
	}
}

class npc_blood_money : public CreatureScript
{
	public : 
		npc_blood_money() : CreatureScript("npc_blood_money") {}

	bool OnGossipHello(Player * player, Creature * creature)
	{
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Challenge a Player", 11, 1000);	
		if (HasBloodMoneyChallenger(player->GetGUID()))
		{
			BloodMoneyList list = m_bloodMoney[player->GetGUID()];
			for (BloodMoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				char msg[50];

				if (Player* plr = Player::GetPlayer(*player, itr->guid))
				{
					if (USE_TOKEN)
					{
						sprintf(msg, "Accept %s's Challenge of %d tokens", plr->GetName(), itr->amount);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_MAIN, itr->guid);
						sprintf(msg, "Decline %s's Challenge of %d tokens", plr->GetName(), itr->amount);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_INFO, itr->guid);
					}
					else
					{
						sprintf(msg, "Accept %s's Challenge of %dg", plr->GetName(), itr->amount/10000);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_MAIN, itr->guid);
						sprintf(msg, "Decline %s's Challenge of %dg", plr->GetName(), itr->amount/10000);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, msg, GOSSIP_SENDER_INFO, itr->guid);
					}
					
				}
			}
		}
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind", GOSSIP_SENDER_MAIN, 1);
		
		player->SEND_GOSSIP_MENU(80025, creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player * player, Creature * creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();
		if (uiAction == 1)
		{
			player->CLOSE_GOSSIP_MENU();
			return true;
		}
		switch(uiSender)
		{
			case GOSSIP_SENDER_MAIN:
				if (Player* target = Player::GetPlayer(*player, uiAction))
				{
					SetChallengeAccepted(player->GetGUID(), target->GetGUID());
					char msg[60];
					sprintf(msg, "%s has accepted your challenge!", player->GetName());
					creature->MonsterWhisper(msg, target->GetGUID(), true);
					player->CLOSE_GOSSIP_MENU();
				}
				break;
			case GOSSIP_SENDER_INFO:
				if (Player* target = Player::GetPlayer(*player, uiAction))
				{
					char msg[60];
					sprintf(msg, "%s has declined your challenge!", player->GetName());
					creature->MonsterWhisper(msg, target->GetGUID(), true);
					RemoveBloodMoneyEntry(player->GetGUID(), uiAction);
					OnGossipHello(player, creature);
				}
				break;
			case 11:
				if (USE_TOKEN)
				{
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 5 tokens", GOSSIP_SENDER_MAIN, 5, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 10 tokens", GOSSIP_SENDER_MAIN, 10, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 15 tokens", GOSSIP_SENDER_MAIN, 15, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 25 tokens", GOSSIP_SENDER_MAIN, 25, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 50 tokens", GOSSIP_SENDER_MAIN, 50, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 100 tokens", GOSSIP_SENDER_MAIN, 100, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 150 tokens", GOSSIP_SENDER_MAIN, 150, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 200 tokens", GOSSIP_SENDER_MAIN, 200, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 250 tokens", GOSSIP_SENDER_MAIN, 250, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 500 tokens", GOSSIP_SENDER_MAIN, 500, "Type in the player's name", 0, true);
				}
				else
				{
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 5g", GOSSIP_SENDER_MAIN, 5, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 10g", GOSSIP_SENDER_MAIN, 10, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 15g", GOSSIP_SENDER_MAIN, 15, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 25g", GOSSIP_SENDER_MAIN, 25, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 50g", GOSSIP_SENDER_MAIN, 50, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 100g", GOSSIP_SENDER_MAIN, 100, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 150g", GOSSIP_SENDER_MAIN, 150, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 200g", GOSSIP_SENDER_MAIN, 200, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 250g", GOSSIP_SENDER_MAIN, 250, "Type in the player's name", 0, true);
					player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_MONEY_BAG, "Bet 500g", GOSSIP_SENDER_MAIN, 500, "Type in the player's name", 0, true);
				}
				
				player->SEND_GOSSIP_MENU(80025, creature->GetGUID());
				break;
		}
		return true;
	}

	bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
	{
		if (player->GetName() == code)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFNow why would you want to challenge yourself?");
			return false;
		}
		if (uint64 targetGUID = sObjectMgr->GetPlayerGUIDByName(code))
		{
			if (Player* target = Player::GetPlayer(*player, targetGUID))
			{
				if (target->GetZoneId() == player->GetZoneId())
				{
					if (USE_TOKEN)
					{
						if (target->GetItemCount(TOKEN_ID) < action)
						{
							ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFThat player does not have enough tokens to make the bet!");
							player->CLOSE_GOSSIP_MENU();
							return false;
						}
						if (player->GetItemCount(TOKEN_ID) < action)
						{
							ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou do not have enough tokens to make the bet!");
							player->CLOSE_GOSSIP_MENU();
							return false;
						}
						
						bool found = false;
						if (HasBloodMoneyChallenger(player->GetGUID()))
						{
							BloodMoneyList list = m_bloodMoney[player->GetGUID()];
							for (BloodMoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
								if (itr->guid == target->GetGUID())
									found = true;
						}
						if (!found)
						{
							if (!HasBloodMoneyChallenger(target->GetGUID(), player->GetGUID()))
							{							    
								AddBloodMoneyEntry(target->GetGUID(), player->GetGUID(), action);
								char msg[60];
								sprintf(msg, "%n has requested a Blood Money duel with you!", player->GetName());
								creature->MonsterWhisper(msg, target->GetGUID(), true);
							}
							else
								ChatHandler(target->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou cannot request a duel with the same person!");
						}
						else
							ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou cannot request a duel with somebody that has challenged you!");
						player->CLOSE_GOSSIP_MENU();
						return true;
					}
					else
					{
						uint32 money = action*10000;
						if (target->GetMoney() < money)
						{
							ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFThat player does not have enough money to make the bet!");
							player->CLOSE_GOSSIP_MENU();
							return false;
						}
						if (player->GetMoney() < money)
						{
							ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou do not have enough money to make the bet!");
							player->CLOSE_GOSSIP_MENU();
							return false;
						}

						bool found = false;
						if (HasBloodMoneyChallenger(player->GetGUID()))
						{
							BloodMoneyList list = m_bloodMoney[player->GetGUID()];
							for (BloodMoneyList::const_iterator itr = list.begin(); itr != list.end(); ++itr)
								if (itr->guid == target->GetGUID())
									found = true;
						}
						if (!found)
						{
							if (!HasBloodMoneyChallenger(target->GetGUID(), player->GetGUID()))
							{
								AddBloodMoneyEntry(target->GetGUID(), player->GetGUID(), money);
								char msg[60];
								sprintf(msg, "%s has requested a Blood Money duel with you!", player->GetName());
								creature->MonsterWhisper(msg, target->GetGUID(), true);
							}
							else
								ChatHandler(target->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou cannot request a duel with the same person!");
						}
						else
							ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou cannot request a duel with somebody that has challenged you!");
						player->CLOSE_GOSSIP_MENU();
						return true;
					}
					
				}
				else
				{
					ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFThat player is not in your zone!");
					player->CLOSE_GOSSIP_MENU();
					return false;
				}
			}
			else
			{
				ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFThat player was not found!");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}
		}
		else
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFThat player was not found!");
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		player->CLOSE_GOSSIP_MENU();
		return true;
	}

};

class BloodMoneyReward : public PlayerScript
{
 public:
	 BloodMoneyReward() : PlayerScript("BloodMoneyReward") {}

	void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type) 
	{ 
		if (type == DUEL_INTERRUPTED)
			return;
		if (HasBloodMoneyChallenger(winner->GetGUID()) || HasBloodMoneyChallenger(loser->GetGUID()))
		{			 
			BloodMoneyList list1 = m_bloodMoney[winner->GetGUID()];
			BloodMoneyList list2 = m_bloodMoney[loser->GetGUID()];

			BloodMoneyList::const_iterator itr;
			for (itr = list1.begin(); itr != list1.end(); ++itr)
			{
				if (itr->guid == loser->GetGUID() && itr->accepted)
				{
					if (USE_TOKEN)
					{
						if (loser->GetItemCount(TOKEN_ID) > itr->amount)
						{
							winner->AddItem(TOKEN_ID, itr->amount);
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFCongratulations on winning %d tokens!", itr->amount);
							Item* item = loser->GetItemByEntry(TOKEN_ID);
							loser->DestroyItemCount(TOKEN_ID, itr->amount, true);
							RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
						}
						else
						{
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFSorry, but your opponent did not have enough tokens to pay off the bet");
							ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou did not have enough tokens to pay off the bet!");
						}
						return;
					}
					else
					{
						if (loser->GetMoney() > itr->amount)
						{
							winner->ModifyMoney(itr->amount);
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFCongratulations on winning %dg!", itr->amount/10000);
							loser->ModifyMoney((int32)(-itr->amount));
							RemoveBloodMoneyEntry(winner->GetGUID(), itr->guid);
						}
						else
						{
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFSorry, but your opponent did not have enough money to pay off the bet");
							ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou did not have enough money to pay off the bet!");
						}
						return;
					}
				}
			}
			for (itr = list2.begin(); itr != list2.end(); ++itr)
			{
				if (itr->guid == winner->GetGUID() && itr->accepted)
				{
					if (USE_TOKEN)
					{
						if (loser->GetItemCount(TOKEN_ID) > itr->amount)
						{
							winner->AddItem(TOKEN_ID, itr->amount);
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFCongratulations on winning %d tokens!", itr->amount);
							Item* item = loser->GetItemByEntry(TOKEN_ID);
							loser->DestroyItemCount(TOKEN_ID, itr->amount, true);
							RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
						}
						else
						{
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFSorry, but your opponent did not have enough tokens to pay off the bet");
							ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou did not have enough tokens to pay off the bet!");
						}
						return;
					}
					else
					{
						if (loser->GetMoney() > itr->amount)
						{
							winner->ModifyMoney(itr->amount);
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFCongratulations on winning %dg!", itr->amount/10000);
							loser->ModifyMoney((int32)(-itr->amount));
							RemoveBloodMoneyEntry(loser->GetGUID(), itr->guid);
						}
						else
						{
							ChatHandler(winner->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFSorry, but your opponent did not have enough money to pay off the bet");
							ChatHandler(loser->GetSession()).PSendSysMessage("|cff800C0C[Blood Money] |cffFFFFFFYou did not have enough money to pay off the bet!");
						}
						return;
					}
				}
			}

		 }
	 }
};

void AddSC_npc_blood_money()
{
	new BloodMoneyReward();
	new npc_blood_money();
}