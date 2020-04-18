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
#define FFA_ENTER_MSG "|cffff6060[Warzone]:|r This is a |cFFFF4500FFA zone|r, remember when you die you will |cFFFF4500lose 1 gold|r but you will gain |cFFFF45002 gold|r per kill!"
#define KILL_MSG "|cff00ff00|TInterface\\PvPRankBadges/PvPRank06:24|t|r Well done you have gained 1 gold for this |cFFFF4500Kill|r!"
#define KILL_FFA_MSG "|cffff6060[Warzone]:|r Well done you have gained 2 gold for this kill! |cFFFF4500Kill|r!"
#define LOST_GOLD_MSG "|cffff6060[Warzone]:|r I'm Sorry but you have |cFFFF4500lost|r 1 gold"
#define ERR_TOO_MUCH_MONEY "|cffff6060[PvP]: You exceeded the max amount of gold!|r"

enum Rewards
{
	NORMAL_REWARD = 10000,
	FFA_REWARD    = 20000,
	FFA_LOST      = 10000
};

class GoldOnKill : public PlayerScript
{
public:
	GoldOnKill() : PlayerScript("GoldOnKill") {}

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

		if(killer->GetGUID() == victim->GetGUID())
		{
			return;
		}
		else
		{
		if(killer->pvpInfo.inFFAPvPArea && victim->pvpInfo.inFFAPvPArea) //gets updated by UpdatePvPState
		{
			if(killer->GetMoney() + FFA_REWARD < MAX_MONEY_AMOUNT)
			{
			killer->SetMoney(killer->GetMoney() + FFA_REWARD);
			kHandler.PSendSysMessage(KILL_FFA_MSG);
			}
			else
				kHandler.PSendSysMessage(ERR_TOO_MUCH_MONEY);
			if(victim->GetMoney() - FFA_LOST > 0)
			{
				if(victim->GetMoney() != 0){
				victim->SetMoney(victim->GetMoney() - FFA_LOST);
				}
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
  }
};

void AddSC_GoldOnKill()
{
	new GoldOnKill();
}