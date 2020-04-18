#include "ScriptPCH.h"
struct accepted_stat_format {uint32 stat_type; char* stat_name; int32 base_stat_change; };

// ########################################################################################
//  Reforging config
// ########################################################################################
static const uint32 tokenEntry      = 65717;    // token entry
static const uint8 maxTokenAmount   = 3;        // max token cost (multiplies the max stat amount also)
static const uint8 maxReforges      = 3;        // maximum reforges for one item
static const bool send_cache_packets = true;    // change player cache?

static const accepted_stat_format accepted_stat_types[] =
{
    // See ItemPrototype.h for ItemModType definitions. You can add more rows for more stats.
    {ITEM_MOD_HEALTH,       "Health",           7500},
    {ITEM_MOD_STRENGTH,     "Strength",         900},
    {ITEM_MOD_INTELLECT,    "Intellect",        900},
    {ITEM_MOD_AGILITY,      "Agility",          300},
    {ITEM_MOD_SPIRIT,       "Spirit",           1250},
    {ITEM_MOD_STAMINA,      "Stamina",          1000},
    {ITEM_MOD_ATTACK_POWER, "Attack power",     1250},
    {ITEM_MOD_SPELL_POWER,  "Spell power",      1000},
};

// ########################################################################################

static const uint32 accepted_stat_types_max = sizeof(accepted_stat_types) / sizeof(accepted_stat_format);
struct playerItems_format {uint32 Entry, lowGUID;};
static UNORDERED_MAP<uint32, std::vector<playerItems_format> > playerItems;

static const void SendReforgePackets(Player* player)
{
    if(!send_cache_packets)
        return;

    uint32 pGUID = player->GetGUIDLow();
    if(playerItems.find(pGUID) == playerItems.end())
        return;

    for (std::vector<playerItems_format>::iterator it = playerItems[pGUID].begin(); it != playerItems[pGUID].end(); it++)
    {
        // See how enchanthing is done
        // Update player cache (self only) pure visual.
        // HandleItemQuerySingleOpcode copy paste:
        const ItemTemplate* proto = sObjectMgr->GetItemTemplate(it->Entry);
        std::string Name        = proto->Name1;
        std::string Description = proto->Description;
        int loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
        if (loc_idx >= 0)
        {
            if (ItemLocale const* il = sObjectMgr->GetItemLocale(proto->ItemId))
            {
                ObjectMgr::GetLocaleString(il->Name, loc_idx, Name);
                ObjectMgr::GetLocaleString(il->Description, loc_idx, Description);
            }
        }
        WorldPacket data(SMSG_ITEM_QUERY_SINGLE_RESPONSE, 600);
        data << proto->ItemId;
        data << proto->Class;
        data << proto->SubClass;
        data << int32(proto->SoundOverrideSubclass);
        data << Name;
        data << uint8(0x00);
        data << uint8(0x00);
        data << uint8(0x00);
        data << proto->DisplayInfoID;
        data << proto->Quality;
        data << proto->Flags;
        data << proto->Flags2;
        data << proto->BuyPrice;
        data << proto->SellPrice;
        data << proto->InventoryType;
        data << proto->AllowableClass;
        data << proto->AllowableRace;
        data << proto->ItemLevel;
        data << proto->RequiredLevel;
        data << proto->RequiredSkill;
        data << proto->RequiredSkillRank;
        data << proto->RequiredSpell;
        data << proto->RequiredHonorRank;
        data << proto->RequiredCityRank;
        data << proto->RequiredReputationFaction;
        data << proto->RequiredReputationRank;
        data << int32(proto->MaxCount);
        data << int32(proto->Stackable);
        data << proto->ContainerSlots;
        data << proto->StatsCount;
        for (uint32 i = 0; i < proto->StatsCount; ++i)
        {
            data << proto->ItemStat[i].ItemStatType;
            if(sObjectMgr->_itemFakeStatStore[it->lowGUID].find(i) != sObjectMgr->_itemFakeStatStore[it->lowGUID].end())
                data << proto->ItemStat[i].ItemStatValue + sObjectMgr->_itemFakeStatStore[it->lowGUID][i];
            else
                data << proto->ItemStat[i].ItemStatValue;
        }
        data << proto->ScalingStatDistribution;
        data << proto->ScalingStatValue;
        for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES; ++i)
        {
            data << proto->Damage[i].DamageMin;
            data << proto->Damage[i].DamageMax;
            data << proto->Damage[i].DamageType;
        }
        data << proto->Armor;
        data << proto->HolyRes;
        data << proto->FireRes;
        data << proto->NatureRes;
        data << proto->FrostRes;
        data << proto->ShadowRes;
        data << proto->ArcaneRes;
        data << proto->Delay;
        data << proto->AmmoType;
        data << proto->RangedModRange;
        for (int s = 0; s < MAX_ITEM_PROTO_SPELLS; ++s)
        {
            SpellInfo const* spell = sSpellMgr->GetSpellInfo(proto->Spells[s].SpellId);
            if (spell)
            {
                bool db_data = proto->Spells[s].SpellCooldown >= 0 || proto->Spells[s].SpellCategoryCooldown >= 0;
                data << proto->Spells[s].SpellId;
                data << proto->Spells[s].SpellTrigger;
                data << uint32(-abs(proto->Spells[s].SpellCharges));
                if (db_data)
                {
                    data << uint32(proto->Spells[s].SpellCooldown);
                    data << uint32(proto->Spells[s].SpellCategory);
                    data << uint32(proto->Spells[s].SpellCategoryCooldown);
                }
                else
                {
                    data << uint32(spell->RecoveryTime);
                    data << uint32(spell->Category);
                    data << uint32(spell->CategoryRecoveryTime);
                }
            }
            else
            {
                data << uint32(0);
                data << uint32(0);
                data << uint32(0);
                data << uint32(-1);
                data << uint32(0);
                data << uint32(-1);
            }
        }
        data << proto->Bonding;
        data << Description;
        data << proto->PageText;
        data << proto->LanguageID;
        data << proto->PageMaterial;
        data << proto->StartQuest;
        data << proto->LockID;
        data << int32(proto->Material);
        data << proto->Sheath;
        data << proto->RandomProperty;
        data << proto->RandomSuffix;
        data << proto->Block;
        data << proto->ItemSet;
        data << proto->MaxDurability;
        data << proto->Area;
        data << proto->Map;
        data << proto->BagFamily;
        data << proto->TotemCategory;
        for (int s = 0; s < MAX_ITEM_PROTO_SOCKETS; ++s)
        {
            data << proto->Socket[s].Color;
            data << proto->Socket[s].Content;
        }
        data << proto->socketBonus;
        data << proto->GemProperties;
        data << proto->RequiredDisenchantSkill;
        data << proto->ArmorDamageModifier;
        data << proto->Duration;
        data << proto->ItemLimitCategory;
        data << proto->HolidayId;
        player->GetSession()->SendPacket(&data);
    }
}

class REFORGING_DATA_HANDLER : public PlayerScript
{
public:
    REFORGING_DATA_HANDLER() : PlayerScript("REFORGING_DATA_HANDLER")
    {
        // DB cleanup on startup
        CharacterDatabase.Execute("DELETE FROM custom_reforges WHERE NOT EXISTS (SELECT 1 FROM item_instance WHERE item_instance.guid = custom_reforges.iGUID)");
    }

    // Called when a player logs out.
    void OnLogout(Player* player)
    {
        DeleteSavedReforges(player->GetGUIDLow()); // delete stored reforges from the player (not DB)
    }

    void OnLogin(Player* player)
    {
        uint32 pGUID = player->GetGUIDLow();

        DeleteSavedReforges(pGUID); // delete saved reforges from the player before loading them
        QueryResult result = CharacterDatabase.PQuery("SELECT `iGUID`, `stat_count_id`, `stat_diff`, `Entry` FROM `custom_reforges` WHERE pGUID = %u and EXISTS (SELECT 1 FROM item_instance WHERE item_instance.guid = custom_reforges.iGUID)", pGUID);
        if (result)
        {
            UNORDERED_MAP<uint32, std::map<uint32, int32> > stat_temp_container; // iGUID <stat_count, stat_diff>
            std::set<uint32> sent_error_message;
            do
            {
                uint32 lowGUID = (*result)[0].GetUInt32();
                if(sObjectMgr->_itemFakeStatStore.find(lowGUID) != sObjectMgr->_itemFakeStatStore.end() && sObjectMgr->_itemFakeStatStore[lowGUID].size() >= maxReforges)
                {
                    if(sent_error_message.find(lowGUID) != sent_error_message.end())
                        continue;
                    sLog->outErrorDb("Too many reforges for item lowGUID %u, ignoring extra reforges.", lowGUID);
                    sent_error_message.insert(lowGUID);
                }
                else
                {
                    stat_temp_container[lowGUID][(*result)[1].GetUInt32()] = (*result)[2].GetInt32();
                    playerItems_format temp = {(*result)[3].GetUInt32(), lowGUID}; // temp var so we can insert our stuff
                    playerItems[pGUID].push_back(temp);
                }
            } while (result->NextRow());

            // apply stat changes for all reforged items equipped and save them to container
            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
            {
                if(Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    uint32 invGUID = invItem->GetGUIDLow();
                    if(stat_temp_container.find(invGUID) != stat_temp_container.end())
                    {
                        player->_ApplyItemMods(invItem, slot, false);
                        for(std::map<uint32, int32>::iterator stat_count_id = stat_temp_container[invGUID].begin(); stat_count_id != stat_temp_container[invGUID].end(); stat_count_id++)
                        {
                            sObjectMgr->_itemFakeStatStore[invGUID][stat_count_id->first] = stat_count_id->second;
                        }
                        player->_ApplyItemMods(invItem, slot, true);
                        stat_temp_container.erase(invGUID); // saved reforges for this item, delete from temp
                    }
                }
            }

            // save the rest of the player's reforges to the container if more exist
            if(!stat_temp_container.empty())
            {
                for(UNORDERED_MAP<uint32, std::map<uint32, int32> >::iterator iGUID = stat_temp_container.begin(); iGUID != stat_temp_container.end(); iGUID++)
                {
                    for(std::map<uint32, int32>::iterator stat_count_id = iGUID->second.begin(); stat_count_id != iGUID->second.end(); stat_count_id++)
                    {
                        sObjectMgr->_itemFakeStatStore[iGUID->first][stat_count_id->first] = stat_count_id->second;
                    }
                }
            }
        }

        SendReforgePackets(player);
    }

private:

    void DeleteSavedReforges(uint32 pGUID)
    {
        if(playerItems.find(pGUID) == playerItems.end())
            return; // Already empty!
        for (std::vector<playerItems_format>::iterator it = playerItems[pGUID].begin(); it != playerItems[pGUID].end(); it++)
        {
            if(sObjectMgr->_itemFakeStatStore.find(it->lowGUID) != sObjectMgr->_itemFakeStatStore.end())
                sObjectMgr->_itemFakeStatStore.erase(it->lowGUID);
        }
        playerItems.erase(pGUID);
    }
};

class REFORGER_NPC : public CreatureScript
{
public:
    REFORGER_NPC() : CreatureScript("REFORGER_NPC")
    {
        for(uint32 i = 0; i < accepted_stat_types_max; i++)
        {
            stat_format temp = {accepted_stat_types[i].stat_name, accepted_stat_types[i].base_stat_change};
            stat_types[accepted_stat_types[i].stat_type] = temp;
        }
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if(selectedItem.find(player->GetGUIDLow()) != selectedItem.end())
            selectedItem.erase(player->GetGUIDLow());

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Buy Reforge Tokens.", VENDOR, 0);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Select equipped item in slot:", MAIN_MENU, 0);
        for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
        {
            if(Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                if(IsReforgable(invItem, player))
                    if(char* slotname = GetSlotName(slot, player->GetSession()))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, slotname, SELECT_STAT_INCREASE, slot);
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Update menu", MAIN_MENU, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(sender)
        {
        case VENDOR: 
            player->GetSession()->SendListInventory(creature->GetGUID());
            break;
        case MAIN_MENU: OnGossipHello(player, creature); break;
        case SELECT_STAT_INCREASE:
            // action = slot
            if (Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, action))
            {
                if(IsReforgable(invItem, player))
                {
                    selectedItem[player->GetGUIDLow()] = invItem;
                    const ItemTemplate* proto = invItem->GetTemplate();
                    char label[250];

                    snprintf(label, 250, "Selected item:\n%s", invItem->GetTemplate()->Name1.c_str());
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, label, sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Select stat to increase:", sender, action);
                    bool hasfakestats = ((sObjectMgr->_itemFakeStatStore.find(invItem->GetGUIDLow()) != sObjectMgr->_itemFakeStatStore.end()) ? true : false);
                    for (uint32 i = 0; i < proto->StatsCount; ++i)
                    {
                        if(hasfakestats && sObjectMgr->_itemFakeStatStore[invItem->GetGUIDLow()].find(i) != sObjectMgr->_itemFakeStatStore[invItem->GetGUIDLow()].end())
                            continue; // already modded this stat, skip.
                        if(char* stat_name = GetStatName(proto->ItemStat[i].ItemStatType))
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, stat_name, SELECT_TOKEN_COST, i);
                    }
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back..", MAIN_MENU, 0);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else
                {
                    player->GetSession()->SendNotification("Item not reforgable");
                    OnGossipHello(player, creature);
                }
            }
            else
            {
                player->GetSession()->SendNotification("No item selected");
                OnGossipHello(player, creature);
            }
            break;
        case SELECT_TOKEN_COST:
            // action = stat_count_id
            {
                Item* invItem = selectedItem[player->GetGUIDLow()];
                if (invItem && invItem->IsInWorld() && IsReforgable(invItem, player))
                {
                    const ItemTemplate* proto = invItem->GetTemplate();
                    char label[250];
                    char popup[250];

                    snprintf(label, 250, "Selected item:\n%s", invItem->GetTemplate()->Name1.c_str());
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, label, sender, action);
                    snprintf(label, 250, "Selected stat: %s", stat_types[proto->ItemStat[action].ItemStatType].stat_name);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, label, sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Select amount to increase:", sender, action);
                    for (uint32 i = 1; i <= maxTokenAmount; ++i)
                    {
                        snprintf(label, 250, "Increase by %i for %u x %s", stat_types[proto->ItemStat[action].ItemStatType].stat_base_value*i, i, GetItemName(tokenEntry, player->GetSession()).c_str());
                        snprintf(popup, 250, "Are you sure?\nThe item is set untradeable and non-refundable\n\nCosts %u x %s", i, GetItemName(tokenEntry, player->GetSession()).c_str());
                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, label, i, action, popup, 0, false); // sender = token_count, action = stat_count_id
                    }
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back..", SELECT_STAT_INCREASE, invItem->GetSlot());
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else
                {
                    player->GetSession()->SendNotification("Invalid item selected");
                    OnGossipHello(player, creature);
                }
            }
            break;
        default: // Reforge
            // sender = token_count, action = stat_count_id
            {
                Item* invItem = selectedItem[player->GetGUIDLow()];
                if (invItem && invItem->IsInWorld() && IsReforgable(invItem, player))
                {
                    if(sender && sender <= maxTokenAmount)
                    {
                        if(player->HasItemCount(tokenEntry, sender))
                        {
                            player->DestroyItemCount(tokenEntry, sender, true);
                            UpdatePlayerReforgeStats(invItem, player, action, sender);
                        }
                        else
                        {
                            player->GetSession()->SendNotification("Not enough tokens");
                            OnGossipSelect(player, creature, SELECT_TOKEN_COST, action);
                            return true;
                        }
                    }
                    else
                        player->GetSession()->SendNotification("Invalid token count");
                }
                else
                    player->GetSession()->SendNotification("Invalid item selected");
                OnGossipHello(player, creature);
            }
        }
        return true;
    }

private:

    enum Senders
    {
        MAIN_MENU = GOSSIP_ACTION_INFO_DEF+1,
        SELECT_ITEM,
        SELECT_STAT_INCREASE,
        SELECT_TOKEN_COST,
	 VENDOR = GOSSIP_ACTION_INFO_DEF+2,
        REFORGE,
    };

    struct stat_format {char* stat_name; int32 stat_base_value; };
    UNORDERED_MAP<uint32, struct stat_format> stat_types;
    UNORDERED_MAP<uint32, Item*> selectedItem;

    char* GetStatName(uint32 stat_type)
    {
        if(stat_types.find(stat_type) != stat_types.end())
            return stat_types[stat_type].stat_name;
        return NULL;
    }

    char * GetSlotName(uint8 slot, WorldSession* session)
    {
        switch (slot)
        {
        case EQUIPMENT_SLOT_HEAD      : return "Head";
        case EQUIPMENT_SLOT_NECK      : return "Neck";
        case EQUIPMENT_SLOT_SHOULDERS : return "Shoulders";
        case EQUIPMENT_SLOT_BODY      : return "Shirt";
        case EQUIPMENT_SLOT_CHEST     : return "Chest";
        case EQUIPMENT_SLOT_WAIST     : return "Waist";
        case EQUIPMENT_SLOT_LEGS      : return "Legs";
        case EQUIPMENT_SLOT_FEET      : return "Feet";
        case EQUIPMENT_SLOT_WRISTS    : return "Wrists";
        case EQUIPMENT_SLOT_HANDS     : return "Hands";
        case EQUIPMENT_SLOT_FINGER1   : return "Right finger";
        case EQUIPMENT_SLOT_FINGER2   : return "left finger";
        case EQUIPMENT_SLOT_TRINKET1  : return "Right trinket";
        case EQUIPMENT_SLOT_TRINKET2  : return "Left trinket";
        case EQUIPMENT_SLOT_BACK      : return "Back";
        case EQUIPMENT_SLOT_MAINHAND  : return "Main hand";
        case EQUIPMENT_SLOT_OFFHAND   : return "Off hand";
        case EQUIPMENT_SLOT_RANGED    : return "Ranged";
        case EQUIPMENT_SLOT_TABARD    : return "Tabard";
        default: return NULL;
        }
    }

    std::string GetItemName(uint32 entry, WorldSession* session)
    {
        const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(entry);
        std::string name = itemTemplate->Name1;
        int loc_idx = session->GetSessionDbLocaleIndex();
        if (loc_idx >= 0)
            if (ItemLocale const* il = sObjectMgr->GetItemLocale(itemTemplate->ItemId))
                sObjectMgr->GetLocaleString(il->Name, loc_idx, name);
        return name;
    }

    bool IsReforgable(Item* invItem, Player* player)
    {
        if(invItem->IsEquipped() && invItem->GetOwnerGUID() == player->GetGUID())
        {
            if(sObjectMgr->_itemFakeStatStore.find(invItem->GetGUIDLow()) != sObjectMgr->_itemFakeStatStore.end())
                if(sObjectMgr->_itemFakeStatStore[invItem->GetGUIDLow()].size() >= maxReforges)
                    return false;
            const ItemTemplate* proto = invItem->GetTemplate();
            // block heirlooms necessary? probably. (their stats are handled differently)
            if(proto->Quality != ITEM_QUALITY_HEIRLOOM && proto->StatsCount > 0)
            {
                for (uint32 i = 0; i < proto->StatsCount; ++i)
                {
                    if(stat_types.find(proto->ItemStat[i].ItemStatType) == stat_types.end())
                        continue;
                    if(proto->ItemStat[i].ItemStatValue == 0)
                        continue;
                    if(sObjectMgr->_itemFakeStatStore.find(invItem->GetGUIDLow()) != sObjectMgr->_itemFakeStatStore.end())
                    {
                        if(sObjectMgr->_itemFakeStatStore[invItem->GetGUIDLow()].find(i) == sObjectMgr->_itemFakeStatStore[invItem->GetGUIDLow()].end())
                            return true; // found a stat that is not increased yet and is accepted by the script
                    }
                    else
                        return true; // the item is not reforged yet and a good stat was found
                }
            }
        }
        return false;
    }

    void UpdatePlayerReforgeStats(Item* invItem, Player* player, uint32 stat_count_id, uint32 token_count)
    {
        const ItemTemplate* proto = invItem->GetTemplate();
        uint32 stat_diff = stat_types[proto->ItemStat[stat_count_id].ItemStatType].stat_base_value * token_count;
        uint32 guidlow = invItem->GetGUIDLow();

        // non tradeable and refundable
        invItem->SetNotRefundable(player);
        invItem->SetBinding(true);

        // Update player stats
        player->_ApplyItemMods(invItem, invItem->GetSlot(), false);
        sObjectMgr->_itemFakeStatStore[guidlow][stat_count_id] = stat_diff; // save to container for item stats applying (used a lot)
        playerItems_format temp = {invItem->GetEntry(), guidlow};           // temp var so we can insert our stuff to playerItems_format
        playerItems[player->GetGUIDLow()].push_back(temp);                  // save entry and guid of the item so we can delete the item data on logout
        player->_ApplyItemMods(invItem, invItem->GetSlot(), true);

        // save to DB
        player->SaveToDB(); // save player to DB too, since if a crash comes by, he will get a free reforge and no token removing is saved.
        CharacterDatabase.PExecute("REPLACE INTO `custom_reforges` (`pGUID`, `Entry`, `iGUID`, `stat_count_id`, `stat_diff`) VALUES (%u, %u, %u, %u, %i)", player->GetGUIDLow(), invItem->GetEntry(), guidlow, stat_count_id, stat_diff);

        SendReforgePackets(player);
    }
};

void AddSC_REFORGER_NPC()
{
    new REFORGER_NPC;
    new REFORGING_DATA_HANDLER;
}
