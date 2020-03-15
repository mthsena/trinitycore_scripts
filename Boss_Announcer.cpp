#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "Chat.h"

class Boss_Announcer : public PlayerScript
{
public:
    Boss_Announcer() : PlayerScript("Boss_Announcer") {}

    void OnCreatureKill(Player* killer, Creature* killed)
    {
        if (killed->isWorldBoss())
        {
            std::string msg;

            msg += "|CFF64FF64The Boss |CFFFFFFFF[";
            msg += killed->GetName();
            msg += "]|r";
            msg += "|CFF64FF64 has killed by|r ";
            msg += ChatHandler(killer->GetSession()).GetNameLink();
            msg += "|CFF64FF64 and your group.|r";
            sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
        }
    }

};

void AddSC_Boss_Announcer()
{
    new Boss_Announcer;
}