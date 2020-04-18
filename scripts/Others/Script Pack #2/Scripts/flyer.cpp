#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

class flyer : public CreatureScript
{
    public:
        flyer() : CreatureScript("flyer") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->CastSpell(pPlayer, 31719, true);
        return true;
    };
};

void AddSC_flyer()
{
    new flyer;
}