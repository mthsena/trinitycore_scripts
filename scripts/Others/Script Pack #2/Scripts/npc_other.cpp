#include "ScriptPCH.h"

#include "ScriptMgr.h"

 

#define MSG_GOSSIP_TEXT_GETTING_STARTED "Welcome to the Revival DM server!"


#define MSG_ERR_INCOMBAT "Please out of combat!"

#define MSG_ERR_ARENA_POINT "Need more Arena Points!"


#define MSG_CHANGE_FACTION_COMPLETE "Please logout and change faction. Do not forget to leave the game and DELETE folder Cache!"


#define MSG_GOSSIP_TEXT_MAX_SKILL "Все уимения на максимум"
#define MSG_GOSSIP_TEXT_RIDING "Изучить езду"


#define MSG_GOSSIP_TEXT_CHANGE_FACTION "Change Faction - 30.000 Arena Points."

#define MSG_GOSSIP_TEXT_A7_PRIEST_HEAL "A8 set for Discipline Priest."

#define MSG_GOSSIP_TEXT_A7_PRIEST_DD "A8 set for Shadow Priest."

#define MSG_GOSSIP_TEXT_A7_DRUID_FERAL "A8 set for Feral Combat Druid."

#define MSG_GOSSIP_TEXT_A7_DRUID_RESTOR "A8 set for Restoration Druid."

#define MSG_GOSSIP_TEXT_A7_DRUID_BALANSE "A8 set for Balance Druid."

#define MSG_GOSSIP_TEXT_A7_WARRIOR "A8 set for Warrior."

#define MSG_GOSSIP_TEXT_A7_MAGE "A8 set for Mage."

#define MSG_GOSSIP_TEXT_A7_HUNTER "A8 set for Hunter."

#define MSG_GOSSIP_TEXT_A7_PALLADIN_HOLI "A8 set for Holy Paladin."

#define MSG_GOSSIP_TEXT_A7_PALLADIN_DD "A8 set for Retribution Paladin."

#define MSG_GOSSIP_TEXT_A7_ROGUE "A8 set for Rogue."

#define MSG_GOSSIP_TEXT_A7_DK "A8 set for Death Knight."

#define MSG_GOSSIP_TEXT_A7_LOOK "A8 set for Warlock."

#define MSG_GOSSIP_TEXT_A7_SHAMAN_HOLI "A8 set for Restoration Shaman." 

#define MSG_GOSSIP_TEXT_A7_SHAMAN_RDD "A8 set for Elemental Shaman." 

#define MSG_GOSSIP_TEXT_A7_SHAMAN_DD "A8 set for Enhancement Shaman."

 
#define CONST_ARENA_POINT_1 15000

#define CONST_ARENA_POINT_2 30000



       		int warlockItem[5] = {51536,51537,51538,51539,51540};

                int warriorItem[5] = {51541,51542,51543,51544,51545};

                int druidRestorItem[5] = {51419,51420,51421,51422,51424};

                int druidBalanceItem[5] =  {51433,51434,51435,51436,51438};

                int druidFeralItem[5] = {51425,51426,51427,51428,51430};

                int priestDiscItem[5] = {51482,51483,51484,51485,51486};

                int priestShadowItem[5] = {51487,51488,51489,51490,51491};

                int mageItem[5] = {51463,51464,51465,51466,51467};

                int hunterItem[5] = {51458,51459,51460,51461,51462};

                int paladinHolyItem[5] = {51468,51469,51470,51471,51473};

                int paladinMeleeItem[5] = {51474,51475,51476,51477,51479};

                int rogueItem[5] = {51492,51493,51494,51495,51496};

                int deathknightItem[5] = {51413,51414,51415,51416,51418};

                int shamanMeleeItem[5] = {51503,51504,51505,51506,51508};

                int shamanElementalItem[5] = {51509,51510,51511,51512,51514};

                int shamanRestorItem[5] = {51497,51498,51499,51500,51502};

 

class npc_other : public CreatureScript

{

    public: 

    npc_other() : CreatureScript("npc_other") { }

 

        void AddSet(Player* player, int massive[5])

        {

                for (int i = 0; i < 5; ++i)

                        {

                                player->AddItem(massive[i], 1);

                        }

                player->CLOSE_GOSSIP_MENU();

        }

 

        bool OnGossipHello(Player *player, Creature *creature)

                { 

        creature->MonsterWhisper(MSG_GOSSIP_TEXT_GETTING_STARTED, player->GetGUID());


                int playerClass = player->getClass();

                switch (playerClass)

                {

                case CLASS_WARLOCK:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_LOOK, GOSSIP_SENDER_MAIN, 7);

                break;

                case CLASS_WARRIOR:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_WARRIOR, GOSSIP_SENDER_MAIN, 8);

                break;

                case CLASS_DRUID:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_DRUID_RESTOR, GOSSIP_SENDER_MAIN, 9);

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_DRUID_BALANSE, GOSSIP_SENDER_MAIN, 10);

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_DRUID_FERAL, GOSSIP_SENDER_MAIN, 11);

                break;

                case CLASS_PRIEST:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_PRIEST_HEAL, GOSSIP_SENDER_MAIN, 12);

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_PRIEST_DD, GOSSIP_SENDER_MAIN, 13);

                break;

                case CLASS_MAGE:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_MAGE, GOSSIP_SENDER_MAIN, 14);

                break;

                case CLASS_PALADIN:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_PALLADIN_HOLI, GOSSIP_SENDER_MAIN, 15);

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_PALLADIN_DD, GOSSIP_SENDER_MAIN, 16);

                break;

                case CLASS_ROGUE:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_ROGUE, GOSSIP_SENDER_MAIN, 17);

                break;

                case CLASS_DEATH_KNIGHT:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_DK, GOSSIP_SENDER_MAIN, 18);

                break;

                case CLASS_SHAMAN:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_SHAMAN_DD, GOSSIP_SENDER_MAIN, 19);

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_SHAMAN_RDD, GOSSIP_SENDER_MAIN, 20);

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_SHAMAN_HOLI, GOSSIP_SENDER_MAIN, 21);

                break;

                case CLASS_HUNTER:

                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, MSG_GOSSIP_TEXT_A7_HUNTER, GOSSIP_SENDER_MAIN, 22);

                break;

                }

                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MAX_SKILL, GOSSIP_SENDER_MAIN, 4); 

 		    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_RIDING, GOSSIP_SENDER_MAIN, 6);

                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_CHANGE_FACTION, GOSSIP_SENDER_MAIN, 25);

            player->SEND_GOSSIP_MENU (DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); 

        return true;

        }

 

 

      bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action )

                {

                  if (!player->getAttackers().empty())

        {

                creature->MonsterWhisper(MSG_ERR_INCOMBAT, player->GetGUID());

                player->CLOSE_GOSSIP_MENU();

        return false;

                  }

                  switch (action)

        {


                  case 4:

                          player->UpdateSkillsToMaxSkillsForLevel();

                      player->CLOSE_GOSSIP_MENU();

                          break;

		  case 6:
	
                      player->SetSkill(762, 6, 450, 450);

                      player->learnSpell(54197, true);

                      player->CLOSE_GOSSIP_MENU();

                          break;

                  case 7:

                          AddSet(player, warlockItem);

                          player->CLOSE_GOSSIP_MENU();

                          break;

                  case 8:

                          AddSet(player, warriorItem);

                          break;

                  case 9:

              AddSet(player, druidRestorItem);

                          break;

                  case 10:

                          AddSet(player, druidBalanceItem);

                          break;

                  case 11:

                          AddSet(player, druidFeralItem);

                          break;

                  case 12:

                          AddSet(player, priestDiscItem);

                          break;

                  case 13:

                          AddSet(player,  priestShadowItem);

                          break;

                  case 14:

                          AddSet(player,  mageItem);

                          break;

                  case 15:

                          AddSet(player,  paladinHolyItem);

                          break;

                  case 16:

                          AddSet(player,  paladinMeleeItem);

                          break;

                  case 17:

                          AddSet(player, rogueItem);

                          break;

                  case 18:

                          AddSet(player, deathknightItem);

                          break;

                  case 19:

                          AddSet(player, shamanMeleeItem);

                          break;

                  case 20:

                          AddSet(player, shamanRestorItem);

                          break;

                  case 21:

                          AddSet(player, shamanElementalItem);

                          break;

                  case 22:

                          AddSet(player, hunterItem);


                  case 25:

                          if (player->GetArenaPoints() < CONST_ARENA_POINT_2)

                          {

                       creature->MonsterWhisper(MSG_ERR_ARENA_POINT, player->GetGUID());

                       player->CLOSE_GOSSIP_MENU();

             }else{

                       // ?????? ????? ???????

                       player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);

                       player->ModifyArenaPoints(-CONST_ARENA_POINT_2);

               creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());

               player->CLOSE_GOSSIP_MENU();

                          }

                          break; 

}

      return true;

}

          };

 

          void AddSC_npc_other()

{

        new npc_other;

}