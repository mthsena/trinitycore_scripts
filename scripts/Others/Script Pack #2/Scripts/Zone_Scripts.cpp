#include "ScriptPCH.h"

class Zone_Scripts : public PlayerScript

{
public: Zone_Scripts() : PlayerScript("Zone_Scripts") { }
		
		void OnDuelStart(Player* player, Player* plTarget)
		{
			if (player->GetZoneId() == 2037)
			{
				if ( player->getPowerType() == POWER_MANA )
				{
					player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				}
				player->SetHealth(player->GetMaxHealth());
				player->RemoveArenaSpellCooldowns();
				player->RemoveAura(57723);
				player->RemoveAura(57724);
				player->RemoveAura(25771);
				player->RemoveAura(41425);
				player->RemoveAura(61987);
				player->RemoveAura(57723);
				player->RemoveAura(57724);
				player->RemoveAura(25771);
				player->RemoveAura(41425);
				player->RemoveAura(61987);
			}
			if (plTarget->GetZoneId() == 2037)
			{
				if ( plTarget->getPowerType() == POWER_MANA )
				{
					plTarget->SetPower(POWER_MANA, plTarget->GetMaxPower(POWER_MANA));
				}
				plTarget->SetHealth(plTarget->GetMaxHealth());
				plTarget->RemoveArenaSpellCooldowns();
				plTarget->RemoveAura(57723);
				plTarget->RemoveAura(57724);
				plTarget->RemoveAura(25771);
				plTarget->RemoveAura(41425);
				plTarget->RemoveAura(61987);
				plTarget->RemoveAura(57723);
				plTarget->RemoveAura(57724);
				plTarget->RemoveAura(25771);
				plTarget->RemoveAura(41425);
				plTarget->RemoveAura(61987);
			}
		}
		
		void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType /*type*/)
		{
			if (pWinner->GetZoneId() == 2037)
			{
				if ( pWinner->getPowerType() == POWER_MANA )
				{
					pWinner->SetPower(POWER_MANA, pWinner->GetMaxPower(POWER_MANA));
				}
				pWinner->SetHealth(pWinner->GetMaxHealth());
				pWinner->RemoveArenaSpellCooldowns();
				pWinner->RemoveAura(57723);
				pWinner->RemoveAura(57724);
				pWinner->RemoveAura(25771);
				pWinner->RemoveAura(41425);
				pWinner->RemoveAura(61987);
				pWinner->RemoveAura(57723);
				pWinner->RemoveAura(57724);
				pWinner->RemoveAura(25771);
				pWinner->RemoveAura(41425);
				pWinner->RemoveAura(61987);
			}
			if (pLoser->GetZoneId() == 2037)
			{
				if ( pLoser->getPowerType() == POWER_MANA )
				{
					pLoser->SetPower(POWER_MANA, pLoser->GetMaxPower(POWER_MANA));
				}
				pLoser->SetHealth(pWinner->GetMaxHealth());
				pLoser->RemoveArenaSpellCooldowns();
				pLoser->RemoveAura(57723);
				pLoser->RemoveAura(57724);
				pLoser->RemoveAura(25771);
				pLoser->RemoveAura(41425);
				pLoser->RemoveAura(61987);
				pLoser->RemoveAura(57723);
				pLoser->RemoveAura(57724);
				pLoser->RemoveAura(25771);
				pLoser->RemoveAura(41425);
				pLoser->RemoveAura(61987);
			}
		}
};
void AddSC_Zone_Scripts()
{
	new Zone_Scripts;
}