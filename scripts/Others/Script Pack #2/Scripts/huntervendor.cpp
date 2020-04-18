#include "ScriptPCH.h"

class npc_huntervendor : public CreatureScript
{
public:
    npc_huntervendor() : CreatureScript("npc_huntervendor") { }

    bool OnGossipHello(Player *pPlayer, Creature *pCreature)
    {
        if(pPlayer->getClass() == CLASS_HUNTER)
	 {
            pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
	 } else {
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pCreature->MonsterWhisper("Your not a HUNTER, i cant sell to you $N!", pPlayer->GetGUID());
	 }

        return true;
    }

    bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        if(!pPlayer->getAttackers().empty())
        {
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pCreature->MonsterWhisper("I will not sell items to you $N when your in a fight!",pPlayer->GetGUID());
        }
        return true;
    }
};

void AddSC_npc_huntervendor()
{
    new npc_huntervendor();
}