#include "Language.h"
#include "Chat.h"

#define DEFAULT_MESSAGE 907

class NPC_Profession : public CreatureScript
{
public:
    NPC_Profession() : CreatureScript("NPC_Profession") { }

    bool PlayerAlreadyHasTwoProfessions(Player* player)
    {
        uint32 skillCount = 0;

        if (player->HasSkill(SKILL_MINING))
            skillCount++;
        if (player->HasSkill(SKILL_SKINNING))
            skillCount++;
        if (player->HasSkill(SKILL_HERBALISM))
            skillCount++;

        if (skillCount >= 2)
            return true;

        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
            if (!SkillInfo)
                continue;

            if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                continue;

            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                continue;

            uint32 skillID = SkillInfo->id;
            if (player->HasSkill(skillID))
                skillCount++;

            if (skillCount >= 2)
                return true;
        }

        return false;
    }

    bool LearnAllRecipesInProfession(Player* player, SkillType skill)
    {
        char* skill_name;

        SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(skill);
        skill_name = SkillInfo->name[ChatHandler(player->GetSession()).GetSessionDbcLocale()];

        if (!SkillInfo)
            return false;

        LearnSkillRecipesHelper(player, SkillInfo->id);

        player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 450, 450);
        ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);

        return true;
    }

    void LearnSkillRecipesHelper(Player* player, uint32 skill_id)
    {
        uint32 classmask = player->getClassMask();

        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;

            if (skillLine->skillId != skill_id)
                continue;

            if (skillLine->forward_spellid)
                continue;

            if (skillLine->racemask != 0)
                continue;

            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
                continue;

            player->LearnSpell(skillLine->spellId, false);
        }
    }

    bool IsSecondarySkill(SkillType skill)
    {
        return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
    }

    void CompleteLearnProfession(Player* player, Creature* creature, SkillType skill)
    {
        if (PlayerAlreadyHasTwoProfessions(player) && !IsSecondarySkill(skill))
            ChatHandler(player->GetSession()).PSendSysMessage("Failure! You already have two professions.");
        else
        {
            if (!LearnAllRecipesInProfession(player, skill))
                ChatHandler(player->GetSession()).PSendSysMessage("Failure! Internal.");
        }
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Alchemy", GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmithing", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Leatherworking", GOSSIP_SENDER_MAIN, 3);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tailoring", GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Engineering", GOSSIP_SENDER_MAIN, 5);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Enchanting", GOSSIP_SENDER_MAIN, 6);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewelcrafting", GOSSIP_SENDER_MAIN, 7);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Inscription", GOSSIP_SENDER_MAIN, 8);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Herbalism", GOSSIP_SENDER_MAIN, 9);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Skinning", GOSSIP_SENDER_MAIN, 10);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Mining", GOSSIP_SENDER_MAIN, 11);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Cooking", GOSSIP_SENDER_MAIN, 12);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "First Aid", GOSSIP_SENDER_MAIN, 13);
        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (actions)
        {
        case 1:
            if (player->HasSkill(SKILL_ALCHEMY))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_ALCHEMY);
            CloseGossipMenuFor(player);
            break;

        case 2:
            if (player->HasSkill(SKILL_BLACKSMITHING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_BLACKSMITHING);
            CloseGossipMenuFor(player);
            break;

        case 3:
            if (player->HasSkill(SKILL_LEATHERWORKING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_LEATHERWORKING);
            CloseGossipMenuFor(player);
            break;

        case 4:
            if (player->HasSkill(SKILL_TAILORING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_TAILORING);
            player->PlayerTalkClass->SendCloseGossip();
            break;

        case 5:
            if (player->HasSkill(SKILL_ENGINEERING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_ENGINEERING);
            CloseGossipMenuFor(player);
            break;

        case 6:
            if (player->HasSkill(SKILL_ENCHANTING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_ENCHANTING);
            CloseGossipMenuFor(player);
            break;

        case 7:
            if (player->HasSkill(SKILL_JEWELCRAFTING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_JEWELCRAFTING);
            CloseGossipMenuFor(player);
            break;

        case 8:
            if (player->HasSkill(SKILL_INSCRIPTION))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_INSCRIPTION);
            CloseGossipMenuFor(player);
            break;

        case 9:
            if (player->HasSkill(SKILL_HERBALISM))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_HERBALISM);
            CloseGossipMenuFor(player);
            break;

        case 10:
            if (player->HasSkill(SKILL_SKINNING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_SKINNING);
            CloseGossipMenuFor(player);
            break;

        case 11:
            if (player->HasSkill(SKILL_MINING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_MINING);
            CloseGossipMenuFor(player);
            break;

        case 12:
            if (player->HasSkill(SKILL_COOKING))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_COOKING);
            CloseGossipMenuFor(player);
            break;

        case 13:
            if (player->HasSkill(SKILL_FIRST_AID))
            {
                CloseGossipMenuFor(player);
                return false;
            }

            CompleteLearnProfession(player, creature, SKILL_FIRST_AID);
            CloseGossipMenuFor(player);;
            break;
        }

        return true;
    }
};

void AddSC_NPC_Profession()
{
    new NPC_Profession();
}