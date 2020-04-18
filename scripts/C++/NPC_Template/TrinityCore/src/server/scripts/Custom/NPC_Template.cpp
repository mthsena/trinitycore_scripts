#include "NPC_Template.h"

void sTemplateNPC::LearnPlateMailSpells(Player* player)
{
    switch (player->getClass())
    {
    case CLASS_WARRIOR:
    case CLASS_PALADIN:
    case CLASS_DEATH_KNIGHT:
        player->LearnSpell(PLATE_MAIL, true);
        break;
    case CLASS_SHAMAN:
    case CLASS_HUNTER:
        player->LearnSpell(MAIL, true);
        break;
    default:
        break;
    }
}

void sTemplateNPC::ApplyBonus(Player* player, Item* item, EnchantmentSlot slot, uint32 bonusEntry)
{
    if (!item)
        return;

    if (!bonusEntry || bonusEntry == 0)
        return;

    player->ApplyEnchantment(item, slot, false);
    item->SetEnchantment(slot, bonusEntry, 0, 0);
    player->ApplyEnchantment(item, slot, true);
}

void sTemplateNPC::ApplyGlyph(Player* player, uint8 slot, uint32 glyphID)
{
    if (GlyphPropertiesEntry const* gp = sGlyphPropertiesStore.LookupEntry(glyphID))
    {
        if (uint32 oldGlyph = player->GetGlyph(slot))
        {
            player->RemoveAurasDueToSpell(sGlyphPropertiesStore.LookupEntry(oldGlyph)->SpellId);
            player->SetGlyph(slot, 0);
        }
        player->CastSpell(player, gp->SpellId, true);
        player->SetGlyph(slot, glyphID);
    }
}

void sTemplateNPC::LearnTemplateTalents(Player* player)
{
    for (TalentContainer::const_iterator itr = m_TalentContainer.begin(); itr != m_TalentContainer.end(); ++itr)
    {
        if ((*itr)->playerClass == GetClassString(player).c_str() && (*itr)->playerSpec == sTalentsSpec)
        {
            player->LearnSpell((*itr)->talentId, false);
            player->AddTalent((*itr)->talentId, player->GetActiveSpec(), true);
        }
    }
    player->SetFreeTalentPoints(0);
    player->SendTalentsInfoData(false);
}

void sTemplateNPC::LearnTemplateGlyphs(Player* player)
{
    for (GlyphContainer::const_iterator itr = m_GlyphContainer.begin(); itr != m_GlyphContainer.end(); ++itr)
    {
        if ((*itr)->playerClass == GetClassString(player).c_str() && (*itr)->playerSpec == sTalentsSpec)
            ApplyGlyph(player, (*itr)->slot, (*itr)->glyph);
    }
    player->SendTalentsInfoData(false);
}

void sTemplateNPC::EquipTemplateGear(Player* player)
{
    if (player->getRace() == RACE_HUMAN)
    {
        for (HumanGearContainer::const_iterator itr = m_HumanGearContainer.begin(); itr != m_HumanGearContainer.end(); ++itr)
        {
            if ((*itr)->playerClass == GetClassString(player).c_str() && (*itr)->playerSpec == sTalentsSpec)
            {
                player->EquipNewItem((*itr)->pos, (*itr)->itemEntry, true); // Equip the item and apply enchants and gems
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), PERM_ENCHANTMENT_SLOT, (*itr)->enchant);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT, (*itr)->socket1);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT_2, (*itr)->socket2);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT_3, (*itr)->socket3);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), BONUS_ENCHANTMENT_SLOT, (*itr)->bonusEnchant);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), PRISMATIC_ENCHANTMENT_SLOT, (*itr)->prismaticEnchant);
            }
        }
    }
    else if (player->GetTeam() == ALLIANCE && player->getRace() != RACE_HUMAN)
    {
        for (AllianceGearContainer::const_iterator itr = m_AllianceGearContainer.begin(); itr != m_AllianceGearContainer.end(); ++itr)
        {
            if ((*itr)->playerClass == GetClassString(player).c_str() && (*itr)->playerSpec == sTalentsSpec)
            {
                player->EquipNewItem((*itr)->pos, (*itr)->itemEntry, true); // Equip the item and apply enchants and gems
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), PERM_ENCHANTMENT_SLOT, (*itr)->enchant);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT, (*itr)->socket1);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT_2, (*itr)->socket2);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT_3, (*itr)->socket3);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), BONUS_ENCHANTMENT_SLOT, (*itr)->bonusEnchant);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), PRISMATIC_ENCHANTMENT_SLOT, (*itr)->prismaticEnchant);
            }
        }
    }
    else if (player->GetTeam() == HORDE)
    {
        for (HordeGearContainer::const_iterator itr = m_HordeGearContainer.begin(); itr != m_HordeGearContainer.end(); ++itr)
        {
            if ((*itr)->playerClass == GetClassString(player).c_str() && (*itr)->playerSpec == sTalentsSpec)
            {
                player->EquipNewItem((*itr)->pos, (*itr)->itemEntry, true); // Equip the item and apply enchants and gems
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), PERM_ENCHANTMENT_SLOT, (*itr)->enchant);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT, (*itr)->socket1);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT_2, (*itr)->socket2);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), SOCK_ENCHANTMENT_SLOT_3, (*itr)->socket3);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), BONUS_ENCHANTMENT_SLOT, (*itr)->bonusEnchant);
                ApplyBonus(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, (*itr)->pos), PRISMATIC_ENCHANTMENT_SLOT, (*itr)->prismaticEnchant);
            }
        }
    }
}

void sTemplateNPC::LoadTalentsContainer()
{
    for (TalentContainer::const_iterator itr = m_TalentContainer.begin(); itr != m_TalentContainer.end(); ++itr)
        delete *itr;

    m_TalentContainer.clear();

    uint32 oldMSTime = getMSTime();
    uint32 count = 0;

    QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec, talentId FROM template_npc_talents;");

    if (!result)
    {
        TC_LOG_INFO("server.worldserver", ">> Loaded 0 talent templates. DB table `template_npc_talents` is empty!");
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        TalentTemplate* pTalent = new TalentTemplate;

        pTalent->playerClass = fields[0].GetString();
        pTalent->playerSpec = fields[1].GetString();
        pTalent->talentId = fields[2].GetUInt32();

        m_TalentContainer.push_back(pTalent);
        ++count;
    } while (result->NextRow());
    TC_LOG_INFO("server.worldserver", ">> Loaded %u talent templates in %u ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

void sTemplateNPC::LoadGlyphsContainer()
{
    for (GlyphContainer::const_iterator itr = m_GlyphContainer.begin(); itr != m_GlyphContainer.end(); ++itr)
        delete *itr;

    m_GlyphContainer.clear();

    QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec, slot, glyph FROM template_npc_glyphs;");

    uint32 oldMSTime = getMSTime();
    uint32 count = 0;

    if (!result)
    {
        TC_LOG_INFO("server.worldserver", ">> Loaded 0 glyph templates. DB table `template_npc_glyphs` is empty!");
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        GlyphTemplate* pGlyph = new GlyphTemplate;

        pGlyph->playerClass = fields[0].GetString();
        pGlyph->playerSpec = fields[1].GetString();
        pGlyph->slot = fields[2].GetUInt8();
        pGlyph->glyph = fields[3].GetUInt32();

        m_GlyphContainer.push_back(pGlyph);
        ++count;
    } while (result->NextRow());
    TC_LOG_INFO("server.worldserver", ">> Loaded %u glyph templates in %u ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

void sTemplateNPC::LoadHumanGearContainer()
{
    for (HumanGearContainer::const_iterator itr = m_HumanGearContainer.begin(); itr != m_HumanGearContainer.end(); ++itr)
        delete *itr;

    m_HumanGearContainer.clear();

    QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec, pos, itemEntry, enchant, socket1, socket2, socket3, bonusEnchant, prismaticEnchant FROM template_npc_human;");

    uint32 oldMSTime = getMSTime();
    uint32 count = 0;

    if (!result)
    {
        TC_LOG_INFO("server.worldserver", ">> Loaded 0 'gear templates. DB table `template_npc_human` is empty!");
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        HumanGearTemplate* pItem = new HumanGearTemplate;

        pItem->playerClass = fields[0].GetString();
        pItem->playerSpec = fields[1].GetString();
        pItem->pos = fields[2].GetUInt8();
        pItem->itemEntry = fields[3].GetUInt32();
        pItem->enchant = fields[4].GetUInt32();
        pItem->socket1 = fields[5].GetUInt32();
        pItem->socket2 = fields[6].GetUInt32();
        pItem->socket3 = fields[7].GetUInt32();
        pItem->bonusEnchant = fields[8].GetUInt32();
        pItem->prismaticEnchant = fields[9].GetUInt32();

        m_HumanGearContainer.push_back(pItem);
        ++count;
    } while (result->NextRow());
    TC_LOG_INFO("server.worldserver", ">> Loaded %u gear templates for Humans in %u ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

void sTemplateNPC::LoadAllianceGearContainer()
{
    for (AllianceGearContainer::const_iterator itr = m_AllianceGearContainer.begin(); itr != m_AllianceGearContainer.end(); ++itr)
        delete *itr;

    m_AllianceGearContainer.clear();

    QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec, pos, itemEntry, enchant, socket1, socket2, socket3, bonusEnchant, prismaticEnchant FROM template_npc_alliance;");

    uint32 oldMSTime = getMSTime();
    uint32 count = 0;

    if (!result)
    {
        TC_LOG_INFO("server.worldserver", ">> Loaded 0 'gear templates. DB table `template_npc_alliance` is empty!");
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        AllianceGearTemplate* pItem = new AllianceGearTemplate;

        pItem->playerClass = fields[0].GetString();
        pItem->playerSpec = fields[1].GetString();
        pItem->pos = fields[2].GetUInt8();
        pItem->itemEntry = fields[3].GetUInt32();
        pItem->enchant = fields[4].GetUInt32();
        pItem->socket1 = fields[5].GetUInt32();
        pItem->socket2 = fields[6].GetUInt32();
        pItem->socket3 = fields[7].GetUInt32();
        pItem->bonusEnchant = fields[8].GetUInt32();
        pItem->prismaticEnchant = fields[9].GetUInt32();

        m_AllianceGearContainer.push_back(pItem);
        ++count;
    } while (result->NextRow());
    TC_LOG_INFO("server.worldserver", ">> Loaded %u gear templates for Alliances in %u ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

void sTemplateNPC::LoadHordeGearContainer()
{
    for (HordeGearContainer::const_iterator itr = m_HordeGearContainer.begin(); itr != m_HordeGearContainer.end(); ++itr)
        delete *itr;

    m_HordeGearContainer.clear();

    QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec, pos, itemEntry, enchant, socket1, socket2, socket3, bonusEnchant, prismaticEnchant FROM template_npc_horde;");

    uint32 oldMSTime = getMSTime();
    uint32 count = 0;

    if (!result)
    {
        TC_LOG_INFO("server.worldserver", ">> Loaded 0 'gear templates. DB table `template_npc_horde` is empty!");
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        HordeGearTemplate* pItem = new HordeGearTemplate;

        pItem->playerClass = fields[0].GetString();
        pItem->playerSpec = fields[1].GetString();
        pItem->pos = fields[2].GetUInt8();
        pItem->itemEntry = fields[3].GetUInt32();
        pItem->enchant = fields[4].GetUInt32();
        pItem->socket1 = fields[5].GetUInt32();
        pItem->socket2 = fields[6].GetUInt32();
        pItem->socket3 = fields[7].GetUInt32();
        pItem->bonusEnchant = fields[8].GetUInt32();
        pItem->prismaticEnchant = fields[9].GetUInt32();

        m_HordeGearContainer.push_back(pItem);
        ++count;
    } while (result->NextRow());
    TC_LOG_INFO("server.worldserver", ">> Loaded %u gear templates for Hordes in %u ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

std::string sTemplateNPC::GetClassString(Player* player)
{
    switch (player->getClass())
    {
    case CLASS_PRIEST:       return "Priest";      break;
    case CLASS_PALADIN:      return "Paladin";     break;
    case CLASS_WARRIOR:      return "Warrior";     break;
    case CLASS_MAGE:         return "Mage";        break;
    case CLASS_WARLOCK:      return "Warlock";     break;
    case CLASS_SHAMAN:       return "Shaman";      break;
    case CLASS_DRUID:        return "Druid";       break;
    case CLASS_HUNTER:       return "Hunter";      break;
    case CLASS_ROGUE:        return "Rogue";       break;
    case CLASS_DEATH_KNIGHT: return "DeathKnight"; break;
    default:
        break;
    }
    return "Unknown"; // Fix warning, this should never happen
}

bool sTemplateNPC::OverwriteTemplate(Player* player, std::string& playerSpecStr)
{
    // Delete old talent and glyph templates before extracting new ones
    CharacterDatabase.PExecute("DELETE FROM template_npc_talents WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());
    CharacterDatabase.PExecute("DELETE FROM template_npc_glyphs WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());

    // Delete old gear templates before extracting new ones
    if (player->getRace() == RACE_HUMAN)
    {
        CharacterDatabase.PExecute("DELETE FROM template_npc_human WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());
        player->GetSession()->SendAreaTriggerMessage("Template successfuly created!");
        return false;
    }
    else if (player->GetTeam() == ALLIANCE && player->getRace() != RACE_HUMAN)
    {
        CharacterDatabase.PExecute("DELETE FROM template_npc_alliance WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());
        player->GetSession()->SendAreaTriggerMessage("Template successfuly created!");
        return false;
    }
    else if (player->GetTeam() == HORDE)
    {                                                                                                        // ????????????? sTemplateNpcMgr here??
        CharacterDatabase.PExecute("DELETE FROM template_npc_horde WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());
        player->GetSession()->SendAreaTriggerMessage("Template successfuly created!");
        return false;
    }
    return true;
}

void sTemplateNPC::ExtractGearTemplateToDB(Player* player, std::string& playerSpecStr)
{
    for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        Item* equippedItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);

        if (equippedItem)
        {
            if (player->getRace() == RACE_HUMAN)
            {
                CharacterDatabase.PExecute("INSERT INTO template_npc_human (`playerClass`, `playerSpec`, `pos`, `itemEntry`, `enchant`, `socket1`, `socket2`, `socket3`, `bonusEnchant`, `prismaticEnchant`) VALUES ('%s', '%s', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u');"
                    , GetClassString(player).c_str(), playerSpecStr.c_str(), equippedItem->GetSlot(), equippedItem->GetEntry(), equippedItem->GetEnchantmentId(PERM_ENCHANTMENT_SLOT),
                    equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT), equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2), equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3),
                    equippedItem->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT), equippedItem->GetEnchantmentId(PRISMATIC_ENCHANTMENT_SLOT));
            }
            else if (player->GetTeam() == ALLIANCE && player->getRace() != RACE_HUMAN)
            {
                CharacterDatabase.PExecute("INSERT INTO template_npc_alliance (`playerClass`, `playerSpec`, `pos`, `itemEntry`, `enchant`, `socket1`, `socket2`, `socket3`, `bonusEnchant`, `prismaticEnchant`) VALUES ('%s', '%s', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u');"
                    , GetClassString(player).c_str(), playerSpecStr.c_str(), equippedItem->GetSlot(), equippedItem->GetEntry(), equippedItem->GetEnchantmentId(PERM_ENCHANTMENT_SLOT),
                    equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT), equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2), equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3),
                    equippedItem->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT), equippedItem->GetEnchantmentId(PRISMATIC_ENCHANTMENT_SLOT));
            }
            else if (player->GetTeam() == HORDE)
            {
                CharacterDatabase.PExecute("INSERT INTO template_npc_horde (`playerClass`, `playerSpec`, `pos`, `itemEntry`, `enchant`, `socket1`, `socket2`, `socket3`, `bonusEnchant`, `prismaticEnchant`) VALUES ('%s', '%s', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u');"
                    , GetClassString(player).c_str(), playerSpecStr.c_str(), equippedItem->GetSlot(), equippedItem->GetEntry(), equippedItem->GetEnchantmentId(PERM_ENCHANTMENT_SLOT),
                    equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT), equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2), equippedItem->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3),
                    equippedItem->GetEnchantmentId(BONUS_ENCHANTMENT_SLOT), equippedItem->GetEnchantmentId(PRISMATIC_ENCHANTMENT_SLOT));
            }
        }
    }
}

void sTemplateNPC::ExtractTalentTemplateToDB(Player* player, std::string& playerSpecStr)
{
    QueryResult result = CharacterDatabase.PQuery("SELECT spell FROM character_talent WHERE guid = '%u' "
        "AND spec = '%u';", player->GetGUID(), player->GetActiveSpec());

    if (!result)
    {
        return;
    }
    else if (player->GetFreeTalentPoints() > 0)
    {
        player->GetSession()->SendAreaTriggerMessage("You have unspend talent points. Please spend all your talent points and re-extract the template.");
        return;
    }
    else
    {
        do
        {
            Field* fields = result->Fetch();
            uint32 spell = fields[0].GetUInt32();

            CharacterDatabase.PExecute("INSERT INTO template_npc_talents (playerClass, playerSpec, talentId) "
                "VALUES ('%s', '%s', '%u');", GetClassString(player).c_str(), playerSpecStr.c_str(), spell);
        } while (result->NextRow());
    }
}

void sTemplateNPC::ExtractGlyphsTemplateToDB(Player* player, std::string& playerSpecStr)
{
    QueryResult result = CharacterDatabase.PQuery("SELECT glyph1, glyph2, glyph3, glyph4, glyph5, glyph6 "
        "FROM character_glyphs WHERE guid = '%u' AND spec = '%u';", player->GetGUID(), player->GetActiveSpec());

    for (uint8 slot = 0; slot < MAX_GLYPH_SLOT_INDEX; ++slot)
    {
        if (!result)
        {
            player->GetSession()->SendAreaTriggerMessage("Get glyphs and re-extract the template!");
            continue;
        }

        Field* fields = result->Fetch();
        uint32 glyph1 = fields[0].GetUInt32();
        uint32 glyph2 = fields[1].GetUInt32();
        uint32 glyph3 = fields[2].GetUInt32();
        uint32 glyph4 = fields[3].GetUInt32();
        uint32 glyph5 = fields[4].GetUInt32();
        uint32 glyph6 = fields[5].GetUInt32();

        uint32 storedGlyph;

        switch (slot)
        {
        case 0:
            storedGlyph = glyph1;
            break;
        case 1:
            storedGlyph = glyph2;
            break;
        case 2:
            storedGlyph = glyph3;
            break;
        case 3:
            storedGlyph = glyph4;
            break;
        case 4:
            storedGlyph = glyph5;
            break;
        case 5:
            storedGlyph = glyph6;
            break;
        default:
            break;
        }

        CharacterDatabase.PExecute("INSERT INTO template_npc_glyphs (playerClass, playerSpec, slot, glyph) "
            "VALUES ('%s', '%s', '%u', '%u');", GetClassString(player).c_str(), playerSpecStr.c_str(), slot, storedGlyph);
    }
}

bool sTemplateNPC::CanEquipTemplate(Player* player, std::string& playerSpecStr)
{
    if (player->getRace() == RACE_HUMAN)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec FROM template_npc_human "
            "WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());

        if (!result)
            return false;
    }
    else if (player->GetTeam() == ALLIANCE && player->getRace() != RACE_HUMAN)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec FROM template_npc_alliance "
            "WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());

        if (!result)
            return false;
    }
    else if (player->GetTeam() == HORDE)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT playerClass, playerSpec FROM template_npc_horde "
            "WHERE playerClass = '%s' AND playerSpec = '%s';", GetClassString(player).c_str(), playerSpecStr.c_str());

        if (!result)
            return false;
    }
    return true;
}

class NPC_Template_Commands : public CommandScript
{
public:
    NPC_Template_Commands() : CommandScript("NPC_Template_Commands") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> createDeathKnightItemSetTable =
        {
            { "blood",             SEC_ADMINISTRATOR,         false,          &HandleCreateDeathKnightBloodItemSetCommand,       ""},
            { "frost",             SEC_ADMINISTRATOR,         false,          &HandleCreateDeathKnightFrostItemSetCommand,       ""},
            { "unholy",            SEC_ADMINISTRATOR,         false,          &HandleCreateDeathKnightUnholyItemSetCommand,      ""},
        };
        static std::vector<ChatCommand> createRogueItemSetTable =
        {
            { "assassination",     SEC_ADMINISTRATOR,         false,          &HandleCreateRogueAssassinationItemSetCommand,     ""},
            { "combat",            SEC_ADMINISTRATOR,         false,          &HandleCreateRogueCombatItemSetCommand,            ""},
            { "subtlety",          SEC_ADMINISTRATOR,         false,          &HandleCreateRogueSubtletyItemSetCommand,          ""},
        };
        static std::vector<ChatCommand> createHunterItemSetTable =
        {
            { "marksmanship",      SEC_ADMINISTRATOR,         false,          &HandleCreateHunterMarksmanshipItemSetCommand,     ""},
            { "beastmastery",      SEC_ADMINISTRATOR,         false,          &HandleCreateHunterBeastmasteryItemSetCommand,     ""},
            { "survival",          SEC_ADMINISTRATOR,         false,          &HandleCreateHunterSurvivalItemSetCommand,         ""},
        };
        static std::vector<ChatCommand> createDruidItemSetTable =
        {
            { "ballance",          SEC_ADMINISTRATOR,         false,          &HandleCreateDruidBallanceItemSetCommand,          ""},
            { "feral",             SEC_ADMINISTRATOR,         false,          &HandleCreateDruidFeralItemSetCommand,             ""},
            { "restoration",       SEC_ADMINISTRATOR,         false,          &HandleCreateDruidRestorationItemSetCommand,       ""},
        };
        static std::vector<ChatCommand> createShamanItemSetTable =
        {
            { "elemental",         SEC_ADMINISTRATOR,         false,          &HandleCreateShamanElementalItemSetCommand,        ""},
            { "enhancement",       SEC_ADMINISTRATOR,         false,          &HandleCreateShamanEnhancementItemSetCommand,      ""},
            { "restoration",       SEC_ADMINISTRATOR,         false,          &HandleCreateShamanRestorationItemSetCommand,      ""},
        };
        static std::vector<ChatCommand> createWarlockItemSetTable =
        {
            { "affliction",        SEC_ADMINISTRATOR,         false,          &HandleCreateWarlockAfflictionItemSetCommand,      ""},
            { "demonology",        SEC_ADMINISTRATOR,         false,          &HandleCreateWarlockDemonologyItemSetCommand,      ""},
            { "destruction",       SEC_ADMINISTRATOR,         false,          &HandleCreateWarlockDestructionItemSetCommand,     ""},
        };
        static std::vector<ChatCommand> createMageItemSetTable =
        {
            { "frost",             SEC_ADMINISTRATOR,         false,          &HandleCreateMageFrostItemSetCommand,              ""},
            { "fire",              SEC_ADMINISTRATOR,         false,          &HandleCreateMageFireItemSetCommand,               ""},
            { "arcane",            SEC_ADMINISTRATOR,         false,          &HandleCreateMageArcaneItemSetCommand,             ""},
        };
        static std::vector<ChatCommand> createWarriorItemSetTable =
        {
            { "arms",              SEC_ADMINISTRATOR,         false,          &HandleCreateWarriorArmsItemSetCommand,            ""},
            { "fury",              SEC_ADMINISTRATOR,         false,          &HandleCreateWarriorFuryItemSetCommand,            ""},
            { "protection",        SEC_ADMINISTRATOR,         false,          &HandleCreateWarriorProtectionItemSetCommand,      ""},
        };
        static std::vector<ChatCommand> createPaladinItemSetTable =
        {
            { "holy",              SEC_ADMINISTRATOR,         false,          &HandleCreatePaladinHolyItemSetCommand,            ""},
            { "protection",        SEC_ADMINISTRATOR,         false,          &HandleCreatePaladinProtectionItemSetCommand,      ""},
            { "retribution",       SEC_ADMINISTRATOR,         false,          &HandleCreatePaladinRetributionItemSetCommand,     ""},
        };

        static std::vector<ChatCommand> createPriestItemSetTable =
        {
            { "discipline",        SEC_ADMINISTRATOR,         false,          &HandleCreatePriestDisciplineItemSetCommand,       ""},
            { "shadow",            SEC_ADMINISTRATOR,         false,          &HandleCreatePriestShadowItemSetCommand,           ""},
            { "holy",              SEC_ADMINISTRATOR,         false,          &HandleCreatePriestHolyItemSetCommand,             ""},
        };
        static std::vector<ChatCommand> createItemSetCommandTable =
        {
            { "priest",            SEC_ADMINISTRATOR,          true,            NULL,         "", createPriestItemSetTable },
            { "paladin",           SEC_ADMINISTRATOR,          true,            NULL,         "", createPaladinItemSetTable },
            { "warrior",           SEC_ADMINISTRATOR,          true,            NULL,         "", createWarriorItemSetTable },
            { "mage",              SEC_ADMINISTRATOR,          true,            NULL,         "", createMageItemSetTable },
            { "warlock",           SEC_ADMINISTRATOR,          true,            NULL,         "", createWarlockItemSetTable },
            { "shaman",            SEC_ADMINISTRATOR,          true,            NULL,         "", createShamanItemSetTable },
            { "druid",             SEC_ADMINISTRATOR,          true,            NULL,         "", createDruidItemSetTable },
            { "hunter",            SEC_ADMINISTRATOR,          true,            NULL,         "", createHunterItemSetTable },
            { "rogue",             SEC_ADMINISTRATOR,          true,            NULL,         "", createRogueItemSetTable },
            { "deathknight",       SEC_ADMINISTRATOR,          true,            NULL,         "", createDeathKnightItemSetTable },
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "create",            SEC_ADMINISTRATOR,         true,             NULL,         "", createItemSetCommandTable },
        };
        return commandTable;
    }

    // DISCIPLINE PRIEST
    static bool HandleCreatePriestDisciplineItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (player->getClass() != CLASS_PRIEST)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a priest!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Discipline";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // SHADOW PRIEST
    static bool HandleCreatePriestShadowItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_PRIEST)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a priest!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Shadow";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // HOLY PRIEST
    static bool HandleCreatePriestHolyItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_PRIEST)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a priest!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Holy";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // HOLY PALADIN
    static bool HandleCreatePaladinHolyItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_PALADIN)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a paladin!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Holy";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // PROTECTION PALADIN
    static bool HandleCreatePaladinProtectionItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_PALADIN)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a paladin!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Protection";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // RETRIBUTION PALADIN
    static bool HandleCreatePaladinRetributionItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_PALADIN)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a paladin!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Retribution";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // FURY WARRIOR
    static bool HandleCreateWarriorFuryItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_WARRIOR)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a warrior!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Fury";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // ARMS WARRIOR
    static bool HandleCreateWarriorArmsItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_WARRIOR)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a warrior!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Arms";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // PROTECTION WARRIOR
    static bool HandleCreateWarriorProtectionItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_WARRIOR)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a warrior!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Protection";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // ARCANE MAGE
    static bool HandleCreateMageArcaneItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_MAGE)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a mage!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Arcane";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // FIRE MAGE
    static bool HandleCreateMageFireItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_MAGE)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a mage!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Fire";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // FROST MAGE
    static bool HandleCreateMageFrostItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_MAGE)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a mage!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Frost";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // AFFLICTION WARLOCK
    static bool HandleCreateWarlockAfflictionItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_WARLOCK)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a warlock!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Affliction";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // DEMONOLOGY WARLOCK
    static bool HandleCreateWarlockDemonologyItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_WARLOCK)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a warlock!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Demonology";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // DESTRUCTION WARLOCK
    static bool HandleCreateWarlockDestructionItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_WARLOCK)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a warlock!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Destruction";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // ELEMENTAL SHAMAN
    static bool HandleCreateShamanElementalItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_SHAMAN)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a shaman!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Elemental";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // ENHANCEMENT SHAMAN
    static bool HandleCreateShamanEnhancementItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_SHAMAN)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a shaman!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Enhancement";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // RESTORATION SHAMAN
    static bool HandleCreateShamanRestorationItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_SHAMAN)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a shaman!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Restoration";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // BALLANCE DRUID
    static bool HandleCreateDruidBallanceItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_DRUID)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a druid!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Ballance";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // FERAL DRUID
    static bool HandleCreateDruidFeralItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_DRUID)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a druid!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Feral";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // RESTORATION DRUID
    static bool HandleCreateDruidRestorationItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_DRUID)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a druid!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Restoration";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // MARKSMANSHIP HUNTER
    static bool HandleCreateHunterMarksmanshipItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_HUNTER)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a hunter!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Marksmanship";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // BEASTMASTERY HUNTER
    static bool HandleCreateHunterBeastmasteryItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_HUNTER)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a hunter!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Beastmastery";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // SURVIVAL HUNTER
    static bool HandleCreateHunterSurvivalItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_HUNTER)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a hunter!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Survival";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // ASSASSINATION ROGUE
    static bool HandleCreateRogueAssassinationItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_ROGUE)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a rogue!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Assassination";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // COMBAT ROGUE
    static bool HandleCreateRogueCombatItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_ROGUE)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a rogue!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Combat";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // SUBTLETY ROGUE
    static bool HandleCreateRogueSubtletyItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_ROGUE)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a rogue!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Subtlety";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // BLOOD DEATHKNIGHT
    static bool HandleCreateDeathKnightBloodItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_DEATH_KNIGHT)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a death knight!");
            return false;
        }
        player->SaveToDB();
        sTemplateNpcMgr->sTalentsSpec = "Blood";
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // FROST DEATHKNIGHT
    static bool HandleCreateDeathKnightFrostItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_DEATH_KNIGHT)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a death knight!");
            return false;
        }
        sTemplateNpcMgr->sTalentsSpec = "Frost";
        player->SaveToDB();
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }

    // UNHOLY DEATHKNIGHT
    static bool HandleCreateDeathKnightUnholyItemSetCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->getClass() != CLASS_DEATH_KNIGHT)
        {
            player->GetSession()->SendAreaTriggerMessage("You're not a death knight!");
            return false;
        }
        sTemplateNpcMgr->sTalentsSpec = "Unholy";
        player->SaveToDB();
        sTemplateNpcMgr->OverwriteTemplate(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGearTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractTalentTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        sTemplateNpcMgr->ExtractGlyphsTemplateToDB(player, sTemplateNpcMgr->sTalentsSpec);
        return true;
    }
};

class NPC_Template : public CreatureScript
{
public:
    NPC_Template() : CreatureScript("NPC_Template") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        switch (player->getClass())
        {
        case CLASS_PRIEST:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_wordfortitude:30|t|r Use Discipline Spec", GOSSIP_SENDER_MAIN, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_holybolt:30|t|r Use Holy Spec", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_shadowwordpain:30|t|r Use Shadow Spec", GOSSIP_SENDER_MAIN, 2);
        }
        break;
        case CLASS_PALADIN:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_holybolt:30|t|r Use Holy Spec", GOSSIP_SENDER_MAIN, 3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_devotionaura:30|t|r Use Protection Spec", GOSSIP_SENDER_MAIN, 4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_auraoflight:30|t|r Use Retribution Spec", GOSSIP_SENDER_MAIN, 5);
        }
        break;
        case CLASS_WARRIOR:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_warrior_innerrage:30|t|r Use Fury Spec", GOSSIP_SENDER_MAIN, 6);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_rogue_eviscerate:30|t|r Use Arms Spec", GOSSIP_SENDER_MAIN, 7);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_warrior_defensivestance:30|t|r Use Protection Spec", GOSSIP_SENDER_MAIN, 8);
        }
        break;
        case CLASS_MAGE:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_holy_magicalsentry:30|t|r Use Arcane Spec", GOSSIP_SENDER_MAIN, 9);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_fire_flamebolt:30|t|r Use Fire Spec", GOSSIP_SENDER_MAIN, 10);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_frost_frostbolt02:30|t|r Use Frost Spec", GOSSIP_SENDER_MAIN, 11);
        }
        break;
        case CLASS_WARLOCK:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_deathcoil:30|t|r Use Affliction Spec", GOSSIP_SENDER_MAIN, 12);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_metamorphosis:30|t|r Use Demonology Spec", GOSSIP_SENDER_MAIN, 13);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_shadow_rainoffire:30|t|r Use Destruction Spec", GOSSIP_SENDER_MAIN, 14);
        }
        break;
        case CLASS_SHAMAN:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_lightning:30|t|r Use Elemental Spec", GOSSIP_SENDER_MAIN, 15);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_lightningshield:30|t|r Use Enhancement Spec", GOSSIP_SENDER_MAIN, 16);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_magicimmunity:30|t|r Use Restoration Spec", GOSSIP_SENDER_MAIN, 17);
        }
        break;
        case CLASS_DRUID:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_starfall:30|t|r Use Ballance Spec", GOSSIP_SENDER_MAIN, 18);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_racial_bearform:30|t|r Use Feral Spec", GOSSIP_SENDER_MAIN, 19);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_nature_healingtouch:30|t|r Use Restoration Spec", GOSSIP_SENDER_MAIN, 20);
        }
        break;
        case CLASS_HUNTER:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_marksmanship:30|t|r Use Markmanship Spec", GOSSIP_SENDER_MAIN, 21);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_hunter_beasttaming:30|t|r Use Beastmastery Spec", GOSSIP_SENDER_MAIN, 22);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_Hunter_swiftstrike:30|t|r Use Survival Spec", GOSSIP_SENDER_MAIN, 23);
        }
        break;
        case CLASS_ROGUE:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_rogue_eviscerate:30|t|r Use Assasination Spec", GOSSIP_SENDER_MAIN, 24);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_backstab:30|t|r Use Combat Spec", GOSSIP_SENDER_MAIN, 25);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\ability_stealth:30|t|r Use Subtlety Spec", GOSSIP_SENDER_MAIN, 26);
        }
        break;
        case CLASS_DEATH_KNIGHT:
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_deathknight_bloodpresence:30|t|r Use Blood Spec", GOSSIP_SENDER_MAIN, 27);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_deathknight_frostpresence:30|t|r Use Frost Spec", GOSSIP_SENDER_MAIN, 28);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\spell_deathknight_unholypresence:30|t|r Use Unholy Spec", GOSSIP_SENDER_MAIN, 29);
        }
        break;
        }
        player->SEND_GOSSIP_MENU(60025, creature->GetGUID());
        return true;
    }

    void EquipFullTemplateGear(Player* player, std::string& playerSpecStr) // Merge
    {
        if (sTemplateNpcMgr->CanEquipTemplate(player, playerSpecStr) == false)
        {
            player->GetSession()->SendAreaTriggerMessage("There's no templates for %s specialization yet.", playerSpecStr.c_str());
            return;
        }

        // Don't let players to use Template feature while wearing some gear
        for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
        {
            if (Item* haveItemEquipped = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                if (haveItemEquipped)
                {
                    player->GetSession()->SendAreaTriggerMessage("You need to remove all your equipped items in order to use this feature!");
                    player->CLOSE_GOSSIP_MENU();
                    return;
                }
            }
        }

        // Don't let players to use Template feature after spending some talent points
        if (player->GetFreeTalentPoints() < 71)
        {
            player->GetSession()->SendAreaTriggerMessage("You have already spent some talent points. You need to reset your talents first!");
            player->CLOSE_GOSSIP_MENU();
            return;
        }

        sTemplateNpcMgr->LearnTemplateTalents(player);
        sTemplateNpcMgr->LearnTemplateGlyphs(player);
        sTemplateNpcMgr->EquipTemplateGear(player);
        sTemplateNpcMgr->LearnPlateMailSpells(player);

        LearnWeaponSkills(player);

        player->GetSession()->SendAreaTriggerMessage("Successfuly equipped %s %s template!", playerSpecStr.c_str(), sTemplateNpcMgr->GetClassString(player).c_str());
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        if (!player || !creature)
            return true;

        switch (uiAction)
        {
        case 0: // Use Discipline Priest Spec
            sTemplateNpcMgr->sTalentsSpec = "Discipline";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 1: // Use Holy Priest Spec
            sTemplateNpcMgr->sTalentsSpec = "Holy";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 2: // Use Shadow Priest Spec
            sTemplateNpcMgr->sTalentsSpec = "Shadow";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 3: // Use Holy Paladin Spec
            sTemplateNpcMgr->sTalentsSpec = "Holy";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 4: // Use Protection Paladin Spec
            sTemplateNpcMgr->sTalentsSpec = "Protection";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 5: // Use Retribution Paladin Spec
            sTemplateNpcMgr->sTalentsSpec = "Retribution";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 6: // Use Fury Warrior Spec
            sTemplateNpcMgr->sTalentsSpec = "Fury";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 7: // Use Arms Warrior Spec
            sTemplateNpcMgr->sTalentsSpec = "Arms";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 8: // Use Protection Warrior Spec
            sTemplateNpcMgr->sTalentsSpec = "Protection";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 9: // Use Arcane Mage Spec
            sTemplateNpcMgr->sTalentsSpec = "Arcane";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 10: // Use Fire Mage Spec
            sTemplateNpcMgr->sTalentsSpec = "Fire";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 11: // Use Frost Mage Spec
            sTemplateNpcMgr->sTalentsSpec = "Frost";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 12: // Use Affliction Warlock Spec
            sTemplateNpcMgr->sTalentsSpec = "Affliction";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 13: // Use Demonology Warlock Spec
            sTemplateNpcMgr->sTalentsSpec = "Demonology";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 14: // Use Destruction Warlock Spec
            sTemplateNpcMgr->sTalentsSpec = "Destruction";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 15: // Use Elemental Shaman Spec
            sTemplateNpcMgr->sTalentsSpec = "Elemental";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 16: // Use Enhancement Shaman Spec
            sTemplateNpcMgr->sTalentsSpec = "Enhancement";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 17: // Use Restoration Shaman Spec
            sTemplateNpcMgr->sTalentsSpec = "Restoration";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 18: // Use Ballance Druid Spec
            sTemplateNpcMgr->sTalentsSpec = "Ballance";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 19: // Use Feral Druid Spec
            sTemplateNpcMgr->sTalentsSpec = "Feral";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 20: // Use Restoration Druid Spec
            sTemplateNpcMgr->sTalentsSpec = "Restoration";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 21: // Use Marksmanship Hunter Spec
            sTemplateNpcMgr->sTalentsSpec = "Marksmanship";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 22: // Use Beastmastery Hunter Spec
            sTemplateNpcMgr->sTalentsSpec = "Beastmastery";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 23: // Use Survival Hunter Spec
            sTemplateNpcMgr->sTalentsSpec = "Survival";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 24: // Use Assassination Rogue Spec
            sTemplateNpcMgr->sTalentsSpec = "Assassination";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 25: // Use Combat Rogue Spec
            sTemplateNpcMgr->sTalentsSpec = "Combat";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 26: // Use Subtlety Rogue Spec
            sTemplateNpcMgr->sTalentsSpec = "Subtlety";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 27: // Use Blood DK Spec
            sTemplateNpcMgr->sTalentsSpec = "Blood";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 28: // Use Frost DK Spec
            sTemplateNpcMgr->sTalentsSpec = "Frost";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;

        case 29: // Use Unholy DK Spec
            sTemplateNpcMgr->sTalentsSpec = "Unholy";
            EquipFullTemplateGear(player, sTemplateNpcMgr->sTalentsSpec);
            player->CLOSE_GOSSIP_MENU();
            break;
        default: // Just in case
            player->GetSession()->SendAreaTriggerMessage("Something went wrong in the code. Please contact the administrator.");
            break;
        }
        player->UpdateSkillsForLevel();
        return true;
    }
};

void AddSC_NPC_Template()
{
    new NPC_Template_Commands();
    new NPC_Template();
}
