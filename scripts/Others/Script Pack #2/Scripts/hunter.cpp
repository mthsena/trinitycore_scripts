#include "ScriptPCH.h"
#include <cstring>
 
#define SET_CURRENCY 1  //0 for gold, 1 for honor, 2 for tokens
#define TOKEN_ID 0 // token id
 
#if SET_CURRENCY == 1
#define BOUNTY_1 "Заказать убийство за 50 очков арены"
#define BOUNTY_2 "Заказать убийство за 75 очков арены"
#define BOUNTY_3 "Заказать убийство за 100 очков арены"
#define BOUNTY_4 "Заказать убийство за 150 очков арены"
#endif
#if SET_CURRENCY == 1
#define BOUNTY_1 "Заказать убийство за 50 очков арены"
#define BOUNTY_2 "Заказать убийство за 75 очков арены"
#define BOUNTY_3 "Заказать убийство за 100 очков арены"
#define BOUNTY_4 "Заказать убийство за 150 очков арены"
#endif
#if SET_CURRENCY == 2
#define BOUNTY_1 "Заказать убийство за 50 очков арены"
#define BOUNTY_2 "Заказать убийство за 75 очков арены"
#define BOUNTY_3 "Заказать убийство за 100 очков арены"
#define BOUNTY_4 "Заказать убийство за 150 очков арены"
#endif
 
#define PLACE_BOUNTY "Заказать убийство"
#define LIST_BOUNTY "Листы заказов"
#define NVM "Отменить"
#define WIPE_BOUNTY "Очистить"
 
 
 
 
#if SET_CURRENCY != 2
//these are just visual prices, if you want to to change the real one, edit the sql further below
enum BountyPrice
{
        BOUNTY_PRICE_1 = 50,
        BOUNTY_PRICE_2 = 75,
        BOUNTY_PRICE_3 = 100,
        BOUNTY_PRICE_4 = 150,
};
#else
enum BountyPrice
{
        BOUNTY_PRICE_1 = 50,
        BOUNTY_PRICE_2 = 75,
        BOUNTY_PRICE_3 = 100,
        BOUNTY_PRICE_4 = 150,
};
#endif
 
bool passChecks(Player * pPlayer, const char * name)
{
 
        Player * pBounty = sObjectAccessor->FindPlayerByName(name);
        WorldSession * m_session = pPlayer->GetSession();
        if(!pBounty)
        {
                m_session->SendNotification("Player is does not exist");
                return false;
        }
        QueryResult result = CharacterDatabase.PQuery("SELECT * FROM bounties WHERE guid ='%u'", pBounty->GetGUID());
        if(result)
        {
                m_session->SendNotification("For this killing is a reward");
                return false;
        }
        if(pPlayer->GetGUID() == pBounty->GetGUID())
        {
                m_session->SendNotification("You can not kill yourself");
                return false;
        }
        return true;
}
 
void alertServer(const char * name, int msg)
{
        std::string message;
        if(msg == 1)
        {
                message = "Received an order to murder ";
                message += name;
                message += "Kill him and get reward!";
        }
        else if(msg == 2)
        {
                message = "Player ";
                message += name;
                message += " Killed!";
        }
        sWorld->SendServerMessage(SERVER_MSG_STRING, message.c_str(), 0);
}
 
 
bool hasCurrency(Player * pPlayer, uint32 required, int currency)
{
        WorldSession *m_session = pPlayer->GetSession();
        switch(currency)
        {
                case 0: //gold
                        {
                        uint32 currentmoney = pPlayer->GetArenaPoints();
                        uint32 requiredmoney = (required * 10000);
                        if(currentmoney < requiredmoney)
                        {
                                m_session->SendNotification("You don't have enough gold!");
                                return false;
                        }
                        pPlayer->SetMoney(currentmoney - requiredmoney);
                        break;
                        }
                case 1: //honor
                        {
                        uint32 currenthonor = pPlayer->GetArenaPoints();
                        if(currenthonor < required)
                        {
                                m_session->SendNotification("Not enough points arena");
                                return false;
                        }
                        pPlayer->SetArenaPoints(currenthonor - required);
                        break;
                        }
                case 2: //tokens
                        {
                        if(!pPlayer->HasItemCount(TOKEN_ID, required))
                        {
                                m_session->SendNotification("You do not have enough arena points!");
                                return false;
                        }
                        pPlayer->DestroyItemCount(TOKEN_ID, required, true, false);
                        break;
                        }
 
        }
        return true;
}
 
void flagPlayer(const char * name)
{
        Player * pBounty = sObjectAccessor->FindPlayerByName(name);
        pBounty->SetPvP(true);
        pBounty->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
}
 
class BountyHunter : public CreatureScript
{
        public:
                BountyHunter() : CreatureScript("BountyHunter"){}
                bool OnGossipHello(Player * Player, Creature * Creature)
                {
                        Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                        Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, LIST_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, NVM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                        if ( Player->isGameMaster() )
                        {
                                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, WIPE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                        }
 
                        Player->PlayerTalkClass->SendGossipMenu(907, Creature->GetGUID());
                        return true;
                }
 
                bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
                {
                        pPlayer->PlayerTalkClass->ClearMenus();
                        switch(uiAction)
                        {
                                case GOSSIP_ACTION_INFO_DEF+1:
                                {
                                        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5, "", 0, true);
                                        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6, "", 0, true);
                                        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7, "", 0, true);
                                        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8, "", 0, true);
                                        pPlayer->PlayerTalkClass->SendGossipMenu(365, pCreature->GetGUID());
                                        break;
                                }
                                case GOSSIP_ACTION_INFO_DEF+2:
                                {
                                        QueryResult Bounties = CharacterDatabase.PQuery("SELECT * FROM bounties");
                                       
                                        if(!Bounties)
                                        {
                                                  pPlayer->CLOSE_GOSSIP_MENU();
                                                return false;
                                        }
#if SET_CURRENCY == 0
                                        if(     Bounties->GetRowCount() > 1)
                                        {
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orders: ", GOSSIP_SENDER_MAIN, 1);
                                                do
                                                {
                                                        Field * fields = Bounties->Fetch();
                                                        std::string option;
                                                        QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
                                                        Field * names = name->Fetch();
                                                        option = names[0].GetString();
                                                        option +=" ";
                                                        option += fields[1].GetString();
                                                        option += " gold";
                                                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
                                                }while(Bounties->NextRow());
                                        }
                                        else
                                        {
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orders: ", GOSSIP_SENDER_MAIN, 1);
                                                Field * fields = Bounties->Fetch();
                                                std::string option;
                                                QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
                                                Field * names = name->Fetch();
                                                option = names[0].GetString();
                                                option +=" ";
                                                option += fields[1].GetString();
                                                option += " gold";
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
                                               
                                        }
#endif
#if SET_CURRENCY == 1
                                        if(     Bounties->GetRowCount() > 1)
                                        {
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orders: ", GOSSIP_SENDER_MAIN, 1);
                                                do
                                                {
                                                        Field * fields = Bounties->Fetch();
                                                        std::string option;
                                                        QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
                                                        Field * names = name->Fetch();
                                                        option = names[0].GetString();
                                                        option +=" ";
                                                        option += fields[1].GetString();
                                                        option += " Arena";
                                                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
                                                }while(Bounties->NextRow());
                                        }
                                        else
                                        {
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orders: ", GOSSIP_SENDER_MAIN, 1);
                                                Field * fields = Bounties->Fetch();
                                                std::string option;
                                                QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
                                                Field * names = name->Fetch();
                                                option = names[0].GetString();
                                                option +=" ";
                                                option += fields[1].GetString();
                                                option += " arena";
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
                                               
                                        }
#endif
#if SET_CURRENCY == 2
                                        if(     Bounties->GetRowCount() > 1)
                                        {
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orders: ", GOSSIP_SENDER_MAIN, 1);
                                                do
                                                {
                                                        Field * fields = Bounties->Fetch();
                                                        std::string option;
                                                        QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
                                                        Field * names = name->Fetch();
                                                        option = names[0].GetString();
                                                        option +=" ";
                                                        option += fields[1].GetString();
                                                        option += " coins";
                                                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
                                                }while(Bounties->NextRow());
                                        }
                                        else
                                        {
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orders: ", GOSSIP_SENDER_MAIN, 1);
                                                Field * fields = Bounties->Fetch();
                                                std::string option;
                                                QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
                                                Field * names = name->Fetch();
                                                option = names[0].GetString();
                                                option +=" ";
                                                option += fields[1].GetString();
                                                option += " coins";
                                                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
                                               
                                        }
#endif
                                        pPlayer->PlayerTalkClass->SendGossipMenu(878, pCreature->GetGUID());
                                        break;
                                }
                                case GOSSIP_ACTION_INFO_DEF+3:
                                {
                                         pPlayer->CLOSE_GOSSIP_MENU();
                                        break;
                                }
                                case GOSSIP_ACTION_INFO_DEF+4:
                                {
                                        CharacterDatabase.PExecute("TRUNCATE TABLE bounties");
                                         pPlayer->CLOSE_GOSSIP_MENU();
                                        break;
                                }
                        }
                        return true;
                }
 
                bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char * code)
                {
                        pPlayer->PlayerTalkClass->ClearMenus();
                        if ( uiSender == GOSSIP_SENDER_MAIN )
                        {
                                if(islower(code[0]))
                                        toupper(code[0]);
 
                                if(passChecks(pPlayer, code))
                                {
                                        Player * pBounty = sObjectAccessor->FindPlayerByName(code);
                                        switch (uiAction)
                                        {
                                                case GOSSIP_ACTION_INFO_DEF+5:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_1, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','20', '1')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','1', '1')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                               pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
                                                       
                                                case GOSSIP_ACTION_INFO_DEF+6:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_2, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '40', '2')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '3', '2')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                                pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
                                                case GOSSIP_ACTION_INFO_DEF+7:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_3, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '100', '3')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '5', '3')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                                 pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
                                                case GOSSIP_ACTION_INFO_DEF+8:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_4, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '200', '4')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '10', '3')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                                pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
 
                                        }
                                }
                                else
                                {
                                         pPlayer->CLOSE_GOSSIP_MENU();
                                }
                        }
                        return true;
                }
};
 
 
class BountyKills : public PlayerScript
{
        public:
                BountyKills() : PlayerScript("BountyKills"){}
 
                void OnPVPKill(Player * Killer, Player * Bounty)
                {
                        if(Killer->GetGUID() == Bounty->GetGUID())
                                return;
 
                        QueryResult result = CharacterDatabase.PQuery("SELECT * FROM bounties WHERE guid='%u'", Bounty->GetGUID());
                        if(!result)
                                return;
 
                        Field * fields = result->Fetch();
#if SET_CURRENCY == 0
                        switch(fields[2].GetUInt64())
                        {
                        case 1:
                                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_1 * 10000));
                                break;
                        case 2:
                                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_2 * 10000));
                                break;
                        case 3:
                                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_3 * 10000));
                                break;
                        case 4:
                                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_4 * 10000));
                                break;
                        }
#endif
#if SET_CURRENCY == 1
                        switch(fields[2].GetUInt64())
                        {
                        case 1:
                                Killer->SetArenaPoints(Killer->GetArenaPoints() + (BOUNTY_PRICE_1));
                                break;
                        case 2:
                                Killer->SetArenaPoints(Killer->GetArenaPoints() + (BOUNTY_PRICE_2));
                                break;
                        case 3:
                                Killer->SetArenaPoints(Killer->GetArenaPoints() + (BOUNTY_PRICE_3));
                                break;
                        case 4:
                                Killer->SetArenaPoints(Killer->GetArenaPoints() + (BOUNTY_PRICE_4));
                                break;
                        }
#endif
#if SET_CURRENCY == 2
                        switch(fields[2].GetUInt64())
                        {
                        case 1:
                                Killer->AddItem(TOKEN_ID, BOUNTY_PRICE_1);
                                break;
                        case 2:
                                Killer->AddItem(TOKEN_ID, BOUNTY_PRICE_2);
                                break;
                        case 3:
                                Killer->AddItem(TOKEN_ID, BOUNTY_PRICE_3);
                                break;
                        case 4:
                                Killer->AddItem(TOKEN_ID, BOUNTY_PRICE_4);
                                break;
                        }
#endif
                        CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid='%u'", Bounty->GetGUID());
                        alertServer(Bounty->GetName(), 2);
 
                }
};
 
void AddSC_BountyHunter()
{
        new BountyHunter();
        new BountyKills();
}
