#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"

uint32 buffs[] = { 43816, 43820, 43822, 43818, 48170, 467, 69994, 48102, 24705, 26035, 69559, 35912, 22888, 26393, 35076, 36001, 48470, 53307, 34410, 24425, 25898, 26991, 32999 };

using namespace rbac;
using namespace std;

class CustomCommands : public CommandScript
{
public:
    CustomCommands() : CommandScript("CustomCommands") {}

    vector<ChatCommand> GetCommands() const override
    {
        static vector<ChatCommand> CommandsTable =
        {
            { "chat", RBAC_PERM_COMMAND_CUSTOM_CHAT, false, &HandleChatCommand, "" },
            { "buff", RBAC_PERM_COMMAND_CUSTOM_BUFF, false, &HandleBuffCommand, "" },
            { "shop", RBAC_PERM_COMMAND_CUSTOM_SHOP, false, &HandleShopCommand, "" },
            { "mail", RBAC_PERM_COMMAND_CUSTOM_MAIL, false, &HandleMailCommand, "" },
            { "bank", RBAC_PERM_COMMAND_CUSTOM_BANK, false, &HandleBankCommand, "" },
            { "maxskills", RBAC_PERM_COMMAND_CUSTOM_MAXSKILLS, false, &HandleMaxSkillsCommand, "" },
            { "tele", RBAC_PERM_COMMAND_CUSTOM_TELE, false, &HandleTeleCommand, "" },
            { "scale", RBAC_PERM_COMMAND_CUSTOM_SCALE, false, &HandleScaleCommand, "" },
            { "hover", RBAC_PERM_COMMAND_CUSTOM_HOVER, false, &HandleHoverCommand, "" },
            { "customize", RBAC_PERM_COMMAND_CUSTOM_CUSTOMIZE, false, &HandleCustomizeCommand, "" },
            { "changerace", RBAC_PERM_COMMAND_CUSTOM_CHANGERACE, false, &HandleChangeRaceCommand, "" },
            { "changefaction", RBAC_PERM_COMMAND_CUSTOM_CHANGEFACTION, false, &HandleChangeFactionCommand, "" },
            { "transfer", RBAC_PERM_COMMAND_CUSTOM_TRANSFER, false, &HandleTransferCommand, "" },
            { "castall", RBAC_PERM_COMMAND_CUSTOM_CASTALL, false, &HandleCastAllCommand, "" },
            { "summonall", RBAC_PERM_COMMAND_CUSTOM_SUMMONALL, false, &HandleSummonAllCommand, "" },
        };

        return CommandsTable;
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

    static bool AccountExists(string accountName)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s'", accountName.c_str());

        if (!result)
            return false;

        return true;
    }

    static bool CharacterExists(string characterName)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE name = '%s'", characterName.c_str());

        if (!result)
            return false;

        return true;
    }

    static bool AccountHasCharacter(uint32 accountId, string characterName)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account = %u AND name = '%s'", accountId, characterName.c_str());

        if (!result)
            return false;

        return true;
    }

    static bool HasRealmCharacter(uint32 accountId)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT acctid FROM realmcharacters WHERE acctid = %u", accountId);

        if (!result)
            return false;

        return true;
    }

    static uint32 GetCharacterAccountId(string characterName)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT account FROM characters WHERE name = '%s'", characterName.c_str());

        if (!result)
            return NULL;

        return result->Fetch()[0].GetUInt32();
    }

    static string GetAccountNameById(uint32 accountId)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", accountId);

        if (!result)
            return NULL;

        return result->Fetch()[0].GetString();
    }

    static bool CheckMessage(Player* player, std::string& msg)
    {
        size_t stringpos;

        if (msg.find("|TInterface") != string::npos)
            return false;

        if (msg.find("\n") != string::npos)
            return false;

        if (msg.find("%") != string::npos)
            return false;

        // Quests
        if ((stringpos = msg.find("|Hquest:")) != string::npos)
            return false;

        // Professions
        if ((stringpos = msg.find("|Htrade:")) != string::npos)
            return false;

        // Talents
        if ((stringpos = msg.find("|Htalent:")) != string::npos)
            return false;

        // Enchants
        if ((stringpos = msg.find("|Henchant:")) != string::npos)
            return false;

        // Achievements
        if ((stringpos = msg.find("|Hachievement:")) != string::npos)
            return false;

        // Glyphs
        if ((stringpos = msg.find("|Hglyph:")) != string::npos)
            return false;

        // Spells
        if ((stringpos = msg.find("|Hspell:")) != string::npos)
            return false;

        // Items
        if ((stringpos = msg.find("Hitem:")) != string::npos)
            return false;

        if (msg.find("|c") != string::npos && msg.find("|r") != string::npos)
            return false;

        if (msg.find("|c") != string::npos && msg.find("|h") != string::npos)
            return false;

        const char* checks[] = {
            "sytes",
            "instant",
            "dyndns",
            "no-ip",
            "http:",
            ".com",
            ".net",
            ".org",
            ".eu",
            ".fr",
            ".bg",
            ".info",
            ".br",
            "https:",
            "wow",
            "www.",
            "no-ip",
            ".zapto",
            ".biz",
            ".servegame",
        };
        const int checksize = sizeof(checks) / sizeof(*checks);

        std::string checkmsg = msg;
        checkmsg.erase(remove_if(checkmsg.begin(), checkmsg.end(), isspace), checkmsg.end());
        std::transform(checkmsg.begin(), checkmsg.end(), checkmsg.begin(), ::tolower);

        if (player->GetSession()->GetSecurity() <= SEC_PLAYER)
        {
            for (int i = 0; i < checksize; ++i)
            {
                if (checkmsg.find(checks[i]) != std::string::npos)
                {
                    msg = "";
                    ChatHandler(player->GetSession()).PSendSysMessage("Links or Bad Words are not allowed on the server.");
                    PreparedStatement * mt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_MUTE_TIME);
                    int64 muteTime = time(NULL) + 180;
                    player->GetSession()->m_muteTime = muteTime;
                    mt->setInt64(0, muteTime);
                    return false;
                }
            }
        }

        return true;
    }

    static bool SendChat(Player* player, string message)
    {
        uint16 size = message.size();
        for (uint16 i = 0; i < size; i++)
            message[i] = tolower(message[i]);

        if (!CheckMessage(player, message))
            return false;

        string faction;
        ostringstream chat_string;

        if (player->GetTeam() == ALLIANCE)
            faction = "|TInterface/PVPFrame/PVP-Currency-Alliance:16:16:0:-2|t";
        else
            faction = "|TInterface/PVPFrame/PVP-Currency-Horde:16:16:0:-2|t";

        chat_string << faction << " " << ChatHandler(player->GetSession()).GetNameLink() << " " << "|CFF00FF00" << "Chat: " << "|CFF4387C4" << message;
        char msg[1024];
        snprintf(msg, 1024, chat_string.str().c_str());

        sWorld->SendGlobalText(msg, NULL);
        return true;
    }

    static bool HandleChatCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        if (!*args)
        {
            handler->SendSysMessage("Syntax: .chat #message");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if(SendChat(player, args))
            handler->PSendSysMessage("Success! Message sent.");

        return true;
    }

    static bool HandleBuffCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        for (int i = 0; i < (sizeof(buffs) / sizeof(*buffs)); i++)
            player->AddAura(buffs[i], player);

        handler->PSendSysMessage("Success! Buffs added.");
        return true;
    }

    static bool HandleShopCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->TeleportTo(player->GetStartPosition());
        handler->PSendSysMessage("Success! You was teleported.");
        return true;
    }

    static bool HandleMailCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        handler->GetSession()->SendShowMailBox(player->GetGUID());
        handler->PSendSysMessage("Success! Mail opened.");
        return true;
    }

    static bool HandleBankCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        handler->GetSession()->SendShowBank(player->GetGUID());
        handler->PSendSysMessage("Success! Bank opened.");
        return true;
    }

    static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->UpdateSkillsToMaxSkillsForLevel();
        handler->PSendSysMessage("Success! Skills maximized.");
        return true;
    }

    static bool HandleTeleCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        if (!*args)
        {
            handler->SendSysMessage("Syntax: .tele #mapName");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);

        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }

        player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        handler->PSendSysMessage("Success! You was teleported.");
        return true;
    }

    static bool HandleScaleCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        if (!*args)
        {
            handler->SendSysMessage("Syntax: .scale #size(0.75/1.25)");
            handler->SetSentErrorMessage(true);
            return false;
        }

        float scale = (float)atof((char*)args);

        if (scale > 1.25f || scale < 0.75f)
        {
            handler->SendSysMessage("Failure! Must be between 0.75 to 1.25.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        player->SetFloatValue(OBJECT_FIELD_SCALE_X, scale);
        handler->PSendSysMessage("Success! Your size was changed.");
        return true;
    }

    static bool HandleHoverCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->CastSpell(player, 11010);
        handler->PSendSysMessage("Success! You are floating.");
        return true;
    }

    static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
        handler->PSendSysMessage("Success! Logout and customize.");
        return true;
    }

    static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
        handler->PSendSysMessage("Success! Logout and change your race.");
        return true;
    }

    static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
        handler->PSendSysMessage("Success! Logout and change your faction.");
        return true;
    }

    static bool HandleTransferCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        if (!*args)
        {
            handler->PSendSysMessage("Syntax: .transfer #characterName #newAccountName");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* c_CharName = strtok((char*)args, " ");
        char* c_NewAccountName = strtok(NULL, " ");
        if (!c_CharName || !c_NewAccountName)
            return false;

        string CharName = c_CharName;
        CharName[0] = toupper(CharName[0]);

        if (!CharacterExists(CharName))
        {
            handler->PSendSysMessage("Failure! The character %s not exists.", CharName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        string NewAccountName = c_NewAccountName;
        NewAccountName[0] = toupper(NewAccountName[0]);

        if (!AccountExists(NewAccountName))
        {
            handler->PSendSysMessage("Failure! The account %s not exists.", NewAccountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 OldAccountId = GetCharacterAccountId(CharName);
        uint32 NewAccountId = AccountMgr::GetId(NewAccountName);

        if (!AccountHasCharacter(OldAccountId, CharName))
        {
            handler->PSendSysMessage("Failure! The account %s not has the character %s.", GetAccountNameById(OldAccountId).c_str(), CharName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (AccountMgr::GetCharactersCount(NewAccountId) >= sWorld->getIntConfig(CONFIG_CHARACTERS_PER_REALM))
        {
            handler->PSendSysMessage("Failure! The account %s is full.", NewAccountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (Player* player = ObjectAccessor::FindConnectedPlayerByName(CharName.c_str()))
        {
            player->SaveToDB();
            player->GetSession()->KickPlayer();
        }

        if (!HasRealmCharacter(NewAccountId))
            LoginDatabase.PQuery("INSERT INTO realmcharacters (realmid, acctid, numchars) VALUES ('1', '%u', '0')", NewAccountId);

        LoginDatabase.PQuery("UPDATE realmcharacters SET numchars = numchars - 1 WHERE acctid = %u", OldAccountId);
        LoginDatabase.PQuery("UPDATE realmcharacters SET numchars = numchars + 1 WHERE acctid = %u", NewAccountId);
        CharacterDatabase.PQuery("UPDATE characters SET account = %u WHERE name = '%s'", NewAccountId, CharName.c_str());

        handler->PSendSysMessage("Success! The character %s was transferred to the account %s.", CharName.c_str(), NewAccountName.c_str());
        return true;
    }

    static bool HandleCastAllCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!*args)
        {
            handler->PSendSysMessage("Syntax: .castall #spellId");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!CanUseCommand(player, handler))
            return false;

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId)
            return false;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo)
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer()))
        {
            handler->PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spellId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        SessionMap sessions = sWorld->GetAllSessions();
        for (SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
        {
            Player* player = itr->second->GetPlayer();
            player->CastSpell(player, spellId, false);
        }

        handler->PSendSysMessage("Success! All players were affected.");
        return true;
    }

    static bool HandleSummonAllCommand(ChatHandler* handler, const char* args)
    {
        Player* adm = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(adm, handler))
            return false;

        SessionMap sessions = sWorld->GetAllSessions();
        for (SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
        {
            Player* player = itr->second->GetPlayer();

            if (player)
                if (player->GetSession()->GetSecurity() <= SEC_MODERATOR)
                    player->TeleportTo(adm->GetMapId(), adm->GetPositionX() + urand(2, 4), adm->GetPositionY() + urand(2, 4), adm->GetPositionZ() + urand(2, 4), adm->GetOrientation() + urand(2, 4));
        }

        handler->PSendSysMessage("Success! All players were summoned.");
        return true;
    }
};

void AddSC_CustomCommands()
{
    new CustomCommands();
}
