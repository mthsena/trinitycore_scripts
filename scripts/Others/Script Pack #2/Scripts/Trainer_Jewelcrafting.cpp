#include "ScriptPCH.h"

class Trainer_Jewelcrafting: public CreatureScript
{
public:
	Trainer_Jewelcrafting()
		: CreatureScript("Trainer_Jewelcrafting")
	{
	}

	struct Trainer_JewelcraftingAI : public ScriptedAI
	{
		Trainer_JewelcraftingAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_JewelcraftingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Jewelcrafting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51311) == true)
				{
		         pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dragon's Eye - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);	
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Jewelcrafting
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51311) == true)
				{
			    pCreature->MonsterWhisper("You already know Jewelcrafting!", pPlayer->GetGUID());
				}
			    if(pPlayer->HasSpell(51311) == false)
					{
				    if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
					if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(51311); // Grand Master Skill
				        pPlayer->learnSpellHighRank(56049); // Bold Dragon's Eye 
				        pPlayer->learnSpellHighRank(56052); // Delicate Dragon's Eye
				        pPlayer->learnSpellHighRank(56053); // Runed Dragon's Eye
				        pPlayer->learnSpellHighRank(56054); // Bright Dragon's Eye
				        pPlayer->learnSpellHighRank(56055); // Subtle Dragon's Eye
				        pPlayer->learnSpellHighRank(56056); // Flashing Dragon's Eye
				        pPlayer->learnSpellHighRank(56074); // Brilliant Dragon's Eye
				        pPlayer->learnSpellHighRank(56076); // Fractured Dragon's Eye
				        pPlayer->learnSpellHighRank(56077); // Lustrous Dragon's Eye
				        pPlayer->learnSpellHighRank(56079); // Mystic Dragon's Eye
				        pPlayer->learnSpellHighRank(56081); // Precise Dragon's Eye
				        pPlayer->learnSpellHighRank(56083); // Quick Dragon's Eye
				        pPlayer->learnSpellHighRank(56084); // Rigid Dragon's Eye
				        pPlayer->learnSpellHighRank(56085); // Smooth Dragon's Eye
				        pPlayer->learnSpellHighRank(56086); // Solid Dragon's Eye
				        pPlayer->learnSpellHighRank(56087); // Sparkling Dragon's Eye
				        pPlayer->learnSpellHighRank(56088); // Stormy Dragon's Eye
				        pPlayer->learnSpellHighRank(56089); // Thick Dragon's Eye
						pPlayer->MonsterWhisper("You have succesfully learned Jewelcrafting!", pPlayer->GetGUID());
						}
					if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(51311); // Grand Master Skill
				        pPlayer->learnSpellHighRank(56049); // Bold Dragon's Eye 
				        pPlayer->learnSpellHighRank(56052); // Delicate Dragon's Eye
				        pPlayer->learnSpellHighRank(56053); // Runed Dragon's Eye
				        pPlayer->learnSpellHighRank(56054); // Bright Dragon's Eye
				        pPlayer->learnSpellHighRank(56055); // Subtle Dragon's Eye
				        pPlayer->learnSpellHighRank(56056); // Flashing Dragon's Eye
				        pPlayer->learnSpellHighRank(56074); // Brilliant Dragon's Eye
				        pPlayer->learnSpellHighRank(56076); // Fractured Dragon's Eyepo
				        pPlayer->learnSpellHighRank(56077); // Lustrous Dragon's Eye
				        pPlayer->learnSpellHighRank(56079); // Mystic Dragon's Eye
				        pPlayer->learnSpellHighRank(56081); // Precise Dragon's Eye
				        pPlayer->learnSpellHighRank(56083); // Quick Dragon's Eye
				        pPlayer->learnSpellHighRank(56084); // Rigid Dragon's Eye
				        pPlayer->learnSpellHighRank(56085); // Smooth Dragon's Eye
				        pPlayer->learnSpellHighRank(56086); // Solid Dragon's Eye
				        pPlayer->learnSpellHighRank(56087); // Sparkling Dragon's Eye
				        pPlayer->learnSpellHighRank(56088); // Stormy Dragon's Eye
				        pPlayer->learnSpellHighRank(56089); // Thick Dragon's Eye
						pPlayer->MonsterWhisper("You have succesfully learned Jewelcrafting!", pPlayer->GetGUID());
						}		
				    }
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 2: // Dragon's Eye - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(42225, 3);
		}
        return true;
	}
};

void AddSC_Script_Jewelcrafting()
{
	new Trainer_Jewelcrafting();
}