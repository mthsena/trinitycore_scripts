/*
 
- Original code by ??? -
- Improved a lot by Karhma -
- Fixed Error by SymbolixDEV
 
*/
#include "ScriptPCH.h"
#include "Pet.h"
 
class Npc_Beastmaster : public CreatureScript
{
public:
        Npc_Beastmaster() : CreatureScript("Npc_Beastmaster") { }
 
        void CreatePet(Player *player, Creature * m_creature, uint32 entry) {
 
                if(player->getClass() != CLASS_HUNTER) {
                        m_creature->MonsterWhisper("You are not a Hunter!", player->GetGUID());
                        player->PlayerTalkClass->SendCloseGossip();
                        return;
                }
 
                if(player->GetPet()) {
                        m_creature->MonsterWhisper("First drop your current Pet!", player->GetGUID());
                        player->PlayerTalkClass->SendCloseGossip();
                        return;
                }
 
                Creature *creatureTarget = m_creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY()+2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
                if(!creatureTarget) return;
 
                Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
                if(!pet) return;
 
                creatureTarget->setDeathState(JUST_DIED);
                creatureTarget->RemoveCorpse();
                creatureTarget->SetHealth(0);                       // just for nice GM-mode view
 
                pet->SetPower(POWER_HAPPINESS, 1048000);
 
                pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
                pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
 
                pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
                pet->GetMap()->AddToMap(pet->ToCreature());
 
                pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
 
                pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
                if(!pet->InitStatsForLevel(player->getLevel()))
                        sLog->outError(LOG_FILTER_PETS, "Fail: no init stats for entry %u", entry);
 
                pet->UpdateAllStats();
 
                player->SetMinion(pet, true);
 
                pet->SavePetToDB(PET_SAVE_AS_CURRENT);
                pet->InitTalentForLevel();
                player->PetSpellInitialize();
 
                player->PlayerTalkClass->SendCloseGossip();
                m_creature->MonsterWhisper("Pet successfully added!", player->GetGUID());
        }
 
 
        bool OnGossipHello(Player *player, Creature * m_creature)
        {
 
                if(player->getClass() != CLASS_HUNTER)
                {
                        m_creature->MonsterWhisper("You are not a Hunter!", player->GetGUID());
                        return true;
                }
                player->ADD_GOSSIP_ITEM(7, "Get a New Pet.", GOSSIP_SENDER_MAIN, 1000);
                if (player->CanTameExoticPets())
                {
                        player->ADD_GOSSIP_ITEM(7, "Get a New Exotic Pet.", GOSSIP_SENDER_MAIN, 50);
                }
                player->ADD_GOSSIP_ITEM(2, "Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
                player->ADD_GOSSIP_ITEM(1, "Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
                player->ADD_GOSSIP_ITEM(4, "Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
                player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                return true;
        }
 
        bool OnGossipSelect(Player *player, Creature * m_creature, uint32 sender, uint32 action)
        {
                player->PlayerTalkClass->ClearMenus();
                switch (action)
                {
 
                case 100:
                        player->ADD_GOSSIP_ITEM(7, "Get a New Pet.", GOSSIP_SENDER_MAIN, 1000);
                        if (player->CanTameExoticPets())
                        {
                                player->ADD_GOSSIP_ITEM(7, "Get a New Exotic Pet.", GOSSIP_SENDER_MAIN, 50);
                        }
                        player->ADD_GOSSIP_ITEM(2, "Take me to the Stable.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
                        player->ADD_GOSSIP_ITEM(1, "Sell me some Food for my Pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
                        player->ADD_GOSSIP_ITEM(4, "Close Beastmaster Window.", GOSSIP_SENDER_MAIN, 150);
                        player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                        break;
 
                case 150:
                        player->CLOSE_GOSSIP_MENU();
                        break;

    				case 1000: // Submenu
										player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
										player->ADD_GOSSIP_ITEM(5, "[Next Page] ->", GOSSIP_SENDER_MAIN, 10000);
                                        player->ADD_GOSSIP_ITEM(4, "Tame a Bat!", GOSSIP_SENDER_MAIN, 1001);
                                        player->ADD_GOSSIP_ITEM(4, "Tame a Bear!", GOSSIP_SENDER_MAIN, 1002);
                                        player->ADD_GOSSIP_ITEM(4, "Tame a Bird of Prey!", GOSSIP_SENDER_MAIN, 1003);
                                        player->ADD_GOSSIP_ITEM(4, "Tame a Boar!", GOSSIP_SENDER_MAIN, 1004);
										player->ADD_GOSSIP_ITEM(4, "Tame a Carrion Bird!", GOSSIP_SENDER_MAIN, 1005);
										player->ADD_GOSSIP_ITEM(4, "Tame a Cat!", GOSSIP_SENDER_MAIN, 1006);
										player->ADD_GOSSIP_ITEM(4, "Tame a Crab!", GOSSIP_SENDER_MAIN, 1007);
										player->ADD_GOSSIP_ITEM(4, "Tame a Crocolisk!", GOSSIP_SENDER_MAIN, 1008);
										player->ADD_GOSSIP_ITEM(4, "Tame a Dragonhawk!", GOSSIP_SENDER_MAIN, 1009);
										player->ADD_GOSSIP_ITEM(4, "Tame a Gorilla!", GOSSIP_SENDER_MAIN, 1010);
										player->ADD_GOSSIP_ITEM(4, "Tame a Hyena!", GOSSIP_SENDER_MAIN, 1011);
										player->ADD_GOSSIP_ITEM(4, "Tame a Moth!", GOSSIP_SENDER_MAIN, 1012);
										player->ADD_GOSSIP_ITEM(4, "Tame a Nether Ray!", GOSSIP_SENDER_MAIN, 1013);
										player->ADD_GOSSIP_ITEM(4, "Tame a Raptor!", GOSSIP_SENDER_MAIN, 1014);
                                        player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                                        break;

						case 10000: // Submenu
										player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
										player->ADD_GOSSIP_ITEM(5, "<- [Previous Menu]", GOSSIP_SENDER_MAIN, 1000);										
										player->ADD_GOSSIP_ITEM(4, "Tame a Ravager!", GOSSIP_SENDER_MAIN, 1015);
										player->ADD_GOSSIP_ITEM(4, "Tame a Scorpid!", GOSSIP_SENDER_MAIN, 1016);
										player->ADD_GOSSIP_ITEM(4, "Tame a Serpent!", GOSSIP_SENDER_MAIN, 1017);
										player->ADD_GOSSIP_ITEM(4, "Tame a Spider!", GOSSIP_SENDER_MAIN, 1018);
										player->ADD_GOSSIP_ITEM(4, "Tame a Sporebat!", GOSSIP_SENDER_MAIN, 1019);
										player->ADD_GOSSIP_ITEM(4, "Tame a Tallstrider!", GOSSIP_SENDER_MAIN, 1020);
										player->ADD_GOSSIP_ITEM(4, "Tame a Turtle!", GOSSIP_SENDER_MAIN, 1021);
										player->ADD_GOSSIP_ITEM(4, "Tame a Warpstalker!", GOSSIP_SENDER_MAIN, 1022);
										player->ADD_GOSSIP_ITEM(4, "Tame a Windserpent!", GOSSIP_SENDER_MAIN, 1023);
										player->ADD_GOSSIP_ITEM(4, "Tame a Wolf!", GOSSIP_SENDER_MAIN, 1024);
										player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                                        break;
 
                case 1001:
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
                        player->ADD_GOSSIP_ITEM(6, "Brown Bat", GOSSIP_SENDER_MAIN, 1);
						player->ADD_GOSSIP_ITEM(6, "Red Bat", GOSSIP_SENDER_MAIN, 2);
						player->ADD_GOSSIP_ITEM(6, "Tan Bat", GOSSIP_SENDER_MAIN, 283);
						player->ADD_GOSSIP_ITEM(6, "White Bat", GOSSIP_SENDER_MAIN, 4);
                        player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                        break;
 
                case 1002:  
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Bear", GOSSIP_SENDER_MAIN, 8);
						player->ADD_GOSSIP_ITEM(6, "Brown Bear", GOSSIP_SENDER_MAIN, 9);
						player->ADD_GOSSIP_ITEM(6, "Dark Brown Bear", GOSSIP_SENDER_MAIN, 10);
						player->ADD_GOSSIP_ITEM(6, "Grey Bear", GOSSIP_SENDER_MAIN, 11);
						player->ADD_GOSSIP_ITEM(6, "White Bear", GOSSIP_SENDER_MAIN, 12);
						player->ADD_GOSSIP_ITEM(6, "Diseased Black Bear", GOSSIP_SENDER_MAIN, 13);
						player->ADD_GOSSIP_ITEM(6, "Diseased Brown Bear", GOSSIP_SENDER_MAIN, 284);
						player->ADD_GOSSIP_ITEM(6, "Diseased Dark Brown Bear", GOSSIP_SENDER_MAIN, 282);
						player->ADD_GOSSIP_ITEM(6, "Diseased White Bear", GOSSIP_SENDER_MAIN, 17);
                        player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                        break;

				case 1003:
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
                        player->ADD_GOSSIP_ITEM(6, "Black Owl", GOSSIP_SENDER_MAIN, 18);
						player->ADD_GOSSIP_ITEM(6, "Brown Owl", GOSSIP_SENDER_MAIN, 19);
						player->ADD_GOSSIP_ITEM(6, "Dark Brown Owl", GOSSIP_SENDER_MAIN, 20);
						player->ADD_GOSSIP_ITEM(6, "Green Owl", GOSSIP_SENDER_MAIN, 21);
						player->ADD_GOSSIP_ITEM(6, "Grey Owl", GOSSIP_SENDER_MAIN, 22);
						player->ADD_GOSSIP_ITEM(6, "Red/Purple Owl", GOSSIP_SENDER_MAIN, 23);
						player->ADD_GOSSIP_ITEM(6, "Red Owl", GOSSIP_SENDER_MAIN, 24);
						player->ADD_GOSSIP_ITEM(6, "White Owl", GOSSIP_SENDER_MAIN, 25);
						player->ADD_GOSSIP_ITEM(4, "[Next Page] ->", GOSSIP_SENDER_MAIN, 10003);
                        player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                        break;

					case 10003:
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "<- [Previous Page]", GOSSIP_SENDER_MAIN, 1003);
						player->ADD_GOSSIP_ITEM(6, "Bald Eagle", GOSSIP_SENDER_MAIN, 29);
						player->ADD_GOSSIP_ITEM(6, "Brown Eagle", GOSSIP_SENDER_MAIN, 30);
						player->ADD_GOSSIP_ITEM(6, "White Eagle", GOSSIP_SENDER_MAIN, 32);
						player->ADD_GOSSIP_ITEM(6, "Black Hawk", GOSSIP_SENDER_MAIN, 33);
						player->ADD_GOSSIP_ITEM(6, "Brown Hawk", GOSSIP_SENDER_MAIN, 34);
						player->ADD_GOSSIP_ITEM(6, "Blue Parrot", GOSSIP_SENDER_MAIN, 35);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1004:
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Boar", GOSSIP_SENDER_MAIN, 37);
						player->ADD_GOSSIP_ITEM(6, "Brown Boar", GOSSIP_SENDER_MAIN, 38);
						player->ADD_GOSSIP_ITEM(6, "Grey Boar", GOSSIP_SENDER_MAIN, 39);
						player->ADD_GOSSIP_ITEM(6, "Red Boar", GOSSIP_SENDER_MAIN, 40);
						player->ADD_GOSSIP_ITEM(6, "Undead Boar", GOSSIP_SENDER_MAIN, 41);
						player->ADD_GOSSIP_ITEM(6, "Yellow Boar", GOSSIP_SENDER_MAIN, 42);
						player->ADD_GOSSIP_ITEM(6, "Armored Black Boar", GOSSIP_SENDER_MAIN, 43);
						player->ADD_GOSSIP_ITEM(6, "Armored Brown Boar", GOSSIP_SENDER_MAIN, 44);
						player->ADD_GOSSIP_ITEM(6, "Armored Ghostly Boar", GOSSIP_SENDER_MAIN, 45);
						player->ADD_GOSSIP_ITEM(6, "Armored Grey Boar", GOSSIP_SENDER_MAIN, 46);
						player->ADD_GOSSIP_ITEM(6, "Black/Green Felboar", GOSSIP_SENDER_MAIN, 47);
						player->ADD_GOSSIP_ITEM(6, "Blue/White Felboar", GOSSIP_SENDER_MAIN, 48);
						player->ADD_GOSSIP_ITEM(6, "Grey/Orange Felboar", GOSSIP_SENDER_MAIN, 49);
						player->ADD_GOSSIP_ITEM(6, "Red/Black Felboar", GOSSIP_SENDER_MAIN, 51);
						player->ADD_GOSSIP_ITEM(6, "Yellow/Black Felboar", GOSSIP_SENDER_MAIN, 52);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1005:
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Vulture", GOSSIP_SENDER_MAIN, 53);
						player->ADD_GOSSIP_ITEM(6, "Brown Vulture", GOSSIP_SENDER_MAIN, 54);
						player->ADD_GOSSIP_ITEM(6, "Red Vulture", GOSSIP_SENDER_MAIN, 55);
						player->ADD_GOSSIP_ITEM(6, "Black Vulture", GOSSIP_SENDER_MAIN, 56);
						player->ADD_GOSSIP_ITEM(6, "White Vulture", GOSSIP_SENDER_MAIN, 57);
						player->ADD_GOSSIP_ITEM(6, "Ghostly Blue Two-Headed Vulture", GOSSIP_SENDER_MAIN, 58);
						player->ADD_GOSSIP_ITEM(6, "Blue Two-Headed Vulture", GOSSIP_SENDER_MAIN, 59);
						player->ADD_GOSSIP_ITEM(6, "Green Two-Headed Vulture", GOSSIP_SENDER_MAIN, 60);
						player->ADD_GOSSIP_ITEM(6, "White Two-Headed Vulture", GOSSIP_SENDER_MAIN, 5);
						player->ADD_GOSSIP_ITEM(6, "Red Two-Headed Vulture", GOSSIP_SENDER_MAIN, 61);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1006:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "[Next Page] ->", GOSSIP_SENDER_MAIN, 10006);
						player->ADD_GOSSIP_ITEM(6, "Black Cat", GOSSIP_SENDER_MAIN, 62);
						player->ADD_GOSSIP_ITEM(6, "Black Spotted Cat", GOSSIP_SENDER_MAIN, 63);
						player->ADD_GOSSIP_ITEM(6, "Black Striped Cat", GOSSIP_SENDER_MAIN, 64);
						player->ADD_GOSSIP_ITEM(6, "Brown Cat", GOSSIP_SENDER_MAIN, 65);
						player->ADD_GOSSIP_ITEM(6, "Dark Striped Cat", GOSSIP_SENDER_MAIN, 66);
						player->ADD_GOSSIP_ITEM(6, "Orange Spotted Cat", GOSSIP_SENDER_MAIN, 67);
						player->ADD_GOSSIP_ITEM(6, "Orange Striped Cat", GOSSIP_SENDER_MAIN, 68);
						player->ADD_GOSSIP_ITEM(6, "Ghost Cat", GOSSIP_SENDER_MAIN, 69);
						player->ADD_GOSSIP_ITEM(6, "White Cat", GOSSIP_SENDER_MAIN, 70);
						player->ADD_GOSSIP_ITEM(6, "White Spotted Cat", GOSSIP_SENDER_MAIN, 71);
						player->ADD_GOSSIP_ITEM(6, "White Stripped Cat", GOSSIP_SENDER_MAIN, 72);
						player->ADD_GOSSIP_ITEM(6, "Aqua Sabercat", GOSSIP_SENDER_MAIN, 73);
						player->ADD_GOSSIP_ITEM(6, "White Stripped Saber Cat", GOSSIP_SENDER_MAIN, 74);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 10006:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "<- [Previous Page]", GOSSIP_SENDER_MAIN, 1006);
						player->ADD_GOSSIP_ITEM(6, "Dark Striped Sabercat", GOSSIP_SENDER_MAIN, 75);
						player->ADD_GOSSIP_ITEM(6, "Lavender Sabercat", GOSSIP_SENDER_MAIN, 76);
						player->ADD_GOSSIP_ITEM(6, "Orange Spotted Sabercat", GOSSIP_SENDER_MAIN, 77);
						player->ADD_GOSSIP_ITEM(6, "Oranged Striped Sabercat", GOSSIP_SENDER_MAIN, 78);
						player->ADD_GOSSIP_ITEM(6, "Brown Lynx", GOSSIP_SENDER_MAIN, 79);
						player->ADD_GOSSIP_ITEM(6, "Red Lynx", GOSSIP_SENDER_MAIN, 80);
						player->ADD_GOSSIP_ITEM(6, "Black Lion", GOSSIP_SENDER_MAIN, 81);
						player->ADD_GOSSIP_ITEM(6, "Gold Lion", GOSSIP_SENDER_MAIN, 82);
						player->ADD_GOSSIP_ITEM(6, "Lioness", GOSSIP_SENDER_MAIN, 83);
						player->ADD_GOSSIP_ITEM(6, "White Lion", GOSSIP_SENDER_MAIN, 84);
						player->ADD_GOSSIP_ITEM(6, "Hunched Black Gem Cat", GOSSIP_SENDER_MAIN, 85);
						player->ADD_GOSSIP_ITEM(6, "Hunched Black Spotted Cat", GOSSIP_SENDER_MAIN, 86);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1007:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Crab", GOSSIP_SENDER_MAIN, 87);
						player->ADD_GOSSIP_ITEM(6, "Bronze Crab", GOSSIP_SENDER_MAIN, 88);
						player->ADD_GOSSIP_ITEM(6, "Red Crab", GOSSIP_SENDER_MAIN, 89);
						player->ADD_GOSSIP_ITEM(6, "White Crab", GOSSIP_SENDER_MAIN, 90);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1008:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Green Crocolisk", GOSSIP_SENDER_MAIN, 91);
						player->ADD_GOSSIP_ITEM(6, "Grey Crocolisk", GOSSIP_SENDER_MAIN, 92);
						player->ADD_GOSSIP_ITEM(6, "White Crocolisk", GOSSIP_SENDER_MAIN, 93);
						player->ADD_GOSSIP_ITEM(6, "Yellow Crocolisk", GOSSIP_SENDER_MAIN, 94);
						player->ADD_GOSSIP_ITEM(6, "Ghostly Hydra", GOSSIP_SENDER_MAIN, 96);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1009:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Dragonhawk", GOSSIP_SENDER_MAIN, 97);
						player->ADD_GOSSIP_ITEM(6, "Orange/Red Dragonhawk", GOSSIP_SENDER_MAIN, 98);
						player->ADD_GOSSIP_ITEM(6, "Orange Dragonhawk", GOSSIP_SENDER_MAIN, 99);
						player->ADD_GOSSIP_ITEM(6, "Red Dragonhawk", GOSSIP_SENDER_MAIN, 101);
						player->ADD_GOSSIP_ITEM(6, "Violet Dragonhawk", GOSSIP_SENDER_MAIN, 102);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1010:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Gorilla", GOSSIP_SENDER_MAIN, 103);
						player->ADD_GOSSIP_ITEM(6, "Dark Grey Gorilla", GOSSIP_SENDER_MAIN, 104);
						player->ADD_GOSSIP_ITEM(6, "Grey Gorilla", GOSSIP_SENDER_MAIN, 105);
						player->ADD_GOSSIP_ITEM(6, "Red Gorilla", GOSSIP_SENDER_MAIN, 106);
						player->ADD_GOSSIP_ITEM(6, "White Gorilla", GOSSIP_SENDER_MAIN, 107);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1011:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Brown Hyena", GOSSIP_SENDER_MAIN, 108);
						player->ADD_GOSSIP_ITEM(6, "Grey Hyena", GOSSIP_SENDER_MAIN, 109);
						player->ADD_GOSSIP_ITEM(6, "Orange Hyena", GOSSIP_SENDER_MAIN, 110);
						player->ADD_GOSSIP_ITEM(6, "Purple Hyena", GOSSIP_SENDER_MAIN, 111);
						player->ADD_GOSSIP_ITEM(6, "Yellow Hyena", GOSSIP_SENDER_MAIN, 112);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1012:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Beige Moth", GOSSIP_SENDER_MAIN, 114);
						player->ADD_GOSSIP_ITEM(6, "Blue/Yellow Moth", GOSSIP_SENDER_MAIN, 115);
						player->ADD_GOSSIP_ITEM(6, "Blue Moth", GOSSIP_SENDER_MAIN, 116);
						player->ADD_GOSSIP_ITEM(6, "Green Moth", GOSSIP_SENDER_MAIN, 117);
						player->ADD_GOSSIP_ITEM(6, "Tan Moth", GOSSIP_SENDER_MAIN, 118);
						player->ADD_GOSSIP_ITEM(6, "White Moth", GOSSIP_SENDER_MAIN, 119);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1013:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Nether Ray", GOSSIP_SENDER_MAIN, 120);
						player->ADD_GOSSIP_ITEM(6, "Gold Nether Ray", GOSSIP_SENDER_MAIN, 121);
						player->ADD_GOSSIP_ITEM(6, "Green Nether Ray", GOSSIP_SENDER_MAIN, 122);
						player->ADD_GOSSIP_ITEM(6, "Purple Nether Ray", GOSSIP_SENDER_MAIN, 123);
						player->ADD_GOSSIP_ITEM(6, "Red Nether Ray", GOSSIP_SENDER_MAIN, 124);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1014:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Raptor", GOSSIP_SENDER_MAIN, 125);
						player->ADD_GOSSIP_ITEM(6, "Blue Raptor", GOSSIP_SENDER_MAIN, 126);
						player->ADD_GOSSIP_ITEM(6, "Green Raptor", GOSSIP_SENDER_MAIN, 127);
						player->ADD_GOSSIP_ITEM(6, "Grey Raptor", GOSSIP_SENDER_MAIN, 128);
						player->ADD_GOSSIP_ITEM(6, "Orange Raptor", GOSSIP_SENDER_MAIN, 129);
						player->ADD_GOSSIP_ITEM(6, "Purple Raptor", GOSSIP_SENDER_MAIN, 130);
						player->ADD_GOSSIP_ITEM(6, "Red Raptor", GOSSIP_SENDER_MAIN, 131);
						player->ADD_GOSSIP_ITEM(6, "Yellow Raptor", GOSSIP_SENDER_MAIN, 132);
						player->ADD_GOSSIP_ITEM(6, "Spiked Black Raptor", GOSSIP_SENDER_MAIN, 133);
						player->ADD_GOSSIP_ITEM(6, "Spiked Blue Raptor", GOSSIP_SENDER_MAIN, 134);
						player->ADD_GOSSIP_ITEM(6, "Spiked Brown Raptor", GOSSIP_SENDER_MAIN, 135);
						player->ADD_GOSSIP_ITEM(6, "Spiked Green Raptor", GOSSIP_SENDER_MAIN, 136);
						player->ADD_GOSSIP_ITEM(6, "Spiked Red Raptor", GOSSIP_SENDER_MAIN, 137);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1015:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Spiked Orange", GOSSIP_SENDER_MAIN, 138);
						player->ADD_GOSSIP_ITEM(6, "Green/Purple Ravager", GOSSIP_SENDER_MAIN, 141);
						player->ADD_GOSSIP_ITEM(6, "Green Ravager", GOSSIP_SENDER_MAIN, 142);
						player->ADD_GOSSIP_ITEM(6, "Orange/Black Ravager", GOSSIP_SENDER_MAIN, 143);
						player->ADD_GOSSIP_ITEM(6, "Orange/Purple Ravager", GOSSIP_SENDER_MAIN, 144);
						player->ADD_GOSSIP_ITEM(6, "Orange Ravager", GOSSIP_SENDER_MAIN, 146);
						player->ADD_GOSSIP_ITEM(6, "Red/Black Ravager", GOSSIP_SENDER_MAIN, 147);
						player->ADD_GOSSIP_ITEM(6, "Spiked Dark Green Ravager", GOSSIP_SENDER_MAIN, 281);
						player->ADD_GOSSIP_ITEM(6, "Spiked Purple Ravager", GOSSIP_SENDER_MAIN, 151);
						player->ADD_GOSSIP_ITEM(6, "Spiked Red Ravager", GOSSIP_SENDER_MAIN, 152);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1016:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Scorpid", GOSSIP_SENDER_MAIN, 153);
						player->ADD_GOSSIP_ITEM(6, "Bronze Scorpid", GOSSIP_SENDER_MAIN, 154);
						player->ADD_GOSSIP_ITEM(6, "Brown Scorpid", GOSSIP_SENDER_MAIN, 155);
						player->ADD_GOSSIP_ITEM(6, "Pink Scorpid", GOSSIP_SENDER_MAIN, 156);
						player->ADD_GOSSIP_ITEM(6, "Red Scorpid", GOSSIP_SENDER_MAIN, 157);
						player->ADD_GOSSIP_ITEM(6, "Yellow Scorpid", GOSSIP_SENDER_MAIN, 158);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1017:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Serpent", GOSSIP_SENDER_MAIN, 159);
						player->ADD_GOSSIP_ITEM(6, "Teal Serpent", GOSSIP_SENDER_MAIN, 160);
						player->ADD_GOSSIP_ITEM(6, "Brown Serpent", GOSSIP_SENDER_MAIN, 161);
						player->ADD_GOSSIP_ITEM(6, "Purple Serpent", GOSSIP_SENDER_MAIN, 163);
						player->ADD_GOSSIP_ITEM(6, "White Serpent", GOSSIP_SENDER_MAIN, 165);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1018:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "[Next Page] ->", GOSSIP_SENDER_MAIN, 10018);
						player->ADD_GOSSIP_ITEM(6, "Black Widow Spider", GOSSIP_SENDER_MAIN, 166);
						player->ADD_GOSSIP_ITEM(6, "Crystal Spider", GOSSIP_SENDER_MAIN, 167);
						player->ADD_GOSSIP_ITEM(6, "Green Spider", GOSSIP_SENDER_MAIN, 168);
						player->ADD_GOSSIP_ITEM(6, "Grey Spider", GOSSIP_SENDER_MAIN, 169);
						player->ADD_GOSSIP_ITEM(6, "Jungle Spider", GOSSIP_SENDER_MAIN, 170);
						player->ADD_GOSSIP_ITEM(6, "Olive Spider", GOSSIP_SENDER_MAIN, 171);
						player->ADD_GOSSIP_ITEM(6, "Purple Spider", GOSSIP_SENDER_MAIN, 172);
						player->ADD_GOSSIP_ITEM(6, "Red Spider", GOSSIP_SENDER_MAIN, 173);
						player->ADD_GOSSIP_ITEM(6, "Tan Spider", GOSSIP_SENDER_MAIN, 174);
						player->ADD_GOSSIP_ITEM(6, "Spiked Orange/Black Spider", GOSSIP_SENDER_MAIN, 175);
						player->ADD_GOSSIP_ITEM(6, "Spiked Red/Black Spider", GOSSIP_SENDER_MAIN, 176);
						player->ADD_GOSSIP_ITEM(6, "Spiked Red/Yellow Spider", GOSSIP_SENDER_MAIN, 177);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 10018:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "<- [Previous Page]", GOSSIP_SENDER_MAIN, 1018);
						player->ADD_GOSSIP_ITEM(6, "Light Grey Bone Spider", GOSSIP_SENDER_MAIN, 178);
						player->ADD_GOSSIP_ITEM(6, "Green Tarantula", GOSSIP_SENDER_MAIN, 179);
						player->ADD_GOSSIP_ITEM(6, "Grey Tarantula", GOSSIP_SENDER_MAIN, 180);
						player->ADD_GOSSIP_ITEM(6, "Lava Tarantula", GOSSIP_SENDER_MAIN, 181);
						player->ADD_GOSSIP_ITEM(6, "Orange Tarantula", GOSSIP_SENDER_MAIN, 182);
						player->ADD_GOSSIP_ITEM(6, "Red Tarantula", GOSSIP_SENDER_MAIN, 183);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1019:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Sporebat", GOSSIP_SENDER_MAIN, 184);
						player->ADD_GOSSIP_ITEM(6, "Brown Sporebat", GOSSIP_SENDER_MAIN, 185);
						player->ADD_GOSSIP_ITEM(6, "Green Sporebat", GOSSIP_SENDER_MAIN, 186);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1020:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Brown Tallstrider", GOSSIP_SENDER_MAIN, 187);
						player->ADD_GOSSIP_ITEM(6, "Grey Tallstrider", GOSSIP_SENDER_MAIN, 188);
						player->ADD_GOSSIP_ITEM(6, "Pink Tallstrider", GOSSIP_SENDER_MAIN, 189);
						player->ADD_GOSSIP_ITEM(6, "Purple Tallstrider", GOSSIP_SENDER_MAIN, 190);
						player->ADD_GOSSIP_ITEM(6, "Turquoise Tallstrider", GOSSIP_SENDER_MAIN, 191);
						player->ADD_GOSSIP_ITEM(6, "White Tallstrider", GOSSIP_SENDER_MAIN, 192);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1021:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Turtle", GOSSIP_SENDER_MAIN, 193);
						player->ADD_GOSSIP_ITEM(6, "Green Turtle", GOSSIP_SENDER_MAIN, 194);
						player->ADD_GOSSIP_ITEM(6, "Grey Turtle", GOSSIP_SENDER_MAIN, 195);
						player->ADD_GOSSIP_ITEM(6, "Orange Turtle", GOSSIP_SENDER_MAIN, 196);
						player->ADD_GOSSIP_ITEM(6, "White Turtle", GOSSIP_SENDER_MAIN, 197);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1022:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Warpstalker", GOSSIP_SENDER_MAIN, 198);
						player->ADD_GOSSIP_ITEM(6, "Blue/Green Warpstalker", GOSSIP_SENDER_MAIN, 199);
						player->ADD_GOSSIP_ITEM(6, "Green Warpstalker", GOSSIP_SENDER_MAIN, 200);
						player->ADD_GOSSIP_ITEM(6, "Red Warpstalker", GOSSIP_SENDER_MAIN, 201);
						player->ADD_GOSSIP_ITEM(6, "White Warpstaler", GOSSIP_SENDER_MAIN, 202);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1023:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Windserpent", GOSSIP_SENDER_MAIN, 203);
						player->ADD_GOSSIP_ITEM(6, "Green Windserpent", GOSSIP_SENDER_MAIN, 204);
						player->ADD_GOSSIP_ITEM(6, "Orange Windserpent", GOSSIP_SENDER_MAIN, 205);
						player->ADD_GOSSIP_ITEM(6, "Red Windserpent", GOSSIP_SENDER_MAIN, 206);
						player->ADD_GOSSIP_ITEM(6, "White Windserpent", GOSSIP_SENDER_MAIN, 207);
						player->ADD_GOSSIP_ITEM(6, "Yellow Windserpent", GOSSIP_SENDER_MAIN, 208);
						player->ADD_GOSSIP_ITEM(6, "Spiked Blue Windserpent", GOSSIP_SENDER_MAIN, 209);
						player->ADD_GOSSIP_ITEM(6, "Spiked Green Windserpent", GOSSIP_SENDER_MAIN, 210);
						player->ADD_GOSSIP_ITEM(6, "Spiked Grey Windserpent", GOSSIP_SENDER_MAIN, 211);
						player->ADD_GOSSIP_ITEM(6, "Spiked Red Windserpent", GOSSIP_SENDER_MAIN, 212);
						player->ADD_GOSSIP_ITEM(6, "Spiked White Windserpent", GOSSIP_SENDER_MAIN, 213);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1024:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "[Next Page] ->", GOSSIP_SENDER_MAIN, 10024);
						player->ADD_GOSSIP_ITEM(6, "Black Wolf", GOSSIP_SENDER_MAIN, 214);
						player->ADD_GOSSIP_ITEM(6, "Diseased Wolf", GOSSIP_SENDER_MAIN, 215);
						player->ADD_GOSSIP_ITEM(6, "Ghost Wolf", GOSSIP_SENDER_MAIN, 216);
						player->ADD_GOSSIP_ITEM(6, "Grey Wolf", GOSSIP_SENDER_MAIN, 217);
						player->ADD_GOSSIP_ITEM(6, "Tan Wolf", GOSSIP_SENDER_MAIN, 218);
						player->ADD_GOSSIP_ITEM(6, "White Wolf", GOSSIP_SENDER_MAIN, 219);
						player->ADD_GOSSIP_ITEM(6, "Bicolour Worg", GOSSIP_SENDER_MAIN, 220);
						player->ADD_GOSSIP_ITEM(6, "Black Worg", GOSSIP_SENDER_MAIN, 221);
						player->ADD_GOSSIP_ITEM(6, "Brown Worg", GOSSIP_SENDER_MAIN, 222);
						player->ADD_GOSSIP_ITEM(6, "Dark Grey Worg", GOSSIP_SENDER_MAIN, 223);
						player->ADD_GOSSIP_ITEM(6, "Grey Worg", GOSSIP_SENDER_MAIN, 224);
						player->ADD_GOSSIP_ITEM(6, "Red Worg", GOSSIP_SENDER_MAIN, 225);
						player->ADD_GOSSIP_ITEM(6, "White Worg", GOSSIP_SENDER_MAIN, 226);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 10024:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(4, "<- [Previous Page]", GOSSIP_SENDER_MAIN, 1024);
						player->ADD_GOSSIP_ITEM(6, "Black Saber Worg", GOSSIP_SENDER_MAIN, 227);
						player->ADD_GOSSIP_ITEM(6, "Brown Saber Worg", GOSSIP_SENDER_MAIN, 228);
						player->ADD_GOSSIP_ITEM(6, "Grey Saber Worg", GOSSIP_SENDER_MAIN, 229);
						player->ADD_GOSSIP_ITEM(6, "White Saber Worg", GOSSIP_SENDER_MAIN, 230);
						player->ADD_GOSSIP_ITEM(6, "Saddled Black Saber Worg", GOSSIP_SENDER_MAIN, 231);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;
 
 
                case 50:  
                        player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
                        player->ADD_GOSSIP_ITEM(6, "Chimaera", GOSSIP_SENDER_MAIN, 1025);
                        player->ADD_GOSSIP_ITEM(6, "Core Hound", GOSSIP_SENDER_MAIN, 1026);
                        player->ADD_GOSSIP_ITEM(6, "Devilsaur", GOSSIP_SENDER_MAIN, 1027);
                        player->ADD_GOSSIP_ITEM(6, "Rhino", GOSSIP_SENDER_MAIN, 1028);
                        player->ADD_GOSSIP_ITEM(6, "Silithid", GOSSIP_SENDER_MAIN, 1029);
                        player->ADD_GOSSIP_ITEM(6, "Worm", GOSSIP_SENDER_MAIN, 1030);
						player->ADD_GOSSIP_ITEM(6, "Spirit Beast", GOSSIP_SENDER_MAIN, 1031);
                        player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
                        break;

					case 1025:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Beige Chimaera", GOSSIP_SENDER_MAIN, 232);
						player->ADD_GOSSIP_ITEM(6, "Green Chimaera", GOSSIP_SENDER_MAIN, 234);
						player->ADD_GOSSIP_ITEM(6, "White Chimaera", GOSSIP_SENDER_MAIN, 235);
						player->ADD_GOSSIP_ITEM(6, "Armored Green Chimaera", GOSSIP_SENDER_MAIN, 236);
						player->ADD_GOSSIP_ITEM(6, "Armored Purple Chimaera", GOSSIP_SENDER_MAIN,237);
						player->ADD_GOSSIP_ITEM(6, "Armored White Chimaera", GOSSIP_SENDER_MAIN, 238);
						player->ADD_GOSSIP_ITEM(6, "Armored Yellow Chimaera", GOSSIP_SENDER_MAIN, 239);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1026:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Green Corehound", GOSSIP_SENDER_MAIN, 240);
						player->ADD_GOSSIP_ITEM(6, "Grey Corehound", GOSSIP_SENDER_MAIN, 242);
						player->ADD_GOSSIP_ITEM(6, "Red Corehound", GOSSIP_SENDER_MAIN, 243);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1027:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Black Devilsaur", GOSSIP_SENDER_MAIN, 244);
						player->ADD_GOSSIP_ITEM(6, "Green Devilsaur", GOSSIP_SENDER_MAIN, 245);
						player->ADD_GOSSIP_ITEM(6, "Red Devilsaur", GOSSIP_SENDER_MAIN, 246);
						player->ADD_GOSSIP_ITEM(6, "White Devilsaur", GOSSIP_SENDER_MAIN, 247);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1028:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue Rhino", GOSSIP_SENDER_MAIN, 248);
						player->ADD_GOSSIP_ITEM(6, "Brown Rhino", GOSSIP_SENDER_MAIN, 249);
						player->ADD_GOSSIP_ITEM(6, "Grey Rhino", GOSSIP_SENDER_MAIN, 250);
						player->ADD_GOSSIP_ITEM(6, "White Rhino", GOSSIP_SENDER_MAIN, 251);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1029:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Green Silithid", GOSSIP_SENDER_MAIN, 252);
						player->ADD_GOSSIP_ITEM(6, "Purple Silithid", GOSSIP_SENDER_MAIN, 253);
						player->ADD_GOSSIP_ITEM(6, "Tan Silithid", GOSSIP_SENDER_MAIN, 254);
						player->ADD_GOSSIP_ITEM(6, "Yellow Silithid", GOSSIP_SENDER_MAIN, 255);
						player->ADD_GOSSIP_ITEM(6, "Blue Silithid Colossi", GOSSIP_SENDER_MAIN, 256);
						player->ADD_GOSSIP_ITEM(6, "Orange Silithid Colossi", GOSSIP_SENDER_MAIN, 257);
						player->ADD_GOSSIP_ITEM(6, "Pink Silithid Colossi", GOSSIP_SENDER_MAIN, 258);
						player->ADD_GOSSIP_ITEM(6, "Brown Ant Silithid", GOSSIP_SENDER_MAIN, 260);
						player->ADD_GOSSIP_ITEM(6, "Green Ant Silithid", GOSSIP_SENDER_MAIN, 261);
						player->ADD_GOSSIP_ITEM(6, "Purple Ant Silithid", GOSSIP_SENDER_MAIN, 262);
						player->ADD_GOSSIP_ITEM(6, "Tan Ant Silithid", GOSSIP_SENDER_MAIN, 263);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1030:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Blue/Black Worm", GOSSIP_SENDER_MAIN, 275);
						player->ADD_GOSSIP_ITEM(6, "Brown Worm", GOSSIP_SENDER_MAIN, 264);
						player->ADD_GOSSIP_ITEM(6, "Green Worm", GOSSIP_SENDER_MAIN, 265);
						player->ADD_GOSSIP_ITEM(6, "Grey Worm", GOSSIP_SENDER_MAIN, 266);
						player->ADD_GOSSIP_ITEM(6, "White Worm", GOSSIP_SENDER_MAIN, 267);
						player->ADD_GOSSIP_ITEM(6, "Yellow Worm", GOSSIP_SENDER_MAIN, 268);
						player->ADD_GOSSIP_ITEM(6, "Black Jormungar", GOSSIP_SENDER_MAIN, 269);
						player->ADD_GOSSIP_ITEM(6, "Blue Jormungar", GOSSIP_SENDER_MAIN, 270);
						player->ADD_GOSSIP_ITEM(6, "Ghost Jormungar", GOSSIP_SENDER_MAIN, 271);
						player->ADD_GOSSIP_ITEM(6, "Green Jormungar", GOSSIP_SENDER_MAIN, 272);
						player->ADD_GOSSIP_ITEM(6, "Purple Jormungar", GOSSIP_SENDER_MAIN, 273);
						player->ADD_GOSSIP_ITEM(6, "White Jormungar", GOSSIP_SENDER_MAIN, 274);
						player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
						break;

					case 1031:
						player->ADD_GOSSIP_ITEM(4, "<- [Main Menu]", GOSSIP_SENDER_MAIN, 100);
						player->ADD_GOSSIP_ITEM(6, "Spectral Bear", GOSSIP_SENDER_MAIN, 277);
						player->ADD_GOSSIP_ITEM(6, "Spectral Saber Tiger", GOSSIP_SENDER_MAIN, 278);
						player->ADD_GOSSIP_ITEM(6, "Spirit Leapard ", GOSSIP_SENDER_MAIN, 279);
						player->ADD_GOSSIP_ITEM(6, "Lightning Saber Worg ", GOSSIP_SENDER_MAIN, 280);
 
                case GOSSIP_OPTION_STABLEPET:
                        player->GetSession()->SendStablePet(m_creature->GetGUID());
                        break;
                case GOSSIP_OPTION_VENDOR:
                        player->GetSession()->SendListInventory(m_creature->GetGUID());
                        break;

                case 1: //Brown Bat
                        CreatePet(player, m_creature, 1513);
                        break;

                case 2: //Red Bat
                        CreatePet(player, m_creature, 1554);
                        break;

                case 283: //Tan Bat
                        CreatePet(player, m_creature, 4861);
                        break;

                case 4: //White Bat
                        CreatePet(player, m_creature, 10357);
                        break;

                case 8: //Black Bear
                        CreatePet(player, m_creature, 1186);
                        break;

                case 9: //Brown Bear
                        CreatePet(player, m_creature, 17345);
                        break;

                case 10: //Dark Brown Bear
                        CreatePet(player, m_creature, 17348);
                        break;

                case 11: //Grey Bear
                        CreatePet(player, m_creature, 2354);
                        break;

                case 12: //White bear
                        CreatePet(player, m_creature, 1130);
                        break;

                case 13: //diseased black bear
                        CreatePet(player, m_creature, 1815);
                        break;

                case 284: //diseased brown bear
                        CreatePet(player, m_creature, 14280);
                        break;

                case 282: //diseased dark brown bear
                        CreatePet(player, m_creature, 17661);
                        break;

                case 16: //diseased white bear
                        CreatePet(player, m_creature, 26643);
                        break;

                case 18: //black owl
                        CreatePet(player, m_creature, 17053);
                        break;

                case 19: //brown owl
                        CreatePet(player, m_creature, 17034);
                        break;

                case 21: //green owl
                        CreatePet(player, m_creature, 27244);
                        break;

                case 22: //grey owl
                        CreatePet(player, m_creature, 7079);
                        break;

                case 23: //redpurple owl
                        CreatePet(player, m_creature, 21084);
                        break;

                case 24: //red owl
                        CreatePet(player, m_creature, 23051);
                        break;

                case 25: //white owl
                        CreatePet(player, m_creature, 14343);
                        break;

                case 20: //dark brown owl
                        CreatePet(player, m_creature, 19429);
                        break;

                case 29: //bold eagle
                        CreatePet(player, m_creature, 26369);
                        break;

                case 30: //brown eagle
                        CreatePet(player, m_creature, 28004);
                        break;

                case 32: //white eagle
                        CreatePet(player, m_creature, 29044);
                        break;

                case 33: //black hawk
                        CreatePet(player, m_creature, 23945);
                        break;

                case 34: //brown hawk
                        CreatePet(player, m_creature, 24747);
                        break;

                case 35: //blue parrot
                        CreatePet(player, m_creature, 32481);
                        break;

                case 37: //black boar
                        CreatePet(player, m_creature, 119);
                        break;

                case 38: //brown boar
                        CreatePet(player, m_creature, 345);
                        break;

                case 39: //grey boar
                        CreatePet(player, m_creature, 3098);
                        break;

                case 40: //red boar
                        CreatePet(player, m_creature, 547);
                        break;

                case 41: //undead boar
                        CreatePet(player, m_creature, 16117);
                        break;

                case 42: //yellow boar
                        CreatePet(player, m_creature, 2966);
                        break;

                case 43: //armored black boar
                        CreatePet(player, m_creature, 4512);
                        break;

                case 44: //armored brown boar
                        CreatePet(player, m_creature, 4511);
                        break;

                case 45: //armored brown ghost boar
                        CreatePet(player, m_creature, 6021);
                        break;

                case 46: //armored grey boar
                        CreatePet(player, m_creature, 4514);
                        break;

                case 47: //black felboar
                        CreatePet(player, m_creature, 21878);
                        break;

                case 48: //blue felboar
                        CreatePet(player, m_creature, 22180);
                        break;

                case 49: //orange felboar
                        CreatePet(player, m_creature, 16863);
                        break;

                case 51: //red felboar
                        CreatePet(player, m_creature, 16880);
                        break;

                case 52: //yellow felboar
                        CreatePet(player, m_creature, 21195);
                        break;

                case 53: //blue vulture
                        CreatePet(player, m_creature, 7376);
                        break;

                case 54: //brown vulture
                        CreatePet(player, m_creature, 1109);
                        break;

                case 55: //red vulture
                        CreatePet(player, m_creature, 5429);
                        break;

                case 56: //black vulture
                        CreatePet(player, m_creature, 2829);
                        break;

                case 57: //white vulture
                        CreatePet(player, m_creature, 2931);
                        break;

                case 58: //ghost blue two headed vulture
                        CreatePet(player, m_creature, 21470);
                        break;

                case 59: //blue two headed vulture
                        CreatePet(player, m_creature, 18707);
                        break;

                case 60: //green two headed vulture
                        CreatePet(player, m_creature, 5983);
                        break;

                case 5: //white two headed vulture
                        CreatePet(player, m_creature, 21515);
                        break;

                case 61: //red two headed vulture
                        CreatePet(player, m_creature, 16973);
                        break;

                case 62: //black cat
                        CreatePet(player, m_creature, 977);
                        break;

                case 63: //black spotted cat
                        CreatePet(player, m_creature, 18982);
                        break;

                case 64: //black striped cat
                        CreatePet(player, m_creature, 21723);
                        break;

                case 65: //brown cat
                        CreatePet(player, m_creature, 24064);
                        break;

                case 66: //dark striped cat
                        CreatePet(player, m_creature, 17023);
                        break;

                case 67: //orange spotted cat
                        CreatePet(player, m_creature, 2731);
                        break;

                case 68: //orange striped cat
                        CreatePet(player, m_creature, 682);
                        break;

                case 69: //ghost cat
                        CreatePet(player, m_creature, 3619);
                        break;

                case 70: //white cat
                        CreatePet(player, m_creature, 7430);
                        break;

                case 71: //white spotted cat
                        CreatePet(player, m_creature, 29327);
                        break;

                case 72: //white striped cat
                        CreatePet(player, m_creature, 21724);
                        break;

                case 73: //aqua sabar cat
                        CreatePet(player, m_creature, 10200);
                        break;

                case 75: //dark striped saber cat
                        CreatePet(player, m_creature, 2175);
                        break;

                case 76: //lavender saber cat
                        CreatePet(player, m_creature, 7434);
                        break;

                case 77: //orange spotted saber cat
                        CreatePet(player, m_creature, 28001);
                        break;

                case 78: //orange striped saber cat
                        CreatePet(player, m_creature, 28297);
                        break;

                case 74: //white striped saber cat
                        CreatePet(player, m_creature, 7431);
                        break;

                case 79: //brown lynx
                        CreatePet(player, m_creature, 16348);
                        break;

                case 80: //red lynx
                        CreatePet(player, m_creature, 15651);
                        break;

                case 81: //black lion
                        CreatePet(player, m_creature, 28097);
                        break;

                case 82: //gold lion
                        CreatePet(player, m_creature, 5807);
                        break;

                case 83: //lioness
                        CreatePet(player, m_creature, 14222);
                        break;

                case 84: //white lion
                        CreatePet(player, m_creature, 3475);
                        break;

                case 85: //black gem cat
                        CreatePet(player, m_creature, 28115);
                        break;

                case 86: //black spotted cat
                        CreatePet(player, m_creature, 28404);
                        break;

                case 87: //blue crab
                        CreatePet(player, m_creature, 26521);
                        break;

                case 88: //bronze crab
                        CreatePet(player, m_creature, 830);
                        break;

                case 89: //red crab
                        CreatePet(player, m_creature, 23929);
                        break;

                case 90: //white crab
                        CreatePet(player, m_creature, 24478);
                        break;

                case 91: //green crocolisk
                        CreatePet(player, m_creature, 4344);
                        break;

                case 92: //grey crocolisk
                        CreatePet(player, m_creature, 17952);
                        break;

                case 93: //white crocolisk
                        CreatePet(player, m_creature, 20773);
                        break;

                case 94: //yellow crocolisk
                        CreatePet(player, m_creature, 1693);
                        break;

                case 96: //ghost hydra
                        CreatePet(player, m_creature, 29033);
                        break;

                case 97: //blue dragonhawk
                        CreatePet(player, m_creature, 25867);
                        break;

                case 98: //orange red dragonhawk
                        CreatePet(player, m_creature, 15650);
                        break;

                case 99: //orange dragonhawk
                        CreatePet(player, m_creature, 15649);
                        break;

                case 101: //red dragon hawk
                        CreatePet(player, m_creature, 18155);
                        break;

                case 102: //violet dragonhawk
                        CreatePet(player, m_creature, 20502);
                        break;

                case 103: //black gorilla
                        CreatePet(player, m_creature, 28096);
                        break;

                case 104: //dark grey gorilla
                        CreatePet(player, m_creature, 1559);
                        break;

                case 105: //grey gorilla
                        CreatePet(player, m_creature, 28098);
                        break;

                case 106: //red gorilla
                        CreatePet(player, m_creature, 9622);
                        break;

                case 107: //white gorilla
                        CreatePet(player, m_creature, 6585);
                        break;

                case 108: //brown hyena
                        CreatePet(player, m_creature, 4690);
                        break;

                case 109: //grey hyena
                        CreatePet(player, m_creature, 5985);
                        break;

                case 110: //orange hyena
                        CreatePet(player, m_creature, 4534);
                        break;

                case 111: //purple hyena
                        CreatePet(player, m_creature, 5427);
                        break;

                case 112: //yellow hyena
                        CreatePet(player, m_creature, 12418);
                        break;

                case 114: //beige moth
                        CreatePet(player, m_creature, 18468);
                        break;

                case 115: //blue yellow moth
                        CreatePet(player, m_creature, 18438);
                        break;

                case 116: //blue moth
                        CreatePet(player, m_creature, 20611);
                        break;

                case 117: //green moth
                        CreatePet(player, m_creature, 18437);
                        break;

                case 118: //tan moth
                        CreatePet(player, m_creature, 25464);
                        break;

                case 119: //white moth
                        CreatePet(player, m_creature, 25498);
                        break;

                case 120: //blue nether ray
                        CreatePet(player, m_creature, 18131);
                        break;

                case 121: //gold nether ray
                        CreatePet(player, m_creature, 22181);
                        break;

                case 122: //green nether ray
                        CreatePet(player, m_creature, 20196);
                        break;

                case 123: //purple nether ray
                        CreatePet(player, m_creature, 18880);
                        break;

                case 124: //red nether ray
                        CreatePet(player, m_creature, 21901);
                        break;

                case 125: //black raptor
                        CreatePet(player, m_creature, 23873);
                        break;

                case 126: //blue raptor
                        CreatePet(player, m_creature, 730);
                        break;

                case 127: //green raptor
                        CreatePet(player, m_creature, 6581);
                        break;

                case 128: //grey raptor
                        CreatePet(player, m_creature, 29334);
                        break;

                case 129: //orange raptor
                        CreatePet(player, m_creature, 1019);
                        break;

                case 130: //purple raptor
                        CreatePet(player, m_creature, 3632);
                        break;

                case 131: //red raptor
                        CreatePet(player, m_creature, 3123);
                        break;

                case 132: //yellow raptor
                        CreatePet(player, m_creature, 2561);
                        break;

                case 133: //black spiked raptor
                        CreatePet(player, m_creature, 20729);
                        break;

                case 134: //blue spiked raptor
                        CreatePet(player, m_creature, 29698);
                        break;

                case 135: //brown spiked raptor
                        CreatePet(player, m_creature, 20634);
                        break;

                case 136: //green spiked raptor
                        CreatePet(player, m_creature, 21124);
                        break;

                case 137: //red spiked raptor
                        CreatePet(player, m_creature, 20751);
                        break;

                case 138: //spiked orange ravager
                        CreatePet(player, m_creature, 17199);
                        break;

                case 141: //green purple ravager
                        CreatePet(player, m_creature, 19189);
                        break;

                case 142: //green ravager
                        CreatePet(player, m_creature, 24922);
                        break;

                case 143: //orange black ravager
                        CreatePet(player, m_creature, 16932);
                        break;

                case 144: //orange purple ravager
                        CreatePet(player, m_creature, 21423);
                        break;

                case 146: //orange ravager
                        CreatePet(player, m_creature, 17199);
                        break;

                case 147: //red black ravager
                        CreatePet(player, m_creature, 19350);
                        break;

                case 281: //spiked green ravager
                        CreatePet(player, m_creature, 16934);
                        break;

                case 151: //spiked purple ravager
                        CreatePet(player, m_creature, 19349);
                        break;

                case 152: //spiked red ravager
                        CreatePet(player, m_creature, 16933);
                        break;

                case 153: //black scorpid
                        CreatePet(player, m_creature, 7022);
                        break;

                case 154: //bronze scorpid
                        CreatePet(player, m_creature, 9691);
                        break;

                case 155: //brown scorpid
                        CreatePet(player, m_creature, 15336);
                        break;

                case 156: //pink scorpid
                        CreatePet(player, m_creature, 15240);
                        break;

                case 157: //red scorpid
                        CreatePet(player, m_creature, 15196);
                        break;

                case 158: //yellow scorpid
                        CreatePet(player, m_creature, 11736);
                        break;

                case 159: //blue serpent
                        CreatePet(player, m_creature, 5048);
                        break;

                case 160: //teal serpent
                        CreatePet(player, m_creature, 5225);
                        break;

                case 161: //brown serpent
                        CreatePet(player, m_creature, 28011);
                        break;

                case 163: //purple serpent
                        CreatePet(player, m_creature, 5755);
                        break;

                case 165: //white serpent
                        CreatePet(player, m_creature, 7268);
                        break;

                case 166: //black widow spider
                        CreatePet(player, m_creature, 1505);
                        break;

                case 167: //crystal spider
                        CreatePet(player, m_creature, 10596);
                        break;

                case 168: //green spider
                        CreatePet(player, m_creature, 4379);
                        break;

                case 169: //grey spider
                        CreatePet(player, m_creature, 217);
                        break;

                case 170: //jungle spider
                        CreatePet(player, m_creature, 15976);
                        break;

                case 171: //olive spider
                        CreatePet(player, m_creature, 22044);
                        break;

                case 172: //purple spider
                        CreatePet(player, m_creature, 29461);
                        break;

                case 173: //red spider
                        CreatePet(player, m_creature, 20682);
                        break;

                case 174: //tan spider
                        CreatePet(player, m_creature, 22132);
                        break;

                case 175: //spiked orange spider
                        CreatePet(player, m_creature, 28342);
                        break;

                case 176: //spiked red black spider
                        CreatePet(player, m_creature, 17683);
                        break;

                case 177: //spiked red yellow spider
                        CreatePet(player, m_creature, 17522);
                        break;

                case 178: //light grey bone spider
                        CreatePet(player, m_creature, 32475);
                        break;

                case 179: //green tarantula
                        CreatePet(player, m_creature, 1986);
                        break;

                case 180: //grey tarantula
                        CreatePet(player, m_creature, 14266);
                        break;

                case 181: //lava tarantula
                        CreatePet(player, m_creature, 5857);
                        break;

                case 182: //orange tarantula
                        CreatePet(player, m_creature, 442);
                        break;

                case 183: //red tarantula
                        CreatePet(player, m_creature, 11738);
                        break;

                case 184: //blue sporebat
                        CreatePet(player, m_creature, 18128);
                        break;

                case 185: //brown sporebat
                        CreatePet(player, m_creature, 18280);
                        break;

                case 186: //green sporebat
                        CreatePet(player, m_creature, 18129);
                        break;

                case 187: //brown tallstrider
                        CreatePet(player, m_creature, 2955);
                        break;

                case 188: //grey tallstrider
                        CreatePet(player, m_creature, 2956);
                        break;

                case 189: //pink tallstrider
                        CreatePet(player, m_creature, 3068);
                        break;

                case 190: //purple tallstrider
                        CreatePet(player, m_creature, 22807);
                        break;

                case 191: //turquoise tallstrider
                        CreatePet(player, m_creature, 2172);
                        break;

                case 192: //white tallstrider
                        CreatePet(player, m_creature, 3246);
                        break;

                case 193: //blue turtle
                        CreatePet(player, m_creature, 3653);
                        break;

                case 194: //green turtle
                        CreatePet(player, m_creature, 4824);
                        break;

                case 195: //grey turtle
                        CreatePet(player, m_creature, 4397);
                        break;

                case 196: //orange turtle
                        CreatePet(player, m_creature, 22885);
                        break;

                case 197: //white turtle
                        CreatePet(player, m_creature, 25482);
                        break;

                case 198: //black warp stalker
                        CreatePet(player, m_creature, 23163);
                        break;

                case 199: //blue green warp stalker
                        CreatePet(player, m_creature, 18884);
                        break;

                case 200: //green warp stalker
                        CreatePet(player, m_creature, 20906);
                        break;

                case 201: //red warp stalker
                        CreatePet(player, m_creature, 22255);
                        break;

                case 202: //white warp stalker
                        CreatePet(player, m_creature, 23219);
                        break;

                case 203: //black windserpent
                        CreatePet(player, m_creature, 5056);
                        break;

                case 204: //green windserpent
                        CreatePet(player, m_creature, 5756);
                        break;

                case 205: //orange wind serpent
                        CreatePet(player, m_creature, 5307);
                        break;

                case 206: //red wind serpent
                        CreatePet(player, m_creature, 5708);
                        break;

                case 207: //white wind serpent
                        CreatePet(player, m_creature, 26806);
                        break;

                case 208: //yellow wind serpent
                        CreatePet(player, m_creature, 8336);
                        break;

                case 209: //spiked blue wind serpent
                        CreatePet(player, m_creature, 26446);
                        break;

                case 210: //spiked green wind serpent
                        CreatePet(player, m_creature, 21123);
                        break;

                case 211: //spiked grey wind serpent
                        CreatePet(player, m_creature, 20673);
                        break;

                case 212: //spiked red wind serpent
                        CreatePet(player, m_creature, 20749);
                        break;

                case 213: //spiked white wind serpent
                        CreatePet(player, m_creature, 28477);
                        break;

                case 214: //black wolf
                        CreatePet(player, m_creature, 20330);
                        break;

                case 215: //diseased black wolf
                        CreatePet(player, m_creature, 1817);
                        break;

                case 216: //ghost wolf
                        CreatePet(player, m_creature, 26111);
                        break;

                case 217: //grey wolf
                        CreatePet(player, m_creature, 1508);
                        break;

                case 218: //tan wolf
                        CreatePet(player, m_creature, 2958);
                        break;

                case 219: //white wolf
                        CreatePet(player, m_creature, 29993);
                        break;

                case 220: //bicolor worg
                        CreatePet(player, m_creature, 10220);
                        break;

                case 221: //black worg
                        CreatePet(player, m_creature, 10221);
                        break;

                case 222: //brown worg
                        CreatePet(player, m_creature, 19458);
                        break;

                case 223: //dark grey worg
                        CreatePet(player, m_creature, 8211);
                        break;

                case 224: //grey worg
                        CreatePet(player, m_creature, 118);
                        break;

                case 225: //red worg
                        CreatePet(player, m_creature, 2753);
                        break;

                case 226: //white worg
                        CreatePet(player, m_creature, 521);
                        break;

                case 227: //black saber worg
                        CreatePet(player, m_creature, 24475);
                        break;

                case 228: //brown saber worg
                        CreatePet(player, m_creature, 24516);
                        break;

                case 229: //grey saber worg
                        CreatePet(player, m_creature, 24517);
                        break;

                case 230: //white saber worg
                        CreatePet(player, m_creature, 24677);
                        break;

                case 231: //saddled black worg
                        CreatePet(player, m_creature, 17669);
                        break;

                case 232: //beige chimeara
                        CreatePet(player, m_creature, 8764);
                        break;

                case 234: //green chimeara
                        CreatePet(player, m_creature, 8660);
                        break;

                case 235: //white chimeara
                        CreatePet(player, m_creature, 24673);
                        break;

                case 236: //armored green chimeara
                        CreatePet(player, m_creature, 21789);
                        break;

                case 237: //armored purple chimeara
                        CreatePet(player, m_creature, 20932);
                        break;

                case 238: //armored white chimeara
                        CreatePet(player, m_creature, 11497);
                        break;

                case 239: //armored yellow chimeara
                        CreatePet(player, m_creature, 21033);
                        break;

                case 240: //green corehound
                        CreatePet(player, m_creature, 21102);
                        break;

                case 242: //grey corehound
                        CreatePet(player, m_creature, 17447);
                        break;

                case 243: //red corehound
                        CreatePet(player, m_creature, 11671);
                        break;

                case 244: //black devilsaur
                        CreatePet(player, m_creature, 6499);
                        break;

                case 245: //green devilsaur
                        CreatePet(player, m_creature, 32485);
                        break;

                case 246: //red devilsaur
                        CreatePet(player, m_creature, 6584);
                        break;

                case 247: //white devilsaur
                        CreatePet(player, m_creature, 6498);
                        break;

                case 248: //blue rhino
                        CreatePet(player, m_creature, 29838);
                        break;

                case 249: //brown rhino
                        CreatePet(player, m_creature, 25488);
                        break;

                case 250: //grey rhino
                        CreatePet(player, m_creature, 28288);
                        break;

                case 251: //white rhino
                        CreatePet(player, m_creature, 32361);
                        break;

                case 252: //green silithid
                        CreatePet(player, m_creature, 15622);
                        break;

                case 253: //purple silithid
                        CreatePet(player, m_creature, 14473);
                        break;

                case 254: //tan silithid
                        CreatePet(player, m_creature, 15230);
                        break;

                case 255: //yellow silithid
                        CreatePet(player, m_creature, 15323);
                        break;

                case 256: //blue giant silithid
                        CreatePet(player, m_creature, 15543);
                        break;

                case 257: //orange giant silithid
                        CreatePet(player, m_creature, 15511);
                        break;

                case 258: //pink giant silithid
                        CreatePet(player, m_creature, 15544);
                        break;

                case 260: //brown ant silithid
                        CreatePet(player, m_creature, 11725);
                        break;

                case 261: //green ant silithid
                        CreatePet(player, m_creature, 15229);
                        break;

                case 262: //purple ant silithid
                        CreatePet(player, m_creature, 11733);
                        break;

                case 263: //tan ant silithid
                        CreatePet(player, m_creature, 15300);
                        break;

                case 275: //blue worm
                        CreatePet(player, m_creature, 11789);
                        break;

                case 264: //brown worm
                        CreatePet(player, m_creature, 21381);
                        break;

                case 265: //green worm
                        CreatePet(player, m_creature, 11788);
                        break;

                case 266: //grey worm
                        CreatePet(player, m_creature, 11741);
                        break;

                case 267: //white worm
                        CreatePet(player, m_creature, 5226);
                        break;

                case 268: //yellow worm
                        CreatePet(player, m_creature, 14477);
                        break;

                case 269: //black jormungar
                        CreatePet(player, m_creature, 26360);
                        break;

                case 270: //blue jormungar
                        CreatePet(player, m_creature, 30291);
                        break;

                case 271: //ghost jormungar
                        CreatePet(player, m_creature, 30423);
                        break;

                case 272: //green jormungar
                        CreatePet(player, m_creature, 26358);
                        break;

                case 273: //purple jormungar
                        CreatePet(player, m_creature, 25454);
                        break;

                case 274: //white jormungar
                        CreatePet(player, m_creature, 26359);
                        break;

                case 277: //spectral bear
                        CreatePet(player, m_creature, 38453);
                        break;

                case 278: //spectral tiger
                        CreatePet(player, m_creature, 33776);
                        break;

                case 279: //spirit leopard
                        CreatePet(player, m_creature, 32517);
                        break;

                case 280: //lighting worg
                        CreatePet(player, m_creature, 35189);
                        break;


                }
                return true;
        }
};
 
void AddSC_Npc_Beastmaster()
{
        new Npc_Beastmaster();
}
