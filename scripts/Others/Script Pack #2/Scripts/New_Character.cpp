class New_Character : public PlayerScript
{
public:
	New_Character() : PlayerScript("New_Character") {}

	void OnLogin(Player* player)
	{
		if (player->GetTotalPlayedTime() < 1)
		{
				if (player->GetSession()->GetSecurity() > 1)
				{
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BODY, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET1, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET2, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TABARD, true);
					player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET, true);
					player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 2586, true); // [Gamemaster's Robe]
					player->EquipNewItem(EQUIPMENT_SLOT_FEET, 11508, true); // [Gamemaster's Slippers]
					player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 12064, true); // [Gamemaster Hood]
					ChatHandler(player->GetSession()).PSendSysMessage("|cff00ccffGM character is ready for use.|r");
				}

				else // if normal char

				{
					if (player->getGender() == GENDER_MALE)
					{
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BODY, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET1, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET2, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TABARD, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET, true);
						player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 6834, true); // Tuxedo Jacket
						player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 10035, true); // Tuxedo Pants
						player->EquipNewItem(EQUIPMENT_SLOT_FEET, 6836, true); // Dress shoes
					}

					else // if female

					{
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BODY, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET1, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET2, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TABARD, true);
						player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET, true);
						player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 22279, true); // Loveley Black Dress
						player->EquipNewItem(EQUIPMENT_SLOT_FEET, 6836, true); // Dress shoes
					}
				}
			}
		}
};

void AddSC_New_Character()
{
	new New_Character;
}