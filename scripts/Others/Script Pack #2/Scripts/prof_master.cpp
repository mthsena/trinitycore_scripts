/*
© Cemak 2012*/
class prof_master : public CreatureScript
{
public:
    prof_master() : CreatureScript("prof_master") { }

	void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
    {
        if (PlayerAlreadyHasNineProfessions(pPlayer) && !IsSecondarySkill(skill)){
        char wh[255];
        sprintf(wh, "АТАТА по рукам вы уже выучили %i професии!", sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL));
            pCreature->MonsterWhisper(wh, pPlayer->GetGUID(), true);
		}
        else
        {
            if (!LearnAllRecipesInProfession(pPlayer, skill))
                pCreature->MonsterWhisper("Ошибка!", pPlayer->GetGUID(), true);
        }
    }
	
	 bool IsSecondarySkill(SkillType skill) const
    {
        return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
    }
	
	 bool PlayerAlreadyHasNineProfessions(const Player *pPlayer) const
    {
        uint32 skillCount = 0;

        if (pPlayer->HasSkill(SKILL_MINING))
            skillCount++;
        if (pPlayer->HasSkill(SKILL_SKINNING))
            skillCount++;
        if (pPlayer->HasSkill(SKILL_HERBALISM))
            skillCount++;

        if (skillCount >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
            return true;

        for (uint32 i = 0; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
            if (!SkillInfo)
                continue;

            if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                continue;

            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                continue;

            const uint32 skillID = SkillInfo->id;
            if (pPlayer->HasSkill(skillID))
                skillCount++;

            if (skillCount >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
                return true;
        }

        return false;
    }

    bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
    {
        ChatHandler handler(pPlayer);
        char* skill_name;

        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
        skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

        if (!SkillInfo)
        {
            sLog->outError("Teleport NPC: received non-valid skill ID (LearnAllRecipesInProfession)");
            return false;
        }

        LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

        uint16 maxLevel = pPlayer->GetPureMaxSkillValue(SkillInfo->id);
        pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), maxLevel, maxLevel);
        handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);
        
        return true;
    }
    // See "static void HandleLearnSkillRecipesHelper(Player* player,uint32 skill_id)" from cs_learn.cpp 
    void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
    {
        uint32 classmask = player->getClassMask();

        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;

            // wrong skill
            if (skillLine->skillId != skill_id)
                continue;

            // not high rank
            if (skillLine->forward_spellid)
                continue;

            // skip racial skills
            if (skillLine->racemask != 0)
                continue;

            // skip wrong class skills
            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;

            SpellEntry const* spellInfo = sSpellStore.LookupEntry(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
                continue;

            player->learnSpell(skillLine->spellId, false);
        }
    }
	
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
			
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Алхимия", GOSSIP_SENDER_MAIN, 44);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Кузнечное дело", GOSSIP_SENDER_MAIN, 45);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Кожевничество", GOSSIP_SENDER_MAIN, 46);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Портняжное дело", GOSSIP_SENDER_MAIN, 47);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Инженерное дело", GOSSIP_SENDER_MAIN, 48);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Наложение чар", GOSSIP_SENDER_MAIN, 49);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ювелирное дело", GOSSIP_SENDER_MAIN, 50);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Начертание", GOSSIP_SENDER_MAIN, 51);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Снятие шкур", GOSSIP_SENDER_MAIN, 52);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Травничество", GOSSIP_SENDER_MAIN, 53);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Кулинария", GOSSIP_SENDER_MAIN, 54);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Первая помощь", GOSSIP_SENDER_MAIN, 55);
				
				pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
	
void SendDefaultMenu(Player *pPlayer, Creature *pCreature, uint32 action)
    {
        switch(action)
      {
	    case 44:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_ALCHEMY);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 45:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_BLACKSMITHING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 46:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_LEATHERWORKING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 47:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_TAILORING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 48:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_ENGINERING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 49:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_ENCHANTING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 50:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_JEWELCRAFTING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 51:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_INSCRIPTION);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 52:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_SKINNING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 53:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_HERBALISM);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 54:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_COOKING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 55:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_FIRST_AID);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            
	   }
	 }
			
       bool OnGossipSelect(Player *pPlayer, Creature *_Creature, uint32 sender, uint32 action )
        {
                if (sender == GOSSIP_SENDER_MAIN)
                        SendDefaultMenu(pPlayer, _Creature, action);

                return true;

        }
	
};

void AddSC_prof_master()
{
    new prof_master;
}