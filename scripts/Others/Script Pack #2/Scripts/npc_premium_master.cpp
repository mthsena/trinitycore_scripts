/*
 * SD Name: Npc Premium Master.
 * SD Custom Script.
 * SD Special For Vip Account Patch.
 * SD Complete 100%.
 * SD Autor (Crispi).
 * SD Data 02.01.2012.
 */

#include "ScriptPCH.h"

#define CONST_ARENA_RENAME 500
#define CONST_ARENA_CUSTOMIZE 500
#define CONST_ARENA_CHANGE_FACTION 1000
#define CONST_ARENA_CHANGE_RACE 1000

#define EMOTE_NO_VIP "Ты не VIP..."
#define EMOTE_COMBAT "Ты в бою!"
#define MSG_CHANGE_FACTION_COMPLETE "Успешно, сделайте релог!!" 
#define MSG_CHANGE_RACE_COMPLETE "Успешно, сделайте релог!!"
#define MSG_MAX_SKILL "Все умения - максимум!"
#define MSG_RIDING_COMPLETE "Ваша верховая езда - максимум!"
#define MSG_RESET_COOLDOWN "Ваши кулдауны обновлены!"
#define MSG_CHARACTER_SAVE_TO_DB "Игрок сохранен!"
#define MSG_CHARACTER_DONATE "Предмет получен!"

class npc_premium_master : public CreatureScript
{
public:
    npc_premium_master() : CreatureScript("npc_premium_master") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
     if (!player->GetSession()->IsPremium() && !player->isGameMaster())
     {
        player->CLOSE_GOSSIP_MENU();
        creature->MonsterWhisper(EMOTE_NO_VIP, player->GetGUID());
        return true;
     }
        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM(5, "Сохранить", GOSSIP_SENDER_MAIN, 1213);
        player->ADD_GOSSIP_ITEM(3, "Сбросить таланты", GOSSIP_SENDER_MAIN, 1207);
        player->ADD_GOSSIP_ITEM(3, "Сбровить кулдауны", GOSSIP_SENDER_MAIN, 1212);
        player->ADD_GOSSIP_ITEM(3, "Все умения на максимум", GOSSIP_SENDER_MAIN, 1204);
        player->ADD_GOSSIP_ITEM(3, "Верховая езда", GOSSIP_SENDER_MAIN, 1211);
        player->ADD_GOSSIP_ITEM(9, "Маунты ->", GOSSIP_SENDER_MAIN, 1208);
        player->ADD_GOSSIP_ITEM(6, "Морфы ->", GOSSIP_SENDER_MAIN, 1203);
        player->ADD_GOSSIP_ITEM(6, "Баффы ->", GOSSIP_SENDER_MAIN, 1206);
        player->ADD_GOSSIP_ITEM(8, "Видео ->", GOSSIP_SENDER_MAIN, 1214);
		  player->ADD_GOSSIP_ITEM(6, "Донат ->", GOSSIP_SENDER_MAIN, 1215);
		  player->ADD_GOSSIP_ITEM(5, "Донат ->", GOSSIP_SENDER_MAIN, 1216);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
         return true;
	}
	
	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 action)
	{
            if (!player->getAttackers().empty())
            {
                creature->MonsterWhisper(EMOTE_COMBAT, player->GetGUID());
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

            player->PlayerTalkClass->ClearMenus();

          switch (action)
          {
            case 1207: // Reset talents
                player->CLOSE_GOSSIP_MENU();
                player->SendTalentWipeConfirm(creature->GetGUID());
                break;
            case 1203: // Morphs
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(5, "Мурлок", GOSSIP_SENDER_MAIN, 499);
                player->ADD_GOSSIP_ITEM(5, "Амброз Искрокрут", GOSSIP_SENDER_MAIN, 500);
                player->ADD_GOSSIP_ITEM(5, "Джонатан Богослов", GOSSIP_SENDER_MAIN, 501);
                player->ADD_GOSSIP_ITEM(5, "Маг из армии Расколотого Солнца", GOSSIP_SENDER_MAIN, 502);
                player->ADD_GOSSIP_ITEM(5, "Ворген", GOSSIP_SENDER_MAIN, 503);
                player->ADD_GOSSIP_ITEM(5, "Паладин", GOSSIP_SENDER_MAIN, 504);
                player->ADD_GOSSIP_ITEM(5, "Крок Гроза Плети", GOSSIP_SENDER_MAIN, 505);
                player->ADD_GOSSIP_ITEM(5, "Железный ремонтник", GOSSIP_SENDER_MAIN, 506);
                player->ADD_GOSSIP_ITEM(5, "Друид", GOSSIP_SENDER_MAIN, 507);
                player->ADD_GOSSIP_ITEM(5, "Жрец", GOSSIP_SENDER_MAIN, 508);
                player->ADD_GOSSIP_ITEM(5, "Паладин", GOSSIP_SENDER_MAIN, 509);
                player->ADD_GOSSIP_ITEM(5, "Разбойник", GOSSIP_SENDER_MAIN, 510);
                player->ADD_GOSSIP_ITEM(5, "Рыцарь Смерти", GOSSIP_SENDER_MAIN, 511);
                player->ADD_GOSSIP_ITEM(5, "Чернокнижник", GOSSIP_SENDER_MAIN, 512);
                player->ADD_GOSSIP_ITEM(5, "Воин", GOSSIP_SENDER_MAIN, 513);
                player->ADD_GOSSIP_ITEM(5, "Маг", GOSSIP_SENDER_MAIN, 514);
                player->ADD_GOSSIP_ITEM(5, "Шаман", GOSSIP_SENDER_MAIN, 515);
                player->ADD_GOSSIP_ITEM(5, "Охотник", GOSSIP_SENDER_MAIN, 516);
                player->ADD_GOSSIP_ITEM(5, "Девушка дреней (White)", GOSSIP_SENDER_MAIN, 517);
                player->ADD_GOSSIP_ITEM(5, "Девушка дреней (Black)", GOSSIP_SENDER_MAIN, 518);
                player->ADD_GOSSIP_ITEM(0, "Деморф", GOSSIP_SENDER_MAIN, 519);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            case 499:
                player->CLOSE_GOSSIP_MENU(); // Starcraft Murlock
                player->SetDisplayId(29348);
                break;
            case 500:
                player->CLOSE_GOSSIP_MENU(); // Ambrose Boltspark
                player->SetDisplayId(28586);
                break;
            case 501:
                player->CLOSE_GOSSIP_MENU(); // Jonathan The Revelator
                player->SetDisplayId(15867);
                break;
            case 502:
                player->CLOSE_GOSSIP_MENU(); // Shattered Sun Magi
                player->SetDisplayId(22959);
                break;
            case 503:
                player->CLOSE_GOSSIP_MENU(); // Worgen
                player->SetDisplayId(657);
                break;
            case 504:
                player->CLOSE_GOSSIP_MENU(); // Pandaren Monk
                player->SetDisplayId(30414);
                break;
            case 505:
                player->CLOSE_GOSSIP_MENU(); // Crok Scourgebane
                player->SetDisplayId(30911);
                break;
            case 506:
                player->CLOSE_GOSSIP_MENU(); // Iron Mender
                player->SetDisplayId(26239);
                break;
            case 507:
                player->CLOSE_GOSSIP_MENU(); // Druid
                player->SetDisplayId(30472);
                break;
            case 508:
                player->CLOSE_GOSSIP_MENU(); // Priest
                player->SetDisplayId(21419);
                break;
            case 509:
                player->CLOSE_GOSSIP_MENU(); // Paladin
                player->SetDisplayId(29774);
                break;
            case 510:
                player->CLOSE_GOSSIP_MENU(); // Rogue
                player->SetDisplayId(30485);
                break;
            case 511:
                player->CLOSE_GOSSIP_MENU(); // Death Knight
                player->SetDisplayId(27153);
                break;
            case 512:
                player->CLOSE_GOSSIP_MENU(); // Warlock
                player->SetDisplayId(30487);
                break;
            case 513:
                player->CLOSE_GOSSIP_MENU(); // Warrior
                player->SetDisplayId(30474);
                break;
            case 514:
                player->CLOSE_GOSSIP_MENU(); // Mage
                player->SetDisplayId(30477);
                break;
            case 515:
                player->CLOSE_GOSSIP_MENU(); // Shaman
                player->SetDisplayId(29768);
                break;
            case 516:
                player->CLOSE_GOSSIP_MENU(); // Hunter
                player->SetDisplayId(21379);
                break;
            case 517:
                player->CLOSE_GOSSIP_MENU(); // Coliseum Champion
                player->SetDisplayId(30634);
                break;
            case 518:
                player->CLOSE_GOSSIP_MENU(); // Coliseum Champion
                player->SetDisplayId(30771);
                break;
            case 519: // Demorph Player (remove all morphs)
                player->CLOSE_GOSSIP_MENU();
                player->DeMorph();
                break;
            case 1206: // Buffs
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(5, "Слово силы: Стойкость", GOSSIP_SENDER_MAIN, 4000);
                player->ADD_GOSSIP_ITEM(5, "Молитва духа", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(5, "Защита от темной магии", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(5, "Великое благословение королей", GOSSIP_SENDER_MAIN, 4003);
                player->ADD_GOSSIP_ITEM(5, "Великое благословение могущества", GOSSIP_SENDER_MAIN,4004);
                player->ADD_GOSSIP_ITEM(5, "Великое благословение мудрости", GOSSIP_SENDER_MAIN, 4005);
                player->ADD_GOSSIP_ITEM(5, "Великое благословение неприкосновенности", GOSSIP_SENDER_MAIN, 4006);
                player->ADD_GOSSIP_ITEM(5, "Чародейский интеллект", GOSSIP_SENDER_MAIN, 4007);
                player->ADD_GOSSIP_ITEM(5, "Ослабление магии", GOSSIP_SENDER_MAIN, 4008);
                player->ADD_GOSSIP_ITEM(5, "Усиление магии", GOSSIP_SENDER_MAIN, 4009);
                player->ADD_GOSSIP_ITEM(5, "Дар дикой природы", GOSSIP_SENDER_MAIN, 4010);
                player->ADD_GOSSIP_ITEM(5, "Шипы", GOSSIP_SENDER_MAIN, 4011);
                player->ADD_GOSSIP_ITEM(5, "Гениальность", GOSSIP_SENDER_MAIN, 4012);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            case 4000: // Power Word Fortitude
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48162, true);
                break;
            case 4001: // Prayer of Spirit
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48074, true);
                break;
            case 4002: // Shadow Protection
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48170, true);
                break;
            case 4003: // Greater Blessing of Kings
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 43223, true);
                break;
            case 4004: // Greater Bleesing of Might
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48934, true);
                break;
            case 4005: // Greater Blessing of Wisdom
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 48938, true);
                break;
            case 4006: // Greater Blessing of Sanctuary
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 25899, true);
                break;
            case 4007: // Arane Intellect
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 36880, true);
                break;
            case 4008: // Dampen Magic
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 43015, true);
                break;
            case 4009: // Amplify Magic
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 43017, true);
                break;
            case 4010: // Gift of the Wild
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 69381, true);
                break;
            case 4011: // Thorns
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 467, true);
                break;
            case 4012: // Brilliance Intellect
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 69994, true);
                break;
            case 1204: // Max Skills
                player->CLOSE_GOSSIP_MENU();
                player->UpdateSkillsToMaxSkillsForLevel();
                creature->MonsterWhisper(MSG_MAX_SKILL, player->GetGUID());
                break;
            case 1208: // Mounts Ground
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(5, "Черный киражский резонирующий кристалл", GOSSIP_SENDER_MAIN, 100);
                player->ADD_GOSSIP_ITEM(5, "Аманийский боевой медведь", GOSSIP_SENDER_MAIN, 101);
                player->ADD_GOSSIP_ITEM(5, "Большой боевой медведь", GOSSIP_SENDER_MAIN, 102);
                player->ADD_GOSSIP_ITEM(5, "Поводья коня смерти", GOSSIP_SENDER_MAIN, 103);
                player->ADD_GOSSIP_ITEM(5, "Поводья огненного боевого коня", GOSSIP_SENDER_MAIN, 104);
                player->ADD_GOSSIP_ITEM(5, "Стремительный пурпурный волк", GOSSIP_SENDER_MAIN, 105);
                player->ADD_GOSSIP_ITEM(5, "Большой кодо Хмельного фестиваля", GOSSIP_SENDER_MAIN, 106);
                player->ADD_GOSSIP_ITEM(5, "Верховой северный волк", GOSSIP_SENDER_MAIN, 107);
                player->ADD_GOSSIP_ITEM(5, "Яйцо волшебного петуха", GOSSIP_SENDER_MAIN, 108);
                player->ADD_GOSSIP_ITEM(5, "Поводья белого северного медведя", GOSSIP_SENDER_MAIN, 109);
                player->ADD_GOSSIP_ITEM(5, "Поводья бурого северного медведя", GOSSIP_SENDER_MAIN, 110);
                player->ADD_GOSSIP_ITEM(5, "Поводья багрового коня смерти", GOSSIP_SENDER_MAIN, 111);
                player->ADD_GOSSIP_ITEM(5, "Поводья повелителя воронов", GOSSIP_SENDER_MAIN, 112);
                player->ADD_GOSSIP_ITEM(5, "Поводья резвого призрачного тигра", GOSSIP_SENDER_MAIN, 113);
                player->ADD_GOSSIP_ITEM(5, "Морская черепаха", GOSSIP_SENDER_MAIN, 114);
                player->ADD_GOSSIP_ITEM(5, "Стремительный ящер Раззаши", GOSSIP_SENDER_MAIN, 115);
                player->ADD_GOSSIP_ITEM(5, "Стремительный белый крылобег", GOSSIP_SENDER_MAIN, 116);
                player->ADD_GOSSIP_ITEM(5, "Стремительная жевра", GOSSIP_SENDER_MAIN, 117);
                player->ADD_GOSSIP_ITEM(5, "Стремительный зульский тигр", GOSSIP_SENDER_MAIN, 118);
                player->ADD_GOSSIP_ITEM(5, "Поводья скакуна Всадника без головы", GOSSIP_SENDER_MAIN, 119);
                player->ADD_GOSSIP_ITEM(5, "Белый шерстистый носорог", GOSSIP_SENDER_MAIN, 120);
                player->ADD_GOSSIP_ITEM(5, "Киражские резонирующие кристаллы", GOSSIP_SENDER_MAIN, 121);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
             case 100: // Black Qiraji Resonating Crystal
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(21176, 1);
                break;
                case 101: // Amani War Bear
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(33809, 1);
                break;
             case 102: // Big Battle Bear
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(38576, 1);
                break;
             case 103: // Deathcharger's Reins
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(13335, 1);
                break;
             case 104: // Fiery Warhorse's Reins
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(30480, 1);
                break;
             case 105: // Swift Burgundy Wolf
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 65646, true); // Cast Metod Because Item (Faction Flag)
                break;
             case 106: // Great Brewfest Kodo
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(37828, 1);
                break;
             case 107: // Horn of the Frostwolf Howler
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 23509, true); // Cast Metod Because Item (Faction Flag)
                break;
             case 108: // Magic Rooster Egg
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(46778, 1);
                break;
             case 109: // Reins of the White Polar Bear
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(43962, 1);
                break;
             case 110: // Reins of the Brown Polar Bear
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(43963, 1);
                break;
             case 111: // Reins of the Crimson Deathcharger
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(52200, 1);
                break;
             case 112: // Reins of the Raven Lord
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(32768, 1);
                break;
             case 113: // Reins of the Swift Spectral Tiger
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(33225, 1);
                break;
             case 114: // Sea Turtle
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(46109, 1);
                break;
             case 115: // Swift Razzashi Raptor
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(19872, 1);
                break;
             case 116: // Swift White Hawkstrider
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(35513, 1);
                break;
             case 117: // Swift Zhevra
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(37719, 1);
                break;
             case 118: // Swift Zulian Tiger
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(19902, 1);
                break;
             case 119: // The Horseman's Reins
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(37012, 1);
                break;
             case 120: // Wooly White Rhino
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(54068, 1);
                break;
             case 121: // Four Qiraji Resonating Crystal
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(21218, 1); // Blue Qiraji Resonating Crystal
                player->AddItem(21323, 1); // Green Qiraji Resonating Crystal
                player->AddItem(21321, 1); // Red Qiraji Resonating Crystal
                player->AddItem(21324, 1); // Yellow Qiraji Resonating Crystal
                break;
             case 1211: // Riding Skills
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, 33389, true); // Apprentice Riding
                player->CastSpell(player, 33392, true); // Journeyman Riding
                player->CastSpell(player, 34092, true); // Expert Riding
                player->CastSpell(player, 34093, true); // Artisan Riding
                player->CastSpell(player, 54197, true); // Allows you to ride flying mounts in Northrend.
                creature->MonsterWhisper(MSG_RIDING_COMPLETE, player->GetGUID());
                break;
             case 1212: // Reset Cooldown
                player->CLOSE_GOSSIP_MENU();
                player->RemoveArenaSpellCooldowns();
                creature->MonsterWhisper(MSG_RESET_COOLDOWN, player->GetGUID());
                break;
             case 1213: // Save Character Online
                player->CLOSE_GOSSIP_MENU();
                player->SaveToDB();
                creature->MonsterWhisper(MSG_CHARACTER_SAVE_TO_DB, player->GetGUID());
                break;
             case 1214: // Movie Menu
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(5, "World of Warcraft", GOSSIP_SENDER_MAIN, 250);
                player->ADD_GOSSIP_ITEM(5, "The Wrath Gate", GOSSIP_SENDER_MAIN, 251);
                player->ADD_GOSSIP_ITEM(5, "Fall of The Lich King", GOSSIP_SENDER_MAIN, 252);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
             case 250: // Classic
                player->CLOSE_GOSSIP_MENU();
                player->SendMovieStart(2);
                break;
             case 251: // The Wrath Gate
                player->CLOSE_GOSSIP_MENU();
                player->SendMovieStart(14);
                break;
             case 252: // Fall of The Lich King
                player->CLOSE_GOSSIP_MENU();
                player->SendMovieStart(16);
                break;
				  case 1215: // Donate Menu
				   player->PlayerTalkClass->ClearMenus();
				   player->ADD_GOSSIP_ITEM(5, "Гербовая накидка льда", GOSSIP_SENDER_MAIN, 300);
                player->ADD_GOSSIP_ITEM(5, "Гербовая накидка пламени", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(5, "Печатка гибели богов", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(5, "Кольцо призывателя духов", GOSSIP_SENDER_MAIN, 303);
                player->ADD_GOSSIP_ITEM(5, "Мерцающая печать", GOSSIP_SENDER_MAIN, 304);
                player->ADD_GOSSIP_ITEM(5, "Кольцо Удручающего насилия", GOSSIP_SENDER_MAIN, 305);
				          player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
						   break;
             case 300: // Гербовая накидка льда
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(23709, 1);
                break;
                case 301: // Гербовая накидка пламени
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(23705, 1);
                break;
             case 302: // Печатка гибели богов
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(45525, 1);
                break;
             case 303: // Кольцо призывателя духов
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(47732, 1);
                break;
             case 304: // Мерцающая печать
                player->CLOSE_GOSSIP_MENU();
                player->AddItem(45297, 1);
                break;
             case 305: // Кольцо Удручающего насилия
               player->CLOSE_GOSSIP_MENU();
                player->AddItem(47054, 1);      
                break;
				case 1216: // меню изменения персонажа
				   player->PlayerTalkClass->ClearMenus();
				   player->ADD_GOSSIP_ITEM(5, "Изменить Фракцию", GOSSIP_SENDER_MAIN, 306);
                player->ADD_GOSSIP_ITEM(5, "Изменить внешность", GOSSIP_SENDER_MAIN, 307);
                player->ADD_GOSSIP_ITEM(5, "Изменить имя", GOSSIP_SENDER_MAIN, 308);
				 player->ADD_GOSSIP_ITEM(5, "Изменить рассу", GOSSIP_SENDER_MAIN, 308);
              
				          player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
						  
						   break;
         case 306: // измнеить фракцию
                player->CLOSE_GOSSIP_MENU();
				 player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
               creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());
                break;
				case 307: // внешность
                player->CLOSE_GOSSIP_MENU();
				 player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
               creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());
			     break;
			   case 308: // измнеить имя
                player->CLOSE_GOSSIP_MENU();
				 player->SetAtLoginFlag(AT_LOGIN_RENAME);
               creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());
                break;
				 case 309: // измнеить рассу
                player->CLOSE_GOSSIP_MENU();
				 player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
               creature->MonsterWhisper(MSG_CHANGE_FACTION_COMPLETE, player->GetGUID());
                break;
           }
           return true;
        }
};

void AddSC_npc_premium_master()
{
    new npc_premium_master;
}
