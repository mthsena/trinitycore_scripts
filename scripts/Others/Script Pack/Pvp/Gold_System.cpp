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
 - Developer(s): Jamma
 - Complete: 100%
 - ScriptName: 'Gold System' 
 - Comment: This is the basic Gold per Kill System
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"
#define FFA_ENTER_MSG "You entered FFA arena"
#define KILL_MSG "Good job you killed someone"
#define LOST_GOLD_MSG "You lost gold"
#define ERR_TOO_MUCH_MONEY "You have too much money."

enum Rewards
{
	FFA_REWARD    = 20000,
	NORMAL_REWARD = 10000,
	FFA_LOST      = 10000
};
class Gold_System : public PlayerScript
{
public:
	Gold_System() : PlayerScript("Gold_System") {}


	void OnUpdateZone(Player* player, uint32 zone, uint32 area)
	{
		if(player->pvpInfo.inFFAPvPArea) //gets updated by UpdatePvPState
		{
			ChatHandler handler(player->GetSession());
			handler.PSendSysMessage(FFA_ENTER_MSG);
		}
	}
	void OnPVPKill(Player* killer, Player* victim)
	{
		ChatHandler kHandler(killer->GetSession());
		ChatHandler vHandler(victim->GetSession());
		if(killer->pvpInfo.inFFAPvPArea && victim->pvpInfo.inFFAPvPArea) //gets updated by UpdatePvPState
		{
			if(killer->GetMoney() + FFA_REWARD < MAX_MONEY_AMOUNT)
			{
			killer->SetMoney(killer->GetMoney() + FFA_REWARD);
			kHandler.PSendSysMessage(KILL_MSG);
			}
			else
				kHandler.PSendSysMessage(ERR_TOO_MUCH_MONEY);
			if(victim->GetMoney() - FFA_LOST > 0)
			{
				victim->SetMoney(victim->GetMoney() - FFA_LOST);
				vHandler.PSendSysMessage(LOST_GOLD_MSG);
			}
		}
		else
		{
			if(killer->GetMoney() + NORMAL_REWARD < MAX_MONEY_AMOUNT)
			{
			killer->SetMoney(killer->GetMoney() + NORMAL_REWARD);
			kHandler.PSendSysMessage(KILL_MSG);
			}
			else
				kHandler.PSendSysMessage(ERR_TOO_MUCH_MONEY);
		}
	}
};

void AddSC_Gold_System()
{
	new Gold_System();
}
