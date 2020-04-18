class TransmogItem_NPC : public CreatureScript
{
public:
	TransmogItem_NPC() : CreatureScript("TransmogItem_NPC") {}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, "|TInterface/ICONS/INV_Chest_Plate13:30|t Type an item id here.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t What's this?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		if (action == GOSSIP_ACTION_INFO_DEF+2)
		{
			creature->MonsterWhisper("I'm a NPC that you can request item for Transmorgrification NPC Max item Level 220  ", player->GetGUID());
		    player->PlayerTalkClass->SendCloseGossip();
		}

		return true;
	}

	bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, char const* code)
	{
		player->PlayerTalkClass->ClearMenus();
		if (sender == GOSSIP_SENDER_MAIN)
		{
			switch (action)
			{
				case GOSSIP_ACTION_INFO_DEF+1:
					
					if(strlen(code) > 5)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("Invalid ItemId");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					uint32 itemId = atoi(code);

					if(!itemId)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("Invalid ItemId");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					ItemTemplate const* item_proto = sObjectMgr->GetItemTemplate(itemId);

					if (!item_proto)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("Item does not exist.");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					switch(item_proto->InventoryType)
					{
						case INVTYPE_BAG:
						case INVTYPE_NON_EQUIP:
						case INVTYPE_BODY:
						case INVTYPE_TABARD:
							ChatHandler(player->GetSession()).PSendSysMessage("Item is on the exclusion list.");
							player->PlayerTalkClass->SendCloseGossip();
							return false;
					}

					if (item_proto->ItemLevel > 220)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("Item level to high.");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					// Item Ids Here.

					if (item_proto->ItemId == 12947)
					{
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					if (item_proto->ItemId == 18970)
					{
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					// Item Ids Above.

					if (item_proto->Quality > 4)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("Item is on the exclusion list.");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					if(item_proto->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("This item is not for your faction.");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					if(item_proto->Flags2 & ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE)
					{
						ChatHandler(player->GetSession()).PSendSysMessage("This item is not for your faction.");
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					if (item_proto->Quality > 3)
					{
						if (!player->HasItemCount(32572, 0, false))
						{
							creature->MonsterWhisper("I'm sorry, you don't have any Transmogrification Tokens.", player->GetGUID());
							player->PlayerTalkClass->SendCloseGossip();
							return false;
						}

						else
						{
							player->DestroyItemCount(32572, 0, true);
							player->AddItem(itemId, 1);
							player->PlayerTalkClass->SendCloseGossip();
							return true;
						}
					}

					else
					{
						player->AddItem(itemId, 1);
						player->PlayerTalkClass->SendCloseGossip();
						return true;
					}
			}
		}
		
		return false;
	}
	};

void AddSC_TransmogItem_NPC()
{
    new TransmogItem_NPC();
}