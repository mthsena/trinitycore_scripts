/*******************************************************************************************
*						 __                           __ _   							   *
*					  /\ \ \___  _ __ ___  ___  ___  / _| |_ 							   *
*					 /  \/ / _ \| '_ ` _ \/ __|/ _ \| |_| __|							   *
*					/ /\  / (_) | | | | | \__ \ (_) |  _| |_ 							   *
*					\_\ \/ \___/|_| |_| |_|___/\___/|_|  \__|	- www.Nomsoftware.com -	   *
*                               The policy of Nomsoftware states: Releasing our software   *
*                               or any other files are protected. You cannot re-release    *
*                               anywhere unless you were given permission.                 *
*                           (C) Nomsoftware 'Nomsoft' 2011-2012. All rights reserved.      *
********************************************************************************************/
/**********************************************************
**********************************************************
 *                      Title:                          *
  *            NPC Arena Battle(Dire Maul)             *
   *                                                  *
    *             Idea by: QQrofl                    *
	 *            Sub-Ideas by: Foereaper           *
	  *            Scripted by: QQrofl             *
	   *      		Fondled by: Faded	          *
	    *    Mental Support by: Foereaper        *
		 *            Edited by: u4ea           *  
	      *    							       *
		   *  (C)Nomsoftware 'Nomsoft' 2012   *
		   *##################################*/
#include "npcs_dm_battle.h"

class npc_dire_arena_commander : public CreatureScript
{
   public:
	   npc_dire_arena_commander() : CreatureScript("npc_dire_arena_commander") { }

	   bool OnGossipHello(Player * player, Creature * creature)
	   {
		   if(player->isInCombat())
			   return false;

		   if(isBattleActive)
			   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I'm sorry, but a battle is already active.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
		   else
		       player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, MSG_FIGHT_COMPUTER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nevermind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
		   player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		   return true;
	   }

	   bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
	   {
		   if(sender != GOSSIP_SENDER_MAIN)
			   return false;
		   player->PlayerTalkClass->ClearMenus();
		   switch(actions)
		   {
		      case GOSSIP_ACTION_INFO_DEF+1:
				  
				   m_PlayerGUID = player->GetGUID();
				   playerName = player->GetName();
				   isBattleActive = true;
				   player->CastSpell(player, SPELL_TELEPORT_VISUAL);
				   player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
				   player->PlayerTalkClass->SendCloseGossip();
				  break;

		      case GOSSIP_ACTION_INFO_DEF+2:
					  player->PlayerTalkClass->SendCloseGossip();
				  break;

		      case GOSSIP_ACTION_INFO_DEF+3:
					  player->PlayerTalkClass->SendCloseGossip();
				  break;
		   }
		   return true;
	   }

	   struct npc_dire_arena_commanderAI : public ScriptedAI
	   {
		   npc_dire_arena_commanderAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 checkBattle;
		   uint32 checkPlayer;
		   bool checkIsDead;
		   bool resetOnce;

		   void Reset()
		   {
			   events.Reset();
			   player = NULL;
			   summons.DespawnAll();
			   checkIsDead = true;
			   resetOnce = false;
			   checkBattle = 2000;
			   checkPlayer = 1000;
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   events.Update(diff);

			   if(checkBattle <= diff)
			   {
				   if(!isBattleActive && m_PlayerGUID == 0 && !resetOnce)
				   {
					   events.Reset();
					   resetOnce = true;
				   }

				   if(isBattleActive && m_PlayerGUID != 0 && resetOnce)
				   {   
					   player = Unit::GetPlayer(*me, m_PlayerGUID);
					   events.ScheduleEvent(EVENT_CHECK_ACTIVITY, 1000);
					   resetOnce = false;
				   }
				   if(resetOnce)
					   checkBattle = 2000;
			   }
			   else
				   checkBattle -= diff;

			   if(checkPlayer <= diff) // Checking battle as well
			   {
				   if(m_PlayerGUID == 0)
					   return;

				   if(hasLogged || !inZone)
				   {
						isBattleActive = false;
						summons.DespawnAll();
						events.Reset();
						isWaveBossDead = 0;
						checkIsDead = true;
						hasLogged = false;
						inZone = true;
						resetOnce = false;
						player = NULL;
						m_PlayerGUID = NULL;
						playerName = "";
						sWorld->SendGlobalText("A challenger has been scared off and left the Dire Maul Arena Challenge! Who's next?", NULL);
				   }
					checkPlayer = 1000;
			   }
			   else
				   checkPlayer -= diff;

			   if (isWaveBossDead == 1 && checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = false;
			   }
			   else if (isWaveBossDead == 2 && !checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = true;
			   }
			   else if (isWaveBossDead == 3 && checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = false;
			   }
			   else if (isWaveBossDead == 4 && !checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = true;
			   }
			   else if (isWaveBossDead == 5 && checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = false;
			   }
			   else if (isWaveBossDead == 6 && !checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = true;
			   }
			   else if (isWaveBossDead == 7 && checkIsDead)
			   {
				   events.ScheduleEvent(EVENT_CHECK_WAVES, 1000);
				   checkIsDead = false;
			   }

			   while(uint32 eventIds = events.ExecuteEvent())
			   {
				   switch(eventIds)
				   {
					  case EVENT_CHECK_ACTIVITY:
						  {
							  if(isBattleActive)
							  {
								   MessageOnWave(me, EVENT_CHECK_ACTIVITY);
								   events.ScheduleEvent(EVENT_FIRST_WAVE, 10000);
							  }
							   else
								   events.ScheduleEvent(EVENT_CHECK_ACTIVITY, 1000);
						  }break;

					  case EVENT_CHECK_WAVES:
						  {
							  if(!player)
								  return;

							  if(!isBattleActive)
							  {
								  summons.DespawnAll();
								  checkIsDead = true;
								  resetOnce = false;
								  return;
							  }

							  int itemCount = player->GetItemCount(ITEM_INTRAVENOUS_HEALING_POTION);
							  if(itemCount == 0)
								  player->AddItem(ITEM_INTRAVENOUS_HEALING_POTION, 1);
							  if(isWaveBossDead == 1) // Red Blood Guard
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  events.ScheduleEvent(EVENT_FIRST_WAVE_TREAT, 25000);
								  isWaveBossDead = 0;
							  }
							  
							  if (isWaveBossDead == 2) // Spawn Event
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  events.ScheduleEvent(EVENT_FIRST_WAVE_ELITE, 35000);
								  isWaveBossDead = 0;
							  }

							  if(isWaveBossDead == 3) // Hank the Tank
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
								  events.ScheduleEvent(EVENT_SECOND_WAVE, 35000);
								  isWaveBossDead = 0;
							  }

							  if(isWaveBossDead == 4) // Rogue Initiates
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
								  events.ScheduleEvent(EVENT_SECOND_WAVE_TREAT, 35000);
								  isWaveBossDead = 0;
							  }

							  if(isWaveBossDead == 5) // The Unholys
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
								  events.ScheduleEvent(EVENT_SECOND_WAVE_ELITE, 40000);
								  isWaveBossDead = 0;
							  }

							  if(isWaveBossDead == 6) // The Riders of the Ice
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f);
								  events.ScheduleEvent(EVENT_FINAL_WAVE_BOSS, 35000);
								  isWaveBossDead = 0;
							  }

							  if(isWaveBossDead == 7) // Dragon Final Event
							  {
								  MessageOnWave(me, EVENT_CHECK_WAVES);
								  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
								  AddEndRewards(player, 10, PVP_END_TOKEN, 1);
								  events.ScheduleEvent(EVENT_COMPLETED_WAVES, 5000);
								  isWaveBossDead = 0;
							  }
						  }break;

					  case EVENT_FIRST_WAVE:
						  sLog->outInfo(LOG_FILTER_GENERAL, 0);
						  MessageOnWave(me, EVENT_FIRST_WAVE);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  me->SummonCreature(waveList[0], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, 
							  TEMPSUMMON_MANUAL_DESPAWN, 0);
						  break;

					  case EVENT_FIRST_WAVE_TREAT:
						  MessageOnWave(me, EVENT_FIRST_WAVE_TREAT);
						  me->SummonCreature(waveList[1], -3739.533447f, 1095.419434f, 131.969559f, 3.029968f, TEMPSUMMON_MANUAL_DESPAWN, 0);
						  me->SummonCreature(NPC_PORTAL, m_WaveSpawns[1].m_positionX, m_WaveSpawns[1].m_positionY, m_WaveSpawns[1].m_positionZ, m_WaveSpawns[1].m_orientation,
							    TEMPSUMMON_MANUAL_DESPAWN, 0);
						  me->SummonCreature(NPC_PORTAL, m_WaveSpawns[2].m_positionX, m_WaveSpawns[2].m_positionY, m_WaveSpawns[2].m_positionZ, m_WaveSpawns[2].m_orientation, 
							    TEMPSUMMON_MANUAL_DESPAWN, 0);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  break;

					  case EVENT_FIRST_WAVE_ELITE:
						  MessageOnWave(me, EVENT_FIRST_WAVE_ELITE);
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  me->SummonCreature(waveList[8], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation,
								TEMPSUMMON_MANUAL_DESPAWN, 0);
						  break;

					  case EVENT_SECOND_WAVE:
						  MessageOnWave(me, EVENT_SECOND_WAVE);
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  me->SummonCreature(waveList[10], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation,
								TEMPSUMMON_MANUAL_DESPAWN, 0);
						  break;

					  case EVENT_SECOND_WAVE_TREAT:
						  MessageOnWave(me, EVENT_SECOND_WAVE_TREAT);
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  me->SummonCreature(waveList[13], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation,
								TEMPSUMMON_MANUAL_DESPAWN, 0);
						  break;

					  case EVENT_SECOND_WAVE_ELITE:
						  MessageOnWave(me, EVENT_SECOND_WAVE_ELITE);
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  me->SummonCreature(waveList[16], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation,
								TEMPSUMMON_MANUAL_DESPAWN, 0);
						  break;

					  case EVENT_FINAL_WAVE_BOSS:
						  sLog->outInfo(LOG_FILTER_GENERAL, 0);
						  MessageOnWave(me, EVENT_FINAL_WAVE_BOSS);
						  player->PlayDirectSound(SOUND_HORN_WAVE_START);
						  player->CastSpell(player, SPELL_TELEPORT_VISUAL);
						  player->TeleportTo(1, -3739.533447f, 1095.419434f, 131.969559f, 3.029968f); // Making sure you're in the right place
						  me->SummonCreature(waveList[19], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation,
								TEMPSUMMON_MANUAL_DESPAWN, 0);
						  break;

					  case EVENT_COMPLETED_WAVES:
						  me->MonsterYell("Congratulations to our finest Gladiator that went through a lot to earn our rewards! Who will be our next challenger?", 
							  LANG_UNIVERSAL, me->GetGUID());
						  DoSendCompleteMessage(player->GetName());
						  player->TeleportTo(1, sTeleOut[0].m_positionX, sTeleOut[0].m_positionY, sTeleOut[0].m_positionZ, sTeleOut[0].m_orientation);
						  isBattleActive = false;
						  m_PlayerGUID = NULL;
						  playerName = "";
						  summons.DespawnAll();
						  events.Reset();
						  isWaveBossDead = 0;
						  checkIsDead = true;
						  break;
					}
				}
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
		   }
	   private:
		   EventMap events;
		   Player * player;
		   SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dire_arena_commanderAI(pCreature);
	   }
};

class npc_dire_maul_rb_guard : public CreatureScript
{
   public:
	   npc_dire_maul_rb_guard() : CreatureScript("npc_dire_maul_rb_guard") { }

	   struct npc_dire_maul_rb_guardAI : public ScriptedAI
	   {
		   npc_dire_maul_rb_guardAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 uiCharge;
		   uint32 uiMortalStrike;
		   uint32 uiCheckOutOfRange;
		   bool spawnMinis;

		   void Reset()
		   {
			   spawnMinis = true;
			   uiCharge = 2000;
			   uiMortalStrike = urand(5000, 8000);
			   me->MonsterYell("You can't defeat me!", LANG_UNIVERSAL, me->GetGUID());
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 45233);
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me, summons);
		   }

		   void JustDied(Unit * killer)
		   {
			   if(killer && killer->GetTypeId() != TYPEID_PLAYER)
				   return;
			   me->PlayDirectSound(SOUND_WAVE_COMPLETE, killer->ToPlayer());
			   isWaveBossDead = 1;
			   summons.DespawnAll();
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
			   summoned->AI()->AttackStart(me->getVictim());
			   summoned->GetMotionMaster()->MoveChase(me->getVictim(), 100.0f);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!UpdateVictim())
			   {
				   summons.DespawnAll();
				   return;
			   }

			   ScriptedAI::UpdateAI(diff);
			   if(!isBattleActive)
			   {
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(uiCharge <= diff)
			   {
				   me->CastSpell(me->getVictim(), SPELL_BERSERKER_CHARGE);
				   uiCharge = 12000;
			   }
			   else
				   uiCharge -= diff;

			   if(uiMortalStrike <= diff)
			   {
				   me->CastSpell(me->getVictim(), SPELL_MORTAL_STRIKE);
				   me->CastSpell(me->getVictim(), SPELL_DEEP_WOUNDS); // Cast deep wounds after Mortal strike
				   uiMortalStrike = urand(5000, 120000);
			   }
			   else
				   uiMortalStrike -= diff;

			   if(me->GetHealthPct() <= 45 && spawnMinis)
			   {
				   me->MonsterYell("Minions, come to my aid!", LANG_UNIVERSAL, me->GetGUID());
				   me->SummonCreature(NPC_RED_BLOOD_GUARD_MINI, me->GetPositionX(), me->GetPositionY()+1, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
				   me->SummonCreature(NPC_RED_BLOOD_GUARD_MINI2, me->GetPositionX()+2, me->GetPositionY()+1, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
				   me->SummonCreature(NPC_RED_BLOOD_GUARD_MINI3, me->GetPositionX()+2, me->GetPositionY()+1, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
				   spawnMinis = false;
			   }
			   DoMeleeAttackIfReady();
		   }
	   private:
		   SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dire_maul_rb_guardAI(pCreature);
	   }
};

class npc_red_blood_mini : public CreatureScript
{
   public:
	   npc_red_blood_mini() : CreatureScript("npc_red_blood_mini") { }

	   struct npc_red_blood_miniAI : public ScriptedAI
	   {
		   npc_red_blood_miniAI(Creature * c) : ScriptedAI(c) { me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 45233); }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_red_blood_miniAI(pCreature);
	   }
};

class npc_dm_wave_trigger : public CreatureScript
{
   public:
	   npc_dm_wave_trigger() : CreatureScript("npc_dm_wave_trigger") { }

	   struct npc_dm_wave_triggerAI : public ScriptedAI
	   {
		   npc_dm_wave_triggerAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 startSpawnWave;
		   int spawnPhase;

		   void Reset()
		   {
			   startSpawnWave = 1000;
			   spawnPhase = 0;
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!isBattleActive)
			   {
				   summons.DespawnAll();
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(startSpawnWave <= diff)
			   {
				   switch(spawnPhase)
				   {
				      case 0:
						  {
						      spawnPhase = 1;
							  DoPortalSpawns();
							  startSpawnWave = 13000;
						  }break;

				      case 1:
						  {
							  spawnPhase = 2;
							  DoPortalSpawns();
							  startSpawnWave = 13000;
						  }break;

				      case 2:
						  {
							  spawnPhase = 3;
							  DoPortalSpawns();
							  startSpawnWave = 13000;
						  }break;

				      case 3:
						  {
							  spawnPhase = 4;
							  for(int i = 0; i < 2; i++)
								DoPortalSpawns();
							  startSpawnWave = 25000;
						  }break;

				      case 4:
						  {
							  spawnPhase = 5;
							  for(int i = 0; i < 2; i++)
								DoPortalSpawns();
							  startSpawnWave = 25000;
						  }break;

				      case 5:
						  {
							  spawnPhase = 6;
							  for(int i = 0; i < 4; i++)
								DoPortalSpawns();
							  startSpawnWave = 36000;
						  }break;

				      case 6:
						  {
							  spawnPhase = 7;
							  for(int i = 0; i < 4; i++)
								DoPortalSpawns();
							  startSpawnWave = 36000;
						  }break;

				      case 7:
						  {
							  spawnPhase = 8;
							  DoPortalSpawns();
							  startSpawnWave = 10000;
						  }break;

				      case 8:
						  {
							  spawnPhase = 9;
							  DoPortalSpawns();
							  startSpawnWave = 10000;
						  }break;

				      case 9:
						  {
							  spawnPhase = 10;
							  DoPortalSpawns();
							  startSpawnWave = 15000;
						  }break;

				      case 10:
						  {
							  spawnPhase = 11;
							  for(int i = 0; i < 4; i++)
								DoPortalSpawns();
							  startSpawnWave = 60000;
						  }break;

				      case 11:
						  {
							  if(Player * player = Unit::GetPlayer(*me, m_PlayerGUID))
							  {
								  if(!player)
									  return;
								  me->PlayDirectSound(SOUND_WAVE_COMPLETE, player);
							  }
							  isWaveBossDead = 2;
							  summons.DespawnAll();
							  spawnPhase = 0;
							  me->DespawnOrUnsummon(1);
						  }break;
				   }
			   }
			   else
				   startSpawnWave -= diff;
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
			   if(Player * player = Unit::GetPlayer(*me, m_PlayerGUID))
			   {
				   if(!player)
					   return;
				   summoned->SetInCombatWith(player);
				   summoned->AI()->AttackStart(player);
				   summoned->GetMotionMaster()->MoveChase(player, 500.0f);
			   }
		   }

		   void DoPortalSpawns() // Spawns Random Npcs
		   {
			   int random = urand(0, 4);
			   switch(random)
			   {
			       case 0:
					   me->SummonCreature(waveList[2], m_WaveSpawns[1].m_positionX, m_WaveSpawns[1].m_positionY, m_WaveSpawns[1].m_positionZ, m_WaveSpawns[1].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

			       case 1:
					   me->SummonCreature(waveList[3], m_WaveSpawns[1].m_positionX, m_WaveSpawns[1].m_positionY, m_WaveSpawns[1].m_positionZ, m_WaveSpawns[1].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

			       case 2:
					   me->SummonCreature(waveList[4], m_WaveSpawns[1].m_positionX, m_WaveSpawns[1].m_positionY, m_WaveSpawns[1].m_positionZ, m_WaveSpawns[1].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

			       case 3:
					   me->SummonCreature(waveList[5], m_WaveSpawns[1].m_positionX, m_WaveSpawns[1].m_positionY, m_WaveSpawns[1].m_positionZ, m_WaveSpawns[1].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

			       case 4:
					   me->SummonCreature(waveList[6], m_WaveSpawns[1].m_positionX, m_WaveSpawns[1].m_positionY, m_WaveSpawns[1].m_positionZ, m_WaveSpawns[1].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;
			   }
			   int random2 = urand(0, 4);
			   switch(random2)
			   {
				   case 0:
					   me->SummonCreature(waveList[2], m_WaveSpawns[2].m_positionX, m_WaveSpawns[2].m_positionY, m_WaveSpawns[2].m_positionZ, m_WaveSpawns[2].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

				   case 1:
					   me->SummonCreature(waveList[3], m_WaveSpawns[2].m_positionX, m_WaveSpawns[2].m_positionY, m_WaveSpawns[2].m_positionZ, m_WaveSpawns[2].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

				   case 2:
					   me->SummonCreature(waveList[4], m_WaveSpawns[2].m_positionX, m_WaveSpawns[2].m_positionY, m_WaveSpawns[2].m_positionZ, m_WaveSpawns[2].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

				   case 3:
					   me->SummonCreature(waveList[5], m_WaveSpawns[2].m_positionX, m_WaveSpawns[2].m_positionY, m_WaveSpawns[2].m_positionZ, m_WaveSpawns[2].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;

				   case 4:
					   me->SummonCreature(waveList[6], m_WaveSpawns[2].m_positionX, m_WaveSpawns[2].m_positionY, m_WaveSpawns[2].m_positionZ, m_WaveSpawns[2].m_orientation,
						   TEMPSUMMON_MANUAL_DESPAWN, 0);
					   break;
			   }
		   }
	   private:
		   SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_wave_triggerAI(pCreature);
	   }
};

class npc_dm_wave_spawns : public CreatureScript
{
   public:
	   npc_dm_wave_spawns() : CreatureScript("npc_dm_wave_spawns") { }

	   struct npc_dm_wave_spawnsAI : public ScriptedAI
	   {
		   npc_dm_wave_spawnsAI(Creature * c) : ScriptedAI(c) { }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!isBattleActive)
				   me->DespawnOrUnsummon(1);

			   if(!UpdateVictim())
				   return;

			   DoMeleeAttackIfReady();
		   }
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_wave_spawnsAI(pCreature);
	   }
};

class npc_dm_wave_portals : public CreatureScript
{
   public:
	   npc_dm_wave_portals() : CreatureScript("npc_dm_wave_portals") { }

	   struct npc_dm_wave_portalsAI : public ScriptedAI
	   {
		   npc_dm_wave_portalsAI(Creature * c) : ScriptedAI(c) { }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!isBattleActive)
				   me->DespawnOrUnsummon(1);
		   }
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_wave_portalsAI(pCreature);
	   }
};

uint32 hankAuras[] = { SPELL_BATTLE_STANCE, SPELL_INCREASE_BLOCK_VALUE, SPELL_INCREASE_DEFENSE_RATING, SPELL_INCREASE_DODGE_RATING };
class npc_dm_hank_the_tank : public CreatureScript
{
   public:
	   npc_dm_hank_the_tank() : CreatureScript("npc_dm_hank_the_tank") { }

	   struct npc_dm_hank_the_tankAI : public ScriptedAI
	   {
		   npc_dm_hank_the_tankAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 shoutBuff;
		   uint32 groundStomp;
		   uint32 uiExecute;
		   uint32 tankStrike;
		   uint32 uiRend;
		   uint32 shieldBlock;
		   uint32 shieldBash;

		   void Reset()
		   {
			   me->MonsterYell("You will succumb to death, young scums!", LANG_UNIVERSAL, me->GetGUID());
			   summons.DespawnAll();
			   me->SummonCreature(waveList[9], me->GetPositionX(), me->GetPositionY()+3, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
			   shoutBuff = 1000;
			   groundStomp = 6000;
			   shieldBash = urand(9000, 13000);
			   uiExecute = urand(21000, 26000);
			   shieldBlock = 18000;
			   tankStrike = urand(4000, 8000);
			   uiRend = 11000;
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51516);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+1, 51533);
			   for(int i = 0; i < 4; i++)
				   me->AddAura(hankAuras[i], me);
		   }

		   void EnterCombat(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoCast(who, SPELL_TANK_CHARGE);
		   }

		   void JustDied(Unit * killer)
		   {
			   if(killer && killer->GetTypeId() != TYPEID_PLAYER)
				   return;
			   me->PlayDirectSound(SOUND_WAVE_COMPLETE, killer->ToPlayer());
			   summons.DespawnAll();
			   isWaveBossDead = 3;
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me, summons);
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!UpdateVictim())
				   return;

			   if(!isBattleActive)
			   {
				   summons.DespawnAll();
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(shoutBuff <= diff)
			   {
				   me->AddAura(SPELL_SHOUT_BUFF, me);
				   shoutBuff = 120000; // 2 minutes
			   }
			   else
				   shoutBuff -= diff;

			   if(groundStomp <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_GROUND_STOMP, true);
				   groundStomp = 6000;
			   }
			   else
				   groundStomp -= diff;

			   if(uiExecute <= diff)
			   {
				   if(me->getVictim()->GetHealthPct() <= 20)
					   DoCast(me->getVictim(), SPELL_EXECUTE);
				   uiExecute = urand(21000, 26000);
			   }
			   else
				   uiExecute -= diff;

			   if(shieldBlock <= diff)
			   {
				   DoCast(me, SPELL_SHIELD_BLOCK); // Cast on self
				   shieldBlock = 18000;
			   }
			   else
				   shieldBlock -= diff;

			   if(tankStrike <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_TANK_STRIKE);
				   tankStrike = urand(4000, 8000);
			   }
			   else
				   tankStrike -= diff;

			   if(uiRend <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_REND, true);
				   uiRend = 15000;
			   }
			   else
				   uiRend -= diff;
			   DoMeleeAttackIfReady();
		   }
	   private:
		   SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_hank_the_tankAI(pCreature);
	   }
};

class npc_dm_field_medic : public CreatureScript
{
   public:
	   npc_dm_field_medic() : CreatureScript("npc_dm_field_medic") { }

	   struct npc_dm_field_medicAI : public ScriptedAI
	   {
		   npc_dm_field_medicAI(Creature * c) : ScriptedAI(c) { }

		   uint32 uiRegrowthTimer;
		   uint32 uiHealingTouchTimer;
		   uint32 uiHealRejuvTimer;
		   uint32 uiFlashHealTimer;
		   uint32 uiPowerShieldTimer;
		   uint32 uiLifebloomTimer;
		   int casted;
		   bool showOnce;
		   bool canHealMaster;

		   void Reset()
		   {
			   uiRegrowthTimer = urand(11000, 13000);
			   uiHealingTouchTimer = urand(6000, 8000);
			   uiHealRejuvTimer = 15000;
			   uiFlashHealTimer = urand(14000, 17000);
			   uiPowerShieldTimer = 1000;
			   uiLifebloomTimer = 2000;
			   canHealMaster = true;
			   showOnce = false;
			   int casted = 0;
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51404);
			   me->AddAura(SPELL_HEAL_AURA_HOTS, me);
			   hank = NULL;
			   hank = me->FindNearestCreature(NPC_HANK_THE_TANK, 50.0f, true);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!hank)
				   return;

			   if(hank && hank->isDead() && !showOnce)
			   {
				   me->MonsterYell("Master Dead?!!! I give up!...", LANG_UNIVERSAL, me->GetGUID());
				   me->setFaction(35);
				   me->DespawnOrUnsummon(1);
				   showOnce = true;
				   return;
			   }

			   if(hank && !hank->isInCombat())
				   return;

			   if(hank && hank->GetHealthPct() >= 100)
				   canHealMaster = false;
			   else
				   canHealMaster = true;

			   if(uiRegrowthTimer <= diff)
			   {
				   if(canHealMaster)
					   DoCast(hank, SPELL_HEAL_REGROWTH, true);
				   if(me->GetHealthPct() <= 70)
					   DoCast(me, SPELL_HEAL_REGROWTH, true);
				   uiRegrowthTimer = urand(10000, 16000);
			   }
			   else
				   uiRegrowthTimer -= diff;

			   if(uiHealingTouchTimer <= diff)
			   {
				   if(hank->GetHealthPct() <= 45 && canHealMaster)
					   DoCast(hank, SPELL_HEAL_NORMAL, true);
				   if(me->GetHealthPct() <= 30)
					   DoCast(me, SPELL_HEAL_NORMAL, true);
				   uiHealingTouchTimer = urand(6000, 8000);
			   }
			   else
				   uiHealingTouchTimer -= diff;

			   if(uiHealRejuvTimer <= diff)
			   {
				   if(canHealMaster)
					   DoCast(hank, SPELL_HEAL_REJUV, true);
				   if(me->GetHealthPct() <= 90)
					   DoCast(me, SPELL_HEAL_REJUV, true);
				   uiHealRejuvTimer = 15000;
			   }
			   else
				   uiHealRejuvTimer -= diff;

			   if(uiFlashHealTimer <= diff)
			   {
				   if(canHealMaster)
					   DoCast(hank, SPELL_FLASH_HEAL, true);
				   if(me->GetHealthPct() <= 55)
					   DoCast(me, SPELL_FLASH_HEAL, true);
				   uiFlashHealTimer = urand(14000, 17000);
			   }
			   else
				   uiFlashHealTimer -= diff;

			   if(uiPowerShieldTimer <= diff)
			   {
				   DoCast(me, SPELL_POWER_WORD_SHIELD);
				   uiPowerShieldTimer = 30000;
			   }
			   else
				   uiPowerShieldTimer -= diff;

			   if(uiLifebloomTimer <= diff)
			   {
				   if(canHealMaster)
				   {
					   DoCast(hank, SPELL_HEAL_LIFEBLOOM, true); // Stacking
					   casted++; // Increment the value
					   if(casted != 3)
						   uiLifebloomTimer = 2000;
					   else // Prevents further stacking of this spell
					   {
						   uiLifebloomTimer = 26000;
						   casted = 0;
					   }
				   }
			   }
			   else
				   uiLifebloomTimer -= diff;
		   }
	   private:
		   Creature * hank;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_field_medicAI(pCreature);
	   }
};

class npc_dm_main_rogue : public CreatureScript
{
   public:
	   npc_dm_main_rogue() : CreatureScript("npc_dm_main_rogue") { }

	   struct npc_dm_main_rogueAI : public ScriptedAI
	   {
		   npc_dm_main_rogueAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 uiVanishTimer;
		   uint32 uiCheapShotTimer;
		   uint32 uiStrikeTimer;
		   uint32 uiFinisherTimer;
		   uint32 uiKickTimer;
		   uint32 uiWaitTimer;
		   uint32 uiRuptureTimer;
		   int comboPoints;
		   bool InStealth;
		   bool InVanish;

		   void Reset()
		   {
			   me->MonsterYell("We'll teach you a valued lesson.", LANG_UNIVERSAL, me->GetGUID());
			   InStealth = true;
			   InVanish = false;
			   comboPoints = 0;
			   uiFinisherTimer = 4000;
			   uiStrikeTimer = 6000;   
			   uiRuptureTimer = 9000;
			   uiKickTimer = 10000;
			   uiVanishTimer = 17000;
			   DoCast(me, SPELL_ROGUE_STEALTH);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51517);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+1, 51441);
			   summons.DespawnAll();
			   me->SummonCreature(waveList[11], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY+3, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, TEMPSUMMON_MANUAL_DESPAWN, 0);
			   me->SummonCreature(waveList[12], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY-3, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, TEMPSUMMON_MANUAL_DESPAWN, 0);
		   }

		   void JustDied(Unit * killer)
		   {
			   if(killer && killer->GetTypeId() != TYPEID_PLAYER)
				   return;
			   me->PlayDirectSound(SOUND_WAVE_COMPLETE, killer->ToPlayer());
			   summons.DespawnAll();
			   isWaveBossDead = 4;
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me, summons);
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!UpdateVictim())
				   return;

			   if(!isBattleActive)
			   {
				   summons.DespawnAll();
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(InStealth)
			   {
				   me->CastSpell(me->getVictim(), SPELL_ROGUE_CHEAP_SHOT, true);
				   InStealth = false;
			   }

			   if(uiStrikeTimer <= diff)
			   {
				   if(!InVanish)
				   {
					   DoCast(me->getVictim(), SPELL_ROGUE_STRIKE);
					   comboPoints++;
				   }   
				   uiStrikeTimer = 6000;
			   }
			   else
				   uiStrikeTimer -= diff;

			   if(uiFinisherTimer <= diff)
			   {
				   if(!InVanish && comboPoints >= 2)
				   {
					   me->CastSpell(me->getVictim(), SPELL_ROGUE_FINISHER);
					   comboPoints = 0;
				   }
				   uiFinisherTimer = 4000;
			   }
			   else
				   uiFinisherTimer -= diff;

			   if(uiKickTimer <= diff)
			   {
				   if(!InVanish)
					   DoCast(me->getVictim(), SPELL_ROGUE_KICK);
				   uiKickTimer = 10000;
			   }
			   else
				   uiKickTimer -= diff;

			   if(uiVanishTimer <= diff)
			   {
				   DoCast(me, SPELL_ROGUE_VANISH);
				   InVanish = true;
				   uiVanishTimer = 20000;
				   uiWaitTimer = 6000;
			   }
			   else
				   uiVanishTimer -= diff;

			   if(uiRuptureTimer <= diff)
			   {
				   if(!InVanish)
					   DoCast(me->getVictim(), SPELL_ROGUE_RUPTURE, true);
				   uiRuptureTimer = 9000;
			   }
			   else
				   uiRuptureTimer -= diff;

			   if(InVanish)
			   {
				   if(uiWaitTimer <= diff)
				   {
					   me->CastSpell(me->getVictim(), SPELL_ROGUE_CHEAP_SHOT, true);
					   me->MonsterYell("Attack!", LANG_UNIVERSAL, me->GetGUID());
					   InVanish = false;
				   }
				   else
					   uiWaitTimer -= diff;
			   }
			   if(!InVanish)
				   DoMeleeAttackIfReady();
		   }
	   private:
		   SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_main_rogueAI(pCreature);
	   }
};

class npc_dm_rogue_initiate : public CreatureScript
{
   public:
	   npc_dm_rogue_initiate() : CreatureScript("npc_dm_rogue_initiate") { }

	   struct npc_dm_rogue_initiateAI : public ScriptedAI
	   {
		   npc_dm_rogue_initiateAI(Creature * c) : ScriptedAI(c) { }

		   uint32 uiVanishTimer;
		   uint32 uiCheapShotTimer;
		   uint32 uiStrikeTimer;
		   uint32 uiFinisherTimer;
		   uint32 uiKickTimer;
		   uint32 uiWaitTimer;
		   uint32 uiKidneyShotTimer;
		   int comboPoints;
		   bool InVanish;
		   bool InStealth;

		   void Reset()
		   {
			   InVanish = false;
			   InStealth = true;
			   comboPoints = 0;
			   uiFinisherTimer = 4000;
			   uiStrikeTimer = 6000;   
			   uiKickTimer = 10000;
			   uiKidneyShotTimer = 14000;
			   uiVanishTimer = 17000;	   
			   DoCast(me, SPELL_ROGUE_STEALTH);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51517);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+1, 51441);
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!UpdateVictim())
				   return;

			   if(InStealth)
			   {
				   DoCast(me->getVictim(), SPELL_ROGUE_BACKSTAB);
				   InStealth = false;
			   }

			   if(uiStrikeTimer <= diff)
			   {
				   if(!InVanish)
				   {
					   DoCast(me->getVictim(), SPELL_ROGUE_STRIKE);
					   comboPoints++;
				   }   
				   uiStrikeTimer = 6000;
			   }
			   else
				   uiStrikeTimer -= diff;

			   if(uiFinisherTimer <= diff)
			   {
				   if(!InVanish && comboPoints >= 2)
				   {
					   me->CastSpell(me->getVictim(), SPELL_ROGUE_FINISHER);
					   comboPoints = 0;
				   }
				   uiFinisherTimer = 4000;
			   }
			   else
				   uiFinisherTimer -= diff;

			   if(uiKickTimer <= diff)
			   {
				   if(!InVanish)
					   DoCast(me->getVictim(), SPELL_ROGUE_KICK);
				   uiKickTimer = 10000;
			   }
			   else
				   uiKickTimer -= diff;

			   if(uiKidneyShotTimer <= diff)
			   {
				   if(!InVanish)
					   DoCast(me->getVictim(), SPELL_ROGUE_KIDNEY_SHOT);
				   uiKidneyShotTimer = 12000;
			   }
			   else
				   uiKidneyShotTimer -= diff;

			   if(uiVanishTimer <= diff)
			   {
				   DoCast(me, SPELL_ROGUE_VANISH);
				   InVanish = true;
				   uiVanishTimer = 20000;
				   uiWaitTimer = 6000;
			   }
			   else
				   uiVanishTimer -= diff;

			   if(InVanish)
			   {
				   if(uiWaitTimer <= diff)
				   {
					   DoCast(me->getVictim(), SPELL_ROGUE_BACKSTAB);
					   InVanish = false;
				   }
				   else
					   uiWaitTimer -= diff;
			   }
			   if(!InVanish)
				   DoMeleeAttackIfReady();
		   }
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_rogue_initiateAI(pCreature);
	   }
};

class npc_dm_main_unholy : public CreatureScript
{
   public:
	   npc_dm_main_unholy() : CreatureScript("npc_dm_main_unholy") { }

	   struct npc_dm_main_unholyAI : public ScriptedAI
	   {
		   npc_dm_main_unholyAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 uiCinematic;
		   uint32 uiAoeTimer;
		   uint32 uiPlagueStrikeTimer;
		   uint32 uiStangulateTimer;
		   uint32 uiDeathStrikeTimer;
		   uint32 uiArmyOfTheDeadTimer;
		   int cinematicPassed;
		   bool checkGuin;
		   bool boneArmor;

		   void Reset()
		   {
			   me->MonsterSay("What is this? A trap?", LANG_UNIVERSAL, me->GetGUID());
			   uiCinematic = 9000;
			   cinematicPassed = 0;
			   checkGuin = true;
			   boneArmor = true;
			   me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
			   me->SetReactState(REACT_PASSIVE);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51393);
			   summons.DespawnAll();
			   twin = me->SummonCreature(waveList[14], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY+3, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, TEMPSUMMON_MANUAL_DESPAWN, 0);
			   guin = me->SummonCreature(waveList[15], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY-3, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, TEMPSUMMON_MANUAL_DESPAWN, 0);
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me, summons);
			   twin = NULL;
			   guin = NULL;
		   }

		   void JustDied(Unit * killer)
		   {
			   if(killer && killer->GetTypeId() != TYPEID_PLAYER)
				   return;
			   me->PlayDirectSound(SOUND_WAVE_COMPLETE, killer->ToPlayer());
			   summons.DespawnAll();
			   twin = NULL;
			   guin = NULL;
			   isWaveBossDead = 5;
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!isBattleActive)
			   {
				   summons.DespawnAll();
				   twin = NULL;
				   guin = NULL;
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(uiCinematic <= diff)
			   {
				   switch(cinematicPassed)
				   {
					   case 0:
						   me->MonsterSay("Ahh, so this thing wants to fight, huh?", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 1;
						   uiCinematic = 10000;
						   break;

					   case 1:
						   me->MonsterSay("Don't be a fool!", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 2;
						   uiCinematic = 9000;
						   break;

					   case 2:
						   me->MonsterSay("Twin, no! Let him go. We can just watch, for now....", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 3;
						   break;
				   }
			   }
			   else
				   uiCinematic -= diff;

			   if(checkGuin)
			   {
				   if(guin && guin->isDead())
				   {
					   me->MonsterYell("SO BE IT!", LANG_UNIVERSAL, me->GetGUID());
					   me->AddAura(SPELL_UNHOLY_BONE_SHIELD, me);
					   me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
					   uiAoeTimer = 25000;
					   uiPlagueStrikeTimer = urand(5000, 8000);
					   uiDeathStrikeTimer = urand(9000, 12000);
					   uiStangulateTimer = 15000;
					   uiArmyOfTheDeadTimer = 30000;
					   me->SetReactState(REACT_AGGRESSIVE);
					   if(twin)
					   {
						   twin->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
						   twin->SetReactState(REACT_AGGRESSIVE);
					   }
					   checkGuin = false;
				   }
			   }

			   if(!UpdateVictim())
				   return;

			   if(HealthBelowPct(25) && boneArmor)
			   {
				   me->AddAura(SPELL_UNHOLY_BONE_SHIELD, me);
				   boneArmor = false;
			   }

			   if(uiAoeTimer <= diff)
			   {
				   me->CastSpell(me->getVictim()->GetPositionX(), me->getVictim()->GetPositionY(), me->getVictim()->GetPositionZ(), SPELL_UNHOLY_AOE, true);
				   uiAoeTimer = 25000;
			   }
			   else
				   uiAoeTimer -= diff;

			   if(uiPlagueStrikeTimer <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_UNHOLY_PLAGUE_STRIKE);
				   uiPlagueStrikeTimer = urand(5000, 8000);
			   }
			   else
				   uiPlagueStrikeTimer -= diff;

			   if(uiStangulateTimer <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_UNHOLY_STANGULATE, true);
				   uiStangulateTimer = 15000;
			   }
			   else
				   uiStangulateTimer -= diff;

			   if(uiDeathStrikeTimer <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_UNHOLY_DEATH_STRIKE);
				   uiDeathStrikeTimer = urand(9000, 12000);
			   }
			   else
				   uiDeathStrikeTimer -= diff;

			   if(uiArmyOfTheDeadTimer <= diff)
			   {
				   DoCast(me, SPELL_UNHOLY_ARMY, true);
				   uiArmyOfTheDeadTimer = 30000;
			   }
			   else
				   uiArmyOfTheDeadTimer -= diff;
			   DoMeleeAttackIfReady();
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
		   }

	      private:
			  Creature * guin;
			  Creature * twin;
			  SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_main_unholyAI(pCreature);
	   }
};

class npc_dm_unholy_twin : public CreatureScript
{
   public:
	   npc_dm_unholy_twin() : CreatureScript("npc_dm_unholy_twin") { }

	   struct npc_dm_unholy_twinAI : public ScriptedAI
	   {
		   npc_dm_unholy_twinAI(Creature * c) : ScriptedAI(c) { }

		   uint32 uiCinematic;
		   uint32 uiAoeTimer;
		   uint32 uiPlagueStrikeTimer;
		   uint32 uiStangulateTimer;
		   uint32 uiDeathStrikeTimer;
		   uint32 uiArmyOfTheDeadTimer;
		   int cinematicPassed;
		   bool boneArmor;

		   void Reset()
		   {
			   uiCinematic = 6000;
			   boneArmor = true;
			   cinematicPassed = 0;
			   me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
			   me->SetReactState(REACT_PASSIVE);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51393);
		   }

		   void OnCombatStart(Unit * /* who */)
		   {
			   me->AddAura(SPELL_UNHOLY_BONE_SHIELD, me);
			   uiAoeTimer = 25000;
			   uiPlagueStrikeTimer = urand(5000, 8000);
			   uiDeathStrikeTimer = urand(9000, 12000);
			   uiStangulateTimer = 15000;
			   uiArmyOfTheDeadTimer = 30000;
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(uiCinematic <= diff)
			   {
				   switch(cinematicPassed)
				   {
					   case 0:
						   me->MonsterSay("I believe it wants to fight us.", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 1;
						   uiCinematic = 7000;
						   break;

					   case 1:
						   me->MonsterSay("Yes. So it seems.", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 2;
						   uiCinematic = 6000;
						   break;

					   case 2:
						   me->MonsterSay("What? FIGHT?", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 3;
						   uiCinematic = 3000;
						   break;

					   case 3:
						   me->MonsterYell("GUIN! NO!", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 4;
						   break;
				   }
			   }
			   else
				   uiCinematic -= diff;

			   if(!UpdateVictim())
				   return;

			   if(HealthBelowPct(25) && boneArmor)
			   {
				   me->AddAura(SPELL_UNHOLY_BONE_SHIELD, me);
				   boneArmor = false;
			   }

			   if(uiAoeTimer <= diff)
			   {
				   me->CastSpell(me->getVictim()->GetPositionX(), me->getVictim()->GetPositionY(), me->getVictim()->GetPositionZ(), SPELL_UNHOLY_AOE, true);
				   uiAoeTimer = 25000;
			   }
			   else
				   uiAoeTimer -= diff;

			   if(uiPlagueStrikeTimer <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_UNHOLY_PLAGUE_STRIKE);
				   uiPlagueStrikeTimer = urand(5000, 8000);
			   }
			   else
				   uiPlagueStrikeTimer -= diff;

			   if(uiStangulateTimer <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_UNHOLY_STANGULATE, true);
				   uiStangulateTimer = 15000;
			   }
			   else
				   uiStangulateTimer -= diff;

			   if(uiDeathStrikeTimer <= diff)
			   {
				   DoCast(me->getVictim(), SPELL_UNHOLY_DEATH_STRIKE);
				   uiDeathStrikeTimer = urand(9000, 12000);
			   }
			   else
				   uiDeathStrikeTimer -= diff;

			   if(uiArmyOfTheDeadTimer <= diff)
			   {
				   DoCast(me, SPELL_UNHOLY_ARMY, true);
				   uiArmyOfTheDeadTimer = 30000;
			   }
			   else
				   uiArmyOfTheDeadTimer -= diff;
			   DoMeleeAttackIfReady();
		   }
		   
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_unholy_twinAI(pCreature);
	   }
};

class npc_dm_unholy_pet : public CreatureScript
{
   public:
	   npc_dm_unholy_pet() : CreatureScript("npc_dm_unholy_pet") { }

	   struct npc_dm_unholy_petAI : public ScriptedAI
	   {
		   npc_dm_unholy_petAI(Creature * c) : ScriptedAI(c) { }

		   uint32 uiCinematicTimer;
		   uint32 uiPhaseChangeTimer;
		   uint32 uiEnrageTimer;
		   int phase;
		   int cinematicPassed;

		   void Reset()
		   {
			   uiCinematicTimer = 16000;
			   uiPhaseChangeTimer = 1000;
			   uiEnrageTimer = 5000;
			   phase = 1;
			   cinematicPassed = 0;
			   me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
			   me->SetReactState(REACT_PASSIVE);
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(uiCinematicTimer <= diff)
			   {
				   switch(cinematicPassed)
				   {
					   case 0:
						   me->MonsterSay("Why can't we fight masters?", LANG_UNIVERSAL, me->GetGUID());
						   cinematicPassed = 1;
						   uiCinematicTimer = 5000;
						   break;

					   case 1:
						   me->MonsterYell("Well, I'm hungry!", LANG_UNIVERSAL, me->GetGUID());
						   me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
						   me->SetReactState(REACT_AGGRESSIVE);
						   if(Player * player = me->SelectNearestPlayer(500.0f))
							   if(player && player->GetGUID() == m_PlayerGUID)
							   {
								   me->Attack(player, true);
								   me->GetMotionMaster()->MoveChase(player);
							   }
						   cinematicPassed = 2;
						   break;
				   }
			   }
			   else
				   uiCinematicTimer -= diff;

			   if(!UpdateVictim())
				   return;

			   if(uiPhaseChangeTimer <= diff)
			   {
				   switch(phase)
				   {
					   case 1:
						   break;

					   case 2:
						   break;

					   case 3:
						   break;

					   case 4:
						   break;
				   }
				   if(HealthBelowPct(85) && phase == 1)
				   { 
					   DoIncreaseHealth(me, 2.0f, phase, 2);
				   }
				   else if(HealthBelowPct(65) && phase == 2)
				   {
					   DoIncreaseHealth(me, 2.5f, phase, 3);
				   }
				   else if(HealthBelowPct(35) && phase == 3)
				   {
					   DoIncreaseHealth(me, 3.0f, phase, 4);
				   }
				   else if(HealthBelowPct(15) && phase == 4)
				   {
					   me->MonsterYell("HUNGER!", LANG_UNIVERSAL, me->GetGUID());
					   DoIncreaseHealth(me, 3.5f, phase, 5);
				   }
			   }
			   else
				   uiPhaseChangeTimer -= diff;

			   if(uiEnrageTimer <= diff)
			   {
				   DoCast(SPELL_ENRAGE);
				   uiEnrageTimer = 5000;
			   }
			   else
				   uiEnrageTimer -= diff;
			   DoMeleeAttackIfReady();
		   }
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_unholy_petAI(pCreature);
	   }
};

class npc_army_ghoul : public CreatureScript
{
   public:
	   npc_army_ghoul() : CreatureScript("npc_army_ghoul") { }

	   struct npc_army_ghoulAI : public ScriptedAI
	   {
		   npc_army_ghoulAI(Creature * c) : ScriptedAI(c) { }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }
	   };
	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_army_ghoulAI(pCreature);
	   }
};

class npc_dm_rider_guardian : public CreatureScript
{
   public:
	   npc_dm_rider_guardian() : CreatureScript("npc_dm_rider_guardian") { }

	   struct npc_dm_rider_guardianAI : public ScriptedAI
	   {
		   npc_dm_rider_guardianAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 uiShieldTimer;
		   uint32 uiHealingBoltTimer;
		   uint32 uiRenewTimer;
		   uint32 uiGreaterHealTimer;
		   uint32 uiHealingBoltWaitTimer;
		   bool checkBrutes;
		   bool giveUp;
		   bool InHealingBolt;

		   void Reset()
		   {
			   uiShieldTimer = 25000;
			   uiHealingBoltTimer = urand(10000, 14000);
			   uiRenewTimer = 5000;
			   uiGreaterHealTimer = 8000;
			   me->SetReactState(REACT_PASSIVE);
			   me->CastSpell(me, SPELL_RIDERS_SHIELD);
			   me->CastSpell(me, SPELL_RIDERS_STAM_BUFF);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51453);
			   checkBrutes = false;
			   giveUp = false;
			   InHealingBolt = false;
			   summons.DespawnAll();
			   brute = me->SummonCreature(waveList[17], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY+3, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, TEMPSUMMON_MANUAL_DESPAWN, 0);
			   brute2 = me->SummonCreature(waveList[18], m_WaveSpawns[0].m_positionX, m_WaveSpawns[0].m_positionY-3, m_WaveSpawns[0].m_positionZ, m_WaveSpawns[0].m_orientation, TEMPSUMMON_MANUAL_DESPAWN, 0);
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me, summons);
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!isBattleActive)
			   {
				   summons.DespawnAll();
				   brute = NULL;
				   brute2 = NULL;
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(HealthBelowPct(25) && !giveUp)
			   {
				   me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
				   me->MonsterYell("I.. I GIVE UP!", LANG_UNIVERSAL, me->GetGUID());
				   me->SetHealth(me->GetMaxHealth());
				   checkBrutes = true;
				   giveUp = true;
			   }

			   if(checkBrutes && giveUp)
			   {
				   if(brute && brute->isDead() && brute2 && brute2->isDead())
				   {
					   if(Player * player = me->SelectNearestPlayer(200.0f))
						   if(player && player->GetGUID() == m_PlayerGUID)
							   me->PlayDirectSound(SOUND_WAVE_COMPLETE, player);
					   summons.DespawnAll();
					   me->DespawnOrUnsummon(1);
					   isWaveBossDead = 6;
				   }
				   return;
			   }

			   if(uiShieldTimer <= diff && !InHealingBolt)
			   {
				   int target = urand(0, 2);
				   switch(target)
				   {
				      case 0:
						  if(brute)
						      DoCast(brute, SPELL_RIDERS_SHIELD);
						  break;

					  case 1:
						  if(brute2)
							  DoCast(brute2, SPELL_RIDERS_SHIELD);
						  break;

					  case 2:
						  DoCast(me, SPELL_RIDERS_SHIELD);
						  break;
				   }
				   uiShieldTimer = 16000;
			   }
			   else
				   uiShieldTimer -= diff;

			   if(uiHealingBoltTimer <= diff)
			   {
				   int target = urand(0, 1);
				   switch(target)
				   {
				      case 0:
						  if(brute && brute->GetHealthPct() <= 85)
						      me->CastSpell(brute, SPELL_RIDERS_HEALING_BOLT, true);
						  break;

					  case 1:
						  if(brute2 && brute2->GetHealthPct() <= 65)
							  me->CastSpell(brute2, SPELL_RIDERS_HEALING_BOLT, true);
						  break;
				   }
				   InHealingBolt = true;
				   uiHealingBoltWaitTimer = 3000;
				   uiHealingBoltTimer = urand(10000, 14000);
			   }
			   else
				   uiHealingBoltTimer -= diff;

			   if(InHealingBolt)
			   {
				   if(uiHealingBoltWaitTimer <= diff)
				   {
					   InHealingBolt = false;
				   }
				   else
					   uiHealingBoltWaitTimer -= diff;
			   }

			   if(uiRenewTimer <= diff && !InHealingBolt)
			   {
				   int target = urand(0, 2);
				   switch(target)
				   {
				      case 0:
						  if(brute)
						      DoCast(brute, SPELL_RIDERS_RENEW);
						  break;

					  case 1:
						  if(brute2)
							  DoCast(brute2, SPELL_RIDERS_RENEW);
						  break;

					  case 2:
						  if(HealthBelowPct(80))
							  DoCast(me, SPELL_RIDERS_RENEW);
						  break;
				   }
				   uiRenewTimer = 5000;
			   }
			   else
				   uiRenewTimer -= diff;

			   if(uiGreaterHealTimer <= diff && !InHealingBolt)
			   {
				   int target = urand(0, 2);
				   switch(target)
				   {
				      case 0:
						  if(brute && brute->GetHealthPct() <= 30)
						      me->CastSpell(brute, SPELL_RIDERS_GREATER_HEAL, true);
						  break;

					  case 1:
						  if(brute2 && brute2->GetHealthPct() <= 20)
							  me->CastSpell(brute2, SPELL_RIDERS_GREATER_HEAL, true);
						  break;

					  case 2:
						  if(HealthBelowPct(40))
							  me->CastSpell(me, SPELL_RIDERS_GREATER_HEAL, true);
						  break;
				   }
				   uiGreaterHealTimer = 6000;
			   }
			   else
				   uiGreaterHealTimer -= diff;
		   }
	      private:
			  Creature * brute;
			  Creature * brute2;
			  SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_rider_guardianAI(pCreature);
	   }
};

class npc_dm_rider_brute : public CreatureScript
{
   public:
	   npc_dm_rider_brute() : CreatureScript("npc_dm_rider_brute") { }

	   struct npc_dm_rider_bruteAI : public ScriptedAI
	   {
		   npc_dm_rider_bruteAI(Creature * c) : ScriptedAI(c) { }

		   uint32 uiLightningTimer;
		   uint32 uiChainLightningTimer;
		   uint32 uiMoonfireTimer;
		   uint32 uiLightningStormTimer;
		   uint32 uiLightningWaitTimer;
		   bool InLightningChannel;

		   void Reset()
		   {
			   uiLightningTimer = 13000;
			   uiChainLightningTimer = urand(6000, 9000);
			   uiMoonfireTimer = 5000;
			   uiLightningStormTimer = urand(20000, 26000);
			   InLightningChannel = false;
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+0, 51517);
			   me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+1, 51447);
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!UpdateVictim())
				   return;

			   if(!isBattleActive)
			   {
				   me->DespawnOrUnsummon(1);
				   return;
			   }

			   if(uiLightningTimer <= diff)
			   {
				   if(!InLightningChannel)
					   DoCast(me->getVictim(), SPELL_RIDERS_LIGHTNING);
				   uiLightningTimer = 13000;
			   }
			   else
				   uiLightningTimer -= diff;

			   if(uiChainLightningTimer <= diff)
			   {
				   if(!InLightningChannel)
					   DoCast(me->getVictim(), SPELL_RIDERS_CHAIN_LIGHTNING, true);
				   uiChainLightningTimer = urand(6000, 9000);
			   }
			   else
				   uiChainLightningTimer -= diff;

			   if(uiMoonfireTimer <= diff)
			   {
				   if(!InLightningChannel)
					   DoCast(me->getVictim(), SPELL_RIDERS_MOONFIRE);
				   uiMoonfireTimer = 5000;
			   }
			   else
				   uiMoonfireTimer -= diff;

			   if(uiLightningStormTimer <= diff)
			   {
				   if(!InLightningChannel)
				   {
					   me->CastSpell(me->getVictim(), SPELL_RIDERS_STORM, true);
					   InLightningChannel = true;
					   uiLightningWaitTimer = 10000;
				   }
				   uiLightningStormTimer = urand(20000, 26000);
			   }
			   else
				   uiLightningStormTimer -= diff;

			   if(InLightningChannel)
			   {
				   if(uiLightningWaitTimer <= diff)
				   {
					   InLightningChannel = false;
				   }
				   else
					   uiLightningWaitTimer -= diff;
			   }

			   if(!InLightningChannel)
				   DoMeleeAttackIfReady();
		   }
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_rider_bruteAI(pCreature);
	   }
};

class npc_dm_dragon_final : public CreatureScript
{
   public:
	   npc_dm_dragon_final() : CreatureScript("npc_dm_dragon_final") { }

	   struct npc_dm_dragon_finalAI : public ScriptedAI
	   {
		   npc_dm_dragon_finalAI(Creature * c) : ScriptedAI(c), summons(me) { }

		   uint32 uiBerserkTimer;
		   uint32 uiBreathTimer;
		   uint32 uiTailWhipTimer;
		   uint32 uiClawTimer;
		   uint32 uiFlameStrikeTimer;
		   uint32 uiFlightTimer;
		   uint32 uiFlightWaitTimer;
		   uint32 uiLandTimer;

		   uint32 m_Phase;
		   int  FlameStrikeData;
		   bool IsInFlight;
		   bool FireShield;
		   bool canLand;

		   void Reset()
		   {
			   if(!IsCombatMovementAllowed())
				   SetCombatMovement(true);

			   uiFlightTimer = 10000; // 10s
			   uiClawTimer = urand(3000, 5000);
			   uiTailWhipTimer = urand(12000, 16000);
			   uiBreathTimer = urand(18000, 22000);

			   FlameStrikeData = 0;

			   summons.DespawnAll();
			   IsInFlight = false;
			   FireShield = true;
			   canLand = false;
		   }

		   void EnterCombat(Unit * /* who */)
		   {
			   m_Phase = PHASE_START_COMBAT;
			   uiBerserkTimer = 420000; // 7 Mins
		   }

		   void KilledUnit(Unit * who)
		   {
			   if(who && who->GetTypeId() != TYPEID_PLAYER)
				   return;
			   DoEndBattle(me, summons);
		   }

		   void JustDied(Unit * killer)
		   {
			   if(killer && killer->GetTypeId() != TYPEID_PLAYER && 
				   killer->GetGUID() != m_PlayerGUID)
				   return;
			   me->PlayDirectSound(SOUND_WAVE_COMPLETE, killer->ToPlayer());
			   m_Phase = PHASE_END;
			   isWaveBossDead = 7;
		   }

		   void MovementInform(uint32 type, uint32 id)
		   {
			   if(type == POINT_MOTION_TYPE)
			   {
				   switch(id)
				   {
				       case 1:
						   me->SetFacingTo(sMoveData[0].o);
						   me->SetDisableGravity(true);
						   break;
				   }
			   }
		   }

		   void JustSummoned(Creature * summoned)
		   {
			   summons.Summon(summoned);
		   }

		   void UpdateAI(const uint32 diff)
		   {
			   if(!UpdateVictim() || m_Phase == PHASE_END)
				   return;

			   if(!isBattleActive)
			   {
				   summons.DespawnAll();
				   m_Phase = PHASE_END;
				   me->DespawnOrUnsummon(1);	   
				   return;
			   }

			   if(m_Phase == PHASE_START_COMBAT)
			   {
				   if(HealthBelowPct(15) && FireShield) // Doesn't matter if you're flying
				   {
					   DoCast(me, SPELL_DRAGON_FIRE_SHIELD, true);
					   FireShield = false;
				   }

				   if(uiClawTimer <= diff)
				   {
					   if(!IsInFlight)
						   DoCast(me->getVictim(), SPELL_DRAGON_CLAW);
					   uiClawTimer = urand(3000, 5000);
				   }
				   else
					   uiClawTimer -= diff;

				   if(uiBreathTimer <= diff)
				   {
					   if(!IsInFlight)
						   me->CastSpell(me->getVictim(), SPELL_DRAGON_BREATH, true);
					   uiBreathTimer = urand(18000, 24000);
				   }
				   else
					   uiBreathTimer -= diff;

				   if(uiTailWhipTimer <= diff)
				   {
					   if(!IsInFlight)
						   DoCastAOE(SPELL_DRAGON_TAIL_WHIP, false);
					   uiTailWhipTimer = urand(12000, 16000);
				   }
				   else
					   uiTailWhipTimer -= diff;

				   if(uiBerserkTimer <= diff)
				   {
					   DoCast(me, SPELL_DRAGON_BERSERK);
					   uiBerserkTimer = 420000;
				   }
				   else
					   uiBerserkTimer -= diff;

				   if(uiFlightTimer <= diff && !IsInFlight)
				   {
					   me->SetCanFly(true);
					   me->SetSpeed(MOVE_FLIGHT, 1.3f);					   
					   me->GetMotionMaster()->MovePoint(1, -3786.241943f, 1096.538452f, 153.903366f);					   
					   FlameStrikeData = 0;
					   uiFlameStrikeTimer = 6000;
					   uiFlightWaitTimer = 30000;
					   IsInFlight = true;
					   uiFlightTimer = 50000;
				   }
				   else
					   uiFlightTimer -= diff;

				   if(IsInFlight)
				   {
					   if(uiFlameStrikeTimer <= diff)
					   {
						   switch(FlameStrikeData)
						   {
						      case 0:
								  me->MonsterTextEmote("The Arena Dragon has a lot of fire inside!", 0, true);
								  groundTarget = me->SummonGameObject(sMoveData[0].gobject, me->getVictim()->GetPositionX()-3, me->getVictim()->GetPositionY()+6, me->getVictim()->GetPositionZ(),
									  me->GetOrientation(), 0, 0, 0, 0, 0);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 1;
								  break;

							  case 1:
								  trigger = me->SummonCreature(NPC_DRAGON_BOSS_TRIGGER, groundTarget->GetPositionX(), groundTarget->GetPositionY(), groundTarget->GetPositionZ(), 0.0f,
									  TEMPSUMMON_TIMED_DESPAWN, 3000);
								  me->CastSpell(trigger->GetPositionX(), trigger->GetPositionY(), trigger->GetPositionZ(), sMoveData[0].spellId, true);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 2;
								  break;

							  case 2:
								  if(groundTarget)
									  groundTarget->Delete();
								  me->MonsterTextEmote("The Arena Dragon has a lot of fire inside!", 0, true);
								  groundTarget = me->SummonGameObject(sMoveData[0].gobject, me->getVictim()->GetPositionX()-3, me->getVictim()->GetPositionY()-6, me->getVictim()->GetPositionZ(),
									  me->GetOrientation(), 0, 0, 0, 0, 0);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 3;
								  break;

							  case 3:
								  trigger = me->SummonCreature(NPC_DRAGON_BOSS_TRIGGER, groundTarget->GetPositionX(), groundTarget->GetPositionY(), groundTarget->GetPositionZ(), 0.0f,
									  TEMPSUMMON_TIMED_DESPAWN, 3000);
								  me->CastSpell(trigger->GetPositionX(), trigger->GetPositionY(), trigger->GetPositionZ(), sMoveData[0].spellId, true);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 4;
								  break;

							  case 4:
								  if(groundTarget)
									  groundTarget->Delete();
								  me->MonsterTextEmote("The Arena Dragon has a lot of fire inside!", 0, true);
								  groundTarget = me->SummonGameObject(sMoveData[0].gobject, me->getVictim()->GetPositionX()-3, me->getVictim()->GetPositionY()-6, me->getVictim()->GetPositionZ(),
									  me->GetOrientation(), 0, 0, 0, 0, 0);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 5;
								  break;

							  case 5:
								  trigger = me->SummonCreature(NPC_DRAGON_BOSS_TRIGGER, groundTarget->GetPositionX(), groundTarget->GetPositionY(), groundTarget->GetPositionZ(), 0.0f,
									  TEMPSUMMON_TIMED_DESPAWN, 3000);
								  me->CastSpell(trigger->GetPositionX(), trigger->GetPositionY(), trigger->GetPositionZ(), sMoveData[0].spellId, true);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 6;
								  break;

							  case 6:
								  if(groundTarget)
									  groundTarget->Delete();
								  me->MonsterTextEmote("The Arena Dragon has a lot of fire inside!", 0, true);
								  groundTarget = me->SummonGameObject(sMoveData[0].gobject, me->getVictim()->GetPositionX()-3, me->getVictim()->GetPositionY()+6, me->getVictim()->GetPositionZ(),
									  me->GetOrientation(), 0, 0, 0, 0, 0);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 7;
								  break;

							  case 7:
								  trigger = me->SummonCreature(NPC_DRAGON_BOSS_TRIGGER, groundTarget->GetPositionX(), groundTarget->GetPositionY(), groundTarget->GetPositionZ(), 0.0f,
									  TEMPSUMMON_TIMED_DESPAWN, 3000);
								  me->CastSpell(trigger->GetPositionX(), trigger->GetPositionY(), trigger->GetPositionZ(), sMoveData[0].spellId, true);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 8;
								  break;

							  case 8:
								  if(groundTarget)
									  groundTarget->Delete();
								  me->MonsterTextEmote("The Arena Dragon has a lot of fire inside!", 0, true);
								  groundTarget = me->SummonGameObject(sMoveData[0].gobject, me->getVictim()->GetPositionX()-3, me->getVictim()->GetPositionY()+6, me->getVictim()->GetPositionZ(),
									  me->GetOrientation(), 0, 0, 0, 0, 0);
								  uiFlameStrikeTimer = 2000;
								  FlameStrikeData = 9;
								  break;

							  case 9:
								  trigger = me->SummonCreature(NPC_DRAGON_BOSS_TRIGGER, groundTarget->GetPositionX(), groundTarget->GetPositionY(), groundTarget->GetPositionZ(), 0.0f,
									  TEMPSUMMON_TIMED_DESPAWN, 3000);
								  me->CastSpell(trigger->GetPositionX(), trigger->GetPositionY(), trigger->GetPositionZ(), sMoveData[0].spellId, true);
								  uiFlameStrikeTimer = 1000;
								  FlameStrikeData = 10;
								  break;

							  case 10:
								  if(groundTarget)
									  groundTarget->Delete();
								  FlameStrikeData = 11;
								  break;
						   }
					   }
					   else
						   uiFlameStrikeTimer -= diff;

					   if(uiFlightWaitTimer <= diff && !canLand)
					   {
						   me->GetMotionMaster()->MovePoint(2, me->GetHomePosition()); // Back Home
						   canLand = true;
						   uiLandTimer = 5000;
					   }
					   else
						   uiFlightWaitTimer -= diff;

					   if(uiLandTimer <= diff && canLand)
					   {
						   me->SetCanFly(false);
						   me->SetDisableGravity(false);
						   SetCombatMovement(true);
						   me->GetMotionMaster()->Clear(false);
						   me->GetMotionMaster()->MoveChase(me->getVictim());
						   IsInFlight = false;
						   canLand = false;
					   }
					   else
						   uiLandTimer -= diff;
				   }
			   }
			  if(!IsInFlight)
				  DoMeleeAttackIfReady();
		   }
		   private:
			   GameObject * groundTarget;
			   Creature * trigger;
			   SummonList summons;
	   };

	   CreatureAI * GetAI(Creature * pCreature) const
	   {
		   return new npc_dm_dragon_finalAI(pCreature);
	   }
};

class remove_non_battle_player : public PlayerScript
{
   public:
	   remove_non_battle_player() : PlayerScript("remove_non_battle_player") { }

	   void OnUpdateZone(Player * player, uint32 zone, uint32 area)
	   {
		   if(m_PlayerGUID == 0)
			   return;

		   if(player->GetZoneId() != DIRE_MAUL_ZONE && player->GetAreaId() != DIRE_MAUL_AREA && player->GetGUID() == m_PlayerGUID)
		   {
			   inZone = false;
			   return;
		   }

		   if(player->GetAreaId() != DIRE_MAUL_AREA || player->GetSession()->GetSecurity() > 1)
			   return;

		   if(isBattleActive && player->GetGUID() != m_PlayerGUID)
		   {
			   player->TeleportTo(player->GetStartPosition().GetMapId(), player->GetStartPosition().GetPositionX(), player->GetStartPosition().GetPositionY(), 
			      player->GetStartPosition().GetPositionZ(), player->GetStartPosition().GetOrientation());
			   ChatHandler(player).SendSysMessage("You cannot be in the Dire Maul Arena while the event is going on!");
		   }
	   }

	   void OnLogout(Player * player)
	   {
		   if(m_PlayerGUID == 0)
			   return;

		   if(player->GetGUID() == m_PlayerGUID)
			   hasLogged = true;
	   }
};

void AddSC_arena_link_battle()
{
	/* Npc Classes */
	new npc_dire_arena_commander;
	new npc_dire_maul_rb_guard;
	new npc_red_blood_mini;
	new npc_dm_wave_trigger;
	new npc_dm_wave_spawns;
	new npc_dm_hank_the_tank;
	new npc_dm_field_medic;
	new npc_dm_main_rogue;
	new npc_dm_rogue_initiate;
	new npc_dm_main_unholy;
	new npc_dm_unholy_twin;
	new npc_dm_unholy_pet;
	new npc_army_ghoul;
	new npc_dm_rider_guardian;
	new npc_dm_rider_brute;
	new npc_dm_dragon_final;
	new npc_dm_wave_portals;
	/* Player Classes */
	new remove_non_battle_player;
}