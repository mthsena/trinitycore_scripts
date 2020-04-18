#include "ScriptPCH.h"

class OnPVPHeal : public PlayerScript
{
    public:
        OnPVPHeal() : PlayerScript("OnPVPHeal") {}

    void OnPVPHeal(Player* healer, Unit* healed, uint32 healAmount)
    {
	
    }
};

void AddSC_OnPVPHeal()
{
    new OnPVPHeal();
}