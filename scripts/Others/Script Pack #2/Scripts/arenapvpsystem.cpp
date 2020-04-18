#include "ScriptPCH.h"

class ArenaPVPSystem : public PlayerScript
{
    public:
        ArenaPVPSystem() : PlayerScript("ArenaPVPSystem") {}

    void OnPVPKill(Player* killer, Player* killed)
    {
	if (killer->GetMap()->IsBattleArena())
	{
		killer->GetSession()->SendNotification("You just killed %s and stole his soul!", killed->GetName());
		killer->AddItem(29437, 1);
	}
    }
};

void AddSC_ArenaPVPSystem()
{
    new ArenaPVPSystem;
}
