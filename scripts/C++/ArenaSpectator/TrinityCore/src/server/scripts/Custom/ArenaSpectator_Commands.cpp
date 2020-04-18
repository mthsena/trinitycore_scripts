#include "ScriptPCH.h"
#include "Chat.h"
#include "ArenaTeamMgr.h"
#include "BattlegroundMgr.h"
#include "WorldSession.h"
#include "Player.h"
#include "ArenaTeam.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "CreatureTextMgr.h"
#include "Config.h"

using namespace rbac;
using namespace std;

class ArenaSpectator_Commands : public CommandScript
{
public:
    ArenaSpectator_Commands() : CommandScript("ArenaSpectator_Commands") { }

    vector<ChatCommand> GetCommands() const override
    {
        static vector<ChatCommand> spectateCommandTable =
        {
            { "player", RBAC_PERM_COMMAND_SPECTATE_PLAYER, false, &HandleSpectatePlayerCommand, "" },
            { "view", RBAC_PERM_COMMAND_SPECTATE_VIEW, false, &HandleSpectateViewCommand, "" },
            { "reset", RBAC_PERM_COMMAND_SPECTATE_RESET, false, &HandleSpectateResetCommand, "" },
            { "leave", RBAC_PERM_COMMAND_SPECTATE_LEAVE, false, &HandleSpectateLeaveCommand, "" },
        };

        static vector<ChatCommand> commandTable =
        {
            { "spectate", RBAC_PERM_COMMAND_SPECTATE, false, NULL, "", spectateCommandTable },
        };

        return commandTable;
    }

    static bool HandleSpectatePlayerCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        ObjectGuid target_guid;
        std::string target_name;

        if (!handler->extractPlayerTarget((char*)args, &target, &target_guid, &target_name))
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        if (target == player || target_guid == player->GetGUID())
        {
            handler->PSendSysMessage("You can't spectate yourself.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsInCombat())
        {
            handler->PSendSysMessage("You are in combat.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!target)
        {
            handler->PSendSysMessage("Target is not online or does not exist.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetPet())
        {
            handler->PSendSysMessage("You must hide your pet.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetMap()->IsBattlegroundOrArena() && !player->IsSpectator())
        {
            handler->PSendSysMessage("You are already in a battleground or arena.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Map* cMap = target->GetMap();

        if (!cMap->IsBattleArena())
        {
            handler->PSendSysMessage("Player is not in an Arena match.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetMap()->IsBattleground())
        {
            handler->PSendSysMessage("You can't do that while in a battleground.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target->HasAura(32728) || target->HasAura(32727))
        {
            handler->PSendSysMessage("You can't do that. The Arena match didn't start yet.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target->IsSpectator())
        {
            handler->PSendSysMessage("You can't do that. Your target is a spectator.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsMounted())
        {
            handler->PSendSysMessage("Cannot Spectate while mounted.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // all's well, set bg id
        // when porting out from the bg, it will be reset to 0
        player->SetBattlegroundId(target->GetBattlegroundId(), target->GetBattlegroundTypeId());
        // remember current position as entry point for return at bg end teleportation
        if (!player->GetMap()->IsBattlegroundOrArena())
            player->SetBattlegroundEntryPoint();

        // stop flight if need
        if (player->IsInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            player->SaveRecallPosition();

        // search for two teams
        Battleground *bGround = target->GetBattleground();
        if (bGround->isRated())
        {
            uint32 slot = bGround->GetArenaType() - 2;
            if (bGround->GetArenaType() > 3)
                slot = 2;
            uint32 firstTeamID = target->GetArenaTeamId(slot);
            uint32 secondTeamID = 0;
            Player *firstTeamMember = target;
            Player *secondTeamMember = NULL;
            for (Battleground::BattlegroundPlayerMap::const_iterator itr = bGround->GetPlayers().begin(); itr != bGround->GetPlayers().end(); ++itr)
                if (Player* tmpPlayer = ObjectAccessor::FindPlayer(itr->first))
                {
                    if (tmpPlayer->IsSpectator())
                        continue;

                    uint32 tmpID = tmpPlayer->GetArenaTeamId(slot);
                    if (tmpID != firstTeamID && tmpID > 0)
                    {
                        secondTeamID = tmpID;
                        secondTeamMember = tmpPlayer;
                        break;
                    }
                }

            if (firstTeamID > 0 && secondTeamID > 0 && secondTeamMember)
            {
                ArenaTeam *firstTeam = sArenaTeamMgr->GetArenaTeamById(firstTeamID);
                ArenaTeam *secondTeam = sArenaTeamMgr->GetArenaTeamById(secondTeamID);
                if (firstTeam && secondTeam)
                {
                    handler->PSendSysMessage("You entered a Rated Arena.");
                    handler->PSendSysMessage("Teams:");
                    handler->PSendSysMessage("|cFFffffff%s|r vs |cFFffffff%s|r", firstTeam->GetName().c_str(), secondTeam->GetName().c_str());
                    handler->PSendSysMessage("|cFFffffff%u(%u)|r -- |cFFffffff%u(%u)|r", firstTeam->GetRating(), firstTeam->GetAverageMMR(firstTeamMember->GetGroup()), secondTeam->GetRating(), secondTeam->GetAverageMMR(secondTeamMember->GetGroup()));
                }
            }
        }

        // to point to see at target with same orientation
        float x, y, z;
        target->GetContactPoint(player, x, y, z);

        player->TeleportTo(target->GetMapId(), x, y, z, player->GetAngle(target), TELE_TO_GM_MODE);
        player->SetPhaseMask(target->GetPhaseMask(), true);
        player->SetSpectate(true);
        target->GetBattleground()->AddSpectator(player->GetGUID());

        return true;
    }

    static bool HandleSpectateViewCommand(ChatHandler* handler, const char *args)
    {
        Player* target;
        ObjectGuid target_guid;
        std::string target_name;
        if (!handler->extractPlayerTarget((char*)args, &target, &target_guid, &target_name))
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        if (!target)
        {
            handler->PSendSysMessage("Player is not online or does not exist.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!player->IsSpectator())
        {
            handler->PSendSysMessage("You are not a spectator, spectate someone first.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target->IsSpectator() && target != player)
        {
            handler->PSendSysMessage("You can't do that. Your target is a spectator.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetMap() != target->GetMap())
        {
            handler->PSendSysMessage("You can't do that. Your target might be in a different arena match.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target && target->HasAuraType(SPELL_AURA_MOD_STEALTH))
        {
            handler->PSendSysMessage("You can't target stealthed players.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check for arena preperation
        // if exists than battle didn`t begin
        if (target && target->HasAura(32728) || target->HasAura(32727))
        {
            handler->PSendSysMessage("You can't do that. The Arena match didn't start yet.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target == player && player->getSpectateFrom())
            player->SetViewpoint(player->getSpectateFrom(), false);
        else
            player->SetViewpoint(target, true);
        return true;
    }

    // addon data
    static bool HandleSpectateResetCommand(ChatHandler* handler, const char *args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player->IsSpectator())
        {
            handler->PSendSysMessage("You are not a spectator.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Battleground *bGround = player->GetBattleground();
        if (!bGround)
            return false;

        if (bGround->GetStatus() != STATUS_IN_PROGRESS)
            return true;

        for (Battleground::BattlegroundPlayerMap::const_iterator itr = bGround->GetPlayers().begin(); itr != bGround->GetPlayers().end(); ++itr)
            if (Player* tmpPlayer = ObjectAccessor::FindPlayer(itr->first))
            {
                if (tmpPlayer->IsSpectator())
                    continue;

                uint32 tmpID = bGround->GetPlayerTeam(tmpPlayer->GetGUID());

                // generate addon massage
                std::string pName = tmpPlayer->GetName();
                std::string tName = "";

                if (Player *target = tmpPlayer->GetSelectedPlayer())
                    tName = target->GetName();

                SpectatorAddonMsg msg;
                msg.SetPlayer(pName);
                if (tName != "")
                    msg.SetTarget(tName);
                msg.SetStatus(tmpPlayer->IsAlive());
                msg.SetClass(tmpPlayer->getClass());
                msg.SetCurrentHP(tmpPlayer->GetHealth());
                msg.SetMaxHP(tmpPlayer->GetMaxHealth());
                Powers powerType = tmpPlayer->getPowerType();
                msg.SetMaxPower(tmpPlayer->GetMaxPower(powerType));
                msg.SetCurrentPower(tmpPlayer->GetPower(powerType));
                msg.SetPowerType(powerType);
                msg.SetTeam(tmpID);
                msg.SendPacket(player->GetGUID());
            }

        return true;
    }

    static bool HandleSpectateLeaveCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!player->IsSpectator() || player->isSpectateCanceled())
        {
            handler->PSendSysMessage("You are not a spectator.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // RemoveSpectator shouldn't be needed to be done explicitly as it'll be done in the CancelSpectate func
        //player->GetBattleground()->RemoveSpectator(player->GetGUID());
        player->CancelSpectate();
        player->TeleportToBGEntryPoint();

        return true;
    }
};

void AddSC_ArenaSpectator_Commands()
{
    new ArenaSpectator_Commands();
}
