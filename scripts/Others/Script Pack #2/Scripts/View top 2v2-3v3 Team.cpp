// QQRofl

using namespace std;
 
class npc_top_arena : public CreatureScript
{
        public:
                npc_top_arena() : CreatureScript("npc_top_arena") { }
               
                bool OnGossip(Player * player, Creature * creature)
               
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Top 2v2 Arena Teams", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View Top 3v3 Arena Teams", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                                player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                                return true;
                        }
                       
                        bool OnGossipClick(Player * player, Creature * creature, uint32 sender, uint32 actions)
                        {
                                if(sender == GOSSIP_SENDER_MAIN)
                                {
                                        switch(actions)
                                        {
                                                case GOSSIP_ACTION_INFO_DEF+1:
                                                        {
                                                                QueryResult result = CharacterDatabase.Query("SELECT name,rating FROM arena_team WHERE type='2' ORDER BY rating DESC LIMIT 10");
                                                                if(!result)
                                                                        return false;
                                                                       
                                                                        Field * fields =  NULL;
                                                                        player->MonsterWhisper("|cff4169E1Here are the top 2v2 arena teams:|r", player->GetGUID());
                                                                        do
                                                                        {
                                                                                fields = result->Fetch();
                                                                                string arena_name = fields[0].GetString();
                                                                                uint32 rating = fields[1].GetUInt32();
                                                                                char msg[250]
                                                                                snprintf(msg, 250, "Team Name: |cffFFFF00%s|r, Team Rating: %u \n", arena_name.c_str(), rating);
                                                                                player->MonsterWhisper(msg, player->GetGUID());
                                                                                } while(reult->NextRow());
                                                                                } break;
                                                                               
                                                                                case GOSSIP_ACTION_INFO_DEF+2:
                                                                                {
                                                                                        QueryResult result = CharacterDatabase.Query("SELECT name,rating FROM arena_team WHERE type='3' ORDER BY rating DESC LIMIT 10");
                                                                                        if(!result)
                                                                                                return false;
                                                                                               
                                                                                                Field * fields = NULL;
                                                                                                player->MonsterWhisper("|cff4169E1Here are the top 10 3v3 arena teams:|r", player->GetGUID());
                                                                                                do
                                                                                                {
                                                                                                        fields = result->Fetch();
                                                                                                        string arena_name = fields[0].GetString();
                                                                                                        uint32 rating = fields[1].GetUInt32();
                                                                                                        char msg[250];
                                                                                                        snprintf(msg, 250, "Team Name: |cffFFF00%s|r, Team Rating: $u \n", arena_name.c_str(), rating)
                                                                                                        player->MonsterWhisper(msg, player->GetGUID());
                                                                                                        } while(result->NextRow()); } break;
                                                                                                       
                                                                                                        case GOSSIP_ACTION_INFO_DEF+3:
                                                                                                        {
                                                                                                                player->PlayerTalkClass->SendCloseGossip();
                                                                                                        } break;
                                                                                                       
                                                                                                        }
                                                                                                        }
                                                                                                        return true;
                                                                                                        }
                                                                                                        };
                                                                                                       
                                                                                                        void AddSC_npc_arena()
                                                                                                        {
                                                                                                        new npc_top_arena;
                                                                                                        }