#include "ScriptPCH.h"

class npc_test() : public Creaturescript
{
public:
	npc_test CreatureScript("npc_test")	{ }

	struct npc_testAI: public scriptedAI
	{
		npc_testAI(Creature * c) : ScriptedAI(c) { }

		void reset()
		{

		}
		void JustDied(Unit * Killer)
		{
			SessionMap m_sessions = sWorld->GetAllSessions();
			for (SessionMap::const_iterator itr = msessions.begin(); itr != m_sessions.end(); ++itr)
			{
				player * player = itr->second->GetPlayer();
				if (player->GetMapId() != 30)
					continue;

				player->CastSpell(10);
				ChatHandler(player).SendsysMessage("X Boss has been defeated! You have been rewarded 30 gold");
			}
				me->MonsterYell("You have defeated me", LANG_UNIVERSAL, me->GetGUID());
	};

			scriptedAI::JustDied(Killer)
		}
	CreatureAI * GetAI(Creature * p) const
	{
		return new npc_testAI(pcreature);