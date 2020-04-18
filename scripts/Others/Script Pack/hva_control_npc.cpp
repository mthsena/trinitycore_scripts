/*
--------------------------------------------------------------------
 _____________
|             |              
|___      ____|               
     |   |  |_|                
     |   |   _   _              
     |   |  | |_| |_  ___    ___   _   _   _  ___  _   _   _
     |   |  | |_   _|/ _ \  / _ \ | | | | | || _ || | | | | |
     |   |  | | | | | |_| || | | || | | | | ||| ||| | | | | |
     |   |  | | | | |  _  || | | || |_| |_| |||_||| |_| |_| |
     |___|  |_| |_| |_| |_||_| |_||_________||___||_________| 
--------------------------------------------------------------------
*/
#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellAuras.h"
#include "Player.h"

class hva_control_npc : public CreatureScript
{
public:
    hva_control_npc() : CreatureScript("hva_control_npc") { }

		struct hva_control_npcAI : public ScriptedAI
		{
			hva_control_npcAI(Creature *c) : ScriptedAI(c), summons(me){}
			
			void Reset()
			{				
		        me->SummonCreature(190604, -3361.511230f , -984.742981f, 122.664207f, 1.514387f, TEMPSUMMON_TIMED_DESPAWN,600000);        // Horde Boss
			    me->SummonCreature(190605, -3386.005371f ,-1445.014771f, 122.663940f, 5.489480f, TEMPSUMMON_TIMED_DESPAWN,600000);		  // Ally Boss	
			}
			void KilledUnit(Unit* pPlayer)
			{
		    }
			void EnterCombat(Unit * /*who*/)
            {
            }
			void JustDied(Unit* /*killer*/) 
			{
			        char msg[250];
		            snprintf(msg, 250, "|cffff0000[Event System]|r The Event|cffff0000 Horde vs Alliance|r has now Ended! ", NULL);  // The message
		            sWorld->SendGlobalText(msg, NULL);
					summons.DespawnAll();	
			}
            void JustSummoned(Creature* summoned)
            {
                summons.Summon(summoned);
			}
			
			private:
			    SummonList summons;
        };
		
		CreatureAI * GetAI(Creature * pCreature) const
		{
		    return new hva_control_npcAI(pCreature); 
		}
		
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->isInCombat())
        {
            pPlayer->GetSession()->SendNotification("You are in combat");
            return false;
        }
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Assist the Horde", GOSSIP_SENDER_MAIN, 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Assist the Alliance", GOSSIP_SENDER_MAIN, 2);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Event Boss", GOSSIP_SENDER_MAIN, 3);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn Buffs in the Middle", GOSSIP_SENDER_MAIN, 4);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn Explosive Mines in the Middle", GOSSIP_SENDER_MAIN, 5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Despawn All", GOSSIP_SENDER_MAIN, 6);
        pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
        return true;
    }
	
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
            case 1: // Save the Horde
               {
			       pCreature->CastSpell(pCreature,35517,false);
                   pPlayer->SummonCreature(190600,-3390.664551f ,-1055.223999f, 92.008125f, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190600,-3390.664551f ,-1055.223999f, 92.008125f, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190600,-3390.664551f ,-1055.223999f, 92.008125f, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190600,-3390.664551f ,-1055.223999f, 92.008125f, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190600,-3390.664551f ,-1055.223999f, 92.008125f, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
               }break;
            case 2: // Save the Alliance
              {
			       pCreature->CastSpell(pCreature,35517,false);
                   pPlayer->SummonCreature(190602,-3366.491699f ,-1402.599854f, 0, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190602,-3366.491699f ,-1402.599854f, 0, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190602,-3366.491699f ,-1402.599854f, 0, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190602,-3366.491699f ,-1402.599854f, 0, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
				   pPlayer->SummonCreature(190602,-3366.491699f ,-1402.599854f, 0, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
              }break;
            case 3: // Event Boss
               {
			       pCreature->CastSpell(pCreature,35517,false);
                   pPlayer->SummonCreature(11502,-3367.176514f ,-1218.507935f, 92.008499f, 0,TEMPSUMMON_TIMED_DESPAWN,20000);
               }break;
            case 4: // Spawn Buffs in the Middle
               {
			       pCreature->CastSpell(pCreature,35517,false);
                   pPlayer->SummonGameObject(184965, -3367.176514f ,-1218.507935f, 92.008499f, 0, 0, 0, 0, 0, 30000);
               }break;
            case 5: // Spawn Mines in the middle
               {
			       pCreature->CastSpell(pCreature,35517,false);
                   pPlayer->SummonGameObject(00000, -3367.176514f ,-1218.507935f, 0, 0, 0, 0, 0, 0, 30000);
				   pPlayer->SummonGameObject(00000, -3367.176514f ,-1218.507935f, 0, 0, 0, 0, 0, 0, 30000);
				   pPlayer->SummonGameObject(00000, -3367.176514f ,-1218.507935f, 0, 0, 0, 0, 0, 0, 30000);
				   pPlayer->SummonGameObject(00000, -3367.176514f ,-1218.507935f, 0, 0, 0, 0, 0, 0, 30000);
				   pPlayer->SummonGameObject(00000, -3367.176514f ,-1218.507935f, 0, 0, 0, 0, 0, 0, 30000);
               } break;
			case 6: // Despawn all
               {
               } break;
        }
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_hva_control_npc()
{
    new hva_control_npc();
}