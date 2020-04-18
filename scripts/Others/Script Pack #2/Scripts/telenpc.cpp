#include "ScriptPCH.h"
#include "ScriptedGossip.h"

class telenpc : public CreatureScript
{
public:
    telenpc() : CreatureScript("telenpc") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Cities and Malls --]"           , GOSSIP_SENDER_MAIN, 5005);
	    if (pPlayer->GetTeam() == ALLIANCE)
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 10, "- Alliance Citys"     , GOSSIP_SENDER_MAIN, 1000);
	    }
	    else // Main Menu for Horde
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 10, "- Horde Citys"        , GOSSIP_SENDER_MAIN, 2000);
	    }
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Neutral Mall"	, GOSSIP_SENDER_MAIN, 17398);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Neutral Cities"              		  , GOSSIP_SENDER_MAIN, 3000);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Global PVP Mall"     , GOSSIP_SENDER_MAIN, 7300);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Global NON-PVP Mall"           , GOSSIP_SENDER_MAIN, 7333);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Global Chill-Zone"		, GOSSIP_SENDER_MAIN, 7444);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Buffs and Heals --]"           , GOSSIP_SENDER_MAIN, 5005);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Buff Me Up"              		  , GOSSIP_SENDER_MAIN, 7500);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Heal Me Up"           , GOSSIP_SENDER_MAIN, 7700);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- PvP Areas --]"           , GOSSIP_SENDER_MAIN, 5005);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Duel Gambling",	GOSSIP_SENDER_MAIN, 5050);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- UnforgivenWoW Arenas"             , GOSSIP_SENDER_MAIN, 7400);
           if(pPlayer->getLevel() == 255)
           {
           pPlayer->ADD_GOSSIP_ITEM( 10, "- UnforgivenWoW Battlemaster's"             , GOSSIP_SENDER_MAIN, 7045);
           }
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "- CUSTOM PVP ZONE"           , GOSSIP_SENDER_MAIN, 7401);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Instances --]"           , GOSSIP_SENDER_MAIN, 5005);
	    if(pPlayer->getLevel() == 255)
	    {
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- High Level Instances"             , GOSSIP_SENDER_MAIN, 83717);
	    }				
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Low Level Instances"              , GOSSIP_SENDER_MAIN, 9030);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Other Locations --]"           , GOSSIP_SENDER_MAIN, 5005);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Hidden Village"           , GOSSIP_SENDER_MAIN, 858585);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Leveling Locations"             	  , GOSSIP_SENDER_MAIN, 7310);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Event Locations"           , GOSSIP_SENDER_MAIN, 7800);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Outland Locations"           		  , GOSSIP_SENDER_MAIN, 3600);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Northrend Locations"           		  , GOSSIP_SENDER_MAIN, 3700);
	    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
	    return true;
    }

    void SendDefaultMenu(Player* pPlayer, Creature* pCreature, uint32 uiAction)
    {
		if (pPlayer->isInCombat())
		{
			pPlayer->PlayerTalkClass->SendCloseGossip();
			pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
			return;
		}
           if (pPlayer->GetMap()->IsBattlegroundOrArena() || pPlayer->GetMapId() == 532)
           {
       	    pPlayer->PlayerTalkClass->SendCloseGossip();
                  pCreature->MonsterSay("You cannot teleport in this instance!", LANG_UNIVERSAL, NULL);
                  return;
	    }

	    switch(uiAction)
	    {
		
	    case 1000: //Alliance Town
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Neutral City Dalaran"         , GOSSIP_SENDER_MAIN, 7398);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Darnassus"                    , GOSSIP_SENDER_MAIN, 1001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Exodar"                       , GOSSIP_SENDER_MAIN, 1005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Ironforge"                    , GOSSIP_SENDER_MAIN, 1010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Stormwind"                    , GOSSIP_SENDER_MAIN, 1015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dungeons ->"                  , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 2000: //Horde Town
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Neutral City Dalaran"         , GOSSIP_SENDER_MAIN, 7398);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Orgrimmar"                    , GOSSIP_SENDER_MAIN, 2001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Silvermoon"                   , GOSSIP_SENDER_MAIN, 2005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Thunder Bluff"                , GOSSIP_SENDER_MAIN, 2010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Undercity"                    , GOSSIP_SENDER_MAIN, 2015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dungeons ->"                  , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 3000: //Neutral Town
		    // Check if player is DK for "Ebon Hold"
		    if(pPlayer->getClass()==6)
			    pPlayer->ADD_GOSSIP_ITEM( 10, "Ebon Hold"                    , GOSSIP_SENDER_MAIN, 3001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Booty Bay"                    , GOSSIP_SENDER_MAIN, 3005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dalaran"                      , GOSSIP_SENDER_MAIN, 3010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Everlook"                     , GOSSIP_SENDER_MAIN, 3015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Gadegetzan"                   , GOSSIP_SENDER_MAIN, 3020);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Mudsprocket"                  , GOSSIP_SENDER_MAIN, 3025);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Ratchet"                      , GOSSIP_SENDER_MAIN, 3030);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Shattrath City"               , GOSSIP_SENDER_MAIN, 3035);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Isle Of Quel'Danas"           , GOSSIP_SENDER_MAIN, 3040);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dungeons ->"                  , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 3600: //Outland Location
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Blade's Edge Mountains"       , GOSSIP_SENDER_MAIN, 3601);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Hellfire Peninsula"           , GOSSIP_SENDER_MAIN, 3605);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Nagrand"                      , GOSSIP_SENDER_MAIN, 3610);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Netherstorm"                  , GOSSIP_SENDER_MAIN, 3615);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Shadowmoon Valley"            , GOSSIP_SENDER_MAIN, 3620);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Terokkar Forest"              , GOSSIP_SENDER_MAIN, 3625);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Zangarmarsh"                  , GOSSIP_SENDER_MAIN, 3630);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dungeons ->"                  , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 3700: //Northrend Location
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Borean Tundra"                , GOSSIP_SENDER_MAIN, 3701);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Crystalsong Forest"           , GOSSIP_SENDER_MAIN, 3705);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dragonblight"                 , GOSSIP_SENDER_MAIN, 3710);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Grizzly Hills"                , GOSSIP_SENDER_MAIN, 3715);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Howling Fjord"                , GOSSIP_SENDER_MAIN, 3720);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Hrothgar's Landing"           , GOSSIP_SENDER_MAIN, 3725);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Icecrown"                     , GOSSIP_SENDER_MAIN, 3730);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Sholazar Basin"               , GOSSIP_SENDER_MAIN, 3735);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "The Storm Peaks"              , GOSSIP_SENDER_MAIN, 3740);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Wintergrasp"                  , GOSSIP_SENDER_MAIN, 3745);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Zul'Drak"                     , GOSSIP_SENDER_MAIN, 3750);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dungeons ->"                  , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 5000: //Dungeons
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Kalimdor ->"                  , GOSSIP_SENDER_MAIN, 5010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Eastern Kingdoms ->"          , GOSSIP_SENDER_MAIN, 5015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Outland ->"                   , GOSSIP_SENDER_MAIN, 5025);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Northrend ->"                 , GOSSIP_SENDER_MAIN, 5030);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 858585: //Dungeons
		    pPlayer->ADD_GOSSIP_ITEM( 10, "I have the patches, teleport me."                   , GOSSIP_SENDER_MAIN, 858586);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(858585,pCreature->GetGUID());
		    break; 

	    case 858586: // hidden village
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    if(pPlayer->GetTeam() == ALLIANCE)
		    {
		    		pPlayer->TeleportTo(169, 3226.250000f, 2992.550049f, 12.592100f, 4.670710f);
		    } else {
		    		pPlayer->TeleportTo(169, 3199.629883f, 2993.989990f, 12.585100f, 4.627510f);
		    }
		    break;

	    case 5005: //Back To Main Menu
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Cities and Malls --]"           , GOSSIP_SENDER_MAIN, 5005);
	    if (pPlayer->GetTeam() == ALLIANCE)
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 10, "- Alliance Citys"     , GOSSIP_SENDER_MAIN, 1000);
	    }
	    else // Main Menu for Horde
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 10, "- Horde Citys"        , GOSSIP_SENDER_MAIN, 2000);
	    }
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Neutral Mall"	, GOSSIP_SENDER_MAIN, 17398);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Neutral Cities"              		  , GOSSIP_SENDER_MAIN, 3000);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Global PVP Mall"     , GOSSIP_SENDER_MAIN, 7300); 
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Global Chill-Zone"		, GOSSIP_SENDER_MAIN, 7444);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Buffs and Heals --]"           , GOSSIP_SENDER_MAIN, 5005);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Buff Me"              		  , GOSSIP_SENDER_MAIN, 7500);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Heal Me"           , GOSSIP_SENDER_MAIN, 7700);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- PvP Areas --]"           , GOSSIP_SENDER_MAIN, 5005);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Duel Gambling",	 GOSSIP_SENDER_MAIN, 5050);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- UnforgivenWoW Arenas"             , GOSSIP_SENDER_MAIN, 7400);
           if(pPlayer->getLevel() == 255)
           {
           pPlayer->ADD_GOSSIP_ITEM( 10, "- UnforgivenWoW Battlemaster's"             , GOSSIP_SENDER_MAIN, 7045);
           }
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "- CUSTOM PVP ZONE"           , GOSSIP_SENDER_MAIN, 7401);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Instances --]"           , GOSSIP_SENDER_MAIN, 5005);
	    if(pPlayer->getLevel() == 255)
	    {
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- High Level Instances"             , GOSSIP_SENDER_MAIN, 83717);
	    }				
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Low Level Instances"             			  , GOSSIP_SENDER_MAIN, 9030);
   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Other Locations --]"           , GOSSIP_SENDER_MAIN, 5005);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Leveling Locations]"             	  , GOSSIP_SENDER_MAIN, 7310);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Event Locations"           , GOSSIP_SENDER_MAIN, 7800);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Outland Locations"           		  , GOSSIP_SENDER_MAIN, 3600);
	    pPlayer->ADD_GOSSIP_ITEM( 10, "- Northrend Locations"           		  , GOSSIP_SENDER_MAIN, 3700);
	    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
	    break;

	    case 5010: //Kalimdor
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Blackfathom Deeps"                , GOSSIP_SENDER_MAIN, 6001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Caverns of Time"                  , GOSSIP_SENDER_MAIN, 6005);
		    //pPlayer->ADD_GOSSIP_ITEM( 10, "Dire Maul"                        , GOSSIP_SENDER_MAIN, 6010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Maraudon"                         , GOSSIP_SENDER_MAIN, 6015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Ragefire Chasm"                   , GOSSIP_SENDER_MAIN, 6020);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Razorfen Downs"                   , GOSSIP_SENDER_MAIN, 6025);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Razorfen Kraul"                   , GOSSIP_SENDER_MAIN, 6030);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Ruins of Ahn'Qiraj"               , GOSSIP_SENDER_MAIN, 6035);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Temple of Ahn'Qiraj"              , GOSSIP_SENDER_MAIN, 6040);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Wailing Caverns"                  , GOSSIP_SENDER_MAIN, 6045);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Zul'Farrak"                       , GOSSIP_SENDER_MAIN, 6050);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Back"                          , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 5015: //Eastern Kingdoms 1
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Blackrock Depths"                 , GOSSIP_SENDER_MAIN, 7001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Blackrock Spire"                  , GOSSIP_SENDER_MAIN, 7005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Blackwing Lair"                   , GOSSIP_SENDER_MAIN, 7010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Deadmines"                        , GOSSIP_SENDER_MAIN, 7015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Gnomeregan"                       , GOSSIP_SENDER_MAIN, 7020);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Isle Of Quel'Danas"               , GOSSIP_SENDER_MAIN, 7025);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Karazhan"                         , GOSSIP_SENDER_MAIN, 7030);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Molten Core"                      , GOSSIP_SENDER_MAIN, 7035);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "More ->"                          , GOSSIP_SENDER_MAIN, 5020);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Back"                          , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 5020: //Eastern Kingdoms 2
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Scarlet Monastery"                , GOSSIP_SENDER_MAIN, 7040);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Shadowfang Keep"                  , GOSSIP_SENDER_MAIN, 7050);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Stratholme"                       , GOSSIP_SENDER_MAIN, 7055);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Sunken Temple"                    , GOSSIP_SENDER_MAIN, 7060);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "The Stockade"                     , GOSSIP_SENDER_MAIN, 7065);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Uldaman"                          , GOSSIP_SENDER_MAIN, 7070);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Zul'Aman"                         , GOSSIP_SENDER_MAIN, 7075);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Zul'Gurub"                        , GOSSIP_SENDER_MAIN, 7080);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Back"                          , GOSSIP_SENDER_MAIN, 5015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                     , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 5025: //Outland	
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Auchindoun"                       , GOSSIP_SENDER_MAIN, 8001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Black Temple"                     , GOSSIP_SENDER_MAIN, 8005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Coilfang Reservoir"               , GOSSIP_SENDER_MAIN, 8010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Gruul's Lair"                     , GOSSIP_SENDER_MAIN, 8015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Hellfire Citadel"                 , GOSSIP_SENDER_MAIN, 8020);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Tempest Keep"                     , GOSSIP_SENDER_MAIN, 8025);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Back"                          , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 5030: //Northrend	
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Ahn'Kahet"                        , GOSSIP_SENDER_MAIN, 9001);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Azjol-Nerub"                      , GOSSIP_SENDER_MAIN, 9005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Drak'Tharon Keep"                 , GOSSIP_SENDER_MAIN, 9010);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Gun'Drak"                         , GOSSIP_SENDER_MAIN, 9015);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Icecrown Citadel"                 , GOSSIP_SENDER_MAIN, 9020);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Naxxramas"                        , GOSSIP_SENDER_MAIN, 9025);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "The Nexus"                        , GOSSIP_SENDER_MAIN, 9035);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "The Obsidian Sanctum"             , GOSSIP_SENDER_MAIN, 9040);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Utgarde Keep"                     , GOSSIP_SENDER_MAIN, 9045);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Utgarde Pinnacle"                 , GOSSIP_SENDER_MAIN, 9050);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Ulduar"                           , GOSSIP_SENDER_MAIN, 9055);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Violet Hold"                      , GOSSIP_SENDER_MAIN, 9060);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Back"                          , GOSSIP_SENDER_MAIN, 5000);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

		    //////////////////////////////////////////////////ALLIANCE///////////////////////////////////////////////////////////////
	    case 1001: // Darnassus
		    //pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
		    break; 

	    case 5050: // Darnassus
		    //pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->m_CheatCooldown = false;
		    pPlayer->m_CheatCastTime = false;
		    pPlayer->m_cheatPower = false;
		    pPlayer->TeleportTo(0, -1162.500122f, 1466.012573f, 54.167900f, 1.956749f);
		    break; 

	    case 7398:
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5746.859863f, 599.575012f, 613.872437f, 0.103674f);
		    break;

	    case 17398:
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -3673.392090f, -4384.723145f, 10.02678f, 3.879712f);
		    break;

	    case 1005: // Exodar
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
		    break; 

	    case 1010: // Ironforge
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
		    break; 

	    case 1015: // Stormwind
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
		    break; 

		    //////////////////////////////////////////////////HORDE///////////////////////////////////////////////////////////////
	    case 2001: // Orgrimmar
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
		    break; 

	    case 2005: // Silvermoon
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
		    break; 

	    case 2010: // Thunder Bluff
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
		    break; 

	    case 2015: // Undercity
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
		    break; 

		    //////////////////////////////////////////////////NEUTRAL///////////////////////////////////////////////////////////////
	    case 3001:// Ebon Hold
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 2353.530029f, -5665.819824f, 426.028015f, 0.596f);
		    break; 

	    case 3005:// Booty Bay
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -14438.2f, 472.22f, 15.32f, 0.65f);
		    break; 

	    case 3010: //Dalaran
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5819.08f, 643.99f, 647.80f, 3.32f);
		    break; 

	    case 3015: //Everlook
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 6724.77f, -4610.68f, 720.78f, 4.78f);
		    break; 

	    case 3020: //Gadgetzan
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -7173.26f, -3785.60f, 8.37f, 6.13f);
		    break; 

	    case 3025: //Mudsprocket
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -4564.79f, -3172.38f, 33.93f, 3.21f);
		    break; 

	    case 3030: //Ratchet
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -956.664f, -3754.71f, 5.33239f, 0.996637f);
		    break; 

	    case 3035:// Shattrath City
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
		    break; 

	    case 3040:// Isle Of Quel'Danas
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 12947.4f, -6893.31f, 5.68398f, 3.09154f);
		    break; 

		    //////////////////////////////////////////////////OUTLAND LOCATION///////////////////////////////////////////////////////////////
	    case 3601:// Blade's Edge Mountains
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 1589.919312f, 6784.039063f, 135.167633f, 0.506582f);
		    break; 

	    case 3605:// Hellfire Peninsula
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -248.0f, 956.0f, 84.362808f, 1.549591f);
		    break; 

	    case 3610: //Nagrand
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -604.137146f, 8436.199219f, 61.776058f, 3.019857f);
		    break; 

	    case 3615: //Netherstorm
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 3386.022217f, 4225.194824f, 123.685989f, 5.153f);
		    break; 

	    case 3620: //Shadowmoon Valley
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -2901.471680f, 3125.052734f, 26.8999f, 4.464991f);
		    break; 

	    case 3625: //Terokkar Forest
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -2000.469971f, 4451.540039f, 8.379014f, 4.464991f);
		    break; 

	    case 7600: //onyxia
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -4678.284180f, -3704.267334f, 46.526546f, 3.779467f);
		    break; 

	    case 3630: //Zangarmarsh
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -225.6577f, 5435.426270f, 21.574932f, 1.533886f);
		    break; 

		    //////////////////////////////////////////////////NORTHREND LOCATION///////////////////////////////////////////////////////////////
	    case 3701:// Borean Tundra
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3256.570068f, 5278.229980f, 40.804588f, 0.246367f);
		    break; 

	    case 3705:// Crystalsong Forest
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5766.373047f, 655.131287f, 160.944641f, 4.135118f);
		    break; 

	    case 3710: //Dragonblight
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 4103.359863f, 264.477997f, 50.501900f, 3.093490f);
		    break; 

	    case 3715: //Grizzly Hills
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 4391.729980f, -3587.919922f, 238.531006f, 3.575260f);
		    break; 

	    case 3720: //Howling Fjord
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 1902.150024f, -4883.910156f, 171.363007f, 3.115370f);
		    break; 

	    case 3725: //Hrothgar's Landing
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 9982.508789f, 1037.768188f, 15.307539f, 5.512708f);
		    break; 

	    case 3730: //Icecrown
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 7253.640137f, 1644.780029f, 433.679901f, 4.834120f);
		    break; 

	    case 3735:// Sholazar Basin
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5572.285156f, 5737.171387f, -75.440643f, 1.514785f);
		    break; 

	    case 3740:// The Storm Peaks
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 6119.275391f, -1015.613464f, 408.683258f, 5.175134f);
		    break; 

	    case 3745:// Wintergrasp
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5212.746582f, 2821.331787f, 409.666840f, 1.840724f);
		    break; 

	    case 3750:// Zul'Drak
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5560.229980f, -3211.659912f, 371.709015f, 5.550550f);
		    break; 

		    //////////////////////////////////////////////////KALIMDOR///////////////////////////////////////////////////////////////
	    case 6001:// Blackfathom Deeps
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 4248.72f, 744.35f, -24.67f, 1.34f);
		    break; 

	    case 6005:// Caverns of Time
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8173.66f, -4746.36f, 33.84f, 4.94f);
		    break; 

	    case 6010:// Dire Maul
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -3960.95f, 1130.64f, 161.05f, 0.0f);
		    break; 

	    case 6015:// Maraudon
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -1431.33f, 2962.34f, 98.23f, 4.74f);
		    break; 

	    case 6020:// Ragefire Chasm
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 1814.47f, -4419.46f, -18.78f, 5.28f);
		    break; 

	    case 6025:// Razorfen Downs
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -4657.88f, -2525.59f, 81.4f, 4.16f);
		    break; 

	    case 6030:// Razorfen Kraul
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -4463.6f, -1664.53f, 82.26f, 0.85f);
		    break; 

	    case 6035:// Ruins of Ahn'Qiraj
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8413.33f, 1501.27f, 29.64f, 2.61f);
		    break; 

	    case 6040:// Temple of Ahn'Qiraj
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8245.837891f, 1983.736206f, 129.071686f, 0.936195f);
		    break; 

	    case 6045:// Wailing Caverns
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -722.53f,-2226.30f,16.94f,2.71f);
		    break; 

	    case 6050:// Zul'Farrak
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -6801.9f, -2890.22f, 8.88f, 6.25f);
		    break; 

		    //////////////////////////////////////////////////EASTERN KINGDOMS///////////////////////////////////////////////////////////////
	    case 7001:// Blackrock Depths
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -7180.57f, -920.04f, 165.49f, 5.02f);
		    break; 

	    case 7005:// Blackrock Spire
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -7526.77f, -1225.64f, 285.73f, 5.31f);
		    break; 

	    case 7010:// Blackwing Lair
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(469, -7672.61f, -1107.21f, 396.65f, 3.75f);
		    break; 

	    case 7015:// Deadmines
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -11208.2f, 1675.92f, 24.57f, 1.48f);
		    break; 

	    case 7020:// Gnomeregan
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -5163.32f, 927.18f, 257.158f, 1.44f);
		    break; 

	    case 7025:// Isle Of Quel'Danas
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 13010.00f, -6907.64f, 9.58f, 4.58f);
		    break; 

	    case 7030:// Karazhan
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -11119.6f, -2011.42f, 47.09f, 0.65f);
		    break; 

	    case 7035:// Molten Core
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(230, 1114.85f, -457.76f, -102.81f, 3.83f);
		    break; 

	    case 7040:// Scarlet Monastery
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 2843.89f,-693.74f,139.32f,5.11f);
		    break; 

	    case 7045:// arena and battlemaster 
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -1734.217041f, 5818.219727f, 148.657898f, 1.233753f);
		    break; 

	    case 7050:// Shadowfang Keep
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -239.54f, 1550.8f, 76.89f, 1.18f);
		    break; 

	    case 7055:// Stratholme
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 3370.76f, -3343.63f, 142.26f, 5.23f);
		    break; 

	    case 7060:// Sunken Temple
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -10346.92f, -3851.90f, -43.41f, 6.09f);
		    break; 

	    case 7065:// The Stockade
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -8766.89f, 844.6f, 88.43f, 0.69f);
		    break; 

	    case 7070:// Uldaman
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -6070.72f, -2955.33f, 209.78f, 0.05f);
		    break; 

	    case 7075:// Zul'Aman
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 6851.09f, -7979.71f, 183.54f, 4.72f);
		    break; 

	    case 7080:// Zul'Gurub
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -11916.4f, -1216.23f, 92.28f, 4.75f);
		    break; 

		    //////////////////////////////////////////////////OUTLAND///////////////////////////////////////////////////////////////
	    case 8001:// Auchindoun
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -3322.92f, 4931.02f, -100.56f, 1.86f);
		    break; 

	    case 8005:// Black Temple
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -3649.1f, 317.33f, 35.19f, 2.97f);
		    break; 

	    case 8010:// Coilfang Reservoir
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 721.08f, 6846.77f, -68.75f, 0.34f);
		    break; 

	    case 8015:// Gruul's Lair
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 3539.01f, 5082.36f, 1.69f, 0.0f);
		    break; 

	    case 8020:// Hellfire Citadel
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -292.71f, 3146.77f, 31.60f, 2.05f);
		    break; 

	    case 8025:// Tempest Keep
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 3087.62f, 1376.27f, 184.8f, 4.63f);
		    break; 

		    //////////////////////////////////////////////////NORTHREND///////////////////////////////////////////////////////////////
	    case 9001:// Ahn'Kahet
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3646.76f, 2045.17f, 1.79f, 4.37f);
		    break; 

	    case 9005:// Azjol-Nerub
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3675.43f, 2169.00f, 35.90f, 2.29f);
		    break; 

	    case 9010:// Drak'Tharon Keep
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 4450.86f, -2045.25f, 162.83f, 0.00f);
		    break; 

	    case 9015:// Gun'Drak
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 6937.54f, -4455.98f, 450.68f, 1.00f);
		    break; 

	    case 9020:// Icecrown Citadel
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 6139.24f, 2233.72f, 510.79f, 3.56f);
		    break; 

	    case 9025:// Naxxramas
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);
		    break; 

	    case 9035:// The Nexus
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3789.95f, 6961.48f, 104.23f, 0.28f);
		    break; 

	    case 9040:// The Obsidian Sanctum
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3625.78f, 280.4f, -120.14f, 3.25f);
		    break; 

	    case 9045:// Ulduar
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 1219.72f, -4865.28f, 41.25f, 0.31f);
		    break; 

	    case 9050:// Utgarde Keep
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 1245.69f, -4856.59f, 216.86f, 3.45f);
		    break; 

	    case 9055:// Utgarde Pinnacle
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 8976.24f, -1281.33f, 1059.01f, 0.58f);
		    break; 

	    case 9060:// Violet Hold
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5679.82f, 486.80f, 652.40f, 4.08f);
		    break; 

		    //////////////////////////////////////////Custom Shit////////////////////////////////////////////////////////
	    case 8500:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 7557.40f, -1523.57f, 159.625f, 0.56f);
		    break; 

	    case 7895:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 1219.719971f, -4865.279785f, 41.247898f, 0.313228f);
		    break;

	    case 7896:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 6936.109863f, -4436.950195f, 450.518005f, 0.709854f);
		    break; 

	    case 7887:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5873.819824, 2110.979980, 636.010986, 3.552300f);
		    break; 

	    case 7890:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5638.250000f, 2075.040039f, 798.055847f, 4.599330f);
		    break;

	    case 7899:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 3584.567627f, 220.361084f, -120.055511f, 5.323672f);
		    break;

	    case 7898: 
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 1602.943726f, -2279.975586f, 13.234350f, 1.043760f);
		    break;

	    case 83717: //Custom Instances
	 	    /*pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Vault of Achavon --]"             , GOSSIP_SENDER_MAIN, 7888);
		    if(pPlayer->HasItemCount(51111, 1))
		    {
	 	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Ruby Sanctum --]"             , GOSSIP_SENDER_MAIN, 7899);
		    }
	 	    if(pPlayer->HasItemCount(18, 1))
	    	    {
	    	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- The Frozen Halls --]"             , GOSSIP_SENDER_MAIN, 7890);
	    	    }*/
	    	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Zombie Deathmatch --]"             , GOSSIP_SENDER_MAIN, 7030);
	    	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Icecrown Citadel --]"             , GOSSIP_SENDER_MAIN, 7887);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Kraken --]"		, GOSSIP_SENDER_MAIN, 7898);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7888:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5439.377441f, 2840.757324f, 420.427917f, 6.254289f);
		    break; 

	    case 7889:// Darkshore Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 3091.059570f, 1414.226929f, 189.859924f, 4.622087f);
		    break; 

	    case 8501:// Ravenholt Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 54.350f, -1505.68f, 173.60f, 5.37f);
		    break; 

	    case 8502:// Zul'Farrak
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -6818.33f, -2891.07f, 8.88f, 6.27f);
		    break; 

	    case 8503:// Black Morass
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8734.3f,-4230.11f, -209.5f, 2.16212f);
		    break; 

	    case 8504:// Battle for Mount Hyjal
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8177.89f, -4181.23f, -167.55f, 1.08f);
		    break; 

	    case 8505:// Hogger
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -10075.34f, 620.201f, 39.264f, 3.38f);
		    break; 

	    case 8506:// Spencer
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -7950.17f, -3824.34f, 29.201f, 1.70f);
		    break; 

	    case 8507:// Gurubashi Arena
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    if (pPlayer->GetTeam() == HORDE)
		    {
		    pPlayer->TeleportTo(0, -13248.423828f, -88.410858f, 19.801987f, 4.653514f);
		    } else {
		    pPlayer->TeleportTo(0, -13547.533203f, 86.088730f, 28.731382f, 3.104744f);
		    }
		    break; 

	    case 8508:// Circle of Wills PVP AREA
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 5795.0820f, 647.654907f, 609.9f, 5.527572f);
		    break; 

	    case 8600: //Custom Instances
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Zul'Farrak"                   , GOSSIP_SENDER_MAIN, 8502);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "The Black Morass"                 , GOSSIP_SENDER_MAIN, 8503);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Battle for Mount Hyjal"       , GOSSIP_SENDER_MAIN, 8504);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 9030: //Custom Instances
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Onyxias Lair - Level 200 DUNGEON --]"                   , GOSSIP_SENDER_MAIN, 91030);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Temple of Ahn'Qiraji - 230 RAID --]"                 , GOSSIP_SENDER_MAIN, 91031);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Shadowfang Keep - Level 90 RAID --]"       , GOSSIP_SENDER_MAIN, 7313);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 91030:// Onyxia's Lair
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -4707.44f, -3726.82f, 54.6723f, 3.8f);
		    break; 

	    case 91031:// TAQ
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8257.52f, 1975.76f, 129.072f, 0.774412f);
		    break; 

	    case 8700: //Custom World Bosses
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Hogger [Nightmare Mode]"      , GOSSIP_SENDER_MAIN, 8505);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Spencer [The Rare Desert Cat]", GOSSIP_SENDER_MAIN, 8506);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Dash [Not Avaliable]"         , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7090: // Alliance Boss Area
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 3172.926758f, -3712.650146f, 123.355141f, 1.0f);
		    break; 

	    case 7100: //Alliance Zones
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Alliance Mall Zone --]"	 	 , GOSSIP_SENDER_MAIN, 7102);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Alliance Start Area --]"  	 , GOSSIP_SENDER_MAIN, 7103);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "GM Office"         				 , GOSSIP_SENDER_MAIN, 7106);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7101: // Global Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -1737.470337f, 3226.648682f, 4.823433f, 5.261298f);
		    break; 

	    case 7102: // Ally Mall Zone
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -8452.386719f, 346.997894f, 120.885796f, 1.0f);
		    break; 

	    case 7103: // Ally Start Area
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 4612.216797f, -3862.060303f, 944.182434f, 1.0f);
		    break; 

	    case 7104: // Ally Boss 255
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 3172.926758f, -3712.650146f, 123.355141f, 1.0f);
		    break; 

	    case 7800: //event areas
		    pPlayer->ADD_GOSSIP_ITEM( 10, "--- Stair Events ---" , GOSSIP_SENDER_MAIN, 7800);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Stair Event  #1"                    , GOSSIP_SENDER_MAIN, 7801);
		    //pPlayer->ADD_GOSSIP_ITEM( 10, "Stair Event  #2"                    , GOSSIP_SENDER_MAIN, 7802);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Stair Event  #2"			 , GOSSIP_SENDER_MAIN, 7883);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Stair Event  #3"			 , GOSSIP_SENDER_MAIN, 7884);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Stair Event  #4"			 , GOSSIP_SENDER_MAIN, 7885);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "--- Rocket Events ---"		, GOSSIP_SENDER_MAIN, 7800);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Rocket Jumping #1"				   , GOSSIP_SENDER_MAIN, 7803);
		    //pPlayer->ADD_GOSSIP_ITEM( 10, "Jumping Ship #2"				   , GOSSIP_SENDER_MAIN, 7804);
 		    pPlayer->ADD_GOSSIP_ITEM( 10, "--- Race Events ---"         , GOSSIP_SENDER_MAIN, 7800);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Kings Race   #1  "         , GOSSIP_SENDER_MAIN, 7805);
            	    pPlayer->ADD_GOSSIP_ITEM( 10, "Kings Race   #2  "         , GOSSIP_SENDER_MAIN, 7806);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Trap Race"			, GOSSIP_SENDER_MAIN, 7809);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "--- Labyrinth Events ---" , GOSSIP_SENDER_MAIN, 7800);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Labyrinth #1"		, GOSSIP_SENDER_MAIN, 7807);
            	    pPlayer->ADD_GOSSIP_ITEM( 10, "Labyrinth #2"                , GOSSIP_SENDER_MAIN, 7808);
		    //pPlayer->ADD_GOSSIP_ITEM( 10, "Kings Maze"			 , GOSSIP_SENDER_MAIN, 7886);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7809: // stair event 3
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(573, 2877.901855f, 978.493103f, -0.000344f, 6.175782f);
		    break;
	    case 7886: // stair event 3
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -7775.63f, 453.462f, 59.4575f, 6.24073f);
		    break;
	    case 7885: // stair event 5
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -9626.16f, -1940.66f, 2.99487f, 5.28172f);
		    break;
	    case 7884: // stair event 4
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -11823.6f, 1328.9f, 0.886994f, 1.34418f);
		    break;
	    case 7883: // stair event 3
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -1123.981567f, 3294.8806f, 0.396286f, 4.527313f);
		    break;
	    case 7801: // Stair of winter
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -6952.728027f, -4878.006348f, 0.715152f, 6.258047f);
		    break; 

	    case 7802: // stair of nexus
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -13190.887695f, 321.519745f, 33.241989f, 4.361507f);
		    break; 

	    case 7803: // ship 1
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(573, -259.244019f, -274.849365f, 0.000014f, 6.222119f);
		    break; 

	    case 7804: // ship 2
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 266.557770f, -4917.015625f, 340.918640f, 1.595938f);
		    break; 

        case 7805: // race event
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pPlayer->TeleportTo(1, -6195.622559f, -3920.397949f, -47.341072f, 0.964574f);
            break;

        case 7806: // race event 2
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pPlayer->TeleportTo(1, -6281.371094f, -4012.339111f, -58.749119f, 6.257368f);
            break;
	   
 	    case 7807: // labyrinth 1
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 2034.619995f, 2019.250000f, 131.414001f, 6.222320f);
		    break;

        case 7808: 
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -5239.00f, -4483.68f, 86.111f, 1.56687f);
		    break;

	   case 7105: // Ally Boss 200
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 334.382446f, 372.605347f, -38.309719f, 1.0f);
		    break; 

	    case 7500: // Buffs
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->AddAura(33077, pPlayer);
		    pPlayer->AddAura(33078, pPlayer);
		    pPlayer->AddAura(33079, pPlayer);
		    pPlayer->AddAura(33080, pPlayer);
		    pPlayer->AddAura(33081, pPlayer);
		    pPlayer->AddAura(33082, pPlayer);
		    pPlayer->AddAura(24705, pPlayer);
		    pPlayer->AddAura(26035, pPlayer);
		    pCreature->MonsterSay("Enjoy your buffs, and remember to vote!", LANG_UNIVERSAL, NULL);
		    break; 

	    case 7700: // Heal
		    if (pPlayer->isInCombat())
		    {
			    pPlayer->PlayerTalkClass->SendCloseGossip();
			    pCreature->MonsterSay("You cannot heal while in combat!", LANG_UNIVERSAL, NULL);
			    return;
		    }

		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pCreature->CastSpell(pPlayer,25840,false);
		    pCreature->MonsterSay("You have been healed, enjoy!", LANG_UNIVERSAL, NULL);
		    break; 

	    case 7106: // GM Office		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Alliance Boss --]",    , GOSSIP_SENDER_MAIN, 7336);
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -1324.612305f, -1245.649780f, 32.123672f, 1.0f);
		    break; 

	    case 7091: // Horde Boss Area
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -10428.820313f, -422.008423f, 44.391155f, 1.0f);
		    break; 

	    case 7200: //Horde Zones
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Global Mall Zone --]"     	 , GOSSIP_SENDER_MAIN, 7201);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Horde Mall Zone --]"	 	 , GOSSIP_SENDER_MAIN, 7202);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Horde Start Area --]"  	 , GOSSIP_SENDER_MAIN, 7203);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Horde Boss 255 --]"     	 , GOSSIP_SENDER_MAIN, 7204);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Jamitos Level 200 Boss --]"    , GOSSIP_SENDER_MAIN, 7205);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "GM Office"         				 , GOSSIP_SENDER_MAIN, 7206);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 10200: //Mall Zones
	   	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Global NON-PVP Mall Zone --]"           , GOSSIP_SENDER_MAIN, 7333);	   
	    	    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Global PVP Mall --]"     , GOSSIP_SENDER_MAIN, 7300); 
	    	    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
	    if (pPlayer->GetTeam() == ALLIANCE)
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Alliance Mall --]"     , GOSSIP_SENDER_MAIN, 7334);

	    }
	    else // Main Menu for Horde
	    {
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Horde Mall --]"        , GOSSIP_SENDER_MAIN, 7335);
	    }
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7334: // alliance Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -8517.669922f, 858.127991f, 109.818031f, 3.810410f);
		    break;

	    case 7335: // horde Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, 1806.040039f, 341.354004f, 70.660301f, 4.696770f);
		    break; 

	    case 7337: // alliance boss
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -8455.450195f, 351.008240f, 120.884453f, 2.255328f);
		    break; 

	    case 7201: // Global Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -8503.130859f, 2022.010010f, 104.751045f, 1.0f);
		    break; 

	    case 7202: // Horde Mall Zone
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 1920.535522f, -4129.774414f, 43.142735f, 1.0f);
		    break; 

	    case 7203: // Horde Start Area
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 5628.600098f, -3012.040039f, 1560.140015f, 6.263550f);
		    break; 

	    case 7204: // Horde Boss 255
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -10428.820313f, -422.008423f, 44.391155f, 1.0f);
		    break; 

	    case 7205: // Horde Boss 200
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 7567.507324f, -2891.146240f, 460.661255f, 1.0f);
		    break; 

	    case 7300: // Global PvP Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -1737.521606f, 3226.710938f, 4.823637f, 5.331281f);
		    break; 

	    case 7333: // Global non-PvP Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -1829.760010f, 5362.194824f, -12.427634f, 2.056173f);
		    break; 

	    case 73111: // Global non-PvP Mall
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(534, 5541.770020f, -3783.469971f, 1594.910034f, 2.883010f);
		    break; 

	    case 9599:
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 3438.350098f, 4582.069824f, 200.225006f, 0.712188f);
		    break;

	    case 7444: // chill zone
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -8053.716309f, -317.802429f, 274.619171f, 4.448732f);
		    break; 

	    case 7310: //Leveling Zones
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Starting Area --]"     		    , GOSSIP_SENDER_MAIN, 73111);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Instances:"                 				, GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Cave of Rage 70-150 --]"     		    , GOSSIP_SENDER_MAIN, 7311);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Lair of the Blackwing 150-255 --]"    , GOSSIP_SENDER_MAIN, 7312);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Seaven Deadly S'ins 150-255 --]"      , GOSSIP_SENDER_MAIN, 7314);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Molten Core 100-200 --]"         		, GOSSIP_SENDER_MAIN, 7315);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "Leveling Roads:"                 			, GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Global: Bladges Edge Road --]"		, GOSSIP_SENDER_MAIN, 9599);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Global: Path of the Damned --]"       , GOSSIP_SENDER_MAIN, 7316);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Alpha: Quick Road 200-255 --]"        , GOSSIP_SENDER_MAIN, 7317);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Omega: Quick Road 200-255 --]"        , GOSSIP_SENDER_MAIN, 7318);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 			, GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7092: // Global Starting Road
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -11665.720703f, -2371.583252f, 0.551880f, 1.0f);
		    break; 

	    case 7311: // Cave of Rage 70-150
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 1814.209961f, -4418.845215f, -18.449379f, 1.0f);
		    break; 

	    case 7312: // Lair of the Blackwing
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(469, -7665.308105f, -1101.903564f, 399.679382f, 1.0f);
		    break; 

	    case 7313: // Shadow of the Keep
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -248.317825f, 1527.978882f, 77.162613f, 1.0f);
		    break; 

	    case 7314: // Seaven Deadly S'ins
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -6820.024414f, -2890.770020f, 8.881053f, 1.0f);
		    break; 

	    case 7315: // Molten Core
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(230, 696.154f, 174.377f, -72.149f, 1.0f);
		    break; 

	    case 7316: // Path of Damned
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, 6654.667969f, -6458.312988f, 29.2593025f, 1.0f);
		    break; 

	    case 7317: // Aplha Quick Road
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 7309.867188f, -887.541931f, 31.559586f, 1.0f);
		    break; 

	    case 7318: // Omega Quick Road
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(0, -1042.877441f, -3551.302246f, 54.977585f, 1.0f);
		    break; 

	    case 7400: //Arenas
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Gurubashi Arena --]"     	 , GOSSIP_SENDER_MAIN, 7401);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Blood Arena --]"	 		 , GOSSIP_SENDER_MAIN, 7402);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Blood Ring --]"  	 		 , GOSSIP_SENDER_MAIN, 7403);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- The Cube --]"     		 , GOSSIP_SENDER_MAIN, 7404);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "[-- The Maul (cheats) --]"    			 , GOSSIP_SENDER_MAIN, 7405);
		    //pPlayer->ADD_GOSSIP_ITEM( 10, "[-- Argent Tournament (Cheats) --]"    	 , GOSSIP_SENDER_MAIN, 7406);
		    pPlayer->ADD_GOSSIP_ITEM( 10, "<- Main Menu"                 , GOSSIP_SENDER_MAIN, 5005);
		    pPlayer->PlayerTalkClass->SendGossipMenu(85000,pCreature->GetGUID());
		    break; 

	    case 7401:// Gurubashi Arena
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    if (pPlayer->GetTeam() == HORDE)
		    {
		    pPlayer->TeleportTo(0, -13248.423828f, -88.410858f, 19.801987f, 4.653514f);
		    } else {
		    pPlayer->TeleportTo(0, -13547.533203f, 86.088730f, 28.731382f, 3.104744f);
		    }
		    break; 

	    case 7406: // Blood Arena
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(571, 8431.112305f, 934.426392f, 544.674438f, 1.558206f);
		    break; 

	    case 7402: // Blood Arena
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(530, -2044.388672f, 6655.308594f, 37.733746f, 1.0f);
		    break; 

	    case 7403: // Blood Ring
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 2177.811523f, -4764.241699f, 67.311165f, 1.0f);
		    break; 

	    case 7404: // The Cube
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, 16227.868164f, 16404.136719f, -44.751499f, 1.0f);
		    break; 

	    case 7405: // The Maul
		    pPlayer->PlayerTalkClass->SendCloseGossip();
		    pPlayer->TeleportTo(1, -3750.512451f, 1098.846294f, 151.969482f, 1.0f);
		    break; 

	    } // end of switch
    } //end of function

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
	    pPlayer->PlayerTalkClass->ClearMenus();
	    if (uiSender == GOSSIP_SENDER_MAIN)
	    SendDefaultMenu(pPlayer, pCreature, uiAction);
	    return true;
    }
};

void AddSC_telenpc()
{
	new telenpc();
}
