#include "ScriptPCH.h"

class Killstreak_System : public PlayerScript
{
public:
    Killstreak_System() : PlayerScript("Killstreak_System") {}

    void OnPVPKill(Player * Killer, Player * Victim)
    {
        uint32 KillerGUID = Killer->GetGUIDLow();
        uint32 VictimGUID = Victim->GetGUIDLow();

        struct KillStreak_Info
        {
            uint32 killstreak;
            uint32 lastkill;
        };

        static std::map<uint32, KillStreak_Info> KillStreakData;

        if (KillerGUID == VictimGUID || KillStreakData[KillerGUID].lastkill == VictimGUID)
            return;

        if (KillStreakData[VictimGUID].killstreak >= 3)
        {
            std::ostringstream ss;
            ss << "|cFF81CF42" << Killer->GetName() << "|r Has Ended |cFFFFFFFF" << Victim->GetName() << " !!!! ";
            sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        }

        ++KillStreakData[KillerGUID].killstreak;
        KillStreakData[KillerGUID].lastkill = VictimGUID;
        KillStreakData[VictimGUID].killstreak = 0;
        KillStreakData[VictimGUID].lastkill = 0;

        if (KillStreakData[KillerGUID].killstreak % 3 == 0) // send killstreak message every 3 kills
        {
            std::ostringstream ss;
            ss << "|cFF81CF42" << Killer->GetName() << "|r Has A KillStreak Of |cFF42A0CF" << KillStreakData[KillerGUID].killstreak << "|r!!!!!";
            sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        }
        else if (KillStreakData[KillerGUID].killstreak == 3)
        {
            std::ostringstream ss;
            ss << "|cFF81CF42" << Killer->GetName() << "|r Is On A Killing Spree!!";
            sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
        }

    }
};

void AddSC_Killstreak_System()
{
    new Killstreak_System;
}