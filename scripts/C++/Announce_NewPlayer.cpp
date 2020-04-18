#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"

class Announce_NewPlayer : public PlayerScript
{
public:
    Announce_NewPlayer() : PlayerScript("Announce_NewPlayer") { }

    void OnLogin(Player * player, bool firstLogin)
    {
        std::string msg, faction;

        if (player->GetTeam() == ALLIANCE)
            faction = "|TInterface/PVPFrame/PVP-Currency-Alliance:16:16:0:-2|t";
        else
            faction = "|TInterface/PVPFrame/PVP-Currency-Horde:16:16:0:-2|t";

        if (firstLogin)
        {
            msg += "|cff009bffNew character created - ";
            msg += ChatHandler(player->GetSession()).GetNameLink();
            msg += faction;
            sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str());
            return;
        }

        msg += faction;
        msg += ChatHandler(player->GetSession()).GetNameLink();
        msg += " |CFF00FF00Is Online!|r";
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str());
    }
};

void AddSC_Announce_NewPlayer()
{
    new Announce_NewPlayer();
}