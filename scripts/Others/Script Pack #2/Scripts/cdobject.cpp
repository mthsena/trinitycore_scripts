#include "ScriptPCH.h"

/*
INSERT INTO gameobject_template VALUES
(42001, 3, 2616, 'Cooldown Reset', '', '', '', 0, 0, 0.2, 0, 0, 0, 0, 0, 0, 0, -1, 600, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_cooldown_reset', 12340);
*/
class go_cooldown_reset : public GameObjectScript
{
    public:
        go_cooldown_reset() : GameObjectScript("go_cooldown_reset") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (player->IsInCombat())
                ChatHandler(player).PSendSysMessage("You are in combat.");
            else
            {
                player->RemoveArenaSpellCooldowns();
                go->SetLootState(GO_JUST_DEACTIVATED);
                return true;
            }
            return false;
        }
};

void AddSC_coolown_object()
{
    new go_cooldown_reset();
}
