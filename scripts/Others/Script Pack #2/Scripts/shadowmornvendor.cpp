#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

class shadowmorn_vendor : public CreatureScript
{
    public:
        shadowmorn_vendor() : CreatureScript("shadowmorn_vendor") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case 300356:
                if(pPlayer->GetArenaPersonalRating(1)>2500)
                    pPlayer->SEND_GOSSIP_MENU(pCreature->GetEntry(), pCreature->GetGUID());
                else 
                {
                    pCreature->MonsterWhisper("You need 2200 3x3 rating to have shadowmourne", pPlayer->GetGUID(), true); 
                    return true;
                }
                break;
                
            case 300357:
                if(pPlayer->GetArenaPersonalRating(1)>2000)
                    pPlayer->SEND_GOSSIP_MENU(pCreature->GetEntry(), pCreature->GetGUID());
                else 
                {
                    pCreature->MonsterWhisper("You need 2000 3x3 rating to have weapons", pPlayer->GetGUID(), true); 
                    return true;
                }
                 break;
            default: break;
        }
        return false;
    };
};

void AddSC_shadowmorn_vendor()
{
    new shadowmorn_vendor;
}