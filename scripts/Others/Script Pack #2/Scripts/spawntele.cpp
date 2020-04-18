#include "ScriptPCH.h"
#include "Chat.h"

class item_spawn_teleporter : public ItemScript
{
public:
	item_spawn_teleporter() : ItemScript("item_spawn_teleporter") { }

	bool OnUse(Player* player, Item* item)
	{
  		player->SummonCreature(481851,player->GetPositionX() ,player->GetPositionY()+10, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,30000);
		ChatHandler(player->GetSession()).PSendSysMessage("The Teleporter has been spawened, you have 30 seconds to choose a destination.");
  		return true;
	}

};

void AddSC_item_spawn_teleporter()
{
	new item_spawn_teleporter();
}