/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Styler
 - Complete: 90%
 - ScriptName: 'vipcommands' 
 - Comment: VIP commands for VIPS -> GM rank 1+
<--------------------------------------------------------------------------->
*/

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Common.h"
#include "Language.h"


class vipcommands : public CommandScript
{
public:
    vipcommands() : CommandScript("vipcommands") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand vipCommandTable[] =

        {
			{ "summon",				 SEC_PLAYER,  false, &HandleSummon,					"", NULL },
			{ "appear",				 SEC_PLAYER,  false, &HandleAppear,					"", NULL },
			{ "mall",          	 	 SEC_PLAYER,  false, &HandleVipMallCommand,         "", NULL },
			{ "changerace",          SEC_PLAYER,  false, &HandleChangeRaceCommand,      "", NULL },
			{ "changefaction",		 SEC_PLAYER,  false, &HandleChangeFactionCommand,	"", NULL },
			{ "maxskills",			 SEC_PLAYER,  false, &HandleMaxSkillsCommand,		"", NULL },
			{ "customize",			 SEC_PLAYER,  false, &HandleCustomizeCommand,		"", NULL },
            { NULL,             0,                false, NULL,                          "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "vip",	    SEC_PLAYER,   true, NULL,      "",  vipCommandTable},
	       { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }
	static bool HandleSummon(ChatHandler * handler, const char* args)
	{

		return true;
	}

	static bool HandleAppear(ChatHandler * handler, const char* args)
	{

		return true;
	}

	
	static bool HandlevipCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

            me->Say("vip command?", LANG_UNIVERSAL);
            return true;
    }


	/* The commands */

	static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
		handler->PSendSysMessage("Relog to change race of your character.");
        return true;
    }

		static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		handler->PSendSysMessage("Relog to change faction of your character.");
        return true;
    }

		static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->UpdateSkillsForLevel();
		handler->PSendSysMessage("Your weapon skills are now maximized.");
        return true;
    }

	static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relog to customize your character.");
        return true;
    }

	static bool HandleVipMallCommand(ChatHandler* handler, const char* args)
    {

            Player* me = handler->GetSession()->GetPlayer();

        if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

		me->TeleportTo(571, 6224.2753f,	5757.725098f, -6.372915f, 0.75708f); // MapId, X, Y, Z, O
		handler->PSendSysMessage("You Have Been Teleported!");
        return true;
    }
	    
};

void AddSC_vipcommands()
{
    new vipcommands();
}