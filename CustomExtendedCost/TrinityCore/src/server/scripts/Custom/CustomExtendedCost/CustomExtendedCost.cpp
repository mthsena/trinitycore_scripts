#include "CustomExtendedCost.h"

uint32 CustomExtendedCost::GetCustomCost(uint32 creatureId, uint32 itemId)
{
    QueryResult result = WorldDatabase.PQuery("SELECT CustomCost FROM npc_vendor WHERE entry = %u AND item = %u", creatureId, itemId);

    if (result)
        return result->Fetch()[0].GetUInt32();
    else
        return 0;
}

uint32 CustomExtendedCost::GetCustomValue(uint32 creatureId, uint32 itemId)
{
    QueryResult result = WorldDatabase.PQuery("SELECT CustomValue FROM npc_vendor WHERE entry = %u AND item = %u", creatureId, itemId);

    if (result)
        return result->Fetch()[0].GetUInt32();
    else
        return 0;
}

void CustomExtendedCost::SendMessage(Player* player, uint32 customCost, uint32 customValue, uint32 itemId)
{
    std::ostringstream msg;
    ItemTemplate const* item = sObjectMgr->GetItemTemplate(itemId);

    switch (customCost)
    {
    case CUSTOM_COST_HONOR:
        msg << "[" << item->Name1 << "]" << " requires [Honor Points]: " << customValue << ".";
        break;
    case CUSTOM_COST_ARENA:
        msg << "[" << item->Name1 << "]" << " requires [Arena Points]: " << customValue << ".";
        break;
    case CUSTOM_COST_ITEM:
        msg << "[" << item->Name1 << "]" << " requires [Item]: " << sObjectMgr->GetItemTemplate(customValue)->Name1 << ".";
        break;
    }

    ChatHandler(player->GetSession()).SendSysMessage(msg.str().c_str());
    player->GetSession()->SendNotification(msg.str().c_str());
}

bool CustomExtendedCost::IsEnabled(uint32 creatureId, uint32 itemId)
{
    if (GetCustomCost(creatureId, itemId) != CUSTOM_COST_DISABLED)
        return true;
    else
        return false;
}

void CustomExtendedCost::Initialize(Player* player, uint32 creatureId, uint32 itemId)
{
    uint32 customCost = sCustomExtendedCost->GetCustomCost(creatureId, itemId);
    uint32 customValue = sCustomExtendedCost->GetCustomValue(creatureId, itemId);

    switch (customCost)
    {
    case CUSTOM_COST_HONOR:
        if (player->GetHonorPoints() < customValue)
            sCustomExtendedCost->SendMessage(player, CUSTOM_COST_HONOR, customCost, customValue, itemId);
        else
            player->ModifyHonorPoints(-customValue);
        break;

    case CUSTOM_COST_ARENA:
        if (player->GetArenaPoints() < customValue)
            sCustomExtendedCost->SendMessage(player, CUSTOM_COST_ARENA, customCost, customValue, itemId);
        else
            player->ModifyArenaPoints(-customValue);
        break;

    case CUSTOM_COST_ITEM:
        if (!player->HasItemCount(customValue, 1))
            sCustomExtendedCost->SendMessage(player, CUSTOM_COST_ITEM, customCost, customValue, itemId);
        else
            player->DestroyItemCount(customValue, 1, true);
        break;
    }
}
