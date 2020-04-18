#include "ScriptPCH.h"

class New_Dawning_Mage : public CreatureScript
{
public:
	New_Dawning_Mage() : CreatureScript("New_Dawning_Mage") { }

	bool OnGossipHello(Player * player, Creature * creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Take me to Alcabazar Slithern's laboratory.", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Take me to Avillius Gashoop's laboratory.", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Take me to Merdonal Clash's laboratory.", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Forget it, I'm too scared.", GOSSIP_SENDER_MAIN, 4);
		player->PlayerTalkClass->SendGossipMenu(13333338, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		switch(uiAction)
		{
		case 1: // Take me to Alcabazar Slithern's laboratory.
			creature->MonsterWhisper("I wish you best of luck.", player->GetGUID());
			player->TeleportTo(0, -10384.2f, 414.293f, 29.0793f, 6.06678f);
			player->PlayerTalkClass->SendCloseGossip();
			break;

		case 2: // Take me to Avillius Gashoop's laboratory.
			creature->MonsterWhisper("I wish you best of luck.", player->GetGUID());
			player->TeleportTo(0, 1356.37f, -2574.06f, 109.879f, 0.0386488f);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		
		case 3: // Take me to Merdonal Clash's laboratory.
			creature->MonsterWhisper("I wish you best of luck.", player->GetGUID());
			player->TeleportTo(0, -6569.56f, -3486.64f, 313.998f, 1.54238f);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		
		case 4: // Forget it, I'm too scared.
			player->PlayerTalkClass->SendCloseGossip();
			break;

		}
		return true;
	}
};
     
void AddSC_New_Dawning_Mage()
{
	new New_Dawning_Mage;
}