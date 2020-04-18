#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Group.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"

//This script is made by Blex and was orginally posted on www.ac-web.org
//This script was created after being inspired by Arena-Tournament's player commands. www.arena-tournament.com

class utility_commandscript : public CommandScript
{
public:
    utility_commandscript() : CommandScript("utility_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand utilityCommandTable[] =
        {
            { "changerace",             SEC_PLAYER,  false, &HandleChangeRaceCommand,           "", NULL },
			{ "changefaction",			SEC_PLAYER,  false, &HandleChangeFactionCommand,		"", NULL },
			{ "maxskills",			    SEC_PLAYER,  false, &HandleMaxSkillsCommand,	    	"", NULL },
			{ "customize",			    SEC_PLAYER,  false, &HandleCustomizeCommand,	       	"", NULL },
			{ "mmr",			        SEC_PLAYER,  false, &HandleMMRCommand,      	       	"", NULL },
            { NULL,             0,                   false, NULL,                               "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "utility",           SEC_PLAYER,      true, NULL,                   "", utilityCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

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

	static bool HandleMaxSkillCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* me=handler->GetSession()->GetPlayer();
        {
            handler->SendSysMessage("Your Weapon Skills are now maximized.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // each skills that have max skill value dependent from level seted to current level max skill value
        me->UpdateSkillsToMaxSkillsForLevel();
        return true;
    }

	static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relog to customize your character.");
        return true;
    }

	 static bool HandleMMRCommand(ChatHandler* handler, const char* args)
     {
        Player* player = handler->GetSession()->GetPlayer();

        // 2s MMR check
        uint16 mmrTwo;
        {
			if (ArenaTeam *getmmr = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(0)))
			    mmrTwo = getmmr->GetMember(player->GetGUID())->MatchMakerRating;
		     else if (!mmrTwo)
			    mmrTwo = 1500;
        }
		uint16 mmrThree;
        {
			if (ArenaTeam *getmmr = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(1)))
			    mmrThree = getmmr->GetMember(player->GetGUID())->MatchMakerRating;
		     else if (!mmrThree)
			    mmrThree = 1500;
        }
	    handler->PSendSysMessage("Your mmr from 2v2 arena match is: %u.", mmrTwo);
	    handler->PSendSysMessage("Your mmr from 3v3 arena match is: %u.", mmrThree);
	    handler->PSendSysMessage("You search 2v2 player with mmr between: %u, - %u. For 3v3 Between: %u - %u.", (mmrTwo - 300), (mmrTwo + 300), (mmrThree - 300), (mmrThree + 300));
		return true;
      }
};

void AddSC_utility_commandscript()
{
    new utility_commandscript();
}

