/*
* Author: Xees
* FileName: TowerDefense.h
* Description: This file is used for definitions and requirements of the tower defense system
* Version: 2.1
* Status: Needs an Overhaul!
*/
#ifndef TD_HEADER
#define TD_HEADER

#include "ScriptPCH.h"
#include "Config.h"
#include "MapManager.h"
#include "Language.h"
#include "Chat.h"
#include "Object.h"
#include "PoolMgr.h"
#include "GameEventMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/*
* The Script names to register for the system
*/ 
#define TD_SYSTEM_SCRIPT_NAME "custom_towerdefense_script"
#define TD_SYSTEM_PLAYER_HOOKS_SCRIPT_NAME "custom_towerdefense_player_hooks_script"
#define TD_NPC_SCRIPT_NAME "towerdefense_npc"
#define TD_VENDOR_SCRIPT_NAME "towerdefense_vendor"
#define TD_ITEM_SCRIPT_NAME "towerdefense_item"
#define TD_MOB_SCRIPT_NAME "towerdefense_mob"
#define TD_GUARD_SCRIPT_NAME "towerdefense_guard"
#define TD_UPDATER_SCRIPT_NAME "towerdefense_updater"

/*
* Message colors, used to add effects, make text appear clearer.
*/
#define MSG_COLOR_LIGHTRED      "|cffff6060"
#define MSG_COLOR_LIGHTBLUE     "|cff00ccff"
#define MSG_COLOR_BLUE          "|cff0000ff"
#define MSG_COLOR_GREEN         "|cff00ff00"
#define MSG_COLOR_RED           "|cffff0000"
#define MSG_COLOR_GOLD          "|cffffcc00"
#define MSG_COLOR_GREY          "|cff888888"
#define MSG_COLOR_WHITE         "|cffffffff"
#define MSG_COLOR_SUBWHITE      "|cffbbbbbb"
#define MSG_COLOR_MAGENTA       "|cffff00ff"
#define MSG_COLOR_YELLOW        "|cffffff00"
#define MSG_COLOR_CYAN          "|cff00ffff"
#define MSG_COLOR_ORANGE		"|cffff9900"

/*
* The mail system, sending rewards to players, informing them of previous event status.
*/
#define TD_SYSTEM_MSG_MAIL_SUBJECT "The Tower Defense: Rewards!"
#define TD_SYSTEM_MSG_MAIL_BODY_EVENT_UNFINISHED "Due to an unfinished event. We have added %u resources to your account!"
#define TD_SYSTEM_MSG_MAIL_BODY_EVENT_UNFINISHED_FLED "You have lost your Tower Defense event, before you lost, you had %u resources, and was in wave %u."
#define TD_SYSTEM_MSG_MAIL_BODY_EVENT_LOST "You have lost your Tower Defense event, we have added %u resources to your account."
#define TD_SYSTEM_MSG_MAIL_BODY_EVENT_WON "You have completed every wave in the Tower Defense Mini Game, we have added %u resources you collected to your account."
#define TD_SYSTEM_MAIL_TYPE MAIL_STATIONERY_GM

/*
* The system messages, send to the player in mid center of the screen or in his chatbox
*/
#define TD_SYSTEM_MSG_ALREADYRUNNING "The event is already running!"
#define TD_SYSTEM_MSG_CANNOT_USE_OUTSIDE "You cannot use this item outside a running event!"
#define TD_SYSTEM_MSG_CANNOT_START_DUE "You cannot start the event, if you are logging out, or in combat, or in a group!"
#define TD_SYSTEM_MSG_CANNOT_START_ALREADY " There is a player already running the event in your instance!"
#define TD_SYSTEM_MSG_LOGGING_OUT "You cannot do that while logging out!"
#define TD_SYSTEM_MSG_IN_COMBAT "You cannot do that while in combat!"
#define TD_SYSTEM_MSG_IN_DUEL "You cannot do that while in a duel!"
#define TD_SYSTEM_MSG_NO_EVENT_DATA "You have no event data!"
#define TD_SYSTEM_MSG_STARTED_EVENT_EASY "The event has started in Easy mode, you can now build your base, waves only spawn after you are ready."
#define TD_SYSTEM_MSG_STARTED_EVENT_HARD "The event has started in Hard mode, waves will spawn 30 seconds after current wave has ended, guards cost half as much, enemies have more health, and they can harm guards. You have 30 seconds to get ready!"
#define TD_SYSTEM_MSG_STARTED_EVENT_EXTREME "The event has started in Extreme mode, waves will spawn without rest, guards cost twice as much, enemies have twice as much health, and they can harm guards and you, if you die, all resources are lost!"
#define TD_SYSTEM_MSG_QUIT_EVENT "The event has stopped, you have collected %u resources, and stopped at wave %u."
#define TD_SYSTEM_MSG_LOST_EVENT "You have lost the event, you collected %u resources and lost at wave %u."
#define TD_SYSTEM_MSG_WON_EVENT "You have won, you collected a total of %u resources, congratulations!"
#define TD_SYSTEM_MSG_NOT_STARTED "You have not started the event yet!"
#define TD_SYSTEM_MSG_STARTED_ALREADY "You have already started the event!"
#define TD_SYSTEM_MSG_EVENT_DISABLED "You cannot do that because the event is disabled!"
#define TD_SYSTEM_MSG_NO_GM "You cannot do that because you are a game master!"
#define TD_SYSTEM_MSG_LOW_LEVEL "You cannot do that because your level is too low!"
#define TD_SYSTEM_MSG_MORE_WAVES "You need to defend for at least %u more wave(s)."
#define TD_SYSTEM_MSG_MORE_RESOURCES "You still need %u resources to spawn this Tower."
#define TD_SYSTEM_MSG_MORE_RESOURCES_UPG "You still need %u resources to upgrade this Tower."
#define TD_SYSTEM_MSG_UPGRADED_TOWER_FOR "You upgraded %s for %u resources."
#define TD_SYSTEM_MSG_SOLD_TOWER_FOR "You sold %s for %u resources."
#define TD_SYSTEM_MSG_BOUGHT_GUARD "You purchased a %s for %u resources."
#define TD_SYSTEM_MSG_WAVE_RUNNING "You cannot start the next wave, while your current wave is running!"
#define TD_SYSTEM_MSG_WAVE_HAS_STARTED "Wave %u has started!"
#define TD_SYSTEM_MSG_WAVE_HAS_ENDED "Wave %u has ended!"
#define TD_SYSTEM_MSG_WAVE_STARTING_IN "Starting in %u..."
#define TD_SYSTEM_MSG_WAVE_STARTING "%u..."
#define TD_SYSTEM_MSG_HEALTH_REACHED "Your base health is %u.."
#define TD_SYSTEM_MSG_HEALTH_LOWERING "Your base health has been reduced to %u..."
#define TD_SYSTEM_MSG_WAVE_STARTING_GO "Go!"
#define TD_SYSTEM_MSG_HEALTH_LOW "Your base health is getting low!"
#define TD_SYSTEM_MSG_HEALTH_VERYLOW "Your base health is  dangerously low!"
#define TD_SYSTEM_MSG_HEALTH_ALMOSTDEST "Your base is almost destroyed"
#define TD_SYSTEM_MSG_HEALTH_DEST "Your base was completely destroyed!"
#define TD_SYSTEM_MSG_NO_NEARBY_PLATFORM "No nearby platform found!"
#define TD_SYSTEM_MSG_NEARBY_PLATFORM_NOT_EXIST "Nearby platform does not exist!"
#define TD_SYSTEM_MSG_NEARBY_PLATFORM_TOO_FAR "You need to be closer to the platform!"
#define TD_SYSTEM_MSG_NEARBY_GUARD_TOO_CLOSE "You cannot spawn guards this close to each other."
#define TD_SYSTEM_MSG_NEXT_WAVE_STARTS_IN_HARD "Next wave will start in %u seconds."
#define TD_SYSTEM_MSG_NEXT_WAVE_STARTS_IN_EXTREME "Next wave will start in %u minute(s)."
#define TD_SYSTEM_MSG_NOT_SAME_MAP "You are not in the event instance, you have lost!"
#define TD_SYSTEM_MSG_A_BOSS_APPEARED "A %s has appeared!"

/*
* Global Menu Texts
*/
#define TD_TEXT_EXIT "Nevermind."
#define TD_TEXT_GOBACK "<-- Go back"

/*
* The NPC menu texts before starting the event
*/
#define TD_NPC_TEXT_START_EVENT "I would like to play Tower Defense."
#define TD_NPC_TEXT_EVENT_EASY "I want the easy way! [Easy Mode]"
#define TD_NPC_TEXT_EVENT_HARD "Come at me Tower Defense! [Hard Mode]"
#define TD_NPC_TEXT_EVENT_EXTREME "You shall not pass! [Death Mode]"
#define TD_NPC_TEXT_SHOW_RECORDS "Can you show me my records?"
/*
* The Vendor menu texts
*/
#define TD_VENDOR_TEXT_EXCHANGE "Exchange all your resources into tokens!"
#define TD_VENDOR_TEXT_LIST "Purchase an item!"
/*
* The Item menu texts after starting the event
*/
#define TD_ITEM_TEXT_BASE_HEALTH "Base Health: %u."
#define TD_ITEM_TEXT_CURRENT_RESOURCES "Resources: %u."
#define TD_ITEM_TEXT_START_EVENT "Start event."
#define TD_ITEM_TEXT_START_WAVE "Start wave %u."
#define TD_ITEM_TEXT_SPAWN_TOWER_GUARD "Spawn a %s at the nearest block (Cost %u)."
#define TD_ITEM_TEXT_SPAWN_TOWER_MENU "Spawn a Tower."
#define TD_ITEM_TEXT_QUIT_EVENT "Quit the event!"
#define TD_ITEM_TEXT_NO_EVENT_DATA "You need to start the event to use this item!"
/*
* The Guard menu texts
*/
#define TD_GUARD_TEXT_TOWER_NAME "%s."
#define TD_GUARD_TEXT_UNIT_NAME "%s Unit."
#define TD_GUARD_TEXT_CURRENT_RESOURCES "You have %u resources."
#define TD_GUARD_TEXT_UPGRADE_LEVEL_MAX "This unit reached maximum level."
#define TD_GUARD_TEXT_SELL_GUARD "Sell this guard for %u resources."

enum TDEventInstanceMapId
{
    TD_INSTANCE_MAP_ID = 429,
};

enum TDEventPlayerIndex
{
    TD_PLAYER_STAT_GUID,
    TD_PLAYER_STAT_EVENTS_LOST,
    TD_PLAYER_STAT_EVENTS_WON,
    TD_PLAYER_STAT_EVENTS_UNFINISHED,
    TD_PLAYER_STAT_CURRENT_RESOURCES,
    TD_PLAYER_STAT_MAX
};

enum TDEventSpellCastType
{
    TD_CAST_DEFAULT_CAST_TARGET,
    TD_CAST_ON_SPAWN_CAST_SELF,
    TD_CAST_ON_SPAWN_CAST_TARGET,
    TD_CAST_ON_HIT_CAST_SELF,
    TD_CAST_ON_HIT_TARGET_CAST_TARGET,
    TD_CAST_ON_DAMAGE_TAKEN_CAST_TARGET,
    TD_CAST_ON_DAMAGE_DEALT_CAST_TARGET,
    TD_CAST_ON_CREATURE_NEAR_CAST_TARGET,
    TD_CAST_AOE_CAST_TARGET,
};
/*
* used in HandleEventComplete to finish event, and delete data.
* TD_EVENT_COMPLETE_UNFINISHED: Occurs in OnLogout Hook or incase of server crash.
* TD_EVENT_COMPLETE_QUIT: Occurs in player clicks TD_ITEM_MENU_QUIT_EVENT OnGossipSelect in TD_ITEM(); script OnGossipSelect.
* TD_EVENT_COMPLETE_LOST: Occurs in when player base health is reaches zero.
* TD_EVENT_COMPLETE_WON: Occurs when player completes all waves in event while base health is > 0.
*/
enum TDEventCompleteType
{
    TD_EVENT_COMPLETE_UNFINISHED = 1,
    TD_EVENT_COMPLETE_QUIT,
    TD_EVENT_COMPLETE_LOST,
    TD_EVENT_COMPLETE_WON,
};

enum TDEventMenuIcons
{
    TD_ICON_MAIN_MENU       = GOSSIP_ICON_CHAT,
    TD_ICON_START_EVENT	    = GOSSIP_ICON_BATTLE,			
    TD_ICON_BUY_GUARD		= GOSSIP_ICON_MONEY_BAG,		
    TD_ICON_UPGRADE_GUARD	= GOSSIP_ICON_INTERACT_1,		
    TD_ICON_DOT_EVENT		= GOSSIP_ICON_DOT,				
    TD_ICON_DECLINE		    = GOSSIP_ICON_TAXI,
    TD_ICON_CONVERSE        = GOSSIP_ICON_TALK,
    TD_ICON_EXIT			= GOSSIP_ICON_TABARD,			
};

enum TD_NPC_MENUS
{
    TD_NPC_MENU_MAIN	= 1,
    TD_NPC_MENU_START_EVENT,
    TD_NPC_MENU_EVENT_MODE,
    TD_NPC_MENU_SHOW_RECORDS,
    TD_NPC_MENU_EXIT
};

enum TD_VENDOR_MENUS
{
    TD_VENDOR_MENU_MAIN	= 1,
    TD_VENDOR_EXCHANGE,
    TD_VENDOR_LIST,
    TD_VENDOR_MENU_EXIT
};

enum TD_ITEM_MENUS
{
    TD_ITEM_MENU_MAIN	= 1,
    TD_ITEM_MENU_SELECT_EVENT_MODE,
    TD_ITEM_MENU_START_EVENT,
    TD_ITEM_MENU_BASE_HEALTH,
    TD_ITEM_MENU_CURRENT_RESOURCES,
    TD_ITEM_MENU_START_WAVE,
    TD_ITEM_MENU_SPAWN_TOWER_MENU,
    TD_ITEM_MENU_SPAWN_TOWER_GUARD,
    TD_ITEM_MENU_QUIT_EVENT,
    TD_ITEM_MENU_EXIT
};

enum TD_GUARD_MENUS
{
    TD_GUARD_MENU_MAIN	= 1,
    TD_GUARD_MENU_NAME,
    TD_GUARD_MENU_CURRENT_RESOURCES,
    TD_GUARD_MENU_UPGRADE,
    TD_GUARD_MENU_UPGRADE_MAX,
    TD_GUARD_MENU_SELL,
    TD_GUARD_MENU_EXIT
};

enum TDEventUpdateType
{
    TD_EVENT_INC = 1,
    TD_EVENT_DEC
};

enum TDEventFactions
{
    TD_FACTION_GUARD = 1665, // ally to all players, enemy to all monsters
    TD_FACTION_ATTACKER = 14 // enemy to all units
};
/*
* Sounds, Music used in the event
* You can add more: visit http://www.trinitycore.org/f/topic/2849-all-world-of-warcraft-335a-sound-ids-and-how-to-extract-them-and-hear-them/page__hl__+extract%20+sound#entry18329 for Guide to find ids.
* Music tends to overlap, don't use too much too soon.
*/
enum TDEventMusic
{
    TD_STARTEVENT_MUSIC      = 12318, // Occurs on player start event
    TD_ENDEVENT_MUSIC        = 15095, // Occurs when player loses the event
    TD_BASE_LOSING_HEALTH    = 15047, // Occurs when base health is below 30%
    TD_STARTWAVE_MUSIC       = 15880, // Occurs when wave is started
};

enum TDEventStatus
{
    TD_EVENT_STATUS_NONE, // no event data exists.
    TD_EVENT_STATUS_SETUP, // just setting up the event.
    TD_EVENT_STATUS_TELEPORT, // Teleported and is inside the event, and not running a wave.
    TD_EVENT_STATUS_RUNNING, // Teleported and is running a wave.
    TD_EVENT_STATUS_LOADING, // Teleported, is running a wave, and wave is loading
    TD_EVENT_STATUS_LOADED, // Teleported and is running a wave and the wave is loaded.
};

enum TDEventMode
{
    TD_EVENT_MODE_EASY, 
    TD_EVENT_MODE_HARD,
    TD_EVENT_MODE_EXTREME,
};

enum TDEventData
{
    TD_EVENT_DATA_START_WAVE_MODE = 1,
    TD_EVENT_DATA_START_WAVE_TIMER,
    TD_EVENT_DATA_START_MUSIC_TIMER,
};

struct MonsterInfo
{
    MonsterInfo() : Entry(0), WaveId(0), PathId(0), Power(0), Bounty(0), IsRunning(false), IsAirMob(false), Health(0), Dmg(0), AttackDistance(0), AttackSpeed(0),  Speed(0),  SpellId(0) { }

    void LoadBaseStats()
    {
        /*      
               0         1                2                3                4                  5                   6               7
            (`Id`, `creatureName`, `creatureEntry`,  `creatureCost`, `creatureDamage`, `creatureAttackDist`, `creatureAir`, `creatureBounty`,
                  8                 9                10               11                12                 13                    14
            `creaturePower`, `creatureHealth`, `creatureSpeed`, `creatureRunning`, `creatureType`, `creatureAttackSpeed`, `creatureGround`)
        */
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_base_stats WHERE creatureEntry = '%u'", Entry))
        {
            Field* Fields = queryResult->Fetch();
            SetDamage(Fields[4].GetUInt32());        // Set the creature damage
            SetAttackDistance(Fields[5].GetFloat()); // set attack distance
            SetIsAirMob(Fields[6].GetBool());        // set if the creature is an anti air unit or not
            SetBounty(Fields[7].GetUInt32());        // set the creature bounty
            SetPower(Fields[8].GetUInt32());         // set the creature power
            SetHealth(Fields[9].GetUInt32());        // set the maximum health
            SetSpeed(Fields[10].GetFloat());          // set the creature speed
            SetIsRunning(Fields[11].GetBool());      // set if the creature is running on spawn or walking
            SetAttSpeed(Fields[13].GetUInt32());     // set the creatures attack speed
        }else
            sLog->outBasic("TowerDefense: unable to load base stats for creature entry [%u] in the database.", Entry);
    }

    uint32 GetPathById()
    {
        if (QueryResult queryResult = CharacterDatabase.PQuery("SELECT pathId FROM custom_td_waves_data WHERE waveId = '%u' AND creatureEntry = '%u'", WaveId, Entry))
        {
            Field* Fields = queryResult->Fetch();
            return Fields[0].GetUInt32();
        }else
            sLog->outBasic("TowerDefense: unable to load a path id for creature entry: [%u].", Entry);
        return 0;
    }

    Position GetWaypointData(uint32 pointId)
    {
        if (QueryResult queryResult = WorldDatabase.PQuery("SELECT position_x, position_y, position_z, orientation FROM waypoint_data WHERE id = '%u' AND point = '%u'", GetPathId(), pointId))
        {
            Field* Fields = queryResult->Fetch();
            spawnPos.m_positionX = Fields[0].GetFloat();
            spawnPos.m_positionY = Fields[1].GetFloat();
            spawnPos.m_positionZ = Fields[2].GetFloat();
            spawnPos.m_orientation = Fields[3].GetFloat();
        }
        else
            sLog->outBasic("TowerDefense: there is no waypoint data for point id: [%u], for creature entry: [%u] with path id: [%u]", pointId, Entry, GetPathId());
        return spawnPos;
    }

    uint32 GetSpellIdByCastType(TDEventSpellCastType type)
    {
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_base_spells WHERE creatureEntry = '%u'", Entry))
        {
            Field* Fields = queryResult->Fetch();
            switch(type)
            {
            case TD_CAST_DEFAULT_CAST_TARGET:
                return Fields[3].GetUInt32();
                break;
            case TD_CAST_ON_SPAWN_CAST_SELF:
                return Fields[4].GetUInt32();
                break;
            case TD_CAST_ON_SPAWN_CAST_TARGET:
                return Fields[5].GetUInt32();
                break;
            case TD_CAST_ON_HIT_CAST_SELF:
                return Fields[6].GetUInt32();
                break;
            case TD_CAST_ON_HIT_TARGET_CAST_TARGET:
                return Fields[7].GetUInt32();
                break;
            case TD_CAST_ON_DAMAGE_TAKEN_CAST_TARGET:
                return Fields[8].GetUInt32();
                break;
            case TD_CAST_ON_DAMAGE_DEALT_CAST_TARGET:
                return Fields[9].GetUInt32();
                break;
            case TD_CAST_ON_CREATURE_NEAR_CAST_TARGET:
                return Fields[10].GetUInt32();
                break;
            case TD_CAST_AOE_CAST_TARGET:
                return Fields[11].GetUInt32();
                break;
            }
        }
        return 0;
    }

    void Spawn(Creature* spawner)
    {
        LoadBaseStats();
        SetPathId(GetPathById());
        Creature* me = spawner->SummonCreature(Entry, GetWaypointData(1).m_positionX, GetWaypointData(1).m_positionY, GetWaypointData(1).m_positionZ, GetWaypointData(1).m_orientation, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
        if(!me)
            sLog->outBasic("TowerDefense: could not spawn creature entry: [%u], please review your settings.", Entry);

        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC); // not attackable by player
        me->SetDefaultMovementType(IDLE_MOTION_TYPE); // init motion type
        me->setFaction(14); // enemy faction
        me->SetReactState(REACT_PASSIVE); // do not react from attacks
    }

    void SetDamage(uint32 dmg)              { Dmg = dmg;                }
    uint32 GetDamage()                      { return     Dmg;           }

    void SetPathId(uint32 path)             { PathId = path;            }
    uint32 GetPathId()                      { return     PathId;        }

    void SetAttackDistance(float distance)  { AttackDistance = distance;}
    float GetAttackDistance()               { return     AttackDistance;}

    void SetPower(uint32 power)            { Power = power;             }
    uint32 GetPower()                      { return     Power;          }

    void SetHealth(uint32 hp)              { Health = hp;               }
    uint32 GetHealth()                     { return     Health;         }

    void SetAttSpeed(uint32 attspeed)      { AttackSpeed = attspeed;    }
    uint32 GetAttSpeed()                   { return     AttackSpeed;    }

    void SetSpeed(float speed)             { Speed = speed;             }
    float GetSpeed()                       { return     Speed;          }

    void SetBounty(uint32 bounty)          { Bounty = bounty;           }
    uint32 GetBounty()                     { return     Bounty;         }

    void SetDefSpell(uint32 spellId)       { SpellId = spellId;         }
    uint32 GetDefSpell()				   { return     SpellId;        }

    void SetIsRunning(bool isrunning)      { IsRunning = isrunning;     }
    bool GetIsRunning()                    { return     IsRunning;      }

    void SetIsAirMob(bool isAir)           { IsAirMob = isAir;          }
    bool GetIsAirMob()                     { return     IsAirMob;       }

    uint32 Entry; // creature entry id
    uint32 WaveId;
    uint32 PathId;
    uint32 Power; // how much health does player lose if creature reaches end point
    uint32 Bounty; // how much resources that player gains if creature gets killed from guards
    bool IsRunning; // if true, then enemy is running by default, faster than normal walk speed, if this is true, IsAirMob must be false;
    bool IsAirMob; // if true, then enemy is air attacker, so only anti-air guards can attack him, if this is true, IsRunning must be false;
    uint32 Health;
    uint32 Dmg; // current Damage of the creature
    float AttackDistance;
    uint32 AttackSpeed;
    float Speed;
    uint32 SpellId;
    Position spawnPos;
};

struct GuardInfo
{
    GuardInfo() : Guid(0), Entry(0), Level(0), Dmg(0), UpgradeCost(0), IsAntiAir(false), IsAntiGround(false), AttackDistance(0), AttackSpeed(0), X(0), Y(0), Z(0), O(0), SpellId(0) { }

    void InitOnCreate(Creature* me)
    {
        Guid = me->GetGUID();
        SetLevel(0); 
        LoadBaseStats(me); 
    }

    void LoadBaseStats(Creature* me)
    {
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_base_stats WHERE creatureEntry = '%u'", Entry))
        {
            Field* Fields = queryResult->Fetch();
            SetDamage(Fields[4].GetUInt32());
            SetAttackDistance(Fields[5].GetFloat());
            SetIsAntiAir(Fields[6].GetBool());
            me->SetMaxHealth(Fields[9].GetUInt32());
            me->SetHealth(me->GetMaxHealth());
            SetAttSpeed(Fields[13].GetUInt32());
            SetIsAntiGround(Fields[14].GetBool());
            // LoadSpells();
        }else
            sLog->outBasic("TowerDefense: unable to load base stats for guard entry [%u] in the database.", Entry);
    }

    uint32 GetSpellIdByCastType(TDEventSpellCastType type)
    {
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_base_spells WHERE creatureEntry = '%u'", Entry))
        {
            Field* Fields = queryResult->Fetch();
            switch(type)
            {
            case TD_CAST_DEFAULT_CAST_TARGET:
                return Fields[3].GetUInt32();
                break;
            case TD_CAST_ON_SPAWN_CAST_SELF:
                return Fields[4].GetUInt32();
                break;
            case TD_CAST_ON_SPAWN_CAST_TARGET:
                return Fields[5].GetUInt32();
                break;
            case TD_CAST_ON_HIT_CAST_SELF:
                return Fields[6].GetUInt32();
                break;
            case TD_CAST_ON_HIT_TARGET_CAST_TARGET:
                return Fields[7].GetUInt32();
                break;
            case TD_CAST_ON_DAMAGE_TAKEN_CAST_TARGET:
                return Fields[8].GetUInt32();
                break;
            case TD_CAST_ON_DAMAGE_DEALT_CAST_TARGET:
                return Fields[9].GetUInt32();
                break;
            case TD_CAST_ON_CREATURE_NEAR_CAST_TARGET:
                return Fields[10].GetUInt32();
                break;
            case TD_CAST_AOE_CAST_TARGET:
                return Fields[11].GetUInt32();
                break;
            }
        }else
            sLog->outBasic("TowerDefense: unable to load base spell stats for creature entry [%u] in the database.", Entry);
        return 0;
    }

    void Spawn(Player* player)
    {
        Creature* me = player->SummonCreature(Entry, X, Y, Z, O, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
        InitOnCreate(me);
    }

    void SetDamage(uint32 dmg)              { Dmg = dmg;                }
    uint32 GetDamage()                      { return     Dmg;           }

    void SetLevel(uint32 level)             { Level = level;            }
    uint32 GetLevel()                       { return     Level;         }

    void SetAttackDistance(float distance)  { AttackDistance = distance;}
    float GetAttackDistance()               { return     AttackDistance;}

    void SetIsAntiAir(bool AntiAir)         { IsAntiAir = AntiAir;      }
    bool GetIsAntiAir()                     { return     IsAntiAir;     }

    void SetIsAntiGround(bool AntiG)        { IsAntiGround = AntiG;     }
    bool GetIsAntiGround()                  { return     IsAntiGround;  }

    void SetAttSpeed(uint32 attspeed)       { AttackSpeed = attspeed;    }
    uint32 GetAttSpeed()                    { return     AttackSpeed;    }

    void SetDefSpell(uint32 spellId)       { SpellId = spellId;         }
    uint32 GetDefSpell()				   { return     SpellId;        }

    void SetUpgradeCost(uint32 Cost)	    { UpgradeCost = Cost;    }

    uint32 GetUpgradeCost()					
    { 
        uint32 creatureLevel = 1;
        if(GetLevel() > 0) 
            creatureLevel = GetLevel()+1;
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT upgradeCost FROM custom_td_base_levels WHERE creatureEntry = '%u' AND creatureLevel = '%u'", Entry, creatureLevel))
        {
            uint32 newUpgradeCost = queryResult->Fetch()[0].GetUInt32();
            if(newUpgradeCost)
                SetUpgradeCost(newUpgradeCost);
        }
        return UpgradeCost;
    }
    uint32 GetSellPrice(uint32 Level)       { return 8 + (Level * 6);}

    uint64 Guid; 
    uint32 Entry;
    uint32 Level; 
    uint32 Dmg; 
    uint32 UpgradeCost;
    bool IsAntiAir; 
    bool IsAntiGround; 
    float AttackDistance;
    uint32 AttackSpeed;
    float X,Y,Z,O;
    uint32 SpellId;
};

struct WaveInfo
{
    WaveInfo(uint32 id, bool boss) : Id(id), IsBoss(false) { }

    MonsterInfo* AddMonster(uint32 entry)
    {
        MonsterInfo* m = new MonsterInfo();
        m->Entry = entry;
        m->WaveId = Id;
        Data.push_back(m);
        return m;
    }

    uint32 GetNumCreatures()
    {
        return Data.size();
    }

    void Spawn(uint32 spawnId, Creature* spawner)
    {
        Data[spawnId]->Spawn(spawner);
    }

    bool ContainsCreatureOfEntry(uint32 entry)
    {
        for (std::vector<MonsterInfo*>::iterator itr = Data.begin(); itr != Data.end(); ++itr)
            if (entry == (*itr)->Entry)
                return true;
        return false;
    }

    Unit* GetClosestAttacker(Creature* me)
    {
        for (std::vector<MonsterInfo*>::iterator itr = Data.begin(); itr != Data.end(); ++itr){
            Unit* target = me->FindNearestCreature((*itr)->Entry,500,true);
            if(target && ContainsCreatureOfEntry((*itr)->Entry))
                return target;
        }
        return NULL;
    }

    uint32 Id;
    std::vector<MonsterInfo*> Data;
    bool IsBoss;
};

class TowerDefenseInstanceScript : public InstanceMapScript
{
public:
    TowerDefenseInstanceScript() : InstanceMapScript(TD_SYSTEM_SCRIPT_NAME, TD_INSTANCE_MAP_ID) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new TowerDefenseMapInstanceScript(map);
    }

    struct TowerDefenseMapInstanceScript : public InstanceScript
    {
        TowerDefenseMapInstanceScript(InstanceMap* map) : 
            _player(NULL), CountDown(0), _playerGUID(0), _highEventId(0), _spawntimer(0), _eventId(0), _resources(0), _baseHealth(0), _units(0), 
            _currentWave(0), _eventFinished(false), eventStatus(TD_EVENT_STATUS_NONE), eventMode(TD_EVENT_MODE_EASY), InstanceScript(map) { }

        //On creation, NOT load. this happens every time the instance is created by a player going inside.
        virtual void Initialize()
        {
            LoadConfigData(); // Load configuration data from the database, and set variables
            LoadPastEvents(); // Load past event information to reward players in case of crash, or send mail.
            SetupWaves(); 
        }

        virtual void OnPlayerEnter(Player* player) { }  // the player is only set on activating the event, 

        bool IsEncounterInProgress()
        {
            if (GetEventStatus() >= TD_EVENT_STATUS_TELEPORT)
                return true;
            return false;
        }

        /*
        * External Assignment and Retrieval Functions Variables.
        */
        void SetEventId(uint32 eventId)	                        { _eventId = eventId ;                                  }
        uint32 GetEventId()	                                    { return _eventId;	                                    }

        void SetPlayerGUID(uint32 playerGUID)	                { _playerGUID = playerGUID ;	                        }
        uint32 GetPlayerGUID()	                                { return _playerGUID;	                                }

        void SetCurrentWaveId(uint32 waveId)	                { _currentWave = waveId;	                            }
        uint32 GetCurrentWaveId()	                            { return _currentWave;	                                }

        void SetResources(uint32 resources) 	                { _resources = resources;	                            }
        uint32 GetResources() 	                                { return _resources;	                                }

        void SetBaseHealth(uint32 baseHealth) 	                { _baseHealth = baseHealth;	                            }
        uint32 GetBaseHealth() 	                                { return _baseHealth;	                                }

        void SetUnits(uint32 units) 	                        { _units = units;	                                    }
        uint32 GetUnits() 	                                    { return _units;	                                    }

        void SetFinished(bool finished)                         { _eventFinished = finished;                            }
        bool GetFinished()		                                { return _eventFinished;		                        }

        void SetEventDate(std::string eventTime)                { eventDate = eventTime;						        }
        std::string GetEventDate()                              { return eventDate;						                }

        void SetEventStatus(TDEventStatus status)	            { eventStatus = status;			                        }
        uint8 GetEventStatus()	                                { return eventStatus;					                }

        void SetEventMode(TDEventMode mode)	                    { eventMode = mode;										}
        uint8 GetEventMode()	                                { return eventMode;										}

        void UpdateUnits(TDEventUpdateType type, uint32 add)    { _units += type == TD_EVENT_INC ? add : -(int)add;     }
        void UpdateResources(TDEventUpdateType type, uint32 add);
        void UpdateHealth(uint32 add);

        /*
        * External Assignment and Retrieval Functions - Configuration
        */
        void SetPlayer(Player* player)                          { _player = player;                                     }
        Player* GetPlayer()                                     { return _player;                                       }
        bool IsEventDisabled()                                  { return disableEvent;                                  }
        bool IsLoggingEnabled()                                 { return disableFileLog;                                }
        bool IsGmDisabled()                                     { return disableGM;                                     }
        bool IsAwardingFledPlayers()                            { return awardFled;                                     }
        uint32 GetMapId()                                       { return TD_INSTANCE_MAP_ID;                            }
        float GetPSpawnX()                                      { return pSpawnX;                                       }
        float GetPSpawnY()                                      { return pSpawnY;                                       }
        float GetPSpawnZ()                                      { return pSpawnZ;                                       }
        float GetPSpawnO()                                      { return pSpawnO;                                       }
        uint32 GetMinLevelRequired()                            { return minLvl;                                        }
        uint32 GetQuitAfterWave()                               { return quitAfterWave;                                 }
        uint32 GetPlatformEntry()                               { return gobPlatformEntry;                              }
        uint32 GetItemEntry()                                   { return buildItemEntry;                                }
        uint32 GetStartResources()                              { return startResources;                                }

        /*
        * External Assignment and Retrieval - WaveInfo, GuardInfo, MonsterInfo, System
        */
        // WaveInfo
        WaveInfo* GetWaveById(uint32 id)                        { return Waves[id];                                     }
        MonsterInfo* GetMonsterByEntry(uint32 Entry);
        GuardInfo* GetGuardByGuid(uint64 guid);
        bool IsCreatureInWave(uint32 wave, uint32 entry)        { return GetWaveById(wave)->ContainsCreatureOfEntry(entry); }
        void SpawnNextCreature(Creature* spawner);

        // GuardInfo
        uint32 GetGuardResourceCost(uint32 entry);
        float GetGuardAttackDistance(uint64 guid);
        uint32 GetGuardUpgradeCost(uint64 guid);
        uint32 GetGuardSellPrice(uint64 guid);
        uint32 GetGuardSpellByCastType(uint64 guid, TDEventSpellCastType type);
        uint32 GetGuardAttSpeed(uint64 guid);
        uint32 GetGuardDamage(uint64 guid);
        bool GetGuardIsAntiAir(uint64 guid);
        bool GetGuardIsAntiGround(uint64 guid);

        // System
        void LoadConfigData();
        void OnUpdate(uint32 const diff);
        void SetupWaves();
        void StartNextWave(uint32 timer);
        void StartEvent(Player* player, uint32 Action);
        void FinishLogout();
        void RecordLog(const char * str, ...);
        uint32 GetLastPointInPath(uint32 pathId);
        void GetGuardList();
        void SpawnFromGuardList(uint32 action);
        void UpgradeGuardMenu(uint64 guid);
        void UpgradeGuard(uint64 guid);
        void SellGuard(uint64 guid);
        void SpawnGuard(uint32 entry);
        void HandleEventComplete(TDEventCompleteType completeType);
        void AddSimpleMenuItemToPlayer(Player* player, uint32 icon, uint32 sender, uint32 action, const char *Message, ...);
        void SendMessageToPlayer(const char *msgToSend, ...);
        void GetRecords(Player *player);
        uint32 GetSpellIdByUniqueId(uint32 uniqueId);
    private:
        void LoadPastEvents();
        void SetupEventData();
        void SaveEventData();
        void DeleteEventData();
        void UpdatePlayerStats(uint32 playerGUID, TDEventPlayerIndex statIndex, uint32 statIncreaseValue);
        void SendMailToPlayer(Player *player, uint32 playerGUID, const char *mailMessage, ...);
        uint32 GenerateEventId();
    protected:
        EventMap Events;
        Player* _player;
        Map* map;
        InstanceScript* _instance;
        UNORDERED_MAP<uint32, WaveInfo*> Waves;
        UNORDERED_MAP<uint32, MonsterInfo*> Monsters;
        UNORDERED_MAP<uint64, GuardInfo*> Guards;

        // Configuration options
        bool   disableEvent, awardFled, disableGM, disableFileLog;
        uint32 minLvl, startResources, buildItemEntry, quitAfterWave, gobPlatformEntry;
        float pSpawnX, pSpawnY,pSpawnZ,pSpawnO;

        // Variables used by the system.
        uint32 CountDown, _playerGUID, _highEventId, _spawntimer, _eventId, _resources, _baseHealth, _units, _currentWave;
        bool _eventFinished;
        TDEventStatus eventStatus;
        TDEventMode eventMode;
        std::string eventDate;
    };
};

class TowerDefensePlayerScript : PlayerScript
{
public:
    TowerDefensePlayerScript() : PlayerScript(TD_SYSTEM_PLAYER_HOOKS_SCRIPT_NAME) {}

    // Called when a player logs out
    void OnLogout(Player *player);
};

#endif