/*
* Author: Xees
* FileName: TowerDefense.h
* Description: This file is used for definitions and requirements of the tower defense system
* Version: 2.1
* Status: Needs an Overhaul!
*/
#include "ScriptPCH.h"
#include "TowerDefense.h"

class TD_NPC : public CreatureScript
{
public:
    TD_NPC() : CreatureScript(TD_NPC_SCRIPT_NAME) {}

    bool OnGossipHello(Player *player, Creature *creature) 
    { 
        player->PlayerTalkClass->ClearMenus();

        // Load instance script.
        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript * instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript());
        if(!instance){
            sLog->outBasic("TowerDefense: there is no TowerDefenseMapInstanceScript for this creature On TD_NPC OnGossipHello();!");
            return false;
        }

        if(instance->GetEventStatus() > TD_EVENT_STATUS_NONE){
            ChatHandler(player).SendSysMessage(TD_SYSTEM_MSG_ALREADYRUNNING);
            return false;
        }

        instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_NPC_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1,TD_NPC_TEXT_START_EVENT);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true; 
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action) 
    {
        player->PlayerTalkClass->ClearMenus();
        // Load instance script.
        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript());
        if(!instance){
            sLog->outBasic("TowerDefense: there is no TowerDefenseMapInstanceScript for this creature On TD_NPC OnGossipSelect();!");
            return false;
        }

        switch(sender)
        {
        case TD_NPC_MENU_MAIN:
            if(instance->GetEventStatus() < TD_EVENT_STATUS_TELEPORT){
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_NPC_MENU_EVENT_MODE, GOSSIP_ACTION_INFO_DEF + 1, TD_NPC_TEXT_START_EVENT);
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_NPC_MENU_SHOW_RECORDS, GOSSIP_ACTION_INFO_DEF + 1, TD_NPC_TEXT_SHOW_RECORDS);
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_EXIT,TD_NPC_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1, TD_TEXT_EXIT);
                player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            }else{
                player->GetSession()->SendNotification(TD_SYSTEM_MSG_STARTED_ALREADY);
                player->CLOSE_GOSSIP_MENU();
            }
            break;
        case TD_NPC_MENU_EVENT_MODE:
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_NPC_MENU_START_EVENT, GOSSIP_ACTION_INFO_DEF + 51, TD_NPC_TEXT_EVENT_EASY);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_NPC_MENU_START_EVENT, GOSSIP_ACTION_INFO_DEF + 52, TD_NPC_TEXT_EVENT_HARD);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_NPC_MENU_START_EVENT, GOSSIP_ACTION_INFO_DEF + 53, TD_NPC_TEXT_EVENT_EXTREME);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_EXIT,TD_NPC_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1, TD_TEXT_EXIT);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
            break;
        case TD_NPC_MENU_START_EVENT:
            instance->StartEvent(player, action);
            player->CLOSE_GOSSIP_MENU();
            break;
        case TD_NPC_MENU_SHOW_RECORDS:
            instance->GetRecords(player);
            player->CLOSE_GOSSIP_MENU();
            break;
        case TD_NPC_MENU_EXIT:
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }
};

class TD_ITEM : public ItemScript
{
public:
    TD_ITEM() : ItemScript(TD_ITEM_SCRIPT_NAME) {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        player->PlayerTalkClass->ClearMenus();

        if(player->GetMapId() != TD_INSTANCE_MAP_ID)
            return false;

        // Load instance script.
        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(player->GetInstanceScript());
        if(!instance){
            sLog->outBasic("TowerDefense: there is no TowerDefenseMapInstanceScript for this item On TD_ITEM OnUse();!");
            return false;
        }

        if(instance->GetEventStatus() < TD_EVENT_STATUS_TELEPORT){
            ChatHandler(player).SendSysMessage(TD_SYSTEM_MSG_CANNOT_USE_OUTSIDE);
            return false;
        }

        instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_ITEM_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_START_EVENT);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,item->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Item* item, uint32 Sender, uint32 Action) 
    {
        player->PlayerTalkClass->ClearMenus();

        // Load instance script.
        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(player->GetInstanceScript());
        if(!instance){
            sLog->outBasic("TowerDefense: there is no TowerDefenseMapInstanceScript for this item On TD_ITEM OnGossipSelect();!");
            return false;
        }

        switch(Sender)
        {
        case TD_ITEM_MENU_MAIN:
            if(instance->GetEventStatus() < TD_EVENT_STATUS_TELEPORT)
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_ITEM_MENU_SELECT_EVENT_MODE, GOSSIP_ACTION_INFO_DEF + 1, TD_NPC_TEXT_START_EVENT);
            if(instance && instance->GetEventStatus() >= TD_EVENT_STATUS_TELEPORT)
            {
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_ITEM_MENU_BASE_HEALTH, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_BASE_HEALTH,instance->GetBaseHealth());
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_ITEM_MENU_CURRENT_RESOURCES, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_CURRENT_RESOURCES,instance->GetResources());
                if(instance->GetEventStatus() < TD_EVENT_STATUS_RUNNING && instance->GetEventMode() == TD_EVENT_MODE_EASY){
                    instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_ITEM_MENU_START_WAVE, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_START_WAVE,instance->GetCurrentWaveId()+1);
                }
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_BUY_GUARD,TD_ITEM_MENU_SPAWN_TOWER_MENU, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_SPAWN_TOWER_MENU);
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DECLINE,TD_ITEM_MENU_QUIT_EVENT, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_QUIT_EVENT);
            }
            else{
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_ITEM_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_NO_EVENT_DATA);
            }
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_EXIT,TD_ITEM_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1, TD_TEXT_EXIT);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,item->GetGUID());
            break;
        case TD_ITEM_MENU_SELECT_EVENT_MODE:
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_ITEM_MENU_START_EVENT, GOSSIP_ACTION_INFO_DEF + 51, TD_NPC_TEXT_EVENT_EASY);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_ITEM_MENU_START_EVENT, GOSSIP_ACTION_INFO_DEF + 52, TD_NPC_TEXT_EVENT_HARD);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_START_EVENT,TD_ITEM_MENU_START_EVENT, GOSSIP_ACTION_INFO_DEF + 53, TD_NPC_TEXT_EVENT_EXTREME);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_EXIT,TD_ITEM_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1, TD_TEXT_EXIT);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,item->GetGUID());
            break;
        case TD_ITEM_MENU_START_EVENT:
            player->CLOSE_GOSSIP_MENU();
            instance->StartEvent(player, Action);
            break;
        case TD_ITEM_MENU_BASE_HEALTH:
            OnGossipSelect(player, item, TD_ITEM_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case TD_ITEM_MENU_CURRENT_RESOURCES:
            OnGossipSelect(player, item, TD_ITEM_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case TD_ITEM_MENU_SPAWN_TOWER_MENU:
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_ITEM_MENU_SPAWN_TOWER_MENU, GOSSIP_ACTION_INFO_DEF + 1, TD_ITEM_TEXT_CURRENT_RESOURCES,instance->GetResources());
            instance->GetGuardList();
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_ITEM_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1, TD_TEXT_GOBACK);
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_EXIT,TD_ITEM_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1, TD_TEXT_EXIT);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,item->GetGUID());
            break;
        case TD_ITEM_MENU_SPAWN_TOWER_GUARD:
            player->CLOSE_GOSSIP_MENU();
            instance->SpawnFromGuardList(Action);
            break;
        case TD_ITEM_MENU_START_WAVE:
            instance->StartNextWave(1000); // start wave right away
            player->CLOSE_GOSSIP_MENU();
            break;
        case TD_ITEM_MENU_QUIT_EVENT:
            instance->HandleEventComplete(TD_EVENT_COMPLETE_QUIT);
            player->CLOSE_GOSSIP_MENU();
            break;
        case TD_ITEM_MENU_EXIT:
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }
};

class TD_MOB : public CreatureScript
{
public:
    TD_MOB() : CreatureScript(TD_MOB_SCRIPT_NAME) {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new TD_MOBAI (creature);
    }

    struct TD_MOBAI : public ScriptedAI
    {
        TD_MOBAI(Creature* creature) : instance(static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript())), ScriptedAI(creature) {}

        Player* player;
        uint32 MobSpawnTimer, MobEffectTimer, MobPathId, MobPower, MobBounty, MobHealth, MobDmg, MobAttackSpeed, MobSpellId;
        bool MobStartedPath, MobIsRunning, MobIsAirMob;
        float MobAttackDistance, MobSpeed;
        MonsterInfo* monster;
        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance;

        void Reset()
        {
            if(!instance)
                return;
            player = instance->GetPlayer();
            if(!player)
                return;
            MobSpawnTimer = 500;
            MobEffectTimer = 1000;
            MobStartedPath = false;
            monster = instance->GetMonsterByEntry(me->GetEntry());
            if(!monster){
                me->DespawnOrUnsummon();
                sLog->outBasic("TowerDefense: creature with entry: [%u] has Script Name that is used by TowerDefense, but is not part of the wave: [%u].", me->GetEntry(), instance->GetCurrentWaveId());
            }else{
                MobPathId = monster->GetPathId();
                MobPower = monster->GetPower();
                MobBounty = monster->GetBounty();
                MobIsRunning = monster->GetIsRunning();
                MobIsAirMob = monster->GetIsAirMob();
                MobHealth = monster->GetHealth();
                MobDmg = monster->GetDamage();
                MobAttackDistance = monster->GetAttackDistance();
                MobAttackSpeed = monster->GetAttSpeed();
                MobSpeed = monster->GetSpeed();
                MobSpellId = monster->GetDefSpell();
            }
        }
        /* All attackers creature template needs to have SET RegenHealth = 0  */ 

        void InitOnCreate()
        {
            me->SetMaxHealth(MobHealth);
            me->SetHealth(me->GetMaxHealth());
            SetSpeeds(MobSpeed);
        }

        void SetSpeeds(float speed)
        {
            me->SetSpeed(MOVE_WALK,  speed, true);
            me->SetWalk(true);

            if(MobIsRunning){
                me->SetSpeed(MOVE_RUN,   speed, true);
                me->SetWalk(false);
            }
            if(MobIsAirMob){
                me->SetSpeed(MOVE_FLIGHT,speed, true);
                me->SetWalk(false);
            }
        }

        bool WaveIsRunning()
        {
            if(!instance) return false;

            if(instance->GetEventStatus() >= TD_EVENT_STATUS_RUNNING)
                return true;
            return false;
        }

        void StartWalkingToEndPoint() { 
            (MobPathId) ? me->GetMotionMaster()->MovePath(MobPathId,false) : sLog->outBasic("TowerDefense: Creature entry: [%u] could not load path id, please check path id in the database.", me->GetEntry());
        }

        uint32 GetMobSpellByCastType(TDEventSpellCastType type) {
            if(!monster) return 0;
            return monster->GetSpellIdByCastType(type);
        }

        void CastOnSpawnSpells() {
            if(!player) return;

            if(GetMobSpellByCastType(TD_CAST_ON_SPAWN_CAST_SELF))
                me->CastSpell(me, GetMobSpellByCastType(TD_CAST_ON_SPAWN_CAST_SELF), true);
            if(GetMobSpellByCastType(TD_CAST_ON_SPAWN_CAST_TARGET))
                me->CastSpell(player, GetMobSpellByCastType(TD_CAST_ON_SPAWN_CAST_TARGET), true);
        }

        void DoGuardAOEEffects(Unit* guard) {
            if(!instance) return;

            uint32 AOESpell = instance->GetGuardSpellByCastType(guard->GetGUID(), TD_CAST_AOE_CAST_TARGET);
            guard->CastSpell(me, AOESpell, true);

            switch(AOESpell)
            {
            case 15571: // This is the case where a creature enters the radius of an ice tower, it causes the creatures speed to reset to a lower speed
                SetSpeeds(MobSpeed * 0.7f);
                break;
            }
        }

        void StopGuardAOEEffects(Unit* guard){
            SetSpeeds(MobSpeed);
        }

        Unit* GetClosestAOEGuard() 
        {  
            if(!instance || !WaveIsRunning())
                return NULL;

            Unit* target = me->SelectNearestTarget(5.0f); // TEMP for Ice Tower AOE effects
            if(target){
                GuardInfo* guardInfo = instance->GetGuardByGuid(target->GetGUID());
                if(guardInfo && guardInfo->Entry == target->GetEntry())
                    if(IsAOEGuard(target))
                        return target;
            }
            return NULL;
        }

        Unit* GetClosestGuard() 
        {  
            if(!instance || !WaveIsRunning())
                return NULL;

            Unit* target = me->SelectNearestTarget(5.0f); // TEMP for Ice Tower AOE effects
            if(target){
                GuardInfo* guardInfo = instance->GetGuardByGuid(target->GetGUID());
                if(guardInfo && guardInfo->Entry == target->GetEntry())
                    return target;
            }
            return NULL;
        }

        bool IsAOEGuard(Unit* guard)
        {
            if(!guard)
                return false;
            if (QueryResult queryResult = CharacterDatabase.PQuery("SELECT spellAOECastTarget FROM custom_td_base_spells WHERE creatureEntry = '%u'", guard->GetEntry()))
                return true;
            return false;
        }

        void JustDied(Unit* killer) 
        {
            if(!instance || !killer) return;
            instance->UpdateUnits(TD_EVENT_DEC, 1);
            instance->UpdateResources(TD_EVENT_INC,MobBounty);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if(!instance || !MobPathId) {return;}
            if (id == instance->GetLastPointInPath(MobPathId)){
                instance->UpdateHealth(MobPower);
                instance->UpdateUnits(TD_EVENT_DEC, 1);
                me->DespawnOrUnsummon();
            }
            return;
        }

        void CastDefaultSpell(Unit* target)
        {
            if(!target)
                return;
            if(me->GetDistance(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ()) > 8)
                me->SetFacingTo(target->GetOrientation());

            if(MobIsAirMob && instance->GetGuardIsAntiAir(target->GetGUID()) && MobSpellId) // if mob is air mob, and attacker is anti air, they can attack him
                me->CastSpell(target, MobSpellId, true);
            else if(!MobIsAirMob && instance->GetGuardIsAntiGround(target->GetGUID()) && MobSpellId) // if mob is ground mob, and attacker is ground, then attack
                me->CastSpell(target, MobSpellId, true);
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (damageType != SPELL_DIRECT_DAMAGE) // don't do any spell damage, only specific damage
                return;
            damage = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC); // not attackable by player
        }

        bool GuardIsInDistance(Unit* guard)
        {
            if(!guard)
                return false;
            if (WaveIsRunning()){
                if(me->GetDistance(guard->GetPositionX(),guard->GetPositionY(),guard->GetPositionZ()) <= MobAttackDistance)
                    return true;
            }
            return false;
        }

        bool IsCasting()
        {
            if(me->HasUnitState(UNIT_STATE_CASTING))
                return true;
            return false;
        }

        void UpdateAI(const uint32 diff)
        {
            if(!instance) return;

            Player* player = instance->GetPlayer();
            if(!player || instance->GetEventStatus() < TD_EVENT_STATUS_TELEPORT) me->DespawnOrUnsummon();

            if(!WaveIsRunning()) return;

            if (MobSpawnTimer <= diff && !MobStartedPath)
            {
                me->CastSpell(me, instance->GetSpellIdByUniqueId(1), true);
                InitOnCreate();
                StartWalkingToEndPoint();
                CastOnSpawnSpells();
                MobStartedPath = true;
            } else MobSpawnTimer -= diff;

            if (MobEffectTimer <= diff)
            {
                Unit* guard = GetClosestAOEGuard();
                // will need to rewrite the entire guard script, because this is just stupid.
                if(guard && me->GetDistance(guard->GetPositionX(),guard->GetPositionY(),guard->GetPositionZ()) > 8)
                    StopGuardAOEEffects(guard);

                if(guard && me->GetDistance(guard->GetPositionX(),guard->GetPositionY(),guard->GetPositionZ()) < 8)
                    DoGuardAOEEffects(guard);

                if (!WaveIsRunning() || IsCasting())
                    return;

                if(GuardIsInDistance(GetClosestGuard()))
                    CastDefaultSpell(GetClosestGuard());

                MobEffectTimer = 1000;
            } else MobEffectTimer -= diff;
        }
    };
};

class TD_GUARD : public CreatureScript
{
public:
    TD_GUARD() : CreatureScript(TD_GUARD_SCRIPT_NAME) {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();

        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript());
        if(!instance)
            return false;

        if(instance->GetEventStatus() < TD_EVENT_STATUS_TELEPORT){
            ChatHandler(player).SendSysMessage(TD_SYSTEM_MSG_CANNOT_USE_OUTSIDE);
            return false;
        }

        instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_GUARD_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1,TD_GUARD_TEXT_TOWER_NAME,creature->GetName());
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance = static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript());
        if(!instance)
            return false;

        switch(sender)
        {
        case TD_GUARD_MENU_MAIN:
            if(instance->GetEventStatus() >= TD_EVENT_STATUS_TELEPORT)
            {
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_GUARD_MENU_NAME, GOSSIP_ACTION_INFO_DEF + 1,TD_GUARD_TEXT_TOWER_NAME,creature->GetName());
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_DOT_EVENT,TD_GUARD_MENU_CURRENT_RESOURCES, GOSSIP_ACTION_INFO_DEF + 1,TD_GUARD_TEXT_CURRENT_RESOURCES,instance->GetResources());
                instance->UpgradeGuardMenu(creature->GetGUID());
                instance->AddSimpleMenuItemToPlayer(player,TD_ICON_BUY_GUARD,TD_GUARD_MENU_SELL, GOSSIP_ACTION_INFO_DEF + 1,TD_GUARD_TEXT_SELL_GUARD,instance->GetGuardSellPrice(creature->GetGUID()));
            }
            instance->AddSimpleMenuItemToPlayer(player,TD_ICON_EXIT,TD_GUARD_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1,TD_TEXT_EXIT);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
            break;
        case TD_GUARD_MENU_NAME:
            OnGossipSelect(player, creature, TD_GUARD_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case TD_GUARD_MENU_CURRENT_RESOURCES:
            OnGossipSelect(player, creature, TD_GUARD_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case TD_GUARD_MENU_UPGRADE: 
            instance->UpgradeGuard(creature->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            break;
        case TD_GUARD_MENU_UPGRADE_MAX:
            OnGossipSelect(player, creature, TD_GUARD_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case TD_GUARD_MENU_SELL: 
            instance->SellGuard(creature->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            break;
        case TD_GUARD_MENU_EXIT:
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new TD_GUARDAI (creature);
    }

    struct TD_GUARDAI : public ScriptedAI
    {
        TD_GUARDAI(Creature* creature) : instance(static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript())), ScriptedAI(creature) {}

        uint32 SpawnTimer;
        uint32 SpellTimer;
        Unit* Target;
        bool Spawned;
        MonsterInfo* monster;
        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance;

        void Reset()
        {
            if(!instance){
                sLog->outBasic("TowerDefense: there is no TowerDefenseMapInstanceScript for this creature On TD_GUARDAI Reset();!");
                return;
            }
            Spawned = false;
            SpawnTimer = 200;
            SpellTimer = 1000; // need to allow db attack speed to be loaded before trying to fetch it.
            InitOnCreate();
        }

        void InitOnCreate()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->setFaction(TD_FACTION_GUARD); // Set creature faction to friendly to all players but hostile to monsters
            me->SetReactState(REACT_AGGRESSIVE);
        }

        bool WaveIsRunning()
        {
            if(instance){
                if (instance->GetEventStatus() >= TD_EVENT_STATUS_RUNNING)
                    return true;
            }
            return false;
        }

        bool AttackerIsInWave(Unit* attacker)
        {
            if(!attacker)
                return false;
            if(instance->IsCreatureInWave(instance->GetCurrentWaveId(),attacker->GetEntry()))
                return true;
            return false;
        }

        bool AttackerIsInDistance(Unit* attacker)
        {
            if(!attacker)
                return false;
            if (WaveIsRunning()){
                if(me->GetDistance(attacker->GetPositionX(),attacker->GetPositionY(),attacker->GetPositionZ()) <= instance->GetGuardAttackDistance(me->GetGUID()))
                    return true;
            }
            return false;
        }

        bool IsCasting()
        {
            if(me->HasUnitState(UNIT_STATE_CASTING))
                return true;
            return false;
        }

        Unit* GetClosestAttacker() 
        {  
            if(!instance || !WaveIsRunning())
                return NULL;
            Unit* target = NULL;

            target = SelectTarget(SELECT_TARGET_TOPAGGRO,0,instance->GetGuardAttackDistance(me->GetGUID()),false);
            if(!target)
                target = me->SelectNearestTarget(instance->GetGuardAttackDistance(me->GetGUID()));
            if(target && AttackerIsInWave(target)){
                me->AddThreat(target,100);
                return target;
            }
            return NULL;
        }

        uint32 GetDefaultDmg()
        {
            if(!instance)
                return 0;
            uint32 defDmg = instance->GetGuardDamage(me->GetGUID());
            if(defDmg)
                return defDmg;
            else
                instance->RecordLog("TowerDefense: there is no default damage for guard entry: [%u].", me->GetEntry());
            return 0;
        }

        uint32 GetDefaultSpell()
        {
            if(!instance)
                return 0;
            GuardInfo* guard = instance->GetGuardByGuid(me->GetGUID());
            if(guard)
                return guard->GetDefSpell();
            else
                instance->RecordLog("TowerDefense: there is no default spell id for guard entry: [%u].", me->GetEntry());
            return 0;
        }

        void CastDefaultSpell(Unit* target)
        {
            if(!target)
                return;
            if(me->GetDistance(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ()) > 8)
                me->SetFacingTo(target->GetOrientation());

            if(!GetDefaultSpell())
                return;

            monster = instance->GetMonsterByEntry(target->GetEntry());
            if(!monster){
                sLog->outBasic("TowerDefense: creature with entry: [%u] has Script Name that is used by TowerDefense, but is not part of the wave: [%u].", me->GetEntry(), instance->GetCurrentWaveId());
            }else{
                if(instance->GetGuardIsAntiAir(me->GetGUID()) && monster->GetIsAirMob()) // if guard is anti air, and attacker is air mob then cast
                me->CastSpell(target, GetDefaultSpell(), true);
                else if(instance->GetGuardIsAntiGround(me->GetGUID()) && !monster->GetIsAirMob()) // if guard is anti ground and attacker is ground then cast
                me->CastSpell(target, GetDefaultSpell(), true);
            }
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (damageType != SPELL_DIRECT_DAMAGE) // guards cannot use spells for damage, only default damage
                return;
            damage = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if(!instance || !WaveIsRunning())
                return;
            if (!AttackerIsInWave(attacker))
                damage = 0;
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if(!target || !WaveIsRunning() || !spell)
                return;
            if(target->GetTypeId() == TYPEID_UNIT && AttackerIsInWave(target)){ 
                me->DealDamage(target,GetDefaultDmg()); 
                me->CastSpell(target,instance->GetGuardSpellByCastType(me->GetGUID(), TD_CAST_ON_HIT_TARGET_CAST_TARGET),true);
            }
        }

        void CastOnSpawnSpells()
        {
            if(!instance)
                return;
            Player* player = instance->GetPlayer();
            if(!player)
                return;
            me->CastSpell(me, instance->GetGuardSpellByCastType(me->GetGUID(), TD_CAST_ON_SPAWN_CAST_SELF), true);
        }

        void UpdateAI(const uint32 diff){
            if(!instance)
                return;

            Player* player = instance->GetPlayer();
            if(!player || instance->GetEventStatus() < TD_EVENT_STATUS_TELEPORT)
                me->DespawnOrUnsummon();

            if (SpawnTimer <= diff && !Spawned)
            {
                me->CastSpell(me, instance->GetSpellIdByUniqueId(1), true);
                CastOnSpawnSpells();
                Spawned = true;
            } else SpawnTimer -= diff;

            if (SpellTimer <= diff)
            {
                if (!WaveIsRunning() || IsCasting())
                    return;

                if(AttackerIsInDistance(GetClosestAttacker()))
                    CastDefaultSpell(GetClosestAttacker());

                SpellTimer = instance->GetGuardAttSpeed(me->GetGUID());
            } else SpellTimer -= diff;
        }
    };
};

class TD_UPDATER_TRIGGER : public CreatureScript
{
public:
    TD_UPDATER_TRIGGER() : CreatureScript(TD_UPDATER_SCRIPT_NAME) { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new TD_UPDATER_TRIGGERAI(creature);
    }

    struct TD_UPDATER_TRIGGERAI : public ScriptedAI
    {
        TD_UPDATER_TRIGGERAI(Creature* creature) : instance(static_cast<TowerDefenseInstanceScript::TowerDefenseMapInstanceScript*>(creature->GetInstanceScript())), ScriptedAI(creature) {}

        TowerDefenseInstanceScript::TowerDefenseMapInstanceScript* instance;

        uint32 SpawnTimer;
        uint32 UnitsCounter;
        Player* player;

        void Reset()
        {
            SpawnTimer = 1000;
            UnitsCounter = 0;
            InitOnCreate();
        }

        void InitOnCreate()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_IMMUNE_TO_PC);
            me->SetWalk(false);
            me->setFaction(35);
            me->SetReactState(REACT_PASSIVE);
        }

        bool WaveIsLoaded()
        {
            if (!instance)
                return false;
            if (instance->GetEventStatus() == TD_EVENT_STATUS_LOADED)
                return true;
            return false;
        }

        void SpawnWaveCreatures()
        {
            if (!instance)
                return;
            WaveInfo* wave = instance->GetWaveById(instance->GetCurrentWaveId());
            if(UnitsCounter < wave->GetNumCreatures()) 
            {
                    instance->SpawnNextCreature(me);
                    instance->UpdateUnits(TD_EVENT_INC,1); 
                    UnitsCounter++;
            }else{
                instance->SetEventStatus(TD_EVENT_STATUS_LOADED);
                instance->RecordLog("TowerDefense: Wave [%u] is now loaded for Event Id: [%u].", instance->GetCurrentWaveId(), instance->GetEventId());
                UnitsCounter = 0;
            }
        }

        void UpdateAI(uint32 const diff)
        {
            if (!instance)
                return;
            player = instance->GetPlayer();
            if(!player)
                return;

            instance->OnUpdate(diff); 
            if (instance->GetEventStatus() < TD_EVENT_STATUS_LOADING)
                return;

            if(instance->GetUnits() == 0 && WaveIsLoaded()){
                instance->SendMessageToPlayer(TD_SYSTEM_MSG_WAVE_HAS_ENDED, instance->GetCurrentWaveId());
                instance->SetEventStatus(TD_EVENT_STATUS_TELEPORT);
                instance->RecordLog("Event Id: [%u] there are no spawned units in wave [%u], wave is no longer running.",instance->GetEventId(),instance->GetCurrentWaveId());

                WaveInfo* wave = instance->GetWaveById(instance->GetCurrentWaveId()+1);  
                if(!wave) // if no wave, this means the last wave is done, you can finish the event now!
                    instance->HandleEventComplete(TD_EVENT_COMPLETE_WON);

                switch(instance->GetEventMode())
                {
                case TD_EVENT_MODE_HARD:
                    instance->SendMessageToPlayer(TD_SYSTEM_MSG_NEXT_WAVE_STARTS_IN_HARD, 30);
                    instance->StartNextWave(30000); // start waves after 30 seconds
                    break;
                case TD_EVENT_MODE_EXTREME:
                    instance->StartNextWave(1000); // start waves right away
                    break;
                }
            }

            if (!WaveIsLoaded()){ 
                if (SpawnTimer <= diff)
                {
                    SpawnWaveCreatures();
                    SpawnTimer = 1000;
                } else SpawnTimer -= diff;
            }
        }
    };
};

class TD_VENDOR : public CreatureScript
{
public:
    TD_VENDOR() : CreatureScript(TD_VENDOR_SCRIPT_NAME) {}

    bool OnGossipHello(Player *player, Creature *creature) 
    { 
        player->PlayerTalkClass->ClearMenus();
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, TD_ICON_DOT_EVENT, TD_VENDOR_TEXT_EXCHANGE, TD_VENDOR_MENU_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "", false);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true; 
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action) 
    {
        player->PlayerTalkClass->ClearMenus();
        switch(sender)
        {
        case TD_VENDOR_MENU_MAIN:
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, TD_ICON_DOT_EVENT, TD_VENDOR_TEXT_EXCHANGE, TD_VENDOR_EXCHANGE, GOSSIP_ACTION_INFO_DEF + 1, "", false);
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, TD_ICON_BUY_GUARD, TD_VENDOR_TEXT_LIST, TD_VENDOR_LIST, GOSSIP_ACTION_INFO_DEF + 1, "", false);
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, TD_ICON_EXIT, TD_TEXT_EXIT, TD_VENDOR_MENU_EXIT, GOSSIP_ACTION_INFO_DEF + 1, "", false);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            break;
        case TD_VENDOR_EXCHANGE:
            player->CLOSE_GOSSIP_MENU();
            if(uint32 ResAmount = GetAmountOfResourcesPlayerHas(player))
            {
                UpdatePlayerResources(player, TD_EVENT_DEC, ResAmount);
                player->AddItem(40752, ResAmount);
                ChatHandler(player).SendSysMessage("All your resources were exchanged.");
            }else
                ChatHandler(player).SendSysMessage("You don't have any resources!");
            break;
        case TD_VENDOR_LIST:
            player->GetSession()->SendListInventory(creature->GetGUID());
            break;
        case TD_VENDOR_MENU_EXIT:
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }

    uint32 GetAmountOfResourcesPlayerHas(Player* player)
    {
        if(!player)
            return 0;
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT currentResources FROM custom_td_players WHERE playerGUID = '%u'", player->GetGUIDLow()))
        {
            Field* Fields = queryResult->Fetch();
            return Fields[0].GetUInt32();
        }
        return 0;
    }

    void UpdatePlayerResources(Player* player, TDEventUpdateType type, uint32 resValue)
    {
        if(!player)
            return;
        if(!type)
            return;
        uint32 newRes = 0;
        if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT currentResources FROM custom_td_players WHERE playerGUID = '%u'", player->GetGUIDLow()))
        {
            Field* Fields = queryResult->Fetch();
            uint32 oldRes = Fields[0].GetUInt32();

            switch(type)
            {
            case TD_EVENT_INC:
                newRes = oldRes + resValue;
                break;
            case TD_EVENT_DEC:
                newRes = oldRes - resValue;
                break;
            }
            CharacterDatabase.PExecute("UPDATE custom_td_players SET currentResources = '%u' WHERE playerGUID = '%u'", newRes, player->GetGUIDLow());
        }
        return;
    }
};

void AddSC_TowerDefenseMisc()
{
    new TD_NPC();
    new TD_ITEM();
    new TD_MOB();
    new TD_GUARD();
    new TD_VENDOR();
    new TD_UPDATER_TRIGGER();
}