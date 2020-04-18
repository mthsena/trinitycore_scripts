#include "ScriptPCH.h"
     
class commands : public CommandScript
    {
    public:
            commands() : CommandScript("commands"){}
     
            ChatCommand * GetCommands() const
            {
                    static ChatCommand commandsCommandTable[] =
                    {
                            {"maxskills",       SEC_MODERATOR, false, &HandleMaxSkillsCommand,    "", NULL},
                            {"changefaction",     SEC_MODERATOR, false, &HandleChangeFactionCommand,          "", NULL},
                            {"changerace",      SEC_MODERATOR,     false, &HandleChangeRaceCommand, "", NULL},
                            {"customize",     SEC_MODERATOR, false, &HandleCustomizeCommand,          "", NULL},
                            {"mall",     SEC_MODERATOR, false, &HandleMallCommand,          "", NULL},
                            {"teleport",     SEC_MODERATOR, false, &HandleTeleportCommand,          "", NULL},
     
                            {NULL,          0,                              false,          NULL,                                           "", NULL}
                    };
     
                    return commandsCommandTable;
            }
            static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
            {
     
                    Player* player = handler->GetSession()->GetPlayer();
     
                    if (player->IsDead() || player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                    {
                            player->GetSession()->SendNotification("You can't chat when you're dead!");
                            handler->SetSentErrorMessage(true);
                            return false;
                    }
     
                    player->UpdateSkillsToMaxSkillsForLevel();
                    return true;
            }
            static bool HandleChangeFactionCommand(ChatHandler * handler, const char * args)
            {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		handler->PSendSysMessage("Relog to change faction of your character.");
        return true;
            }
			static bool HandleChangeRaceCommand(ChatHandler * handler, const char * args)
            {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
		handler->PSendSysMessage("Relog to change race of your character.");
        return true;
            }
			static bool HandleCustomizeCommand(ChatHandler * handler, const char * args)
            {
            
        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relog to customize your character.");
        return true;
            }
                         static bool HandleMallCommand(ChatHandler * handler, const char * args)
            {
            
        Player* me = handler->GetSession()->GetPlayer();
		me->TeleportTo(1,  -8409.883789f, 2095.069580f, 145.070374f, 5.108553f); // edit location to your needs.
		handler->PSendSysMessage("Successfully teleported.");
        return true;
            }
static bool HandleTeleportCommand(ChatHandler * handler, const char * args)
    {
        if (!*args)
            return false;
        Player* me = handler->GetSession()->GetPlayer();
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);

        if (!tele)
        {
            handler->PSendSysMessage("Location not found.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (me->IsInCombat())
        {
            handler->PSendSysMessage("You are in combat.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->PSendSysMessage("You cannot teleport to battlegrounds or arenas.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        else
            me->SaveRecallPosition();
        me->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
		handler->PSendSysMessage("Successfully teleported.");
        return true;
		}
     
    };
     
    void AddSC_commands()
    {
            new commands();
}