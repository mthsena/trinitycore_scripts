#include "ScriptPCH.h"
#include <cstring>
#include "ObjectMgr.h"

class voterewarder : public CreatureScript
{
    public:

        voterewarder()
            : CreatureScript("voterewarder")
        {
        }

        void RewardItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
            QueryResult result;
            result = CharacterDatabase.PQuery("SELECT vp FROM realmd.account WHERE id = '%u' AND vp >= '0'", player->GetSession()->GetAccountId());
            char str[200];
            if (!result) // check
            {
                sprintf(str,"Your have abused our systems and gotten a negative balance on your Voting Points. Your points are set to 0.");
		  LoginDatabase.PQuery("UPDATE realmd.account set vp = 0 WHERE id = '%u'", player->GetSession()->GetAccountId());
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, pCreature);
                pCreature->MonsterSay(str, LANG_UNIVERSAL, player->GetGUID());
                return;
            }

            Field *fields = result->Fetch();
            uint32 points = fields[0].GetUInt32();
 
            if (item == 0)
            {
                sprintf(str,"You got %u voting points!", points);
                player->MonsterWhisper(str,player->GetGUID(),true);
            }
            else
            {
                if (points < cost)
                {
                     sprintf(str,"You don't have enough points for this item, you must vote on www.unforgivenwow.com!");
                     player->MonsterWhisper(str,player->GetGUID(),true);
                }
                else
                {
                    if (player->AddItem(item, count))
                    {
  			   std::string DateTime = "%Y-%m-%d %H:%M:%S";
			   ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
                        CharacterDatabase.PQuery("Update realmd.account Set vp = vp - '%u' WHERE id = '%u'", cost, player->GetSession()->GetAccountId());
                        LoginDatabase.PQuery("INSERT INTO realmd.vote_purchases (account_id, character_name, character_guid, vote_item_id, vote_item_name, vote_item_amount, date) VALUES ('%u', '%s', '%u', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), player->GetGUIDLow(), item, itemTemplate->Name1.c_str(), count, DateTime.c_str());
                        sprintf(str,"Your points are taken and your item is in your bag!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
			   player->SaveToDB();
                    }
                    else
                    {
                        sprintf(str,"Item can't be given maybe your bag is full or you already got the item!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
                    }

                }
            }
            player->PlayerTalkClass->ClearMenus();
            OnGossipHello(player, pCreature);
        }

bool HasCheatCooldown(Player* player)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM character_cooldown WHERE guid = '%u' AND cooldown=1", player->GetGUIDLow());
	if(result)
		return true;
	return false;
}
bool HasCheatCasttime(Player* player)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM character_casttime WHERE guid = '%u' AND casttime=1", player->GetGUIDLow());
	if(result)
		return true;
	return false;
}
bool HasCheatPower(Player* player)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM character_cheatpower WHERE guid = '%u' AND cheatpower=1", player->GetGUIDLow());
	if(result)
		return true;
	return false;
}

        bool OnGossipHello(Player* player, Creature* pCreature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "How much voting points do i have?", GOSSIP_SENDER_MAIN, 1000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Get a preview of the vote items", GOSSIP_SENDER_MAIN, 9998);
	     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "NEW: Cheats", GOSSIP_SENDER_MAIN, 5400);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Weapons", GOSSIP_SENDER_MAIN, 2000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Rings/Trinkets/Amulets", GOSSIP_SENDER_MAIN, 3000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Armors", GOSSIP_SENDER_MAIN, 300);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Special Items", GOSSIP_SENDER_MAIN, 5000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Special Tokens", GOSSIP_SENDER_MAIN, 4000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Shirts - 30 VP", GOSSIP_SENDER_MAIN, 10000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Talisman - 36 VP", GOSSIP_SENDER_MAIN, 11000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Emblem of Voting - 1 VP", GOSSIP_SENDER_MAIN, 4005);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voting Sets", GOSSIP_SENDER_MAIN, 5006);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Ancient Box - 80 VP", GOSSIP_SENDER_MAIN, 5007);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Unforgiven Gem - 25 VP - 3 Gems", GOSSIP_SENDER_MAIN, 5100);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Portable Mailbox - 40 VP", GOSSIP_SENDER_MAIN, 5200);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Multi Vendor - 40 VP", GOSSIP_SENDER_MAIN, 5300);

            player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
            case 5400:
                player->PlayerTalkClass->ClearMenus();
		  if(!HasCheatCooldown(player))
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Cooldown Cheat - 150 VP", GOSSIP_SENDER_MAIN, 5401);
		  if(!HasCheatCasttime(player))
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Casttime Cheat - 150 VP", GOSSIP_SENDER_MAIN, 5402);
		  if(!HasCheatPower(player))
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Power Cheat - 100 VP", GOSSIP_SENDER_MAIN, 5403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 5401:
		RewardItem(player, pCreature,24,1,150);
		break;
            case 5402:
		RewardItem(player, pCreature,25,1,150);
		break;
            case 5403:
		RewardItem(player, pCreature,26,1,100);
		break;
            case 5200:
                RewardItem(player, pCreature,40768,1,30);
                break;
	     case 5300:
		RewardItem(player, pCreature,37298,1,30);
		break;
            case 5100:
                RewardItem(player, pCreature,29765,3,20);
                break;
            case 300:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Cloak - 45 VP", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Tabard - 30 VP", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Bag - 15 VP", GOSSIP_SENDER_MAIN, 303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Shield of Neverending Hunger - 40 VP", GOSSIP_SENDER_MAIN, 304);
                if(player->getClass() == CLASS_HUNTER)
		  {
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Quiver - 30 VP", GOSSIP_SENDER_MAIN, 305);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Ammo Pouch - 15 VP", GOSSIP_SENDER_MAIN, 306);
		  }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 301:
                RewardItem(player, pCreature,42081,1,45);
                break;
            case 302:
                RewardItem(player, pCreature,19031,1,30);
                break;
            case 303:
                RewardItem(player, pCreature,21843,1,15);
                break;
            case 304:
                RewardItem(player, pCreature,51791,1,40);
                break;
            case 305:
                RewardItem(player, pCreature,34100,1,30);
                break;
            case 306:
                RewardItem(player, pCreature,34099,1,40);
                break;
            case 1000:
                RewardItem(player, pCreature, 0, 0, 0);
                break;
            case 2000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Staves", GOSSIP_SENDER_MAIN, 2003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ranged", GOSSIP_SENDER_MAIN, 2004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Off-Hand Weapons", GOSSIP_SENDER_MAIN, 2005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Main-Hand Weapons", GOSSIP_SENDER_MAIN, 2006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Sword of Hailstorm - 40 VP", GOSSIP_SENDER_MAIN, 2101);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Dagger - 40 VP", GOSSIP_SENDER_MAIN, 2102);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2101:
                RewardItem(player, pCreature,40491,1,40);
                break;
            case 2102:
                RewardItem(player, pCreature,50016,1,40);
                break;
            case 2002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Unforgiven Blade of Culling (Axe) - 70 VP", GOSSIP_SENDER_MAIN, 2201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Bloodfall Polearm of Unforgiven (Polearm) - 70 VP", GOSSIP_SENDER_MAIN, 2202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Bonegrinder of Unforgiven (Mace) - 70 VP", GOSSIP_SENDER_MAIN, 2203);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Unforgiven Claymore of Madness (Sword) - 70 VP", GOSSIP_SENDER_MAIN, 2204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2201:
                RewardItem(player, pCreature,50798,1,70);
                break;
            case 2202:
                RewardItem(player, pCreature,50178,1,70);
                break;
            case 2203:
                RewardItem(player, pCreature,42322,1,70);
                break;
            case 2204:
                RewardItem(player, pCreature,50048,1,70);
                break;
            case 2003:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Staff of Sorrow - 70 VP", GOSSIP_SENDER_MAIN, 2301);
                if(player->getClass() == CLASS_DRUID)
		  {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Feral Staff - 70 VP", GOSSIP_SENDER_MAIN, 2302);
		  }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2301:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,50429,1,70);
		  }
                break;
	     case 2302:
                RewardItem(player, pCreature,1515,1,70);
                break;
            case 2004:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Bow of the Ancient Gods - 35 VP", GOSSIP_SENDER_MAIN, 2401);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Gun of the Ancient Gods - 35 VP", GOSSIP_SENDER_MAIN, 2402);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Wand of the Ancient Gods - 35 VP", GOSSIP_SENDER_MAIN, 2403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2401:
                if(player->getClass() != CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Hunter, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,34529,1,35);
		  }
                break;
            case 2402:
                if(player->getClass() != CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Hunter, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,45261,1,35);
		  }
                break;
            case 2403:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,45257,1,35);
		  }
                break;
            case 2005:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Warglaive (Off Hand) - 50 VP", GOSSIP_SENDER_MAIN, 2501);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Fist (Off Hand) - 50 VP", GOSSIP_SENDER_MAIN, 2502);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2501:
                RewardItem(player, pCreature, 15335,1,50);
                break;
            case 2502:
                RewardItem(player, pCreature, 32945,1,40);
                break;
            case 2006:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Warglaive (Main Hand) - 50 VP", GOSSIP_SENDER_MAIN, 2601);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Fist (Main Hand) - 50 VP", GOSSIP_SENDER_MAIN, 2602);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 2601:
                RewardItem(player, pCreature, 3400,1,50);
                break;
            case 2602:
                RewardItem(player, pCreature, 32946,1,40);
                break;
            case 3000:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Trinket of the Comet - 30 VP", GOSSIP_SENDER_MAIN, 3001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Band - 35 VP", GOSSIP_SENDER_MAIN, 3002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ring of Haste - 35 VP", GOSSIP_SENDER_MAIN, 3004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "The Black Hole - 40 VP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Necklace of the Ancient Prophet - 40 VP", GOSSIP_SENDER_MAIN, 3005);
		  if (player->GetTeam() == HORDE)
		  {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Medallion of the Horde - 35 VP", GOSSIP_SENDER_MAIN, 3006);
		  } else {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Medallion of the Alliance - 35 VP", GOSSIP_SENDER_MAIN, 3007);
		  }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 3006:
                RewardItem(player, pCreature, 42122,1,35);
                break;
            case 3007:
                RewardItem(player, pCreature, 42123,1,35);
                break;
            case 3001:
                RewardItem(player, pCreature, 50647,1,30);
                break;
            case 3002:
                RewardItem(player, pCreature, 51878,1,35);
                break;
            case 3003:
                RewardItem(player, pCreature, 45292,1,40);
                break;
            case 3004:
                RewardItem(player, pCreature, 50404,1,35);
                break;
            case 3005:
                RewardItem(player, pCreature, 17782,1,35);
                break;
            case 4000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Levelup Token - 1 VP", GOSSIP_SENDER_MAIN, 5040);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Faction Change Token - 18 VP", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Name Change Token - 18 VP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Re-Customize Token - 18 VP", GOSSIP_SENDER_MAIN, 4003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "200 Event Coins - 36 VP", GOSSIP_SENDER_MAIN, 4004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Berserk Token x5 - 10 VP", GOSSIP_SENDER_MAIN, 4006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Honor Booster - 10 VP", GOSSIP_SENDER_MAIN, 4007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Horn of Thorim - 2 VP", GOSSIP_SENDER_MAIN, 4008);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Arena Token - 48 VP", GOSSIP_SENDER_MAIN, 4028);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Group Summoning Token - 60 VP", GOSSIP_SENDER_MAIN, 4029);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Temporary Item Token - 10 VP", GOSSIP_SENDER_MAIN, 4030);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Friendlystep - 100 VP", GOSSIP_SENDER_MAIN, 4031);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 4031:
                RewardItem(player, pCreature, 985410,1,100);
                break;
            case 5040:
                RewardItem(player, pCreature, 44728,1,1);
                break;
            case 4038:
                RewardItem(player, pCreature, 29435,1,12);
                break;
            case 4030:
                RewardItem(player, pCreature, 9850100,1,10);
                break;
            case 4028:
                RewardItem(player, pCreature, 29436,1,48);
                break;
            case 4029:
                RewardItem(player, pCreature, 190,1,60);
                break;
            case 4001:
                RewardItem(player, pCreature, 5,1,18);
                break;
            case 4002:
                RewardItem(player, pCreature, 6,1,18);
                break;
            case 4003:
                RewardItem(player, pCreature, 1,1,18);
                break;
            case 4004:
                RewardItem(player, pCreature, 16,1,36);
                break;
            case 4005:
                RewardItem(player, pCreature, 40753,1,1);
                break;
            case 4006:
                RewardItem(player, pCreature, 31,5,10);
                break;
            case 4007:
                RewardItem(player, pCreature, 44115,5,10);
                break;
            case 4008:
                RewardItem(player, pCreature, 44773,1,2);
                break;
            case 5000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Idol - 30 VP", GOSSIP_SENDER_MAIN, 5001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Thrown - 30 VP", GOSSIP_SENDER_MAIN, 5002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Totem - 30 VP", GOSSIP_SENDER_MAIN, 5003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Sigil - 30 VP", GOSSIP_SENDER_MAIN, 5004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Libram - 30 VP", GOSSIP_SENDER_MAIN, 5005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 5001:
                if(player->getClass() != CLASS_DRUID) {
		  char str[200];
		  sprintf(str,"Your not a Druid, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 50457,1,30);
		  } 
                break;
            case 5002:
                if(player->getClass() != CLASS_ROGUE) {
		  char str[200];
		  sprintf(str,"Your not a Rogue, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 27631,1,30);
		  } 
                break;
            case 5003:
                if(player->getClass() != CLASS_SHAMAN) {
		  char str[200];
		  sprintf(str,"Your not a Shaman, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 47667,1,30);
		  } 
                break;
            case 5004:
                if(player->getClass() != CLASS_DEATH_KNIGHT) {
		  char str[200];
		  sprintf(str,"Your not a Death Knight, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 47672,1,30);
		  } 
                break;
            case 5005:
                if(player->getClass() != CLASS_PALADIN) {
		  char str[200];
		  sprintf(str,"Your not a Paladin, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 50455,1,30);
		  } 
                break;
            case 5006:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voting Tier I Helmet - 45 VP", GOSSIP_SENDER_MAIN, 5130);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voting Tier I Shoulder - 45 VP", GOSSIP_SENDER_MAIN, 5131);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voting Tier I Chest - 45 VP", GOSSIP_SENDER_MAIN, 5132);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voting Tier I Gloves - 45 VP", GOSSIP_SENDER_MAIN, 5133);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voting Tier I Leggings - 45 VP", GOSSIP_SENDER_MAIN, 5134);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85001, pCreature->GetGUID());
                return true;
                break;
            case 5130:
                RewardItem(player, pCreature, 451662,1,45);
                break;
            case 5131:
                RewardItem(player, pCreature, 451661,1,45);
                break;
            case 5132:
                RewardItem(player, pCreature, 451658,1,45);
                break;
            case 5133:
                RewardItem(player, pCreature, 451659,1,45);
                break;
            case 5134:
                RewardItem(player, pCreature, 451660,1,45);
                break;
            case 5007:
                RewardItem(player, pCreature, 92555,1,80);
                break;
	     case 6000:
		  player->DestroyItemCount(22, 1, true, false);
		  LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '-1')", player->GetSession()->GetAccountId());
		  LoginDatabase.PExecute("REPLACE INTO account_premium (`id`, `setdate`, `unsetdate`, `premium_type`, `active`) VALUES ('%u', '0', '0', '1', '1')", player->GetSession()->GetAccountId());
		  char str[200];
		  sprintf(str,"Your now a VIP, thank you for supporting our server!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
		  break;
	     case 11000: // voters talisman
		  switch(player->getClass())
		  {
		  case CLASS_WARRIOR:
                RewardItem(player, pCreature, 250101,1,36);
   		  break;
		  case CLASS_PALADIN:
                RewardItem(player, pCreature, 250107,1,36);
     		  break;
		  case CLASS_HUNTER:
                RewardItem(player, pCreature, 250110,1,36);
	         break;
		  case CLASS_ROGUE:
                RewardItem(player, pCreature, 250105,1,36);
 	         break;
	 	  case CLASS_PRIEST:
                RewardItem(player, pCreature, 250108,1,36);
       	  break;
		  case CLASS_DEATH_KNIGHT:
                RewardItem(player, pCreature, 250102,1,36);
      	         break;
		  case CLASS_SHAMAN:
                RewardItem(player, pCreature, 250109,1,36);
      	 	  break;
		  case CLASS_MAGE:
                RewardItem(player, pCreature, 250103,1,36);
       	  break;
		  case CLASS_WARLOCK:
                RewardItem(player, pCreature, 250106,1,36);
        	  break;
		  case CLASS_DRUID:
                RewardItem(player, pCreature, 250104,1,36);
                break;

		  default: break;
		  }
		  break;
	     case 10000:
		  switch(player->getClass())
		  {
		  case CLASS_WARRIOR:
                RewardItem(player, pCreature, 62009,1,30);
   		  break;
		  case CLASS_PALADIN:
                RewardItem(player, pCreature, 62007,1,30);
     		  break;
		  case CLASS_HUNTER:
                RewardItem(player, pCreature, 61005,1,30);
	         break;
		  case CLASS_ROGUE:
                RewardItem(player, pCreature, 62004,1,30);
 	         break;
	 	  case CLASS_PRIEST:
                RewardItem(player, pCreature, 62010,1,30);
       	  break;
		  case CLASS_DEATH_KNIGHT:
                RewardItem(player, pCreature, 62006,1,30);
      	         break;
		  case CLASS_SHAMAN:
                RewardItem(player, pCreature, 62001,1,30);
      	 	  break;
		  case CLASS_MAGE:
                RewardItem(player, pCreature, 62008,1,30);
      	 	  break;
		  case CLASS_WARLOCK:
                RewardItem(player, pCreature, 62003,1,30);
        	  break;
		  case CLASS_DRUID:
                RewardItem(player, pCreature, 62000,1,30);
                break;

		  default: break;
		  }
		  break;
	     case 9998:
		  player->GetSession()->SendListInventory(pCreature->GetGUID());
		  break;
            case 9999:
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, pCreature);
                break;
            }


            return true;
        }

};

void AddSC_voterewarder()
{
    new voterewarder();
}