//Created by: Squeezee
// Estrania.com - World of Warcraft First Private Server

#include "ScriptPCH.h"

///////////////////////////////////////////////////////////////////////
///////////////////////      CONFIG      /////////////////////////////
/////////////////////////////////////////////////////////////////////

float Version = 2.50f; //Don't touch this.
bool PvPSystemEnabled = true; //Set to false if you want to disable the PvP System
bool OnlyInBattlegrounds = false; //Set to true if you want to enable this only in battlegrounds.
bool LooseTokenOnPvPDeath = true; //Set to true if you want the victim to loose tokens when the victim dies.
int32 AmountOfItemsYouWantTheVictimToLoose = 1; //Amount of items you want the victim to loose when victim dies.
bool AddTokenOnPvPKill = false; //Set to false if you don't want the killer to be rewarded.
int32 ItemReward = 40752; //The ItemID of the reward.
int32 AmountOfRewardsOnKillStreak[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 }; //With how many items you want to reward the killer when he slays the victim.
int32 HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim = 15; //Name speaks for It self.
const int32 KillerStreak15 = 15; 
const int32 KillerStreak20 = 20; 
const int32 KillerStreak30 = 30; 
const int32 KillerStreak40 = 35; 
const int32 KillerStreak50 = 40;
const int32 KillerStreak60 = 45;
const int32 KillerStreak70 = 50;
const int32 KillerStreak80 = 55;
const int32 KillerStreak90 = 60;
const int32 KillerStreak100 = 65;
const int32 KillerStreak110 = 70;
const int32 KillerStreak120 = 75;
const int32 KillerStreak130 = 80;
const int32 KillerStreak140 = 85; 
int32 KillStreaks[14] = { KillerStreak15, KillerStreak20, KillerStreak30, KillerStreak40, KillerStreak50, KillerStreak60, KillerStreak70, KillerStreak80, KillerStreak90, KillerStreak100, KillerStreak110, KillerStreak120 ,KillerStreak130, KillerStreak140  };
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

class System_OnPVPKill : public PlayerScript
{
        public:
                System_OnPVPKill() : PlayerScript("System_OnPVPKill") {}

        
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
        if(!pKiller->GetMap()->IsBattleground())
           return;
      }

        KillingStreak[kGUID].KillStreak++;
        KillingStreak[vGUID].KillStreak = 0;
        KillingStreak[kGUID].LastGUIDKill = vGUID;
        KillingStreak[vGUID].LastGUIDKill = 0;
      if(AddTokenOnPvPKill == true)
          pKiller->AddItem(ItemReward, 1);
      if(LooseTokenOnPvPDeath == true)
        pVictim->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
                
        switch(KillingStreak[kGUID].KillStreak)
        {
	        
	        
	        
        case KillerStreak15:
        sprintf(msg, "[Raven PvP System]: -RANK-(1) - Beware of %s the Criminal who destroyed %s and is warming up with a 15 person killing spree. Rising to the top!", pKiller->GetName(), pVictim->GetName(), KillStreaks[1]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,11010,true);
        break;

        case KillerStreak20:
        sprintf(msg, "[Raven PvP System]: -RANK-(2) - Avoid %s the Insane who dismembered %s and is on fire with a 20 person killing spree. Inspired by death..", pKiller->GetName(), pVictim->GetName(), KillStreaks[2]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,70571,true);
        break;

        case KillerStreak30:
        sprintf(msg, "[Raven PvP System]: -RANK-(3) - Watch out! %s the Maniac has slain %s and is on a crazed 30 person killing spree. Full of comtempt!", pKiller->GetName(), pVictim->GetName(), KillStreaks[3]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,69861,true);
        break;
        
        case KillerStreak40:
        sprintf(msg, "[Raven PvP System]: -RANK-(4) - Caution! %s the Serial Killer has massacred %s and is on a 35 person killing spree. Focused on the path.", pKiller->GetName(), pVictim->GetName(), KillStreaks[4]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,47335,true);
        break;

        case KillerStreak50:
        sprintf(msg, "[Raven PvP System]: -RANK-(5) - Fate steps aside as %s the Unmerciful has relinquished %s to the heavens and is on a 40 person killing spree. Demonic intentions", pKiller->GetName(), pVictim->GetName(), KillStreaks[5]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,60342,true);
        break;
        
        case KillerStreak60:
        sprintf(msg, "[Raven PvP System]: -RANK-(6) - Attention! %s the Ender has absolved %s and is on a 45 person killing spree. Halfway to the highest of Ken", pKiller->GetName(), pVictim->GetName(), KillStreaks[6]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,62398,true);
        break;
        
        case KillerStreak70:
        sprintf(msg, "[Raven PvP System]: -RANK-(7) - Be wary! %s the Gravedigger has buried %s and is raging with a 50 person killing spree. Working the late night shift!", pKiller->GetName(), pVictim->GetName(), KillStreaks[7]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,51929,true);
        break;

        case KillerStreak80:
        sprintf(msg, "[Raven PvP System]: -RANK-(8) - Like clockwork, %s the Mastermind has tactfully removed %s from battle and is on fire with a 55 person killing spree. Motivated by the one.", pKiller->GetName(), pVictim->GetName(), KillStreaks[8]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,63660,true);
        break;

        case KillerStreak90:
        sprintf(msg, "[Raven PvP System]: -RANK-(9) - Concealed in the Shadows, %s the Assassinhas slain %s and is on a 60 person killing spree. Seeking revenge for the past.", pKiller->GetName(), pVictim->GetName(), KillStreaks[9]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,43776,true);
        break;

        case KillerStreak100:
        sprintf(msg, "[Raven PvP System]: -RANK-(10) - Tossing the carcass aside, %s the Bloodletter has devoured %s and is on a 65 person killing spree. Hell walks among the living.", pKiller->GetName(), pVictim->GetName(), KillStreaks[10]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,41969,true);
        break;

        case KillerStreak110:
        sprintf(msg, "[Raven PvP System]: -RANK-(11) - Cower before %s the Unstoppable who has slain %s and is on a rampaging 70 person killing spree. Second in command to only one!", pKiller->GetName(), pVictim->GetName(), KillStreaks[11]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,19883,true); 
        break;
        
        case KillerStreak120:
        sprintf(msg, "[Raven PvP System]: -RANK-(12) - Fear %s the Conqueror; who has annihilated yet another victim, %s, and is on a 75 person killing spree. UnMatched by all, can no one stop them?", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,72726,true);
        break;
        
        case KillerStreak130:
        sprintf(msg, "[Raven PvP System]: -RANK-(13) - Fear %s the Conqueror; who has annihilated yet another victim, %s, and is on a 80 person killing spree. UnMatched by all, can no one stop them?", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,11009,true);
        break;
        
        case KillerStreak140:
        sprintf(msg, "[Raven PvP System]: -RANK-(14) - Fear %s the Conqueror; who has annihilated yet another victim, %s, and is on a 85 person killing spree. UnMatched by all, can no one stop them?", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[2]);
        pKiller->CastSpell(pKiller,42828,true);
        break;
        
        

                                               
                                                        
                                                       }
    											} 

                
        }
};

void AddSC_System_OnPVPKill()
{
    new System_OnPVPKill();
}