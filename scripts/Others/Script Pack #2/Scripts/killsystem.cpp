#include "ScriptPCH.h"
#include <cstring>

///////////////////////      CONFIG      /////////////////////////////
/////////////////////////////////////////////////////////////////////

float Version = 2.50f; //Don't touch this.
bool PvPSystemEnabled = true; //Set to false if you want to disable the PvP System
bool OnlyInBattlegrounds = true; //Set to true if you want to enable this only in battlegrounds.
bool LooseTokenOnPvPDeath = true; //Set to true if you want the victim to loose tokens when the victim dies.
int32 AmountOfItemsYouWantTheVictimToLoose = 1; //Amount of items you want the victim to loose when victim dies.
bool AddTokenOnPvPKill = true; //Set to false if you don't want the killer to be rewarded.
int32 ItemReward = 23247; //The ItemID of the reward.
int32 AmountOfRewardsOnKillStreak[5] = { 5, 10, 15, 20, 25 }; //With how many items you want to reward the killer when he slays the victim.
int32 HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim = 2; //Name speaks for It self.
const int32 KillerStreak1 = 05; 
const int32 KillerStreak2 = 10; 
const int32 KillerStreak3 = 15; 
const int32 KillerStreak4 = 20; 
const int32 KillerStreak5 = 30; 
int32 KillStreaks[5] = { KillerStreak1, KillerStreak2, KillerStreak3, KillerStreak4, KillerStreak5 };
///////////////////////////////////////////////////////////////////
///////////////////////      END      ////////////////////////////
/////////////////////////////////////////////////////////////////

struct SystemInfo
{
    uint32 KillStreak;
    uint32 LastGUIDKill;
    uint8 KillCount;
};

static std::map<uint32, SystemInfo> KillingStreak;

class System_OnPvPKill : public PlayerScript
{
    public:
        System_OnPvPKill() : PlayerScript("System_OnPvPKill") {}

        
void OnPVPKill(Player *pKiller, Player *pVictim)
{
    if(PvPSystemEnabled == false)
    {
             return;
    }
    else if(PvPSystemEnabled == true)
    {
        uint32 kGUID; 
        uint32 vGUID;
        char msg[500];
        kGUID = pKiller->GetGUID();
        vGUID = pVictim->GetGUID();                 
        if(kGUID == vGUID)
        {
          return;
        }
                
      if(KillingStreak[kGUID].LastGUIDKill == vGUID)
        {
        KillingStreak[kGUID].KillCount++;
        KillingStreak[vGUID].KillCount = 1;
          pKiller->AddItem(ItemReward, 1);
        if(LooseTokenOnPvPDeath == true)
          pVictim->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
	   ChatHandler(pVictim->GetSession()).PSendSysMessage("You died, because of that you have lost an Event Token!");
	}
      if(KillingStreak[kGUID].LastGUIDKill != vGUID)
      {
        KillingStreak[kGUID].KillCount = 1;
        KillingStreak[vGUID].KillCount = 1;
      }

      if(KillingStreak[kGUID].KillCount == HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim)
      {
        return;
      }

      if(OnlyInBattlegrounds == true)
      {
        if(!pKiller->GetMap()->IsBattleground() || pKiller->GetMapId() == 30)
           return;
      }

        KillingStreak[kGUID].KillStreak++;
        KillingStreak[vGUID].KillStreak = 0;
        KillingStreak[kGUID].LastGUIDKill = vGUID;
        KillingStreak[vGUID].LastGUIDKill = 0;
      if(AddTokenOnPvPKill == true)
          pKiller->AddItem(29435, 1);
	   ChatHandler(pKiller->GetSession()).PSendSysMessage("You killed a player therefor you have been rewarded with his soul!");
      if(LooseTokenOnPvPDeath == true)
          pVictim->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
                
        switch(KillingStreak[kGUID].KillStreak)
        {
        case KillerStreak1:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF00005|cffFFFF05 kill streak. ", pKiller->GetName(), pVictim->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_SYSTEM, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
	 pKiller->ModifyHonorPoints(250);
	 pKiller->CastSpell(pKiller, 24378, true);
        break;

        case KillerStreak2:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF000010|cffFFFF05 kill streak. ", pKiller->GetName(), pVictim->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_SYSTEM, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[2]);
	 pKiller->ModifyHonorPoints(250);
	 pKiller->CastSpell(pKiller, 24378, true);
        break;

        case KillerStreak3:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF000015|cffFFFF05 kill streak. ", pKiller->GetName(), pVictim->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_SYSTEM, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[3]);
	 pKiller->ModifyHonorPoints(250);
	 pKiller->CastSpell(pKiller, 24378, true);
        break;

        case KillerStreak4:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF000020|cffFFFF05 kill streak. ", pKiller->GetName(), pVictim->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_SYSTEM, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[4]);
	 pKiller->ModifyHonorPoints(250);
	 pKiller->CastSpell(pKiller, 24378, true);
        break;

        case KillerStreak5:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF000030|cffFFFF05 kill streak. ", pKiller->GetName(), pVictim->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_SYSTEM, msg);
        pKiller->AddItem(23247, 25);
        KillingStreak[kGUID].KillStreak = 0;
	 pKiller->ModifyHonorPoints(250);
	 pKiller->CastSpell(pKiller, 24378, true);
        break;
     }
    }
}
};

void AddSC_System()
{
    new System_OnPvPKill;
}
