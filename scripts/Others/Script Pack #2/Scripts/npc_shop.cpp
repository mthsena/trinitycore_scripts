#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

class npc_shop : public CreatureScript
{
    public:
       npc_shop() : CreatureScript("npc_shop") {}

    // ^_^!
};

void AddSC_npc_shop()
{
    new npc_shop();
}
