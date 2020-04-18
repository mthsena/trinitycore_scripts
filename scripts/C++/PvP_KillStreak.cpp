#include "ScriptMgr.h"
#include "Player.h"

struct KillData
{
    uint32 kills;
};
static std::map<uint32, KillData> DataKills;

class ClearTimes : public BasicEvent
{
public:
    ClearTimes() {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/)
    {
        DataKills.clear();
        return true;
    }
};

void alertServer(Player* killer, Player* victim, uint32 killstreak)
{
    std::ostringstream string;

    std::string killstreakStr;

    switch (killstreak)
    {
    case 2:
        killstreakStr = "|cff3f83e0Double Kill|r";
        break;
    case 3:
        killstreakStr = "|cff59e77eTriple Kill|r";
        break;
    case 4:
        killstreakStr = "|cff48f6e3Ultra Kill|r";
        break;
    case 5:
        killstreakStr = "|cffe791dcMonster Kill|r";
        break;
    case 6:
        killstreakStr = "|cfff9f475Rampage|r";
        break;
    case 7:
        killstreakStr = "|cffff3d3dGodlike|r";
        break;
    }

    string << "|cffff9900<Campo de Batalha> |cffffffff[" << killer->GetName() << "]|cffff9900 fez |cffffffff[" << killstreakStr << "] - |cffffffff[" << victim->GetName() << "]|r |cffff9900 morreu honrado.";

    char msg[1024];

    snprintf(msg, 1024, string.str().c_str());

    sWorld->SendGlobalText(msg, NULL);
}

class PvP_KillStreak : public PlayerScript
{
public:
    PvP_KillStreak() : PlayerScript("PvP_KillStreak"){ }

    void OnPVPKill(Player* killer, Player* victim)
    {
        if (killer->GetGUID() == victim->GetGUID())
            return;

        if (killer->InArena() || victim->InArena())
            return;

        if (!killer->InBattleground() || !victim->InBattleground())
            return;

        uint32 data = killer->GetGUID();

        killer->m_Events.AddEvent(new ClearTimes(), killer->m_Events.CalculateTime(300000));
        DataKills[data].kills++;

        switch (DataKills[data].kills)
        {
        case 2:
            alertServer(killer, victim, DataKills[data].kills);
            break;
        case 3:
            alertServer(killer, victim, DataKills[data].kills);
            break;
        case 4:
            alertServer(killer, victim, DataKills[data].kills);
            break;
        case 5:
            alertServer(killer, victim, DataKills[data].kills);
            break;
        case 6:
            alertServer(killer, victim, DataKills[data].kills);
            break;
        case 7:
            alertServer(killer, victim, DataKills[data].kills);
            break;
        case 8:
            DataKills.clear();
            break;
        }
    }
};

void AddSC_PvP_KillStreak()
{
    new PvP_KillStreak();
}