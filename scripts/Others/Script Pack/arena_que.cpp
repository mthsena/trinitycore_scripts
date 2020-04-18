#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Common.h"
#include "Language.h"
 
class arenaqueue : public CommandScript
{
public:
  arenaqueue() : CommandScript("arenaqueue") { }
 
  ChatCommand* GetCommands() const
	{
		static ChatCommand arenaCommandTable[] =
 
		{
			{ "2v2",	SEC_PLAYER,		false,	&Handle2v2Command,		"Queue's for 2v2", NULL },
			{ "3v3",	SEC_PLAYER,		false,	&Handle3v3Command,		"Queue's for 3v3", NULL },
			{ "5v5",	SEC_PLAYER,		false,	&Handle5v5Command,		"Queue's for 5v5", NULL },
			{  NULL,			 0,		false,				 NULL,					   "", NULL }
		};
 
		static ChatCommand commandTable[] =
		{
			{ "arena",	SEC_PLAYER,		true,				 NULL,					   "", arenaCommandTable},
			{    NULL,			 0,	   false,				 NULL,					   "",			   NULL }
		};
		return commandTable;
 
	}
 
	static bool Handle2v2Command(ChatHandler* handler, const char* args)
		{
		Player* me = handler->GetSession()->GetPlayer();
			if(me->GetArenaTeamId(1) != 0)
					{
					me->AddBattlegroundQueueId(BATTLEGROUND_QUEUE_2v2);
					}
			else
					{
					handler->PSendSysMessage("You aren't in an arena team.");
					}
			return true;
		}
 
	static bool Handle3v3Command(ChatHandler* handler, const char* args)
		{
		Player* me = handler->GetSession()->GetPlayer();
			if(me->GetArenaTeamId(1) != 1)
					{
					me->AddBattlegroundQueueId(BATTLEGROUND_QUEUE_3v3);
					}
			else
					{
					handler->PSendSysMessage("You aren't in an arena team.");
					}
			return true;
		}
 
	static bool Handle5v5Command(ChatHandler* handler, const char* args)
		{
		Player* me = handler->GetSession()->GetPlayer();
			if(me->GetArenaTeamId(1) != 2)
					{
						me->AddBattlegroundQueueId(BATTLEGROUND_QUEUE_5v5);
					}
			else
					{
					handler->PSendSysMessage("You aren't in an arena team.");
					}
			return true;
		}
 
	};
 
void AddSC_arenaqueue()
{
    new arenaqueue();
}