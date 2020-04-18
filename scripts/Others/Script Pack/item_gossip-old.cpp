#include "ScriptPCH.h"
#include "Chat.h"

class ItemUse_item_custom_test : public ItemScript
{
	public:
		ItemUse_item_custom_test() : ItemScript("item_gossip") {}

		bool OnGossipHello(Player* player, Item* item)
		{
			player->ADD_GOSSIP_ITEM(4, "Mall", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
			player->PlayerTalkClass->SendGossipMenu(534, item->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
		{
			switch(action)
			{
				case GOSSIP_ACTION_INFO_DEF+1:
				  player->CastSpell(player,35517,false);
                  player->TeleportTo(571, 4627.821289f, -5642.055664f, -113.147522f, 4.170808f);
				  ChatHandler(player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Mall|r!", player->GetName());
					break;
			}

			return true;
		}
};

void AddSC_ItemUse_item_custom_test()
{
	new ItemUse_item_custom_test();
}