#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Language.h"
#include "VipSystem.h"

using namespace std;
using namespace rbac;

class VipSystemCommands : public CommandScript
{
public:
    VipSystemCommands() : CommandScript("VipSystemCommands") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> VipCommandTable =
        {
            { "add", RBAC_PERM_COMMAND_CUSTOM_VIPSYSTEM, true, &HandleVipManagerAddCommand, "" },
            { "delete", RBAC_PERM_COMMAND_CUSTOM_VIPSYSTEM, true, &HandleVipManagerDeleteCommand, "" },
            { "list", RBAC_PERM_COMMAND_CUSTOM_VIPSYSTEM, true, &HandleVipManagerListCommand, "" },
        };

        static std::vector<ChatCommand> CommandTable =
        {
            { "vipsystem", RBAC_PERM_COMMAND_CUSTOM_VIPSYSTEM, true, NULL, "", VipCommandTable },
        };

        return CommandTable;
    }

    static bool CanUseCommand(Player* player, ChatHandler* handler)
    {
        if (player->IsInFlight())
        {
            handler->PSendSysMessage("Failure! You are flying.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsInCombat())
        {
            handler->PSendSysMessage("Failure! You are in combat.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->isDead() || player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
        {
            handler->PSendSysMessage("Failure! You are dead.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        return true;
    }

    static bool HandleVipManagerAddCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        if (!*args)
        {
            handler->PSendSysMessage("Syntax: .vipsystem add #accountName #vipTime");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* account = strtok((char*)args, " ");
        char* vipTime = strtok(NULL, " ");
        if (!account || !vipTime)
            return false;

        string accountName = account;
        uint32 accountId = AccountMgr::GetId(accountName);

        if (!accountId)
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sVipSystem->IsGm(accountId))
        {
            handler->PSendSysMessage("Failure! This account is gm.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sVipSystem->IsVip(accountId))
        {
            handler->PSendSysMessage("Failure! This account is already vip.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        sVipSystem->AddVip(accountId, vipTime);
        handler->PSendSysMessage("Success! Vip added.");
        return true;
    }

    static bool HandleVipManagerDeleteCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        if (!*args)
        {
            handler->PSendSysMessage("Syntax: .vipsystem del #accountName");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* account = strtok((char*)args, " ");
        if (!account)
            return false;

        string accountName = account;
        uint32 accountId = AccountMgr::GetId(accountName);

        if (!accountId)
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sVipSystem->IsGm(accountId))
        {
            handler->PSendSysMessage("Failure! This account is gm.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sVipSystem->IsVip(accountId))
        {
            handler->PSendSysMessage("Failure! This account is not a vip.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        sVipSystem->DelVip(accountId);
        handler->PSendSysMessage("Success! Vip removed.");
        return true;
    }

    static bool HandleVipManagerListCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        QueryResult result = LoginDatabase.PQuery("SELECT id, vipTime FROM account_access WHERE gmlevel = %u", SEC_VIP);

        if (!result)
        {
            handler->PSendSysMessage("Failure! No vip found.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        do
        {
            Field* field = result->Fetch();

            uint32 accountId = field[0].GetUInt32();
            uint64 vipTime = field[1].GetUInt64();

            string accountName;
            AccountMgr::GetName(accountId, accountName);

            char msg[250];
            snprintf(msg, 250, "Account: %s.\nTime Left: %s", accountName.c_str(), secsToTimeString(vipTime - time(NULL)).c_str());

            handler->PSendSysMessage(msg);
            handler->PSendSysMessage("---------------------------------------");

        } while (result->NextRow());
        return true;
    }
};

void AddSC_VipSystemCommands()
{
    new VipSystemCommands();
}
