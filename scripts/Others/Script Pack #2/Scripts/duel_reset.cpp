#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "Config.h"

class duel_reset : public PlayerScript
{
public:
    duel_reset() : PlayerScript("duel_reset") {}

    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
    {
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN_ON_FINISH))
        {
                    if (type == DUEL_WON)
                    {
                        winner->SetHealth(winner->GetMaxHealth());
                        looser->SetHealth(looser->GetMaxHealth());

                        if (winner->getPowerType() == POWER_MANA) 
                            winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));

                        if (looser->getPowerType() == POWER_MANA) 
                            looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
                    }

            else
                if (type == DUEL_WON)
                {
                    winner->SetHealth(winner->GetMaxHealth());
                    looser->SetHealth(looser->GetMaxHealth());

                    if (winner->getPowerType() == POWER_MANA) 
                        winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));

                    if (looser->getPowerType() == POWER_MANA) 
                        looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
                }
        }
    }
};
void AddSC_DuelReset()
{
    new duel_reset();
}
