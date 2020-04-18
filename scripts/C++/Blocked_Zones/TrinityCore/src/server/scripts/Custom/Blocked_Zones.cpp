#include "ScriptMgr.h"
#include "Player.h"
#include "WorldSession.h"
#include "Config.h"

class Blocked_Zones : public PlayerScript
{
public:
	Blocked_Zones() : PlayerScript("Blocked_Zones") {}

	bool bzEnable = sConfigMgr->GetBoolDefault("BZ.Enable", false);

	uint32 bzVipZoneID = sConfigMgr->GetIntDefault("BZ.VIP.ZoneID", 0);
	uint32 bzVipRequiresAccountRank = sConfigMgr->GetIntDefault("BZ.VIP.Requires.AccountRank", 0);
	uint32 bzVipRequiresItemEntry = sConfigMgr->GetIntDefault("BZ.VIP.Requires.ItemEntry", 0);
	uint32 bzVipRequiresItemCount = sConfigMgr->GetIntDefault("BZ.VIP.Requires.ItemCount", 0);

	uint32 bzGmZoneID = sConfigMgr->GetIntDefault("BZ.GM.ZoneID", 0);
	uint32 bzGmRequiresAccountRank = sConfigMgr->GetIntDefault("BZ.GM.Requires.AccountRank", 0);
	uint32 bzGmRequiresItemEntry = sConfigMgr->GetIntDefault("BZ.GM.Requires.ItemEntry", 0);
	uint32 bzGmRequiresItemCount = sConfigMgr->GetIntDefault("BZ.GM.Requires.ItemCount", 0);

	bool IsReady(Player* player, uint32 newZone, uint32 zoneID, uint32 requiresAccountRank, uint32 requiresItemEntry, uint32 requiresItemCount)
	{
		uint32 playerRank = (uint32)player->GetSession()->GetSecurity();
		bool playerHasItem = player->HasItemCount(requiresItemEntry, requiresItemCount, false);

		if (!bzEnable)
			return false;

		if (requiresItemEntry > 0)
		{
			if ((playerRank < requiresAccountRank || !playerHasItem) && newZone == zoneID)
			{
				player->GetSession()->SendNotification("You're not allowed to enter this area.");
				player->TeleportTo(player->GetStartPosition());
				return false;
			}
		}
		else
		{
			if (playerRank < requiresAccountRank && newZone == zoneID)
			{
				player->GetSession()->SendNotification("You're not allowed to enter this area.");
				player->TeleportTo(player->GetStartPosition());
				return false;
			}
		}
		return true;
	}

	void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea)
	{
		IsReady(player, newZone, bzVipZoneID, bzVipRequiresAccountRank, bzVipRequiresItemEntry, bzVipRequiresItemCount);
		IsReady(player, newZone, bzGmZoneID, bzGmRequiresAccountRank, bzGmRequiresItemEntry, bzGmRequiresItemCount);
		return;
	}
};

void AddSC_Blocked_Zones()
{
	new Blocked_Zones();
}