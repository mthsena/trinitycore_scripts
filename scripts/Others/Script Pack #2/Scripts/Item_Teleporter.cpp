#include "ScriptPCH.h"

class Item_Teleporter : public ItemScript
{
public:
		Item_Teleporter() : ItemScript ("Item_Teleporter") { }

	bool onUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
	{
		player->ADD_GOSSIP_ITEM(2, "test menu 1", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(2, "test menu 2", GOSSIP_SENDER_MAIN, 2);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,item->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Item* item, uint32 sender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
			{
			case 1:
				ChatHandler(player->GetSession()).PSendSysMessage("test message number 1 :).");
				break;
			case 2:
				ChatHandler(player->GetSession()).PSendSysMessage("test message number 2 :).");
				break;
			}
	}
};

void AddSC_Item_Teleporter()
{
	new Item_Teleporter;
}