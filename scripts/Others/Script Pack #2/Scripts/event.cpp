//by SymbolixDEV https://github.com/SymbolixDEV
#include "ScriptPCH.h"
#include "Chat.h"

/* Colors */
#define MSG_COLOR_WHITE  "|cffffffff"
#define MSG_COLOR_LIGHTBLUE "|cffADD8E6"

class eventannouncercommand : public CommandScript
{
public:
    eventannouncercommand() : CommandScript("eventannouncer") { }
 
        ChatCommand* GetCommands() const
    {
        static ChatCommand IngameCommandTable[] =
        {
        { "eventannouncer",           SEC_GAMEMASTER,         true,  &HandleEventAnnouncerCommand,                "", NULL },
        { NULL,             0,                  false, NULL,                              "", NULL }
        };
                 return IngameCommandTable;
    }
        static bool HandleEventAnnouncerCommand(ChatHandler * handler, const char * args)
    {
   if(!*args)
                        return false;
        char message[1024];
 
                if(handler->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
                {
                                  snprintf(message, 1024, "[Event Announcer][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, handler->GetSession()->GetPlayer()->GetName().c_str(), MSG_COLOR_LIGHTBLUE, args);
                                sWorld->SendServerMessage(SERVER_MSG_STRING, message, NULL);
    }
  return true;
  }
};

void AddSC_eventannouncer()
{
        new eventannouncercommand;
}
