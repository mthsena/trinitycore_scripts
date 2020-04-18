/*
PKstreak 
*/
#include "ScriptPCH.h"
#include "Chat.h"

class PK_Win : public PlayerScript
{
public:
	PK_Win() : PlayerScript("PK_Win") { }

	void OnDuelStart(Player* Player1, Player* Player2)
	{
		/*--PK BEGIN--*/
		//Gives casters full power
		Player1->SetHealth(Player1->GetMaxHealth());
		Player2->SetHealth(Player2->GetMaxHealth());
		Player1->SetPower(POWER_MANA, Player1->GetMaxPower(POWER_MANA));
		Player2->SetPower(POWER_MANA, Player2->GetMaxPower(POWER_MANA));
		Player1->SetPower(POWER_RAGE, Player1->GetMaxPower(POWER_RAGE));
		Player2->SetPower(POWER_RAGE, Player2->GetMaxPower(POWER_RAGE));
		Player1->SetPower(POWER_ENERGY, Player1->GetMaxPower(POWER_ENERGY));
		Player2->SetPower(POWER_ENERGY, Player2->GetMaxPower(POWER_ENERGY));
		Player1->SetPower(POWER_RUNIC_POWER, Player1->GetMaxPower(POWER_RUNIC_POWER));
		Player2->SetPower(POWER_RUNIC_POWER, Player2->GetMaxPower(POWER_RUNIC_POWER));
		//Resets CDs
		Player1->RemoveArenaSpellCooldowns();
		Player2->RemoveArenaSpellCooldowns();
		//Begin info
		Player1->GetSession()->SendNotification("Good luck !");
		Player2->GetSession()->SendNotification("Good luck !");
	}

	void OnDuelEnd(Player* Winner, Player* Loser, DuelCompleteType type)
	{
		if (type != DUEL_WON)
			return;
		{
			/*--PK END--*/
			//Gives winner money and Decrease Loser money
			Winner->ModifyMoney(100);
			Loser->ModifyMoney(50);
			//Set winner auras
			Winner->AddAura(16791, Winner); 
			//Gives winner items
			Winner->AddItem(11966, 1);
			//Resets casters full power
			Winner->SetHealth(Winner->GetMaxHealth());
			Loser->SetHealth(Loser->GetMaxHealth());
			Winner->ResetAllPowers();
			Loser->ResetAllPowers();
			//Resets CDs
			Winner->RemoveArenaSpellCooldowns();
			Loser->RemoveArenaSpellCooldowns();
			//Over info
			Winner->GetSession()->SendNotification("Well done, continue to !");
			Loser->GetSession()->SendNotification("You must practice exercises !");
		}
	}

};

void AddSC_PK_Win()
{
	new PK_Win();
}