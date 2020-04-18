#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Language.h"

#define MSG_GOSSIP_TEXT_GETTING_STARTED	"Welcome to Warlord-Gaming!"

#define MSG_ERR_HONOR "You do not have enough Honor for the purchase!"
#define MSG_ERR_ARENA_POINT_1 "You do not have enough Apa!"
#define MSG_ERR_TITLE "At this character already has a title!"
#define MSG_ERR_INCOMBAT "You are in combat. Npc To use this exit it."
#define MSG_COMPLETE_RENAME "Make Payment Successfully Produced Logout and enter a new name Personazha.Ne Forget After a name change, leave the game and remove from the Client Folder Cache!"
#define MSG_CUSTOMIZE_COMPLETE "Make Payment succeeded, Logout, and Change the Appearance Personazha.Ne Forget after the change of appearance, leave the game and remove from the Client Folder Cache!"
#define MSG_CHANGE_FACTION_COMPLETE "Make Payment succeeded, Logout, and Change the fraction Personazha.Ne Forget after the change of appearance, leave the game and remove from the Client Folder Cache!"

#define MSG_GOSSIP_TEXT_MAX_HEALTH "Heal me!"
#define MSG_GOSSIP_TEXT_MAX_SKILL "Learn all the skills and weapons of defense."

#define MSG_GOSSIP_TEXT_BUFF_POWER_WORD "Power Word: Fortitude"
#define MSG_GOSSIP_TEXT_BUFF_BLESSING_OF_KINGS "Blessing of Kings"
#define MSG_GOSSIP_TEXT_BUFF_MARK_OF_THE_WILD "Mark of the Wild"
#define MSG_GOSSIP_TEXT_BUFF_ARCANE_BRILLIANCE "Dalaran Brilliance"
#define MSG_GOSSIP_TEXT_BUFF_BLESSING_OF_MIGHT "Greater Blessing of Might"
#define MSG_GOSSIP_TEXT_BUFF_BLESSING_OF_WISDOM "Blessing of Wisdom"
#define MSG_GOSSIP_TEXT_BUFF_THORNS "Thorns"
#define MSG_GOSSIP_TEXT_BUFF_DIVINE_SPIRIT "Divine Spirit"
#define MSG_GOSSIP_TEXT_BUFF_SHADOW_PROTECTION "Shadow Protection"
#define MSG_GOSSIP_TEXT_BUFF_STAMINA "Endurance"

#define MSG_GOSSIP_TEXT_BUFF_MENU "[Buffs Menu] ->"
#define MSG_GOSSIP_TEXT_MAIN_MENU "<- [Return to Main Menu]"
#define MSG_GOSSIP_TEXT_PROFFESION_MENU "[Professions Menu] ->"
#define MSG_GOSSIP_TEXT_PROFFESION_SECON_MENU "[The menu is secondary professions] ->"

#define MSG_GOSSIP_TEXT_RENAME "Character Name Change for Free." / / Thank Crispi
#define MSG_GOSSIP_TEXT_CUSTOM "Changing the appearance of the character for Free" / / Thank Crispi
#define MSG_GOSSIP_TEXT_CHANGE_FACTION "Character Faction Change for Free."

#define MSG_GOSSIP_TEXT_TITLES_JENKINS "Get the title for 500 Jenkins Apa."
#define MSG_GOSSIP_TEXT_TITLES_THE_LOVE_FOOL "Madly in Love Get a rank of 500 Apa."
#define MSG_GOSSIP_TEXT_TITLES_MERRYMAKER "Get Merry title for 500 Apa."
#define MSG_GOSSIP_TEXT_TITLES_SCARAB_LORD "Get the title of Lord of Skorobeev for 500 Apa."
#define MSG_GOSSIP_TEXT_TITLES_THE_NOBLE "Get A wonderful title for 500 Apa."
#define MSG_GOSSIP_TEXT_TITLES_OBSIDIAN_SLAYER "Get the title of Conqueror of Obsidian for 1 thousand Apa."

#define MSG_GOSSIP_TEXT_MORTH_GNOME_MALE "[Turn] Gnome, man."
#define MSG_GOSSIP_TEXT_MORTH_GNOME_FEMALE "[Turn] Dwarf, woman."
#define MSG_GOSSIP_TEXT_MORTH_HUMAN_FEMALE "[Turn] Man, woman."
#define MSG_GOSSIP_TEXT_MORTH_HUMAN_MALE "[Turn] Man, man."
#define MSG_GOSSIP_TEXT_MORTH_BLOOD_ELF_MALE "[Turn] Blood Elf, man."
#define MSG_GOSSIP_TEXT_MORTH_BLOOD_ELF_FEMALE "[Turn] Blood Elf, woman."
#define MSG_GOSSIP_TEXT_MORTH_TAUREN_MALE "[Turn] Tauren, man."
#define MSG_GOSSIP_TEXT_MORTH_TAUREN_FEMALE "[Turn] Tauren, woman."

#define MSG_GOSSIP_TEXT_ALCHEMY "Learn Alchemy"
#define MSG_GOSSIP_TEXT_BLACKSMITHING "Learn Blacksmithing."
#define MSG_GOSSIP_TEXT_ENCNANTING "Learn Enchanting."
#define MSG_GOSSIP_TEXT_ENGINEERING "Learn Engineering."
#define MSG_GOSSIP_TEXT_HERBALISM "Learn Herbalism."
#define MSG_GOSSIP_TEXT_INSCRIPTION "Learn Inscription"
#define MSG_GOSSIP_TEXT_JEWELCRAFTING "Learn Jewelcrafting."
#define MSG_GOSSIP_TEXT_LEATHERWORKING "Learn Leatherworking."
#define MSG_GOSSIP_TEXT_MINING "Learn Mining."
#define MSG_GOSSIP_TEXT_SKINNING "Learn Skinning."
#define MSG_GOSSIP_TEXT_TAILORING "Learn TAiloring."

#define MSG_GOSSIP_TEXT_RIDING "Learn riding."
#define MSG_GOSSIP_TEXT_COOKING "Learn cooking."
#define MSG_GOSSIP_TEXT_FIRST_AID "Learn first aid."
#define MSG_GOSSIP_TEXT_FISHING "Learn fishing."

#define CONST_HONOR_1  0
#define CONST_HONOR_2  0
#define CONST_ARENA_POINT_1  500
#define CONST_ARENA_POINT_2  1000
#define CONST_ARENA_POINT_3  3000
#define CONST_ARENA_POINT_4  5000


class npc_buffer : public CreatureScript
{
    public: 
    npc_buffer() : CreatureScript("npc_buffer") { }


	void CompleteLearnProfession(Player *player, Creature * _creature, SkillType skill) 
     { 
         if (PlayerAlreadyHasNineProfessions(player) && !IsSecondarySkill(skill)) 
            _creature->MonsterWhisper("Already Trained 2 Proffesion!", player->GetGUID()); 
         else 
         { 
             if (!LearnAllRecipesInProfession(player, skill)) 
                 _creature->MonsterWhisper("Error!", player->GetGUID()); 
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

         if (skillCount >= 2) 
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

             if (skillCount >= 2) 
                 return true; 
         } 

         return false; 
     } 

     bool LearnAllRecipesInProfession(Player *player, SkillType skill) 
     { 
         ChatHandler handler(player->GetSession()); 
         char* skill_name; 

         SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill); 
         skill_name = SkillInfo->name[handler.GetSessionDbcLocale()]; 

         if (!SkillInfo) 
         { 
             TC_LOG_ERROR(LOG_FILTER_GENERAL, "Teleport NPC: received non-valid skill ID (LearnAllRecipesInProfession)"); 
             return false; 
         } 

         LearnSkillRecipesHelper(player, SkillInfo->id); 

         uint16 maxLevel = player->GetPureMaxSkillValue(SkillInfo->id); 
         player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), maxLevel, maxLevel); 
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

             SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
                continue; 

             player->learnSpell(skillLine->spellId, false); 
         } 
     } 

	bool OnGossipHello(Player *player, Creature *_creature)
		{ 
        _creature->MonsterWhisper(MSG_GOSSIP_TEXT_GETTING_STARTED, player->GetGUID());
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_RIDING, GOSSIP_SENDER_MAIN, 35);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MAX_HEALTH, GOSSIP_SENDER_MAIN, 33);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MAX_SKILL, GOSSIP_SENDER_MAIN, 34);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_BUFF_MENU, GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_PROFFESION_MENU, GOSSIP_SENDER_MAIN, 36);
        player->SEND_GOSSIP_MENU (DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID()); 
        return true;
	}
             
	bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 action )
		{
		  if (!player->getAttackers().empty())
	{
		_creature->MonsterWhisper(MSG_ERR_INCOMBAT, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
        return false;
		  }
    switch (action)
	{
	case 2:
        player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_POWER_WORD, GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_BLESSING_OF_KINGS, GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_MARK_OF_THE_WILD, GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_ARCANE_BRILLIANCE, GOSSIP_SENDER_MAIN, 6);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_BLESSING_OF_MIGHT, GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_BLESSING_OF_WISDOM, GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_THORNS, GOSSIP_SENDER_MAIN, 9);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_DIVINE_SPIRIT, GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_SHADOW_PROTECTION, GOSSIP_SENDER_MAIN, 11);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BUFF_STAMINA, GOSSIP_SENDER_MAIN, 12);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_MAIN_MENU, GOSSIP_SENDER_MAIN, 21);
	    player->SEND_GOSSIP_MENU (DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID());
		break;
	case 3:
		// Наложение стойкости (Исправлено)
	    player->CastSpell(player, 69377, true);
		player->CLOSE_GOSSIP_MENU();
	    break;
    case 4:
		 // Наложение Благословение Королей (Исправлено)
		player->CastSpell(player, 56525, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 5:
		 // Наложение Знак дикой природы
		player->CastSpell(player, 1126, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 6:
		 // Наложение Чародейской гениальности Даларана (Исправлено)
		player->CastSpell(player, 61316, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 7:
         // Наложение Благословение могущества (Исправлено)
		player->CastSpell(player, 29381, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 8:
		 // Наложение Благословение мудрости (Исправлено)
		player->CastSpell(player, 56521, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 9:
		 // Наложение Шипов (Исправлено)
		player->CastSpell(player, 53307, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 10:
		 // Наложение Божественный духа (Исправлено)
		player->CastSpell(player, 48074, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 11:
		 // Наложение Защиты от темной магии (Исправлено)
		player->CastSpell(player, 48170, true);
	    player->CLOSE_GOSSIP_MENU();
		break;
	case 12:
		player->CastSpell(player, 48102, true);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 13:
	if (player->GetHonorPoints() < CONST_HONOR_1)
	    {
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение берсерка и отнятие 1 ляма хонора (Доработано)
		player->CastSpell(player, 41924, true);
		player->ModifyHonorPoints(-CONST_HONOR_1);
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 14:
    if (player->GetHonorPoints() < CONST_HONOR_2)
	    {
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение Эгиды Рагнароса(Доработано)
		player->CastSpell(player, 20620, true);
		player->ModifyHonorPoints(-CONST_HONOR_2);
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 15:
    if (player->GetHonorPoints() < CONST_HONOR_2)
	    {
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение Защита Нелтариона(Доработано)
		player->CastSpell(player, 51512, true);
		player->ModifyHonorPoints(-CONST_HONOR_2);
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 16:
	if (player->GetHonorPoints() < CONST_HONOR_2)
		{
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение Благословение А'дала
		player->CastSpell(player, 35076, true);
		player->ModifyHonorPoints(-CONST_HONOR_2);
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 17:
	if (player->GetHonorPoints() < CONST_HONOR_2)
		{
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение Критического срабатывания положительных эффектов
		player->CastSpell(player, 31305, true);
		player->ModifyHonorPoints(-CONST_HONOR_2);
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 18:
	if (player->GetHonorPoints() < CONST_HONOR_2)
		{
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
	    player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение Благословения мистера Пинчи
		player->CastSpell(player, 33053, true);
		player->ModifyHonorPoints(-CONST_HONOR_2);
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 19:
        if (player->GetHonorPoints() < CONST_HONOR_2)
		{
		_creature->MonsterWhisper(MSG_ERR_HONOR, player->GetGUID());
	    player->CLOSE_GOSSIP_MENU();
	}else{
		// Наложение Прозрачности
		player->CastSpell(player, 37802, true);
		player->ModifyHonorPoints(-CONST_HONOR_2);
        player->CLOSE_GOSSIP_MENU();
	case 20:
		player->PlayerTalkClass->ClearMenus();
      player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_RIDING, GOSSIP_SENDER_MAIN, 35);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MAX_HEALTH, GOSSIP_SENDER_MAIN, 33);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MAX_SKILL, GOSSIP_SENDER_MAIN, 34);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_BUFF_MENU, GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_PROFFESION_MENU, GOSSIP_SENDER_MAIN, 36);
        player->SEND_GOSSIP_MENU (DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID()); 
		break; 
	case 21:
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_TITLES_JENKINS, GOSSIP_SENDER_MAIN, 23);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_TITLES_THE_LOVE_FOOL, GOSSIP_SENDER_MAIN, 24);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_TITLES_MERRYMAKER, GOSSIP_SENDER_MAIN, 25);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_TITLES_SCARAB_LORD, GOSSIP_SENDER_MAIN, 26);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_TITLES_THE_NOBLE, GOSSIP_SENDER_MAIN, 27);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_TITLES_OBSIDIAN_SLAYER, GOSSIP_SENDER_MAIN, 28);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_MAIN_MENU, GOSSIP_SENDER_MAIN, 21);
		player->SEND_GOSSIP_MENU (DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID()); 
		break;
	case 22:
		{CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(143);
		if (player->HasTitle(titleInfo))  
		{  
        _creature->MonsterWhisper(MSG_ERR_TITLE, player->GetGUID());   
        player->CLOSE_GOSSIP_MENU();
	    return false;
	}
	if (player->GetArenaPoints() < CONST_ARENA_POINT_1)
		{
         _creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID()); 
		 player->CLOSE_GOSSIP_MENU();
	}else{
        // Даем звание Дженкинс 
		player->SetTitle(titleInfo);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_1);
        player->CLOSE_GOSSIP_MENU();
	}
		}
		break;
	case 23: 
		{CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(135); 
    if (player->HasTitle(titleInfo))   
      {   
       _creature->MonsterWhisper(MSG_ERR_TITLE, player->GetGUID());   
       player->CLOSE_GOSSIP_MENU();
	   return false;
	} 
    if (player->GetArenaPoints() < CONST_ARENA_POINT_1) 
	 {
	    _creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID()); 
		player->CLOSE_GOSSIP_MENU();
	}else{
        // Даем звание Безумно Влюбленный
		player->SetTitle(titleInfo);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_1);
        player->CLOSE_GOSSIP_MENU();
	}
		   }
				break;
	case 24:
		{CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(134); 
	if (player->HasTitle(titleInfo))   
      {   
        _creature->MonsterWhisper(MSG_ERR_TITLE, player->GetGUID());   
        player->CLOSE_GOSSIP_MENU();   
	    return false;
	} 
    if (player->GetArenaPoints() < CONST_ARENA_POINT_1) {
		_creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID()); 
		player->CLOSE_GOSSIP_MENU();
	}else{
        // Даем звание Весельчак
		player->SetTitle(titleInfo);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_1);
        player->CLOSE_GOSSIP_MENU();
	}
		 }
				break;
	case 25:
		{CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(46); 
    if (player->HasTitle(titleInfo))   
      {   
        _creature->MonsterWhisper(MSG_ERR_TITLE, player->GetGUID());   
        player->CLOSE_GOSSIP_MENU();   
	    return false;
	}  
    if (player->GetArenaPoints() < CONST_ARENA_POINT_1) {
        _creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID()); 
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Даем звание Повелитель Скоробеев
		player->SetTitle(titleInfo);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_1);
        player->CLOSE_GOSSIP_MENU();
	}
		 }
				break;
	case 26:
	    {CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(155);
	if (player->HasTitle(titleInfo))   
      {   
        _creature->MonsterWhisper(MSG_ERR_TITLE, player->GetGUID());   
        player->CLOSE_GOSSIP_MENU();   
	    return false;
	}  
    if (player->GetArenaPoints() < CONST_ARENA_POINT_1) {
	    _creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID()); 
	    player->CLOSE_GOSSIP_MENU();
	}else{
	     // Даем звание Чудесный 
		 player->SetTitle(titleInfo);
		 player->ModifyArenaPoints(-CONST_ARENA_POINT_1);
         player->CLOSE_GOSSIP_MENU();
	}
		  }
				break;
	case 27:
	    {CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(139);
	if (player->HasTitle(titleInfo))   
      {   
        _creature->MonsterWhisper(MSG_ERR_TITLE, player->GetGUID());   
        player->CLOSE_GOSSIP_MENU();   
	    return false;
	} 
	if (player->GetArenaPoints() < CONST_ARENA_POINT_1) {
	    _creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID()); 
	    player->CLOSE_GOSSIP_MENU();
	}else{
		// Даем звание Покоритель Обсидианового святилища 
		player->SetTitle(titleInfo);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_2);
        player->CLOSE_GOSSIP_MENU();
	}
		}
				break;
	case 28:
    player->PlayerTalkClass->ClearMenus();
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_RENAME, GOSSIP_SENDER_MAIN, 30);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_CUSTOM, GOSSIP_SENDER_MAIN, 31);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_CHANGE_FACTION, GOSSIP_SENDER_MAIN, 32);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_MAIN_MENU, GOSSIP_SENDER_MAIN, 21);
    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID());
	            break;
	case 29:
	if (player->GetArenaPoints() < CONST_ARENA_POINT_3)
	  {
	    _creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID());
	    player->CLOSE_GOSSIP_MENU();
	}else{
		// Делаем Ренейм
		player->SetAtLoginFlag(AT_LOGIN_RENAME);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_0);
        _creature->MonsterWhisper(MSG_COMPLETE_RENAME, player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
	}
				break;
	case 30:
	if (player->GetArenaPoints() < CONST_ARENA_POINT_0)
	  {
		_creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Делаем Смену внешности
		player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_0);
        _creature->MonsterWhisper(MSG_CUSTOMIZE_COMPLETE, player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
	}
	           break;
	case 31:
		if (player->GetArenaPoints() < CONST_ARENA_POINT_0)
	  {
		_creature->MonsterWhisper(MSG_ERR_ARENA_POINT_1, player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
	}else{
		// Делаем Смену внешности
		player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		player->ModifyArenaPoints(-CONST_ARENA_POINT_0);
        _creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());
        player->CLOSE_GOSSIP_MENU();
	}
		       break; 
	case 32:
		player->SetHealth(player->GetMaxHealth());
		player->CLOSE_GOSSIP_MENU();
      
	           break;
    case 33:
		player->UpdateSkillsToMaxSkillsForLevel();
		player->CLOSE_GOSSIP_MENU();
		break;
    case 34:
	    player->learnSpell(90265, true);
		player->SetSkill(762, 6, 450, 450);
		player->learnSpell(54197, true);
		player->CLOSE_GOSSIP_MENU();
		       break;
	case 35:
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_ALCHEMY, GOSSIP_SENDER_MAIN, 37);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_BLACKSMITHING, GOSSIP_SENDER_MAIN, 38);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_ENCNANTING, GOSSIP_SENDER_MAIN, 39);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_ENGINEERING, GOSSIP_SENDER_MAIN, 40);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_HERBALISM, GOSSIP_SENDER_MAIN, 41);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_INSCRIPTION, GOSSIP_SENDER_MAIN, 42);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_JEWELCRAFTING, GOSSIP_SENDER_MAIN, 43);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_LEATHERWORKING, GOSSIP_SENDER_MAIN, 44);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_MINING, GOSSIP_SENDER_MAIN, 45);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_SKINNING, GOSSIP_SENDER_MAIN, 46);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_TAILORING, GOSSIP_SENDER_MAIN, 47);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_PROFFESION_SECON_MENU, GOSSIP_SENDER_MAIN, 48);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_MAIN_MENU, GOSSIP_SENDER_MAIN, 21);
	    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID());
		       break;
	case 36:
		CompleteLearnProfession(player, _creature, SKILL_ALCHEMY); 
		player->CLOSE_GOSSIP_MENU();
		       break;
	case 37:
		CompleteLearnProfession(player, _creature, SKILL_BLACKSMITHING); 
		player->CLOSE_GOSSIP_MENU();
		break;
	case 38:
		CompleteLearnProfession(player, _creature,  SKILL_ENCHANTING); 
		player->CLOSE_GOSSIP_MENU();
			   break;
	case 39:
		CompleteLearnProfession(player, _creature, SKILL_ENGINEERING); 
		player->CLOSE_GOSSIP_MENU();
		       break;
	case 40:
		CompleteLearnProfession(player, _creature, SKILL_HERBALISM); 
		player->CLOSE_GOSSIP_MENU();
	case 41:
		CompleteLearnProfession(player, _creature, SKILL_INSCRIPTION); 
		player->CLOSE_GOSSIP_MENU();
		       break;
	case 42:
		CompleteLearnProfession(player, _creature, SKILL_JEWELCRAFTING);
		player->CLOSE_GOSSIP_MENU();
			   break;
	case 43:
		CompleteLearnProfession(player, _creature, SKILL_LEATHERWORKING);
		player->CLOSE_GOSSIP_MENU();
		       break;
	case 44:
		CompleteLearnProfession(player, _creature, SKILL_MINING);
		player->CLOSE_GOSSIP_MENU();
			   break;
	case 45:
		CompleteLearnProfession(player, _creature, SKILL_SKINNING);
		player->CLOSE_GOSSIP_MENU();
			   break;
	case 46:
		CompleteLearnProfession(player, _creature, SKILL_TAILORING);
		player->CLOSE_GOSSIP_MENU();
		       break;
	case 47:
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_COOKING, GOSSIP_SENDER_MAIN, 49);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_FIRST_AID, GOSSIP_SENDER_MAIN, 50);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, MSG_GOSSIP_TEXT_FISHING, GOSSIP_SENDER_MAIN, 51);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_MAIN_MENU, GOSSIP_SENDER_MAIN, 21);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID());
		       break;
	case 48:
		CompleteLearnProfession(player, _creature, SKILL_COOKING);
		player->CLOSE_GOSSIP_MENU();
		break;
	case 49:
		CompleteLearnProfession(player, _creature, SKILL_FIRST_AID); 
		player->CLOSE_GOSSIP_MENU();
	    break;
	case 50:
		CompleteLearnProfession(player, _creature, SKILL_FISHING); 
		player->CLOSE_GOSSIP_MENU();
	    break;
	case 51:
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_GNOME_MALE, GOSSIP_SENDER_MAIN, 53);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_GNOME_FEMALE, GOSSIP_SENDER_MAIN, 54);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_HUMAN_MALE, GOSSIP_SENDER_MAIN, 55);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_HUMAN_FEMALE, GOSSIP_SENDER_MAIN, 56);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_BLOOD_ELF_MALE, GOSSIP_SENDER_MAIN, 57);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_BLOOD_ELF_MALE, GOSSIP_SENDER_MAIN, 58);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_TAUREN_MALE, GOSSIP_SENDER_MAIN, 59);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, MSG_GOSSIP_TEXT_MORTH_TAUREN_FEMALE, GOSSIP_SENDER_MAIN, 50);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, MSG_GOSSIP_TEXT_MAIN_MENU, GOSSIP_SENDER_MAIN, 21);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_creature->GetGUID());
		break;
	case 52:
		player->CastSpell(player, 37808, true);
        player->CLOSE_GOSSIP_MENU();
		break;
	case 53:
		player->CastSpell(player, 37809, true);
        player->CLOSE_GOSSIP_MENU();
		break;
	case 54:
		player->CastSpell(player, 35466, true);
        player->CLOSE_GOSSIP_MENU();
		break;
	case 55:
		player->CastSpell(player, 37805, true);
        player->CLOSE_GOSSIP_MENU();
		break;
	case 56:
		player->CastSpell(player, 37807, true);
        player->CLOSE_GOSSIP_MENU();
        break;
	case 57:
		player->CastSpell(player, 37806, true);
        player->CLOSE_GOSSIP_MENU();
        break;
	case 58:
		player->CastSpell(player, 37810, true);
        player->CLOSE_GOSSIP_MENU();
		break;
	case 59:
		player->CastSpell(player, 37811, true);
        player->CLOSE_GOSSIP_MENU();
		break;
	case 60:
		player->RemoveAllAuras();
		player->CLOSE_GOSSIP_MENU();
            }
			}
				return true;
}

   };
void AddSC_npc_buffer()
{
    new npc_buffer;
}