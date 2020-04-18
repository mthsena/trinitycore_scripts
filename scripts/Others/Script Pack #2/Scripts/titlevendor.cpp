/* Custom Shadowhack Title Vendor */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

#define MAXTITLES 94

struct title
{
    uint8 id;
    char* name;
    uint32 honor;
};

const title titles[MAXTITLES]=
{/*{1, "рядовой", 10000 },
{2, "капрал", 12000},
{3, "сержант", 15000},
{4, "старший сержант",18000},
{5, "старшина", 20000},
{6, "рыцарь", 21000},
{7, "рыцарь-лейтенант", 30000},
{8, "рыцарь-капитан", 35000},
{9, "рыцарь-защитник", 40000},
{10, "лейтенант-командор", 45000},
{11, "командор", 40000},
{12, "маршал", 45000},
{13, "фельдмаршал", 50000},
{14, "главнокомандующий", 70000},
{15, "разведчик", 30000},
{16, "пехотинец", 25000},
{17, "сержант", 15000},
{18, "старший сержант", 18000},
{19, "старшина", 20000},
{20, "каменый страж", 30000},
{21, "кровавый страж", 40000},
{22, "легионер", 40000},
{23, "центурион", 45000},
{24, "защитник", 50000},
{25, "генерал лейтенант", 50000},
{26, "генерал", 45000},
{27, "вождь", 60000},
{28, "верховный вождь", 80000},
{43, "дуэлянт", 25000},
{44, "фаворит", 30000},
{45, "претендент", 35000},*/
{46, "повелитель скарабеев", 60000},
{47, "завоеватель", 80000 },
{53, "Защитник Наару", 75000},
{63, "Из расколотого сонца", 60000},
{64, "Длань Адала", 80000},
{72, "Военачальник", 30000},
{74, "Премудрый", 64000},
{75, "Страж огня", 40000},
{76, "Хранитель огня", 50000},
{77, "Превозносимый", 90000},
{78, "Исследователь", 100000},
{79, "Дипломат", 40000},
{81, "Искатель", 82000},
{83, "Морской дьявол", 90000},
{84, "Шеф-повар", 15000},
{85, "Повелитель штормов", 70000},
{87, "Изумрудный сновидец", 105000},
{89, "Пророк", 80000},
{90, "Тлетворный", 30000},
{91, "Ловчий", 25000},
{92, "Черного клинка", 50000},
{93, "Верховный маг", 70000},
{94, "Вестник войны", 60000},
{95, "Ассасин", 85000},
{96, "Великий алхимик", 20000},
{97, "Великий кузнец", 20000},
{98, "Великий шеф-повар", 20000},
{99, "Великий зачаровыватель", 20000},
{100, "Великий инженер", 20000},
{101, "Доктор", 18000},
{102, "Великий рыболов", 20000},
{103, "Великий травник", 20000},
{104, "Великий начертатель", 20000},
{105, "Великий ювелир", 20000},
{106, "Великий кожевник", 20000},
{107, "Великий мастер горного дела", 20000 },
{108, "Великий мастер снятия шкур", 20000},
{109, "Великий портной", 20000},
{110, "Сын КельТаласа", 90000},
{111, "Сын Аргуса", 95000},
{112, "Сын Хаз Модана", 80000},
{113, "Гномреганский", 65000},
{114, "Львиное сердце", 110000},
{115, "Защитник Элуны", 90000},
{116, "Герой Оргриммара", 87000},
{117, "Хозяин лугов", 20000},
{118, "из черного копья", 50000},
{119, "Отрекшийся", 50000},
{120, "Искатель магии", 40000},
{121, "Покоритель сумрака", 120000},
{122, "Завоеватель Наксрамаса", 120000},
{123, "Герой нордскола", 125000},
{124, "Тыквер", 50000},
{125, "Хранитель мудрости", 60000},
{126, "Сын Альянса", 50000 },
{127, "Сын орды", 50000},
{128, "Всепобеждающий", 100000},
{129, "Защитник ледяных пустошей", 100000},
{130, "Посланник", 30000},
{131, "Серебрянный защитник", 25000},
{132, "Защитник кенария", 25000},
{133, "Хмелевар", 45000},
{134, "Весельчак", 50000},
{135, "Безумно влюбленный", 30000},
{137, "Благотетельница", 25000},
{138, "Благодетель", 25000},
{139, "Покоритель обсидианового святилища", 110000},
{140, "Сумеречный", 110000},
{141, "Беcсмертный", 115000},
{142, "Неумирающий", 115000},
{143, "Дженкинс", 60000},
{144, "Адмирал кровавого паруса", 55000},
{145, "Чокнутый", 70000},
{146, "Экзодарский", 40000},
{147, "Дарнасский", 40000},
{148, "Стальгорнский", 40000 },
{149, "Штормградский", 40000},
{150, "Огримарский", 40000},
{151, "СенДжинский", 35000},
{152, "из Луносвета", 35000 },
{153, "из Громового Утеса", 35000},
{154, "из Подгорода", 35000 },
{155, "Чудесный", 80000},
{156, "Крестоносец", 100000},
{158, "Победивший смерть", 90000},
{159, "Небесный заступник", 95000},
{160, "Завоеватель Ульдуара", 125000},
{161, "Защитник Ульдуара", 125000},
{164, "говорящий со звездами", 97000},
{165, "звездный скиталец", 100000},
{166, "посланник титанов", 100000},
{168, "Странник", 40000},
{170, "Великий крестоносец", 150000},
{171, "Серебрянный заступник", 30000}};

class npc_titlevendor : public CreatureScript
{
    public:
        npc_titlevendor() : CreatureScript("npc_titlevendor") { }
        
    bool OnGossipHello(Player *player, Creature *_Creature)
    {
        int lastindex=0;
        uint8 i=0;
        for (; i<11; ++i)
        {
            char TitleCost[80];
            snprintf( TitleCost, 80,     "%s, cost - %i", titles[lastindex+i].name, titles[lastindex+i].honor );
            player->ADD_GOSSIP_ITEM(11, TitleCost, GOSSIP_SENDER_MAIN, lastindex+i);
        }
        player->ADD_GOSSIP_ITEM( 7, "More titles?", GOSSIP_SENDER_MAIN, 1300+lastindex+i);
        player->ADD_GOSSIP_ITEM( 4, "Nevermind", GOSSIP_SENDER_MAIN, 1224);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        if(action == 1224)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        player->PlayerTalkClass->GetGossipMenu().ClearMenu();
        uint16 lastindex=action>1300?action-1300:0;
        if(lastindex)
        {
            uint8 i=0;
            for (; i<11; ++i)
            {
                if(lastindex+i>MAXTITLES-1)
                    break;
                char TitleCost[80];
                snprintf( TitleCost, 80,     "%s, cost - %i", titles[lastindex+i].name, titles[lastindex+i].honor );
                player->ADD_GOSSIP_ITEM(11, TitleCost, GOSSIP_SENDER_MAIN, lastindex+i);
            }
            
            if(lastindex+i<MAXTITLES-1)
                player->ADD_GOSSIP_ITEM( 7, "More titles?", GOSSIP_SENDER_MAIN, 1300+lastindex+i);
            player->ADD_GOSSIP_ITEM( 4, "Nevermind", GOSSIP_SENDER_MAIN, 1224);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
            return true;
        }
        
        if(player->HasTitle(titles[action].id))
        {
            creature->MonsterWhisper("You allredy have this title", player->GetGUID(), true); 
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        
        if(player->GetHonorPoints()<=titles[action].honor)
        {
            creature->MonsterWhisper("You need more honor points", player->GetGUID(), true);
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        
        player->ModifyHonorPoints(0-titles[action].honor);
        CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(titles[action].id);
        player->SetTitle(titleInfo);
        creature->MonsterWhisper("You got new title!", player->GetGUID(), true); 
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
    
    bool GossipSelect_titlevendor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        // Main menu
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

void AddSC_npc_titlevendor()
{
    new npc_titlevendor;
}
