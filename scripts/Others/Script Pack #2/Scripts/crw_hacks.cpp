#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "World.h"
#include "Util.h"
#include <cstring>


#define SAY_OTHER "Моя работа состоит в изменение вашего персонажа. Как только я делаю свое дело, стоит Вам перезайти - и возле вашего персонажа появится иконка на которую стоит нажать, и Вы все поймете!"
#define DEADLY_GLAD_WYRM "Give me Deadly Gladiator Frostwyrm"
#define FURIOUS_GLAD_WYRM "Give me Furious Gladiator Frostwyrm"
#define RELENTLESS_GLAD_WYRM "Give me Relentless Gladiator Frostwyrm"
#define WRATHFUL_GLAD_WYRM "Give me Wrathful Gladiator Frostwyrm"
#define SAY_ALLERT "You have no title Furious/Relentless/Wrathful/Deadly Gladiator or Gladiator"
#define LEARN "Continue..."
#define SAY_DESERT_1    "You lucky! Deserter deleted!"
#define SAY_DESERT_2    "Sorry, fail deserter deleted :( thanks for you money!"
#define SAY_DESERT_3    "Hm, deserter not deleted :( my 100 gold for you!"
#define MAXRINGS 20

const uint32 rings[MAXRINGS]=
{
    /*MIGHT*/
    52569,
    52570,
    52571,
    52572,
    /*CASTER*/
    50377,
    50384,
    50397,
    50398,
    /*HEAL*/
    50378,
    50386,
    50399,
    50400,
    /*AGILITY*/
    50376,
    50387,
    50401,
    50402,
    /*TANK*/
    50375,
    50388,
    50403,
    50404
};

enum eTrainingDummy
{
    NPC_ADVANCED_TARGET_DUMMY                  = 2674,
    NPC_TARGET_DUMMY                           = 2673,
    NPC_CRAB_800                               = 100675,
    NPC_CRAB_1100                              = 100685,
    NPC_CRAB_1400                              = 100695
};

enum eMenu
{
    CIRCLE_NAGRAND,
    BLADEEDGE,
    GURUBASHI,
    STORMWIND,
    ORGRIMMAR,
    YAICA,
    CD,
    FLY,
    FOOD,
    DESERT,
    SELLER,
    ONE_FLOOR,
    TWO_FLOOR,
    ONE_FLOOR_PHASE,
    TWO_FLOOR_PHASE,
    TALENT
};

enum Spells
{
    SPELL_KILL         = 5,
    SPELL_BLIND        = 21060,
    SPELL_WATER        = 55760,
    SPELL_BOP          = 10278,
    SPELL_BUBLE        = 13874,
    SPELL_HEX          = 51514,
    SPELL_SHEEP        = 61721,
    SPELL_DES          = 26013,
    SPELL_HEX1         = 66054,
    SPELL_FIX          = 65632,
    SHEEP              = 61025,
    SCALE              = 4335,
    bs_spell           = 65282,
    jc_spell           = 65286,
    eg_spell           = 61464,
    ec_spell           = 65285,
    lw_spell           = 65284
};

enum eRings
{
    RING_MIGHT_1      = 52569,
    RING_MIGHT_2      = 52570,
    RING_MIGHT_3      = 52571,
    RING_MIGHT_4      = 52572,
    RING_CASTER_1     = 50377,
    RING_CASTER_2     = 50384,
    RING_CASTER_3     = 50397,
    RING_CASTER_4     = 50398,
    RING_HEAL_1       = 50378,
    RING_HEAL_2       = 50386,
    RING_HEAL_3       = 50399,
    RING_HEAL_4       = 50400,
    RING_AGILITY_1    = 50376,
    RING_AGILITY_2    = 50387,
    RING_AGILITY_3    = 50401,
    RING_AGILITY_4    = 50402,
    RING_TANK_1       = 50375,
    RING_TANK_2       = 50388,
    RING_TANK_3       = 50403,
    RING_TANK_4       = 50404
};

enum eTitles
{
    TITLE_GLADIATOR                = 29,
    TITLE_DEADLY_GLADIATOR         = 56,
    TITLE_FURIOUS_GLADIATOR        = 132,
    TITLE_RELENTLESS_GLADIATOR     = 134,
    TITLE_WRATHFUL_GLADIATOR       = 142
};

/*<! --------------------------------- ! >*/
/*######
### VENDOR FOR GLADIATORS ###
######*/
/*<! --------------------------------- ! >*/

class npc_gladiator_vendor : public CreatureScript
{
    public:
        npc_gladiator_vendor() : CreatureScript("npc_gladiator_vendor") { }
        
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((pPlayer->HasTitle(TITLE_RELENTLESS_GLADIATOR)) || (pPlayer->HasTitle(TITLE_WRATHFUL_GLADIATOR)) || (pPlayer->HasTitle(TITLE_FURIOUS_GLADIATOR)) || (pPlayer->HasTitle(TITLE_DEADLY_GLADIATOR)) || (pPlayer->HasTitle(TITLE_GLADIATOR)))
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, DEADLY_GLAD_WYRM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, FURIOUS_GLAD_WYRM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, RELENTLESS_GLAD_WYRM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, WRATHFUL_GLAD_WYRM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        }
        else
            pCreature->MonsterWhisper(SAY_ALLERT, pPlayer->GetGUID(), true);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
            {
                if(player->GetMoney()>=7000000)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 46708, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 46708, true);
                        player->CLOSE_GOSSIP_MENU();
                        break;
                    }
                    else
                        player->SendEquipError(msg,NULL,NULL);
            
                    player->ModifyMoney(-7000000);
                    creature->MonsterSay("Deadly Gladiator Frostwyrm у Вас в инвентаре!", LANG_UNIVERSAL, NULL);
                    break;
                }
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);
            }
            case GOSSIP_ACTION_INFO_DEF+2:
            {
                if(player->GetMoney()>=7000000)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 46171, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 46171, true);
                        player->CLOSE_GOSSIP_MENU();
                        break;
                    }
                    else
                        player->SendEquipError(msg,NULL,NULL);
            
                    player->ModifyMoney(-7000000);
                    creature->MonsterSay("Furious Gladiator Frostwyrm у Вас в инвентаре!", LANG_UNIVERSAL, NULL);
                    break;
                }    
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);
            }
            case GOSSIP_ACTION_INFO_DEF+3:
            {
                if(player->GetMoney()>=7000000)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 461700, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 461700, true);
                        player->CLOSE_GOSSIP_MENU();
                        break;
                    }
                    else
                        player->SendEquipError(msg,NULL,NULL);
            
                    player->ModifyMoney(-7000000);
                    creature->MonsterSay("Relentless Gladiator Frostwyrm у Вас в инвентаре!", LANG_UNIVERSAL, NULL);
                    break;
                }
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);
            }
            case GOSSIP_ACTION_INFO_DEF+4:
            {
                if(player->GetMoney()>=7000000)
                {
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75570, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75570, true);
                        player->CLOSE_GOSSIP_MENU();
                        break;
                    }
                    else
                        player->SendEquipError(msg,NULL,NULL);
            
                    player->ModifyMoney(-7000000);
                    creature->MonsterSay("Wrathful Gladiator Frostwyrm у Вас в инвентаре!", LANG_UNIVERSAL, NULL);
                    break;
                }
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);
            }
        }
        return true;
    }
    
    bool GossipSelect_npc_gladiator_vendor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### TITLE MASTER ###
######*/
/*<! --------------------------------- ! >*/

class npc_title_master : public CreatureScript
{
    public:
        npc_title_master() : CreatureScript("npc_title_master") { }
        
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->HasItemCount(76000, 1))
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Я готов получить Wrathful Gladiator'a", GOSSIP_SENDER_MAIN, 1);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 10);
        }
        else if (pPlayer->HasItemCount(76001, 1))
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Я готов получить Gladiator'a", GOSSIP_SENDER_MAIN, 2);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 10);
        }
        else if (pPlayer->HasItemCount(76002, 1))
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Я готов получить Duelist'a", GOSSIP_SENDER_MAIN, 3);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 10);
        }
        else if (pPlayer->HasItemCount(76003, 1))
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Я готов получить Challenger'a", GOSSIP_SENDER_MAIN, 4);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 10);
        }
        else if ((pPlayer->HasTitle(TITLE_RELENTLESS_GLADIATOR)) || (pPlayer->HasTitle(TITLE_WRATHFUL_GLADIATOR)) || (pPlayer->HasTitle(TITLE_FURIOUS_GLADIATOR)) || (pPlayer->HasTitle(TITLE_DEADLY_GLADIATOR)) || (pPlayer->HasTitle(TITLE_GLADIATOR)))
            pCreature->MonsterWhisper("Вы уже стали гладиатором, дважды ето сделать нельзя :)", pPlayer->GetGUID(), true);
        else
            pCreature->MonsterWhisper("Вы не достоины стать одним из гладиаторов!", pPlayer->GetGUID(), true);
            
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        CharTitlesEntry const* titleWrathful = sCharTitlesStore.LookupEntry(177);
        CharTitlesEntry const* titleGlad = sCharTitlesStore.LookupEntry(42);
        CharTitlesEntry const* titleDuelist = sCharTitlesStore.LookupEntry(43);
        CharTitlesEntry const* titleChallenger = sCharTitlesStore.LookupEntry(45);
        switch (action)
        {
            case 1:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(76000, 1))
                {
                    player->DestroyItemCount(76000, 1, true);
                    player->SetTitle(titleWrathful);
                    player->SetTitle(titleGlad);
                }
                else
                    creature->MonsterWhisper("Вы не достоины стать одним из гладиаторов!", player->GetGUID(), true);
                break;
            }
            case 2:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(76001, 1))
                {
                    player->DestroyItemCount(76001, 1, true);
                    player->SetTitle(titleGlad);
                }
                else
                    creature->MonsterWhisper("Вы не достоины стать одним из гладиаторов!", player->GetGUID(), true);
                break;
            }
            case 3:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(76002, 1))
                {
                    player->DestroyItemCount(76002, 1, true);
                    player->SetTitle(titleDuelist);
                }
                else
                    creature->MonsterWhisper("Вы не достоины стать одним из гладиаторов!", player->GetGUID(), true);
                break;
            }
            case 4:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(76003, 1))
                {
                    player->DestroyItemCount(76003, 1, true);
                    player->SetTitle(titleChallenger);
                }
                else
                    creature->MonsterWhisper("Вы не достоины стать одним из гладиаторов!", player->GetGUID(), true);
                break;
            }
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
    
    bool GossipSelect_npc_title_master(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        // Main menu
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};
                

/*<! --------------------------------- ! >*/
/*######
### ARENA MASTER ###
######*/
/*<! --------------------------------- ! >*/

class arena_master : public CreatureScript
{
    public:
        arena_master() : CreatureScript("arena_master") { }
        
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->PlayerTalkClass->GetGossipMenu().ClearMenu();
        if ((pPlayer->HasTitle(29)) || (pPlayer->HasTitle(30)) || (pPlayer->HasTitle(31)) || (pPlayer->HasTitle(37)) || (pPlayer->HasTitle(56)) || (pPlayer->HasTitle(132)) || 
        (pPlayer->HasTitle(134)) || (pPlayer->HasTitle(142)) || (pPlayer->HasTitle(28)) || (pPlayer->HasTitle(14)))
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Elite Shop WSG Arena Gamers!", GOSSIP_SENDER_MAIN, 30);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Что такое 'WAM'?", GOSSIP_SENDER_MAIN, 6);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Я - победитель турнира!", GOSSIP_SENDER_MAIN, 40);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Обменять хонор -> золото", GOSSIP_SENDER_MAIN, 4);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Обменять золото -> хонор", GOSSIP_SENDER_MAIN, 3);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Обменять Arena Points -> WAM (Normal)", GOSSIP_SENDER_MAIN, 15);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Обменять Arena Points -> WAM (Heroic)", GOSSIP_SENDER_MAIN, 16);
        }
        else
        {
            pPlayer->ADD_GOSSIP_ITEM( 10, "Получить титул Rival для доступа к магазину - 250 WAM", GOSSIP_SENDER_MAIN, 5);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Что я смогу увидеть в магазине?", GOSSIP_SENDER_MAIN, 17);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Что такое 'WAM'?", GOSSIP_SENDER_MAIN, 6);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Я - победитель турнира!", GOSSIP_SENDER_MAIN, 40);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Обменять хонор -> золото", GOSSIP_SENDER_MAIN, 4);
            pPlayer->ADD_GOSSIP_ITEM( 10, "Обменять золото -> хонор", GOSSIP_SENDER_MAIN, 3);
        }
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch(action)
        {
            case 3:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Да", GOSSIP_SENDER_MAIN, 11);
                player->ADD_GOSSIP_ITEM( 10, "Нет", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9); 
                player->SEND_GOSSIP_MENU(1500017, creature->GetGUID()); 
                break;
            }
            case 4:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Да", GOSSIP_SENDER_MAIN, 12);
                player->ADD_GOSSIP_ITEM( 10, "Нет", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9); 
                player->SEND_GOSSIP_MENU(1500016, creature->GetGUID()); 
                break;
            }
            case 5:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Да", GOSSIP_SENDER_MAIN, 10);
                player->ADD_GOSSIP_ITEM( 10, "Нет", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9); 
                player->SEND_GOSSIP_MENU(1500011, creature->GetGUID()); 
                break;
            }
            case 6:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                player->SEND_GOSSIP_MENU(1500012, creature->GetGUID()); 
                break;
            }
            case 7:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Обменять АП -> WAM (H)", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM( 10, "Обменять АП -> WAM (N)", GOSSIP_SENDER_MAIN, 14); 
                break;
            }
            case 8:
            {
                player->CLOSE_GOSSIP_MENU(); break;
            }
            case 9:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if ((player->HasTitle(29)) || (player->HasTitle(30)) || (player->HasTitle(31)) || (player->HasTitle(37)) || (player->HasTitle(56)) || (player->HasTitle(132)) || 
                    (player->HasTitle(134)) || (player->HasTitle(142)) || (player->HasTitle(28)) || (player->HasTitle(14)))
                {
                    player->ADD_GOSSIP_ITEM( 10, "Elite Shop WSG Arena Gamers!", GOSSIP_SENDER_MAIN, 30);
                    player->ADD_GOSSIP_ITEM( 10, "Что такое 'WAM'?", GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM( 10, "Я - победитель турнира!", GOSSIP_SENDER_MAIN, 40);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM( 10, "Обменять хонор -> золото", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM( 10, "Обменять золото -> хонор", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM( 10, "Обменять Arena Points -> WAM (Normal)", GOSSIP_SENDER_MAIN, 15);
                    player->ADD_GOSSIP_ITEM( 10, "Обменять Arena Points -> WAM (Heroic)", GOSSIP_SENDER_MAIN, 16);
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Получить титул Rival для доступа к магазину - 250 WAM", GOSSIP_SENDER_MAIN, 5);
                    player->ADD_GOSSIP_ITEM( 10, "Что я смогу увидеть в магазине?", GOSSIP_SENDER_MAIN, 17);
                    player->ADD_GOSSIP_ITEM( 10, "Что такое 'WAM'?", GOSSIP_SENDER_MAIN, 6);
                    player->ADD_GOSSIP_ITEM( 10, "Я - победитель турнира!", GOSSIP_SENDER_MAIN, 40);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->ADD_GOSSIP_ITEM( 10, "Обменять хонор -> золото", GOSSIP_SENDER_MAIN, 4);
                    player->ADD_GOSSIP_ITEM( 10, "Обменять золото -> хонор", GOSSIP_SENDER_MAIN, 3);
                }
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            case 10:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75556, 250))
                {
                    CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(44);
                    player->DestroyItemCount(75556, 250, true);
                    player->SetTitle(titleInfo);
                    creature->MonsterSay("Вы получили титул Rival, который позволит Вам пользоваться моим магазином!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); 
                    break;
                }
                else
                {
                    creature->MonsterSay("У вас не достаточно WAM!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;
                }
                break;
            }
            case 11:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if(player->GetMoney()>=15000000)
                {
                    player->ModifyMoney(-25000000);
                    player->ModifyHonorPoints(5000);
                    creature->MonsterSay("Обмен золота на хонор закончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);        
                    player->SEND_GOSSIP_MENU(1500018, creature->GetGUID());
                }
                break;
            }
            case 12:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if(player->GetHonorPoints()>=100000)
                {
                    player->ModifyHonorPoints(-120000);
                    player->ModifyMoney(10000000);
                    creature->MonsterSay("Обмен хонора на золото закончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);        
                    player->SEND_GOSSIP_MENU(1500019, creature->GetGUID());
                }
                break;
            }
            case 13:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->GetArenaPoints()>=1350)
                {
                    player->ModifyArenaPoints(-1350);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75556, 10, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75556, 10, true);
                    }
                    creature->MonsterSay("Обмена AP -> Arena Money (Heroic) окончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                    player->SEND_GOSSIP_MENU(1500021, creature->GetGUID());
                    break;
                }
                break;
            }
            case 14:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->GetArenaPoints()>=1150)
                {
                    player->ModifyArenaPoints(-1150);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75557, 10, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75557, 10, true);
                    }
                    creature->MonsterSay("Обмена AP -> Arena Money (Normal) окончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                    player->SEND_GOSSIP_MENU(1500021, creature->GetGUID());
                    break;
                }
                break;
            }
            case 15:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Да", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM( 10, "Нет", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9); 
                player->SEND_GOSSIP_MENU(1500022, creature->GetGUID()); 
                break;
            }
            case 16:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Да", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM( 10, "Нет", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9); 
                player->SEND_GOSSIP_MENU(1500023, creature->GetGUID()); 
                break;
            }
            case 17:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->SEND_GOSSIP_MENU(1500014, creature->GetGUID()); 
                break;
            }
            case 21:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75556, 50))
                {
                    player->DestroyItemCount(75556, 50, true);
                    player->ModifyHonorPoints(50000);
                    creature->MonsterSay("Обмен хонора закончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(1500013, creature->GetGUID()); 
                    break;
                }
                break;
            }
            case 22:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75556, 125))
                {
                    player->DestroyItemCount(75556, 125, true);
                
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 49426, 40, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 49426, 40, true);
                    }
                    creature->MonsterSay("Обмена эмблем закончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                    player->SEND_GOSSIP_MENU(1500013, creature->GetGUID());
                    break;
                }
                break;
            }
            case 23:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75556, 100))
                {
                    player->DestroyItemCount(75556, 100, true);
                    player->ModifyMoney(7000000);
                    creature->MonsterSay("Обмен золота окончен!", LANG_UNIVERSAL, NULL);
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    break;
                }
                else
                {
                    player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                    player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                    player->SEND_GOSSIP_MENU(1500013, creature->GetGUID()); 
                    break;
                }
                break;
            }
            case 25:
            {
                player->PrepareQuestMenu(creature->GetGUID());
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->SEND_GOSSIP_MENU(creature->GetEntry(), creature->GetGUID());
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                break;
            }
            case 30:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Обменять 50 WAM -> 50к хонора", GOSSIP_SENDER_MAIN, 21);
                player->ADD_GOSSIP_ITEM( 10, "Обменять 125 WAM -> 40 Emblem of Frost", GOSSIP_SENDER_MAIN, 22);
                player->ADD_GOSSIP_ITEM( 10, "Обменять 100 WAM -> 7000 gold", GOSSIP_SENDER_MAIN, 23);
                player->ADD_GOSSIP_ITEM( 10, "ПвЕ-санинка", GOSSIP_SENDER_MAIN, 25);
                player->ADD_GOSSIP_ITEM( 10, "Доступ к Gear Update 2", GOSSIP_SENDER_MAIN, 32);
                player->ADD_GOSSIP_ITEM( 10, "Покупка достижений >- в разработке -<", GOSSIP_SENDER_MAIN, 24);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;
            }
            case 31:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                player->SEND_GOSSIP_MENU(1500015, creature->GetGUID()); 
                break;
            }
            case 32:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Так точно, Кэп!", GOSSIP_SENDER_MAIN, 33);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8); 
                player->SEND_GOSSIP_MENU(1500020, creature->GetGUID()); 
                break;
            }
            case 33:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(47464, 1))
                {
                    ItemPosCountVec dest;
                    player->DestroyItemCount(47464, 1, true);
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75558, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75558, 1, true);
                    }
                }
                else if (player->HasItemCount(47477, 1))
                {
                    ItemPosCountVec dest;
                    player->DestroyItemCount(47477, 1, true);
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75558, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75558, 1, true);
                    }
                }
                else if (player->HasItemCount(47432, 1))
                {
                    ItemPosCountVec dest;
                    player->DestroyItemCount(47432, 1, true);
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75558, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75558, 1, true);
                    }
                }
                else if (player->HasItemCount(45931, 1))
                {
                    ItemPosCountVec dest;
                    player->DestroyItemCount(45931, 1, true);
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75558, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75558, 1, true);
                    }
                }
                else if (player->HasItemCount(50339, 1))
                {
                    ItemPosCountVec dest;
                    player->DestroyItemCount(50339, 1, true);
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 75558, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, 75558, 1, true);
                    }
                }
                else
                {
                    player->CastSpell(player,11027,false); 
                    creature->MonsterSay("Попытались Вы нас обмануть, а мы Вас в ... посылаем!", LANG_UNIVERSAL, NULL);
                    return true;
                }
                break;
            }
            case 40:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->ADD_GOSSIP_ITEM( 10, "Информация", GOSSIP_SENDER_MAIN, 31);
                player->ADD_GOSSIP_ITEM( 10, "Получение титула 'Merciles Gladiator'", GOSSIP_SENDER_MAIN, 132);
                player->ADD_GOSSIP_ITEM( 10, "Вернуться в главное меню", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( 10, "Закрыть меню", GOSSIP_SENDER_MAIN, 8);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                break;
            }
            break;
        }
        return true;
    }
    
    bool GossipSelect_arena_master(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### NPC CUSTOMIZER ###
######*/
/*<! --------------------------------- ! >*/

class npc_customizer : public CreatureScript
{
    public:
        npc_customizer() : CreatureScript("npc_customizer") { }
        
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->PlayerTalkClass->GetGossipMenu().ClearMenu();
        if ((pPlayer->GetMoney()>=50000000) || (pPlayer->HasItemCount(75556, 50)))
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Хочу изменить внешность своего персонажа!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Хочу изменить расу своего персонажа!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Хочу изменить фракцию своего персонажа!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Телепортироваться к парикмахерской?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "В чем заключается моя работа?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        }
        else
            pCreature->MonsterWhisper("У вас недостаточно золота, или нету 50 WAM!", LANG_UNIVERSAL, NULL);
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        QueryResult result;

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if(player)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Готовы ли вы потратить 5000 золота?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Готовы ли вы потратить 50 WSG Arena Money?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); break;
                }
            }
            case GOSSIP_ACTION_INFO_DEF+2:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if(player->HasItemCount(75556,15))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Да.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Нет.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); break;
                }
                else
                {
                    creature->MonsterSay("У вас недостаточно WarSong Money", LANG_UNIVERSAL, NULL);
                    player->CLOSE_GOSSIP_MENU(); break;
                }
            }
            case GOSSIP_ACTION_INFO_DEF+4:
            {
                player->TeleportTo(571, 5890.344f, 621.37f, 649.381f, 5.68f);
                player->CLOSE_GOSSIP_MENU(); break;
            }
            case GOSSIP_ACTION_INFO_DEF+5:
            {
                creature->MonsterSay(SAY_OTHER, LANG_UNIVERSAL, NULL);
                player->CLOSE_GOSSIP_MENU(); break;
            }
            case GOSSIP_ACTION_INFO_DEF + 6:
            {
                player->CLOSE_GOSSIP_MENU(); break;
            }
            case GOSSIP_ACTION_INFO_DEF + 7:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75556, 50))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Да.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Нет.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); break;
                }
                else
                {
                    creature->MonsterSay("У вас не хватает WSG Arena Money :(", LANG_UNIVERSAL, NULL); 
                    player->CLOSE_GOSSIP_MENU(); break;
                }
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 8:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if(player)
                {
                    if (player->HasItemCount(75556, 50))
                    {
                        player->DestroyItemCount(75556, 50, true);
                        player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                        result = CharacterDatabase.PQuery("UPDATE characters SET at_login = at_login | '8' WHERE guid = '%u'",player->GetGUIDLow());
                        creature->MonsterSay("Операция выполнена успешно, следует перезайти!", LANG_UNIVERSAL, NULL); 
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                    else
                    {
                        creature->MonsterSay("У вас не хватает WSG Arena Money :(", LANG_UNIVERSAL, NULL); 
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                }
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 9:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75560, 15))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Да.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Нет.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); break;
                }
                else
                {
                    creature->MonsterSay("У вас не хватает WarSong Money :(", LANG_UNIVERSAL, NULL); 
                    player->CLOSE_GOSSIP_MENU(); break;
                }
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 10:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if (player->HasItemCount(75560, 15))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Да.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Нет.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); break;
                }
                else
                {
                    creature->MonsterSay("У вас не хватает WarSong Money :(", LANG_UNIVERSAL, NULL); 
                    player->CLOSE_GOSSIP_MENU(); break;
                }
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 11:
            {
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                if(player)
                {
                    if (player->HasItemCount(75560, 15))
                    {
                        player->DestroyItemCount(75560, 15, true);
                        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                        result = CharacterDatabase.PQuery("UPDATE characters SET at_login = at_login | '128' WHERE guid = '%u'",player->GetGUIDLow());
                        creature->MonsterSay("Операция выполнена успешно, следует перезайти!", LANG_UNIVERSAL, NULL); 
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                    else
                    {
                        creature->MonsterSay("У вас не хватает WarSong Money :(", LANG_UNIVERSAL, NULL); 
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                }
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 12:
            {
                if(player)
                {
                    player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                    if (player->HasItemCount(75560, 15))
                    {
                        player->DestroyItemCount(75560, 15, true);
                        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                        result = CharacterDatabase.PQuery("UPDATE characters SET at_login = at_login | '64' WHERE guid = '%u'",player->GetGUIDLow());
                        creature->MonsterSay("Операция выполнена успешно, следует перезайти!", LANG_UNIVERSAL, NULL); 
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                    else
                    {
                        creature->MonsterSay("У вас не хватает WarSong Money :(", LANG_UNIVERSAL, NULL); 
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                }
                break;
            }
            case GOSSIP_ACTION_INFO_DEF+13:
            {
                if((player->GetMoney()>=50000000) || (player->HasItemCount(75556, 50)))
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Да.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Нет.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID()); break;
                }
                else
                {
                    creature->MonsterSay("У вас недостаточно золота, или нету 50 WAM!!", LANG_UNIVERSAL, NULL);
                    player->CLOSE_GOSSIP_MENU(); break;
                }
            }
            case GOSSIP_ACTION_INFO_DEF + 14:
            {
                if (player->GetMoney()>=50000000)
                {
                    player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                    result = CharacterDatabase.PQuery("UPDATE characters SET at_login = at_login | '8' WHERE guid = '%u'",player->GetGUIDLow());
                    player->ModifyMoney(-50000000);
                    creature->MonsterSay("Операция выполнена успешно, следует перезайти!", LANG_UNIVERSAL, NULL); 
                    player->CLOSE_GOSSIP_MENU(); break;
                }
                else
                {
                    player->ModifyMoney(-50000000);
                    player->ModifyHonorPoints(-55000);
                }
    
            }
            break;
        }
        return true;
    }
    
    bool GossipSelect_npc_customizer(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### PVP CUSTOM PORTER AND FUNNY NPC ###
######*/
/*<! --------------------------------- ! >*/

class pvp_porter : public CreatureScript
{
    public:
        pvp_porter() : CreatureScript("pvp_porter") { }
        
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((pPlayer->GetZoneId() == 14 && pPlayer->GetTeam() == ALLIANCE) || (pPlayer->GetZoneId() == 12 && pPlayer->GetTeam() == HORDE))
        {
            pCreature->CastSpell(pPlayer,SPELL_KILL,false);
            pCreature->MonsterWhisper("НЕУДАЧНИКАМ НЕТ МЕСТА В НАШЕМ МИРЕ!", LANG_UNIVERSAL, NULL);
        }
        else
        {
            if (pPlayer->GetTeam() == ALLIANCE)
            {
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Nagrand PvP Arena", GOSSIP_SENDER_MAIN, CIRCLE_NAGRAND);
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Blade Edge PvP Arena", GOSSIP_SENDER_MAIN, BLADEEDGE);
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Gurubashi PvP Arena", GOSSIP_SENDER_MAIN, GURUBASHI);
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Stormwind", GOSSIP_SENDER_MAIN, STORMWIND);
                pPlayer->ADD_GOSSIP_ITEM(0, "Попытайте удачу!", GOSSIP_SENDER_MAIN, YAICA);
                pPlayer->ADD_GOSSIP_ITEM(0, "Я хочу снять колдауны.", GOSSIP_SENDER_MAIN, CD);
                pPlayer->ADD_GOSSIP_ITEM(0, "Хотелось бы полетать!", GOSSIP_SENDER_MAIN, FLY);
                pPlayer->ADD_GOSSIP_ITEM(0, "Восстановить показатели Health / Mana", GOSSIP_SENDER_MAIN, FOOD);
                pPlayer->ADD_GOSSIP_ITEM(0, "Снять ауру [Дезертир] (600 gold & 30% chance)", GOSSIP_SENDER_MAIN, DESERT);
                pPlayer->ADD_GOSSIP_ITEM(0, "Телепорт в Darkshore (Rel Seller)", GOSSIP_SENDER_MAIN, SELLER);
            }
            if (pPlayer->GetTeam() == HORDE)
            {
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Nagrand PvP Arena", GOSSIP_SENDER_MAIN, CIRCLE_NAGRAND);
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Blade Edge PvP Arena", GOSSIP_SENDER_MAIN, BLADEEDGE);
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Gurubashi PvP Arena", GOSSIP_SENDER_MAIN, GURUBASHI);
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Orgrimmar", GOSSIP_SENDER_MAIN, ORGRIMMAR);
                pPlayer->ADD_GOSSIP_ITEM(0, "Попытайте удачу!", GOSSIP_SENDER_MAIN, YAICA);
                pPlayer->ADD_GOSSIP_ITEM(0, "Я хочу снять колдауны. [2 BKM]", GOSSIP_SENDER_MAIN, CD);
                pPlayer->ADD_GOSSIP_ITEM(0, "Хотелось бы полетать!", GOSSIP_SENDER_MAIN, FLY);
                pPlayer->ADD_GOSSIP_ITEM(0, "Восстановить показатели Health / Mana [2 BKM]", GOSSIP_SENDER_MAIN, FOOD);
                pPlayer->ADD_GOSSIP_ITEM(0, "Снять ауру [Дезертир] (600 gold & 30% chance)", GOSSIP_SENDER_MAIN, DESERT);
                pPlayer->ADD_GOSSIP_ITEM(0, "Телепорт в Darkshore (Rel Seller)", GOSSIP_SENDER_MAIN, SELLER);
            }
        }
        pPlayer->SEND_GOSSIP_MENU(1500009,pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {

        if(sender != GOSSIP_SENDER_MAIN) return true;
        if(!player->getAttackers().empty()) return true;
    
        if (player->HasAura(SPELL_AURA_MOD_STEALTH))
        {
            creature->DealDamage(player,player->GetHealth()/2,NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            player->RemoveAurasByType(SPELL_AURA_MOD_STEALTH);
            player->CLOSE_GOSSIP_MENU();
        }
        else
        switch(action)
        {
            case CIRCLE_NAGRAND:
                player->TeleportTo(530, -2039.237f, 6655.946f, 13.05f, 0.57f);
                player->CLOSE_GOSSIP_MENU(); break;
            case BLADEEDGE:
                player->TeleportTo(530, 2838.790f, 5929.032f, 11.08f, 5.58f);
                player->CLOSE_GOSSIP_MENU(); break;
            case GURUBASHI:
                player->TeleportTo(0, -13261.364f, 160.399f, 36.32f, 0.57f);
                player->CLOSE_GOSSIP_MENU(); break;
            case STORMWIND:
                player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); break;
            case ORGRIMMAR:
                player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); break;
            case SELLER:
                player->TeleportTo(1, 7300.33f, -1524.25f, 179.84f, 1.34f);
                player->CLOSE_GOSSIP_MENU(); break;    
            case CD:
                if (player->duel)
                {
                    creature->CastSpell(player,11027,false);
                    creature->CastSpell(player,46014,false);
                    creature->CastSpell(player,59881,false);
                    creature->MonsterSay("OHOHOHO, NO ABUSING CD LOL NOOB! BYE BYE! HAHAHAHH...", LANG_UNIVERSAL, NULL); break;
                }
                else
                {
                    if (player->getLevel() >= 70)
                    {
                        if (player->HasItemCount(75555, 2))
                        {
                            player->DestroyItemCount(75555, 2, true);
                            creature->CastSpell(player,59881,false);
                            player->RemoveArenaSpellCooldowns();
                            creature->MonsterSay("COOLDOWN DELETED", LANG_UNIVERSAL, NULL);
                            break;
                        }
                        else
                            creature->MonsterSay("Вам не хватает BG Killing Mark's (требуется 2)", LANG_UNIVERSAL, NULL); break;
                    }
                    else
                    {
                        creature->CastSpell(player,59881,false);
                        player->RemoveArenaSpellCooldowns();
                        creature->MonsterSay("COOLDOWN DELETED", LANG_UNIVERSAL, NULL); break;
                    }
                }
                player->CLOSE_GOSSIP_MENU(); break;
            case FLY:
                switch (rand()%2)
                {
                    case 0:
                        creature->CastSpell(player,11027,false); 
                        creature->MonsterSay("GGOOOODDD LUUUCCCKKK!", LANG_UNIVERSAL, NULL);
                        break;
                    case 1:
                        player->CastSpell(player,46014,false); 
                        creature->MonsterSay("GGOOOODDD LUUUCCCKKK!", LANG_UNIVERSAL, NULL);
                        break;
                }
                player->CLOSE_GOSSIP_MENU(); break;
            case FOOD:
            {
                if (player->getLevel() >= 70)
                {
                    if (player->HasItemCount(75555, 2))
                    {
                        player->DestroyItemCount(75555, 2, true);
                        player->CastSpell(player,58648,false);
                        player->CLOSE_GOSSIP_MENU(); break;
                    }
                    else
                        creature->MonsterSay("Вам не хватает BG Killing Mark's (требуется 2)", LANG_UNIVERSAL, NULL); break;
                }
                else
                {
                    player->CastSpell(player,58648,false);
                    player->CLOSE_GOSSIP_MENU(); break;
                }
            }
            case YAICA:
                switch (rand()%13)
                {
                    case 0:
                        creature->CastSpell(player,SPELL_KILL,false);
                        creature->MonsterSay("НЕУДАЧНИКАМ НЕТ МЕСТА В НАШЕМ МИРЕ!", LANG_UNIVERSAL, NULL);
                        break;
                
                    case 1:
                        player->ModifyMoney(10000);
                        creature->MonsterSay("Так и обоготится недолго!", LANG_UNIVERSAL, NULL);
                        break;
                
                    case 2:
                        creature->CastSpell(player,SPELL_BLIND,false);
                        creature->MonsterSay("ДЖЕМБЫ НЕ ПРОЙДУТ!", LANG_UNIVERSAL, NULL);
                        break;
                
                    case 3:
                        creature->DealDamage(player,player->GetHealth()/2,NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                        player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                        player->CLOSE_GOSSIP_MENU(); break;
                
                    case 4:
                        creature->DealDamage(player,player->GetHealth()/2,NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                        player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                        player->CLOSE_GOSSIP_MENU(); break;
                
                    case 5:
                        creature->CastSpell(player,SPELL_WATER,false);
                        creature->MonsterSay("ТЕБЕ НЕ ХОЛОДНО?!", LANG_UNIVERSAL, NULL);
                        break;
                    case 6:
                        player->CastSpell(player,SPELL_BUBLE,false);
                        creature->MonsterSay("ПОЧУВСТВУЙ СЕБЯ ПАЛАДИНОМ!", LANG_UNIVERSAL, NULL);
                        break;
                    case 7:
                        creature->CastSpell(player,SPELL_BOP,false);
                        creature->MonsterSay("Hand of Protection saved of the day!", LANG_UNIVERSAL, NULL);
                        break;
                    case 8:
                        creature->CastSpell(player,SPELL_HEX1,false);
                        creature->MonsterSay("ДАВИТЕ ЖАБУ!", LANG_UNIVERSAL, NULL);
                        break;
                    case 9:
                        creature->CastSpell(player,SPELL_DES,false);
                        creature->MonsterSay("КАЖДЫЙ НЕГОДЯЙ ДОСТОИН ДЕЗЕРТИРА!", LANG_UNIVERSAL, NULL);
                        break;    
                    case 10:
                        creature->CastSpell(player,11027,false);
                        creature->MonsterSay("пдыщ!", LANG_UNIVERSAL, NULL);
                        break;
                    case 11:
                        creature->CastSpell(player,SHEEP,false);
                        creature->MonsterSay("тссс...", LANG_UNIVERSAL, NULL);
                        break;
                
                    case 12:
                        creature->CastSpell(player,11027,false);
                        creature->CastSpell(player,46014,false);
                        creature->CastSpell(player,46014,false);
                        creature->CastSpell(player,11027,false);
                        creature->MonsterSay("НЕУДАЧНИКАМ НЕТ МЕСТА В НАШЕМ МИРЕ!", LANG_UNIVERSAL, NULL);
                        break;
                
                    case 13:
                        creature->CastSpell(player,SCALE,false);
                        creature->MonsterSay("scale...", LANG_UNIVERSAL, NULL);
                        break;
                }
                player->CLOSE_GOSSIP_MENU(); break;
            case DESERT:
            {
                switch (rand()%3)
                {    
                    case 0:
                        player->RemoveAurasDueToSpell(26013);
                        player->ModifyMoney(-6000000);
                        creature->MonsterYell(SAY_DESERT_1,LANG_UNIVERSAL,NULL); break;
                    case 1:
                        player->ModifyMoney(-6000000);
                        creature->MonsterYell(SAY_DESERT_2,LANG_UNIVERSAL,NULL); break;
                    case 2:
                        player->ModifyMoney(10000);
                        creature->MonsterYell(SAY_DESERT_3,LANG_UNIVERSAL,NULL); break;
                }
            }
            player->CLOSE_GOSSIP_MENU(); break;
            default:break;
        }
        return true;
    }
    
    bool GossipSelect_pvp_porter(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        // Main menu
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### ARENA RATING VENDOR ###
######*/
/*<! --------------------------------- ! >*/

class arena_vendor : public CreatureScript
{
    public:
        arena_vendor() : CreatureScript("arena_vendor") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        switch (pCreature->GetEntry())
        {
            case 100600:
            {
                if((pPlayer->GetArenaPersonalRating(1)>2599 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>2599) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else 
                    pCreature->MonsterWhisper("У вас нет 2600 рейтинга в 3х3 или 5х5", pPlayer->GetGUID(), true);
                break;
            }
            case 100601:
            {
                if((pPlayer->GetArenaPersonalRating(1)>2699 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>2699) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else 
                    pCreature->MonsterWhisper("У вас нет 2700 рейтинга в 3х3 или 5х5", pPlayer->GetGUID(), true);
                break;
            }
            case 33936:
            {
                if((pPlayer->GetArenaPersonalRating(1)>2249 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>2249) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else 
                    pCreature->MonsterWhisper("You have not ehough 2250 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34093:
            {
                if((pPlayer->GetArenaPersonalRating(1)>2349 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>2349) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else 
                    pCreature->MonsterWhisper("You have not ehough 2350 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 33927:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1849 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1849) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1850 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 100587:
            {
                if ((pPlayer->GetArenaPersonalRating(0)>1709 && pPlayer->GetMaxPersonalArenaRatingRequirement(0)>1709) || pPlayer->isGameMaster() || (pPlayer->GetArenaPersonalRating(1)>1709 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1709))
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1710 rating in 2x2/3x3/5x5 brackets", pPlayer->GetGUID(), true);
                break;
            }
            case 100508:
            case 33937:
            {
                if ((pPlayer->GetArenaPersonalRating(0)>1984 && pPlayer->GetMaxPersonalArenaRatingRequirement(0)>1984) || pPlayer->isGameMaster() || (pPlayer->GetArenaPersonalRating(1)>1824 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1824))
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough (1985) rating in 2x2 or (1824) rating 3x3 brackets", pPlayer->GetGUID(), true);
                break;
            }
            case 33938:
            {
                if ((pPlayer->GetArenaPersonalRating(0)>1709 && pPlayer->GetMaxPersonalArenaRatingRequirement(0)>1709) || pPlayer->isGameMaster() || (pPlayer->GetArenaPersonalRating(1)>1709 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1709))
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1710 rating in 2x2/3x3/5x5 brackets", pPlayer->GetGUID(), true);
                break;
            }
            case 34038:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1849 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1849) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1850 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34063:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1219 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1219) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1220 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34084:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1749 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1749) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1750 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34060:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1899 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1749) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1900 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34075:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1949 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1949) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 1950 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34078:
            {
                if((pPlayer->GetArenaPersonalRating(1)>1999 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>1999) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 2000 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            case 34095:
            {
                if((pPlayer->GetArenaPersonalRating(1)>2349 && pPlayer->GetMaxPersonalArenaRatingRequirement(1)>2349) || pPlayer->isGameMaster())
                    pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
                else
                    pCreature->MonsterWhisper("You have not ehough 2350 rating in 3x3 bracket", pPlayer->GetGUID(), true);
                break;
            }
            return false;
        }
        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### DK PORTER: TELEPORTS FOR DEATH KNIGHT LOCATION ###
######*/
/*<! --------------------------------- ! >*/

class dkporter : public CreatureScript
{
    public:
        dkporter() : CreatureScript("dkporter") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {

        if(pPlayer->getClass() == CLASS_DEATH_KNIGHT )
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to 1 floor (Phase 1!)", GOSSIP_SENDER_MAIN, ONE_FLOOR);
            pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to 2 floor (Phase 1!)", GOSSIP_SENDER_MAIN, TWO_FLOOR);
            pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to 1 floor (Phase 2!)", GOSSIP_SENDER_MAIN, ONE_FLOOR_PHASE);
            pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to 2 floor (Phase 2!)", GOSSIP_SENDER_MAIN, TWO_FLOOR_PHASE);

            if( pPlayer->GetTeam() == HORDE)
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Orgrimmar", GOSSIP_SENDER_MAIN, ORGRIMMAR);
            else
                pPlayer->ADD_GOSSIP_ITEM(0, "Teleport to Stormwind", GOSSIP_SENDER_MAIN, STORMWIND);
        }
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if(sender != GOSSIP_SENDER_MAIN) return true;
        if(!player->getAttackers().empty()) return true;
    
        switch(action)
        {
            case ONE_FLOOR:
                player->TeleportTo(609, 2370.427f, -5655.111f, 382.315f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); 
                break;
            case ONE_FLOOR_PHASE:
                player->TeleportTo(0, 2370.427f, -5655.111f, 382.315f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); 
                break;
            case TWO_FLOOR:
                player->TeleportTo(609, 2370.427f, -5655.111f, 426.128f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); 
                break;
            case TWO_FLOOR_PHASE:
                player->TeleportTo(0, 2370.427f, -5655.111f, 426.128f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); 
                break;
            case STORMWIND:
                player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); 
                break;
            case ORGRIMMAR:
                player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                player->CLOSE_GOSSIP_MENU(); 
                break;
        }
        return true;
    }
    
    bool GossipSelect_dkporter(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### PROFESSIONS NPC FOR TOURNAMENT REALM ###
######*/
/*<! --------------------------------- ! >*/


class npc_prof : public CreatureScript
{
    public:
        npc_prof() : CreatureScript("npc_prof") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        uint32 freeProfs = pPlayer->GetFreePrimaryProfessionPoints()+1;
        if (freeProfs >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить профессию!", GOSSIP_SENDER_MAIN, 10);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
        }
        else
            pCreature->MonsterWhisper("Ата-та по рукам! Нельзя так много проф юзать!", LANG_UNIVERSAL, NULL);
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch(action)
        {
            case 9:
            {
                uint32 freeProfs = player->GetFreePrimaryProfessionPoints()+1;
                if (freeProfs >= sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL))
                {
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить профессию!", GOSSIP_SENDER_MAIN, 10);
                    player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
                }
                else
                {
                    creature->MonsterSay("Ата-та по рукам! Нельзя так много проф юзать!", LANG_UNIVERSAL, NULL);
                    player->CLOSE_GOSSIP_MENU();
                }
        
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());    
                break;
            }
            case 10:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Jewelcrafting (Ювелирное дело)!", GOSSIP_SENDER_MAIN, 11);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Enchanting (Наложение чар)!", GOSSIP_SENDER_MAIN, 12);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Engineering (Инженерное дело)!", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Blacksmith (Кузнечное дело)!", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Хочу изучить Leatherworking (Кожевничество)!", GOSSIP_SENDER_MAIN, 15);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 11:
            {
                player->CastSpell(player, jc_spell, true);

                player->SetSkill(755, player->GetSkillStep(755), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,755);
                creature->MonsterSay("Операция выполнена успешно, Jewelcrafting выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 12:
            {
                player->CastSpell(player, ec_spell, true);

                player->SetSkill(333, player->GetSkillStep(333), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,333);
                creature->MonsterSay("Операция выполнена успешно, Enchanting выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 13:
            {
                player->CastSpell(player, eg_spell, true);

                player->SetSkill(202, player->GetSkillStep(202), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,202);
                creature->MonsterSay("Операция выполнена успешно, Engineering выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 14:
            {
                player->CastSpell(player, bs_spell, true);

                player->SetSkill(164, player->GetSkillStep(164), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,164);
                creature->MonsterSay("Операция выполнена успешно, Blacksmith выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 15:
            {
                player->CastSpell(player, lw_spell, true);

                player->SetSkill(165, player->GetSkillStep(165), 450, 450);
                ((ChatHandler*)player)->HandleLearnSkillRecipesHelper(player,165);
                creature->MonsterSay("Операция выполнена успешно, Leatherworking выучен!", LANG_UNIVERSAL, NULL);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Вернуться в главное меню!", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 20);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 20:
            {
                player->CLOSE_GOSSIP_MENU();
                break;
            }
        }
        return true;
    }
    
    bool GossipSelect_npc_prof(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### RING VENDOR ###
######*/
/*<! --------------------------------- ! >*/

class ring_vendor : public CreatureScript
{
    public:
        ring_vendor() : CreatureScript("ring_vendor") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((pPlayer->HasItemCount(RING_MIGHT_1, 1)) || (pPlayer->HasItemCount(RING_MIGHT_2, 1)) || (pPlayer->HasItemCount(RING_MIGHT_3, 1)) || (pPlayer->HasItemCount(RING_MIGHT_4, 1)))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Я хочу поменять свой Ring Might на..", GOSSIP_SENDER_MAIN, 2);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 1);
        }
        else if ((pPlayer->HasItemCount(RING_CASTER_1, 1)) || (pPlayer->HasItemCount(RING_CASTER_2, 1)) || (pPlayer->HasItemCount(RING_CASTER_3, 1)) || (pPlayer->HasItemCount(RING_CASTER_4, 1)))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Я хочу поменять свой Caster Ring на..", GOSSIP_SENDER_MAIN, 4);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 1);
        }
        else if ((pPlayer->HasItemCount(RING_HEAL_1, 1)) || (pPlayer->HasItemCount(RING_HEAL_2, 1)) || (pPlayer->HasItemCount(RING_HEAL_3, 1)) || (pPlayer->HasItemCount(RING_HEAL_4, 1)))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Я хочу поменять свой Heal Ring на..", GOSSIP_SENDER_MAIN, 6);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 1);
        }
        else if ((pPlayer->HasItemCount(RING_AGILITY_1, 1)) || (pPlayer->HasItemCount(RING_AGILITY_2, 1)) || (pPlayer->HasItemCount(RING_AGILITY_3, 1)) || (pPlayer->HasItemCount(RING_AGILITY_4, 1)))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Я хочу поменять свой Ring Agility на..", GOSSIP_SENDER_MAIN, 8);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 1);
        }
        else if ((pPlayer->HasItemCount(RING_TANK_1, 1)) || (pPlayer->HasItemCount(RING_TANK_2, 1)) || (pPlayer->HasItemCount(RING_TANK_3, 1)) || (pPlayer->HasItemCount(RING_TANK_4, 1)))
        {
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Я хочу поменять свой Tank Ring на..", GOSSIP_SENDER_MAIN, 10);
            pPlayer->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Закрыть меню!", GOSSIP_SENDER_MAIN, 1);
        }
        else
        {
            pCreature->MonsterYell("У вас нет не одного кольца за репутацию Ashen Verdict",LANG_UNIVERSAL,NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
        }

        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch(action)
        {
            case 1:
            {
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            case 2:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Might Level 1", GOSSIP_SENDER_MAIN, 20);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Might Level 2", GOSSIP_SENDER_MAIN, 21);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Might Level 3", GOSSIP_SENDER_MAIN, 22);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Might Level 4", GOSSIP_SENDER_MAIN, 23);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            case 4:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Caster Ring Level 1", GOSSIP_SENDER_MAIN, 30);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Caster Ring Level 2", GOSSIP_SENDER_MAIN, 31);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Caster Ring Level 3", GOSSIP_SENDER_MAIN, 32);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Caster Ring Level 4", GOSSIP_SENDER_MAIN, 33);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            case 6:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Heal Ring Level 1", GOSSIP_SENDER_MAIN, 40);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Heal Ring Level 2", GOSSIP_SENDER_MAIN, 41);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Heal Ring Level 3", GOSSIP_SENDER_MAIN, 42);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Heal Ring Level 4", GOSSIP_SENDER_MAIN, 43);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            case 8:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Agility Level 1", GOSSIP_SENDER_MAIN, 50);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Agility Level 2", GOSSIP_SENDER_MAIN, 51);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Agility Level 3", GOSSIP_SENDER_MAIN, 52);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Ring Agility Level 4", GOSSIP_SENDER_MAIN, 53);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            case 10:
            {
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Tank Ring Level 1", GOSSIP_SENDER_MAIN, 60);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Tank Ring Level 2", GOSSIP_SENDER_MAIN, 61);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Tank Ring Level 3", GOSSIP_SENDER_MAIN, 62);
                player->ADD_GOSSIP_ITEM( GOSSIP_ICON_DOT, "Tank Ring Level 4", GOSSIP_SENDER_MAIN, 63);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }
            /* MIGHT */
            case 20:
            {
                if (player->HasItemCount(RING_MIGHT_1, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_2, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_3, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_4, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_1, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 21:
            {
                if (player->HasItemCount(RING_MIGHT_1, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_2, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_3, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_4, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_2, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 22:
            {
                if (player->HasItemCount(RING_MIGHT_1, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_2, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_3, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_4, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_3, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 23:
            {
                if (player->HasItemCount(RING_MIGHT_1, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_2, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_3, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_MIGHT_4, 1))
                {
                    player->DestroyItemCount(RING_MIGHT_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_MIGHT_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_MIGHT_4, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            /* CASTER */
            case 30:
            {
                if (player->HasItemCount(RING_CASTER_1, 1))
                {
                    player->DestroyItemCount(RING_CASTER_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_2, 1))
                {
                    player->DestroyItemCount(RING_CASTER_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_3, 1))
                {
                    player->DestroyItemCount(RING_CASTER_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_4, 1))
                {
                    player->DestroyItemCount(RING_CASTER_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_1, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 31:
            {
                if (player->HasItemCount(RING_CASTER_1, 1))
                {
                    player->DestroyItemCount(RING_CASTER_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_2, 1))
                {
                    player->DestroyItemCount(RING_CASTER_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_3, 1))
                {
                    player->DestroyItemCount(RING_CASTER_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_4, 1))
                {
                    player->DestroyItemCount(RING_CASTER_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_2, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 32:
            {
                if (player->HasItemCount(RING_CASTER_1, 1))
                {
                    player->DestroyItemCount(RING_CASTER_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_2, 1))
                {
                    player->DestroyItemCount(RING_CASTER_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_3, 1))
                {
                    player->DestroyItemCount(RING_CASTER_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_4, 1))
                {
                    player->DestroyItemCount(RING_CASTER_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_3, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 33:
            {
                if (player->HasItemCount(RING_CASTER_1, 1))
                {
                    player->DestroyItemCount(RING_CASTER_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_2, 1))
                {
                    player->DestroyItemCount(RING_CASTER_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_3, 1))
                {
                    player->DestroyItemCount(RING_CASTER_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_CASTER_4, 1))
                {
                    player->DestroyItemCount(RING_CASTER_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_CASTER_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_CASTER_4, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            /* HEAL */
            case 40:
            {
                if (player->HasItemCount(RING_HEAL_1, 1))
                {
                    player->DestroyItemCount(RING_HEAL_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_2, 1))
                {
                    player->DestroyItemCount(RING_HEAL_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_3, 1))
                {
                    player->DestroyItemCount(RING_HEAL_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_4, 1))
                {
                    player->DestroyItemCount(RING_HEAL_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_1, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 41:
            {
                if (player->HasItemCount(RING_HEAL_1, 1))
                {
                    player->DestroyItemCount(RING_HEAL_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_2, 1))
                {
                    player->DestroyItemCount(RING_HEAL_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_3, 1))
                {
                    player->DestroyItemCount(RING_HEAL_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_4, 1))
                {
                    player->DestroyItemCount(RING_HEAL_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_2, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 42:
            {
                if (player->HasItemCount(RING_HEAL_1, 1))
                {
                    player->DestroyItemCount(RING_HEAL_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_2, 1))
                {
                    player->DestroyItemCount(RING_HEAL_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_3, 1))
                {
                    player->DestroyItemCount(RING_HEAL_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_4, 1))
                {
                    player->DestroyItemCount(RING_HEAL_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_3, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 43:
            {
                if (player->HasItemCount(RING_HEAL_1, 1))
                {
                    player->DestroyItemCount(RING_HEAL_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_2, 1))
                {
                    player->DestroyItemCount(RING_HEAL_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_3, 1))
                {
                    player->DestroyItemCount(RING_HEAL_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_HEAL_4, 1))
                {
                    player->DestroyItemCount(RING_HEAL_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_HEAL_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_HEAL_4, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
                
            }
            /* AGILITY */
            case 50:
            {
                if (player->HasItemCount(RING_AGILITY_1, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_2, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_3, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_4, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_1, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 51:
            {
                if (player->HasItemCount(RING_AGILITY_1, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_2, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_3, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_4, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_2, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 52:
            {
                if (player->HasItemCount(RING_AGILITY_1, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_2, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_3, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_4, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_3, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 53:
            {
                if (player->HasItemCount(RING_AGILITY_1, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_2, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_3, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_AGILITY_4, 1))
                {
                    player->DestroyItemCount(RING_AGILITY_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_AGILITY_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_AGILITY_4, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
                
            }
            /* TANK */
            case 60:
            {
                if (player->HasItemCount(RING_TANK_1, 1))
                {
                    player->DestroyItemCount(RING_TANK_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_2, 1))
                {
                    player->DestroyItemCount(RING_TANK_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_3, 1))
                {
                    player->DestroyItemCount(RING_TANK_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_1, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_4, 1))
                {
                    player->DestroyItemCount(RING_TANK_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_1, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_1, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 61:
            {
                if (player->HasItemCount(RING_TANK_1, 1))
                {
                    player->DestroyItemCount(RING_TANK_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_2, 1))
                {
                    player->DestroyItemCount(RING_TANK_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_3, 1))
                {
                    player->DestroyItemCount(RING_TANK_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_2, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_4, 1))
                {
                    player->DestroyItemCount(RING_TANK_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_2, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_2, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 62:
            {
                if (player->HasItemCount(RING_TANK_1, 1))
                {
                    player->DestroyItemCount(RING_TANK_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_2, 1))
                {
                    player->DestroyItemCount(RING_TANK_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_3, 1))
                {
                    player->DestroyItemCount(RING_TANK_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_3, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_4, 1))
                {
                    player->DestroyItemCount(RING_TANK_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_3, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_3, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
            }
            case 63:
            {
                if (player->HasItemCount(RING_TANK_1, 1))
                {
                    player->DestroyItemCount(RING_TANK_1, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_2, 1))
                {
                    player->DestroyItemCount(RING_TANK_2, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_3, 1))
                {
                    player->DestroyItemCount(RING_TANK_3, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_4, 1, true);
                    }
                }
                else if (player->HasItemCount(RING_TANK_4, 1))
                {
                    player->DestroyItemCount(RING_TANK_4, 1, true);
                    ItemPosCountVec dest;
                    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, RING_TANK_4, 1, false);
                    if (msg == EQUIP_ERR_OK)
                    {
                        player->StoreNewItem(dest, RING_TANK_4, 1, true);
                    }
                }
                else
                    creature->MonsterYell("Error",LANG_UNIVERSAL,NULL);
                    
                break;
                
            }
        }
        return true;
    }
    
    bool GossipSelect_ring_vendor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};
                    
/*<! --------------------------------- ! >*/
/*######
### DAWN NPC ###
######*/
/*<! --------------------------------- ! >*/
    
class npc_dawn : public CreatureScript
{
    public:
        npc_dawn() : CreatureScript("npc_dawn") { }
        
    struct npc_dawnAI : public ScriptedAI
    {
        npc_dawnAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        uint32 cooldown;
        void Reset()
        {
            cooldown=0;
        }
        void UpdateAI(const uint32 diff)
        {
            if (cooldown <= diff)
            {
                me->CastSpell(me, 25823, false);
                cooldown=180000;
            }
            else cooldown-=diff;
        }
    };
    
    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_dawnAI(creature);
    }
};
    
/*<! --------------------------------- ! >*/
/*######
### SNOW NPC ###
######*/
/*<! --------------------------------- ! >*/
    
class npc_snow : public CreatureScript
{
    public:
        npc_snow() : CreatureScript("npc_snow") { }
        
    struct npc_snowAI : public ScriptedAI
    {
        npc_snowAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        uint32 cooldown;
        void Reset()
        {
            cooldown=1;
        }
        void UpdateAI(const uint32 diff)
        {
            if (cooldown <= diff)
            {
                me->CastSpell(me, 62463, true);
                cooldown=55000;
            }
            else cooldown-=diff;
        }
    };
    
    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_snowAI(creature);
    }
};

/*<! --------------------------------- ! >*/
/*######
### SCARAB NPC ###
######*/
/*<! --------------------------------- ! >*/

class scarab_vendor : public CreatureScript
{
    public:
        scarab_vendor() : CreatureScript("scarab_vendor") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {

        if (pPlayer->HasTitle(33))
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Вы уже Scarab Lord", GOSSIP_SENDER_MAIN, 3);
        }
        else if (pPlayer->GetQuestStatus(120170) != QUEST_STATUS_COMPLETE)
        {
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
        }
        else if (!pPlayer->HasTitle(33) && pPlayer->GetQuestStatus(120170) == QUEST_STATUS_COMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Я готов стать одним из немногих Scarab Lord'ов", GOSSIP_SENDER_MAIN, 1);
        }
        else
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Мне нечего сказать тебе ...", GOSSIP_SENDER_MAIN, 2);
        }
        
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {

        if(sender != GOSSIP_SENDER_MAIN) return true;
        if(!player->getAttackers().empty()) return true;
        CharTitlesEntry const* titleScrub = sCharTitlesStore.LookupEntry(46);
        uint64 guid = creature->GetGUID();
    
        switch(action)
        {
            case 1:
                uint32 entry = 120170;
                Quest const* pQuest = sObjectMgr->GetQuestTemplate(entry);
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 21176, 1, false);
                if (msg == EQUIP_ERR_OK)
                {
                    player->StoreNewItem(dest, 21176, 1, true);
                }
                player->SetTitle(titleScrub);
                // remove all quest entries for 'entry' from quest log
                for (uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
                {
                    uint32 quest = player->GetQuestSlotQuestId(slot);
                    if (quest == entry)
                    {
                        player->SetQuestSlot(slot,0);
                        // we ignore unequippable quest items in this case, its' still be equipped
                        player->TakeQuestSourceItem(quest, false);
                    }
                }
                player->CompleteQuest(entry);
                Creature* scarab = NULL;
                scarab = Creature::GetCreature((*creature), guid);
                {
                    scarab->CombatStop();
                    scarab->DeleteFromDB();
                    scarab->AddObjectToRemoveList();
                }
            break;
        }
        return true;
    }
    
    bool GossipSelect_scarab_vendor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};
    
/*<! --------------------------------- ! >*/
/*######
### GNOME EVENT QUEUE ###
######*/
/*<! --------------------------------- ! >*/

class gnome_event : public CreatureScript
{
    public:
        gnome_event() : CreatureScript("gnome_event") { }
        
    std::set<uint64> playerslist;
    std::set<uint64>::const_iterator itr;
    uint8 count;

    void Initialize()
    {
        count = 0;
    }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((pPlayer->HasItemCount(21525, 1) || pPlayer->HasItemCount(21524, 1)) && pPlayer->getRace() == RACE_GNOME && pPlayer->getLevel() <= 5 && !pPlayer->isGameMaster())
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Отметиться", GOSSIP_SENDER_MAIN, 1);
        }
        else if (pPlayer->isGameMaster())
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Сбросить отметки", GOSSIP_SENDER_MAIN, 5);
        }
        else
            pCreature->MonsterWhisper("У вас нет шапочки или Вы уже отмечались!", pPlayer->GetGUID(), true);
            
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        uint64 guid = player->GetGUID();
        
        switch (action)
        {
            case 1:
                itr = playerslist.find(guid);
                if (itr == playerslist.end())
                {
                    playerslist.insert(guid);
                    sWorld->SendWorldText(LANG_GNOME_EVENT, player->GetName(), ++count);
                    player->CastSpell(player, 26275, false);
                }
                else
                    creature->MonsterWhisper("Вы уже отмечены", guid, true);
                break;
            case 5:
                count = 0;
                playerslist.clear();
                creature->MonsterYell("Лист отмеченных сброшен", guid, true);
                break;
            default:
                break;
        }
        return true;
    }
    
    bool GossipSelect_gnome_event(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### GNOME EVENT DEFENDER ###
######*/
/*<! --------------------------------- ! >*/

class gnome_defender : public CreatureScript
{
    public:
        gnome_defender() : CreatureScript("gnome_defender") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((!pPlayer->HasAura(26157) || !pPlayer->HasAura(26272) || !pPlayer->HasAura(26273) || !pPlayer->HasAura(26274)) && (pPlayer->HasItemCount(21525, 1) || pPlayer->HasItemCount(21524, 1)) && pPlayer->getRace() == RACE_GNOME
            && pPlayer->getLevel() <= 5)
            pPlayer->ADD_GOSSIP_ITEM(0, "ХОЧУ БАБЛ!", GOSSIP_SENDER_MAIN, 1);
        else
            pCreature->MonsterWhisper("Ни чем не могу помочь ;(", pPlayer->GetGUID(), true);
            
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch (action)
        {
            case 1:
                player->CastSpell(player, SPELL_BUBLE, false);
                break;
            default:
                break;
        }
        return true;
    }
    
    bool GossipSelect_gnome_defender(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### NEW YEAR EVENT PORT ###
######*/
/*<! --------------------------------- ! >*/

class newyear_port : public CreatureScript
{
    public:
        newyear_port() : CreatureScript("newyear_port") { }
        
    std::list<Player*> hordeplayers;
    std::list<Player*> allianceplayers;
    std::set<uint64> playerslist;
    std::set<uint64>::const_iterator smashguid;
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Телепортироваться", GOSSIP_SENDER_MAIN, 1);
           /* pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Выйти из очереди", GOSSIP_SENDER_MAIN, 3); */
            
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    /*bool isIPinList(std::string ips)
    {
        std::string playerip;
        bool found = false;
        for (std::list<Player*>::iterator itr = hordeplayers.begin(); itr != hordeplayers.end(); ++itr)
        {
            playerip = (*itr)->GetSession()->GetRemoteAddress();
            if (!(*itr) || !(*itr)->IsInWorld())
                hordeplayers.erase(itr);
            if (found)
                continue;
            if (playerip == ips)
                found = true;
        }
        for (std::list<Player*>::iterator itr = allianceplayers.begin(); itr != allianceplayers.end(); ++itr)
        {
            playerip = (*itr)->GetSession()->GetRemoteAddress();
            if (!(*itr) || !(*itr)->IsInWorld())
                allianceplayers.erase(itr);
            if (found)
                continue;
            if (playerip == ips)
                found = true;
        }
        return found;
    }*/
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        /*uint64 guid = player->GetGUID();
        smashguid = playerslist.find(guid);
        switch (action)
        {
            case 1:
            {
                if (smashguid == playerslist.end()/* && !isIPinList(player->GetSession()->GetRemoteAddress()))
                {
                    if (player->GetTeam() == ALLIANCE)
                    {
                        allianceplayers.push_back(player);
                        playerslist.insert(guid);
                        if (hordeplayers.size() > 4 && allianceplayers.size() > 4)
                        {
                            creature->MonsterWhisper("Вы успешно записаны и вас сейчас телепортирует", player->GetGUID(), true);
                            player->CLOSE_GOSSIP_MENU();
                            for (std::list<Player *>::iterator itr = hordeplayers.begin(); itr != hordeplayers.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->IsInWorld())
                                {
                                    (*itr)->TeleportTo(1, -7083.27, -5422.08, 6.32, 1.45);
                                    (*itr)->CastSpell((*itr),200015,true);
                                }
                            }
                            for (std::list<Player *>::iterator itr = allianceplayers.begin(); itr != allianceplayers.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->IsInWorld())
                                {
                                    (*itr)->TeleportTo(1, -7087.58, -5420.08, 6.32, 0.72);
                                    (*itr)->CastSpell((*itr),200015,true);
                                }
                            }
                            allianceplayers.clear();
                            hordeplayers.clear();
                            playerslist.clear();
                        }
                        else
                        {
                            creature->MonsterWhisper("Вы успешно записаны", player->GetGUID(), true);
                            player->CLOSE_GOSSIP_MENU();
                            break;
                        }
                    }
                    else
                    {
                        hordeplayers.push_back(player);
                        playerslist.insert(guid);
                        if (hordeplayers.size() > 4 && allianceplayers.size() > 4)
                        {
                            creature->MonsterWhisper("Вы успешно записаны и вас сейчас телепортирует", player->GetGUID(), true);
                            player->CLOSE_GOSSIP_MENU();
                            for (std::list<Player *>::iterator itr = hordeplayers.begin(); itr != hordeplayers.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->IsInWorld())
                                {
                                    (*itr)->TeleportTo(1, -7083.27, -5422.08, 6.32, 1.45);
                                    (*itr)->CastSpell((*itr),200015,true);
                                }
                            }
                            for (std::list<Player *>::iterator itr = allianceplayers.begin(); itr != allianceplayers.end(); ++itr)
                            {
                                if ((*itr) && (*itr)->IsInWorld())
                                {
                                    (*itr)->TeleportTo(1, -7087.58, -5420.08, 6.32, 0.72);
                                    (*itr)->CastSpell((*itr),200015,true);
                                }
                            }
                            allianceplayers.clear();
                            hordeplayers.clear();
                            playerslist.clear();
                        }
                        else
                        {
                            creature->MonsterWhisper("Вы успешно записаны", player->GetGUID(), true);
                            player->CLOSE_GOSSIP_MENU();
                            break;
                        }
                    }
                }
                else
                {
                    creature->MonsterWhisper("Вы уже записаны!", player->GetGUID(), true);
                    player->CLOSE_GOSSIP_MENU();
                    break;
                }
                break;
            }
            case 2:
                char nameannounce[80];
                snprintf (nameannounce,80,"Орда: %u, Альянс: %u",hordeplayers.size(),allianceplayers.size());
                creature->MonsterWhisper(nameannounce, player->GetGUID(), true);
                break;
            case 3:
                if (player->GetTeam() == ALLIANCE)
                {
                    playerslist.erase(player->GetGUID());
                    for (std::list<Player*>::iterator itr = allianceplayers.begin(); itr != allianceplayers.end(); ++itr)
                        allianceplayers.erase(itr);
                    creature->MonsterWhisper("Вы успешно вышли из очереди", player->GetGUID(), true);
                    player->CLOSE_GOSSIP_MENU();
                }
                else
                {
                    playerslist.erase(player->GetGUID());
                    for (std::list<Player*>::iterator itr = hordeplayers.begin(); itr != hordeplayers.end(); ++itr)
                        hordeplayers.erase(itr);
                    creature->MonsterWhisper("Вы успешно вышли из очереди", player->GetGUID(), true);
                    player->CLOSE_GOSSIP_MENU();
                }
                break;
            break;
        }
        return true;*/
        switch (action)
        {
            case 1:
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->TeleportTo(1, -7087.58f, -5420.08f, 6.32f, 0.72f);
                player->CastSpell(player,200015,true);
                player->SEND_GOSSIP_MENU(creature->GetEntry(), creature->GetGUID());
                break;
            default:
                break;
        }
        return true;
    }
    
    bool GossipSelect_newyear_port(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};           
      
/*<! --------------------------------- ! >*/
/*######
### NEW YEAR EVENT VENDOR ###
######*/
/*<! --------------------------------- ! >*/

class newyear_vendor : public CreatureScript
{
    public:
        newyear_vendor() : CreatureScript("newyear_vendor") { }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->HasAura(200015))
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Продать мне новогодние подарки", GOSSIP_SENDER_MAIN, 1);
        }
        else
        {
            pCreature->MonsterWhisper("Время использования магазина окончено или запрещено", pPlayer->GetGUID(), true);
            pCreature->CastSpell(pPlayer, 11027, false);
        }
            
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch (action)
        {
            case 1:
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->PrepareQuestMenu(creature->GetGUID());
                player->RemoveAurasDueToSpell(26013);
                player->SEND_GOSSIP_MENU(creature->GetEntry(), creature->GetGUID());
                break;
            default:
                break;
        }
        return true;
    }
    
    bool GossipSelect_newyear_vendor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### SONS OF HODIR REPUTATION HACK VENDOR ###
######*/
/*<! --------------------------------- ! >*/

class sonsofhodir_vendor : public CreatureScript
{
    public:
        sonsofhodir_vendor() : CreatureScript("sonsofhodir_vendor") { }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetReputationRank(1119) >= REP_EXALTED)
        {
            pPlayer->ADD_GOSSIP_ITEM(0, "Продать мне награды за репутацию", GOSSIP_SENDER_MAIN, 1);
        }
        else
        {
            pCreature->MonsterWhisper("У вас не хватает репутации для покупки итемов.", pPlayer->GetGUID(), true);
            pCreature->CastSpell(pPlayer, 11027, false);
            pPlayer->TeleportTo(571, 6047.093f, 741.73f, 674.98f, 1.45f);
        }
            
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        switch (action)
        {
            case 1:
                player->PlayerTalkClass->GetGossipMenu().ClearMenu();
                player->SEND_VENDORLIST(creature->GetGUID());
                break;
            default:
                break;
        }
        return true;
    }
    
    bool GossipSelect_sonsofhodir_vendor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*<! --------------------------------- ! >*/
/*######
### NPC FOR TEST DAMAGE ON RESILIENCE (800) ###
######*/
/*<! --------------------------------- ! >*/

class npc_crab_res : public CreatureScript
{
public:
    npc_crab_res() : CreatureScript("npc_crab_res") { }

    struct npc_crab_resAI : Scripted_NoMovementAI
    {
        npc_crab_resAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
        {
            uiEntry = pCreature->GetEntry();
        }

        uint32 uiEntry;
        uint32 uiResetTimer;
        uint32 uiDespawnTimer;

        void Reset()
        {
            me->SetControlled(true,UNIT_STAT_STUNNED);//disable rotate
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);//imune to knock aways like blast wave

            uiResetTimer = 5000;
            uiDespawnTimer = 15000;
            if (!me->HasAura(56450))
            {
                switch (me->GetEntry())
                {
                    case 100675:
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        break;
                    case 100685:
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        break;
                    case 100695:
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        me->AddAura(56450, me);
                        break;
                    default: break;
                }
            }        
        }

        void EnterEvadeMode()
        {
            if (!_EnterEvadeMode())
                return;

            Reset();
        }

        void DamageTaken(Unit * /*done_by*/, uint32 &damage)
        {
            uiResetTimer = 5000;
            damage = 0;
        }

        void EnterCombat(Unit * /*who*/)
        {
            if (uiEntry != NPC_ADVANCED_TARGET_DUMMY && uiEntry != NPC_TARGET_DUMMY)
                return;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (!me->HasUnitState(UNIT_STAT_STUNNED))
                me->SetControlled(true,UNIT_STAT_STUNNED);//disable rotate

            if (uiEntry != NPC_ADVANCED_TARGET_DUMMY && uiEntry != NPC_TARGET_DUMMY)
            {
                if (uiResetTimer <= uiDiff)
                {
                    EnterEvadeMode();
                    uiResetTimer = 5000;
                }
                else
                    uiResetTimer -= uiDiff;
                return;
            }
            else
            {
                if (uiDespawnTimer <= uiDiff)
                    me->ForcedDespawn();
                else
                    uiDespawnTimer -= uiDiff;
            }
        }
        void MoveInLineOfSight(Unit * /*who*/){return;}
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_crab_resAI(pCreature);
    }
};

/* < ! --- END OF SCRIPTS --- ! > */

void AddSC_crw_scripts()
{
    new npc_gladiator_vendor;
    new arena_master;
    new npc_customizer;
    new pvp_porter;
    new arena_vendor;
    new dkporter;
    new npc_prof;
    new ring_vendor;
    new npc_dawn;
    new npc_title_master;
    new npc_snow;
    new scarab_vendor;
    new gnome_event;
    new gnome_defender;
    new newyear_port;
    new newyear_vendor;
    new sonsofhodir_vendor;
    new npc_crab_res;
}
/* EOF */