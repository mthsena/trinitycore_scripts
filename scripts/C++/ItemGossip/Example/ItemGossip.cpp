#include "ScriptPCH.h"

class ItemGossip_Example : public ItemScript
{
public:
    ItemGossip_Example() : ItemScript("ItemGossip_Example") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
    {
        player->PlayerTalkClass->ClearMenus();

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Menu", GOSSIP_SENDER_MAIN, 1);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
        return true;
    }

    void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            break;
        }
    }
};

void AddSC_ItemGossip_Example()
{
    new ItemGossip_Example();
}