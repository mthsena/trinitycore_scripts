/* Custom Script for Strand of the Ancients */

#include "ScriptPCH.h"
#include "Zones/BattlegroundSA.h"

class npc_demolisher_salesman : public CreatureScript
{
    public:
        npc_demolisher_salesman() : CreatureScript("npc_demolisher_salesman") { }
        
    struct npc_demolisher_salesmanAI : public ScriptedAI
    {
        npc_demolisher_salesmanAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            me->SetReactState(REACT_PASSIVE);
            Reset();
        }
        uint32 DemolisherCount;
        uint32 ZaryadCount;
        
        void Reset()
        {
            DemolisherCount = 0;
            ZaryadCount = 0;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_demolisher_salesmanAI (pCreature);
    }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
        if(CAST_AI(npc_demolisher_salesmanAI, pCreature->AI())->DemolisherCount<3)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Построить танк.", GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF);
        if(CAST_AI(npc_demolisher_salesmanAI, pCreature->AI())->ZaryadCount<5)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Построить гранату.", GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF+1);
        else
            pCreature->MonsterSay("Я не могу строить больше!", LANG_UNIVERSAL, NULL); 
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->CLOSE_GOSSIP_MENU();
        switch(action)
        {
            case 0:
            // removing the flag non_attackable after summon Battleground demolisher
                if(creature->GetPositionY()<0)
                {
                    TempSummon* tank_a = creature->SummonCreature(28781, 1371.18f, -317.45f, 34.98f, 1.78f);
                    tank_a->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                    tank_a->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
                else
                {
                    TempSummon* tank_b = creature->SummonCreature(28781, 1353.18f, 223.71f, 35.26f, 4.34f);
                    tank_b->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
                    tank_b->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
                CAST_AI(npc_demolisher_salesmanAI, creature->AI())->DemolisherCount++;
                break;
            case 1:
                creature->SummonGameObject(190753, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, 0, 0, 0, 0, 10*MINUTE*IN_MILLISECONDS);
                CAST_AI(npc_demolisher_salesmanAI, creature->AI())->ZaryadCount++;
                break;
        }
        return true;
    }
    
    bool GossipSelect_npc_demolisher_salesman(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

/*######
## go_wintergrasp_def_portal
######*/

static float SpawnLocation[5][3]=
{
    {1468.380005f, -225.798996f, 30.896200f}, //blue
    {1394.270020f, 72.551399f, 31.054300f},//green
    {1065.260010f, -89.79501f, 81.073402f},//yellow
    {1216.069946f, 47.904301f, 54.278198f}, //purple
    {1255.569946f, -233.548996f, 56.43699f},//red
};

static float TeleLocation[5][3]=
{
    {1451.72f, -224.863f, 41.9564f},
    {1401.6f, 88.6693f, 41.1833f},
    {1062.83f, -87.1955f, 93.8061f},
    {1210.68f, 60.3558f, 64.7388f},
    {1245.03f, -226.439f, 66.7201f},
};

class SA_defender_portal : public GameObjectScript
{
    public:
        SA_defender_portal() : GameObjectScript("SA_defender_portal") { }
        
    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetMapId() == 607 && !player->HasAura(54643))
        {
            if (Battleground *bg = player->GetBattleground())
            {
                for (uint32 i=0; i<5; ++i)
                {
                    if ((go->GetPositionX() == SpawnLocation[i][0]) && 
                        (go->GetPositionY() == SpawnLocation[i][1]) &&
                        (go->GetPositionZ() == SpawnLocation[i][2]))
                        {
                            player->TeleportTo(bg->GetMapId(),TeleLocation[i][0],TeleLocation[i][1],TeleLocation[i][2],0);
                            player->CastSpell(player,54643,true);
                            return true;
                        }
                } 
            }
        }
        return false;
    }
};

void AddSC_strand_of_the_ancients()
{
    new SA_defender_portal();
    new npc_demolisher_salesman();
}
