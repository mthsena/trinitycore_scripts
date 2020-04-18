#include "ScriptPCH.h"

class refundvendor : public CreatureScript
{
    public:

        refundvendor()
            : CreatureScript("refundvendor")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Weapons", GOSSIP_SENDER_MAIN, 2000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Rings/Trinkets/Amulets", GOSSIP_SENDER_MAIN, 3000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Armors", GOSSIP_SENDER_MAIN, 300);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: FROSTMOURNE = 35 DP", GOSSIP_SENDER_MAIN, 9997);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Special Items", GOSSIP_SENDER_MAIN, 5000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Shirts = 10 DP", GOSSIP_SENDER_MAIN, 10000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Talisman = 20 DP", GOSSIP_SENDER_MAIN, 11000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Send back donation set.", GOSSIP_SENDER_MAIN, 13000);

            pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
            case 13000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Both includes: +5 Enchant + 30 gem + 10 reforge.", GOSSIP_SENDER_MAIN, 13000);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Get first arena set + 75 dp", GOSSIP_SENDER_MAIN, 13001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Get best arena set.", GOSSIP_SENDER_MAIN, 13002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
	     case 13001: // donors set - arena +75
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(65015, 1) && pPlayer->HasItemCount(65016, 1) && pPlayer->HasItemCount(65017, 1) && pPlayer->HasItemCount(65018, 1) && pPlayer->HasItemCount(65019, 1))
		  {
			pPlayer->DestroyItemCount(65015, 1, true);
			pPlayer->DestroyItemCount(65016, 1, true);
			pPlayer->DestroyItemCount(65017, 1, true);
			pPlayer->DestroyItemCount(65018, 1, true);
			pPlayer->DestroyItemCount(65019, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);

			pPlayer->AddItem(291094, 1);
			pPlayer->AddItem(291092, 1);
			pPlayer->AddItem(291093, 1);
			pPlayer->AddItem(261536, 1);
			pPlayer->AddItem(261537, 1);
			pPlayer->AddItem(261538, 1);
			pPlayer->AddItem(261539, 1);
			pPlayer->AddItem(261540, 1);

			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(65035, 1) && pPlayer->HasItemCount(65036, 1) && pPlayer->HasItemCount(65037, 1) && pPlayer->HasItemCount(65038, 1) && pPlayer->HasItemCount(65039, 1))
		  {
			pPlayer->DestroyItemCount(65035, 1, true);
			pPlayer->DestroyItemCount(65036, 1, true);
			pPlayer->DestroyItemCount(65037, 1, true);
			pPlayer->DestroyItemCount(65038, 1, true);
			pPlayer->DestroyItemCount(65039, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(271091, 1);
			pPlayer->AddItem(271089, 1);
			pPlayer->AddItem(274551, 1);
			pPlayer->AddItem(274555, 1);
			pPlayer->AddItem(274552, 1);
			pPlayer->AddItem(274553, 1);
			pPlayer->AddItem(274554, 1);
			pPlayer->AddItem(271090, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
     		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(65005, 1) && pPlayer->HasItemCount(65006, 1) && pPlayer->HasItemCount(65007, 1) && pPlayer->HasItemCount(65008, 1) && pPlayer->HasItemCount(65009, 1))
		  {
			pPlayer->DestroyItemCount(65005, 1, true);
			pPlayer->DestroyItemCount(65006, 1, true);
			pPlayer->DestroyItemCount(65007, 1, true);
			pPlayer->DestroyItemCount(65008, 1, true);
			pPlayer->DestroyItemCount(65009, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(264532, 1);
			pPlayer->AddItem(264533, 1);
			pPlayer->AddItem(264534, 1);
			pPlayer->AddItem(264531, 1);
			pPlayer->AddItem(264535, 1);
			pPlayer->AddItem(271088, 1);
			pPlayer->AddItem(271087, 1);
			pPlayer->AddItem(271086, 1);


			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
	         break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(65010, 1) && pPlayer->HasItemCount(65011, 1) && pPlayer->HasItemCount(65012, 1) && pPlayer->HasItemCount(65013, 1) && pPlayer->HasItemCount(65014, 1))
		  {
			pPlayer->DestroyItemCount(65010, 1, true);
			pPlayer->DestroyItemCount(65011, 1, true);
			pPlayer->DestroyItemCount(65012, 1, true);
			pPlayer->DestroyItemCount(65013, 1, true);
			pPlayer->DestroyItemCount(65014, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(271083, 1);
			pPlayer->AddItem(264541, 1);
			pPlayer->AddItem(264545, 1);
			pPlayer->AddItem(264544, 1);
			pPlayer->AddItem(264543, 1);
			pPlayer->AddItem(264542, 1);
			pPlayer->AddItem(271084, 1);
			pPlayer->AddItem(271085, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
 	         break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(65020, 1) && pPlayer->HasItemCount(65021, 1) && pPlayer->HasItemCount(65022, 1) && pPlayer->HasItemCount(65023, 1) && pPlayer->HasItemCount(65024, 1))
		  {
			pPlayer->DestroyItemCount(65020, 1, true);
			pPlayer->DestroyItemCount(65021, 1, true);
			pPlayer->DestroyItemCount(65022, 1, true);
			pPlayer->DestroyItemCount(65023, 1, true);
			pPlayer->DestroyItemCount(65024, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(271077, 1);
			pPlayer->AddItem(271079, 1);
			pPlayer->AddItem(271078, 1);
			pPlayer->AddItem(264546, 1);
			pPlayer->AddItem(264547, 1);
			pPlayer->AddItem(264549, 1);
			pPlayer->AddItem(264548, 1);
			pPlayer->AddItem(264550, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(65000, 1) && pPlayer->HasItemCount(65001, 1) && pPlayer->HasItemCount(65002, 1) && pPlayer->HasItemCount(65003, 1) && pPlayer->HasItemCount(65004, 1))
		  {
			pPlayer->DestroyItemCount(65000, 1, true);
			pPlayer->DestroyItemCount(65001, 1, true);
			pPlayer->DestroyItemCount(65002, 1, true);
			pPlayer->DestroyItemCount(65003, 1, true);
			pPlayer->DestroyItemCount(65004, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(264521, 1);
			pPlayer->AddItem(264525, 1);
			pPlayer->AddItem(264522, 1);
			pPlayer->AddItem(264523, 1);
			pPlayer->AddItem(264524, 1);
			pPlayer->AddItem(271070, 1);
			pPlayer->AddItem(271069, 1);
			pPlayer->AddItem(271068, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	         break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(65040, 1) && pPlayer->HasItemCount(65041, 1) && pPlayer->HasItemCount(65042, 1) && pPlayer->HasItemCount(65043, 1) && pPlayer->HasItemCount(65044, 1))
		  {
			pPlayer->DestroyItemCount(65040, 1, true);
			pPlayer->DestroyItemCount(65041, 1, true);
			pPlayer->DestroyItemCount(65042, 1, true);
			pPlayer->DestroyItemCount(65043, 1, true);
			pPlayer->DestroyItemCount(65044, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(271082, 1);
			pPlayer->AddItem(271080, 1);
			pPlayer->AddItem(271081, 1);
			pPlayer->AddItem(264511, 1);
			pPlayer->AddItem(264515, 1);
			pPlayer->AddItem(264512, 1);
			pPlayer->AddItem(264514, 1);
			pPlayer->AddItem(264513, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	 	  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(65045, 1) && pPlayer->HasItemCount(65046, 1) && pPlayer->HasItemCount(65047, 1) && pPlayer->HasItemCount(65048, 1) && pPlayer->HasItemCount(65049, 1))
		  {
			pPlayer->DestroyItemCount(65045, 1, true);
			pPlayer->DestroyItemCount(65046, 1, true);
			pPlayer->DestroyItemCount(65047, 1, true);
			pPlayer->DestroyItemCount(65048, 1, true);
			pPlayer->DestroyItemCount(65049, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(271075, 1);
			pPlayer->AddItem(271076, 1);
			pPlayer->AddItem(264557, 1);
			pPlayer->AddItem(264558, 1);
			pPlayer->AddItem(264560, 1);
			pPlayer->AddItem(264556, 1);
			pPlayer->AddItem(264559, 1);
			pPlayer->AddItem(271074, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(65030, 1) && pPlayer->HasItemCount(65031, 1) && pPlayer->HasItemCount(65032, 1) && pPlayer->HasItemCount(65033, 1) && pPlayer->HasItemCount(65034, 1))
		  {
			pPlayer->DestroyItemCount(65030, 1, true);
			pPlayer->DestroyItemCount(65031, 1, true);
			pPlayer->DestroyItemCount(65032, 1, true);
			pPlayer->DestroyItemCount(65033, 1, true);
			pPlayer->DestroyItemCount(65034, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(264517, 1);
			pPlayer->AddItem(264519, 1);
			pPlayer->AddItem(264518, 1);
			pPlayer->AddItem(264516, 1);
			pPlayer->AddItem(264520, 1);
			pPlayer->AddItem(271073, 1);
			pPlayer->AddItem(271072, 1);
			pPlayer->AddItem(271071, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
        	  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(65025, 1) && pPlayer->HasItemCount(65026, 1) && pPlayer->HasItemCount(65027, 1) && pPlayer->HasItemCount(65028, 1) && pPlayer->HasItemCount(65029, 1))
		  {
			pPlayer->DestroyItemCount(65025, 1, true);
			pPlayer->DestroyItemCount(65026, 1, true);
			pPlayer->DestroyItemCount(65027, 1, true);
			pPlayer->DestroyItemCount(65028, 1, true);
			pPlayer->DestroyItemCount(65029, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(264526, 1);
			pPlayer->AddItem(264529, 1);
			pPlayer->AddItem(264527, 1);
			pPlayer->AddItem(264528, 1);
			pPlayer->AddItem(264530, 1);
			pPlayer->AddItem(271067, 1);
			pPlayer->AddItem(271066, 1);
			pPlayer->AddItem(271065, 1);

			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

		  default: break;
		  }
		  break;
	     case 13002: // donors set - arena +75
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(65015, 1) && pPlayer->HasItemCount(65016, 1) && pPlayer->HasItemCount(65017, 1) && pPlayer->HasItemCount(65018, 1) && pPlayer->HasItemCount(65019, 1))
		  {
			pPlayer->DestroyItemCount(65015, 1, true);
			pPlayer->DestroyItemCount(65016, 1, true);
			pPlayer->DestroyItemCount(65017, 1, true);
			pPlayer->DestroyItemCount(65018, 1, true);
			pPlayer->DestroyItemCount(65019, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(191094, 1);
			pPlayer->AddItem(191092, 1);
			pPlayer->AddItem(191093, 1);
			pPlayer->AddItem(161536, 1);
			pPlayer->AddItem(161537, 1);
			pPlayer->AddItem(161538, 1);
			pPlayer->AddItem(161539, 1);
			pPlayer->AddItem(161540, 1);


			
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(65035, 1) && pPlayer->HasItemCount(65036, 1) && pPlayer->HasItemCount(65037, 1) && pPlayer->HasItemCount(65038, 1) && pPlayer->HasItemCount(65039, 1))
		  {
			pPlayer->DestroyItemCount(65035, 1, true);
			pPlayer->DestroyItemCount(65036, 1, true);
			pPlayer->DestroyItemCount(65037, 1, true);
			pPlayer->DestroyItemCount(65038, 1, true);
			pPlayer->DestroyItemCount(65039, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(171091, 1);
			pPlayer->AddItem(171089, 1);
			pPlayer->AddItem(174551, 1);
			pPlayer->AddItem(174555, 1);
			pPlayer->AddItem(174552, 1);
			pPlayer->AddItem(174553, 1);
			pPlayer->AddItem(174554, 1);
			pPlayer->AddItem(171090, 1);


			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
     		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(65005, 1) && pPlayer->HasItemCount(65006, 1) && pPlayer->HasItemCount(65007, 1) && pPlayer->HasItemCount(65008, 1) && pPlayer->HasItemCount(65009, 1))
		  {
			pPlayer->DestroyItemCount(65005, 1, true);
			pPlayer->DestroyItemCount(65006, 1, true);
			pPlayer->DestroyItemCount(65007, 1, true);
			pPlayer->DestroyItemCount(65008, 1, true);
			pPlayer->DestroyItemCount(65009, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(164532, 1);
			pPlayer->AddItem(164533, 1);
			pPlayer->AddItem(164534, 1);
			pPlayer->AddItem(164531, 1);
			pPlayer->AddItem(164535, 1);
			pPlayer->AddItem(171088, 1);
			pPlayer->AddItem(171087, 1);
			pPlayer->AddItem(171086, 1);

			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
	         break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(65010, 1) && pPlayer->HasItemCount(65011, 1) && pPlayer->HasItemCount(65012, 1) && pPlayer->HasItemCount(65013, 1) && pPlayer->HasItemCount(65014, 1))
		  {
			pPlayer->DestroyItemCount(65010, 1, true);
			pPlayer->DestroyItemCount(65011, 1, true);
			pPlayer->DestroyItemCount(65012, 1, true);
			pPlayer->DestroyItemCount(65013, 1, true);
			pPlayer->DestroyItemCount(65014, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(171083, 1);
			pPlayer->AddItem(164541, 1);
			pPlayer->AddItem(164545, 1);
			pPlayer->AddItem(164544, 1);
			pPlayer->AddItem(164543, 1);
			pPlayer->AddItem(164542, 1);
			pPlayer->AddItem(171084, 1);
			pPlayer->AddItem(171085, 1);


			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
 	         break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(65020, 1) && pPlayer->HasItemCount(65021, 1) && pPlayer->HasItemCount(65022, 1) && pPlayer->HasItemCount(65023, 1) && pPlayer->HasItemCount(65024, 1))
		  {
			pPlayer->DestroyItemCount(65020, 1, true);
			pPlayer->DestroyItemCount(65021, 1, true);
			pPlayer->DestroyItemCount(65022, 1, true);
			pPlayer->DestroyItemCount(65023, 1, true);
			pPlayer->DestroyItemCount(65024, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(171077, 1);
			pPlayer->AddItem(171079, 1);
			pPlayer->AddItem(171078, 1);
			pPlayer->AddItem(164546, 1);
			pPlayer->AddItem(164547, 1);
			pPlayer->AddItem(164549, 1);
			pPlayer->AddItem(164548, 1);
			pPlayer->AddItem(164550, 1);


			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(65000, 1) && pPlayer->HasItemCount(65001, 1) && pPlayer->HasItemCount(65002, 1) && pPlayer->HasItemCount(65003, 1) && pPlayer->HasItemCount(65004, 1))
		  {
			pPlayer->DestroyItemCount(65000, 1, true);
			pPlayer->DestroyItemCount(65001, 1, true);
			pPlayer->DestroyItemCount(65002, 1, true);
			pPlayer->DestroyItemCount(65003, 1, true);
			pPlayer->DestroyItemCount(65004, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(164521, 1);
			pPlayer->AddItem(164525, 1);
			pPlayer->AddItem(164522, 1);
			pPlayer->AddItem(164523, 1);
			pPlayer->AddItem(164524, 1);
			pPlayer->AddItem(171070, 1);
			pPlayer->AddItem(171069, 1);
			pPlayer->AddItem(171068, 1);


			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	         break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(65040, 1) && pPlayer->HasItemCount(65041, 1) && pPlayer->HasItemCount(65042, 1) && pPlayer->HasItemCount(65043, 1) && pPlayer->HasItemCount(65044, 1))
		  {
			pPlayer->DestroyItemCount(65040, 1, true);
			pPlayer->DestroyItemCount(65041, 1, true);
			pPlayer->DestroyItemCount(65042, 1, true);
			pPlayer->DestroyItemCount(65043, 1, true);
			pPlayer->DestroyItemCount(65044, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(171082, 1);
			pPlayer->AddItem(171080, 1);
			pPlayer->AddItem(171081, 1);
			pPlayer->AddItem(164511, 1);
			pPlayer->AddItem(164515, 1);
			pPlayer->AddItem(164512, 1);
			pPlayer->AddItem(164514, 1);
			pPlayer->AddItem(164513, 1);


			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	 	  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(65045, 1) && pPlayer->HasItemCount(65046, 1) && pPlayer->HasItemCount(65047, 1) && pPlayer->HasItemCount(65048, 1) && pPlayer->HasItemCount(65049, 1))
		  {
			pPlayer->DestroyItemCount(65045, 1, true);
			pPlayer->DestroyItemCount(65046, 1, true);
			pPlayer->DestroyItemCount(65047, 1, true);
			pPlayer->DestroyItemCount(65048, 1, true);
			pPlayer->DestroyItemCount(65049, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(171075, 1);
			pPlayer->AddItem(171076, 1);
			pPlayer->AddItem(164557, 1);
			pPlayer->AddItem(164558, 1);
			pPlayer->AddItem(164560, 1);
			pPlayer->AddItem(164556, 1);
			pPlayer->AddItem(164559, 1);
			pPlayer->AddItem(171074, 1);

			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(65030, 1) && pPlayer->HasItemCount(65031, 1) && pPlayer->HasItemCount(65032, 1) && pPlayer->HasItemCount(65033, 1) && pPlayer->HasItemCount(65034, 1))
		  {
			pPlayer->DestroyItemCount(65030, 1, true);
			pPlayer->DestroyItemCount(65031, 1, true);
			pPlayer->DestroyItemCount(65032, 1, true);
			pPlayer->DestroyItemCount(65033, 1, true);
			pPlayer->DestroyItemCount(65034, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(164517, 1);
			pPlayer->AddItem(164519, 1);
			pPlayer->AddItem(164518, 1);
			pPlayer->AddItem(164516, 1);
			pPlayer->AddItem(164520, 1);
			pPlayer->AddItem(171073, 1);
			pPlayer->AddItem(171072, 1);
			pPlayer->AddItem(171071, 1);


			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
        	  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(65025, 1) && pPlayer->HasItemCount(65026, 1) && pPlayer->HasItemCount(65027, 1) && pPlayer->HasItemCount(65028, 1) && pPlayer->HasItemCount(65029, 1))
		  {
			pPlayer->DestroyItemCount(65025, 1, true);
			pPlayer->DestroyItemCount(65026, 1, true);
			pPlayer->DestroyItemCount(65027, 1, true);
			pPlayer->DestroyItemCount(65028, 1, true);
			pPlayer->DestroyItemCount(65029, 1, true);
			pPlayer->AddItem(41596, 5);
			pPlayer->AddItem(29765, 30);
			pPlayer->AddItem(65717, 20);
			pPlayer->AddItem(164526, 1);
			pPlayer->AddItem(164529, 1);
			pPlayer->AddItem(164527, 1);
			pPlayer->AddItem(164528, 1);
			pPlayer->AddItem(164530, 1);
			pPlayer->AddItem(171067, 1);
			pPlayer->AddItem(171066, 1);
			pPlayer->AddItem(171065, 1);

			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

		  default: break;
		  }
		  break;
            case 300:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Cloak of Triumph = 10 DP", GOSSIP_SENDER_MAIN, 301);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Tabard = 15 DP", GOSSIP_SENDER_MAIN, 302);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Bag = 3 DP", GOSSIP_SENDER_MAIN, 303);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Quiver = 3 DP", GOSSIP_SENDER_MAIN, 1303);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Shield = 10 DP", GOSSIP_SENDER_MAIN, 304);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 1303:
		if(pPlayer->HasItemCount(7278, 1))
		{
			pPlayer->DestroyItemCount(7278, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		} else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		}
              break;
            case 301:
		if(pPlayer->HasItemCount(21394, 1))
		{
			pPlayer->DestroyItemCount(21394, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		} else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		}
                break;
            case 302:
		  if(pPlayer->HasItemCount(20131, 1))
		  {
			pPlayer->DestroyItemCount(20131, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 303:
		  if(pPlayer->HasItemCount(20400, 1))
		  {
			pPlayer->DestroyItemCount(20400, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
                case 304:
		  if(pPlayer->HasItemCount(34185, 1))
		  {
			pPlayer->DestroyItemCount(34185, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Staves", GOSSIP_SENDER_MAIN, 2003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ranged", GOSSIP_SENDER_MAIN, 2004);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Off-Hand Weapons", GOSSIP_SENDER_MAIN, 2005);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Main-Hand Weapons", GOSSIP_SENDER_MAIN, 2006);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2001:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Sword = 10 DP", GOSSIP_SENDER_MAIN, 2101);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Dagger = 10 DP", GOSSIP_SENDER_MAIN, 2102);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Axe = 10 DP", GOSSIP_SENDER_MAIN, 2103);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Mace = 10 DP", GOSSIP_SENDER_MAIN, 2103);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2101:
		if(pPlayer->HasItemCount(50672, 1))
		{
			pPlayer->DestroyItemCount(50672, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		} else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		}
                break;
            case 2102:
		  if(pPlayer->HasItemCount(32044, 1))
		  {
			pPlayer->DestroyItemCount(32044, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2103:
		  if(pPlayer->HasItemCount(50759, 1))
		  {
			pPlayer->DestroyItemCount(50759, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2104:
		  if(pPlayer->HasItemCount(46017, 1))
		  {
			pPlayer->DestroyItemCount(46017, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2002:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Two-Hand Sword = 20 DP", GOSSIP_SENDER_MAIN, 2201);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Two-Hand Axe = 20 DP", GOSSIP_SENDER_MAIN, 2202);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Two-Hand Mace = 20 DP", GOSSIP_SENDER_MAIN, 2203);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Hunters Two-Hand Polearm = 20 DP", GOSSIP_SENDER_MAIN, 2204);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2201:
		  if(pPlayer->HasItemCount(50761, 1))
		  {
			pPlayer->DestroyItemCount(50761, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2202:
		  if(pPlayer->HasItemCount(49623, 1))
		  {
			pPlayer->DestroyItemCount(49623, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2203:
		  if(pPlayer->HasItemCount(33663, 1))
		  {
			pPlayer->DestroyItemCount(33663, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
		  break;
            case 2204:
		  if(pPlayer->HasItemCount(50425, 1))
		  {
			pPlayer->DestroyItemCount(50425, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2003:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Staff = 15 DP", GOSSIP_SENDER_MAIN, 2301);
		  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Feral Staff  = 15 DP", GOSSIP_SENDER_MAIN, 2302);
		  pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Healing Staff  = 15 DP", GOSSIP_SENDER_MAIN, 2303);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2301:
		  if(pPlayer->HasItemCount(54806, 1))
		  {
			pPlayer->DestroyItemCount(54806, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2302:
		  if(pPlayer->HasItemCount(40348, 1))
		  {
			pPlayer->DestroyItemCount(40348, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2303:
		  if(pPlayer->HasItemCount(28633, 1))
		  {
			pPlayer->DestroyItemCount(28633, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2004:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Bow = 10 DP", GOSSIP_SENDER_MAIN, 2401);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Gun = 10 DP", GOSSIP_SENDER_MAIN, 2402);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Wand = 10 DP", GOSSIP_SENDER_MAIN, 2403);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2401:
		  if(pPlayer->HasItemCount(34334, 1))
		  {
			pPlayer->DestroyItemCount(34334, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2402:
		  if(pPlayer->HasItemCount(51450, 1))
		  {
			pPlayer->DestroyItemCount(51450, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2403:
		  if(pPlayer->HasItemCount(37177, 1))
		  {
			pPlayer->DestroyItemCount(37177, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2005:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Warglaive (Off Hand) = 15 DP", GOSSIP_SENDER_MAIN, 2501);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Fist (Off Hand) = 10 DP", GOSSIP_SENDER_MAIN, 2502);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2501:
		  if(pPlayer->HasItemCount(1951, 1))
		  {
			pPlayer->DestroyItemCount(1951, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2502:
		  if(pPlayer->HasItemCount(34203, 1))
		  {
			pPlayer->DestroyItemCount(34203, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2006:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Warglaive (Main Hand) = 15 DP", GOSSIP_SENDER_MAIN, 2601);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Fist (Main Hand) = 10 DP", GOSSIP_SENDER_MAIN, 2602);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2601:
		  if(pPlayer->HasItemCount(1469, 1))
		  {
			pPlayer->DestroyItemCount(1469, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2602:
		  if(pPlayer->HasItemCount(34331, 1))
		  {
			pPlayer->DestroyItemCount(34331, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 3000:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ancient Box = 25 DP", GOSSIP_SENDER_MAIN, 3001);
		  if (pPlayer->GetTeam() == HORDE)
		  {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Medallion of the Horde = 15 DP", GOSSIP_SENDER_MAIN, 3002);
		  } else {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Medallion of the Alliance = 15 DP", GOSSIP_SENDER_MAIN, 3012);
		  }
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Card Destruction (melee) = 15 DP", GOSSIP_SENDER_MAIN, 3003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Card Judgement (spell) = 15 DP", GOSSIP_SENDER_MAIN, 3015);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Trinket of the Comet = 10 DP", GOSSIP_SENDER_MAIN, 3005);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 3001:
		  if(pPlayer->HasItemCount(50402, 1) && pPlayer->HasItemCount(52572, 1) && pPlayer->HasItemCount(34204, 1))
		  {
			pPlayer->DestroyItemCount(50402, 1, true);
			pPlayer->DestroyItemCount(52572, 1, true);
			pPlayer->DestroyItemCount(34204, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 25 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 3002:
		  if(pPlayer->HasItemCount(42126, 1))
		  {
			pPlayer->DestroyItemCount(42126, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 3003:
		  if(pPlayer->HasItemCount(42989, 1))
		  {
			pPlayer->DestroyItemCount(42989, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 3004:
		  if(pPlayer->HasItemCount(39246, 1))
		  {
			pPlayer->DestroyItemCount(39246, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 3005:
		  if(pPlayer->HasItemCount(19336, 1))
		  {
			pPlayer->DestroyItemCount(19336, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 3012:
		  if(pPlayer->HasItemCount(38589, 1))
		  {
			pPlayer->DestroyItemCount(38589, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
  	     case 3015:
		  if(pPlayer->HasItemCount(19288, 1))
		  {
			pPlayer->DestroyItemCount(19288, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
		  break;
            case 5000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Idol = 10 DP", GOSSIP_SENDER_MAIN, 5001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Thrown = 10 DP", GOSSIP_SENDER_MAIN, 5002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Totem = 10 DP", GOSSIP_SENDER_MAIN, 5003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Sigil = 10 DP", GOSSIP_SENDER_MAIN, 5004);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Libram = 10 DP", GOSSIP_SENDER_MAIN, 5005);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 5001:
		  if(pPlayer->HasItemCount(50456, 1))
		  {
			pPlayer->DestroyItemCount(50456, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 5002:
		  if(pPlayer->HasItemCount(30025, 1))
		  {
			pPlayer->DestroyItemCount(30025, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 5003:
		  if(pPlayer->HasItemCount(45169, 1))
		  {
			pPlayer->DestroyItemCount(45169, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 5004:
		  if(pPlayer->HasItemCount(45144, 1))
		  {
			pPlayer->DestroyItemCount(45144, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 5005:
		  if(pPlayer->HasItemCount(50461, 1))
		  {
			pPlayer->DestroyItemCount(50461, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
	     case 10000:
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(61009, 1))
		  {
			pPlayer->DestroyItemCount(61009, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(61007, 1))
		  {
			pPlayer->DestroyItemCount(61007, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
     		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(63005, 1))
		  {
			pPlayer->DestroyItemCount(63005, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
	         break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(61004, 1))
		  {
			pPlayer->DestroyItemCount(61004, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
 	         break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(61010, 1))
		  {
			pPlayer->DestroyItemCount(61010, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(61006, 1))
		  {
			pPlayer->DestroyItemCount(61006, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	         break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(61001, 1))
		  {
			pPlayer->DestroyItemCount(61001, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	 	  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(61008, 1))
		  {
			pPlayer->DestroyItemCount(61008, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(61003, 1))
		  {
			pPlayer->DestroyItemCount(61003, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
        	  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(61000, 1))
		  {
			pPlayer->DestroyItemCount(61000, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

		  default: break;
		  }
		  break;
	     case 11000: // donors talisman
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(32485, 1))
		  {
			pPlayer->DestroyItemCount(32485, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(32489, 1))
		  {
			pPlayer->DestroyItemCount(32489, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
     		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(32487, 1))
		  {
			pPlayer->DestroyItemCount(32487, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
	         break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(32492, 1))
		  {
			pPlayer->DestroyItemCount(32492, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
 	         break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(32490, 1))
		  {
			pPlayer->DestroyItemCount(32490, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(21670, 1))
		  {
			pPlayer->DestroyItemCount(21670, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	         break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(32491, 1))
		  {
			pPlayer->DestroyItemCount(32491, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	 	  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(32488, 1))
		  {
			pPlayer->DestroyItemCount(32488, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(32493, 1))
		  {
			pPlayer->DestroyItemCount(32493, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
        	  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(32486, 1))
		  {
			pPlayer->DestroyItemCount(32486, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

		  default: break;
		  }
		  break;
	     case 12000: // donors set
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(65015, 1) && pPlayer->HasItemCount(65016, 1) && pPlayer->HasItemCount(65017, 1) && pPlayer->HasItemCount(65018, 1) && pPlayer->HasItemCount(65019, 1))
		  {
			pPlayer->DestroyItemCount(65015, 1, true);
			pPlayer->DestroyItemCount(65016, 1, true);
			pPlayer->DestroyItemCount(65017, 1, true);
			pPlayer->DestroyItemCount(65018, 1, true);
			pPlayer->DestroyItemCount(65019, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(65035, 1) && pPlayer->HasItemCount(65036, 1) && pPlayer->HasItemCount(65037, 1) && pPlayer->HasItemCount(65038, 1) && pPlayer->HasItemCount(65039, 1))
		  {
			pPlayer->DestroyItemCount(65035, 1, true);
			pPlayer->DestroyItemCount(65036, 1, true);
			pPlayer->DestroyItemCount(65037, 1, true);
			pPlayer->DestroyItemCount(65038, 1, true);
			pPlayer->DestroyItemCount(65039, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
     		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(65005, 1) && pPlayer->HasItemCount(65006, 1) && pPlayer->HasItemCount(65007, 1) && pPlayer->HasItemCount(65008, 1) && pPlayer->HasItemCount(65009, 1))
		  {
			pPlayer->DestroyItemCount(65005, 1, true);
			pPlayer->DestroyItemCount(65006, 1, true);
			pPlayer->DestroyItemCount(65007, 1, true);
			pPlayer->DestroyItemCount(65008, 1, true);
			pPlayer->DestroyItemCount(65009, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
	         break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(65010, 1) && pPlayer->HasItemCount(65011, 1) && pPlayer->HasItemCount(65012, 1) && pPlayer->HasItemCount(65013, 1) && pPlayer->HasItemCount(65014, 1))
		  {
			pPlayer->DestroyItemCount(65010, 1, true);
			pPlayer->DestroyItemCount(65011, 1, true);
			pPlayer->DestroyItemCount(65012, 1, true);
			pPlayer->DestroyItemCount(65013, 1, true);
			pPlayer->DestroyItemCount(65014, 1, true);
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
 	         break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(65020, 1) && pPlayer->HasItemCount(65021, 1) && pPlayer->HasItemCount(65022, 1) && pPlayer->HasItemCount(65023, 1) && pPlayer->HasItemCount(65024, 1))
		  {
			pPlayer->DestroyItemCount(65020, 1, true);
			pPlayer->DestroyItemCount(65021, 1, true);
			pPlayer->DestroyItemCount(65022, 1, true);
			pPlayer->DestroyItemCount(65023, 1, true);
			pPlayer->DestroyItemCount(65024, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(65000, 1) && pPlayer->HasItemCount(65001, 1) && pPlayer->HasItemCount(65002, 1) && pPlayer->HasItemCount(65003, 1) && pPlayer->HasItemCount(65004, 1))
		  {
			pPlayer->DestroyItemCount(65000, 1, true);
			pPlayer->DestroyItemCount(65001, 1, true);
			pPlayer->DestroyItemCount(65002, 1, true);
			pPlayer->DestroyItemCount(65003, 1, true);
			pPlayer->DestroyItemCount(65004, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	         break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(65040, 1) && pPlayer->HasItemCount(65041, 1) && pPlayer->HasItemCount(65042, 1) && pPlayer->HasItemCount(65043, 1) && pPlayer->HasItemCount(65044, 1))
		  {
			pPlayer->DestroyItemCount(65040, 1, true);
			pPlayer->DestroyItemCount(65041, 1, true);
			pPlayer->DestroyItemCount(65042, 1, true);
			pPlayer->DestroyItemCount(65043, 1, true);
			pPlayer->DestroyItemCount(65044, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
      	 	  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(65045, 1) && pPlayer->HasItemCount(65046, 1) && pPlayer->HasItemCount(65047, 1) && pPlayer->HasItemCount(65048, 1) && pPlayer->HasItemCount(65049, 1))
		  {
			pPlayer->DestroyItemCount(65045, 1, true);
			pPlayer->DestroyItemCount(65046, 1, true);
			pPlayer->DestroyItemCount(65047, 1, true);
			pPlayer->DestroyItemCount(65048, 1, true);
			pPlayer->DestroyItemCount(65049, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
       	  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(65030, 1) && pPlayer->HasItemCount(65031, 1) && pPlayer->HasItemCount(65032, 1) && pPlayer->HasItemCount(65033, 1) && pPlayer->HasItemCount(65034, 1))
		  {
			pPlayer->DestroyItemCount(65030, 1, true);
			pPlayer->DestroyItemCount(65031, 1, true);
			pPlayer->DestroyItemCount(65032, 1, true);
			pPlayer->DestroyItemCount(65033, 1, true);
			pPlayer->DestroyItemCount(65034, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
        	  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(65025, 1) && pPlayer->HasItemCount(65026, 1) && pPlayer->HasItemCount(65027, 1) && pPlayer->HasItemCount(65028, 1) && pPlayer->HasItemCount(65029, 1))
		  {
			pPlayer->DestroyItemCount(65025, 1, true);
			pPlayer->DestroyItemCount(65026, 1, true);
			pPlayer->DestroyItemCount(65027, 1, true);
			pPlayer->DestroyItemCount(65028, 1, true);
			pPlayer->DestroyItemCount(65029, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;

		  default: break;
		  }
		  break;
	     case 9997:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Are you sure you wish to sell your frostmourne?", GOSSIP_SENDER_MAIN, 9997);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Yes.", GOSSIP_SENDER_MAIN, 9996);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: No.", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
	     case 9996:
		  if(pPlayer->HasItemCount(27769, 1))
		  {
			pPlayer->DestroyItemCount(27769, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 35 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			ChatHandler(pPlayer).PSendSysMessage("Success. Your donor item has been removed and your points has been refunded.");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			ChatHandler(pPlayer).PSendSysMessage("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            }

            return true;
     }
};

void AddSC_refundvendor()
{
    new refundvendor();
}
