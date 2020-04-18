#include "ScriptPCH.h"
#include "ScriptedGossip.h"

class npc_trainerspawn : public CreatureScript
{
public:
	npc_trainerspawn() : CreatureScript("npc_trainerspawn") { }

	bool OnGossipHello(Player *player, Creature *_Creature)
	{
		player->PlayerTalkClass->ClearMenus();

		if (player->isInCombat())
		{
			player->PlayerTalkClass->SendCloseGossip();
			_Creature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
			return true;
		}
		if (player->GetMap()->IsBattlegroundOrArena())
		{
			player->PlayerTalkClass->SendCloseGossip();
			_Creature->MonsterSay("You can't summon trainers while in battleground or Arena!", LANG_UNIVERSAL, NULL);
			return true;
		}

		_Creature->MonsterWhisper("Welcome dear player, please choose the trainer desired for your class.", player->GetGUID());

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn your Class Trainer." 	 , GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Spawn Max Payne." 	 	 	 , GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Maybe later."               	 , GOSSIP_SENDER_MAIN, 2);
		player->PlayerTalkClass->SendGossipMenu(85004, _Creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *_Creature, uint32 sender, uint32 action)
	{

		switch(action)
		{
		case 1:
			switch(player->getClass())
			{
			case CLASS_DEATH_KNIGHT:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(28474,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_DRUID:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(12042,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_HUNTER:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(3406,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_MAGE:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(5882,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_PALADIN:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(20406,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_PRIEST:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(6018,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_ROGUE:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(3327,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_SHAMAN:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(3344,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_WARLOCK:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(3325,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			case CLASS_WARRIOR:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(4593,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("You got your trainer, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;

			default: break;
			}
			break;
		case 7:
				player->PlayerTalkClass->SendCloseGossip();
				player->SummonCreature(77777,player->GetPositionX() ,player->GetPositionY()+1, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,45000);
				_Creature->MonsterWhisper("Max Payne is here, i must say farewell..", player->GetGUID());
				_Creature->DisappearAndDie();
				break;
		case 2:
			_Creature->MonsterWhisper("Please come again.", player->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			_Creature->DisappearAndDie();
			break;

		}

		return true;
	}

};

void AddSC_npc_trainerspawn()
{
	new npc_trainerspawn();
}
