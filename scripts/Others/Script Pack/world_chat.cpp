#include "ScriptPCH.h"
#include "Chat.h"
 
class cs_world_chat : public CommandScript
{
        public:
                cs_world_chat() : CommandScript("cs_world_chat"){}
 
        ChatCommand * GetCommands() const
        {
                static ChatCommand WorldChatCommandTable[] =
                {
                        {"chat",        SEC_PLAYER,             true,           &HandleWorldChatCommand,        "", NULL},
                        {NULL,          0,                              false,          NULL,                                           "", NULL}
                };
 
                return WorldChatCommandTable;
        }
 
        static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
        {
                if (!args)
                        return false;
 
                std::string msg = "";
                Player * player = handler->GetSession()->GetPlayer();
 
                switch(player->GetSession()->GetSecurity())
                {
				         /* PLAYER RANKS */ 
						 
                        case SEC_PLAYER://player
                               msg += "|cffa335ee[World]|cffffffff";
                               msg += player->GetName();
                               msg += ": |cfffaeb00";
                                break;
                        case 1://vip
                                msg += "|cffa335ee[World]|cff9d9d9d[VIP]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
								
						case 2://helper
                                msg += "|cffa335ee[World]|cff9d9d9d[Helper]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;								
								/* STAFF RANKS */
								
						case 3: // Trial GM
                                msg += "|cffa335ee[World]|cff41A317[Trial GM]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 4: // Junior GM
                                msg += "|cffa335ee[World]|cff00BFFF[Junior GM]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 5: // GM
                                msg += "|cffa335ee[World]|cff1589FF[GM]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 6: // Senior GM
                                msg += "|cffa335ee[World]|cff1eff00[Senior GM]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 7: // Head GM
                                msg += "|cffa335ee[World]|cffFF0000[Head GM]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 8: // Admin
                                msg += "|cffa335ee[World]|cffFF0000[Admin]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
                        case 9: // Senior Admin
                                msg += "|cffa335ee[World]|cffFF0000[Senior Admin]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
                        case 10: // Senior Developer
                                msg += "|cffa335ee[World]|cffFF0000[Senior Dev]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 11: // Head Admin
                                msg += "|cffa335ee[World]|cffFF0000[Head Admin]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 12: // Head Developer
                                msg += "|cffa335ee[World]|cFFFF0000[Head Dev]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 13: // Co Owner
                                msg += "|cffa335ee[World]|cFFFF0000[Co Owner]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 14: // Owner
                                msg += "|cffa335ee[World]|cFFFF0000[Owner]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
						case 15: // Console
                                msg += "|cffa335ee[World]|cFFFF0000[Console]|cffffffff";
                                msg += player->GetName();
                                msg += ": |cfffaeb00";
                                break;
 
                }
                       
                msg += args;
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);  
 
                return true;
        }
};
 
void AddSC_cs_world_chat()
{
        new cs_world_chat();
}