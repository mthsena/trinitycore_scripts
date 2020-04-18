/*

- Made by mthsena -
- Edited by Jameyboor -
*/

/*
SQL =

CREATE TABLE `anti-farm log` (
  `ID` MEDIUMINT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
	`Character` TEXT NOT NULL,
	`Account` TEXT NOT NULL,
	`Warning` MEDIUMINT(1) UNSIGNED NULL DEFAULT '0',
	PRIMARY KEY (`ID`)
)
COMMENT='used by the Anti-Farm System'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
ROW_FORMAT=DEFAULT
AUTO_INCREMENT=1
*/
#include "ScriptPCH.h"

class NoFarming : public PlayerScript
{
public: NoFarming() : PlayerScript("NoFarming") {}

void OnPVPKill(Player * killer, Player * killed)
{
	if (killer->GetGUID() == killed->GetGUID())
	{
		return;
	}
	if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress() || killed->GetMaxHealth() < 10000) // about 1/4 of the maximum hp a character can have on your server to make this fully functional.
	{
		uint32 Warning = 1;
		std::string Acc;
		std::string Char = killer->GetName();
		std::string str = "";
		str = "|cFFFFFC00[Anti-Farm System]|cFF00FFFF[|cFF60FF00" + std::string(killer->GetName()) + "|cFF00FFFF] Possible Farmer!";
		WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
		data << str;
		sWorld->SendGlobalGMMessage(&data); 
		QueryResult result = WorldDatabase.PQuery("SELECT `Warning` FROM `anti-farm log` WHERE `Character` = %s", Char);
		if(result)
		{
			Field* fields = result->Fetch();
			Warning = fields[0].GetUInt32();
		}
		result = LoginDatabase.PQuery("SELECT `username` FROM `account` WHERE `id` = %u", killer->GetSession()->GetAccountId());
		if(result)
		{
			Field* fields = result->Fetch();
			Acc = fields[0].GetString();
		}
		result = WorldDatabase.PQuery("SELECT `ID` FROM `anti-farm log` WHERE Character = %s", Char);
		if(result)
		WorldDatabase.PExecute("UPDATE `anti-farm log` SET `Warning` = Warning + 1 WHERE `Character` = %s", Char);
		else
		WorldDatabase.PExecute("INSERT INTO `anti-farm log` (`Character`, `Account`, `Warning`) VALUES (%s, %s, %u)", Char, Acc, Warning);

		result = WorldDatabase.PQuery("SELECT `Warning` FROM `anti-farm log` WHERE `Character` = %s AND `Warning` >= 5 ", Char);
		if(result)
			sWorld->BanCharacter(Char, "1d", "Ignored warnings of the Anti-Farm System", "Anti-Farm System");
		
	}
	else
	{
		return;
	}

}

};

class NoFarm_Commands : public CommandScript
{
public:
	NoFarm_Commands() : CommandScript ("NF_Commands") {}

	ChatCommand* GetCommands() const
	{

		static ChatCommand HelpDeleteSubCommandTable[] =
		{
			{ "all",		SEC_GAMEMASTER,		false,	&HandleHelpDeleteAllCommand,		"",	NULL },
			{ "ID",		SEC_GAMEMASTER,		false,	&HandleHelpDeleteIDCommand,		"",	NULL },
		};

		static ChatCommand HelpCommandSubTable[] =
		{
			{ "log",		SEC_GAMEMASTER,		false,	&HandleHelpLogCommand,		"",	NULL },
			{ "delete",		SEC_GAMEMASTER,		false,	NULL,		"",	HelpDeleteSubCommandTable },
			{ "clear",		SEC_GAMEMASTER,		false,	&HandleHelpClearCommand,		"",	NULL },
			{ NULL,			0,				false,	NULL,						"",	NULL }
		};

		static ChatCommand DeleteCommandSubTable[] =
		{
			{ "all",		SEC_GAMEMASTER,		true,	&HandleDeleteAllCommand,		"",	NULL },
			{ "ID",		SEC_GAMEMASTER,		true,	&HandleDeleteIDCommand,		"",	NULL },
			{ NULL,			0,				false,	NULL,						"",	NULL }
		};
		static ChatCommand AFSSubCommandTable[] =
		{
			{ "log",		SEC_GAMEMASTER,		true,	&HandleLogCommand,		"",	NULL },
			{ "delete",		SEC_ADMINISTRATOR,		true,	NULL,		"", DeleteCommandSubTable },
			{ "help",		SEC_GAMEMASTER,		false,	NULL,		"", HelpCommandSubTable },
			{ "editai",		SEC_ADMINISTRATOR,		true,	&HandleEditAICommand,		"",	NULL },
			{ NULL,			0,				false,	NULL,						"",	NULL }
		};

		
		static ChatCommand CommandTable[] =
		{
			{ "afs",	SEC_GAMEMASTER,		true,	NULL,		"",	AFSSubCommandTable },
			{ NULL,			0,				false,	NULL,		"",	NULL }
		};
		return CommandTable;
	}

	static bool HandleLogCommand(ChatHandler* handler, const char* args)
	{
		WorldSession * Session = handler->GetSession();
		Player* player = Session->GetPlayer();
		uint32 RLimit = 10;
		if((char*)args)
		RLimit = atoi((char*)args);

		if(RLimit == 0 || RLimit > 100)
			RLimit = 10;

		QueryResult result = WorldDatabase.PQuery("SELECT * FROM `anti-farm log` LIMIT %u", RLimit);
		if(!result)
		{
			Session->SendNotification("There are no records");
				return false;
		}
		Field * fields = NULL;
	do{
		fields = result->Fetch();
		uint32 ID = fields[0].GetUInt32();
		std::string Character = fields[1].GetString();
		std::string Account = fields[2].GetString();
		uint32 Warning = fields[3].GetUInt32();
		char msg[250];
		snprintf(msg, 250, "ID : %u Character : %s Account : %s Warning Level : %u \n" , ID, Character.c_str(), Account.c_str(), Warning);
		handler->PSendSysMessage (msg);
		handler->SetSentErrorMessage (true);
	  }
	while(result->NextRow());
	return true;
	}

	static bool HandleDeleteAllCommand(ChatHandler* handler, const char* args)
	{
		WorldSession * Session = handler->GetSession();
		Player* player = Session->GetPlayer();
	    WorldDatabase.Execute("DELETE FROM `anti-farm log`");
		QueryResult result = WorldDatabase.Query("SELECT `ID` FROM `anti-farm log`");
		if(result)
		{
			Session->SendNotification("Deletion failed");
			return false;
		}
		else
		{
			Session->SendAreaTriggerMessage("Deletion successful!");
			return true;
		}
		return true;
	}

	static bool HandleDeleteIDCommand(ChatHandler* handler, const char* args)
	{
		if(!*args)
			return false;
		WorldSession * Session = handler->GetSession();
		Player* player = Session->GetPlayer();
		uint32 ID = atoi((char*)args);
		QueryResult result = WorldDatabase.PQuery("SELECT * FROM `anti-farm log` WHERE `ID` = %u", ID);
		if(!result)
		{
			char msg [250];
			snprintf(msg, 250, "Log with Log ID : %u doesn't exist", ID);
			Session->SendNotification(msg);
			return false;
		}
		WorldDatabase.PExecute("DELETE FROM `anti-farm log` WHERE `ID` = %u", ID);
		Session->SendAreaTriggerMessage("Deletion of Log ID : %u Successful!", ID);
		return true;
	}

	static bool HandleHelpLogCommand(ChatHandler* handler, const char* args)
	{
		handler->PSendSysMessage("This command allows you to check the Database Log for abusers of the Anti-Farm System \n");
		handler->PSendSysMessage("Entering a number after this command will be used to check the maximum lines shown \n");
		handler->PSendSysMessage("Example : \".afs log 15\" will show the first 15 records, even if there are more.");
		handler->SetSentErrorMessage(true);
		return true;
	}

	static bool HandleHelpDeleteAllCommand(ChatHandler* handler, const char* args)
	{
		handler->PSendSysMessage("This command will delete all existing records of abusers \n");
		handler->PSendSysMessage("This command does not have any arguments.");
		handler->SetSentErrorMessage(true);
		return true;
	}

	static bool HandleHelpDeleteIDCommand(ChatHandler* handler, const char* args)
	{
		handler->PSendSysMessage("This command will let you delete a specific record from the Database \n");
		handler->PSendSysMessage("Entering a number after this command will act like the ID of the record \n");
		handler->PSendSysMessage("Example : \".afs delete ID 50 \" will delete the record with ID 50.");
		handler->SetSentErrorMessage(true);
		return true;
	}
	static bool HandleHelpClearCommand(ChatHandler* handler, const char* args)
	{
		handler->SendSysMessage("This command edits the starting point of the Auto Incrementation for the ID column according to your argument");
		handler->SendSysMessage("this is usually used when the number of ID gets too high after \n the  records lower than the Auto Increment are deleted");
		handler->SendSysMessage("Example : \".afs editAI 50\" will edit the starting point of the Auto Incrementation to 50.");
		handler->SetSentErrorMessage(true);
		return true;
	}

    static bool HandleEditAICommand(ChatHandler* handler, const char* args)
	{
		uint32 AIedit = atoi((char*)args);
		WorldSession * Session = handler->GetSession();
		Player* player = Session->GetPlayer();
		WorldDatabase.PExecute("ALTER TABLE `anti-farm log` AUTO_INCREMENT = %u", AIedit);
		Session->SendAreaTriggerMessage("Auto Increment starting point successfully set to %u", AIedit);
		return true;
	}
};
void AddSC_NoFarming()
{
   new NoFarming();
   new NoFarm_Commands();
}
