#include "ScriptPCH.h"
     
    class Mall_Guide_NPC : public CreatureScript
    {
            public:
          Mall_Guide_NPC() : CreatureScript("Mall_Guide_NPC") { }
     
                    bool OnGossipHello(Player * player, Creature * creature)
                    {
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "284 Items", GOSSIP_SENDER_MAIN, 1);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Arena Weapons", GOSSIP_SENDER_MAIN, 2);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Gems and Enchants", GOSSIP_SENDER_MAIN, 3);                                
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "PvE Weapons", GOSSIP_SENDER_MAIN, 4);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Season 8", GOSSIP_SENDER_MAIN, 5);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "264 BiS / 10.5 Heroic", GOSSIP_SENDER_MAIN, 6);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Reagents", GOSSIP_SENDER_MAIN, 8);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mounts & Companions", GOSSIP_SENDER_MAIN, 9);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Transmogrification", GOSSIP_SENDER_MAIN, 11);
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Quest Building", GOSSIP_SENDER_MAIN, 13);  
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Arena Battle Masters", GOSSIP_SENDER_MAIN, 16);
						player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
						return true;
					}
					
					bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
					{
						player->PlayerTalkClass->ClearMenus();
               
						switch(uiAction)
						{
						case 1:
							player->TeleportTo(530, -3069.394287f, 744.839661f, -9.947959f, 3.3711818f);
							player->PlayerTalkClass->SendCloseGossip();
							break;
						
						case 2:
							player->TeleportTo(530, -3069.394287f, 744.839661f, -9.947959f, 3.3711818f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 3:
							player->TeleportTo(530, -3004.956496f, 831.831604f, -9.979859f,  0.165748f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 4:
							player->TeleportTo(530, -3033.995605f, 852.717346f, -9.303583f, 1.837854f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 5:
							player->TeleportTo(530, -3049.50615f, 824.107361f, -10.502844f, 2.523511f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 6:
							player->TeleportTo(530, -3067.342773f, 804.728088f, -9.190586f, 2.843953f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 7:
							player->TeleportTo(530, -3067.677734f, 788.065857f, -10.011227f, 3.107062f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 8:
							player->TeleportTo(530, -3040.119385f, 762.909912f, -10.241382f, 5.317174f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 9:
							player->TeleportTo(530, -3067.914551f, 765.689819f, -10.147302, 3.381872f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 10:
							player->TeleportTo(530, -3020.750000f, 778.107971f, -10.062300f, 2.95240f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 11:
							player->TeleportTo(530, -3049.460693f, 745.850708f, -9.665066f, 4.766610f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 12:
							player->TeleportTo(530, -3020.750000f, 778.107971f, -10.062300f, 2.95240f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 13:
							player->TeleportTo(530, -3015.476074f, 855.437439f, -10.477199f, 0.384086f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 14:
							player->TeleportTo(530, -3037.530518f, 815.546814f, -10.334641f, 2.540788f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 15:
							player->TeleportTo(530, -2993.192627f, 787.042603f, -8.054831f, 2.460678f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 16:
							player->TeleportTo(530, -3040.119385f, 762.909912f, -10.241382f, 5.317174f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 17:
							player->TeleportTo(530, -3069.394287f, 744.839661f, -9.947959f, 3.3711818f);
							player->PlayerTalkClass->SendCloseGossip();
							break;

							case 18:
							player->TeleportTo(530, -3040.892334f, 778.114807f, -10.118193f, 4.485646f);
							player->PlayerTalkClass->SendCloseGossip();
							break;
						}
						return true;
					}
};
     
void AddSC_Mall_Guide_NPC()
{
	new Mall_Guide_NPC;
}