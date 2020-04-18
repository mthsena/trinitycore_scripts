// Created by AlexeWarr (ak47sigh)
//Special thankies to: Rochet2 & LittleCarl

#include "Chat.h"
#include "ScriptMgr.h"

//!Commands Info (Using .help <cmd>)
#define cinfo_player			"Give warn to player."
#define cinfo_list_all			"Show all available warnings"
#define cinfo_list_name			"Show available warnings for player name."
#define cinfo_remove_id			"Remove warn with specified ID."
#define cinfo_remove_name		"Remove warns of player name."

//!Commands Syntax (How-To-Use)
#define csyntax_player			"\nSyntax: <player> <reason> <priority[1, 2, 3]>"
#define csyntax_list_name		"\nSyntax: <player name>"
#define csyntax_remove_id		"\nSyntax: <id>"
#define csyntax_remove_name		"\nSyntax: <name>"

//![[Recommended to leave them as they are right now :D]]!
#define chelp_player		cinfo_player		/*&&*/ csyntax_player
#define chelp_list_all		cinfo_list_all
#define chelp_list_name		cinfo_list_name		/*&&*/ csyntax_list_name
#define chelp_remove_id		cinfo_remove_id		/*&&*/ csyntax_remove_id
#define chelp_remove_name	cinfo_remove_name	/*&&*/ csyntax_remove_name
// - - - ---------- End --------- - - - //

class custom_warnings : public CommandScript
{
public:
    custom_warnings() : CommandScript("custom_warnings") { }

    ChatCommand* GetCommands() const
    {
		static ChatCommand warnListCommandTable[] =
        {
			{ "all",			SEC_MODERATOR,		true,		&PWarnListAll,			chelp_list_all, NULL }, // done
			{ "name",			SEC_MODERATOR,		true,		&PWarnListName,		   chelp_list_name, NULL }, // done
			{ NULL, 0, false, NULL, "", NULL }
        };
		static ChatCommand warnRemoveCommandTable[] =
        {
			{ "id",				SEC_MODERATOR,		true,		&PWarnRemoveID,		   chelp_remove_id, NULL }, // done
			{ "name",			SEC_MODERATOR,		true,		&PWarnRemoveName,	 chelp_remove_name, NULL }, // done
			{ NULL, 0, false, NULL, "", NULL }
        };
		static ChatCommand warnCommandTable[] =
        {
			{ "list",			SEC_MODERATOR,		true,		NULL, "",				warnListCommandTable }, // done
			{ "player",			SEC_MODERATOR,		true,		&PWarnPlayer,			  chelp_player, NULL }, // done
			{ "remove",			SEC_MODERATOR,		true,		NULL, "",			  warnRemoveCommandTable }, // done
			{ NULL, 0, false, NULL, "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "pwarn",			SEC_MODERATOR,		true,		NULL, "",					warnCommandTable }, // done
            { NULL,				SEC_PLAYER,			false,		NULL, "",								NULL }
        };
        return commandTable;
    }

	static void SendGlobalAnnounce(Player* player, char* reportedPlayer, char* reason)
	{
		std::ostringstream BuildAnnounce;

		BuildAnnounce << "|cff2E9AFE[Global Announce]|r " << "Player |cffFF0000" << reportedPlayer << "|r warned by |cffFF0000" << player->GetName().c_str() << "|r reason: \"" << reason << "\"";

		sWorld->SendGlobalText(BuildAnnounce.str().c_str(), NULL);
	}

	static void sendCMDError(ChatHandler* handler, const char* error)
    {
        handler->GetSession()->SendNotification(error);
        handler->PSendSysMessage(error);
		handler->SetSentErrorMessage(true);
    }

	static bool PlayerExists(ChatHandler* handler, std::string player)
	{
		if (!normalizePlayerName(player))
			return false;

		Player* pWarned = sObjectAccessor->FindPlayerByName(player.c_str());

		if (!pWarned)
		{
		    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GUID_BY_NAME);
			stmt->setString(0, player.c_str());
		    PreparedQueryResult resultCharacter = CharacterDatabase.Query(stmt);

		    if (!resultCharacter)
		        return false;
		}

		return true;
	}

	static bool WarnIDExists(ChatHandler* handler, uint8 warnid)
	{
		QueryResult warnCheckID = CharacterDatabase.PQuery("SELECT * FROM `player_warnings` WHERE `warnID`='%u'", warnid);

		if(!warnCheckID)
			return false;

		return true;
	}

	static bool WarnNameExists(ChatHandler* handler, char* name)
	{
		QueryResult warnCheckID = CharacterDatabase.PQuery("SELECT * FROM `player_warnings` WHERE `reported`='%s'", name);

		if(!warnCheckID)
			return false;

		return true;
	}

	static void InsertWarnInDB(Player* player, char* reportedPlayer, char* reason, uint8 priority)
	{
		CharacterDatabase.PExecute("INSERT INTO `player_warnings` (`reporter`, `reported`, `reason`, `priority`, `bindAcc`) VALUES ('%s', '%s', '%s', '%u', '%i');", player->GetName().c_str(), reportedPlayer, reason, priority, player->GetSession()->GetAccountId());
	}

	static bool CheckIfReportedSamePlayer(Player* player, char* reportedPlayer)
	{
		QueryResult warnCheckbyAcc = CharacterDatabase.PQuery("SELECT * FROM `player_warnings` WHERE `bindAcc`='%u' AND `reported`='%s'", player->GetSession()->GetAccountId(), reportedPlayer);

		if(warnCheckbyAcc)
			return false;
		
		return true;
	}

	static bool CheckIfWarnIDExists(uint32 warnid)
	{
		QueryResult warnInfo = CharacterDatabase.PQuery("SELECT * FROM `player_warnings` WHERE `warnID`='%u'", warnid);

		if(!warnInfo)
			return false;

		return true;
	}

	static void ListWarnings(ChatHandler* handler, QueryResult warnList)
	{
	    do
	    {
	        Field* list = warnList->Fetch();
	        uint8 warnID        = list[0].GetUInt8();
	        uint8 priorityAsID  = list[4].GetUInt8();
	        const char* gmName  = list[1].GetCString();
	        const char* plrName = list[2].GetCString();
	        const char* reason  = list[3].GetCString();
	        const char* priorityToStr;
	
	        switch(priorityAsID) 
	        {
	        case 1:
	            priorityToStr = "|cffff6060low|r";
	            break;
	        case 2:
	            priorityToStr = "|cffFF4500medium|r";
	            break;
	        case 3:
	            priorityToStr = "|cffFF0000high|r";
	            break;
	        default:
	            priorityToStr = "[?]";
	        }
	        handler->PSendSysMessage("|cff00ff00Id:|r |cff00ccff%u|r.|cffFF5555 %s|r |cff00ff00warned by|r|cffFF5555 %s|r|cff00ff00 with|r %s|cff00ff00 priority|r.|cff00ff00 Reason:|r|cffF9F5C8 %s|r", warnID, plrName, gmName, priorityToStr, reason);
	    } while (warnList->NextRow());
	}
	
	static bool GetWarnList(ChatHandler* handler, uint8 type, char* name)
	{
	    QueryResult warnList = NULL;
	    switch(type)
	    {
	    case 1: // listing all warnings
	        warnList = CharacterDatabase.PQuery("SELECT * FROM `player_warnings` ORDER by `priority` DESC LIMIT 20");
	        break;
	    case 2: // list warnings for player name
	        warnList = CharacterDatabase.PQuery("SELECT * FROM `player_warnings` WHERE `reported`='%s' ORDER by `priority` DESC LIMIT 20", name);
	        break;
	    }
	    if(warnList)
	        ListWarnings(handler, warnList);
	    else
	        return false;
	    return true;
	}

	static bool PWarnListAll(ChatHandler* handler, const char* /*args*/)
	{
		handler->PSendSysMessage("Displaying all players warnings:");

		if(!GetWarnList(handler, 1, NULL))
		{
			sendCMDError(handler, "|cffFF0000NULL|r");
            return false;
		}

		return true;
	}
 
	static bool PWarnListName(ChatHandler* handler, const char* args)
	{
		if(!*args)
			return false;

		char* plrname = strtok((char*)args, " ");

		if(!PlayerExists(handler, plrname))
		{
			sendCMDError(handler, "Player not found");
            return false;
		}

		handler->PSendSysMessage("Displaying all %s's warnings:", plrname);

		if(!GetWarnList(handler, 2, plrname))
		{
			sendCMDError(handler, "|cffFF0000NULL|r");
            return false;
		}

		return true;
	}

    static bool PWarnPlayer(ChatHandler* handler, const char* args)
    {
        if(!*args)
			return false;

		uint8 priorityAsID;

		Player* player = handler->GetSession()->GetPlayer();

		char* plrname = strtok((char*)args, " ");
		char* tail = *args == '"' ? (char*)args : strtok(NULL, "");
		if (!tail)
		    return false;
		char* reason = handler->extractQuotedArg(tail);
		char* priority = strtok(NULL, " ");

		if(player->GetName() == plrname)
		{
			sendCMDError(handler, "You can't warn yourself");
            return false;
		}

		if(!PlayerExists(handler, plrname))
		{
			sendCMDError(handler, "Player not found");
            return false;
		}

		if(!reason)
		{
			sendCMDError(handler, "Warning a player requires a reason and must be between quotes");
			return false;
		}

		if(!priority)
		{
			sendCMDError(handler, "You forgot to set warning priority");
			return false;
		}

		if(!CheckIfReportedSamePlayer(player, plrname))
		{
			sendCMDError(handler, "You alrady warned this player");
            return false;
		}

		if(!atoi(priority))
		{
			sendCMDError(handler, "Priority must be a numeric number");
			handler->SetSentErrorMessage(true);
			return false;
		}

		priorityAsID = atoi(priority);

		if(priorityAsID < 0 || priorityAsID > 3)
		{
			sendCMDError(handler, "Priority must be between 1 and 3 concerning low, medium or high");
			return false;
		}

		switch(priorityAsID)
		{
		case 1:
			priority = "low";
			break;
		case 2:
			priority = "medium";
			break;
		case 3:
			priority = "high";
			break;
		}

		InsertWarnInDB(player, plrname, reason, priorityAsID);

		SendGlobalAnnounce(player, plrname, reason);

		handler->PSendSysMessage("Player [%s] warned for \'%s\' with %s priority.", plrname, reason, priority);

        return true;
    }

	static bool PWarnRemoveID(ChatHandler* handler, const char* args)
	{
		if(!*args)
			return false;

		if(!atoi(args))
		{
			sendCMDError(handler, "Invalid ID");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if( !WarnIDExists(handler, atoi(args)) )
		{
			sendCMDError(handler, "This ID does not exist");
			handler->SetSentErrorMessage(true);
			return false;
		}

		CharacterDatabase.PExecute("DELETE FROM `player_warnings` WHERE `warnID`='%u'", atoi(args));

		handler->PSendSysMessage("Warn removed");

		return true;
	}

	static bool PWarnRemoveName(ChatHandler* handler, const char* args)
	{
		if(!*args)
			return false;

		char* name = strtok((char*)args, " ");

		if(!PlayerExists(handler, name))
		{
			sendCMDError(handler, "Player not found");
            return false;
		}

		if(!WarnNameExists(handler, name))
		{
			sendCMDError(handler, "This player does not have any warnings");
			handler->SetSentErrorMessage(true);
			return false;
		}

		CharacterDatabase.PExecute("DELETE FROM `player_warnings` WHERE `reported`='%s'", name);

		handler->PSendSysMessage("All %s's warnings removed", name);

		return true;
	}

};
 
void AddSC_custom_warnings()
{
    new custom_warnings();
}
