/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Styler
 - Complete: 100 %
 - ScriptName: 'Reset_OnDuelEnd' 
 - Comment: This will reset HP, Mana, Cooldowns.
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
    {
						// Resets Players 1
                        winner->RemoveArenaSpellCooldowns();
					    winner->SetHealth(winner->GetMaxHealth());
                        winner->SetPower(winner->getPowerType(), winner->GetMaxPower(winner->getPowerType()));
						// Resets Player 2
						looser->RemoveArenaSpellCooldowns();
                        looser->SetHealth(looser->GetMaxHealth());
                        looser->SetPower(looser->getPowerType(), looser->GetMaxPower(looser->getPowerType()));
             //   }
    }
};

void AddSC_Reset()
{
    new Reset_OnDuelEnd;
}
