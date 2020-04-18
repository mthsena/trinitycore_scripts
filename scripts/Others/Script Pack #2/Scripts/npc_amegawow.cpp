/* https://bitbucket.org/cemak/amegawow/
© Cemak 2011*/

#include "ScriptPCH.h"
#include "Config.h"

class npc_amegawow : public CreatureScript
{
public:
    npc_amegawow() : CreatureScript("npc_amegawow") { }

	void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
    {
        if (PlayerAlreadyHasNineProfessions(pPlayer) && !IsSecondarySkill(skill))
            pCreature->MonsterWhisper("Вы уже выучили 3 професии!", pPlayer->GetGUID());
        else
        {
            if (!LearnAllRecipesInProfession(pPlayer, skill))
                pCreature->MonsterWhisper("Ошибка!", pPlayer->GetGUID());
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

        if (skillCount >= 3)
            return true;

        for (uint32 i = 2; i < sSkillLineStore.GetNumRows(); ++i)
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

            if (skillCount >= 3)
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

        pCreature->MonsterWhisper("Добро пожаловать на WoWCircle ! ", pPlayer->GetGUID(), false);
		
		pPlayer->ADD_GOSSIP_ITEM(0, "Как начать играть ?", GOSSIP_SENDER_MAIN, 6); //как начать
		//pPlayer->ADD_GOSSIP_ITEM(0, "Как мне зарегистрироваться на Озеро Ледяных Оков?", GOSSIP_SENDER_MAIN, 46);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка Сумок"   , GOSSIP_SENDER_MAIN, 2); //Сумки
		
		/*if (pPlayer->GetSession()->GetSecurity() >= 1)
		{
		pCreature->MonsterWhisper("Вы зашли в меню для Випов, выбирайте опции", pPlayer->GetGUID(), false);
		pPlayer->ADD_GOSSIP_ITEM(7, "[Вип]Меню БГ", GOSSIP_SENDER_MAIN, 36);
		pPlayer->ADD_GOSSIP_ITEM(7, "[Вип]Аннонсы Меню", GOSSIP_SENDER_MAIN, 37);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Вип]Купить Призовые жетоны Хмельного фестиваля 200 штук", GOSSIP_SENDER_MAIN, 38);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Вип]Купить Печати Чемпиона 150 штук", GOSSIP_SENDER_MAIN, 39);
		} else { pCreature->MonsterWhisper("Вы не Вип", pPlayer->GetGUID()); }*/
		
		if ((pPlayer->getClass() == CLASS_MAGE)){
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на мага"  , GOSSIP_SENDER_MAIN, 1); //Сет на мага a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Мага(Крита)", GOSSIP_SENDER_MAIN, 27);
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Мага(Скорость)", GOSSIP_SENDER_MAIN, 29);
			 }else if ((pPlayer->getClass() == CLASS_PALADIN))
           {
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Паладина (Возмездие)", GOSSIP_SENDER_MAIN, 4); //Сет на пала дд a8
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Паладина (Свет)", GOSSIP_SENDER_MAIN, 7); //Сет на холи пала a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Паладина (Возмездие)", GOSSIP_SENDER_MAIN, 26);
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Паладина (Свет)", GOSSIP_SENDER_MAIN, 25);
			  
			  
		   }else if ((pPlayer->getClass() == CLASS_HUNTER))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Охотника", GOSSIP_SENDER_MAIN, 8); //Нонсет Сет на ханта a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Охотника", GOSSIP_SENDER_MAIN, 35);
		   }else if ((pPlayer->getClass() == CLASS_DRUID))
           {
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Друида (Исцеление)", GOSSIP_SENDER_MAIN, 9); //Сет на друида хила a8
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Друида (Сила зверя)", GOSSIP_SENDER_MAIN, 10); //Сет на друида дд a8
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Друида (Баланс)", GOSSIP_SENDER_MAIN, 11); //Сет на друида рдд a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Друида (Баланс)", GOSSIP_SENDER_MAIN, 30);
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Друида (Сила зверя)", GOSSIP_SENDER_MAIN, 32);
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Друида(Исцеление)", GOSSIP_SENDER_MAIN, 31);
			  
		   }else if ((pPlayer->getClass() == CLASS_WARRIOR))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Война", GOSSIP_SENDER_MAIN, 12); //Сет на вара a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Война", GOSSIP_SENDER_MAIN, 26);
			  
		   }else if ((pPlayer->getClass() == CLASS_WARLOCK))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Чернокнижника", GOSSIP_SENDER_MAIN, 13); //Сет на лока a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Чернокнижника (Крита)", GOSSIP_SENDER_MAIN, 27);
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Чернокнижника (Скорость)", GOSSIP_SENDER_MAIN, 29);
			 
		   }else if ((pPlayer->getClass() == CLASS_SHAMAN))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Шамана (Исцеление)", GOSSIP_SENDER_MAIN, 14); //Сет на шамана хила a8
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Шамана (Совершенствование)", GOSSIP_SENDER_MAIN, 15); //Сет на шамана рд a8
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Шамана (Стихия)", GOSSIP_SENDER_MAIN, 16); //Сет на шамана рдд a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Шамана (Исцеление)", GOSSIP_SENDER_MAIN, 34);
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Шамана (Совершенствование)", GOSSIP_SENDER_MAIN, 35);
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Шамана (Cтихия)", GOSSIP_SENDER_MAIN, 33);		      
		   }else if ((pPlayer->getClass() == CLASS_ROGUE))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Разбойника", GOSSIP_SENDER_MAIN, 17); //Сет на рогу a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Разбойника", GOSSIP_SENDER_MAIN, 32);
		   }else if ((pPlayer->getClass() == CLASS_PRIEST))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Жреца (Темная магия)", GOSSIP_SENDER_MAIN, 18); //Сет на приста ШП a8
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Жреца (Свет)", GOSSIP_SENDER_MAIN, 19); //Сет на приста свет a8
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Жреца (Свет)", GOSSIP_SENDER_MAIN, 28);
		      pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Жреца(Скорость)", GOSSIP_SENDER_MAIN, 29);
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Жреца (Крита)", GOSSIP_SENDER_MAIN, 27);
		   }else if ((pPlayer->getClass() == CLASS_DEATH_KNIGHT))
           {
	          pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Рыцаря смерти", GOSSIP_SENDER_MAIN, 20); //Сет на дк a8
			  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[НонСет] а8 Level (264) на Рыцаря смерти", GOSSIP_SENDER_MAIN, 26);
		   }
		   
		   pPlayer->ADD_GOSSIP_ITEM(9, "Вылечи меня!"                     , GOSSIP_SENDER_MAIN, 3);
		   pPlayer->ADD_GOSSIP_ITEM(5, "Обучить верховую езду на максимум", GOSSIP_SENDER_MAIN, 21); //Верховая езда
		   pPlayer->ADD_GOSSIP_ITEM(9, "Обучить мои навыки защиты и оружия на максимум", GOSSIP_SENDER_MAIN, 23); //Навык макс.
	       pPlayer->ADD_GOSSIP_ITEM(7, "[Меню Телепорта] ->", GOSSIP_SENDER_MAIN, 5); 
           pPlayer->ADD_GOSSIP_ITEM(7, "[Меню Баффов] ->" , GOSSIP_SENDER_MAIN, 24); //Баффер
           pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "[Меню Професий] ->",GOSSIP_SENDER_MAIN, 43);		   
         
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch(uiAction)
      {
	    case 1:
	  	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8_2 Level (270) на мага"  , GOSSIP_SENDER_MAIN, 1000); //Сет на мага a8
		
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
		
		break;
		
		case 2:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1001); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 3:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "[Сет] а8 Level (270) на Шамана (Исцеление)"   , GOSSIP_SENDER_MAIN, 1002); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 4:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1005); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 5:
		if (pPlayer->GetTeam() == ALLIANCE ) {
		    pPlayer->ADD_GOSSIP_ITEM(5, "Награнд (Стартовая точка для Альянс)." , GOSSIP_SENDER_MAIN, 3034);
			pPlayer->ADD_GOSSIP_ITEM(5, "Телепортироваться на ОЛО." , GOSSIP_SENDER_MAIN, 3035);
            pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                 , GOSSIP_SENDER_MAIN, 4035);
            pPlayer->ADD_GOSSIP_ITEM(5, "Дарнасс."                         , GOSSIP_SENDER_MAIN, 12030);
            pPlayer->ADD_GOSSIP_ITEM(5, "Экзодар."                         , GOSSIP_SENDER_MAIN, 1216);
            pPlayer->ADD_GOSSIP_ITEM(5, "Штормград."                       , GOSSIP_SENDER_MAIN, 12060);
            pPlayer->ADD_GOSSIP_ITEM(5, "Стальгорн."                       , GOSSIP_SENDER_MAIN, 1224);
            pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                       , GOSSIP_SENDER_MAIN, 1222);
            pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                         , GOSSIP_SENDER_MAIN, 1287);
            pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                         , GOSSIP_SENDER_MAIN, 1205);
            pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."               , GOSSIP_SENDER_MAIN, 1288);
            if (sConfig->GetIntDefault("RealmID", 0) == 5)
            {
                pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."           , GOSSIP_SENDER_MAIN, 4039);
                pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."              , GOSSIP_SENDER_MAIN, 4040);
            }
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                    , GOSSIP_SENDER_MAIN, 5550);
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"              , GOSSIP_SENDER_MAIN, 5554);

        }  else {
		
            pPlayer->ADD_GOSSIP_ITEM(5, "Награнд (Стартовая точка для Орды)." , GOSSIP_SENDER_MAIN, 3033);
			pPlayer->ADD_GOSSIP_ITEM(5, "Телепортироваться на ОЛО." , GOSSIP_SENDER_MAIN, 3035);
            pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                 , GOSSIP_SENDER_MAIN, 4035);
            pPlayer->ADD_GOSSIP_ITEM(5, "Оргриммар."                       , GOSSIP_SENDER_MAIN, 1215);
            pPlayer->ADD_GOSSIP_ITEM(5, "Луносвет."                        , GOSSIP_SENDER_MAIN, 1217);
            pPlayer->ADD_GOSSIP_ITEM(5, "Подгород."                        , GOSSIP_SENDER_MAIN, 1213);
            pPlayer->ADD_GOSSIP_ITEM(5, "Громовой утёс."                   , GOSSIP_SENDER_MAIN, 1225);
            pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                       , GOSSIP_SENDER_MAIN, 1222);
            pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                         , GOSSIP_SENDER_MAIN, 1287);
            pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                         , GOSSIP_SENDER_MAIN, 1205);
            pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."               , GOSSIP_SENDER_MAIN, 1288);
            if (sConfig->GetIntDefault("RealmID", 0) == 5)
            {
                pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."           , GOSSIP_SENDER_MAIN, 4039);
                pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."              , GOSSIP_SENDER_MAIN, 4040);
            }
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                    , GOSSIP_SENDER_MAIN, 5550);
            pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"              , GOSSIP_SENDER_MAIN, 5554);
        }
		
	   
	   case 6:
		pPlayer->ADD_GOSSIP_ITEM(0, "Как начать играть ?"   , GOSSIP_SENDER_MAIN, 1003); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 7:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1006); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 8:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1007); //Сумки*/
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 9:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1008); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 10:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1009); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 11:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1010); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 12:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1011); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 13:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1012); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 14:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1013); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 15:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1014); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 16:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1015); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 17:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1016); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 18:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1017); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 19:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1018); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 20:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1019); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	    case 21:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1020); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 22:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1021); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 23:
	   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1022); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	   case 24:
		pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Слово силы: Стойкость, Ранк 8", GOSSIP_SENDER_MAIN, 4000);
   				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Великое благословение королей", GOSSIP_SENDER_MAIN, 4001);
        	     pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Великое благословение могущества", GOSSIP_SENDER_MAIN,4002);
    			 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Великое благословение мудрости", GOSSIP_SENDER_MAIN, 4003);
    			 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Знак дикой природы, Ранк 9", GOSSIP_SENDER_MAIN, 4004);
    			 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Чародейский интеллект, Ранк 7", GOSSIP_SENDER_MAIN, 4005);
   				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Шипы, Ранк 8", GOSSIP_SENDER_MAIN, 6007);
  				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Божественный дух, Ранк 8", GOSSIP_SENDER_MAIN, 6008);
   				 pPlayer->ADD_GOSSIP_ITEM(0, "[Бафф]Защита от темной магии, Ранк 5", GOSSIP_SENDER_MAIN, 6009);	
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	 /* case 46:
	pPlayer->ADD_GOSSIP_ITEM(0, "Снять с меня превращения", GOSSIP_SENDER_MAIN, 724);
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
		 break;*/
		 
	case 25:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1023); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
    case 26:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1024); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
    
    case 27:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1025); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
    
    case 28:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1026); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;

    case 29:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1027); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;	   
	   
	case 30:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1028); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	case 31:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1029); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break; 

    case 32:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1030); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;	
    
    case 33:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1031); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;	
	   
	case 34:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1032); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;
	   
	case 35:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1033); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;  
	   
	   case 36://меню бг
		    pPlayer->ADD_GOSSIP_ITEM(0, "Ущелье песни войны 100%", GOSSIP_SENDER_MAIN, 1034);
			pPlayer->ADD_GOSSIP_ITEM(0, "Око бури 100%", GOSSIP_SENDER_MAIN, 1035);
			pPlayer->ADD_GOSSIP_ITEM(0, "Арати базин 100%", GOSSIP_SENDER_MAIN, 1036);
			pPlayer->ADD_GOSSIP_ITEM(0, "Берега древних 100%", GOSSIP_SENDER_MAIN, 1037);
			pPlayer->ADD_GOSSIP_ITEM(0, "Альтерак 100%", GOSSIP_SENDER_MAIN, 1038);
			pPlayer->ADD_GOSSIP_ITEM(0, "Рандом БГ 100%", GOSSIP_SENDER_MAIN, 1051);
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break;  
	   
	    case 37:
		pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Ущелье песни войны!", GOSSIP_SENDER_MAIN, 1039);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Низину Арати!", GOSSIP_SENDER_MAIN, 1040);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс ОЛО!", GOSSIP_SENDER_MAIN, 1041);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Остров Завоеваний!", GOSSIP_SENDER_MAIN, 1042);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Альтерак!", GOSSIP_SENDER_MAIN, 1043);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Рандом БГ!", GOSSIP_SENDER_MAIN, 1044);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Арену 2v2!", GOSSIP_SENDER_MAIN, 1045);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Арену 3v3!", GOSSIP_SENDER_MAIN, 1046);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Арену 5v5!", GOSSIP_SENDER_MAIN, 1047);
        pPlayer->ADD_GOSSIP_ITEM(0, "Дать Аннонс Око Бури!", GOSSIP_SENDER_MAIN, 1048);
		break;
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break; 
	   
	    case 38:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1049); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break; 
	   
	    case 39:
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Покупка_2 Сумок"   , GOSSIP_SENDER_MAIN, 1050); //Сумки
		
	   pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	   
	   break; 
	   
	   case 43:
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
				
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

 		break;
		
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
            case 54:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_COOKING);

                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            case 55:
                CompleteLearnProfession(pPlayer, pCreature, SKILL_FIRST_AID);

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

         case 1000: //сет на мага
	   pPlayer->CLOSE_GOSSIP_MENU();
	   pPlayer->AddItem(51465, 1);
	   pPlayer->AddItem(51467, 1);
	   pPlayer->AddItem(51463, 1);
	   pPlayer->AddItem(51464, 1);
	   pPlayer->AddItem(51466, 1);
	   break;
	   
       case 1001: //сумки
		pPlayer->CLOSE_GOSSIP_MENU();
		pPlayer->AddItem(23162, 4);
		break;
		
		case 1002: // Heal me!
		pPlayer->CLOSE_GOSSIP_MENU();
                if (pPlayer->HasAura(45523) )
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("Я больше не могу - это сделать.", pPlayer->GetGUID(), false);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->CastSpell(pPlayer, 39321, true);
                    pPlayer->CastSpell(pPlayer, 45523, true);
                }
                break;
		 
        case 1003:
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("Здравствуй странник, знаю для тебя - это ново, но слушай меня. Только у меня ты можешь приобрести безвозмездно снаряжение комплекта а8, Нонсет а8,  а также попасть почти в любую точку света, обучить верховую езду, обучить свои навыки защиты и оружия, приобрести сумки. Ну и многое другое...  выбирай =)", pPlayer->GetGUID(), false);
		 break;
		 
		 case 1005://Сет на ретри пала a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51476, 1);
		 pPlayer->AddItem(51479, 1);
		 pPlayer->AddItem(51474, 1);
		 pPlayer->AddItem(51475, 1);
		 pPlayer->AddItem(51477, 1);
		 break;
		 
         case 1006://Сет на холи пала a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51470, 1);
		 pPlayer->AddItem(51473, 1);
		 pPlayer->AddItem(51468, 1);
		 pPlayer->AddItem(51469, 1);
		 pPlayer->AddItem(51471, 1);
		 break;
		 
		 case 1007: //Сет на ханта a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51460, 1);
		 pPlayer->AddItem(51462, 1);
		 pPlayer->AddItem(51458, 1);
		 pPlayer->AddItem(51459, 1);
		 pPlayer->AddItem(51461, 1);
		 break;
		 
		 case 1008://Сет на друида хилла a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51421, 1);
		 pPlayer->AddItem(51424, 1);
		 pPlayer->AddItem(51419, 1);
		 pPlayer->AddItem(51420, 1);
		 pPlayer->AddItem(51422, 1);
		 break;
		 
         case 1009://Сет на друида дд a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51427, 1);
		 pPlayer->AddItem(51430, 1);
		 pPlayer->AddItem(51425, 1);
		 pPlayer->AddItem(51426, 1);
		 pPlayer->AddItem(51428, 1);
		 break;
		 
         case 1010://Сет на друида рдд a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51435, 1);
		 pPlayer->AddItem(51438, 1);
		 pPlayer->AddItem(51433, 1);
		 pPlayer->AddItem(51434, 1);
		 pPlayer->AddItem(51436, 1);
		 break;
		 
		 case 1011://Сет на вара a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51543, 1);
		 pPlayer->AddItem(51545, 1);
		 pPlayer->AddItem(51541, 1);
		 pPlayer->AddItem(51542, 1);
		 pPlayer->AddItem(51544, 1);
		 break;
		 
		 case 1012://Сет на лока a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51538, 1);
		 pPlayer->AddItem(51540, 1);
		 pPlayer->AddItem(51536, 1);
		 pPlayer->AddItem(51537, 1);
		 pPlayer->AddItem(51539, 1);
		 break;
		 
        case 1013://Сет на шамана хила a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51499, 1);
		 pPlayer->AddItem(51502, 1);
		 pPlayer->AddItem(51497, 1);
		 pPlayer->AddItem(51498, 1);
		 pPlayer->AddItem(51500, 1);
		 break;
		 
         case 1014://Сет на шамана дд a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51505, 1);
		 pPlayer->AddItem(51508, 1);
		 pPlayer->AddItem(51503, 1);
		 pPlayer->AddItem(51504, 1);
		 pPlayer->AddItem(51506, 1);
		 break;
		 
         case 1015://Сет на шамана рдд a8
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(51511, 1);
		 pPlayer->AddItem(51514, 1);
		 pPlayer->AddItem(51509, 1);
		 pPlayer->AddItem(51510, 1);
		 pPlayer->AddItem(51512, 1);
		 break;	

         case 1016: //Сет на рогу a8
		  pPlayer->CLOSE_GOSSIP_MENU();
		  pPlayer->AddItem(51494, 1);
		  pPlayer->AddItem(51496, 1);
		  pPlayer->AddItem(51492, 1);
		  pPlayer->AddItem(51493, 1);
		  pPlayer->AddItem(51495, 1);
		  break;
		  
          case 1017://Сет на приста ШП a8
	  pPlayer->CLOSE_GOSSIP_MENU();
	  pPlayer->AddItem(51489, 1);
	  pPlayer->AddItem(51491, 1);
	  pPlayer->AddItem(51487, 1);
	  pPlayer->AddItem(51488, 1);
	  pPlayer->AddItem(51490, 1);
	  break;
	  
      case 1018: //Сет на приста свет a8
	  pPlayer->CLOSE_GOSSIP_MENU();
	  pPlayer->AddItem(51484, 1);
	  pPlayer->AddItem(51486, 1);
	  pPlayer->AddItem(51482, 1);
	  pPlayer->AddItem(51483, 1);
	  pPlayer->AddItem(51485, 1);
	  break;
	  
     case 1019: //сет на дк
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51415, 1);
	 pPlayer->AddItem(51418, 1);
	 pPlayer->AddItem(51413, 1);
	 pPlayer->AddItem(51414, 1);
	 pPlayer->AddItem(51416, 1);
	 break;
	
     case 1020: //Верховая езда
	 pPlayer->CLOSE_GOSSIP_MENU();
		      {
		        pPlayer->learnSpell(33388, false);
		        pPlayer->learnSpell(33391, false);
		        pPlayer->learnSpell(34090, false);
		        pPlayer->learnSpell(34091, false);
		        pPlayer->learnSpell(54197, false);
		      }	
			  return true;
	
	case 1022:
	pPlayer->CLOSE_GOSSIP_MENU();
		pPlayer->UpdateSkillsToMaxSkillsForLevel();
		pCreature->MonsterWhisper("Вы успешно приобрели навыки защиты и оружия.", pPlayer->GetGUID(), false);
		break;
	
	case 1023: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51361, 1);
	 pPlayer->AddItem(51360, 1);
	 pPlayer->AddItem(51359, 1);
	 break;
	
	case 1024: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51364, 1);
	 pPlayer->AddItem(51362, 1);
	 pPlayer->AddItem(51363, 1);
	 break;
	 
	case 1025: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51329, 1);
	 pPlayer->AddItem(51328, 1);
	 pPlayer->AddItem(51327, 1);
	 break;
	 
	case 1026: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51367, 1);
	 pPlayer->AddItem(51366, 1);
	 pPlayer->AddItem(51365, 1);
	 break;
	 
	case 1027: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51339, 1);
	 pPlayer->AddItem(51338, 1);
	 pPlayer->AddItem(51337, 1);
	 break;
	 
	case 1028: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51345, 1);
	 pPlayer->AddItem(51344, 1);
	 pPlayer->AddItem(51343, 1);
	 break;
	 
	case 1029: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51342, 1);
	 pPlayer->AddItem(51341, 1);
	 pPlayer->AddItem(51340, 1);
	 break;
	 
	case 1030: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51370, 1);
	 pPlayer->AddItem(51369, 1);
	 pPlayer->AddItem(51368, 1);
	 break;
	 
	case 1031: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51376, 1);
	 pPlayer->AddItem(51375, 1);
	 pPlayer->AddItem(51374, 1);
	 break;
	 
	case 1032: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51373, 1);
	 pPlayer->AddItem(51372, 1);
	 pPlayer->AddItem(51371, 1);
	 break;
	 
	case 1033: 
	 pPlayer->CLOSE_GOSSIP_MENU();
	 pPlayer->AddItem(51352, 1);
	 pPlayer->AddItem(51351, 1);
	 pPlayer->AddItem(51350, 1);
	 break;
	 
	 case 1034: // WSG 100%
			/* Comment: IDS:
			SOTA - 9
			AV - 1
			WSG - 2
			AB - 3
			EOTS - 7
			Random - 32*/

			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=0 WHERE `entry` IN(1, 3, 7, 9)");
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=10 WHERE `entry`=2");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Done", GOSSIP_SENDER_MAIN, 12345);
			break;

		case 1035: // EOTS 100%
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=0 WHERE `entry` IN(1, 3, 2, 9)");
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=10 WHERE `entry`=7");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Done", GOSSIP_SENDER_MAIN, 12345);
			break;

		case 1036: // AB 100%
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=0 WHERE `entry` IN(1, 2, 7, 9)");
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=10 WHERE `entry`=3");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Done", GOSSIP_SENDER_MAIN, 12345);
			break;

		case 1037: // Sota 100%
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=0 WHERE `entry` IN(1, 3, 7, 2)");
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=10 WHERE `entry`=9");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Done", GOSSIP_SENDER_MAIN, 12345);
			break;

		case 1038: // AV 100%
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=0 WHERE `entry` IN(2, 3, 7, 9)");
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=10 WHERE `entry`=1");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Done", GOSSIP_SENDER_MAIN, 12345);
			break;
			
		case 1039:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте БГ Ущелье Песни Войны");
                break;
 
        case 1040:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте БГ Арати");
                break;
 
        case 1041:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте ОЛО");
                break;
 
        case 1042:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте БГ Берег Древних");
                break;
 
        case 1043:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте БГ Альтерак");
                break;
 
        case 1044:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте Рандом БГ");
                break;
 
        case 1045:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте Арену 2х2");
                break;
 
        case 1046:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте Арену 3х3");
                break;
 
        case 1047:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте Арену 5х5");
                break;
 
        case 1048:
                pPlayer->CLOSE_GOSSIP_MENU();
                ChatHandler(pPlayer).SendSysMessage("Регайте БГ Око Бури");
                break;
		
		case 1049:
		 pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(37829, 200);
		 break;
		 
		case 1050:
		pPlayer->CLOSE_GOSSIP_MENU();
		 pPlayer->AddItem(44990, 150);
		 break;
		 
		case 1051: // RANDOM 100%
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=0 WHERE `entry` IN(1, 3, 7, 9)");
			WorldDatabase.PQuery("UPDATE `battleground_template` SET `Weight`=10 WHERE `entry`=32");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Done", GOSSIP_SENDER_MAIN, 12345);
			break;
		 
	
	case 4000:
	        pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48161, false);
            break;
 
        case 4001:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 25898, false);
            break;
 
        case 4002:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48934, false);
            break;
 
        case 4003:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48938, false);
            break;
 
        case 4004:
		pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48469, false);
            break;                              
                
                case 4005:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 42995, false);
            break;
 
                case 6007:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 53307, false);
            break;
 
                case 6008:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48073, false);
            break;
 
                case 6009:
				pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 48169, false);
            break;
	   
	   case 5550: //Instances
                pPlayer->ADD_GOSSIP_ITEM(5, "Огненная пропасть."            , GOSSIP_SENDER_MAIN, 1248);
                pPlayer->ADD_GOSSIP_ITEM(5, "Пещеры стенаний."              , GOSSIP_SENDER_MAIN, 1249);
                pPlayer->ADD_GOSSIP_ITEM(5, "Тюрьма."                       , GOSSIP_SENDER_MAIN, 1253);
                pPlayer->ADD_GOSSIP_ITEM(5, "Мертвые копи."                 , GOSSIP_SENDER_MAIN, 1250);
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Темного Клыка."       , GOSSIP_SENDER_MAIN, 1251);
                pPlayer->ADD_GOSSIP_ITEM(5, "Непроглядная Пучина."          , GOSSIP_SENDER_MAIN, 1252);
                pPlayer->ADD_GOSSIP_ITEM(5, "Лабиринты Иглошкурых."         , GOSSIP_SENDER_MAIN, 1254);
                pPlayer->ADD_GOSSIP_ITEM(5, "Курганы Иглошкурых."           , GOSSIP_SENDER_MAIN, 1256);
                pPlayer->ADD_GOSSIP_ITEM(5, "Монастырь Алого Ордена."       , GOSSIP_SENDER_MAIN, 1257);
                pPlayer->ADD_GOSSIP_ITEM(5, "Аукиндон."                     , GOSSIP_SENDER_MAIN, 4038);
                pPlayer->ADD_GOSSIP_ITEM(7, "[Ещё] ->"                      , GOSSIP_SENDER_MAIN, 5551);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"             , GOSSIP_SENDER_MAIN, 5552);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5551: //More Instances
                pPlayer->ADD_GOSSIP_ITEM(5, "Ульдаман."                  , GOSSIP_SENDER_MAIN, 1258);
                pPlayer->ADD_GOSSIP_ITEM(5, "Зул'Фаррак."                , GOSSIP_SENDER_MAIN, 1259);
                pPlayer->ADD_GOSSIP_ITEM(5, "Мародон."                   , GOSSIP_SENDER_MAIN, 1260);
                pPlayer->ADD_GOSSIP_ITEM(5, "Затонувший храм."           , GOSSIP_SENDER_MAIN, 1261);
                pPlayer->ADD_GOSSIP_ITEM(5, "Глубины Чёрной Горы."       , GOSSIP_SENDER_MAIN, 1262);
                pPlayer->ADD_GOSSIP_ITEM(5, "Забытый Город."             , GOSSIP_SENDER_MAIN, 1263);
                pPlayer->ADD_GOSSIP_ITEM(5, "Пик Чёрной горы."           , GOSSIP_SENDER_MAIN, 1264);
                pPlayer->ADD_GOSSIP_ITEM(5, "Стратхольм."                , GOSSIP_SENDER_MAIN, 1265);
                pPlayer->ADD_GOSSIP_ITEM(5, "Некроситет."                , GOSSIP_SENDER_MAIN, 1266);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ан'кираж."                  , GOSSIP_SENDER_MAIN, 4037);
                pPlayer->ADD_GOSSIP_ITEM(7, "[Ещё] ->"                   , GOSSIP_SENDER_MAIN, 5553);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                 , GOSSIP_SENDER_MAIN, 5550);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"          , GOSSIP_SENDER_MAIN, 5552);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5553: //Instances 60-70
                pPlayer->ADD_GOSSIP_ITEM(5, "Каражан."                   , GOSSIP_SENDER_MAIN, 4007);
                pPlayer->ADD_GOSSIP_ITEM(5, "Логово Груула."             , GOSSIP_SENDER_MAIN, 4008);
                pPlayer->ADD_GOSSIP_ITEM(5, "Цитадель Адского Пламени."  , GOSSIP_SENDER_MAIN, 4009);
                pPlayer->ADD_GOSSIP_ITEM(5, "Резервуар Кривого Клыка."   , GOSSIP_SENDER_MAIN, 4010);
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Бурь."             , GOSSIP_SENDER_MAIN, 4011);
                pPlayer->ADD_GOSSIP_ITEM(5, "Пещеры Времени."            , GOSSIP_SENDER_MAIN, 4012);
                pPlayer->ADD_GOSSIP_ITEM(5, "Зул'Аман."                  , GOSSIP_SENDER_MAIN, 4016);
                pPlayer->ADD_GOSSIP_ITEM(5, "Зул'Гуруб."                 , GOSSIP_SENDER_MAIN, 4034);
                pPlayer->ADD_GOSSIP_ITEM(5, "Чёрный Храм."               , GOSSIP_SENDER_MAIN, 4013);
                pPlayer->ADD_GOSSIP_ITEM(5, "Террасса Магистров."        , GOSSIP_SENDER_MAIN, 4017);
                pPlayer->ADD_GOSSIP_ITEM(5, "Плато Солнечного Колодца."  , GOSSIP_SENDER_MAIN, 4018);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                 , GOSSIP_SENDER_MAIN, 5550);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"          , GOSSIP_SENDER_MAIN, 5552);


                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5554: //Instances 75-80 NORTHREND
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Утгард."                        , GOSSIP_SENDER_MAIN, 4019);
                pPlayer->ADD_GOSSIP_ITEM(5, "Нексус."                                 , GOSSIP_SENDER_MAIN, 4020);
                pPlayer->ADD_GOSSIP_ITEM(5, "Азжол-Неруб."                            , GOSSIP_SENDER_MAIN, 4021);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ан'кахет: Старое Королевство."           , GOSSIP_SENDER_MAIN, 4022);
                pPlayer->ADD_GOSSIP_ITEM(5, "Крепость Драк'Тарон."                    , GOSSIP_SENDER_MAIN, 4023);
                pPlayer->ADD_GOSSIP_ITEM(5, "Аметистовая Цитадель."                   , GOSSIP_SENDER_MAIN, 4024);
                pPlayer->ADD_GOSSIP_ITEM(5, "Гун'Драк."                               , GOSSIP_SENDER_MAIN, 4025);
                pPlayer->ADD_GOSSIP_ITEM(5, "Вершина Утгард."                         , GOSSIP_SENDER_MAIN, 4026);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ульдуар."                                , GOSSIP_SENDER_MAIN, 4027);
                pPlayer->ADD_GOSSIP_ITEM(7, "[Ещё] ->"                                , GOSSIP_SENDER_MAIN, 5555);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                              , GOSSIP_SENDER_MAIN, 5550);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"                       , GOSSIP_SENDER_MAIN, 5552);


                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5555: //Instances 75-80 NORTHREND more
                pPlayer->ADD_GOSSIP_ITEM(5, "Обсидиановое святилище."                , GOSSIP_SENDER_MAIN, 4028);
                pPlayer->ADD_GOSSIP_ITEM(5, "Наксрамас."                             , GOSSIP_SENDER_MAIN, 4029);
                pPlayer->ADD_GOSSIP_ITEM(5, "Колизей Серебрянного Авангарда."        , GOSSIP_SENDER_MAIN, 4032);
                pPlayer->ADD_GOSSIP_ITEM(5, "Склеп Аркавона."                        , GOSSIP_SENDER_MAIN, 4030);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ледяная Корона: Рейд."                  , GOSSIP_SENDER_MAIN, 4031);
                pPlayer->ADD_GOSSIP_ITEM(5, "Ледяная Корона: Ледяные Залы."          , GOSSIP_SENDER_MAIN, 4033);
                pPlayer->ADD_GOSSIP_ITEM(5, "Логово Ониксии."                        , GOSSIP_SENDER_MAIN, 4036);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Назад]"                             , GOSSIP_SENDER_MAIN, 5554);
                pPlayer->ADD_GOSSIP_ITEM(7, "<- [Главное меню]"                      , GOSSIP_SENDER_MAIN, 5552);


                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;

            case 5552: //Back To Main Menu
                if (pPlayer->GetTeam() == ALLIANCE ) {
                    pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                       , GOSSIP_SENDER_MAIN, 4035);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Дарнасс."                               , GOSSIP_SENDER_MAIN, 12030);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Экзодар."                               , GOSSIP_SENDER_MAIN, 1216);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Штормград."                             , GOSSIP_SENDER_MAIN, 12060);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Стальгорн."                             , GOSSIP_SENDER_MAIN, 1224);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                             , GOSSIP_SENDER_MAIN, 1222);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                               , GOSSIP_SENDER_MAIN, 1287);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                               , GOSSIP_SENDER_MAIN, 12050);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."                     , GOSSIP_SENDER_MAIN, 1288);
                    if (sConfig->GetIntDefault("RealmID", 0) == 5)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."                 , GOSSIP_SENDER_MAIN, 4039);
                        pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."                    , GOSSIP_SENDER_MAIN, 4040);
                    }
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                          , GOSSIP_SENDER_MAIN, 5550);
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"                    , GOSSIP_SENDER_MAIN, 5554);

                }  else {

                    pPlayer->ADD_GOSSIP_ITEM(5, "Пиратская Бухта."                       , GOSSIP_SENDER_MAIN, 4035);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Оргриммар."                             , GOSSIP_SENDER_MAIN, 1215);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Луносвет."                              , GOSSIP_SENDER_MAIN, 1217);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Подгород."                              , GOSSIP_SENDER_MAIN, 1213);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Громовой утёс."                         , GOSSIP_SENDER_MAIN, 1225);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Гномреган."                             , GOSSIP_SENDER_MAIN, 1222);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат.."                              , GOSSIP_SENDER_MAIN, 1287);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                               , GOSSIP_SENDER_MAIN, 12050);
                    pPlayer->ADD_GOSSIP_ITEM(5, "Остров Кель'Данас."                     , GOSSIP_SENDER_MAIN, 1288);
                    if (sConfig->GetIntDefault("RealmID", 0) == 5)
                    {
                        pPlayer->ADD_GOSSIP_ITEM(5, "Стартовая локация."                 , GOSSIP_SENDER_MAIN, 4039);
                        pPlayer->ADD_GOSSIP_ITEM(5, "Арена награнда."                    , GOSSIP_SENDER_MAIN, 4040);
                    }
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы] ->"                          , GOSSIP_SENDER_MAIN, 5550);
                    pPlayer->ADD_GOSSIP_ITEM(7, "[Инстансы WotLK] ->"                    , GOSSIP_SENDER_MAIN, 5554);
                }

                    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

                break;
			case 3035: //портал на ОЛО
			pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(571, 5325.06f, 2843.36f, 409.285f, 3.2f);
                  break;
				  
			case 3033://орда
			pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, -1244.28f, 7169.27f, 57.26f, 2.21f);
                break;
				
			case 3034: //алы
            pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, -2647.65f, 7190.15f, 23.60f, 0.9f);
                break;
				
            case 12030: // Teleport to Darnassus
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
                break;

            case 12060: // Teleport to Stormwind
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                break;

            case 12050: // Teleport to Dalaran
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(571, 5804.14f, 624.770f, 647.7670f, 1.64f);
                break;

            case 1213: // Teleport to Undercity
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
                break;

            case 1215: // Teleport to Orgrimmar
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                break;

            case 1216: // Teleport to Exodar
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, -4073.03f, -12020.4f, -1.47f, 0.0f);
                break;

            case 1217: // Teleport to Silvermoon
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
                break;

            case 1222: // Teleport to Gnomeregan
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -5163.43f,660.40f,348.28f,4.65f);
                    break;

            case 1224: // Teleport to Ironforge
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
                break;

            case 1225: // Teleport to Thunder Bluff
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(1, -1280.19f,127.21f,131.35f,5.16f); 
                break;

            case 1248: // Teleport Player to Ragefire Chasm
                if( pPlayer->getLevel() >= 8)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, 1800.53f,-4394.68f,-17.93f,5.49f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 8!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1249: // Teleport to the Wailing Caverns
                if (pPlayer->getLevel() >= 10)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -722.53f,-2226.30f,16.94f,2.71f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 10!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1250: // Teleport to the Deadmines
                if (pPlayer->getLevel() >= 10)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -11212.04f,1658.58f,25.67f,1.45f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 10!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1251: // Teleport to Shadowfang Keep
                if (pPlayer->getLevel() >= 15)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -254.47f,1524.68f,76.89f,1.56f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 15!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1252: // Teleport to Blackfathom Deeps
                if (pPlayer->getLevel() >= 15)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, 4254.58f,664.74f,-29.04f,1.97f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 15!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1253: // Teleport to the Stockade
                if (pPlayer->getLevel() >= 20)  
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -8769.76f,813.08f,97.63f,2.26f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 20!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1254: // Teleport to Razorfen Kraul
                if (pPlayer->getLevel() >= 24)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -4484.04f,-1739.40f,86.47f,1.23f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 24!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1255: // Teleport to Gnomeregan
                if (pPlayer->getLevel() >= 20)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -5162.62f,667.81f,248.05f,1.48f);   
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 20!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1256: // Teleport to Razorfen Downs
                if (pPlayer->getLevel() >= 25)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -4645.08f,-2470.85f,85.53f,4.39f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 25!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1257: // Teleport to the Scarlet Monastery
                if (pPlayer->getLevel() >= 25)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, 2843.89f,-693.74f,139.32f,5.11f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 25!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1258://Teleport to Uldaman
                if (pPlayer->getLevel() >= 35)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -6119.70f,-2957.30f,204.11f,0.03f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 35!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1259: // Teleport to Zul'Farrak
                if (pPlayer->getLevel() >= 35)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -6839.39f,-2911.03f,8.87f,0.41f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 35!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1260: // Teleport to Maraudon
                if (pPlayer->getLevel() >= 40)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -1433.33f,2955.34f,96.21f,4.82f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 40!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1261: // Teleport to the Sunken Temple
                if (pPlayer->getLevel() >= 45)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -10346.92f,-3851.90f,-43.41f,6.09f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 45!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1262: // Teleport to Blackrock Depths
                if (pPlayer->getLevel() >= 45)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -7301.03f,-913.19f,165.37f,0.08f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 45!", LANG_UNIVERSAL, NULL);
                }
                    break;

            case 1263: // Teleport to Dire Maul
                if (pPlayer->getLevel() >= 50)       
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -3982.47f,1127.79f,161.02f,0.05f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1264: // Teleport to Blackrock Spire
                if (pPlayer->getLevel() >= 50)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -7535.43f,-1212.04f,285.45f,5.29f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1265: // Teleport to Stratholme
                if (pPlayer->getLevel() >= 50)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, 3263.54f,-3379.46f,143.59f,0.00f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1266: // Teleport to Scholomance
                if (pPlayer->getLevel() >= 50)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, 1219.01f,-2604.66f,85.61f,0.50f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1287:// Shattrath City
                if( pPlayer->getLevel() >= 58)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 58!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 1288: // Teleport to Isle Of Quel'Danas
                if (pPlayer->getLevel() >= 65)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 12947.4f,-6893.31f,5.68398f,3.09154f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 65!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4007: // Karazhan
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -11118.8f, -2010.84f, 47.0807f, 0.0f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4008: // Gruul's Lair
                if (pPlayer->getLevel() >= 65)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 3539.007568f, 5082.357910f, 1.691071f, 0.0f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 65!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4009: // Hellfire Citadel
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, -305.816223f, 3056.401611f, -2.473183f, 2.01f);
                break;

            case 4010: // Coilfang Reservoir
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(530, 517.288025f, 6976.279785f, 32.007198f, 0.0f);
                break;

            case 4011: // Tempest Keep
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 3089.579346f, 1399.046509f, 187.653458f, 4.794070f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4012: // Caverns of Time
                if (pPlayer->getLevel() >= 66)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -8173.66f, -4746.36f, 33.8423f, 4.93989f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 66!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4016: // Zul'Aman
                if (pPlayer->getLevel() >= 70)  
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 6846.95f, -7954.5f, 170.028f, 4.61501f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4013: // Black Temple
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -3610.719482f, 324.987579f, 37.400028f, 3.282981f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4017: // magistrate
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4018: // Sunwell
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4019:// Utgarde Keep
                if (pPlayer->getLevel() >= 70)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 1219.720f, -4865.28f, 41.25f, 0.31f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4020: // The Nexus
                if (pPlayer->getLevel() >= 70)  
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3776.950f, 6953.80f, 105.05f, 0.345f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4021: // Azjol-Nerub
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3675.430f, 2169.00f, 35.90f, 2.29f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4022: // Ahn'kahet: The Old Kingdom
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3646.760f, 2045.17f, 1.79f, 4.37f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4023: // Drak'Tharon Keep
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 4450.860f, -2045.25f, 162.83f, 0.00f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4024: // The Violet Hold
                if (pPlayer->getLevel() >= 70)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5679.820f, 486.80f, 652.40f, 4.08f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4025: // Gun' Drak
                if (pPlayer->getLevel() >= 70)    
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 6937.540f, -4455.98f, 450.68f, 1.00f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4026: // Utgarde Pinnacle
                if (pPlayer->getLevel() >= 70) 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 1245.690f, -4856.59f, 216.86f, 3.45f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4027: // Ulduar
                if (pPlayer->getLevel() >= 70) 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 8976.240f, -1281.33f, 1059.01f, 0.58f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4028: // The Obsidian Sanctum
                if (pPlayer->getLevel() >= 70)   
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3625.780f, 280.40f, -120.14f, 3.25f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4029: // Naxxramas
                if (pPlayer->getLevel() >= 70)       
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 3668.719f, -1262.460f, 243.63f, 5.03f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4030: // Archavon's Valut
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5475.506f, 2840.60f, 418.67f, 6.25f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень не должен быть ниже бы уровня 70!", LANG_UNIVERSAL, NULL);
                } 
                break;

            case 4031: // Icecrown Raid
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5796.494f, 2075.29f, 636.06f, 3.59f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень не должен быть ниже бы уровня 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4032: // Argent Coliseum
                if (pPlayer->getLevel() >= 70)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 8516.204f, 641.40f, 547.32f, 1.61f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень не должен быть ниже бы уровня 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4033: // Icecrown Daily
                if (pPlayer->getLevel() >= 70)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(571, 5631.911f, 2011.72f, 798.26f, 4.59f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 70!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4034: // Zul'Gurub
                if (pPlayer->getLevel() >= 50)     
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -11916.153f, -1211.612f, 92.28f, 4.68f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4035: // Booty Bay
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->TeleportTo(0, -14290.535f, 548.290f, 8.85f, 4.29f);
                break;

            case 4036: // Onyxia
                if (pPlayer->getLevel() >= 60)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(1, -4712.451f, -3729.173f, 54.21f, 0.56f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 60!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4037: // AQ
                if (pPlayer->getLevel() >= 50)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -8254.271f, 1536.794f, -4.80f, 5.67f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4038:
                if (pPlayer->getLevel() >= 50)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(0, -3354.630f, 4930.559f, -99.97f, 0.33f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterSay("Ваш уровень должен превышать 50!", LANG_UNIVERSAL, NULL);
                }
                break;

            case 4039: // Start locations
                if (pPlayer->GetTeam() == ALLIANCE)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -2244.01f, 8698.61f, -2.73f, 5.16f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -1236.92f, 7144.97f, 57.26f, 4.78f);
                }
                break;

            case 4040: // Nagrand Arena
                if (pPlayer->GetTeam() == ALLIANCE)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -2106.58f, 6749.17f, -3.65f, 5.27f);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->TeleportTo(530, -1971.01f, 6541.43f, 12.75f, 2.48f);
                }
                break;
         

case 724: 
    pPlayer->CLOSE_GOSSIP_MENU();
	pCreature->MonsterWhisper("Выберите у меня меню Телепорт -> Телепортироваться на ОЛО, далее у вас выскочет меню 'Присоединиться к битве за Озеро Леляных Оков' Жмете 'да' и вы в пати. Больше создавать самим пати на ОЛО не нужно. ", pPlayer->GetGUID(), false);
break;

			}
			
        return true;
    }
};

class item_9999020 : public ItemScript
{
public:
    item_9999020() : ItemScript("item_9999020") { }

    bool OnUse(Player* pPlayer, Item* /*pItem*/, SpellCastTargets const& /*targets*/)
    {
	     if( pPlayer->isInCombat() || pPlayer->isInFlight() || pPlayer->GetMap()->IsBattlegroundOrArena() || pPlayer->HasStealthAura() || pPlayer->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || pPlayer->isDead())
		 {
		  pPlayer->CastSpell(pPlayer, 39321, true);
          pPlayer->TeleportTo(1, 4825.540f, -1961.160f, 1070.730f, 3.85f);
		 }
    
        return false;
    }
};

class item_9999021 : public ItemScript
{
public:
    item_9999021() : ItemScript("item_9999021") { }

    bool OnUse(Player* pPlayer, Item* /*pItem*/, SpellCastTargets const& /*targets*/)
    {
	     if( pPlayer->isInCombat() || pPlayer->isInFlight() || pPlayer->GetMap()->IsBattlegroundOrArena() || pPlayer->HasStealthAura() || pPlayer->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || pPlayer->isDead())
		 {
		  pPlayer->CastSpell(pPlayer, 39321, true);
          pPlayer->TeleportTo(0, -7516.500f, -3479.83f, 172.068f, 2.71f);
         }
        return false;
    }
};

void AddSC_npc_amegawow()
{
    new npc_amegawow;
	new item_9999020;
	new item_9999021;
}
