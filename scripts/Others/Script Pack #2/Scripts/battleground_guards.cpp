#include "ScriptPCH.h"
#include <cstring>

///////////////////////      CONFIG      /////////////////////////////
/////////////////////////////////////////////////////////////////////

//float Version = 2.50f; //Don't touch this.
bool AVPvPSystemEnabled = true; //Set to false if you want to disable the PvP System
bool AVOnlyInBattlegrounds = true; //Set to true if you want to enable this only in battlegrounds.
bool AVLooseTokenOnPvPDeath = true; //Set to true if you want the victim to loose tokens when the victim dies.
int32 AVAVAmountOfItemsYouWantTheVictimToLoose = 1; //Amount of items you want the victim to loose when victim dies.
bool AVAddTokenOnPvPKill = true; //Set to false if you don't want the killer to be rewarded.
int32 AVItemReward = 23247; //The ItemID of the reward.
int32 AVAmountOfRewardsOnKillStreak[5] = { 5, 10, 15, 20, 25 }; //With how many items you want to reward the killer when he slays the victim.
int32 AVHowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim = 2; //Name speaks for It self.
const int32 KillerStreak1 = 05; 
const int32 KillerStreak2 = 10; 
const int32 KillerStreak3 = 15; 
const int32 KillerStreak4 = 20; 
const int32 KillerStreak5 = 30; 
int32 AVKillStreaks[5] = { KillerStreak1, KillerStreak2, KillerStreak3, KillerStreak4, KillerStreak5 };
///////////////////////////////////////////////////////////////////
///////////////////////      END      ////////////////////////////
/////////////////////////////////////////////////////////////////

struct SystemInfo
{
    uint32 AVKillStreak;
    uint32 AVLastGUIDKill;
    uint8 KillCount;
};

static std::map<uint32, SystemInfo> KillingStreak;

class System_AVOnPvPKill : public PlayerScript
{
    public:
        System_AVOnPvPKill() : PlayerScript("System_AVOnPvPKill") {}

        
void OnCreatureKill(Player* killer, Creature* killed)
{
    if(AVPvPSystemEnabled == false || killer->GetMapId() != 30)
    {
             return;
    }
    else if(AVPvPSystemEnabled == true && killer->GetMapId() == 30)
    {
        uint32 kGUID; 
        uint32 vGUID;
        char msg[500];
        kGUID = killer->GetGUID();
        vGUID = killed->GetGUID();                 
        if(kGUID == vGUID)
        {
          return;
        }
                
      if(KillingStreak[kGUID].AVLastGUIDKill == vGUID)
        {
        KillingStreak[kGUID].KillCount++;
        KillingStreak[vGUID].KillCount = 1;
          killer->AddItem(AVItemReward, 1);
	}
      if(KillingStreak[kGUID].AVLastGUIDKill != vGUID)
      {
        KillingStreak[kGUID].KillCount = 1;
        KillingStreak[vGUID].KillCount = 1;
      }

      if(KillingStreak[kGUID].KillCount == AVHowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim)
      {
        return;
      }

        KillingStreak[kGUID].AVKillStreak++;
        KillingStreak[vGUID].AVKillStreak = 0;
        KillingStreak[kGUID].AVLastGUIDKill = vGUID;
        KillingStreak[vGUID].AVLastGUIDKill = 0;
      if(AVAddTokenOnPvPKill == true)
          killer->AddItem(28558, 1);
	   ChatHandler(killer->GetSession()).PSendSysMessage("You destroyed a victim, you have been awarded with a token!");
                
        switch(KillingStreak[kGUID].AVKillStreak)
        {
        case KillerStreak1:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 is on a |cffFF00005|cffFFFF05 kill streak. ", killer->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_AVSYSTEM, msg);
        killer->AddItem(AVItemReward, AVAmountOfRewardsOnKillStreak[1]);
	 killer->ModifyHonorPoints(150);
        break;

        case KillerStreak2:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 is on a |cffFF000010|cffFFFF05 kill streak. ", killer->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_AVSYSTEM, msg);
        killer->AddItem(AVItemReward, AVAmountOfRewardsOnKillStreak[2]);
	 killer->ModifyHonorPoints(150);
        break;

        case KillerStreak3:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 is on a |cffFF000015|cffFFFF05 kill streak. ", killer->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_AVSYSTEM, msg);
        killer->AddItem(AVItemReward, AVAmountOfRewardsOnKillStreak[3]);
	 killer->ModifyHonorPoints(150);
        break;

        case KillerStreak4:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 is on a |cffFF000020|cffFFFF05 kill streak. ", killer->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_AVSYSTEM, msg);
        killer->AddItem(AVItemReward, AVAmountOfRewardsOnKillStreak[4]);
	 killer->ModifyHonorPoints(150);
        break;

        case KillerStreak5:
        sprintf(msg, "|cffFF0000%s|cffFFFF05 is on a |cffFF000030|cffFFFF05 kill streak. ", killer->GetName());
        sWorld->SendWorldText(LANG_PVPKILL_AVSYSTEM, msg);
        killer->AddItem(AVItemReward, AVAmountOfRewardsOnKillStreak[5]);
        KillingStreak[kGUID].AVKillStreak = 0;
	 killer->ModifyHonorPoints(150);
        break;
     }
    }
}
};

void AddSC_System_AVOnPvPKill()
{
    new System_AVOnPvPKill;
}
