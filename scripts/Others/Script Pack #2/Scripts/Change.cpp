//Special Thanks for Saqirmdev
#include "ScriptPCH.h"
#include "InstanceSaveMgr.h"
#include "InstanceScript.h"
#include "MapManager.h"

class npc_change : public CreatureScript
{
    public:
        npc_change() : CreatureScript("npc_change") { }

         bool OnGossipHello(Player *player, Creature *_creature)
           {
		        if (player->isInCombat()) 
                {		
				     /// @todo check Combat
                    _creature->MonsterWhisper("You are in Combat", player->GetGUID());
				    player->CLOSE_GOSSIP_MENU();
					return true;
                }
                else
                { 
				    player->ADD_GOSSIP_ITEM( 0, "10 Mark -> Reset Instance"                                    , GOSSIP_SENDER_MAIN, 1);
				    player->ADD_GOSSIP_ITEM( 0, "10 Mark -> 25 Arena Points"                                   , GOSSIP_SENDER_MAIN, 2);
				    player->ADD_GOSSIP_ITEM( 0, "10 Badge of Justice -> 1 Mark"                                             , GOSSIP_SENDER_MAIN, 3);
				    player->ADD_GOSSIP_ITEM( 0, "2 Mark -> 1 EoT"                                              , GOSSIP_SENDER_MAIN, 4);
				    player->ADD_GOSSIP_ITEM( 0, "4 Mark -> 5000 Honor"                                         , GOSSIP_SENDER_MAIN, 5);
				    player->ADD_GOSSIP_ITEM( 0, "1 Mark -> 10 Badge of Justice"                                             , GOSSIP_SENDER_MAIN, 6);
				    player->ADD_GOSSIP_ITEM( 0, "1 Mark -> 10 Wood(GH MARK)"                                   , GOSSIP_SENDER_MAIN, 7);
				    player->ADD_GOSSIP_ITEM( 0, "1 Mark -> 1 Metal(GH MARK)"                                   , GOSSIP_SENDER_MAIN, 7);
				    player->ADD_GOSSIP_ITEM( 0, "100 Mark -> [MOUNT]Reins of the Raven Lord"                   , GOSSIP_SENDER_MAIN, 16);
				    player->ADD_GOSSIP_ITEM( 0, "50 Mark -> [MOUNT]Swift Zhevra"                               , GOSSIP_SENDER_MAIN, 17);
				    player->ADD_GOSSIP_ITEM( 0, "75 Mark -> [MOUNT]Swift Zulian Tiger"                         , GOSSIP_SENDER_MAIN, 18);
		        }	


				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
			    return true;
            }

            bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
            {

                if (sender != GOSSIP_SENDER_MAIN)
				    return true;

                player->PlayerTalkClass->ClearMenus();

                switch(uiAction)
                {

                    case 1:
					    if (player->HasItemCount(19322, 10, true))
						{
							player->DestroyItemCount(19322, 10, true);
							// Unbind ALL instances
							for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
							{
								Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
								for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
								{
									InstanceSave* save = itr->second.save;
									if (itr->first != player->GetMapId())
										player->UnbindInstance(itr, Difficulty(i));
									else
										++itr;
								}
							}
							_creature->MonsterWhisper("Unbind all Instances complete!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
						else
						{
							_creature->MonsterWhisper("Missing items", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
                        break;
 
                    case 2:
					    if (player->HasItemCount(19322, 10, true))
						{

							player->DestroyItemCount(19322, 10, true);								
							player->ModifyArenaPoints(+25);
							_creature->MonsterWhisper("Change Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

						}
						else
						{
							_creature->MonsterWhisper("Missing Items.", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();									
						}
                        break;


                    case 3:
					    if (player->HasItemCount(29434, 10, true))
						{
						    player->DestroyItemCount(29434, 10, true);								
							player->AddItem(19322, 1);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

						}
						else
						{									
							_creature->MonsterWhisper("You need more Badge of Justice!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
                        break;

                    case 4:
					    if (player->HasItemCount(19322, 2, true))
						{

							player->DestroyItemCount(19322, 2, true);								
							player->AddItem(47241, 1);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{									
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
					    }
                        break;

                    case 5:
					    if (player->HasItemCount(19322, 4, true))
						{

							player->ModifyHonorPoints(+5000);							
							player->DestroyItemCount(19322, 4, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
                    case 6:
					    if (player->HasItemCount(19322, 1, true))
						{
						    player->AddItem(29434, 10);
							player->DestroyItemCount(19322, 1, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
                    case 7: // Wood 
					    if (player->HasItemCount(19322, 1, true))
						{
						    player->AddItem(4470, 10);
							player->DestroyItemCount(19322, 1, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
                    case 8: // Metal
					    if (player->HasItemCount(19322, 1, true))
						{
						    player->AddItem(35691, 1);
							player->DestroyItemCount(19322, 1, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
						
						
						
						
						
				    case 16: // Raven Lord Mount
					    if (player->HasItemCount(19322, 100, true))
						{
						    player->AddItem(32768, 1);
							player->DestroyItemCount(19322, 100, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
						
				    case 17: // Swift Zhevra Mount
					    if (player->HasItemCount(19322, 50, true))
						{
						    player->AddItem(37719, 1);
							player->DestroyItemCount(19322, 50, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
				    case 18: // Swift Zulian tiger Mount
					    if (player->HasItemCount(19322, 75, true))
						{
						    player->AddItem(19902, 1);
							player->DestroyItemCount(19322, 75, true);
							_creature->MonsterWhisper("Chance Succesful!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
						else
						{
							_creature->MonsterWhisper("Missing Items!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();

					    }
                        break;
                    default:
                        break;
                }
                return true;
        }
};

void AddSC_npc_change()
{
    new npc_change();
}
