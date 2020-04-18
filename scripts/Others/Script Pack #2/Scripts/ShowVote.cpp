#include "ScriptPCH.h"
 
enum Tokens
{
        DONOR_TOKEN = 24581, // Your token ID, Default: Mark of Thrallmar
        VOTER_TOKEN = 24579, // Your token ID, Default: Mark of Honor Hold
};
 
class Donor_Voter_Trader : public CreatureScript
{
public:
        Donor_Voter_Trader() : CreatureScript("Donor_Voter_Trader") { }
 
        bool OnGossipHello(Player *player, Creature *creature)
        {
                player->ADD_GOSSIP_ITEM(0, "[Donor Points]->", GOSSIP_SENDER_MAIN, 1);
                player->ADD_GOSSIP_ITEM(0, "[Voter Points]->", GOSSIP_SENDER_MAIN, 2);
                player->ADD_GOSSIP_ITEM(0, "Show My Points", GOSSIP_SENDER_MAIN, 3);
                player->ADD_GOSSIP_ITEM(4, "Close Window.", GOSSIP_SENDER_MAIN, 10);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());        
                return true;
        }
 
        bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
        {
                QueryResult select = LoginDatabase.PQuery("SELECT dp, vp FROM account WHERE id = '%u'", player->GetSession()->GetAccountId());
 
                if(!select)
                {
                        player->GetSession()->SendAreaTriggerMessage("Internal error!");
                        return false;
                }
 
                Field* fields = select->Fetch();
                uint32 dp = fields[0].GetUInt32();
                uint32 vp = fields[1].GetUInt32();
 
                player->PlayerTalkClass->ClearMenus();
 
                if (sender == GOSSIP_SENDER_MAIN)
                {
                        switch(uiAction)
                        {
                        case 1:// Donor Points
                                if (dp == 0)
                                {
                                        player->GetSession()->SendAreaTriggerMessage("You don't have none donor point.");
                                        player->CLOSE_GOSSIP_MENU();
                                        return false;
                                }
 
                                player->ADD_GOSSIP_ITEM_EXTENDED(0, "[1 Point] For [1 Token]", GOSSIP_SENDER_MAIN, 4, "Are you sure?", 0, false);
                                player->ADD_GOSSIP_ITEM_EXTENDED(0, "[10 Points] For [10 Tokens]", GOSSIP_SENDER_MAIN, 5, "Are you sure?", 0, false);
                                player->ADD_GOSSIP_ITEM(4, "...Back", GOSSIP_SENDER_MAIN, 11);
                                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());  
                                break;
 
                        case 2:// Voter Points
                                if (vp == 0)
                                {
                                        player->GetSession()->SendAreaTriggerMessage("You don't have none voter point.");
                                        player->CLOSE_GOSSIP_MENU();
                                        return false;
                                }
 
                                player->ADD_GOSSIP_ITEM_EXTENDED(0, "[1 Point] For [1 Token]", GOSSIP_SENDER_MAIN, 6, "Are you sure?", 0, false);
                                player->ADD_GOSSIP_ITEM_EXTENDED(0, "[10 Points] For [10 Tokens]", GOSSIP_SENDER_MAIN, 7, "Are you sure?", 0, false);
                                player->ADD_GOSSIP_ITEM(4, "...Back", GOSSIP_SENDER_MAIN, 11);
                                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                                break;
 
                        case 3:// Show My Points
                                player->GetSession()->SendAreaTriggerMessage("Donor Points: %u", dp);
                                player->GetSession()->SendAreaTriggerMessage("Voter Points: %u", vp);
                                player->CLOSE_GOSSIP_MENU();
                                break;
 
                        case 4:// [1 Donor Point] For [1 Donor Token]
                                if (dp < 1)
                                {
                                        player->GetSession()->SendAreaTriggerMessage("You don't have the required points.");
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                else
                                {
                                        LoginDatabase.PExecute("UPDATE account SET dp = '%u' -1 WHERE id = '%u'", dp, player->GetSession()->GetAccountId()); // DP Exchange 1
                                        player->GetSession()->SendAreaTriggerMessage("Successfully!");
                                        player->AddItem(DONOR_TOKEN, 1);
                                        player->SaveToDB();
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                break;
 
                        case 5:// [10 Donor Points] For [10 Donor Tokens]
                                if (dp < 10)
                                {
                                        player->GetSession()->SendAreaTriggerMessage("You don't have the required points.");
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                else
                                {
                                        LoginDatabase.PExecute("UPDATE account SET dp = '%u' -10 WHERE id = '%u'", dp, player->GetSession()->GetAccountId()); // DP Exchange 10
                                        player->GetSession()->SendAreaTriggerMessage("Successfully!");
                                        player->AddItem(DONOR_TOKEN, 10);
                                        player->SaveToDB();
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                break;
 
                        case 6:// [1 Voter Point] For [1 Voter Token]
                                if (vp < 1)
                                {
                                        player->GetSession()->SendAreaTriggerMessage("You don't have the required points.");
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                else
                                {
                                        LoginDatabase.PExecute("UPDATE account SET vp = '%u' -1 WHERE id = '%u'", vp, player->GetSession()->GetAccountId()); // VP Exchange 1
                                        player->GetSession()->SendAreaTriggerMessage("Successfully!");
                                        player->AddItem(VOTER_TOKEN, 1);
                                        player->SaveToDB();
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                break;
 
                        case 7:// [10 Voter Points] For [10 Voter Tokens]
                                if (vp < 10)
                                {
                                        player->GetSession()->SendAreaTriggerMessage("You don't have the required points.");
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                else
                                {
                                        LoginDatabase.PExecute("UPDATE account SET vp = '%u' -10 WHERE id = '%u'", vp, player->GetSession()->GetAccountId()); // VP Exchange 10
                                        player->GetSession()->SendAreaTriggerMessage("Successfully!");
                                        player->AddItem(VOTER_TOKEN, 10);
                                        player->SaveToDB();
                                        player->CLOSE_GOSSIP_MENU();
                                }
                                break;
 
                        case 10:// Close Window
                                player->CLOSE_GOSSIP_MENU();
                                break;
 
                        case 11: // ...Back
                                OnGossipHello(player, creature);
                                break;
                        }
                }
 
                return true;
        }
};
 
void AddSC_Donor_Voter_Trader()
{
        new Donor_Voter_Trader();
}
