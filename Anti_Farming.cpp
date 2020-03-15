#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"

struct ReportsInfo
{
    uint32 Times;
};
static std::map<uint32, ReportsInfo> reportTimes;

class ClearTimes : public BasicEvent
{
public:
    ClearTimes() {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/)
    {
        reportTimes.clear();
        return true;
    }
};

class Anti_Farming : PlayerScript
{
public:
    Anti_Farming() : PlayerScript("Anti_Farming") { }

    void OnPVPKill(Player* killer, Player* victim)
    {
        if (killer->GetGUID() == victim->GetGUID())
            return;

        if (killer->GetSession()->GetRemoteAddress() == victim->GetSession()->GetRemoteAddress())
        {
            uint32 key = killer->GetGUID();

            killer->m_Events.AddEvent(new ClearTimes(), killer->m_Events.CalculateTime(60000));
            reportTimes[key].Times++;

            switch (reportTimes[key].Times)
            {
            case 3:
                ChatHandler(killer->GetSession()).PSendSysMessage("[AntiFarming] :: 1/3 to punish.");
                break;
            case 4:
                ChatHandler(killer->GetSession()).PSendSysMessage("[AntiFarming] :: 2/3 to punish.");
                break;
            case 5:
                sWorld->BanCharacter(killer->GetName(), "1d", "Farming", "[AntiFarming]");
                break;
            }
        }

    }
};

void AddSC_Anti_Farming()
{
    new Anti_Farming();
}
