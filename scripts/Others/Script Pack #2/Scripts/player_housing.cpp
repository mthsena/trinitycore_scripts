#include "ScriptPCH.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "Group.h"

enum eEnums
{
    GAMEOBJECT_SPAWN_LIMIT  =	20,
    NPC_SPAWN_LIMIT	   =	10,

    SAY_NOT_INTERESTED      = -1999922,
    SAY_WRONG               = -1999923,
    SAY_CORRECT             = -1999924,

    ITEM_1 =	183779,
    ITEM_2 =	26990,
    ITEM_3 =	184140,
    ITEM_4 =	181087,
    ITEM_5 =	1594,
    ITEM_6 =	153584,
    ITEM_7 =	176210,
    ITEM_8 =	85004,
    ITEM_9 =	184284,
    ITEM_10 =	182070,
    ITEM_11 =	170592,
    ITEM_12 =	180376,
    ITEM_13 =	180379,
    ITEM_14 =	180377,

    NPC_1 =     481851,
    NPC_2 =     18885,
    NPC_3 =     18886,
    NPC_4 =     50071,
    NPC_5 =     50070,
    NPC_6 =     50170,
    NPC_7 =     50027,
    NPC_8 =     26303,
    NPC_9 =     50040,
    NPC_10 =    985000,
    NPC_11 =    32666,
    NPC_12 =    50000,

    //PACKAGE 1 GOBJS and NPCs
    P1_ITEM_1 =	179481,
    P1_ITEM_2 =	179483,
    P1_ITEM_3 =	183036,
    P1_ITEM_4 =	183516,
    P1_ITEM_5 =	184998,
    P1_NPC_1 =     50073,
    P1_NPC_2 =     1459,
    P1_NPC_3 =     24181,
    P1_NPC_4 =     985001,
    P1_NPC_5 =     70015,
    //PACKAGE 2 GOBJS and NPCs
    P2_ITEM_1 =	182774,
    P2_ITEM_2 =	186729,
    P2_ITEM_3 =	187294,
    P2_ITEM_4 =	164882,
    P2_ITEM_5 =	180876,
    P2_NPC_1 =     13,
    P2_NPC_2 =     50014,
    P2_NPC_3 =     66667,
    P2_NPC_4 =     500256,
    P2_NPC_5 =     50072,
    P2_NPC_6 =     33357,
    //PACKAGE 3 GOBJS and NPCs
    P3_ITEM_1 =	185547,
    P3_ITEM_2 =	181653,
    P3_ITEM_3 =	1607,
    P3_ITEM_4 =	186682,
    P3_ITEM_5 =	181448,
    P3_NPC_1 =     12198,
    P3_NPC_2 =     20002,
    P3_NPC_3 =     51181,
    P3_NPC_4 =     20381,
    P3_NPC_5 =     19859,
    P3_NPC_6 =     49001,
    //PACKAGE 4 GOBJS and NPCs
    P4_ITEM_1 =	8007658,
    P4_ITEM_2 =	8021000,
    P4_ITEM_3 =	383771,
    P4_ITEM_4 =	21680,
    P4_ITEM_5 =	180334,
    P4_NPC_1 =     190001,
    P4_NPC_2 =     25141,
    P4_NPC_3 =     69305,
    P4_NPC_4 =     63305,
    P4_NPC_5 =     66305,
    P4_NPC_6 =     985402,
    P4_NPC_7 =     985401
};

#define	ITEM_1_TEXT  		"Chair"
#define 	ITEM_2_TEXT  		"Table"
#define	ITEM_3_TEXT 		"Mailbox"
#define	ITEM_4_TEXT 		"Plant"
#define	ITEM_5_TEXT 		"Bookshelf"
#define	ITEM_6_TEXT 		"Campfire"
#define	ITEM_7_TEXT 		"Tent"
#define	ITEM_8_TEXT 		"Emeth the Ancient Portal"
#define	ITEM_9_TEXT 		"Purple Torch"
#define	ITEM_10_TEXT 		"Red Crystal"
#define	ITEM_11_TEXT 		"Throne"
#define	ITEM_12_TEXT 		"Berserk Buff"
#define	ITEM_13_TEXT 		"Speed Buff"
#define	ITEM_14_TEXT 		"Heal Buff"

#define	NPC_1_TEXT  		"Teleporter"
#define 	NPC_2_TEXT  		"Arena Vendor"
#define	NPC_3_TEXT 		"Invincible Gear Vendor"
#define	NPC_4_TEXT 		"Donor Vendor"
#define	NPC_5_TEXT 		"Vote Vendor"
#define	NPC_6_TEXT 		"Refund Vendor"
#define	NPC_7_TEXT 		"Honor Vendor"
#define	NPC_8_TEXT 		"Custom Gems"
#define	NPC_9_TEXT 		"Event Vendor"
#define	NPC_10_TEXT 		"God of PvP"
#define	NPC_11_TEXT 		"Training Dummy"
#define	NPC_12_TEXT 		"Battle Maiden"


//PACKAGE 1 GOBJs and NPCs
#define	P1_ITEM_1_TEXT  		"Alliance Banner"
#define 	P1_ITEM_2_TEXT  		"Horde Banner"
#define	P1_ITEM_3_TEXT 		"Rune Aura"
#define	P1_ITEM_4_TEXT 		"Purple Aura"
#define	P1_ITEM_5_TEXT 		"Flying Platform"
#define	P1_NPC_1_TEXT  		"Lord Tirion"
#define 	P1_NPC_2_TEXT  		"Deluxe Voter"
#define	P1_NPC_3_TEXT 		"Voters Gear"
#define	P1_NPC_4_TEXT 		"Master of Illusions"
#define	P1_NPC_5_TEXT 		"Title Master"
//PACKAGE 2 GOBJs and NPCs
#define	P2_ITEM_1_TEXT  		"Golden Bench"
#define 	P2_ITEM_2_TEXT  		"Bush"
#define	P2_ITEM_3_TEXT 		"Guild Vault"
#define	P2_ITEM_4_TEXT 		"Cleansed Songflower"
#define	P2_ITEM_5_TEXT 		"Elune's Blessing"
#define	P2_NPC_1_TEXT  		"Beastermaster Arogon"
#define 	P2_NPC_2_TEXT  		"Sylvannas"
#define	P2_NPC_3_TEXT 		"Sharrow"
#define	P2_NPC_4_TEXT 		"Totems and More"
#define	P2_NPC_5_TEXT 		"Token Converter"
#define	P2_NPC_6_TEXT			"Spectral Tiger"
//PACKAGE 3 GOBJs and NPCs
#define	P3_ITEM_1_TEXT  		"Owl Statue"
#define 	P3_ITEM_2_TEXT  		"Man Statue"
#define	P3_ITEM_3_TEXT 		"Little Flame"
#define	P3_ITEM_4_TEXT 		"Beer Tent"
#define	P3_ITEM_5_TEXT 		"Signalling Gem Aura"
#define	P3_NPC_1_TEXT  		"Arathi Basin"
#define 	P3_NPC_2_TEXT  		"Warsong Gulch"
#define	P3_NPC_3_TEXT 		"Real Steel"
#define	P3_NPC_4_TEXT 		"Eye of the Storm"
#define	P3_NPC_5_TEXT 		"Arena Battlemaster"
#define	P3_NPC_6_TEXT 		"Arena Organizer"
//PACKAGE 4 GOBJs and NPCs
#define	P4_ITEM_1_TEXT  		"Arena Earth Rune"
#define 	P4_ITEM_2_TEXT  		"Gambling Records"
#define	P4_ITEM_3_TEXT 		"Gambling Area"
#define	P4_ITEM_4_TEXT 		"Duel Flag"
#define	P4_ITEM_5_TEXT 		"Stormwind Rug"
#define	P4_NPC_1_TEXT  		"Transmogrification"
#define 	P4_NPC_2_TEXT  		"Commander Steele"
#define	P4_NPC_3_TEXT 		"Irelia"
#define	P4_NPC_4_TEXT 		"Bounty Hunter"
#define	P4_NPC_5_TEXT 		"Bounty Bear"
#define	P4_NPC_6_TEXT 		"Gladiators Gear"
#define	P4_NPC_7_TEXT			"Gladiators Gear"

//gomj cmds
bool spawnGoObject(Player *pPlayer, uint32 itemID);
int getSpawnCount(uint32 plrName);
int getSpawnCountBonus(uint32 plrName);
bool getClosestObjectAndDelete(Player *pPlayer);
bool isPossibleGo(uint32 gobjID);
//char cmds
bool isCharacterInLand(Player *pPlayer);
bool isCharacterLandOwner(Player *pPlayer);
bool hasPackage1(uint32 AccID, uint32 package);
bool summonFriend(Player *pPlayer);
bool teleportToLand(Player *pPlayer);
//npc cmds
bool isPossibleNpc(uint32 npcId);
int getNPCCount(uint32 plrName);
int getNPCCountBonus(uint32 plrName);
bool deleteNPC(Player *pPlayer);
bool spawnNPC(Player *pPlayer, uint32 npcID);
bool isTargetInLand(Player *plrTarget, uint32 ownerName);

float top_x = 0;
float bottom_x;
float left_y = 0;
float right_y;
int mapid;
bool ownsLand = false;

class npc_player_house : public ItemScript
{
public:
    npc_player_house() : ItemScript("npc_player_house") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        uint32 AccID = player->GetGUIDLow();
        player->PlayerTalkClass->ClearMenus();
        if(player->isInCombat()){
            ChatHandler(player->GetSession()).PSendSysMessage("You can not use this item while in combat!");
            return false;
        }

        if(isCharacterLandOwner(player)){
            if(isCharacterInLand(player)){
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn GameObjects", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+500);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn NPCs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+501);
                if(hasPackage1(AccID, 1))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+502);
                if(hasPackage1(AccID, 2))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+503);
                if(hasPackage1(AccID, 3))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
                if(hasPackage1(AccID, 4))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+505);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Delete closest GameObject", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Delete NPC", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Summon Friend!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Summon Party/Raid!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Scale NPC.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Scale Objects.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,"Kick Intruder!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            } else {
                QueryResult result = CharacterDatabase.PQuery("SELECT zone_name FROM player_house_taken WHERE player_guid=%u", player->GetGUIDLow());	
                uint32 house_count = 1;
                if(result)
                {
                    do{
                        Field *fields = result->Fetch();
                        std::string zone_name = fields[0].GetString();
                        if(zone_name == "")
                            zone_name = "First House";
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to " + zone_name, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+800+house_count);
                        house_count++;
                    } while (result->NextRow());
                }
            }
        } else {
            ChatHandler(player->GetSession()).PSendSysMessage("You do not own any land!");
            return false;
        }
        player->PlayerTalkClass->SendGossipMenu(1, item->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Item* item, uint32 sender , uint32 action)
    {
        uint32 AccID = player->GetGUIDLow();
        switch(action){
            //GOBJS
        case GOSSIP_ACTION_INFO_DEF +500: 
            player->PlayerTalkClass->ClearMenus();

            char buffer [50];
            char buffer2 [50];
            sprintf (buffer, "You can spawn %i more items.", GAMEOBJECT_SPAWN_LIMIT + getSpawnCountBonus(player->GetGUIDLow()) - getSpawnCount(player->GetGUIDLow()));

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+100);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+110);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+120);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+130);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+140);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_6_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+150);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_7_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+160);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_8_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+170);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_9_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+180);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_10_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+190);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_11_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+255);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_12_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+256);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_13_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+257);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, ITEM_14_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+258);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+500);
            player->PlayerTalkClass->SendGossipMenu(9000, item->GetGUID());
            break;

            //NPC's
        case GOSSIP_ACTION_INFO_DEF +501: 
            player->PlayerTalkClass->ClearMenus();

            sprintf (buffer, "You can spawn %i more nps.", NPC_SPAWN_LIMIT + getNPCCountBonus(player->GetGUIDLow()) - getNPCCount(player->GetGUIDLow()));

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+200);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+210);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+220);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+230);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+240);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_6_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+250);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_7_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+260);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_8_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+270);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_9_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+280);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_10_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+290);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_11_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+291);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, NPC_12_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+292);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+501);
            player->PlayerTalkClass->SendGossipMenu(9000, item->GetGUID());
            break;
            //spawn package 1
        case GOSSIP_ACTION_INFO_DEF +502:
            player->PlayerTalkClass->ClearMenus();

            sprintf (buffer, "You can spawn %i more nps.", NPC_SPAWN_LIMIT + getNPCCountBonus(player->GetGUIDLow()) - getNPCCount(player->GetGUIDLow()));
            sprintf (buffer2, "You can spawn %i more items.", GAMEOBJECT_SPAWN_LIMIT + getSpawnCountBonus(player->GetGUIDLow()) - getSpawnCount(player->GetGUIDLow()));

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- OBJECTS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+502);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_ITEM_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+300);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_ITEM_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+310);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_ITEM_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+320);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_ITEM_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+330);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_ITEM_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+340);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_ITEM_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+340);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- NPCS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+502);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_NPC_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+350);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_NPC_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+360);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_NPC_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+370);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_NPC_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+380);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P1_NPC_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+390);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+502);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+502);
            player->PlayerTalkClass->SendGossipMenu(9000, item->GetGUID());
            break;
            //spawn package 2
        case GOSSIP_ACTION_INFO_DEF +503:
            player->PlayerTalkClass->ClearMenus();

            sprintf (buffer, "You can spawn %i more nps.", NPC_SPAWN_LIMIT + getNPCCountBonus(player->GetGUIDLow()) - getNPCCount(player->GetGUIDLow()));
            sprintf (buffer2, "You can spawn %i more items.", GAMEOBJECT_SPAWN_LIMIT + getSpawnCountBonus(player->GetGUIDLow()) - getSpawnCount(player->GetGUIDLow()));

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- OBJECTS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+503);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_ITEM_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+400);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_ITEM_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+410);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_ITEM_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+420);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_ITEM_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+430);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_ITEM_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+440);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- NPCS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+503);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_NPC_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+450);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_NPC_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+460);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_NPC_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+470);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_NPC_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+480);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_NPC_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+490);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P2_NPC_6_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1500);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+503);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+503);
            player->PlayerTalkClass->SendGossipMenu(9000, item->GetGUID());
            break;
            //spawn package 3
        case GOSSIP_ACTION_INFO_DEF +504: 
            player->PlayerTalkClass->ClearMenus();

            sprintf (buffer, "You can spawn %i more nps.", NPC_SPAWN_LIMIT + getNPCCountBonus(player->GetGUIDLow()) - getNPCCount(player->GetGUIDLow()));
            sprintf (buffer2, "You can spawn %i more items.", GAMEOBJECT_SPAWN_LIMIT + getSpawnCountBonus(player->GetGUIDLow()) - getSpawnCount(player->GetGUIDLow()));

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- OBJECTS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_ITEM_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+600);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_ITEM_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+610);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_ITEM_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+620);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_ITEM_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+630);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_ITEM_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+640);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- NPCS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_NPC_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+650);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_NPC_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+660);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_NPC_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+670);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_NPC_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+680);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_NPC_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+690);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P3_NPC_6_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+700);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
            player->PlayerTalkClass->SendGossipMenu(9000, item->GetGUID());
            break;
            //spawn package 4
        case GOSSIP_ACTION_INFO_DEF +505: 
            player->PlayerTalkClass->ClearMenus();

            sprintf (buffer, "You can spawn %i more nps.", NPC_SPAWN_LIMIT + getNPCCountBonus(player->GetGUIDLow()) - getNPCCount(player->GetGUIDLow()));
            sprintf (buffer2, "You can spawn %i more items.", GAMEOBJECT_SPAWN_LIMIT + getSpawnCountBonus(player->GetGUIDLow()) - getSpawnCount(player->GetGUIDLow()));

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- OBJECTS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+505);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_ITEM_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+910);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_ITEM_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+920);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_ITEM_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+930);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_ITEM_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+940);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_ITEM_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+950);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "-- NPCS --", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+505);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_1_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+960);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_2_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+970);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_3_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+980);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_4_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+990);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_5_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_6_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1010);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, P4_NPC_7_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1020);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+505);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buffer2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+505);
            player->PlayerTalkClass->SendGossipMenu(9000, item->GetGUID());
            break;
            //main menu 
        case GOSSIP_ACTION_INFO_DEF+999:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn GameObjects", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+500);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn NPCs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+501);
            if(hasPackage1(AccID, 1))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+502);
            if(hasPackage1(AccID, 2))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+503);
            if(hasPackage1(AccID, 3))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
            if(hasPackage1(AccID, 4))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Spawn Package #4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+504);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Delete closest GameObject", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Delete NPC", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Summon Friend!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Summon Party/Raid!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,"Kick Intruder!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            player->PlayerTalkClass->SendGossipMenu(1, item->GetGUID());
            break;

            //delete gobj
        case GOSSIP_ACTION_INFO_DEF +2: getClosestObjectAndDelete(player); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+999); break;
            //delete NPC
        case GOSSIP_ACTION_INFO_DEF +6: deleteNPC(player); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+999); break;

            //teleport to house
        case GOSSIP_ACTION_INFO_DEF +3:  
            player->CLOSE_GOSSIP_MENU();
            teleportToLand(player);
            break;
            //summon friend
        case GOSSIP_ACTION_INFO_DEF +4: summonFriend(player); player->CLOSE_GOSSIP_MENU(); break;
            //kickplr
        case GOSSIP_ACTION_INFO_DEF +7: 
            {
                player->PlayerTalkClass->SendCloseGossip();
                Group* grp = player->GetGroup();
                if(!grp)
                    break;
                GroupReference* grpRef = grp->GetFirstMember();
                if(!grpRef)
                    break;

                for (grpRef; grpRef != NULL; grpRef = grpRef->next())
                {
                    Player* groupMember = grpRef->getSource();
                    ChatHandler(player->GetSession()).PSendSysMessage("Sending summon request to...");
                    if(!groupMember)
                        continue;		
                    else
                        break;

                    if(groupMember == player)
                        break;

                    player->SetSelection(groupMember->GetGUID());
                    player->CastSpell(groupMember, 7720, true);
                    ChatHandler(player->GetSession()).PSendSysMessage("%s", groupMember->GetName());
                }
            }
            break;
        case GOSSIP_ACTION_INFO_DEF +8:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 0.25", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 0.50", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 1.00", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 1.50", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 1.75", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
            player->PlayerTalkClass->SendGossipMenu(1, item->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF +9:
            {
                if(isCharacterInLand(player)){
                    Creature* target = ChatHandler(player).getSelectedCreature();
                    if (!target)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("Please select a valid creature within your land area.");
                        player->PlayerTalkClass->SendCloseGossip(); // Rochet's comment: Why close gossip? Why not return to the menu, so its easier to try again?
                        return false;
                    }

                    target->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.25);
                    target->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 0.25", target->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +10:
            {
                if(isCharacterInLand(player)){
                    Creature* target = ChatHandler(player).getSelectedCreature();
                    if (!target)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("Please select a valid creature within your land area.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    target->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.50);
                    target->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 0.50", target->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +11:
            {
                if(isCharacterInLand(player)){
                    Creature* target = ChatHandler(player).getSelectedCreature();
                    if (!target)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("Please select a valid creature within your land area.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    target->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.00);
                    target->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 1.00", target->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +12:
            {
                if(isCharacterInLand(player)){
                    Creature* target = ChatHandler(player).getSelectedCreature();
                    if (!target)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("Please select a valid creature within your land area.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    target->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.50);
                    target->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 1.50", target->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +13:
            {
                if(isCharacterInLand(player)){
                    Creature* target = ChatHandler(player).getSelectedCreature();
                    if (!target || !target->GetTypeId() == TYPEID_UNIT || !isPossibleNpc(target->GetEntry()))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("Please select a valid creature within your land area.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    target->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.75);
                    target->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 1.75", target->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;

        case GOSSIP_ACTION_INFO_DEF +14:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 0.25", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 0.50", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 1.00", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+17);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 1.50", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+18);
            player->ADD_GOSSIP_ITEM( 10, "Set Scale 1.75", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+19);
            player->PlayerTalkClass->SendGossipMenu(1, item->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF +15:
            {
                if(isCharacterInLand(player)){
                    GameObject* object = ChatHandler(player).GetNearbyGameObject();
                    if (!object || !isPossibleGo(object->GetEntry()))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("No object found. Or the object is not in range of your land.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    object->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.25);
                    object->DestroyForNearbyPlayers();
	             object->UpdateObjectVisibility();
                    object->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 0.25", object->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +16:
            {
                if(isCharacterInLand(player)){
                    GameObject* object = ChatHandler(player).GetNearbyGameObject();
                    if (!object || !isPossibleGo(object->GetEntry()))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("No object found. Or the object is not in range of your land.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    object->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.50);
                    object->DestroyForNearbyPlayers();
	             object->UpdateObjectVisibility();
                    object->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 0.50", object->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +17:
            {
                if(isCharacterInLand(player)){
                    GameObject* object = ChatHandler(player).GetNearbyGameObject();
                    if (!object || !isPossibleGo(object->GetEntry()))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("No object found. Or the object is not in range of your land.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    object->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.00);
                    object->DestroyForNearbyPlayers();
	             object->UpdateObjectVisibility();
                    object->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 1.00", object->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +18:
            {
                if(isCharacterInLand(player)){
                    GameObject* object = ChatHandler(player).GetNearbyGameObject();
                    if (!object || !isPossibleGo(object->GetEntry()))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("No object found. Or the object is not in range of your land.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    object->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.50);
                    object->DestroyForNearbyPlayers();
	             object->UpdateObjectVisibility();
                    object->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 1.50", object->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;
        case GOSSIP_ACTION_INFO_DEF +19:
            {
                if(isCharacterInLand(player)){
                    GameObject* object = ChatHandler(player).GetNearbyGameObject();
                    if (!object || !isPossibleGo(object->GetEntry()))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("No object found. Or the object is not in range of your land.");
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }

                    object->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.75);
                    object->DestroyForNearbyPlayers();
	             object->UpdateObjectVisibility();
                    object->SaveToDB();
                    ChatHandler(player->GetSession()).PSendSysMessage("You have modified %s, and changed the size to: 1.75", object->GetName());
                    player->PlayerTalkClass->SendCloseGossip();

                    return true;
                } else {
                    teleportToLand(player);
                }
            } break;

            //kickplr
        case GOSSIP_ACTION_INFO_DEF +5:  
            {
                player->PlayerTalkClass->SendCloseGossip();
                Player* selPlr = player->GetSelectedPlayer();
                if(!selPlr)
                    break;
                if(selPlr != player){
                    ChatHandler(selPlr->GetSession()).PSendSysMessage("You have been kicked off %s land!", player->GetName());
                    isTargetInLand(selPlr, player->GetGUIDLow());
                }
            }
            break;

            //ADD ITEMS
        case GOSSIP_ACTION_INFO_DEF +100: spawnGoObject(player, ITEM_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +110: spawnGoObject(player, ITEM_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +120: spawnGoObject(player, ITEM_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +130: spawnGoObject(player, ITEM_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +140: spawnGoObject(player, ITEM_5) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +150: spawnGoObject(player, ITEM_6) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +160: spawnGoObject(player, ITEM_7) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +170: spawnGoObject(player, ITEM_8) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +180: spawnGoObject(player, ITEM_9) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +190: spawnGoObject(player, ITEM_10); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +255: spawnGoObject(player, ITEM_11); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +256: spawnGoObject(player, ITEM_12); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +257: spawnGoObject(player, ITEM_13); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
        case GOSSIP_ACTION_INFO_DEF +258: spawnGoObject(player, ITEM_14); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+500); break;
            //ADD NPCS
        case GOSSIP_ACTION_INFO_DEF +200: spawnNPC(player, NPC_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +210: spawnNPC(player, NPC_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +220: spawnNPC(player, NPC_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +230: spawnNPC(player, NPC_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +240: spawnNPC(player, NPC_5) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +250: spawnNPC(player, NPC_6) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +260: spawnNPC(player, NPC_7) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +270: spawnNPC(player, NPC_8) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +280: spawnNPC(player, NPC_9) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +290: spawnNPC(player, NPC_10); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +291: spawnNPC(player, NPC_11); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;
        case GOSSIP_ACTION_INFO_DEF +292: spawnNPC(player, NPC_12); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+501); break;

            //package 1
        case GOSSIP_ACTION_INFO_DEF +300: spawnGoObject(player, P1_ITEM_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +310: spawnGoObject(player, P1_ITEM_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +320: spawnGoObject(player, P1_ITEM_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +330: spawnGoObject(player, P1_ITEM_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +340: spawnGoObject(player, P1_ITEM_5) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +350: spawnNPC(player, P1_NPC_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +360: spawnNPC(player, P1_NPC_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +370: spawnNPC(player, P1_NPC_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +380: spawnNPC(player, P1_NPC_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;
        case GOSSIP_ACTION_INFO_DEF +390: spawnNPC(player, P1_NPC_5); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+502); break;

            //package 2
        case GOSSIP_ACTION_INFO_DEF +400: spawnGoObject(player, P2_ITEM_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +410: spawnGoObject(player, P2_ITEM_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +420: spawnGoObject(player, P2_ITEM_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +430: spawnGoObject(player, P2_ITEM_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +440: spawnGoObject(player, P2_ITEM_5) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +450: spawnNPC(player, P2_NPC_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +460: spawnNPC(player, P2_NPC_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +470: spawnNPC(player, P2_NPC_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +480: spawnNPC(player, P2_NPC_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +490: spawnNPC(player, P2_NPC_5); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;
        case GOSSIP_ACTION_INFO_DEF +1500: spawnNPC(player, P2_NPC_6); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+503); break;

            //package 3
        case GOSSIP_ACTION_INFO_DEF +600: spawnGoObject(player, P3_ITEM_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +610: spawnGoObject(player, P3_ITEM_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +620: spawnGoObject(player, P3_ITEM_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +630: spawnGoObject(player, P3_ITEM_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +640: spawnGoObject(player, P3_ITEM_5) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +650: spawnNPC(player, P3_NPC_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +660: spawnNPC(player, P3_NPC_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +670: spawnNPC(player, P3_NPC_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +680: spawnNPC(player, P3_NPC_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +690: spawnNPC(player, P3_NPC_5); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;
        case GOSSIP_ACTION_INFO_DEF +700: spawnNPC(player, P3_NPC_6); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+504); break;

            //package 4
        case GOSSIP_ACTION_INFO_DEF +910: spawnGoObject(player, P4_ITEM_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +920: spawnGoObject(player, P4_ITEM_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +930: spawnGoObject(player, P4_ITEM_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +940: spawnGoObject(player, P4_ITEM_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +950: spawnGoObject(player, P4_ITEM_5) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +960: spawnNPC(player, P4_NPC_1) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +970: spawnNPC(player, P4_NPC_2) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +980: spawnNPC(player, P4_NPC_3) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +990: spawnNPC(player, P4_NPC_4) ; OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +1000: spawnNPC(player, P4_NPC_5); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +1010: spawnNPC(player, P4_NPC_6); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;
        case GOSSIP_ACTION_INFO_DEF +1020: spawnNPC(player, P4_NPC_7); OnGossipSelect(player, item, item->GetGUID(), GOSSIP_ACTION_INFO_DEF+505); break;

        case GOSSIP_ACTION_INFO_DEF +801: teleportToHouse(player, 1); break;
        case GOSSIP_ACTION_INFO_DEF +802: teleportToHouse(player, 2); break;
        case GOSSIP_ACTION_INFO_DEF +803: teleportToHouse(player, 3); break;
        case GOSSIP_ACTION_INFO_DEF +804: teleportToHouse(player, 4); break;
        case GOSSIP_ACTION_INFO_DEF +805: teleportToHouse(player, 5); break;
        case GOSSIP_ACTION_INFO_DEF +806: teleportToHouse(player, 6); break;
        case GOSSIP_ACTION_INFO_DEF +807: teleportToHouse(player, 7); break;
        case GOSSIP_ACTION_INFO_DEF +808: teleportToHouse(player, 8); break;
        case GOSSIP_ACTION_INFO_DEF +809: teleportToHouse(player, 9); break;
        case GOSSIP_ACTION_INFO_DEF +810: teleportToHouse(player, 10); break;
        }
        return true;
    }

    bool teleportToHouse(Player* player, uint32 selection)
    {
        if(player->isInCombat() || player->GetMap()->IsBattlegroundOrArena() || player->GetMap()->IsDungeon()){ return false; }

        QueryResult result = CharacterDatabase.PQuery("SELECT map_id, spawn_x, spawn_y, spawn_z, spawn_o FROM player_house_taken WHERE player_guid=%u", player->GetGUIDLow());	
        uint32 house_count = 1;
        do{
            if(house_count == selection) 
            {
                Field *fields = result->Fetch();
                player->TeleportTo(fields[0].GetUInt32(),fields[1].GetFloat(),fields[2].GetFloat(),fields[3].GetFloat(),fields[4].GetFloat());
                ChatHandler(player->GetSession()).SendSysMessage("Welcome Home!");
                return true;
            }
            house_count++;
        } while (result->NextRow());

        return false;
    }

};
bool summonFriend(Player *pPlayer)
{
    Player *plrFriend = pPlayer->GetSelectedPlayer();
    if(plrFriend){
        if(plrFriend->isInCombat()){ ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your friend is in combat!"); return false;}
        if(plrFriend->GetMap()->IsBattlegroundOrArena()){ ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your friend is in a battleground!"); return false;}
        if(plrFriend->GetMap()->IsDungeon()){ ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your friend is in a dungeon!"); return false;}
        if(plrFriend->IsBeingTeleported()) { return false; };
        if(plrFriend->isDead()) { return false; };

        if(pPlayer->IsInPartyWith(plrFriend) || pPlayer->IsInRaidWith(plrFriend)){
            pPlayer->CastSpell(plrFriend, 7720, true);
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("Summon request sent!");
            return true;
        } else {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("You must invite this person to your party first!");
        }
    } else {
        try{
            pPlayer->CastSpell(plrFriend, 7720, true);
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("Summon request sent!");
        } catch(...) {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("You must target the person you want to summon! (Invite to party/raid)");
        }

    }
    return false;
}

bool isCharacterInLand(Player *pPlayer)
{
    float playerx = pPlayer->GetPositionX();
    float playery = pPlayer->GetPositionY();
    uint32 mapid_multi = pPlayer->GetMap()->GetId();

    QueryResult result = CharacterDatabase.PQuery("SELECT map_id, bottom_x, top_x, left_y, right_y FROM player_house_taken WHERE player_guid=%u AND map_id=%u", pPlayer->GetGUID(), mapid_multi);	
    if(!result) 
        return false;

    do{
        Field *fields = result->Fetch();
        mapid = fields[0].GetInt32();
        bottom_x = fields[1].GetFloat();
        top_x = fields[2].GetFloat();
        left_y = fields[3].GetFloat();
        right_y = fields[4].GetFloat();

        if(playerx < bottom_x && playerx > top_x && playery < left_y && playery > right_y) { ownsLand = true; return true; }
    } while (result->NextRow());

    return false;
}

bool isTargetInLand(Player *plrTarget, uint32 ownerName)
{
    if(plrTarget)
    {
        float playerx = plrTarget->GetPositionX();
        float playery = plrTarget->GetPositionY();
        uint32 mapid_multi = plrTarget->GetMap()->GetId();

        QueryResult result = CharacterDatabase.PQuery("SELECT map_id, bottom_x, top_x, left_y, right_y FROM player_house_taken WHERE player_guid=%u AND map_id=%u", ownerName, mapid_multi);	
        do{
            Field *fields = result->Fetch();
            mapid = fields[0].GetInt32();
            bottom_x = fields[1].GetFloat();
            top_x = fields[2].GetFloat();
            left_y = fields[3].GetFloat();
            right_y = fields[4].GetFloat();

            if(playerx < bottom_x && playerx > top_x && playery < left_y && playery > right_y)
            {
                if(plrTarget)
                {
                    plrTarget->TeleportTo(534, 5541.770020f, -3783.469971f, 1594.910034f, 2.883010f);
                }
                return true;
            } else {
                ChatHandler(plrTarget->GetSession()).PSendSysMessage("%s is not located on your land!", plrTarget->GetName());
            }

        } while (result->NextRow());
    }
    return false;
}

bool isCharacterLandOwner(Player *pPlayer)
{
    QueryResult result;
    if(!ownsLand){
        result = CharacterDatabase.PQuery("SELECT * FROM player_house_taken WHERE player_guid=%u", pPlayer->GetGUIDLow());	
        if(result)
        {
            ownsLand = true;
        }
    } else {
        result = CharacterDatabase.PQuery("SELECT * FROM player_house_taken WHERE player_guid=%u", pPlayer->GetGUIDLow());
        if(result) { ownsLand = true; } else { ownsLand = false; }
    }
    return ownsLand;
}

bool teleportToLand(Player *pPlayer)
{
    if(pPlayer->isInCombat() || pPlayer->GetMap()->IsBattlegroundOrArena() || pPlayer->GetMap()->IsDungeon()){ return false; }
    QueryResult spawnresult;
    spawnresult = CharacterDatabase.PQuery("SELECT map_id, spawn_x, spawn_y, spawn_z, spawn_o FROM player_house_taken WHERE player_guid=%u", pPlayer->GetGUIDLow());	
    if(spawnresult){
        Field *fields = spawnresult->Fetch();
        pPlayer->TeleportTo(fields[0].GetUInt32(),fields[1].GetFloat(),fields[2].GetFloat(),fields[3].GetFloat(),fields[4].GetFloat());
        ChatHandler(pPlayer->GetSession()).SendSysMessage("Welcome Home!");
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    } else {
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("Could not locate your spawn! Please contact a GM!");
    }
    return false;
}

/*
*****
GAMEOBJECT METHODS
*****
*/

bool isPossibleGo(uint32 gobjID)
{
    QueryResult result;
    result = CharacterDatabase.PQuery("SELECT * FROM player_house_objects where gobjID = %u", gobjID);
    if(result)
        return true;

    return false;
}

bool getClosestObjectAndDelete(Player *pPlayer)
{
    if(getSpawnCount(pPlayer->GetGUIDLow()) < 0 || getSpawnCount(pPlayer->GetGUIDLow() > 500))
    {
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("You land item has been locked, please contact a GM");
        return false;
    }

    if(!isCharacterInLand(pPlayer))
    {
	 teleportToLand(pPlayer);
        return false;
    }

    float distance = 10;
    uint32 count = 0;
    uint32 gameguid, gameentry;
    QueryResult result = WorldDatabase.PQuery("SELECT guid, id, position_x, position_y, position_z, map, "
        "(POW(position_x - '%f', 2) + POW(position_y - '%f', 2) + POW(position_z - '%f', 2)) AS order_ "
        "FROM gameobject WHERE map='%u' AND (POW(position_x - '%f', 2) + POW(position_y - '%f', 2) + POW(position_z - '%f', 2)) <= '%f' ORDER BY order_ LIMIT 1",
        pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),
        pPlayer->GetMapId(),pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),distance*distance);

    if (result)
    {
        Field *fields = result->Fetch();
        gameguid = fields[0].GetUInt32();
        gameentry = fields[1].GetUInt32();
        float x = fields[2].GetFloat();
        float y = fields[3].GetFloat();
        float z = fields[4].GetFloat();
        int mapid = fields[5].GetUInt16();
        ++count;
    }
    if(count == 0){
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("No items found within 10 yards. Try moving closer to your target");
        return true;
    }

    if(!isPossibleGo(gameentry))
    {
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("That object is not able to be deleted. Contact an administrator to get it removed.");
        return false;
    }

    if(gameguid) { 
        GameObject* gObj = NULL;
        gObj = pPlayer->GetMap()->GetGameObject(MAKE_NEW_GUID(gameguid, gameentry, HIGHGUID_GAMEOBJECT));
        if(!gObj)
        {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("Could not find gameobject. Please wait 5-10 seconds to delete a object after you have spawned it.");
            return false;
        }
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("%s was deleted!", gObj->GetName());
        gObj->SetRespawnTime(0);                                 
        gObj->Delete();
        gObj->DeleteFromDB();
        CharacterDatabase.PExecute("UPDATE player_house SET items_spawned = items_spawned - 1 WHERE player_guid=%u", pPlayer->GetGUID());
    }

    return true;
}

bool hasPackage1(uint32 AccID, uint32 package)
{
    QueryResult result = CharacterDatabase.PQuery("SELECT * FROM player_house WHERE package%u = 1 AND player_guid = %u", package, AccID);
    if(result)
        return true;
    return false;
}

bool spawnGoObject(Player *pPlayer, uint32 itemID)
{
    if(isCharacterInLand(pPlayer)){
        if(getSpawnCount(pPlayer->GetGUIDLow() < 0) || getSpawnCount(pPlayer->GetGUIDLow() > 1000))
        {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("You land item has been locked, please contact a GM");
            return false;
        }

        int bonus = getSpawnCountBonus(pPlayer->GetGUIDLow());
        if(getSpawnCount(pPlayer->GetGUIDLow()) < GAMEOBJECT_SPAWN_LIMIT + bonus)
        {
            Map *map = pPlayer->GetMap();
            GameObject* pGameObj = new GameObject;	
            uint32 db_lowGUID = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

            if (!pGameObj->Create(db_lowGUID, itemID, map, 1, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
            {
                delete pGameObj;
                return false;
            }

            pGameObj->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()),pPlayer->GetPhaseMaskForSpawn());
            map->AddToMap(pGameObj);
            sObjectMgr->AddGameobjectToGrid(db_lowGUID, sObjectMgr->GetGOData(db_lowGUID));
            CharacterDatabase.PExecute("UPDATE player_house SET items_spawned = items_spawned + 1 WHERE player_guid=%u", pPlayer->GetGUIDLow());
        } else {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("GameObject spawn limit reached!");
        }
    } else {
        teleportToLand(pPlayer);
    }
    return true;
}

int getSpawnCount(uint32 plrName)
{
    uint32 spawn = 0;
    QueryResult result = CharacterDatabase.PQuery("SELECT items_spawned FROM player_house WHERE player_guid = %u", plrName);
    if(result)
    {
        spawn = (*result)[0].GetUInt32();
        if (spawn <= 0)
            return 0;
    } else {
        return 0;
    }
    return spawn;
}

int getSpawnCountBonus(uint32 plrName)
{
    uint32 spawn = 0;
    QueryResult result = CharacterDatabase.PQuery("SELECT items_bonus FROM player_house WHERE player_guid = %u", plrName);
    if(result)
    {
        spawn = (*result)[0].GetUInt32();
        if (spawn <= 0)
            return 0;
    } else {
        return 0;
    }
    return spawn;
}
/*
-------
END GAMEOBJECT METHODS
-----
*/


/*
-----
ADD NPC METHODS
------
*/

bool isPossibleNpc(uint32 npcId)
{
    QueryResult result;
    result = CharacterDatabase.PQuery("SELECT * FROM player_house_npcs where npcId = %u", npcId);
    if(result)
        return true;

    return false;
}

int getNPCCount(uint32 plrName)
{
    uint32 npc = 0;
    QueryResult result = CharacterDatabase.PQuery("SELECT npcs_spawned FROM player_house WHERE player_guid = %u", plrName);
    if(result)
    {
        npc = (*result)[0].GetUInt32();
        if (npc <= 0)
            return 0;
    } else {
        return 0;
    }
    return npc;
}

int getNPCCountBonus(uint32 plrName)
{
    uint32 npc = 0;
    QueryResult result = CharacterDatabase.PQuery("SELECT npcs_bonus FROM player_house WHERE player_guid = %u", plrName);
    if(result)
    {
        npc = (*result)[0].GetUInt32();
        if (npc <= 0)
            return 0;
    } else {
        return 0;
    }
    return npc;
}

bool spawnNPC(Player *pPlayer, uint32 npcID)
{
    if(isCharacterInLand(pPlayer)){
        if(getNPCCount(pPlayer->GetGUIDLow() < 0) || getNPCCount(pPlayer->GetGUIDLow() > 500))
        {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("You land item has been locked, please contact a GM");
            return false;
        }

        int bonus = getNPCCountBonus(pPlayer->GetGUID());
        if(getNPCCount(pPlayer->GetGUIDLow()) < NPC_SPAWN_LIMIT + bonus)
        {
            float player_x = pPlayer->GetPositionX();
            float player_y = pPlayer->GetPositionY();
            float player_z = pPlayer->GetPositionZ();
            float player_o = pPlayer->GetOrientation();
            uint32 mapid = pPlayer->GetMapId();
            Map *map = pPlayer->GetMap();
            Creature* creature = new Creature;
            if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), map, 1, npcID, 0, 1, player_x, player_y, player_z, player_o)){
                delete creature;
                return false;
            }
            creature->SaveToDB(mapid, (1 << map->GetSpawnMode()), pPlayer->GetPhaseMaskForSpawn());
            uint32 db_guid = creature->GetDBTableGUIDLow();
            if (!creature->LoadCreatureFromDB(db_guid, map)){
                delete creature;
                return false;
            }
            sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));

            CharacterDatabase.PExecute("UPDATE player_house SET npcs_spawned = npcs_spawned + 1 WHERE player_guid=%u", pPlayer->GetGUIDLow());
        } else {
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("NPC spawn limit reached!");
        }
    } else {
        teleportToLand(pPlayer);
    }
    return true;
}

bool deleteNPC(Player *pPlayer)
{
    Creature *creep = pPlayer->GetMap()->GetCreature(pPlayer->GetSelection());
    if(!creep)
        return false;
    if(creep->isPet() || creep->isHunterPet() || creep->IsControlledByPlayer() || creep->isSpiritHealer() || creep->isSummon())
        return false;

    if(getNPCCount(pPlayer->GetGUIDLow()) < 0)
    {
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("You land item has been locked, please contact a GM");
        return false;
    }


    if(!isPossibleNpc(creep->GetEntry()))
    {
        ChatHandler(pPlayer->GetSession()).PSendSysMessage("Your not allowed to delete that creature.");
        return false;
    }

    float playerx = creep->GetPositionX();
    float playery = creep->GetPositionY();
    uint32 mapid_multi = pPlayer->GetMap()->GetId();

    QueryResult result = CharacterDatabase.PQuery("SELECT map_id, bottom_x, top_x, left_y, right_y FROM player_house_taken WHERE player_guid=%u AND map_id=%u", pPlayer->GetGUIDLow(), mapid_multi);	
    do{
        Field *fields = result->Fetch();
        mapid = fields[0].GetInt32();
        bottom_x = fields[1].GetFloat();
        top_x = fields[2].GetFloat();
        left_y = fields[3].GetFloat();
        right_y = fields[4].GetFloat();

        if(playerx < bottom_x && playerx > top_x && playery < left_y && playery > right_y)
        {
            creep->CombatStop();
            creep->DeleteFromDB();
            creep->AddObjectToRemoveList();
            CharacterDatabase.PExecute("UPDATE player_house SET npcs_spawned = npcs_spawned - 1 WHERE player_guid=%u", pPlayer->GetGUIDLow());
            ChatHandler(pPlayer->GetSession()).PSendSysMessage("%s has been deleted!", creep->GetName());
            return true;
        }

    } while (result->NextRow());

    ChatHandler(pPlayer->GetSession()).PSendSysMessage("%s is not located on your land!", creep->GetName());	
    return false;
}

class playerhouse_commandscript : public CommandScript
{
public:
    playerhouse_commandscript() : CommandScript("playerhouse_commandscript") { }

    ChatCommand* GetCommands() const
    {

        static ChatCommand playerhouseCommandTable[] =
        {
            { "add",         SEC_GAMEMASTER,     false, &HandleAddPlayerHouse,                 "", NULL },
            { "fix",         SEC_ADMINISTRATOR,  false, &HandleFixPlayerHouse,                 "", NULL },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "house",          SEC_GAMEMASTER,     false, NULL,            "", playerhouseCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool HandleFixPlayerHouse(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if(player->GetSession()->GetSecurity() == 10)
        {
            CharacterDatabase.PExecute("ALTER TABLE player_house_available DROP id");
            CharacterDatabase.PExecute("ALTER TABLE player_house_available AUTO_INCREMENT = 1");
            CharacterDatabase.PExecute("ALTER TABLE player_house_available ADD id int UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY FIRST");
            handler->PSendSysMessage("Houses are now set in order!");
        } else {
            handler->PSendSysMessage("Only rank 10 people can use this command.");
            return false; }

        return true;
    }

    static bool HandleAddPlayerHouse(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* nameStr = strtok((char*)args, " ");
        if (!nameStr)
            return false;

        char* _price = strtok(NULL, " ");
        uint32 price;

        if (!_price)
            price = 10;
        else
            price = atoi(_price);

        if (!price || price == NULL || price <= 0)
            price = 10;

        //Check to see how many locations are in the DB (10max)
        QueryResult result = CharacterDatabase.PQuery("SELECT * FROM player_house_available");
        if(result){
            if(result->GetRowCount() >= 20)
            {
                handler->PSendSysMessage("You can only have 20 active locations at a time!");
                return true;
            }
        }

        //Cordinates for available house
        float top_x = 0;
        float bottom_x = 0;
        float left_y = 0;
        float right_y = 0;

        //Varibles used throughout code
        Player *player = handler->GetSession()->GetPlayer();
        float player_x = player->GetPositionX();
        float player_y = player->GetPositionY();
        uint32 mapid = player->GetMapId();
        Map *map = player->GetMap();

        //Check to see if you are to close to avliable players land
        result = CharacterDatabase.PQuery("SELECT bottom_x, top_x, left_y, right_y FROM player_house_available WHERE map_id= '%u'", mapid);
        if(result)
        {
            do{
                Field *fields = result->Fetch();
                bottom_x = fields[0].GetFloat() - 40.0;
                top_x = fields[1].GetFloat() + 40.0;
                left_y = fields[2].GetFloat() - 40.0;
                right_y = fields[3].GetFloat() + 40.0;

                if(player_x > bottom_x && player_x < top_x && player_y > left_y && player_y < right_y){
                    handler->PSendSysMessage("You are to close to another players land! Please move further away and try again.");
                    return false;
                }
            } while (result->NextRow());
        }

        //Check to see if occupied land is close to where youre located.
        result = CharacterDatabase.PQuery("SELECT bottom_x, top_x, left_y, right_y FROM player_house_taken WHERE map_id= '%u'", mapid);
        if(result)
        {
            do{
                Field *fields = result->Fetch();
                bottom_x = fields[0].GetFloat() - 40.0;
                top_x = fields[1].GetFloat() + 40.0;
                left_y = fields[2].GetFloat() - 40.0;
                right_y = fields[3].GetFloat() + 40.0;			
                if(player_x > bottom_x && player_x < top_x && player_y > left_y && player_y < right_y){
                    handler->PSendSysMessage("You are to close to another players land! Please move further away and try again.");
                    return false;
                } 
            } while (result->NextRow());
        }

        //Set bottom_x, left_y as highest value
        if((player_x - 23) > (player_x + 23)){
            bottom_x = player_x - 23; top_x = player_x + 23; }
        else{
            bottom_x = player_x + 23; top_x = player_x - 23; }
        if((player_y + 23) > (player_y - 23)) {
            left_y = player_y + 23; right_y = player_y - 23; }
        else{
            left_y = player_y - 23; right_y = player_y + 23; }

        //Spawn creature to assist with purchase of land.
        Creature* creature = new Creature;
        if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), map, player->GetPhaseMaskForSpawn(), 594, 0, 1, player_x+1, player_y+1, player->GetPositionZ(), player->GetOrientation()))
            delete creature;
        creature->SaveToDB(mapid, (1 << map->GetSpawnMode()), player->GetPhaseMaskForSpawn());
        uint32 db_guid = creature->GetDBTableGUIDLow();
        if (!creature->LoadCreatureFromDB(db_guid, map))
            delete creature;
        sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));

        //Insert data into available houses
        CharacterDatabase.PExecute("INSERT INTO player_house_available (zone_name, price, map_id, bottom_x, top_x, left_y, right_y, spawn_x, spawn_y, spawn_z, spawn_o, c_guid) VALUES (\"%s\", %u, %u, %f, %f, %f, %f, %f, %f, %f, %f, %u)",
            nameStr, price, mapid, bottom_x, top_x,
            left_y, right_y, player_x, player_y,
            player->GetPositionZ(), player->GetOrientation(), db_guid);

        handler->PSendSysMessage("Success! %s has been added for %u DP to the database as possible land!", nameStr, price);
        return true;
    }
};

/*
-----
END NPC METHODS
---
*/

void AddSC_npc_player_house()
{
    new npc_player_house();
    new playerhouse_commandscript();
}