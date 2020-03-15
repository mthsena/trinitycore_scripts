#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"

class Anti_Advertising : public PlayerScript
{
public:
    Anti_Advertising() : PlayerScript("Anti_Advertising") { }

    bool CheckMessage(Player* player, std::string& msg)
    {
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
    };

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg) override
    {
        if (!CheckMessage(player, msg))
            return;
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* /*receiver*/) override
    {
        if (!CheckMessage(player, msg))
            return;
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* /*group*/) override
    {
        if (!CheckMessage(player, msg))
            return;
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* /*guild*/) override
    {
        if (!CheckMessage(player, msg))
            return;
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* /*channel*/) override
    {
        if (!CheckMessage(player, msg))
            return;
    }
};

void AddSC_Anti_Advertising()
{
    new Anti_Advertising();
}
