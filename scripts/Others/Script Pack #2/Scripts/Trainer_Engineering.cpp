#include "ScriptPCH.h"

class Trainer_Engineering : public CreatureScript
{
public:
	Trainer_Engineering()
		: CreatureScript("Trainer_Engineering")
	{
	}

	struct Trainer_EngineeringAI : public ScriptedAI
	{
		Trainer_EngineeringAI(Creature *c) : ScriptedAI(c)
		{
		}

		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
        {
            me->GetMotionMaster()->Clear();
            ScriptedAI::EnterEvadeMode();
        }

	};

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new Trainer_EngineeringAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Engineering", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51306) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mind Amplification Dish Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nitro Boosts Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hand-Mounted Pyro Rocket Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hyperspeed Accelerators Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reticulated Armor Webbing Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Flexweave Underlay Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Springy Arachnoweave Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Frag Belt", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
		        }
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (pPlayer->isInCombat())
		{
			pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Engineering
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51306) == true)
				{
			    pCreature->MonsterWhisper("You already know Engineering!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51306) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(51306); // Grand Master Skill
				        pPlayer->learnSpellHighRank(54998); // Hand-Mounted Pyro Rocket
				        pPlayer->learnSpellHighRank(54999); // Hyperspeed Accelerators
				        pPlayer->learnSpellHighRank(55016); // Nitro Boosts
				        pPlayer->learnSpellHighRank(67839); // Mind Amplification Dish  
				        pPlayer->learnSpellHighRank(63765); // Springy Arachnoweave
				        pPlayer->learnSpellHighRank(55002); // Flexweave Underlay 
			    	    pPlayer->learnSpellHighRank(63770); // Reticulated Armor Webbing
			    	    pPlayer->learnSpellHighRank(54793); // Frag Belt
						pPlayer->MonsterWhisper("You have succesfully learned Engineering!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(51306); // Grand Master Skill
				        pPlayer->learnSpellHighRank(54998); // Hand-Mounted Pyro Rocket
				        pPlayer->learnSpellHighRank(54999); // Hyperspeed Accelerators
				        pPlayer->learnSpellHighRank(55016); // Nitro Boosts
				        pPlayer->learnSpellHighRank(67839); // Mind Amplification Dish  
				        pPlayer->learnSpellHighRank(63765); // Springy Arachnoweave
				        pPlayer->learnSpellHighRank(55002); // Flexweave Underlay 
			    	    pPlayer->learnSpellHighRank(63770); // Reticulated Armor Webbing
			    	    pPlayer->learnSpellHighRank(54793); // Frag Belt
						pPlayer->MonsterWhisper("You have succesfully learned Engineering!", pPlayer->GetGUID());
						}		
				    }
					break;
			
			case GOSSIP_ACTION_INFO_DEF + 2: // Mind Amplification Dish Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 8);
				pPlayer->AddItem(39683, 1);
				break;
			
			case GOSSIP_ACTION_INFO_DEF + 3: // Nitro Boosts Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(39690, 6);
				pPlayer->AddItem(39681, 6);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 4: // Hand-Mounted Pyro Rocket Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 6);
				pPlayer->AddItem(37702, 4);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 5: // Hyperspeed Accelerators Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 6);
				pPlayer->AddItem(37700, 4);
				break;				
				
			case GOSSIP_ACTION_INFO_DEF + 6: // Reticulated Armor Webbing Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 4);
				pPlayer->AddItem(35624, 2);
				break;				
				
			case GOSSIP_ACTION_INFO_DEF + 7: // Flexweave Underlay Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(33470, 12);
				pPlayer->AddItem(39682, 1);
				break;				
				
			case GOSSIP_ACTION_INFO_DEF + 8: // Springy Arachnoweave Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(33470, 12);
				pPlayer->AddItem(39682, 1);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 9: // Frag Belt
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36916, 8);
				pPlayer->AddItem(39690, 8);
		}
        return true;
	}
};

void AddSC_Script_Engineering()
{
	new Trainer_Engineering();
}