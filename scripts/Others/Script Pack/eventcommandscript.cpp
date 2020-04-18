#include "ScriptPCH.h"
#include "Chat.h"
#include "World.h"

class hva_commandscript : public CommandScript
{
public:
    hva_commandscript() : CommandScript("hva_commandscript") { }

	ChatCommand* GetCommands() const
    {
        static ChatCommand IngameCommandTable[] =
        {
			{ "hva",                SEC_PLAYER,  false, &HandleHvaCommand,                 "",  NULL },
			{ "stophva",            SEC_PLAYER,  false, &HandleStophvaCommand,             "",  NULL },
            {  NULL,                         0,  false, NULL,                              "",  NULL }
        };
		return IngameCommandTable;
    }
	
	    static bool HandleHvaCommand(ChatHandler* handler, const char* args)
		{
		            Player* me = handler->GetSession()->GetPlayer();
					{
					me->SummonCreature(190606, -3289.386963f , -1197.079224f, 120.644569f, 0, TEMPSUMMON_TIMED_DESPAWN, 600000);
					char msg[250];
		            snprintf(msg, 250, "|cffff0000[Event System]|r The Event|cffff0000 Horde vs Alliance|r has now started! ", NULL);  // The message
		            sWorld->SendGlobalText(msg, NULL);
					return true;
					}
		}
		
		static bool HandleStophvaCommand(ChatHandler* handler, const char* args)
		{
		           Player* me = handler->GetSession()->GetPlayer();
					{
			        char msg[250];
		            snprintf(msg, 250, "|cffff0000[Event System]|r The Event|cffff0000 Horde vs Alliance|r has now ended! ", NULL);  // The message
		            sWorld->SendGlobalText(msg, NULL);
					return true;
					}
		}
		private:
};

void AddSC_hva_commandscript()
{
    new hva_commandscript();
}	