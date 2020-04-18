/*
* Author: Xees
* FileName: TowerDefense.h
* Description: This file is used for definitions and requirements of the tower defense system
* Version: 2.1
* Status: Needs an Overhaul!
*/
#include "ScriptPCH.h"
#include "TowerDefense.h"

const char *TowerDefensePlayerStatFields[TD_PLAYER_STAT_MAX] = 
{
    "playerGUID",
    "eventsLost",
    "eventsWon",
    "eventsUnfinished",
    "currentResources",
};

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::LoadConfigData()
{
    QueryResult queryResult = CharacterDatabase.Query("SELECT * FROM custom_td_config");
    if(!queryResult){
        RecordLog("TowerDefense: Unable to load tables required, please check your character database for the necessary tables.");
        return;
    }else{
            Field *Fields = queryResult->Fetch();
            /*
                 0           1         2          3          4          5            6             7                 8               9                10                 11                12
            (`pSpawnX`, `pSpawnY`, `pSpawnZ`, `pSpawnO`, `minLvl`, `awardFled`, `disableGM`, `startResources`, `disableEvent`, `buildItemEntry`, `quitAfterWave`, `disableFileLog`, `gobPlatformEntry`)
            */
            pSpawnX             = Fields[0].GetFloat();
            pSpawnY             = Fields[1].GetFloat();
            pSpawnZ             = Fields[2].GetFloat();
            pSpawnO             = Fields[3].GetFloat();
            minLvl              = Fields[4].GetUInt32();
            awardFled		    = Fields[5].GetBool();
            disableGM		    = Fields[6].GetBool();
            startResources      = Fields[7].GetUInt32();
            disableEvent		= Fields[8].GetBool();
            buildItemEntry      = Fields[9].GetUInt32();
            quitAfterWave       = Fields[10].GetUInt32();
            disableFileLog		= Fields[11].GetBool();
            gobPlatformEntry    = Fields[12].GetUInt32();
    } 

    if(QueryResult IdResult = CharacterDatabase.Query("SELECT MAX(Id) FROM custom_td_events"))
        _highEventId = IdResult->Fetch()[0].GetUInt32();
    else
        _highEventId = 0;
    CountDown = 0;
    RecordLog("TowerDefense: Configuration table was loaded.");
    return;
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::LoadPastEvents()
{
    if(QueryResult queryResult = CharacterDatabase.Query("SELECT * FROM custom_td_events"))
    {
        do
        {
            // If there is a result, then create new event data, and set it.
            if(queryResult)
            {
                Field* pFields = queryResult->Fetch();
                uint32 playerGUID = pFields[1].GetUInt32();
                uint32 currentResources = pFields[3].GetUInt32();
                bool finished = pFields[6].GetBool();

                if(!finished)
                {
                    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_players WHERE playerGUID = '%u'", playerGUID)){
                        UpdatePlayerStats(playerGUID, TD_PLAYER_STAT_EVENTS_UNFINISHED, 1);
                        UpdatePlayerStats(playerGUID, TD_PLAYER_STAT_CURRENT_RESOURCES, currentResources);
                    }
                    else{
                        CharacterDatabase.PExecute("REPLACE INTO custom_td_players (playerGUID, eventsUnfinished, currentResources) values('%u','1','%u');",playerGUID,currentResources);
                        RecordLog("TowerDefense: Inserted stats for Player GUID: [%u], added [%u] resources and 1 unfinished events.", playerGUID,currentResources);
                    }
                    SendMailToPlayer(NULL, playerGUID, TD_SYSTEM_MSG_MAIL_BODY_EVENT_UNFINISHED, currentResources);
                    continue;
                }
            }
        }while(queryResult->NextRow());
        CharacterDatabase.PExecute("DELETE FROM custom_td_events WHERE eventFinished = '0'");
        RecordLog("TowerDefense: All past unfinished events were deleted, and their information was sent to the players.");
    }
    else if(!queryResult)
        RecordLog("TowerDefense: No past events exist!");
}
/*
* This is used to spawn creatures
*/
void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::OnUpdate(uint32 const diff)
{
    if(GetEventStatus() < TD_EVENT_STATUS_RUNNING) // if wave is not running
        return;

    Events.Update(diff);

    Player* player = GetPlayer();
    if(!player)
        return;
    while (uint32 eventId = Events.ExecuteEvent())
    {
        switch (eventId)
        {

        case TD_EVENT_DATA_START_MUSIC_TIMER: // this is just some event music to make it feel alive.
            {
                Events.RescheduleEvent(TD_EVENT_DATA_START_MUSIC_TIMER, 240000); // repeat every 4 min, length of track
            }
            break;
        case TD_EVENT_DATA_START_WAVE_TIMER:
            {
                switch(CountDown)
                {
                case 0:
                    player->PlayDirectSound(TD_STARTWAVE_MUSIC,player);
                    SendMessageToPlayer(TD_SYSTEM_MSG_WAVE_STARTING_IN,3);
                    Events.RescheduleEvent(TD_EVENT_DATA_START_WAVE_TIMER, 1000);
                    ++CountDown;
                    break;

                case 1:
                    SendMessageToPlayer(TD_SYSTEM_MSG_WAVE_STARTING,2);
                    Events.RescheduleEvent(TD_EVENT_DATA_START_WAVE_TIMER, 1000);
                    ++CountDown;
                    break;

                case 2:
                    player->PlayDirectSound(TD_STARTWAVE_MUSIC,player);
                    SendMessageToPlayer(TD_SYSTEM_MSG_WAVE_STARTING,1);
                    Events.CancelEvent(TD_EVENT_DATA_START_WAVE_TIMER);
                    Events.ScheduleEvent(TD_EVENT_DATA_START_WAVE_MODE, 1000);
                    ++CountDown;
                    break;
                }
            }
            break;
        case TD_EVENT_DATA_START_WAVE_MODE:
            {
                CountDown = 0;
                SetEventStatus(TD_EVENT_STATUS_LOADING); // set wave status to running so the boss npc can start spawning
                SendMessageToPlayer(TD_SYSTEM_MSG_WAVE_STARTING_GO);
                Events.CancelEvent(TD_EVENT_DATA_START_WAVE_MODE);
                RecordLog("TowerDefense: Wave Id: [%u] is now running.", GetCurrentWaveId());
            }
            break;
        }
    }
}

/*
* Here, you can arrange mob spawns, add more mobs to the wave, remove mobs, add more waves, remove waves.
*/
void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SetupWaves()
{
    CountDown = 0;
    if(QueryResult waveResult = CharacterDatabase.PQuery("SELECT waveId, isBossWave FROM custom_td_waves"))
    {
        do
        {
            Field *Fields = waveResult->Fetch();
            uint32 waveId = Fields[0].GetUInt32();
            uint32 isBossWave = Fields[1].GetBool();
            WaveInfo* Wave = new WaveInfo(waveId, isBossWave);
            if(QueryResult creatureResult = CharacterDatabase.PQuery("SELECT creatureEntry, creatureAmount, pathId FROM custom_td_waves_data WHERE waveId = '%u' ORDER BY creatureOrder ASC", waveId))
            {
                do
                {
                    Field *Fields = creatureResult->Fetch();
                    uint32 creatureEntry  = Fields[0].GetUInt32();
                    uint32 creatureAmount = Fields[1].GetUInt32();
                    uint32 creaturePath   = Fields[2].GetUInt32();
                    for (uint32 i = 0; i < creatureAmount ; ++i)
                    {
                        MonsterInfo* monster = Wave->AddMonster(creatureEntry);  
                        if (Monsters.find(creatureEntry) == Monsters.end()) 
                            Monsters[creatureEntry] = monster;
                        monster->LoadBaseStats();
                    }
                }while(creatureResult->NextRow());
            }
            Waves[waveId] = Wave;
        }while(waveResult->NextRow());
    }
}
/*
* This occurs when the player clicks on TD_ITEM(); TD_ITEM_MENU_START_WAVE OnGossipSelect, it starts counting.
* wave starting in 3... 2... 1... Wave Started.
* Timer that sends a message to the player every second, decreasing the time till wave is spawned, once it reaches zero. then it sets wave running to true.
*/
void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::StartNextWave(uint32 timer)
{
    uint32 waveId = GetCurrentWaveId();
    SetCurrentWaveId(++waveId);
    SetEventStatus(TD_EVENT_STATUS_RUNNING);
    Events.ScheduleEvent(TD_EVENT_DATA_START_MUSIC_TIMER, 200000); // some music 
    Events.ScheduleEvent(TD_EVENT_DATA_START_WAVE_TIMER, timer); // wave countdown
    RecordLog("TowerDefense: Wave Id: [%u] has been scheduled to run in %u milliseconds.", GetCurrentWaveId(), timer);
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::StartEvent(Player* player, uint32 Action)
{
    if (!player || player->isInCombat() || player->GetSession()->isLogingOut() || player->GetGroup()){
        ChatHandler(player).SendSysMessage(TD_SYSTEM_MSG_CANNOT_START_DUE);
        return;
    }
    if(GetPlayer() && player->GetGUIDLow() != GetPlayer()->GetGUIDLow()){
        ChatHandler(player).SendSysMessage(TD_SYSTEM_MSG_CANNOT_START_ALREADY);
        return;
    }else{
        SetPlayer(player);
    }

    if(!player)
        return;

    player->PlayDirectSound(TD_STARTEVENT_MUSIC,player);
    SetupEventData();
    player->AddItem(34131, 1); // add the spawning item to the player
    player->SaveToDB(); // save the player to the db in case of crash
    player->TeleportTo(GetMapId(), GetPSpawnX(), GetPSpawnY(), GetPSpawnZ(), GetPSpawnO()); // teleport to starting location
    SetEventStatus(TD_EVENT_STATUS_TELEPORT);
    switch(Action)
    {
    case 1051: // Easy
        SetEventMode(TD_EVENT_MODE_EASY);
        SendMessageToPlayer(TD_SYSTEM_MSG_STARTED_EVENT_EASY); 
        // wait for user input to start wave
        break;
    case 1052: // Hard
        SetEventMode(TD_EVENT_MODE_HARD);
        SendMessageToPlayer(TD_SYSTEM_MSG_STARTED_EVENT_HARD);
        StartNextWave(30000); // start wave from the start within 30 seconds
        break;
    case 1053: // Extreme
        SetEventMode(TD_EVENT_MODE_EXTREME);
        SendMessageToPlayer(TD_SYSTEM_MSG_STARTED_EVENT_EXTREME);
        StartNextWave(1000); // start waves right away
        break;
    }
    RecordLog("TowerDefense: Player Name: [%s] has started the tower defense event. With Event Id: [%u]",player->GetName(), GetEventId());
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SpawnNextCreature(Creature* spawner)
{
    WaveInfo* wave = GetWaveById(GetCurrentWaveId());
    if(wave)
        wave->Spawn(GetUnits(), spawner);
    else
        sLog->outBasic("TowerDefense: Wave Id [%u] does not have correct loading data in the db. the core could not load the wave.", GetCurrentWaveId());
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SpawnGuard(uint32 entry)
{
    if (!entry)
        return;
    Player *player = GetPlayer();
    if(!player)
        return;

    GuardInfo* guard = new GuardInfo();
    bool found = false;
    float objectX, objectY, objectZ, objectO;
    uint32 objectLowGUID, objectId;
    uint16 objectMap, objectPhase;
    uint32 objectPool;
    GameEventMgr::ActiveEvents const& activeEventsList = sGameEventMgr->GetActiveEventList();

    std::ostringstream eventFilter;
    eventFilter << " AND (eventEntry IS NULL ";
    bool initString = true;

    for (GameEventMgr::ActiveEvents::const_iterator itr = activeEventsList.begin(); itr != activeEventsList.end(); ++itr)
    {
        if (initString)
        {
            eventFilter  <<  "OR eventEntry IN (" << *itr;
            initString = false;
        }
        else
            eventFilter << ',' << *itr;
    }

    if (!initString)
        eventFilter << "))";
    else
        eventFilter << ')';

    QueryResult queryResult = WorldDatabase.PQuery("SELECT gameobject.guid, id, position_x, position_y, position_z, orientation, map, phaseMask, "
        "(POW(position_x - %f, 2) + POW(position_y - %f, 2) + POW(position_z - %f, 2)) AS order_ FROM gameobject "
        "LEFT OUTER JOIN game_event_gameobject on gameobject.guid = game_event_gameobject.guid WHERE map = '%i' %s ORDER BY order_ ASC LIMIT 10",
        player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(),player->GetMapId(), eventFilter.str().c_str());

    if (!queryResult)
    {  
        SendMessageToPlayer(TD_SYSTEM_MSG_NO_NEARBY_PLATFORM);  // if there were no nearby platforms to place guards.
        return;
    }
    do
    {
        Field* fields = queryResult->Fetch();
        objectLowGUID = fields[0].GetUInt32();
        objectId =      fields[1].GetUInt32();
        objectX =       fields[2].GetFloat();
        objectY =       fields[3].GetFloat();
        objectZ =       fields[4].GetFloat();
        objectO =       fields[5].GetFloat();
        objectMap =   fields[6].GetUInt16();
        objectPhase =   fields[7].GetUInt16();
        objectPool =  sPoolMgr->IsPartOfAPool<GameObject>(objectLowGUID);
        if (!objectPool || sPoolMgr->IsSpawnedObject<GameObject>(objectLowGUID))
            found = true;
    } while (queryResult->NextRow() && !found);

    if (!found)
    {
        SendMessageToPlayer(TD_SYSTEM_MSG_NEARBY_PLATFORM_NOT_EXIST); // no nearby platform found
        return;
    }

    GameObjectTemplate const* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);
    if (!objectInfo)
    {
        SendMessageToPlayer(TD_SYSTEM_MSG_NEARBY_PLATFORM_NOT_EXIST); // nearby platform is not an actual object
        return;
    }
    guard->Entry = entry;
    guard->X = objectX;
    guard->Y = objectY;
    guard->Z = objectZ + 0.5; // depends on size of platform object
    guard->O = objectO;
    if(player->GetDistance(objectX,objectY,objectZ) > 3)
    {
        SendMessageToPlayer(TD_SYSTEM_MSG_NEARBY_PLATFORM_TOO_FAR);
        return;
    }else 
    {
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureEntry FROM custom_td_base_stats WHERE creatureType = 'Guard' ORDER BY Id ASC LIMIT 1"))
        {
            do
            {
                Field *Fields = queryResult->Fetch();
                uint32 creatureEntry = Fields[0].GetUInt32();

                Creature* creature = player->FindNearestCreature(creatureEntry,2,true);
                if(creature){
                    SendMessageToPlayer(TD_SYSTEM_MSG_NEARBY_GUARD_TOO_CLOSE);
                    return;
                }
            }while(queryResult->NextRow());
        }

        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureName, creatureEntry, creatureCost FROM custom_td_base_stats WHERE creatureEntry = '%u'", entry))
        {
            Field *Fields = queryResult->Fetch();
            std::string creatureName = Fields[0].GetString();
            uint32 creatureEntry = Fields[1].GetUInt32();
            uint32 creatureCost = Fields[2].GetUInt32();
            if(GetResources() < creatureCost)
            {
                SendMessageToPlayer(TD_SYSTEM_MSG_MORE_RESOURCES, creatureCost - GetResources());
                return;
            }else
            {
                guard->Spawn(player);
                Guards[guard->Guid] = guard;
                guard->SetDefSpell(guard->GetSpellIdByCastType(TD_CAST_DEFAULT_CAST_TARGET)); // set default spell
                UpdateResources(TD_EVENT_DEC,creatureCost);
                SendMessageToPlayer(TD_SYSTEM_MSG_BOUGHT_GUARD, creatureName.c_str(), creatureCost);
                RecordLog("TowerDefense: Event ID: [%u] has spawned Guard Entry: [%u] for [%u] resources.", GetEventId(), guard->Entry,creatureCost);
            }  
        }
    }
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::UpgradeGuardMenu(uint64 guid)
{
    if(!guid)
        return;
    Player *player = GetPlayer();
    if(!player)
        return;
    uint32 currentLevel = 0;
    uint32 entry = GUID_ENPART(guid);
    std::string upgradeText = "";
    if (Guards.find(guid) != Guards.end())
    {
        GuardInfo* guard = Guards[guid];
        currentLevel = guard->Level;
        uint32 newLevel = currentLevel +1;
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureName, creatureEntry, creatureCost FROM custom_td_base_stats WHERE creatureEntry = '%u'", entry))
        {
            uint32 UpgradeCost = guard->GetUpgradeCost();
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                UpgradeCost = UpgradeCost + (UpgradeCost/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                UpgradeCost = UpgradeCost + (UpgradeCost/2);
                break;
            }
            if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_base_levels WHERE creatureEntry = '%u' AND creatureLevel = '%u'", entry, newLevel))
            {
                Field* Fields = queryResult->Fetch();
                upgradeText = Fields[3].GetString();
                AddSimpleMenuItemToPlayer(player,TD_ICON_UPGRADE_GUARD,TD_GUARD_MENU_UPGRADE, GOSSIP_ACTION_INFO_DEF + 1,upgradeText.c_str(),newLevel,UpgradeCost);
            }else
                AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_GUARD_MENU_UPGRADE, GOSSIP_ACTION_INFO_DEF + 1,TD_GUARD_TEXT_UPGRADE_LEVEL_MAX);
        }
    }
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::UpgradeGuard(uint64 guid)
{
    if(!guid)
        return;
    Player* player = GetPlayer();
    if(!player)
        return;

    Creature* creature = player->GetMap()->GetCreature(guid);
    if(!creature)
        return;
    uint32 currentLevel = 0;
    uint32 entry = GUID_ENPART(guid);
    if (Guards.find(guid) != Guards.end())
    {
        GuardInfo* guard = Guards[guid];
        currentLevel = guard->Level;
        uint32 newLevel = currentLevel +1;
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureName, creatureEntry, creatureCost FROM custom_td_base_stats WHERE creatureEntry = '%u'", entry))
        {   
            uint32 UpgradeCost = guard->GetUpgradeCost();
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                UpgradeCost = UpgradeCost + (UpgradeCost/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                UpgradeCost = UpgradeCost + (UpgradeCost/2);
                break;
            }
            if(GetResources() < UpgradeCost){
                SendMessageToPlayer(TD_SYSTEM_MSG_MORE_RESOURCES_UPG, UpgradeCost - GetResources());
                return;
            }
            if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_base_levels WHERE creatureEntry = '%u' AND creatureLevel = '%u'", entry, newLevel))
            {
                creature->CastSpell(creature, GetSpellIdByUniqueId(4),true); // upgrade level visual
                guard->SetLevel(newLevel);
                UpdateResources(TD_EVENT_DEC,UpgradeCost); // remove resource cost from player
                creature->RemoveAllAuras(); // remove all auras to apply new ones.
                SendMessageToPlayer(TD_SYSTEM_MSG_UPGRADED_TOWER_FOR, creature->GetName(),UpgradeCost);

                Field* Fields = queryResult->Fetch();

                uint32 newDefaultSpell = Fields[4].GetUInt32();
                if(newDefaultSpell)
                    guard->SetDefSpell(newDefaultSpell);

                uint32 newAttackSpeed = Fields[9].GetUInt32();
                if (newAttackSpeed)
                    guard->SetAttSpeed(newAttackSpeed);

                float newAttackDistance = Fields[8].GetFloat();
                if(newAttackDistance)
                    guard->SetAttackDistance(newAttackDistance);

                uint32 newAura = Fields[7].GetUInt32();
                if(newAura)
                    creature->CastSpell(creature,newAura,true);

                uint32 newDisplay = Fields[6].GetUInt32();
                if(newDisplay)
                    creature->SetDisplayId(newDisplay);

                float  newScale = Fields[5].GetFloat();
                if(newScale)
                    creature->SetObjectScale(newScale);

                uint32 newDamage = Fields[10].GetUInt32();
                if (newDamage)
                    guard->SetDamage(newDamage);

                uint32 newIsAntiAir = Fields[11].GetBool();
                if (newIsAntiAir)
                    guard->SetIsAntiAir(newIsAntiAir);

                uint32 newIsAntiGround = Fields[12].GetBool();
                if (newIsAntiGround)
                    guard->SetIsAntiGround(newIsAntiGround);
            }
        }
    } 
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SellGuard(uint64 guid)
{
    if(!guid)
        return;
    Player* player = GetPlayer();
    if(!player)
        return;
    Creature* creature = player->GetMap()->GetCreature(guid);
    if(!creature)
        return;
    uint32 entry = GUID_ENPART(guid);
    if (Guards.find(guid) != Guards.end())
    {
        GuardInfo* guard = Guards[guid];
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureName, creatureEntry, creatureCost FROM custom_td_base_stats WHERE creatureEntry = '%u'", entry))
        {   
            creature->CastSpell(creature, GetSpellIdByUniqueId(5),true);
            uint32 SellPrice = guard->GetSellPrice(guard->GetLevel());
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                SellPrice = SellPrice - (SellPrice/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                SellPrice = SellPrice - (SellPrice/2);
                break;
            }
            UpdateResources(TD_EVENT_INC,SellPrice);
            SendMessageToPlayer(TD_SYSTEM_MSG_SOLD_TOWER_FOR, creature->GetName(),SellPrice);
            creature->DisappearAndDie();
            Guards.erase(guid);
        }
    } 
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardList()
{
    Player* player = GetPlayer();
    if(!player)
        return;
    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureName, creatureEntry, creatureCost FROM custom_td_base_stats WHERE creatureType = 'Guard' ORDER BY Id ASC"))
    {
        do
        {
            Field *Fields = queryResult->Fetch();
            std::string creatureName = Fields[0].GetString();
            uint32 creatureEntry = Fields[1].GetUInt32();
            uint32 creatureCost = Fields[2].GetUInt32();
            AddSimpleMenuItemToPlayer(player,TD_ICON_BUY_GUARD,TD_ITEM_MENU_SPAWN_TOWER_GUARD, GOSSIP_ACTION_INFO_DEF + creatureEntry, TD_ITEM_TEXT_SPAWN_TOWER_GUARD, creatureName.c_str(), creatureCost);
        }while(queryResult->NextRow());
    }
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SpawnFromGuardList(uint32 Action)
{
    Player* player = GetPlayer();
    if(!player || !Action)
        return;
    uint32 Entry = Action - GOSSIP_ACTION_INFO_DEF;
    SpawnGuard(Entry);
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetSpellIdByUniqueId(uint32 uniqueId)
{
    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT spellDefaultCastTarget FROM custom_td_base_spells WHERE uniqueId = '%u'", uniqueId))
    {
        Field* Fields = queryResult->Fetch();
        return Fields[0].GetUInt32();
    }else
        RecordLog("TowerDefense: unable to get system spell by unique Id: [%u]", uniqueId);
    return 0;
}

MonsterInfo* TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetMonsterByEntry(uint32 Entry)
{
    if(!Entry)
        return NULL;
    if (Monsters.find(Entry) != Monsters.end())
    {
        MonsterInfo* monster = Monsters[Entry];
        return monster;
    }else
        RecordLog("No monster data found for entry [%u]", Entry);
    return NULL;
}

GuardInfo* TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardByGuid(uint64 guid)
{
    if(guid){
        if (Guards.find(guid) != Guards.end())
        {
            GuardInfo* guard = Guards[guid];
            return guard;
        }else
            RecordLog("No creature data found for guid [%u]", guid);
    }
    return NULL;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardResourceCost(uint32 entry)
{
    if(!entry)
        return 0;
    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT creatureCost FROM custom_td_base_stats WHERE creatureEntry = '%u'", entry))
    {
        Field* Fields = queryResult->Fetch();
        if(uint32 defCost = Fields[0].GetUInt32()){
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                defCost = defCost + (defCost/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                defCost = defCost + (defCost/2);
                break;
            }
            return defCost;
        }
    }

    return 0;
}

bool TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardIsAntiAir(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard)
            return guard->GetIsAntiAir();
        else
            RecordLog("Could not find GetGuardIsAntiAir by Guard Guid [%u].", guid);
    }
    return 0;
}

bool TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardIsAntiGround(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard)
            return guard->GetIsAntiGround();
        else
            RecordLog("Could not find GetGuardIsAntiGround by Guard Guid [%u].", guid);
    }
    return 0;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardSpellByCastType(uint64 guid, TDEventSpellCastType type)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard)
            return guard->GetSpellIdByCastType(type);
        else
            RecordLog("Could not find GetGuardSpellByCastType by Guard Guid [%u].", guid);
    }
    return 0;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardAttSpeed(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard)
            return guard->GetAttSpeed();
        else
            RecordLog("Could not find GetGuardAttSpeed by Guard Guid [%u].", guid);
    }
    return 0;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardDamage(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard){
            uint32 defDmg = guard->GetDamage();
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                defDmg = defDmg - (defDmg/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                defDmg = defDmg - (defDmg/2);
                break;
            }
            return defDmg;
        }
        else
            RecordLog("Could not find GetGuardDamage by Guard Guid [%u].", guid);
    }
    return 0;
}

float TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardAttackDistance(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard)
            return guard->GetAttackDistance();
        else
            RecordLog("Could not find GetGuardAttackDistance by Guard Guid [%u].", guid);
    }
    return 0;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardUpgradeCost(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard){
            uint32 UpgradeCost =  guard->GetUpgradeCost();
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                UpgradeCost = UpgradeCost + (UpgradeCost/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                UpgradeCost = UpgradeCost + (UpgradeCost/2);
                break;
            }
            return UpgradeCost;
        }
        else
            RecordLog("Could not find GetGuardUpgradeCost by Guard Guid [%u].", guid);
    }
    return 0;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetGuardSellPrice(uint64 guid)
{
    if(guid){
        GuardInfo* guard = GetGuardByGuid(guid);
        if(guard){
            uint32 SellPrice = guard->GetSellPrice(guard->GetLevel());
            switch(GetEventMode())
            {
            case TD_EVENT_MODE_HARD:
                SellPrice = SellPrice - (SellPrice/4);
                break;
            case TD_EVENT_MODE_EXTREME:
                SellPrice = SellPrice - (SellPrice/2);
                break;
            }
            return SellPrice;
        }
        else
            RecordLog("Could not find GetGuardUpgradeCost by Guard Guid [%u].", guid);
    }
    return 0;
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetLastPointInPath(uint32 pathId)
{
    uint32 lastPoint = 0;
    if (QueryResult queryResult = WorldDatabase.PQuery("SELECT MAX(point) FROM waypoint_data WHERE id = '%u'", pathId)){
        lastPoint = queryResult->Fetch()[0].GetUInt32();
        return --lastPoint;
    }else
        RecordLog("TowerDefense: There is no waypoint data for GetLastPointInPath() for path [%u].", pathId);
    return 0;
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::HandleEventComplete(TDEventCompleteType completeType)
{
    Player *player = GetPlayer();
    if(!player)
        return;
    if(!completeType)
        return;

    switch(completeType)
    {
    case TD_EVENT_COMPLETE_UNFINISHED:
        {
            if(IsAwardingFledPlayers()){
                UpdatePlayerStats(GetPlayerGUID(), TD_PLAYER_STAT_CURRENT_RESOURCES, GetResources());
                SendMailToPlayer(NULL, GetPlayerGUID(), TD_SYSTEM_MSG_MAIL_BODY_EVENT_UNFINISHED, GetResources());
                RecordLog("TowerDefense: Player: [%s] has received: [%u] resources due to an unfinished Event Id: [%u].", player->GetName(), GetResources(), GetEventId());
            }else{
                SendMailToPlayer(NULL, GetPlayerGUID(), TD_SYSTEM_MSG_MAIL_BODY_EVENT_UNFINISHED_FLED, GetResources(), GetCurrentWaveId());
                RecordLog("TowerDefense: Player: [%s] was informed that he lost all his unfinished Event Id: [%u] rewards.", player->GetName(), GetResources(), GetEventId());
            }
            UpdatePlayerStats(player->GetGUIDLow(), TD_PLAYER_STAT_EVENTS_UNFINISHED, 1);
        }break;
    case TD_EVENT_COMPLETE_QUIT:
        {
            if(player->GetSession()->isLogingOut()){
                SendMessageToPlayer(TD_SYSTEM_MSG_LOGGING_OUT);
                return;
            }
            if(GetCurrentWaveId() < GetQuitAfterWave()){
                uint32 remaining = GetQuitAfterWave() - GetCurrentWaveId();
                SendMessageToPlayer(TD_SYSTEM_MSG_MORE_WAVES, remaining);
                return;
            }
            SendMessageToPlayer(TD_SYSTEM_MSG_QUIT_EVENT, GetResources(), GetCurrentWaveId());
            UpdatePlayerStats(GetPlayerGUID(), TD_PLAYER_STAT_CURRENT_RESOURCES, GetResources());
            UpdatePlayerStats(player->GetGUIDLow(), TD_PLAYER_STAT_EVENTS_LOST, 1);
            RecordLog("TowerDefense: Player: [%s] has received: [%u] resources after leaving Event Id: [%u].", player->GetName(), GetResources(), GetEventId());
        }break;
    case TD_EVENT_COMPLETE_LOST:
        {
            player->PlayDirectSound(TD_ENDEVENT_MUSIC,_player);
            SendMessageToPlayer(TD_SYSTEM_MSG_LOST_EVENT, GetResources(), GetCurrentWaveId());
            UpdatePlayerStats(player->GetGUIDLow(), TD_PLAYER_STAT_EVENTS_LOST, 1);
            RecordLog("TowerDefense: Player: [%s] was informed that he lost all his Event Id: [%u] rewards.", player->GetName(), GetResources(), GetEventId());
        }break;
    case TD_EVENT_COMPLETE_WON:
        {
            SendMessageToPlayer(TD_SYSTEM_MSG_WON_EVENT, GetResources());
            UpdatePlayerStats(GetPlayerGUID(), TD_PLAYER_STAT_CURRENT_RESOURCES, GetResources());
            UpdatePlayerStats(player->GetGUIDLow(), TD_PLAYER_STAT_EVENTS_WON, 1);
            RecordLog("TowerDefense: Player: [%s] has won [%u] resources after completing Event Id: [%u].", player->GetName(), GetResources(), GetEventId());
        }break;
    }
    player->DestroyItemCount(GetItemEntry(),1,true); // destroy the item from the player
    player->TeleportTo(1, -3673.392090, -4384.723145, 10.026433,  3.879712); // Teleport to a Neutral Mall
    player->RemoveAllAuras(); // remove all auras set by event
    player->RemoveAllAttackers(); // remove all attackers
    SetFinished(true); // finish the event
    SaveEventData(); // save event information
    RecordLog("TowerDefense: Player: [%s] has completed Event Id: [%u] and his event data was saved and he was teleported.", player->GetName(), GetEventId());
    DeleteEventData();
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::UpdateHealth(uint32 remove)
{
    if(!remove)
        return;

    Player *player = GetPlayer();
    if(!player)
        return;

    uint32 currentHealth = GetBaseHealth();
    if(remove > currentHealth){
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_DEST); // the removal from the base health is larger than the base health. the player's event ends.
        player->PlayDirectSound(TD_ENDEVENT_MUSIC,player); // play ending music
        player->GetSession()->SendNotification("The Tower defense game has finished. You lost!");
        HandleEventComplete(TD_EVENT_COMPLETE_LOST); // Complete the event data using the lost type
        RecordLog("TowerDefense: Player Name: [%s] has lost the tower defense event. With Event Id: [%u]",player->GetName(), GetEventId()); // record a log to the server log if enabled.
        return;
    }else {
        currentHealth -= remove;  // decrement current health
        SetBaseHealth(currentHealth);
        RecordLog("TowerDefense: Updated health for Event Id: [%u] to [%u].", GetEventId(), currentHealth);
    }

    switch(currentHealth)
    {
    case 90:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_REACHED, 90);
        break;
    case 80:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_LOWERING, 80);
        break;
    case 70:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_REACHED, 70);
        break;
    case 60:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_LOWERING, 60);
        break;
    case 50:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_REACHED, 50);
        break;
    case 40:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_LOW);
        player->CastSpell(player,GetSpellIdByUniqueId(3),true);
        player->PlayDirectSound(TD_ENDEVENT_MUSIC,player);
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_REACHED, 40);
        break;
    case 25:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_VERYLOW);
        player->CastSpell(player,GetSpellIdByUniqueId(2),true);
        player->PlayDirectSound(TD_BASE_LOSING_HEALTH,_player);
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_LOWERING, 25);
        break;
    case 10:
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_REACHED, 10);
        SendMessageToPlayer(TD_SYSTEM_MSG_HEALTH_ALMOSTDEST);
        break;
    }
    return;
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::UpdateResources(TDEventUpdateType type, uint32 add)
{
    if(!type || !add)
        return;

    Player *player = GetPlayer();
    if(!player)
        return;

    uint32 currentRes = GetResources();
    uint32 newRes = 0;
    if(type == TD_EVENT_INC){
        newRes = currentRes + add;
    }else{
        newRes = currentRes - add;
    }
    SetResources(newRes);
    RecordLog("TowerDefense: New resources were set: it is now %u.", newRes);
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::AddSimpleMenuItemToPlayer(Player* player, uint32 icon, uint32 sender,uint32 action, const char *Message, ...)
{
    if(!player)
        return;

    char Result[1024];
    va_list List;
    va_start(List, Message);
    vsnprintf(Result, 1024, Message, List);
    va_end(List);

    player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, icon,	Result,	sender,	action, "", false);
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SendMessageToPlayer(const char *msgToSend, ...)
{
    Player *player = GetPlayer();
    if(!player)
        return;

    char Result[1024];
    va_list List;
    va_start(List, msgToSend);
    vsnprintf(Result, 1024, msgToSend, List);
    va_end(List);

    player->GetSession()->SendAreaTriggerMessage(Result);
    ChatHandler(player).PSendSysMessage(Result);
    RecordLog("TowerDefense: Player: [%s] received the message: [%s] from the tower defense system.", player->GetName(), Result);
}

uint32 TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GenerateEventId()
{
    _highEventId++;
    return _highEventId;
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::UpdatePlayerStats(uint32 playerGUID, TDEventPlayerIndex statIndex, uint32 statIncreaseValue)
{
    if(statIndex > TD_PLAYER_STAT_MAX)
    {
        RecordLog("TowerDefense: UpdatePlayerStats statIndex out of range");
        return;
    }
    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT %s FROM custom_td_players WHERE %s = '%u'", TowerDefensePlayerStatFields[statIndex], TowerDefensePlayerStatFields[TD_PLAYER_STAT_GUID], playerGUID)){
        CharacterDatabase.PExecute("UPDATE custom_td_players SET %s = '%u' WHERE %s = '%u'", TowerDefensePlayerStatFields[statIndex], queryResult->Fetch()[0].GetUInt32()+statIncreaseValue, TowerDefensePlayerStatFields[TD_PLAYER_STAT_GUID], playerGUID);
        RecordLog("Updated stats for Player GUID: [%u], added [%u] to [%s].", playerGUID, statIncreaseValue, TowerDefensePlayerStatFields[statIndex]);
    }
    else{
        CharacterDatabase.PExecute("REPLACE INTO custom_td_players (%s,%s) VALUES('%u', '%u')", TowerDefensePlayerStatFields[TD_PLAYER_STAT_GUID], TowerDefensePlayerStatFields[statIndex], playerGUID, statIncreaseValue);
        RecordLog("Inserted stats for Player GUID: [%u], added [%u] to [%s].", playerGUID, statIncreaseValue, TowerDefensePlayerStatFields[statIndex]);
    }
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SendMailToPlayer(Player *player, uint32 playerGUID, const char *mailMessage, ...)
{
    MailSender toSend(MAIL_NORMAL, playerGUID, TD_SYSTEM_MAIL_TYPE);
    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    char Body[1024];
    va_list List;
    va_start(List, mailMessage);
    vsnprintf(Body, 1024, mailMessage, List);
    va_end(List);

    MailDraft mailDraft(TD_SYSTEM_MSG_MAIL_SUBJECT, Body);
    if(player){
        mailDraft.SendMailTo(trans, MailReceiver(player), toSend);
        RecordLog("TowerDefense: Player: [%s] received the mail: [%s] from the tower defense system.", player->GetName(), Body);
    }
    else{
        mailDraft.SendMailTo(trans, MailReceiver(playerGUID), toSend);
        RecordLog("TowerDefense: Player GUID: [%u] received the mail: [%s] from the tower defense system.", playerGUID, Body);
    }
    CharacterDatabase.CommitTransaction(trans);
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SetupEventData()
{
    Player *player = GetPlayer();
    if(!player)
        return;

    SetEventId(GenerateEventId()); // set the event id
    SetPlayerGUID(player->GetGUIDLow()); // set the player guid 
    SetCurrentWaveId(0); // set the current wave id to zero
    SetBaseHealth(100); // set the base health to 100
    SetResources(GetStartResources()); // set the resources that the player has to starter resources
    SetUnits(0); // set the number of spawned attackers to zero
    SetFinished(false); // set the event to unfinished
    SetEventStatus(TD_EVENT_STATUS_TELEPORT); // Set the event status to started and not running a wave
    Events.Reset();
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::SaveEventData()
{
    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_events WHERE Id = '%u'", GetEventId())){
        CharacterDatabase.PExecute("UPDATE custom_td_events SET eventFinished = '%u'", GetFinished());
        RecordLog("TowerDefense: Updated Event Id: [%u], it is now set to finished!",GetEventId());
    }
    else{
        CharacterDatabase.PExecute("INSERT INTO custom_td_events VALUES ('%u', '%u', '%u', '%u', '%u', NOW(), '%u')", GetEventId(), GetPlayerGUID(), GetCurrentWaveId(), GetResources(),GetBaseHealth(), GetFinished());
        RecordLog("TowerDefense: Inserted Event Id: [%u] to the database.", GetEventId());
    }
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::DeleteEventData()
{
    Player *player = GetPlayer();
    if(!player)
        return;

    SetEventId(0);
    SetPlayerGUID(0);
    SetCurrentWaveId(0);
    SetBaseHealth(0);
    SetResources(0);
    SetUnits(0);
    SetFinished(false);
    SetEventStatus(TD_EVENT_STATUS_NONE);
    CountDown = 0;
    Events.Reset();
    RecordLog("TowerDefense: the tower defense event for player %s was deleted", player->GetName());
    _player = NULL;
}

void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::GetRecords(Player *player)
{
    if(!player)
        return;
    if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM custom_td_players WHERE playerGUID = '%u'", player->GetGUIDLow()))
    {
        Field *Fields = queryResult->Fetch();
        uint32 playerGUID = Fields[0].GetUInt32();
        uint32 eventsLost = Fields[1].GetUInt32();
        uint32 eventsWon = Fields[2].GetUInt32();
        uint32 eventsUnfinished = Fields[3].GetUInt32();
        uint32 currentResources = Fields[4].GetUInt32();

        std::ostringstream Lost;
        std::ostringstream Won;
        std::ostringstream UnFinished;
        std::ostringstream Resources;

        Lost << MSG_COLOR_SUBWHITE << "You have lost: " << MSG_COLOR_LIGHTBLUE <<  eventsLost << " Event(s)." ;
        Won << MSG_COLOR_SUBWHITE << "You have won: " << MSG_COLOR_LIGHTBLUE <<  eventsWon << " Event(s)." ;
        UnFinished << MSG_COLOR_SUBWHITE << "You have resigned: " << MSG_COLOR_LIGHTBLUE <<  eventsUnfinished << " Event(s)." ;
        Resources << MSG_COLOR_SUBWHITE << "You have: " << MSG_COLOR_LIGHTBLUE <<  currentResources << " Resource(s)." ;

        ChatHandler(player).SendSysMessage(Lost.str().c_str());
        ChatHandler(player).SendSysMessage(Won.str().c_str());
        ChatHandler(player).SendSysMessage(UnFinished.str().c_str());
        ChatHandler(player).SendSysMessage(Resources.str().c_str());
    }
    else
        ChatHandler(player).SendSysMessage(TD_SYSTEM_MSG_NO_EVENT_DATA);
}
void TowerDefenseInstanceScript::TowerDefenseMapInstanceScript::RecordLog(const char * str, ...)
{
    if (!str)
        return;

    // If file logging is enabled!
    if(IsLoggingEnabled())
    {
        char Result[1024];
        va_list List;
        va_start(List, str);
        vsnprintf(Result, 1024, str, List);
        va_end(List);
        sLog->outBasic(Result);
    }
}

void TowerDefensePlayerScript::OnLogout(Player *player)
{
    if(!player){
        sLog->outBasic("TowerDefense: OnLogout player is NULL!");
        return;
    }
    TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(player->GetInstanceScript());
    if (instance && instance->GetEventStatus() >= TD_EVENT_STATUS_TELEPORT)
        if(player == instance->GetPlayer())
            instance->HandleEventComplete(TD_EVENT_COMPLETE_UNFINISHED);
}

void AddSC_TowerDefenseInstanceScript()
{
    new TowerDefenseInstanceScript();
    new TowerDefensePlayerScript(); 
}