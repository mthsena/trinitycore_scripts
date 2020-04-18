#include "ScriptPCH.h"

class Trainer_Inscription : public CreatureScript
{
public:
	Trainer_Inscription()
		: CreatureScript("Trainer_Inscription")
	{
	}

	struct Trainer_InscriptionAI : public ScriptedAI
	{
		Trainer_InscriptionAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_InscriptionAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Inscription", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(45363) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Master's Inscription - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Inscription
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(45363) == true)
				{
			    pCreature->MonsterWhisper("You already know Inscription!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(45363) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(45363); // Grand Master Skill
				        pPlayer->learnSpellHighRank(61117); // Inscription of the Axe
				        pPlayer->learnSpellHighRank(61118); // Inscription of the Crag
				        pPlayer->learnSpellHighRank(61119); // Inscription of the Pinnacle
				        pPlayer->learnSpellHighRank(61120); // Inscription of the Storm
						pPlayer->MonsterWhisper("You have succesfully learned Inscription!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(45363); // Grand Master Skill
				        pPlayer->learnSpellHighRank(61117); // Inscription of the Axe
				        pPlayer->learnSpellHighRank(61118); // Inscription of the Crag
				        pPlayer->learnSpellHighRank(61119); // Inscription of the Pinnacle
				        pPlayer->learnSpellHighRank(61120); // Inscription of the Storm
						pPlayer->MonsterWhisper("You have succesfully learned Inscription!", pPlayer->GetGUID());
						}	
				    }
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 2: // Master's Inscription - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(43127, 1);
		}
        return true;
	}
};

void AddSC_Script_Inscription()
{
	new Trainer_Inscription();
}