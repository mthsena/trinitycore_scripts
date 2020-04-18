//by SymbolixDEV
#include "ScriptPCH.h"

class Arena_Scripts : public PlayerScript
{
public:
	Arena_Scripts() : PlayerScript("Arena_Scripts") {  }
	
	void OnUpdateZone(Player* player, uint32 zone, uint32 area)
	{
		float x = player->GetPositionX();
		float y = player->GetPositionY();
		float z = player->GetPositionZ();
		float ang = player->GetOrientation();
		float rot2 = std::sin(ang/2);
		float rot3 = std::cos(ang/2);
		
		switch (player->getClass())
		{
		case CLASS_MAGE:
			{
				if (zone == 3698) // Nagrand Arena.
				{
					player->SummonGameObject(193061, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 3702) // Blade's Edge Arena.
				{
					player->SummonGameObject(193061, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 4378) // Dalaran Arena.
				{
					player->SummonGameObject(193061, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 3968) // Ruins of Lordaeron.
				{
					player->SummonGameObject(193061, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 4406) // Ring of Valor.
				{
					player->SummonGameObject(193061, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				break;
				}
		
		case CLASS_WARLOCK:
			{
				if (zone == 3698) // Nagrand Arena.
				{
					player->SummonGameObject(193169, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 3702) // Blade's Edge Arena.
				{
					player->SummonGameObject(193169, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 4378) // Dalaran Arena.
				{
					player->SummonGameObject(193169, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
				if (zone == 3968) // Ruins of Lordaeron.
				{
					player->SummonGameObject(193169, x, y, z, ang, 0, 0, rot2, rot3, 30);
				}
			if (zone == 4406) // Ring of Valor.
			{
				player->SummonGameObject(193169, x, y, z, ang, 0, 0, rot2, rot3, 30);
			}
			break;
			}
		}
	}
};

void AddSC_Arena_Scripts()
{
	new Arena_Scripts;
}