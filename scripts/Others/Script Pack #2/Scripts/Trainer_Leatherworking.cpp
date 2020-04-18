#include "ScriptPCH.h"

class Trainer_Leatherworking : public CreatureScript
{
public:
	Trainer_Leatherworking()
		: CreatureScript("Trainer_Leatherworking")
	{
	}

	struct Trainer_LeatherworkingAI : public ScriptedAI
	{
		Trainer_LeatherworkingAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_LeatherworkingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Leatherworking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51302) == true)
						{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fur Lining - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Leatherworking
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51302) == true)
				{
			    pCreature->MonsterWhisper("You already know Leatherworking!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51302) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(51302); // Grand Master Skill
				        pPlayer->learnSpellHighRank(57683); // Fur Lining - Attack Power
				        pPlayer->learnSpellHighRank(57690); // Fur Lining - Stamina
				        pPlayer->learnSpellHighRank(57691); // Fur Lining - Spell Power
						pPlayer->MonsterWhisper("You have succesfully learned Leatherworking!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(51302); // Grand Master Skill
				        pPlayer->learnSpellHighRank(57683); // Fur Lining - Attack Power
				        pPlayer->learnSpellHighRank(57690); // Fur Lining - Stamina
				        pPlayer->learnSpellHighRank(57691); // Fur Lining - Spell Power
						pPlayer->MonsterWhisper("You have succesfully learned Leatherworking!", pPlayer->GetGUID());
						}		
				    }
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 2: // Fur Lining - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(44128, 1);
		}
        return true;
	}
};

void AddSC_Script_Leatherworking()
{
	new Trainer_Leatherworking();
}