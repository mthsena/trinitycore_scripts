#include "ScriptPCH.h"

class OnEnterMap: public PlayerScript
{
    public:
        OnEnterMap() : PlayerScript("OnEnterMap") {}

    void OnPlayerEnterMap(Map* map, Player* player)
    {
    	if (player->GetMapId() == 532 && (player->GetCommandStatus(CHEAT_COOLDOWN) || player->GetCommandStatus(CHEAT_CASTTIME)))
    	{
		player->m_CheatCastTime = false;
		player->m_CheatCooldown = false;
    	}
    }
};

void AddSC_OnEnterMap()
{
    new OnEnterMap();
}