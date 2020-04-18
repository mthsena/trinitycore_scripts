#include "ScriptPCH.h"
#include "Player.h"

class Announce_OnPVPKill : public PlayerScript
{
    public:
        Announce_OnPVPKill() : PlayerScript("Announce_OnPVPKill") {}

    void OnPVPKill(Player* killer, Player* killed)
    {
	if(killer->GetGUID() == killed->GetGUID())
	   return;

	if(killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress())
	   return;

		if (killer->isPVPArea(killer->GetAreaId()))
		{
			if (killed->getLevel() < 255 || killed->HasAura(27827, true) || killed->HasAura(2479)) 
			{
			killer->GetSession()->SendNotification("You can't steal a soul from %s!", killed->GetName());
			return;
			} else {
			killer->GetSession()->SendNotification("You just killed %s and stole his soul!", killed->GetName());
			killer->AddItem(29438, 1);
			}
		}
	       else if(killer->GetMap()->IsBattleArena())
	       {
		       killer->GetSession()->SendNotification("You just killed %s and stole his soul!", killed->GetName());
		       killer->AddItem(29437, 2);
	       }
    }
};

void AddSC_Announce_OnPVPKill()
{
    new Announce_OnPVPKill();
}