#include "ScriptPCH.h"
#include "Channel.h"

class System_Censure : public PlayerScript
{
    public:
        System_Censure() : PlayerScript("System_Censure") {}

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg)
        {
            CheckMessage(player, msg, lang, NULL, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
        {
            CheckMessage(player, msg, lang, receiver, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group)
        {
            CheckMessage(player, msg, lang, NULL, group, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
        {
            CheckMessage(player, msg, lang, NULL, NULL, guild, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel)
        {
            CheckMessage(player, msg, lang, NULL, NULL, NULL, channel);
        }

    void CheckMessage(Player* player, std::string& msg, uint32 lang, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
    {
        if (player->isGameMaster() || lang == LANG_ADDON)
            return;

        // transform to lowercase (for simpler checking)
        std::string lower = msg;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        const uint8 cheksSize = 38;
        std::string checks[cheksSize];
        // Strony (Sites)
        checks[0] ="http://";
        checks[1] =".com";
        checks[2] =".www";
        checks[3] =".net";
        checks[4] =".org";
        checks[5] =".ru";
        checks[6] ="www.";
        checks[7] ="wow-";
        checks[8] ="-wow";
        checks[9] =".pl";
		checks[10] =".bg";
		checks[11] =".eu";
		checks[12] =".biz";
		checks[13] =".-ip";
		checks[14] =".-zapto.org";
        for (int i = 0; i < cheksSize; ++i)
             if (lower.find(checks[i]) != std::string::npos)
             {
                 msg = "";
                 ChatHandler(player->GetSession()).PSendSysMessage("Advertising and vulgar behavior is not allowed!");
                 return;
             }
    }
};

void AddSC_System_Censure()
{
    new System_Censure();
}
