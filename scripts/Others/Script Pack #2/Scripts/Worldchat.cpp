#include "ScriptPCH.h"
#include "Chat.h"
#include "Common.h"

class World_Chat : public CommandScript
{
public:
	World_Chat() : CommandScript("World_Chat") { }
	
	static bool HandleWorldChatCommand(ChatHandler * pChat, const char * msg)
	{
		if(!*msg)
			return false;
		
		Player * player = pChat->GetSession()->GetPlayer();
		char message[1024];
		
		switch(player->GetSession()->GetSecurity())
		{
		case SEC_PLAYER:
			snprintf(message, 1024, "|cffffff00[World][Player][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_PREMIUM:
			snprintf(message, 1024, "|cff00ccff[World][Premium][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
	
		case SEC_MODERATOR:
			snprintf(message, 1024, "|cffADFF2F[World][Moderator][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_TICKET_GM:
			snprintf(message, 1024, "|cffADFF2F[World][GM][%s]: %s|r", player->GetName().c_str(), msg);
		    sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_EVENT_GM:
			snprintf(message, 1024, "|cffADFF2F[World][EM][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_GAMEMASTER:
			snprintf(message, 1024, "|cffADFF2F[World][Gamemaster][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_HEAD_GM:
			snprintf(message, 1024, "|cffADFF2F[World][Head GM][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_DEVELOPER:
			snprintf(message, 1024, "|cff8B8B83[World][Developer][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_HEAD_DEVELOPER:
			snprintf(message, 1024, "|cff8B8B83[World][Head Dev][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_ADMINISTRATOR:
			snprintf(message, 1024, "|cffFF4500[World][Administrator][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		case SEC_OWNER:
			snprintf(message, 1024, "|cffFF4500[World][Owner][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		
		case SEC_CONSOLE:
			snprintf(message, 1024, "|cffFF4500[World][Console][%s]: %s|r", player->GetName().c_str(), msg);
			sWorld->SendGlobalText(message, NULL);
			break;
		}
		return true;
	}
	
	ChatCommand * GetCommands() const
	{
		static ChatCommand HandleWorldChatCommandTable[] =
		{
			{ "world",        SEC_PLAYER,         true,     &HandleWorldChatCommand,               "",  NULL },
			{ NULL,              0,               false,    NULL,                                  "",  NULL }
		};
		return HandleWorldChatCommandTable;
	}
};

void AddSC_World_Chat()
{
	new World_Chat;
}