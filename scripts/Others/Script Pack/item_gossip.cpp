#include "ScriptPCH.h"

class ItemUse_item_custom : public ItemScript
{
	public:
		ItemUse_item_custom() : ItemScript("Gossip") {}

		bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
		{
			player->SummonCreature(245,player->GetPositionX()+4 ,player->GetPositionY(), player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
			return true;
		}
};

void AddSC_ItemUse_item_custom()
{
    new ItemUse_item_custom();
}