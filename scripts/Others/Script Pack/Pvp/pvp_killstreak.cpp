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
 - Developer(s): AwkwardDev
 - Complete: 100%
 - ScriptName: 'system_player_streaking' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"
#include "Battleground.h"
#include "Group.h"
#include "Chat.h"

struct SystemInfo
{
    uint64 KillStreak;
    uint64 LastGUIDKill;
};

static std::map<uint64, SystemInfo> KillingStreak;

class kill_streak : public PlayerScript
{
    public:
        kill_streak() : PlayerScript("kill_streak") {}

        void OnPVPKill(Player *killer, Player *victim)
        {
	        Battleground* bg = killer->GetBattleground();
	        if (bg) // battleground restricted streaking
	        {
                int16 MONEY_AMOUNT = urand(100, 1000);

    	        uint64 kGUID;
    	        uint64 vGUID;
    	        kGUID = killer->GetGUID();
    	        vGUID = victim->GetGUID();

		        if (kGUID == vGUID)
    	                return;

    	        if (KillingStreak[kGUID].LastGUIDKill == vGUID)
    	            return;

                KillingStreak[kGUID].KillStreak++;
                KillingStreak[vGUID].KillStreak = 0;
                KillingStreak[kGUID].LastGUIDKill = vGUID;
                KillingStreak[vGUID].LastGUIDKill = 0;
                //killer->AddItem(29434, 1); // item sample
				if (Group* group = killer->GetGroup()) // grouping mechanism
				{
            	    for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
					{
            	        if (Player* groupMember = itr->getSource())
						{
           	                if (groupMember->IsAtGroupRewardDistance(victim))
							{
							    if (groupMember->isAlive())
							    {
            	                    if (groupMember != killer)
							        {
            	                        groupMember->ModifyMoney(+ MONEY_AMOUNT);
					                    groupMember->GetSession()->SendNotification("", victim->GetName());
								    }
								}
								else
								    groupMember->GetSession()->SendNotification("msg here", victim->GetName());
          	                }
						}
					}
				}

                switch (KillingStreak[kGUID].KillStreak) // kill streak ranks
                {
				    char msg[200];
	                case 1: // sample text msg self targetted
				        killer->ModifyMoney(+ MONEY_AMOUNT);
						ChatHandler(killer->GetSession()).PSendSysMessage("", victim->GetName());
                    break;
	            	case 5: // sample text msg world-wide spread
				        killer->ModifyMoney(+ MONEY_AMOUNT + 400);
        	            sprintf(msg, "", killer->GetName(), victim->GetName(), killer->GetName());
            	        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
                    break;
					default:
					KillingStreak[kGUID].KillStreak = 0;
					
                }

				switch (KillingStreak[vGUID].KillStreak) // kill streak ranks stealing mechanism
				{
					char msg[200];
					case 5: // steal 5 streaks of opponent's sixt 'active' streak
						sprintf(msg, "", killer->GetName(), victim->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
						KillingStreak[kGUID].KillStreak = 5;
						victim->ModifyMoney(-10000); 
						killer->ModifyMoney(+10000); // 1 gold
					break;
					default:
					KillingStreak[kGUID].KillStreak = 0;
				}
	        }
			else // world-wide kill system
			{
			    if (killer->GetGUID() == victim->GetGUID())
    	            return;

			    int16 MONEY_AMOUNT = urand(100, 1000);

			    if (victim->HasAura(15007))
				{
	 	            ChatHandler(killer->GetSession()).PSendSysMessage("", victim->GetName());
     	            ChatHandler(victim->GetSession()).PSendSysMessage("", killer->GetName());
				}
				else
				{ 
			        killer->ModifyMoney(+MONEY_AMOUNT);
					ChatHandler(killer->GetSession()).PSendSysMessage("", victim->GetName());
     	            victim->ModifyMoney(-MONEY_AMOUNT);
					ChatHandler(victim->GetSession()).PSendSysMessage("", killer->GetName());
				}
   	        }
		}
};

class death_streak : public PlayerScript
{
    public:
        death_streak() : PlayerScript("death_streak") {}


        void OnPVPKill(Player *killer, Player *victim)
        {
	        Battleground* bg = killer->GetBattleground();
	        if (bg)
	        {
                int16 MONEY_AMOUNT = urand(100, 1000);

    	        uint64 kGUID;
    	        uint64 vGUID;
    	        kGUID = killer->GetGUID();
    	        vGUID = victim->GetGUID();

		        if (kGUID == vGUID)
    	            return;

    	        if (KillingStreak[kGUID].LastGUIDKill == vGUID)
    	            return;

                KillingStreak[kGUID].KillStreak++;
                KillingStreak[vGUID].KillStreak = 0;
                KillingStreak[kGUID].LastGUIDKill = vGUID;
                KillingStreak[vGUID].LastGUIDKill = 0;

                switch (KillingStreak[kGUID].KillStreak)
                {
      		        char msg[200];
      		        case 1: // self targetted msg 
      	    			victim->ModifyMoney(- MONEY_AMOUNT);
	  	        	    ChatHandler(victim->GetSession()).PSendSysMessage("You have been awarded", killer->GetName());
	  	    		break;
	  				case 5: // world-wide targetted msg
	  				    victim->ModifyMoney(- MONEY_AMOUNT - 400);
   	  	    	        sprintf(msg, "", victim->GetName(), killer->GetName(), victim->GetName());
   	  	        	    sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
   	  	        	break;
					default:
					KillingStreak[vGUID].KillStreak = 0;
                }
	        }
		}
};

void AddSC_system_player_streak()
{
    new kill_streak;
	new death_streak;
}
