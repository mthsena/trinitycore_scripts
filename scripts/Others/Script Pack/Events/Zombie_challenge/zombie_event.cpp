/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Orion / Thunderofnl
 - Complete: 90%
 - ScriptName: 'Zombie Event' 
 - Comment:  None
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"
#include "Group.h"
#include "GroupMgr.h"
#include "GameEventMgr.h"
#include "Spell.h"
#include <list>
#include <algorithm>


//Config
uint32 const VENDOR_ID = 2500063;
bool debug = false;

///////Script/////////

enum ZombieSpells
{
    // Zombie
    SPELL_VISUAL_ATTACK_1H                      = 42880,
    SPELL_VISUAL_ATTACK_2H                      = 42904,
    SPELL_ZOMBIE_DIE_EFFECT                     = 61454,
    SPELL_EMERGE_VISUAL                         = 50142,
    SPELL_AURA_ZOMBIE_ON_FIRE                   = 42469,
    SPELL_INFECTED_BITE                         = 59364,
    SPELL_VOLATILE_INFECTION                    = 59228,

    // Bomb Bot and Proximity Mine
    SPELL_EXPLOSION                             = 63009,

    // Zombie Turret
    SPELL_RAPID_FIRE                            = 71250,

    // Zombie Cannon
    SPELL_FIRE_CANNON                           = 51362,

    // Spirit Guide
    SPELL_GHOST                                 =  8326,
    SPELL_RESURRECT_IMPACT_VISUAL               = 24171,

    // Zombie Spawnpoint
    SPELL_AURA_BLOWN_UP                         = 48143,

    // General
    SPELL_AURA_INVISIBLE                        = 44312,
    SPELL_AURA_TAG_ARROW                        = 20374,
    SPELL_AURA_SICKNESS                         = 15007,
    SPELL_AURA_ZOMBIE_DESERTER                  = 73535,
    SPELL_AURA_ZOMBIE_DESERTER_CHECKER          = 60125,
    SPELL_PLAYER_SUMMON_PET                     =   883,
};

enum ZombieGameobjects
{
    // Custom
    GAMEOBJECT_BARRICADE                        = 293610,
    GAMEOBJECT_ANVIL                            = 293611,
    GAMEOBJECT_TELEPORT_AWAY                    = 293612,
    GAMEOBJECT_ANVIL_INTRO                      = 293613,
    GAMEOBJECT_CANNON                           = 293614,

    // Already made
    GAMEOBJECT_POWER_UP                         = 180148, // Temporarily
    GAMEOBJECT_SPAWNPOINT_FIRE                  = 191158,
};

enum ZombieCreatures
{
    NPC_ZOMBIE                                  = 792130,
    NPC_KILL_WAVE_COUNTER                       = 792131,
    NPC_BRANN                                   = 792132,
    NPC_SPAWNPOINT                              = 792133,
    NPC_BARRICADE_TRIGGER                       = 792134,
    NPC_TURRET                                  = 792135,
    NPC_ZOMBIE_VEHICLE                          = 792136,
    NPC_BOMB_BOT                                = 792137,
    NPC_KEEP_OUT                                = 792138,
    NPC_TARUK                                   = 792139,
    NPC_INTRODUCTION_ARROW                      = 792140,
    NPC_SPIRIT_GUIDE                            = 792141,
    NPC_ANVIL_SPAWNER                           = 792142,
    NPC_FIRE_SPAWNER                            = 792143,
    NPC_CANNON_SHOOTER                          = 792144,
    NPC_ZOMBIE_INTRO_ONE                        = 792145,
    NPC_ZOMBIE_INTRO_TWO                        = 792146,
    NPC_ZOMBIE_INTRO_THREE                      = 792147,
    NPC_ZOMBIE_INTRO_FOUR                       = 792148,
    NPC_CANNON_SPAWNER                          = 792149,
    NPC_GOBLIN_ENGINEER                         = 792150,

    NPC_PROXIMITY_MINE                          =  34362,

    NPC_RISEN_CONSTRUCT                         =  10488,
    NPC_RATTLEGORE                              =  11622,
};

enum ZombieEvents
{
    // Zombie Turret
    EVENT_FIRE_TURRET                           = 1,
    
    // Zombie Cannon Shooter
    EVENT_FIRE_CANNON                           = 2,
    EVENT_CANNON_SHOOTER_DESPAWN                = 3,

    // Bomb Bot
    EVENT_BOMB_BOT_MOVE_TO_BARRICADE            = 4,
};

enum ZombieActions
{
    // Fire Spawner
    ACTION_FIRE_SPAWNER_MAKE_SPAWNPOINT_EXPLODE = 1,

    // Zombie
    ACTION_ZOMBIE_ATTEMPT_SPAWN_POWER_UP        = 2,
    ACTION_ZOMBIE_CAN_START_MOVING_AFTER_EMERGE = 3,
    ACTION_ZOMBIE_EMERGE_VISUAL                 = 4,
    ACTION_ZOMBIE_EMERGES_AFTER_DEATH           = 5,
    ACTION_ZOMBIE_NO_LONGER_EMERGING            = 6,

    // Zombie Wave & Kill Counter
    ACTION_COUNTER_INCREMENT_COUNTERS           = 7,

    // Zombie Barricade Trigger
    ACTION_BARRICADE_TRIGGER_INCR_HIT_COUNTER   = 8,
    ACTION_BARRICADE_TRIGGER_REPAIRED           = 9,

    // Brann
    ACTION_BRANN_INTRODUCTION_FINISHED          = 10,
    ACTION_BRANN_START_INTRODUCTION             = 11,
    ACTION_BRANN_EVENT_FINISHED                 = 12,

    // Spawnpoint
    ACTION_SPAWNPOINT_CAN_START_SUMMONING       = 13,
    ACTION_SPAWNPOINT_NO_LONGER_BLOWN_UP        = 14,
    ACTION_SPAWNPOINT_EXPLODES                  = 15,
    ACTION_SPAWNPOINT_CAN_SUMMON_TWO_AT_ONCE    = 16,
    ACTION_SPAWNPOINT_SPAWN_ZOMBIES             = 17,
    ACTION_SPAWNPOINT_CAN_SUMMON_THREE_AT_ONCE  = 18,
    ACTION_SPAWNPOINT_STOP_SPAWNING             = 19,

    // Spirit Guide
    ACTION_SPIRIT_GUIDE_INTRODUCTION_OVER       = 20,
};

enum ZombiePoints
{
    // Zombie
    POINT_MOVE_DOWN_SKULL_PILE                  = 1,
    POINT_MOVE_TO_BARRICADE                     = 2,
    POINT_MIDDLE_OF_BARRICADES                  = 3,

    // Engineering crew
    POINT_ENGINEER_TO_BARRICADE                 = 4,

    // Bomb Bot
    POINT_BOMB_BOT_TO_BARRICADE                 = 5,
    POINT_BOMB_BOT_TO_SPAWNPOINT                = 6,
};

enum ZombieMisceleaneous
{
    MAP_SCHOLOMANCE                             = 289,

    GAME_EVENT_ZOMBIE_EVENT                     = 123,

    ITEM_WAVE_TOKEN                             = 43949,
};
bool EVENT_ENDED = false;
uint32 const MAX_TURRET_CANNON_POINTS = 4;
Position const TurretCannonPlacePoints[MAX_TURRET_CANNON_POINTS] =
{
    {134.823120f, 178.290100f, 95.134583f, 1.759652f},
    {140.701843f, 178.517105f, 95.164375f, 1.005670f},
    {135.199432f, 165.664093f, 94.240585f, 4.375037f},
    {141.618805f, 165.910690f, 94.524040f, 4.924971f},
};

class ZombieEvent
{
    public:
        void SendMessageToPlayer(Player* player, std::string message)
        {
            if (!player || !player->IsInWorld())
                return;

            std::string str = "|cFFFFFC00" + std::string(message); // make message yellow
            WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
            data << str;
            player->GetSession()->SendPacket(&data);
        }

        void SendMessageToGroup(Player* player, std::string message)
        {
            if (!player)
                return;

            Group* group = player->GetGroup();

            if (!group)
            {
                SendMessageToPlayer(player, message);
                return;
            }

            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                if (Player* member = itr->getSource())
                {
                    std::string str = "|cFFFFFC00" + std::string(message);
                    WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
                    data << str;
                    member->GetSession()->SendPacket(&data);
                }
            }
        }

        const uint32 GetAmountToSpawn() const { return _AmountToSpawn; }
        void SetAmountToSpawn(uint32 value) { _AmountToSpawn = value; }
        const uint32 GetWaveTotalAmount() const { return _WaveTotal; }
        void SetWaveTotalAmount(uint32 value) { _WaveTotal = value; }

    private:
        uint32 _AmountToSpawn;
        uint32 _WaveTotal;
};

class zombie_start_with_invisible_aura : public BasicEvent
{
    public:
        zombie_start_with_invisible_aura(Creature* zombie) : _zombie(zombie) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _zombie->RemoveAurasDueToSpell(SPELL_AURA_INVISIBLE);
            _zombie->AI()->DoAction(ACTION_ZOMBIE_EMERGE_VISUAL);
            return true;
        }

    private:
        Creature* _zombie;
};

class zombie_start_moving_after_emerge : public BasicEvent
{
    public:
        zombie_start_moving_after_emerge(Creature* zombie) : _zombie(zombie) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _zombie->AI()->DoAction(ACTION_ZOMBIE_CAN_START_MOVING_AFTER_EMERGE);
            return true;
        }

    private:
        Creature* _zombie;
};

class zombie_spawnpoint_start_spawning_again : public BasicEvent
{
    public:
        zombie_spawnpoint_start_spawning_again(Creature* spawnpoint) : _spawnpoint(spawnpoint) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _spawnpoint->AI()->DoAction(ACTION_SPAWNPOINT_NO_LONGER_BLOWN_UP);
            return true;
        }

    private:
        Creature* _spawnpoint;
};

class zombie_barricade_anvil_spawn : public BasicEvent
{
    public:
        zombie_barricade_anvil_spawn(Creature* barricadeTrigger) : _barricadeTrigger(barricadeTrigger) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _barricadeTrigger->SummonCreature(NPC_ANVIL_SPAWNER, _barricadeTrigger->GetPositionX(), _barricadeTrigger->GetPositionY(), _barricadeTrigger->GetPositionZ(), _barricadeTrigger->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            return true;
        }

    private:
        Creature* _barricadeTrigger;
};

class zombie_emerge_after_death_one : public BasicEvent
{
    public:
        zombie_emerge_after_death_one(Creature* zombie) : _zombie(zombie) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _zombie->Respawn(true);
            _zombie->SetReactState(REACT_PASSIVE);
            _zombie->AI()->DoCast(SPELL_EMERGE_VISUAL);
            return true;
        }

    private:
        Creature* _zombie;
};

class zombie_emerge_after_death_two : public BasicEvent
{
    public:
        zombie_emerge_after_death_two(Creature* zombie) : _zombie(zombie) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _zombie->AI()->DoAction(ACTION_ZOMBIE_NO_LONGER_EMERGING);
            _zombie->SetReactState(REACT_AGGRESSIVE);

            if (Player* player = _zombie->FindNearestPlayer(50.0f))
                _zombie->AI()->AttackStart(player);

            return true;
        }

    private:
        Creature* _zombie;
};

class zombie_spawn_two_zombie_random_timer : public BasicEvent
{
    public:
        zombie_spawn_two_zombie_random_timer(Creature* spawnpoint) : _spawnpoint(spawnpoint) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _spawnpoint->AI()->DoAction(ACTION_SPAWNPOINT_SPAWN_ZOMBIES);
            return true;
        }

    private:
        Creature* _spawnpoint;
};

class zombie_player_resurrects_pet_after_death : public BasicEvent
{
    public:
        zombie_player_resurrects_pet_after_death(Player* player) : _player(player) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _player->CastSpell(_player, SPELL_PLAYER_SUMMON_PET, false); // Summons last used pet if it exists
            return true;
        }

    private:
        Player* _player;
};

class zombie_fire_spawner_makes_spawnpoint_explode : public BasicEvent
{
    public:
        zombie_fire_spawner_makes_spawnpoint_explode(Creature* fireSpawner) : _fireSpawner(fireSpawner) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _fireSpawner->AI()->DoAction(ACTION_FIRE_SPAWNER_MAKE_SPAWNPOINT_EXPLODE);
            return true;
        }

    private:
        Creature* _fireSpawner;
};

class zombie_dies_from_catched_fire : public BasicEvent
{
    public:
        zombie_dies_from_catched_fire(Creature* zombie) : _zombie(zombie) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _zombie->Kill(_zombie, false);
            return true;
        }

    private:
        Creature* _zombie;
};

class zombie_player_visually_resurrects_after_teleport : public BasicEvent
{
    public:
        zombie_player_visually_resurrects_after_teleport(Player* player) : _player(player) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _player->CastSpell(_player, SPELL_RESURRECT_IMPACT_VISUAL, false);
            return true;
        }

    private:
        Player* _player;
};

class zombie_brann_disappears : public BasicEvent
{
    public:
        zombie_brann_disappears(Creature* brann) : _brann(brann) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _brann->AddAura(SPELL_AURA_INVISIBLE, _brann);
            return true;
        }

    private:
        Creature* _brann;
};

class zombie_bomb_bot_explodes_at_spawnpoint : public BasicEvent
{
    public:
        zombie_bomb_bot_explodes_at_spawnpoint(Creature* bombBot) : _bombBot(bombBot) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            if (Creature* spawnpoint = _bombBot->FindNearestCreature(NPC_SPAWNPOINT, 1.0f))
            {
                spawnpoint->AI()->DoAction(ACTION_SPAWNPOINT_EXPLODES);
                _bombBot->CastSpell(_bombBot, SPELL_EXPLOSION, false);
                _bombBot->Kill(_bombBot, false);
                _bombBot->DespawnOrUnsummon(2000);
            }
            else
                _bombBot->DespawnOrUnsummon();

            return true;
        }

    private:
        Creature* _bombBot;
};

class zombie_barricade_repaired : public BasicEvent
{
    public:
        zombie_barricade_repaired(Creature* barricadeTrigger) : _barricadeTrigger(barricadeTrigger) { }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _barricadeTrigger->AI()->DoAction(ACTION_BARRICADE_TRIGGER_REPAIRED);
            return true;
        }

    private:
        Creature* _barricadeTrigger;
};

class npc_zombie : public CreatureScript
{
    public:
        npc_zombie() : CreatureScript("npc_zombie") { }

        struct npc_zombieAI : public ScriptedAI
        {
            npc_zombieAI(Creature* creature) : ScriptedAI(creature)
            {
                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->SetReactState(REACT_PASSIVE);
                emergedAfterDead = false;
                zombieEvent = new ZombieEvent;
            }

            uint8 random;
            uint8 Spawnpoint;
            uint32 AttackBarricadeTimer;
            uint32 TalkTimer;
            uint32 WaitMoveTimer;
            uint32 InfectedBiteTimer;
            uint32 VolatileInfectionTimer;
            bool emerging;
            bool atBarricade;
            bool movingToBarricade;
            bool canStartMoving;
            bool waitingToMove;
            bool barricadeDown;
            bool emergedAfterDead;
            float x1, y1, z1, x2, y2, z2;
            ZombieEvent* zombieEvent;

            void Reset()
            {
                AttackBarricadeTimer = urand(2500, 5000);
                TalkTimer = urand(13000, 600000);
                InfectedBiteTimer = urand(5000, 60000);
                VolatileInfectionTimer = urand(5000, 60000);
                WaitMoveTimer = 0;
                atBarricade = false;
                movingToBarricade = false;
                canStartMoving = false;
                waitingToMove = false;
                barricadeDown = false;
            }

            void DamageTaken(Unit* /*doneBy*/, uint32& damage)
            {
                if (emerging)
                    damage = 0;
            }

            void IsSummonedBy(Unit* summoner)
            {
                // Used in the code for which barricade they should move to, as two spawnpoints can choose between three barricades
                // and we can't do like *if (urand(0, 2) == 0) else if (urand(0, 2) == 1)* as urand would just be ran again since
                // it's not a saved variable.
                switch (urand(0, 2))
                {
                    case 0:
                        random = 0;
                        break;
                    case 1:
                        random = 1;
                        break;
                    case 2:
                        random = 2;
                        break;
                    default:
                        sLog->outError(LOG_FILTER_WORLDSERVER, "ZombieEvent: uint8 random is NULL - notify Discover-");
                        break;
                }

                if (summoner->ToCreature() && summoner->GetEntry() == NPC_SPAWNPOINT)
                {
                    switch (summoner->ToCreature()->GetDBTableGUIDLow())
                    {
                        case 731533:
                            Spawnpoint = 1;
                            x1 = 124.220886f;
                            y1 = 192.905151f;
                            z1 = 93.188019f;

                            if (urand(0, 1) == 0)
                            {
                                x2 = 130.598251f;
                                y2 = 178.558441f;
                                z2 = 94.500107f;
                            }
                            else
                            {
                                x2 = 127.765358f;
                                y2 = 171.822632f;
                                z2 = 93.612465f;
                            }
                            break;
                        case 731534:
                            Spawnpoint = 1;
                            x1 = 112.752060f;
                            y1 = 192.116272f;
                            z1 = 93.085205f;

                            if (urand(0, 1) == 0)
                            {
                                x2 = 130.598251f;
                                y2 = 178.558441f;
                                z2 = 94.500107f;
                            }
                            else
                            {
                                x2 = 127.765358f;
                                y2 = 171.822632f;
                                z2 = 93.612465f;
                            }
                            break;
                        case 731531:
                            Spawnpoint = 2;
                            x1 = 136.569214f;
                            y1 = 196.414810f;
                            z1 = 93.192978f;

                            if (urand(0, 1) == 0)
                            {
                                x2 = 144.764648f;
                                y2 = 179.722046f;
                                z2 = 94.698616f;
                            }
                            else
                            {
                                x2 = 138.071472f;
                                y2 = 182.225525f;
                                z2 = 94.714081f;
                            }
                            break;
                        case 731532:
                            Spawnpoint = 2;
                            x1 = 156.030457f;
                            y1 = 193.531189f;
                            z1 = 93.085213f;

                            if (random == 0)
                            {
                                x2 = 144.764648f;
                                y2 = 179.722046f;
                                z2 = 94.698616f;
                            }
                            else if (random == 1)
                            {
                                x2 = 138.071472f;
                                y2 = 182.225525f;
                                z2 = 94.714081f;
                            }
                            else if (random == 2)
                            {
                                x2 = 149.385010f;
                                y2 = 171.702881f;
                                z2 = 93.965942f;
                            }
                            break;
                        case 731535:
                            Spawnpoint = 3;
                            x1 = 111.250359f;
                            y1 = 143.112091f;
                            z1 = 93.129074f;

                            if (urand(0, 1))
                            {
                                x2 = 130.840195f;
                                y2 = 163.849030f;
                                z2 = 93.412239f;
                            }
                            else
                            {
                                x2 = 127.479897f;
                                y2 = 170.760162f;
                                z2 = 93.524109f;
                            }
                            break;
                        case 731536:
                            Spawnpoint = 3;
                            x1 = 122.720093f;
                            y1 = 138.038513f;
                            z1 = 93.086525f;

                            if (urand(0, 1))
                            {
                                x2 = 130.840195f;
                                y2 = 163.849030f;
                                z2 = 93.412239f;
                            }
                            else
                            {
                                x2 = 127.479897f;
                                y2 = 170.760162f;
                                z2 = 93.524109f;
                            }
                            break;
                        case 731537:
                            Spawnpoint = 4;
                            x1 = 137.364090f;
                            y1 = 139.050125f;
                            z1 = 93.468979f;

                            if (random == 0)
                            {
                                x2 = 138.247574f;
                                y2 = 162.144928f;
                                z2 = 93.229507f;
                            }
                            else if (random == 1)
                            {
                                x2 = 145.918671f;
                                y2 = 164.188110f;
                                z2 = 93.943298f;
                            }
                            else if (random == 2)
                            {
                                x2 = 149.385010f;
                                y2 = 171.702881f;
                                z2 = 93.965942f;
                            }
                            break;
                        case 731538:
                            Spawnpoint = 4;
                            x1 = 153.228806f;
                            y1 = 142.547073f;
                            z1 = 93.085190f;

                            if (random == 0)
                            {
                                x2 = 138.247574f;
                                y2 = 162.144928f;
                                z2 = 93.229507f;
                            }
                            else if (random == 1)
                            {
                                x2 = 145.918671f;
                                y2 = 164.188110f;
                                z2 = 93.943298f;
                            }
                            else if (random == 2)
                            {
                                x2 = 149.385010f;
                                y2 = 171.702881f;
                                z2 = 93.965942f;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }

            void DoAction(int32 const action)
            {
                switch (action)
                {
                    case ACTION_ZOMBIE_CAN_START_MOVING_AFTER_EMERGE:
                        canStartMoving = true;
                        break;
                    case ACTION_ZOMBIE_EMERGE_VISUAL:
                        emerging = true;
                        DoCast(SPELL_EMERGE_VISUAL);
                        break;
                    case ACTION_ZOMBIE_EMERGES_AFTER_DEATH:
                        emerging = true;
                        emergedAfterDead = true;
                        me->m_Events.AddEvent(new zombie_emerge_after_death_one(me), me->m_Events.CalculateTime(1500)); // Respawn & Emerge
                        me->m_Events.AddEvent(new zombie_emerge_after_death_two(me), me->m_Events.CalculateTime(5500)); // Set Aggressive & Attack
                        zombieEvent->SetAmountToSpawn(zombieEvent->GetAmountToSpawn() - 1); // When emerging a second time we also spawn a second time
                        break;
                    case ACTION_ZOMBIE_NO_LONGER_EMERGING:
                        emerging = false;
                        break;
                    default:
                        break;
                }
            }

            void JustDied(Unit* killer)
            {
                if (Creature* counter = me->FindNearestCreature(NPC_KILL_WAVE_COUNTER, 100.0f))
                    counter->AI()->DoAction(ACTION_COUNTER_INCREMENT_COUNTERS);

                if (!emergedAfterDead && urand(0, 19) == 0)
                {
                    DoCast(me, SPELL_ZOMBIE_DIE_EFFECT, true);
                    DoAction(ACTION_ZOMBIE_EMERGES_AFTER_DEATH);
                    return; // We shouldn't despawn or spawn a powerup when emerging a second time
                }

                if (urand(0, 9) == 0) // 10% chance
                    DoSpawnPowerUp();

                DoCast(me, SPELL_ZOMBIE_DIE_EFFECT, true);
                me->DespawnOrUnsummon(2000);
            }

            void DoSpawnPowerUp()
            {
                switch (urand(0, 1))
                {
                    case 0: // Summon power up
                        // Maybe we should use CastSpellOnAllPlayers (or w/e it's called) from instancescript instead
                        me->SummonGameObject(GAMEOBJECT_POWER_UP, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), 0, 0, 0, 0, 120000);
                        break;
                    case 1: // Kill zombies that are currently spawned within X yards
                        if (urand(0, 5) == 0)
                        {
                            std::list<Creature*> ZombieList;
                            GetCreatureListWithEntryInGrid(ZombieList, me, NPC_ZOMBIE, 100.0f); // All zombies
                            for (std::list<Creature*>::iterator itr = ZombieList.begin(); itr != ZombieList.end(); ++itr)
                                (*itr)->Kill((*itr), false);
                        }
                        else
                        {
                            std::list<Creature*> ZombieList;
                            GetCreatureListWithEntryInGrid(ZombieList, me, NPC_ZOMBIE, 10.0f); // Within 10 yards
                            for (std::list<Creature*>::iterator itr = ZombieList.begin(); itr != ZombieList.end(); ++itr)
                                (*itr)->Kill((*itr), false);
                        }
                        break;
                    // Todo: add more cases
                }
            }

            void EnterCombat(Unit* /*who*/) { }

            void EnterEvadeMode() { }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (point)
                {
                    case POINT_MOVE_DOWN_SKULL_PILE:
                        waitingToMove = true;
                        WaitMoveTimer = 100;
                        break;
                    case POINT_MOVE_TO_BARRICADE:
                        if (!me->FindNearestGameObject(GAMEOBJECT_BARRICADE, 1.5f))
                        {
                            barricadeDown = true;
                            me->SetReactState(REACT_AGGRESSIVE);
                        }

                        if (Creature* barricadeTrigger = me->FindNearestCreature(NPC_BARRICADE_TRIGGER, 5.0f))
                            me->SetFacingToObject(barricadeTrigger);

                        movingToBarricade = false;
                        atBarricade = true;
                        break;
                    case POINT_MIDDLE_OF_BARRICADES:
                        me->GetMotionMaster()->MoveRandom(10.0f);
                        break;
                    default:
                        break;
                }
            }

            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                if (!caster->ToCreature())
                    return;

                // Only die if the caster is a bomb bot or proximity mine, the mine should explode and afterwards we should continue walking
                if (spell->Id == SPELL_EXPLOSION && (caster->GetEntry() == NPC_BOMB_BOT || caster->GetEntry() == NPC_PROXIMITY_MINE))
                    me->Kill(me, false);

                // Since we shouldn't regenerate health when a turret attacks us, we'll set ourselves in combat with them
                if (spell->Id == SPELL_RAPID_FIRE && caster->GetEntry() == NPC_TURRET)
                    me->SetInCombatWith(caster);
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();

                // If you are followed by a lot of zombies, it's a possibility to just move into a spawnpoint's fire and kill them all
                if (me->FindNearestGameObject(GAMEOBJECT_SPAWNPOINT_FIRE, 5.0f))
                {
                    // We are not stopping with moving because it looks better if we keep on moving
                    me->AddAura(SPELL_AURA_ZOMBIE_ON_FIRE, me);
                    me->m_Events.AddEvent(new zombie_dies_from_catched_fire(me), me->m_Events.CalculateTime(5000));
                }

                // When we're down our skullpile
                if (waitingToMove)
                {
                    if (WaitMoveTimer <= diff)
                    {
                        me->GetMotionMaster()->MovePoint(POINT_MOVE_TO_BARRICADE, x2, y2, z2);
                        waitingToMove = false;
                    }
                    else WaitMoveTimer -= diff;
                }

                if (TalkTimer <= diff)
                {
                    switch (urand(0, 3))
                    {
                        case 0:
                            me->MonsterSay("Brains... Brains... Brains...", LANG_UNIVERSAL, me->GetGUID());
                            break;
                        case 1:
                            me->MonsterSay("Brains... Brains...", LANG_UNIVERSAL, me->GetGUID());
                            break;
                        case 2:
                            me->MonsterSay("Brains...", LANG_UNIVERSAL, me->GetGUID());
                            break;
                        default:
                            break;
                    }

                    TalkTimer = urand(100000, 900000);
                }
                else
                    TalkTimer -= diff;

                // Start moving to the bottom of our skullpile
                if (canStartMoving && !movingToBarricade && !atBarricade)
                {
                    emerging = false;
                    movingToBarricade = true;
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_DOWN_SKULL_PILE, x1, y1, z1);
                }

                // If barricade is down and we don't have a victim, search
                // for one and attack it.
                if (!UpdateVictim() && barricadeDown)
                    if (Player* player = me->FindNearestPlayer(50.0f))
                        AttackStart(player);

                if (UpdateVictim())
                {
                    if (InfectedBiteTimer <= diff)
                    {
                        if (urand(0, 3))
                            DoCastVictim(SPELL_INFECTED_BITE);

                        InfectedBiteTimer = urand(20000, 120000);
                    }
                    else
                        InfectedBiteTimer -= diff;

                    if (VolatileInfectionTimer <= diff)
                    {
                        if (urand(0, 3))
                            DoCastVictim(SPELL_VOLATILE_INFECTION);

                        VolatileInfectionTimer = urand(20000, 120000);
                    }
                    else
                        VolatileInfectionTimer -= diff;

                    DoMeleeAttackIfReady();
                }

                // This is at the bottom of UpdateAI because of the return
                if (atBarricade)
                {
                    movingToBarricade = false;

                    if (!me->FindNearestGameObject(GAMEOBJECT_BARRICADE, 3.0f))
                    {
                        barricadeDown = true;

                        if (Player* player = me->FindNearestPlayer(50.0f))
                            AttackStart(player);

                        return;
                    }

                    if (AttackBarricadeTimer <= diff)
                    {
                        if (Creature* barricadeTrigger = me->FindNearestCreature(NPC_BARRICADE_TRIGGER, 8.0f))
                            barricadeTrigger->AI()->DoAction(ACTION_BARRICADE_TRIGGER_INCR_HIT_COUNTER);

                        DoCast(RAND(SPELL_VISUAL_ATTACK_1H, SPELL_VISUAL_ATTACK_2H));
                        AttackBarricadeTimer = urand(2500, 5000);
                    }
                    else
                        AttackBarricadeTimer -= diff;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombieAI(creature);
        }
};

class npc_zombie_brann : public CreatureScript
{
    public:
        npc_zombie_brann() : CreatureScript("npc_zombie_brann") { }
 
        struct npc_zombie_brannAI : public ScriptedAI
        {
            npc_zombie_brannAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                //me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP); //Do this from the db
            }

            bool canStartIntro;
            bool canStartOutro;
            uint8 Step;
            uint32 StepTimer;
            std::list<Creature*> SpawnpointList;

            void Reset()
            {
                canStartIntro = false;
                canStartOutro = false;
                //outroductionGossip = false;
                Step = 0;
                StepTimer = 0;

                std::list<Creature*> RisenConstructList;
                GetCreatureListWithEntryInGrid(RisenConstructList, me, NPC_RISEN_CONSTRUCT, 100.0f);
                for (std::list<Creature*>::iterator itr = RisenConstructList.begin(); itr != RisenConstructList.end(); ++itr)
                {
                    (*itr)->AddAura(SPELL_AURA_INVISIBLE, (*itr));
                    (*itr)->Kill((*itr), false);
                }

                if (Creature* rattlegore = me->FindNearestCreature(NPC_RATTLEGORE, 15.0f))
                {
                    rattlegore->AddAura(SPELL_AURA_INVISIBLE, rattlegore);
                    rattlegore->Kill(rattlegore, false);
                }
            }

            void DoAction(int32 const action)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    return;

                switch (action)
                {
                    case ACTION_BRANN_START_INTRODUCTION:
                        canStartIntro = true;
						me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
						me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
						me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_REPAIR);
                        break;
                    case ACTION_BRANN_INTRODUCTION_FINISHED:
                        canStartIntro = false;
                        Step = 0;
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
						me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
						me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_REPAIR);
                        GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 100.0f);
                        for (std::list<Creature*>::iterator itr = SpawnpointList.begin(); itr != SpawnpointList.end(); ++itr)
                            (*itr)->AI()->DoAction(ACTION_SPAWNPOINT_CAN_START_SUMMONING);

                        // This is because we don't want players to get in the revive
                        // queue while Brann is doing his introduction. They get instantly
                        // resurrected during the introduction.
                        if (Creature* spiritGuide = me->FindNearestCreature(NPC_SPIRIT_GUIDE, 50.0f))
                            spiritGuide->AI()->DoAction(ACTION_SPIRIT_GUIDE_INTRODUCTION_OVER);

                        // Go invisible after 1.5 seconds - this is to prevent the instancescript
                        // to summon a new Brann each time a player enters and Brann already despawned
                        me->m_Events.AddEvent(new zombie_brann_disappears(me), me->m_Events.CalculateTime(8500));

                        summons.DespawnAll();
                        break;
                    case ACTION_BRANN_EVENT_FINISHED:
                        canStartIntro = false;
                        canStartOutro = true;
                        Step = 100;
                        GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 100.0f);
                        for (std::list<Creature*>::iterator itr = SpawnpointList.begin(); itr != SpawnpointList.end(); ++itr)
                            (*itr)->AI()->DoAction(ACTION_SPAWNPOINT_STOP_SPAWNING);

                        std::list<Creature*> ZombieList;
                        GetCreatureListWithEntryInGrid(ZombieList, me, NPC_ZOMBIE, 100.0f);
                        for (std::list<Creature*>::iterator itr = ZombieList.begin(); itr != ZombieList.end(); ++itr)
                            (*itr)->DespawnOrUnsummon(urand(0, 1000)); // Don't use Kill because it shouldn't count as players killing them, they just disappear

                        summons.DespawnAll();
                        break;
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
            }

            void JumpToNextStep(uint32 timer)
            {
                StepTimer = timer;
                Step++;
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                {
                    me->DespawnOrUnsummon();
                    return;
                }

                if (canStartIntro || canStartOutro)
                {
                    if (StepTimer <= diff)
                    {
                        switch (Step)
                        {
                              //////////////////
                             // INTRODUCTION //
                            //////////////////
                            case 0:
                                JumpToNextStep(7000);
                                break;
                            case 1:
                                me->MonsterSay("Knock knock! Are we all here yet?", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                                JumpToNextStep(15000);
                                break;
                            case 2:
                                me->MonsterSay("Welcome to the Zombie Event, fellas. My name is Brann and I will explain and run you through how this event works, what you can expect and how to use certain parts of this mini-game. If this is not your first time in here, please let the group leader talk to me and we will skip this introduction!", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
                                JumpToNextStep(8000);
                                break;
                            case 3:
                                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                JumpToNextStep(16000);
                                break;
                            case 4:
                                me->MonsterSay("Alright, let's get started!", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                                JumpToNextStep(5000);
                                break;
                            case 5:
                                me->MonsterSay("First of all, this event may cause lag due to a high amount of zombies spawned at the same time at the same place. If you have a bad computer, we do not suggest you participate in this event.", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(15000);
                                break;
                            case 6:
                                me->MonsterSay("During the event, a bunch of zombies will spawn constantly. A wave is a specific amount of zombies that you have to kill each time to achieve the next wave. Each time you complete a wave, a bigger amount of zombies will spawn, zombies will spawn faster and there is a chance that there spawn more than one zombies at a time. Each wave you reach grants you a Wave Token.", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(24000);
                                break;
                            case 7:
                                me->MonsterSay("When killing a Zombie, it has a low chance of respawning. It will then emerge a second time and attack its closest target. Zombies that you will encounter during the event will look like either one of these:", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(4000);
                                break;
                            case 8:
                                me->SummonCreature(NPC_ZOMBIE_INTRO_ONE, 137.514130f, 168.905182f, 95.146439f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_ZOMBIE_INTRO_TWO, 137.339874f, 170.526840f, 95.606285f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_ZOMBIE_INTRO_THREE, 137.090836f, 172.844498f, 95.753166f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_ZOMBIE_INTRO_FOUR, 136.841064f, 175.169113f, 95.494354f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 137.514130f, 168.905182f, 95.146439f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 137.339874f, 170.526840f, 95.606285f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 137.090836f, 172.844498f, 95.753166f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 136.841064f, 175.169113f, 95.494354f, 3.248633f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                JumpToNextStep(9000);
                                break;
                            case 9:
                                me->MonsterSay("Even thought it seems like an impossible task at some point, there is no reason to be afraid. There are a few so-called power-ups like land mines, bomb bots and the classic Berserking buff from Warsong Gulch.", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(17000);
                                break;
                            case 10:
                                me->MonsterSay("The Bomb-Bots will randomly spawn after wave two. Only one single bomb-bot spawns each time. It moves to a spawnpoint, explodes after a few seconds and the spawnpoint will stop spawning for a minute. The Bomb-Bot looks like this:", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(3000);
                                break;
                            case 11:
                                me->SummonCreature(NPC_BOMB_BOT, 138.159210f, 172.177246f, 95.829353f, 4.924521f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.159210f, 172.177246f, 95.929353f, 4.924521f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                JumpToNextStep(14000);
                                break;
                            case 12:
                                me->MonsterSay("Land Mines are a completely different story. You can spawn these yourselves. The Land Mine looks like this:", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(2000);
                                break;
                            case 13:
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.159210f, 172.177246f, 95.829353f, 4.924521f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_PROXIMITY_MINE, 138.159210f, 172.177246f, 95.829353f, 4.924521f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                JumpToNextStep(9000);
                                break;
                            case 14:
                                me->MonsterSay("You are able to leave the event anytime you want. This can be simply done by moving over to that portal over there,", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(5000);
                                break;
                            case 15:
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 97.0955f, 167.837f, 95.661186f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SetFacingTo(3.405779f);
                                JumpToNextStep(500);
                                break;
                            case 16:
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(2500);
                                break;
                            case 17:
                                me->MonsterSay("right clicking it and telling it you want to leave the Zombie Event. You must however realize that when you press the option of leaving the event, you will not get a reward, unlike your group mates.", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(2500);
                                break;
                            case 18:
                                me->SetFacingTo(0.005004f);
                                JumpToNextStep(7500);
                                break;
                            case 19:
                                me->MonsterSay("When you die, you will be teleported to a point infront of the Spirit Guide. This Spirit Guide does a global resurrection every two minutes. Once everyone in your group is death at the same time, you lose the event. Please note you can not resurrect each other.", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(19000);
                                break;
                            case 20:
                                me->MonsterSay("Everytime a zombie spawns, it will move to a random barricade and 'attack' it. After 20 hits, the barricade will despawn and the zombie will attack you.", LANG_UNIVERSAL, me->GetGUID());
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 137.948f, 180.109f, 94.9475f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 132.089f, 177.643f, 94.9177f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 147.688f, 171.9f, 94.3889f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 144.728f, 166.243f, 94.4193f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.396f, 164.123f, 93.7887f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 131.517f, 165.805f, 93.6756f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 129.25f, 171.311f, 94.1663f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 144.317f, 177.753f, 94.8725f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                JumpToNextStep(8000);
                                break;
                            case 21:
                                me->MonsterSay("However! When a barricade is broken down you are able to repair it. An anvil will spawn after 15 seconds, which will summon a goblin that repairs your barricade if you right click on the anvil. The anvil will look like this:", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(8000);
                                break;
                            case 22:
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);

                                if (Creature* arrow = me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.159210f, 172.177246f, 95.829353f, 4.924521f, TEMPSUMMON_TIMED_DESPAWN, 8000))
                                    arrow->SummonGameObject(GAMEOBJECT_ANVIL_INTRO, 138.159210f, 172.177246f, 95.829353f, 4.924521f, 4.924521f, 4.924521f, 4.924521f, 4.924521f, 8000);
                                JumpToNextStep(9000);
                                break;
                            case 23:
                                me->MonsterSay("But you must realize that when an anvil is untouched for 30 seconds after spawning, it will remove itself and the barricade will be gone forever!", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(8000);
                                break;
                            case 24:
                                me->MonsterSay("When a barricade is down, several zombies will move into your base and start spreading stackable diseases and infections, dealing a lot of damage to you and your group, so remember to repair barricades as fast as you can in order to keep those barricades up!", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                                JumpToNextStep(17000);
                                break;
                            case 25:
                                me->MonsterSay("The next point I'd like to discuss are turrets and vehicles. In the event there is a turret and a vehicle.", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(7000);
                                break;
                            case 26:
                                me->MonsterSay("The turret shoots each 5 seconds to all zombies that are in front of the turret, damaging them for 25% of their healthpoints. The turret looks like this:", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(500);
                                break;
                            case 27:
                                me->SummonCreature(NPC_TURRET, 138.159210f, 172.177246f, 95.829353f, 0.075471f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.159210f, 172.177246f, 95.829353f, 0.075471f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                JumpToNextStep(9000);
                                break;
                            case 28:
                                me->MonsterSay("The vehicle, however, is able to be possessed. It allows you to shoot at a so-called 'spawnpoint', making it stop spawning zombies for a couple of minutes. The vehicle looks like this:", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(1500);
                                break;
                            case 29:
                                me->SummonCreature(NPC_ZOMBIE_VEHICLE, 138.159210f, 172.177246f, 95.829353f, 0.075471f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.159210f, 172.177246f, 95.829353f, 0.075471f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                 JumpToNextStep(9000);
                                break;
                            case 30:
                                me->MonsterSay("If you able to get past the gate and the invisible walls behind the gate, you will be teleported back here by the Keep Out creature. It looks like this:", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                JumpToNextStep(1500);
                                break;
                            case 31:
                                me->SummonCreature(NPC_KEEP_OUT, 138.159210f, 172.177246f, 97.467354f, 3.103177f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                me->SummonCreature(NPC_INTRODUCTION_ARROW, 138.159210f, 172.177246f, 97.467354f, 3.103177f, TEMPSUMMON_TIMED_DESPAWN, 8000);
                                 JumpToNextStep(9000);
                                break;
                            case 32:
                                me->MonsterSay("That's all for now. If you have questions, you're in bad luck because the event is about to start!", LANG_UNIVERSAL, me->GetGUID());
                                JumpToNextStep(8000);
                                break;
                            case 33:
                                me->MonsterSay("The event will be started in approximately ten (10) seconds from now on. I wish you the best of luck and remember to have fun!", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
                                JumpToNextStep(3000);
                                break;
                            case 34:
                                me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                                JumpToNextStep(1000);
                                break;
                            case 35:
                                DoAction(ACTION_BRANN_INTRODUCTION_FINISHED);
                                break;
                              //////////////////
                             // OUTRODUCTION //
                            //////////////////
                            case 100:
                                if (me->HasAura(SPELL_AURA_INVISIBLE))
                                    me->RemoveAurasDueToSpell(SPELL_AURA_INVISIBLE);

                                JumpToNextStep(1500);
                                break;
                            case 101:
                                me->MonsterSay("Hello again!", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                                JumpToNextStep(8000);
                                break;
                            case 102:
                                me->MonsterSay("So I was told you guys had all died during the event. Is that right?", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
                                JumpToNextStep(8000);
                                break;
                            case 103:
                                // Todo: Brann rewards?
                                me->MonsterSay("Oh well, it doesn't matter a lot anyway. As long as you had some fun, don't you think? I shall reward you now!", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                                JumpToNextStep(8000);
                                break;
                            case 104:
                                me->MonsterSay("Let's see. As I have told you during my introduction, you have gotten one so-called Wave Token for each wave you reached.", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                JumpToNextStep(9000);
                                break;
                            case 105:
                                me->MonsterSay("These Wave Tokens can be exchanged for great rewards.", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                //outroductionGossip = true;
                                JumpToNextStep(8000);
                                break;
                            case 106:
                                me->MonsterSay("So go ahead and talk to me in order to exchange your tokens for rewards.", LANG_UNIVERSAL, me->GetGUID());
                                me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                JumpToNextStep(2000);
                                break;
                            case 107:
                                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
								me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR);
                                JumpToNextStep(5000);
                                break;
                            default:
                                break;
                        }
                    }
                    else
                        StepTimer -= diff;
                }
            }

            private:
                SummonList summons;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_brannAI(creature);
        }

        bool DespawnFromList(std::list<Creature*>& _list)
        {
            for (std::list<Creature*>::iterator itr = _list.begin(); itr != _list.end(); ++itr)
                if ((*itr) && (*itr)->ToCreature())
                    (*itr)->DespawnOrUnsummon();

            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                return true;

            std::list<Creature*> despawnList;
			if(debug){
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Me and my group are new and have never been here before, I would like an introduction.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Me and my group have already been here before and would like to skip your indroduction.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm very sorry but only the leader of the group can start the event.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'd like to exchange my Wave Tokens for rewards.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You don't have any spin tokens to exchange.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
					player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
			return true;
			}
			if (Group* group = player->GetGroup())
            {
				if(!EVENT_ENDED){
                    if (group->GetLeaderGUID() == player->GetGUID()){

					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Me and my group are new and have never been here before, I would like an introduction.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Me and my group have already been here before and would like to skip your indroduction.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
					}
                    else
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm very sorry but only the leader of the group can start the event.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
					}else
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You guys did great.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    if (player->HasItemCount(ITEM_WAVE_TOKEN, 1))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'd like to exchange my Wave Tokens for rewards.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    else
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You don't have any spin tokens to exchange.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            }
            else{

				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need to be in a group to start the event.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
				 if (player->HasItemCount(ITEM_WAVE_TOKEN, 1))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'd like to exchange my Wave Tokens for rewards.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    else
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You don't have any spin tokens to exchange.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
			}

            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
			WorldSession * m_session = player->GetSession();

            if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                return true;

            switch (action)
            {
                case GOSSIP_ACTION_INFO_DEF + 1:
                    creature->AI()->DoAction(ACTION_BRANN_INTRODUCTION_FINISHED);
                    creature->MonsterSay("The introduction has been skipped. The event will start in ten seconds from now on! Good luck!", LANG_UNIVERSAL, creature->GetGUID());
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case GOSSIP_ACTION_INFO_DEF + 2:
						player->vendorLoader = VENDOR_ID;
						m_session->SendListCustomInventory(creature->GetGUID(), VENDOR_ID);
						player->PlayerTalkClass->SendCloseGossip();
                case GOSSIP_ACTION_INFO_DEF + 3:
                case GOSSIP_ACTION_INFO_DEF + 4:
                case GOSSIP_ACTION_INFO_DEF + 5:
                case GOSSIP_ACTION_INFO_DEF + 6:
                case GOSSIP_ACTION_INFO_DEF + 7:
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
				case GOSSIP_ACTION_INFO_DEF + 8:
					creature->AI()->DoAction(ACTION_BRANN_START_INTRODUCTION);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                default:
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
            }

            return true;
        }
};

class npc_zombie_introduction : public CreatureScript
{
    public:
        npc_zombie_introduction() : CreatureScript("npc_zombie_introduction") { }

        struct npc_zombie_introductionAI : public ScriptedAI
        {
            npc_zombie_introductionAI(Creature* creature) : ScriptedAI(creature) { }

            uint32 AttackTimer;

            void Reset()
            {
                AttackTimer = urand(1000, 3000);
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();

                if (AttackTimer <= diff)
                {
                    DoCast(RAND(SPELL_VISUAL_ATTACK_1H, SPELL_VISUAL_ATTACK_2H));
                    AttackTimer = urand(1000, 3000);
                }
                else
                    AttackTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_introductionAI(creature);
        }
};

class npc_zombie_wave_kill_counter : public CreatureScript
{
    public:
        npc_zombie_wave_kill_counter() : CreatureScript("npc_zombie_wave_kill_counter") { }

        struct npc_zombie_wave_kill_counterAI : public ScriptedAI
        {
            npc_zombie_wave_kill_counterAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                zombieEvent = new ZombieEvent;
            }

            uint32 WaveCounter;
            uint32 KillCounter;
            uint32 AmountToSpawn;
            ZombieEvent* zombieEvent;

            void InitializeAI()
            {
                zombieEvent->SetWaveTotalAmount(20); // First wave always starts with 20 zombies
            }

            void Reset()
            {
                KillCounter = 0;
                WaveCounter = 0;
                AmountToSpawn = 0;
            }

            void DoAction(int32 const action)
            {
                if (action == ACTION_COUNTER_INCREMENT_COUNTERS)
                {
                    KillCounter++;

                    // If next wave is reached
                    if (KillCounter >= zombieEvent->GetWaveTotalAmount())
                        ReachedNextWave();
                }
            }

            void ReachedNextWave()
            {
                WaveCounter++;
                KillCounter = 0;
                
                switch (urand(0, 4))
                {
                    case 0: case 1:
                        me->SummonCreature(NPC_BOMB_BOT, 138.790329f, 172.884232f, 95.752052f, 3.118893f);
                        break;
                    case 2: case 3: case 4:
                        // TODO: Implement Proximity Mine spawner here
                        break;
                }

                // Give all players a so-called 'Wave Token' when they reach the next wave
                if (Player* player = me->SelectNearestPlayer(100.0f))
                {
                    if (!player->isGameMaster())
                    {
                        if (Group* group = player->GetGroup())
                        {
                            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                            {
                                if (Player* member = itr->getSource())
                                {
                                    if (member && member->GetSession() && member->IsInWorld())
                                    {
                                        member->AddItem(ITEM_WAVE_TOKEN, 1);
                                    }
                                }
                            }
                        }
                        else
                            player->AddItem(ITEM_WAVE_TOKEN, 1);
                    }
                }

                std::list<Creature*> SpawnpointList;
                GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 100.0f);
                for (std::list<Creature*>::iterator itr = SpawnpointList.begin(); itr != SpawnpointList.end(); ++itr)
                    (*itr)->AI()->SetData(0, WaveCounter);

                // We should not make it too hard on the players participating on below or at wave 5
                if (WaveCounter <= 5)
                {
                    AmountToSpawn = zombieEvent->GetWaveTotalAmount() + ((WaveCounter * urand(7, 10)) * 2);
                    zombieEvent->SetAmountToSpawn(AmountToSpawn);
                    zombieEvent->SetWaveTotalAmount(zombieEvent->GetAmountToSpawn());

                    if (Player* player = me->SelectNearestPlayer(100.0f))
                        zombieEvent->SendMessageToGroup(player, "You've reached the next wave!");
                }
                // Between wave 6 and 10
                else if (WaveCounter > 5 && WaveCounter <= 10)
                {
                    AmountToSpawn = zombieEvent->GetWaveTotalAmount() + ((WaveCounter * urand(9, 12)) * 2);
                    std::list<Creature*> SpawnpointList;
                    GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 100.0f);
                    for (std::list<Creature*>::iterator itr = SpawnpointList.begin(); itr != SpawnpointList.end(); ++itr)
                        (*itr)->AI()->DoAction(ACTION_SPAWNPOINT_CAN_SUMMON_TWO_AT_ONCE);

                    zombieEvent->SetAmountToSpawn(AmountToSpawn);
                    zombieEvent->SetWaveTotalAmount(zombieEvent->GetAmountToSpawn());

                    if (Player* player = me->SelectNearestPlayer(100.0f))
                        zombieEvent->SendMessageToGroup(player, "You've reached the next wave!");
                }
                // Between wave 11 and 20
                else if (WaveCounter > 10 && WaveCounter <= 20)
                {
                    AmountToSpawn = zombieEvent->GetWaveTotalAmount() + ((WaveCounter * urand(11, 14)) * 2);
                    std::list<Creature*> SpawnpointList;
                    GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 100.0f);
                    for (std::list<Creature*>::iterator itr = SpawnpointList.begin(); itr != SpawnpointList.end(); ++itr)
                        (*itr)->AI()->DoAction(ACTION_SPAWNPOINT_CAN_SUMMON_THREE_AT_ONCE);

                    zombieEvent->SetAmountToSpawn(AmountToSpawn);
                    zombieEvent->SetWaveTotalAmount(zombieEvent->GetAmountToSpawn());

                    if (Player* player = me->SelectNearestPlayer(100.0f))
                        zombieEvent->SendMessageToGroup(player, "You've reached the next wave! Spawnpoints will now have a chance to summon three zombies at once.");
                }

                uint8 t = urand(0, MAX_TURRET_CANNON_POINTS);

                switch (urand(0, 1))
                {
                    case 0:
                        me->SummonCreature(NPC_TURRET, TurretCannonPlacePoints[t].GetPositionX(), TurretCannonPlacePoints[t].GetPositionY(), TurretCannonPlacePoints[t].GetPositionZ(), TurretCannonPlacePoints[t].GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 120000);
                        break;
                    case 1:
                        if (Creature* cannonSpawner = me->SummonCreature(NPC_CANNON_SPAWNER, me->GetPositionX(), me->GetPositionZ(), me->GetPositionY(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 120000))
                            cannonSpawner->SummonGameObject(GAMEOBJECT_CANNON, TurretCannonPlacePoints[t].GetPositionX(), TurretCannonPlacePoints[t].GetPositionY(), TurretCannonPlacePoints[t].GetPositionZ(), TurretCannonPlacePoints[t].GetOrientation(), TurretCannonPlacePoints[t].GetOrientation(), TurretCannonPlacePoints[t].GetOrientation(), TurretCannonPlacePoints[t].GetOrientation(), TurretCannonPlacePoints[t].GetOrientation(), 120000);
                        break;
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_wave_kill_counterAI(creature);
        }
};

class npc_zombie_barricade_trigger : public CreatureScript
{
    public:
        npc_zombie_barricade_trigger() : CreatureScript("npc_zombie_barricade_trigger") { }

        struct npc_zombie_barricade_triggerAI : public ScriptedAI
        {
            npc_zombie_barricade_triggerAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                zombieEvent = new ZombieEvent;
            }

            bool broken;
            uint8 HitCounter;
            uint32 TestTimer;
            ZombieEvent* zombieEvent;

            void Reset()
            {
                broken = false;
                TestTimer = 5000;
                HitCounter = 0;

                if (!me->FindNearestGameObject(GAMEOBJECT_BARRICADE, 1.0f))
                    me->SummonGameObject(GAMEOBJECT_BARRICADE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), 60000);
            }

            void DoAction(int32 const action)
            {
                switch (action)
                {
                    case ACTION_BARRICADE_TRIGGER_INCR_HIT_COUNTER:
                        if (broken)
                            break;

                        HitCounter++;

                        if (HitCounter == 20)
                        {
                            Player* player = me->SelectNearestPlayer(80.0f);
                            HitCounter = 0;
                            broken = true;

                            if (player)
                                zombieEvent->SendMessageToGroup(player, "Barricade down over at the arrow point! An anvil to repair this barricade will be spawned within 15 seconds.");

                            me->SummonCreature(NPC_INTRODUCTION_ARROW, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 15000);
                            me->m_Events.AddEvent(new zombie_barricade_anvil_spawn(me), me->m_Events.CalculateTime(15000));

                            if (GameObject* barricade = me->FindNearestGameObject(GAMEOBJECT_BARRICADE, 1.0f))
                            {
                                barricade->Delete();
                                barricade->DeleteFromDB();
                            }
                        }
                        break;
                    case ACTION_BARRICADE_TRIGGER_REPAIRED:
                        broken = false;
                        me->SummonGameObject(GAMEOBJECT_BARRICADE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), 60000);

                        if (Creature* anvilSpawner = me->FindNearestCreature(NPC_ANVIL_SPAWNER, 1.0f))
                            anvilSpawner->DespawnOrUnsummon();
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                {
                    if (GameObject* barricade = me->FindNearestGameObject(GAMEOBJECT_BARRICADE, 1.0f))
                    {
                        barricade->Delete();
                        barricade->DeleteFromDB();
                    }

                    me->DespawnOrUnsummon();
                    return;
                }

                if (me->FindNearestGameObject(GAMEOBJECT_BARRICADE, 0.5f))
                    broken = false;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_barricade_triggerAI(creature);
        }
};

class npc_zombie_anvil_spawner : public CreatureScript
{
    public:
        npc_zombie_anvil_spawner() : CreatureScript("npc_zombie_anvil_spawner") { }

        struct npc_zombie_anvil_spawnerAI : public ScriptedAI
        {
            npc_zombie_anvil_spawnerAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
            }

            uint32 DespawnTimer;

            void IsSummonedBy(Unit* summon)
            {
                if (Creature* summoner = summon->ToCreature())
                {
                    if (summoner->GetEntry() == NPC_BARRICADE_TRIGGER)
                    {
                        DespawnTimer = 30000;
                        me->SummonGameObject(GAMEOBJECT_ANVIL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), me->GetOrientation(), 5000);
                    }
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();

                if (DespawnTimer <= diff)
                    me->DespawnOrUnsummon();
                else
                    DespawnTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_anvil_spawnerAI(creature);
        }
};

class npc_zombie_spawnpoint : public CreatureScript
{
    public:
        npc_zombie_spawnpoint() : CreatureScript("npc_zombie_spawnpoint") { }

        struct npc_zombie_spawnpointAI : public ScriptedAI
        {
            npc_zombie_spawnpointAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                zombieEvent = new ZombieEvent;
            }

            ZombieEvent* zombieEvent;
            uint8 WaveCounter;
            uint32 SummonTimer;
            bool canSummonThree;
            bool canSummonTwo;
            bool canSummon;
            bool onFire;
            float x, y, z;

            void Reset()
            {
                WaveCounter = 0;
                canSummonThree = false;
                canSummonTwo = false;
                canSummon = false;
                onFire = false;
                SummonTimer = urand(15000, 19000); // after a while the summons will be completely different from other spawnpoints
            }

            void SetData(uint32 type, uint32 data)
            {
                WaveCounter = data;
            }

            void DoAction(int32 const action)
            {
                switch (action)
                {
                    case ACTION_SPAWNPOINT_CAN_START_SUMMONING:
                        canSummon = true;
                        break;
                    case ACTION_SPAWNPOINT_EXPLODES:
                        if (onFire)
                            break;

                        onFire = true;
                        canSummon = false;
                        me->AddAura(SPELL_AURA_BLOWN_UP, me);
                        me->m_Events.AddEvent(new zombie_spawnpoint_start_spawning_again(me), me->m_Events.CalculateTime(125000));
                        break;
                    case ACTION_SPAWNPOINT_NO_LONGER_BLOWN_UP:
                        onFire = false;
                        canSummon = true;
                        me->RemoveAurasDueToSpell(SPELL_AURA_BLOWN_UP);

                        if (Creature* fireSpawner = me->FindNearestCreature(NPC_FIRE_SPAWNER, 1.0f))
                            fireSpawner->DespawnOrUnsummon();
                        break;
                    case ACTION_SPAWNPOINT_CAN_SUMMON_TWO_AT_ONCE:
                        canSummonTwo = true;
                        break;
                    case ACTION_SPAWNPOINT_CAN_SUMMON_THREE_AT_ONCE:
                        canSummonTwo = false;
                        canSummonThree = true;
                        break;
                    case ACTION_SPAWNPOINT_SPAWN_ZOMBIES:
                        SpawnZombie();
                        break;
                    case ACTION_SPAWNPOINT_STOP_SPAWNING:
                        canSummon = false;
                        canSummonTwo = false;
                        canSummonThree = false;

                        // Remove fire in case we have it
                        DoAction(ACTION_SPAWNPOINT_NO_LONGER_BLOWN_UP);
                        break;
                    default:
                        break;
                }
            }

            void SpawnZombie()
            {
			if(EVENT_ENDED == false){
                if (!canSummon)
                    return;

                if (zombieEvent->GetAmountToSpawn() <= 0)
                    return;

                z = me->GetPositionZ();

                switch (me->GetDBTableGUIDLow())
                {
                    case 731531: case 731537: case 731536: // Small skull piles
                        x = me->GetPositionX() + irand(-3, 3);
                        y = me->GetPositionY() + irand(-3, 3);
                        break;
                    case 731533: case 731534: case 731535: // Medium skull piles
                        x = me->GetPositionX() + irand(-4, 4);
                        y = me->GetPositionY() + irand(-4, 4);
                        break;
                    case 731532: case 731538: // Big skull piles
                        x = me->GetPositionX() + irand(-5.5, 5.5);
                        y = me->GetPositionY() + irand(-5.5, 5.5);
                        break;
                }

                if (Creature* zombie = me->SummonCreature(NPC_ZOMBIE, x, y, z, me->GetOrientation()))
                {
                    zombie->AI()->DoCast(SPELL_AURA_INVISIBLE); // Removed after 5 sec - this is so players wont see the falling effect
                    zombie->m_Events.AddEvent(new zombie_start_with_invisible_aura(zombie), zombie->m_Events.CalculateTime(5000));
                    zombie->m_Events.AddEvent(new zombie_start_moving_after_emerge(zombie), zombie->m_Events.CalculateTime(9000));
                    zombieEvent->SetAmountToSpawn(zombieEvent->GetAmountToSpawn() - 1);
				  }
				}
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    return;

                if (canSummon)
                {
                    if (SummonTimer <= diff)
                    {
                        // The reason we use BasicEvents here is because we want to seperate the zombie spawns if we summon more than one at the same time
                        if (!canSummonTwo && !canSummonThree)
                            SpawnZombie();
                        else if (canSummonTwo && !canSummonThree)
                        {
                            if (urand(0, 2) == 0)
                                for (uint8 i = 0; i < 2; i++)
                                    me->m_Events.AddEvent(new zombie_spawn_two_zombie_random_timer(me), me->m_Events.CalculateTime(urand(0, urand(3000, 6000))));
                            else
                                SpawnZombie();
                        }
                        else if (canSummonThree && !canSummonTwo)
                        {
                            if (urand(0, 2) == 0)
                            {
                                for (uint8 i = 0; i < 3; i++)
                                    me->m_Events.AddEvent(new zombie_spawn_two_zombie_random_timer(me), me->m_Events.CalculateTime(urand(0, urand(3000, 6000))));
                            }
                            else
                                SpawnZombie();
                        }

                        switch (WaveCounter)
                        {
                            case 0: case 1:
                                SummonTimer = urand(15000, 20000);
                                break;
                            case 2: case 3:
                                SummonTimer = urand(10000, 15000);
                                break;
                            case 4: case 5:
                                SummonTimer = urand(8000, 12000);
                                break;
                            default: // Anything above wavecounter 5 is unlikely but possible
                                SummonTimer = urand(5000, 10000);
                                break;
                        }
                    }
                    else
                        SummonTimer -= diff;
                }
            }
        };
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_spawnpointAI(creature);
        }
};

class npc_zombie_fire_spawner : public CreatureScript
{
    public:
        npc_zombie_fire_spawner() : CreatureScript("npc_zombie_fire_spawner") { }

        struct npc_zombie_fire_spawnerAI : public ScriptedAI
        {
            npc_zombie_fire_spawnerAI(Creature* creature) : ScriptedAI(creature) { }

            void DoAction(int32 const action)
            {
                if (action == ACTION_FIRE_SPAWNER_MAKE_SPAWNPOINT_EXPLODE)
                {
                    if (Creature* spawnpoint = me->FindNearestCreature(NPC_SPAWNPOINT, 1.0f))
                    {
                        if (!spawnpoint->HasAura(SPELL_AURA_BLOWN_UP))
                        {
                            spawnpoint->AI()->DoAction(ACTION_SPAWNPOINT_EXPLODES);
                            me->SummonGameObject(GAMEOBJECT_SPAWNPOINT_FIRE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 12000);
                        }
                    }
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_fire_spawnerAI(creature);
        }
};

class npc_zombie_spirit_guide : public CreatureScript
{
    public:
        npc_zombie_spirit_guide() : CreatureScript("npc_zombie_spirit_guide") { }

        struct npc_zombie_spirit_guideAI : public ScriptedAI
        {
            npc_zombie_spirit_guideAI(Creature* creature) : ScriptedAI(creature)
            {
                zombieEvent = new ZombieEvent;
            }
            
            bool eventFailed;
            bool introduction;
            bool canRessurrect;
            bool one, two, three, four;
            ZombieEvent* zombieEvent;
            uint32 ResurrectionTimer;
            uint32 DebugOutputTestTimer;
            std::list<Player*> revive_queue;

            void Reset()
            {
                canRessurrect = true;
                introduction = true;
                eventFailed = false;
                ResurrectionTimer = 120000;
                DebugOutputTestTimer = 5000;
                one = false; two = false;
                three = false; four = false;
            }

            void DoAction(int32 const action)
            {
                if (action == ACTION_SPIRIT_GUIDE_INTRODUCTION_OVER)
                    introduction = false;
            }

            void DoResurrectPlayer(Player* player, bool ressurectDueToFail)
            {
                if (player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_WARLOCK)
                    player->m_Events.AddEvent(new zombie_player_resurrects_pet_after_death(player), player->m_Events.CalculateTime(1000));

                player->ResurrectPlayer(1.0, false);
                player->TeleportTo(MAP_SCHOLOMANCE, 138.790329f, 172.884232f, 95.752052f, 3.118893f, TELE_TO_NOT_UNSUMMON_PET);
                player->ResetAllPowers();
                player->SetFullHealth();
                player->DurabilityRepairAll(false, 0, false);

                // If we won't cast the visual resurrection with a delay, there is no visual because of the teleport
                player->m_Events.AddEvent(new zombie_player_visually_resurrects_after_teleport(player), player->m_Events.CalculateTime(300));

                if (!ressurectDueToFail)
                {
                    // Only whisper normal message if it wasn't an instant ressurection due to Brann's introduction being active during player's death
                    if (!introduction)
                        me->MonsterWhisper("You will now be resurrected.", player->GetGUID());
                    else
                        me->MonsterWhisper("You have been instantly resurrected because you can't die during the introduction of Brann.", player->GetGUID());
                }
                else
                {
                    zombieEvent->SendMessageToGroup(player, "Your whole group is dead and you have therefore lost the event.");
                    canRessurrect = false;
                    eventFailed = true;
                    delete zombieEvent;
                    zombieEvent = NULL;
					EVENT_ENDED = true;
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                {
                    me->DespawnOrUnsummon();
                    return;
                }

                if (eventFailed)
                    return;

                //! We empty the revive_queue every worldtick
                //! so we won't have players that, for example,
                //! are not death. This also means we fill it
                //! back up again with players that DO have the
                //! ghost aura, preventing any type of exploits.
                revive_queue.clear();

                Map* map = me->GetMap();
                Map::PlayerList const& playerList = map->GetPlayers();
                for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                {
                    if (Player* player = itr->getSource())
                    {
						if (player->isDead())
                        {
                            //! When a player dies while Brann is still talking about
                            //! the introduction, the player will be instantly resurrected.
                            //! Else, if the introduction is over, we just add the player
                            //! to the revive queue.
                            if (introduction)
                                DoResurrectPlayer(player, false);
                            else
                                revive_queue.push_back(player); // Add player to revive queue
                        }
                    }
                }
				if(debug){
                if (DebugOutputTestTimer <= diff)
                {
					
                    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Size of revive queue:     %u", revive_queue.size());
                    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Players in map:           %u", map->GetPlayersCount());
                    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Size of playerList:       %u", playerList.getSize());
                    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Time till resurrection:   %u", ResurrectionTimer);
                    sLog->outInfo(LOG_FILTER_WORLDSERVER, "----------------------------");
                    DebugOutputTestTimer = 50000;
                }
                else
                    DebugOutputTestTimer -= diff;
				}
                //! Some documentation required here I guess.
                //! Since we clear out revive_queue every single
                //! Update(AI) call and also fill it up with valid
                //! players that are not a GM and do have the Ghost
                //! aura, there is never a need to remove a player
                //! from the revive_queue.
                if (ResurrectionTimer <= diff)
                {
                    for (std::list<Player*>::iterator itr = revive_queue.begin(); itr != revive_queue.end(); ++itr)
                    {
                        if (!(*itr) || !(*itr)->GetSession() || !(*itr)->IsInWorld() || !(*itr)->ToPlayer())
                            continue;

                        if (canRessurrect)
                            DoResurrectPlayer(*itr, false);
                    }

                    ResurrectionTimer = 120000;
                }
                else
                {
                    ResurrectionTimer -= diff;

                    //! We let the whole group know, even the ones that are alive should
                    //! know the time till their groupmates are getting resurrected.
                    for (std::list<Player*>::iterator itr = revive_queue.begin(); itr != revive_queue.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->GetSession() && (*itr)->ToPlayer() && (*itr)->isDead())
                        {
                            if (revive_queue.size() >= map->GetPlayersCount() && canRessurrect)
                            {
                                if (Creature* brann = me->FindNearestCreature(NPC_BRANN, 50.0f))
                                    if (brann->HasAura(SPELL_AURA_INVISIBLE))
                                        brann->AI()->DoAction(ACTION_BRANN_EVENT_FINISHED);

                                DoResurrectPlayer(*itr, true);
                                continue;
                            }
                            else
                            {
                                if (!one && ResurrectionTimer >= 119000 && ResurrectionTimer <= 120000)
                                {
                                    one = true;
                                    zombieEvent->SendMessageToGroup((*itr), "Two minutes left till global resurrection.");
                                }

                                if (!two && one && ResurrectionTimer >= 59000 && ResurrectionTimer <= 60000)
                                {
                                    two = true;
                                    zombieEvent->SendMessageToGroup((*itr), "One minute left till global resurrection.");
                                }

                                if (!three && two && ResurrectionTimer >= 29000 && ResurrectionTimer <= 30000)
                                {
                                    three = true;
                                    zombieEvent->SendMessageToGroup((*itr), "Half a minute left till global resurrection.");
                                }

                                if (!four && three && ResurrectionTimer >= 9000 && ResurrectionTimer <= 10000)
                                {
                                    four = true;
                                    zombieEvent->SendMessageToGroup((*itr), "Ten seconds left till global resurrection.");
                                }

                                if (ResurrectionTimer >= 1000 && ResurrectionTimer <= 1500)
                                {
                                    one = false; two = false;
                                    three = false; four = false;
                                }
                            }
                        }
                        else
                            sLog->outError(LOG_FILTER_WORLDSERVER, "Something went wrong in Zombie Event code (revive_queue). Please notify Discover-");
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_spirit_guideAI(creature);
        }
};

class npc_zombie_proximity_mine : public CreatureScript
{
    public:
        npc_zombie_proximity_mine() : CreatureScript("npc_zombie_proximity_mine") { }

        struct npc_zombie_proximity_mineAI : public Scripted_NoMovementAI
        {
            npc_zombie_proximity_mineAI(Creature* creature) : Scripted_NoMovementAI(creature) { }

            bool exploded;
            bool introduction;

            void Reset()
            {
                exploded = false;
                introduction = false;
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (summoner->ToCreature() && summoner->GetEntry() == NPC_BRANN)
                    introduction = true;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (introduction || exploded || !who || !who->ToCreature())
                    return;

                if (who->GetEntry() == NPC_ZOMBIE)
                {
                    if (me->IsWithinDist(who, 0.7f))
                    {
                        exploded = true;
                        DoCast(SPELL_EXPLOSION);
                        me->DespawnOrUnsummon(1000);
                    }
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (introduction)
                    return;

                if (me->GetMapId() != MAP_SCHOLOMANCE || !sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_proximity_mineAI(creature);
        }
};

class npc_zombie_bomb_bot : public CreatureScript
{
    public:
        npc_zombie_bomb_bot() : CreatureScript("npc_zombie_bomb_bot") { }

        struct npc_zombie_bomb_botAI : public ScriptedAI
        {
            npc_zombie_bomb_botAI(Creature* creature) : ScriptedAI(creature) { }

            std::list<Creature*> SpawnpointList;
            std::list<Creature*> MoveToBarricadeList;
            std::list<Creature*> BarricadeTriggerList;
            bool introduction;
            bool atSpawnpoint;
            bool movingToBarricade;
            bool movingToSpawnpoint;

            void Reset()
            {
                introduction = false;
                atSpawnpoint = false;
                movingToBarricade = false;
                movingToSpawnpoint = false;
                _events.ScheduleEvent(EVENT_BOMB_BOT_MOVE_TO_BARRICADE, 500);
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (summoner->ToCreature() && summoner->GetEntry() == NPC_BRANN)
                    introduction = true;
            }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type != POINT_MOTION_TYPE)
                    return;
                
                if (point == POINT_BOMB_BOT_TO_BARRICADE)
                {
                    movingToBarricade = false;
                    GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 80.0f);
                    for (std::list<Creature*>::iterator itr = SpawnpointList.begin(); itr != SpawnpointList.end(); ++itr)
                    {
                        if (movingToSpawnpoint)
                            continue;

                        if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_SPAWNPOINT && (*itr)->isInFront(me))
                        {
                            movingToSpawnpoint = true;
                            me->GetMotionMaster()->MovePoint(POINT_BOMB_BOT_TO_SPAWNPOINT, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ());
                        }
                    }
                }

                if (point == POINT_BOMB_BOT_TO_SPAWNPOINT)
                {
                    atSpawnpoint = true;
                    movingToSpawnpoint = false;
                    me->m_Events.AddEvent(new zombie_bomb_bot_explodes_at_spawnpoint(me), me->m_Events.CalculateTime(urand(1000, 2500)));
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (introduction || movingToBarricade || movingToSpawnpoint || atSpawnpoint)
                    return;

                _events.Update(diff);

                GetCreatureListWithEntryInGrid(BarricadeTriggerList, me, NPC_BARRICADE_TRIGGER, 80.0f);
                for (std::list<Creature*>::iterator itr = BarricadeTriggerList.begin(); itr != BarricadeTriggerList.end(); ++itr)
                    if ((*itr) && (*itr)->ToCreature() && !(*itr)->FindNearestGameObject(GAMEOBJECT_BARRICADE, 1.0f))
                        MoveToBarricadeList.push_back(*itr);

                if (_events.ExecuteEvent() == EVENT_BOMB_BOT_MOVE_TO_BARRICADE)
                {
                    if (movingToBarricade)
                        return;

                    for (std::list<Creature*>::iterator itr = MoveToBarricadeList.begin(); itr != MoveToBarricadeList.end(); ++itr)
                    {
                        if ((*itr) && (*itr)->ToCreature() && (*itr)->ToCreature()->GetEntry() == NPC_BARRICADE_TRIGGER)
                        {
                            if (!(*itr)->FindNearestGameObject(GAMEOBJECT_BARRICADE, 1.0f))
                            {
                                movingToBarricade = true;
                                me->GetMotionMaster()->MovePoint(POINT_BOMB_BOT_TO_BARRICADE, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ());
                            }
                            else
                                me->DespawnOrUnsummon(500);
                        }
                    }
                }
            }

        private:
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_bomb_botAI(creature);
        }
};

class npc_zombie_turret : public CreatureScript
{
    public:
        npc_zombie_turret() : CreatureScript("npc_zombie_turret") { }

        struct npc_zombie_turretAI : public Scripted_NoMovementAI
        {
            npc_zombie_turretAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                introduction = false;
                me->SetReactState(REACT_PASSIVE);
                _events.Reset();
                _events.ScheduleEvent(EVENT_FIRE_TURRET, 1500);
            }

            bool introduction;

            void IsSummonedBy(Unit* summoner)
            {
                if (summoner->ToCreature() && summoner->GetEntry() == NPC_BRANN)
                    introduction = true;
            }

            void UpdateAI(uint32 const diff)
            {
                if (introduction)
                    return;

                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();

                _events.Update(diff);

                if (_events.ExecuteEvent() == EVENT_FIRE_TURRET)
                {
                    me->CastSpell((Unit*)NULL, SPELL_RAPID_FIRE, false);
                    _events.ScheduleEvent(EVENT_FIRE_TURRET, 4500);
                }
            }

        private:
            EventMap _events;

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_turretAI(creature);
        }
};

class npc_zombie_vehicle : public CreatureScript
{
    public:
        npc_zombie_vehicle() : CreatureScript("npc_zombie_vehicle") { }

        struct npc_zombie_vehicleAI : public Scripted_NoMovementAI
        {
            npc_zombie_vehicleAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
            }

            bool introduction;

            void Reset()
            {
                introduction = false;
            }

            void PassengerBoarded(Unit* who, int8 seatId, bool apply)
            {
                if (introduction || !me->GetVehicle())
                    return;
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (summoner->ToCreature() && summoner->GetEntry() == NPC_BRANN)
                    introduction = true;
            }

            void UpdateAI(uint32 const diff)
            {
                if (introduction)
                    return;

                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_vehicleAI(creature);
        }
};

class npc_zombie_cannon_shooter : public CreatureScript
{
    public:
        npc_zombie_cannon_shooter() : CreatureScript("npc_zombie_cannon_shooter") { }

        struct npc_zombie_cannon_shooterAI : public Scripted_NoMovementAI
        {
            npc_zombie_cannon_shooterAI(Creature* creature) : Scripted_NoMovementAI(creature) { }

            void Reset()
            {
                _events.Reset();

                // Apparently 5 yards is too big and makes two of the summons work at a certain spawnpoint
                if (GameObject* cannon = me->FindNearestGameObject(GAMEOBJECT_CANNON, 2.5f))
                {
                    //! Checking orientation here as we spawn a Cannon Shooter
                    //! at each of the cannon/turret spawnpoints with the
                    //! orientation of the cannon that's spawned at the time,
                    //! so if the group reaches two waves within two minutes
                    //! of each other and they get two cannons, it would cause
                    //! the cannons to both shoot twice if done fast enough.
                    if (cannon->GetOrientation() == me->GetOrientation())
                        _events.ScheduleEvent(EVENT_FIRE_CANNON, 2000);
                    else
                        me->DespawnOrUnsummon();
                }
                else
                    me->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 const diff)
            {
                _events.Update(diff);
                std::list<Creature*> SpawnpointList;
                GetCreatureListWithEntryInGrid(SpawnpointList, me, NPC_SPAWNPOINT, 80.0f);
                std::list<Creature*>::iterator itr = SpawnpointList.begin();

                switch (_events.ExecuteEvent())
                {
                    case EVENT_FIRE_CANNON:
                        do
                            std::advance(itr, urand(0, SpawnpointList.size() - 1));
                        while (!(*itr) || !(*itr)->isInFront(me) || !me->isInFront(*itr));

                        if ((*itr) && (*itr)->ToCreature())
                        {
                            me->CastSpell((*itr), SPELL_FIRE_CANNON, false);

                            if (Creature* fireSpawner = me->SummonCreature(NPC_FIRE_SPAWNER, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ()))
                                fireSpawner->m_Events.AddEvent(new zombie_fire_spawner_makes_spawnpoint_explode(fireSpawner), fireSpawner->m_Events.CalculateTime(4000));
                        }

                        _events.ScheduleEvent(EVENT_CANNON_SHOOTER_DESPAWN, 5000);
                        break;
                    case EVENT_CANNON_SHOOTER_DESPAWN:
                        if (GameObject* cannon = me->FindNearestGameObject(GAMEOBJECT_CANNON, 5.0f))
                        {
                            cannon->Delete();
                            cannon->DeleteFromDB();
                        }

                        me->DespawnOrUnsummon();
                        break;
                }
            }

        private:
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_cannon_shooterAI(creature);
        }
};

class npc_zombie_barricade_repair_crew : public CreatureScript
{
    public:
        npc_zombie_barricade_repair_crew() : CreatureScript("npc_zombie_barricade_repair_crew") { }

        struct npc_zombie_barricade_repair_crewAI : public ScriptedAI
        {
            npc_zombie_barricade_repair_crewAI(Creature* creature) : ScriptedAI(creature) { }

            bool atBarricade;
            bool repaired;
            uint32 EmoteRepairTimer;
            uint32 RepairingDoneTimer;

            void Reset()
            {
                atBarricade = false;
                repaired = false;
                EmoteRepairTimer = 1250;
                RepairingDoneTimer = 15000;
            }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (point == POINT_ENGINEER_TO_BARRICADE)
                {
                    if (GameObject* anvil = me->FindNearestGameObject(GAMEOBJECT_ANVIL, 3.0f))
                        me->SetFacingToObject(anvil);

                    atBarricade = true;
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    me->DespawnOrUnsummon();

                if (atBarricade)
                {
                    if (!repaired)
                    {
                        if (EmoteRepairTimer <= diff)
                        {
                            me->HandleEmoteCommand(EMOTE_ONESHOT_WORK_MINING);
                            EmoteRepairTimer = 1250;
                        }
                        else
                            EmoteRepairTimer -= diff;

                        if (RepairingDoneTimer <= diff)
                        {
                            repaired = true;
                            me->MonsterSay("There you go, your barricade is back up!", LANG_UNIVERSAL, me->GetGUID());
                            me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);

                            if (Creature* barricadeTrigger = me->FindNearestCreature(NPC_BARRICADE_TRIGGER, 3.0f))
                                barricadeTrigger->m_Events.AddEvent(new zombie_barricade_repaired(barricadeTrigger), barricadeTrigger->m_Events.CalculateTime(2500));

                            if (Creature* anvilSpawner = me->FindNearestCreature(NPC_ANVIL_SPAWNER, 3.0f))
                                anvilSpawner->DespawnOrUnsummon();

                            if (GameObject* anvil = me->FindNearestGameObject(GAMEOBJECT_ANVIL, 3.0f))
                                anvil->Delete();

                            me->DespawnOrUnsummon(2000);
                        }
                        else
                            RepairingDoneTimer -= diff;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_barricade_repair_crewAI(creature);
        }
};

class npc_zombie_keep_out : public CreatureScript
{
    public:
        npc_zombie_keep_out() : CreatureScript("npc_zombie_keep_out") { }

        struct npc_zombie_keep_outAI : public ScriptedAI
        {
            npc_zombie_keep_outAI(Creature* creature) : ScriptedAI(creature) { }

            bool introduction;

            void Reset()
            {
                introduction = false;
            }

            void IsSummonedBy(Unit* summoner)
            {
                if (summoner->ToCreature() && summoner->GetEntry() == NPC_BRANN)
                    introduction = true;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (introduction || !who || who->GetTypeId() != TYPEID_PLAYER)
                    return;
                
                if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                    return;

                if (Player* player = who->ToPlayer())
                {
                    if (!player->IsBeingTeleported() && me->IsWithinDist(player, 13.0f))
                    {
                        player->GetSession()->SendNotification("You can not be here during the Zombie Event and will be teleported back to the Zombie Event spot.");
                        player->TeleportTo(MAP_SCHOLOMANCE, 138.790329f, 172.884232f, 95.752052f, 3.118893f, TELE_TO_NOT_UNSUMMON_PET);
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zombie_keep_outAI(creature);
        }
};

class npc_zombie_teleporter : public CreatureScript
{
    public:
        npc_zombie_teleporter() : CreatureScript("npc_zombie_teleporter") { }

        bool SendWhisperToGroup(Player* player, Creature* creature, Group* group, char const* message)
        {
            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                if (Player* member = itr->getSource())
                    creature->MonsterWhisper(message, member->GetGUID());

            return true;
        }

        bool WhisperRulesToGroup(Creature* creature, Player* player, Group* group)
        {
            SendWhisperToGroup(player, creature, group, "Here follows a list of disallowed things in order to participate in the Zombie Event:");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be deserted for the Zombie Event (the aura is called 'Approved!').");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be in either an arena or battleground.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be in either an arena or battleground queue.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be Away from Keyboard (or even marked as).");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be dead or in ghost form.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be below level 80.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be a game master.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be in the middle of a flight (through flight masters).");
            SendWhisperToGroup(player, creature, group, "- None of your group members may have Resurrection Sickness.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be in the loading screen.");
            SendWhisperToGroup(player, creature, group, "- None of your group members may be in the progression of logging out.");
            SendWhisperToGroup(player, creature, group, "- Your group may not be a raid or LFG group.");
            SendWhisperToGroup(player, creature, group, "- Your group must contain five players.");
            SendWhisperToGroup(player, creature, group, "A list of players that do not follow these rules will be whispered to all members, if any.");
            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
            {
                creature->MonsterWhisper("[Zombie Event] The Zombie Event is not active at this moment", player->GetGUID());
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }

            Group* group = player->GetGroup();
            ZombieEvent* zombieEvent = new ZombieEvent;
            std::list<Player*> errorList;
            std::stringstream msg;
            bool isErrored = false;

            if (!player->isGameMaster()) // Only run through these checks if player is not a gamemaster, else we simply add gossip without any checks
            {
                if (!group)
                {
                    creature->MonsterWhisper("[Zombie Event] You must be in a group in order to participate in the Zombie Event.", player->GetGUID(), false);
                    return true;
                }

                if (!group->IsLeader(player->GetGUID()))
                {
                    creature->MonsterWhisper("[Zombie Event] You must be the group leader of your group in order to participate in the Zombie Event.", player->GetGUID(), false);
                    return true;
                }

                if (group->isRaidGroup())
                {
                    creature->MonsterWhisper("[Zombie Event] Your group may not be a raid group.", player->GetGUID(), false);
                    return true;
                }

                if (group->isLFGGroup())
                {
                    creature->MonsterWhisper("[Zombie Event] Your group may not be a LFG group.", player->GetGUID(), false);
                    return true;
                }

                /*if (group->GetMembersCount() != 5)
                {
                    creature->MonsterWhisper("Your group must and may contain five and only five players.", player->GetGUID(), false);
                    return true;
                }*/

                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'd like a list of all disallowed things in order to participate in the Zombie Event.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                SendWhisperToGroup(player, creature, group, "[Zombie Event] If you want a list of disallowed things in order to join the Zombie Event, talk to me.");

                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* member = itr->getSource();

                    if (!member || !member->IsInWorld())
                    {
                        creature->MonsterWhisper("[Zombie Event] One or more of the group members are not online.", member->GetGUID());
                        player->PlayerTalkClass->SendCloseGossip();
                        isErrored = true;
                        continue;
                    }

                    if (member->InBattleground() || member->InArena() || member->InBattlegroundQueue() || member->isAFK() || member->isDead() || !member->isAlive() ||
                        member->getLevel() != 80 || member->isGameMaster() || member->isInFlight() || member->HasAura(SPELL_AURA_SICKNESS) || member->IsBeingTeleported() ||
                        member->GetSession()->isLogingOut() || member->HasAura(SPELL_AURA_ZOMBIE_DESERTER))
                    {
                        isErrored = true;
                        errorList.push_back(member);
                        continue;
                    }
                }

                if (errorList.size() > 1)
                    msg << "[Zombie Event] Your group is not eligible for the Zombie Event due to these players doing something wrong: ";
                else if (errorList.size() == 1)
                {
                    std::list<Player*>::iterator itr = errorList.begin();
                    msg << "[Zombie Event] Your group is not eligible for the Zombie Event due to this player doing something wrong: " << (*itr)->GetName() << ".";
                    SendWhisperToGroup(player, creature, group, msg.str().c_str());
                    errorList.clear();
                    return true;
                }

                if (errorList.size() != 0)
                {
                    for (std::list<Player*>::iterator itr = errorList.begin(); itr != errorList.end(); ++itr)
                    {
                        if (!(*itr) || !(*itr)->GetSession() || !(*itr)->IsInWorld() || !(*itr)->ToPlayer())
                            continue;

                        if (errorList.back() == *itr)
                            msg << "and ";

                        msg << (*itr)->GetName();

                        if (errorList.back() != *itr)
                            msg << ", ";
                        else
                            msg << ".";
                    }

                    SendWhisperToGroup(player, creature, group, msg.str().c_str());
                }
            }

            if (isErrored)
            {
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Me and my group would like to participate in the Zombie Event.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
            {
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }

            player->PlayerTalkClass->ClearMenus();
            player->PlayerTalkClass->SendCloseGossip();

            Group* group = player->GetGroup();

            if (action == GOSSIP_ACTION_INFO_DEF + 1)
                WhisperRulesToGroup(creature, player, group);

            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    if (Player* member = itr->getSource())
                    {
                        member->ResetAllPowers();
                        member->RemoveArenaAuras();
                        member->RemoveArenaSpellCooldowns(true);

                        // We only send an accept request to the group members, the group leader instantly gets teleported
                        if (member->GetGUID() != player->GetGUID())
                        {
                            member->SetSummonPoint(MAP_SCHOLOMANCE, 138.790329f, 172.884232f, 95.752052f);
                            WorldPacket data(SMSG_SUMMON_REQUEST, 8 + 4 + 4);
                            data << uint64(member->GetGUID());
                            data << uint32(member->GetZoneId());
                            data << uint32(300000); // Auto decline after 5 minutes
                            member->GetSession()->SendPacket(&data); // Send data to member
                        }
                        else if (member->GetGUID() == player->GetGUID())
                        {
                            player->AddAura(SPELL_AURA_ZOMBIE_DESERTER_CHECKER, player);
                            player->TeleportTo(MAP_SCHOLOMANCE, 138.790329f, 172.884232f, 95.752052f, 3.118893f, TELE_TO_NOT_UNSUMMON_PET);
                        }
                    }
                }
            }

            return true;
        }
};

class ZombieEntryCheck
{
    public:
        ZombieEntryCheck() { }

        bool operator()(WorldObject* unit) const
        {
            // If Zombie isn't a Zombie, don't shoot
            if (unit->GetTypeId() == TYPEID_PLAYER)
                return true;

            // If Zombie is dead, don't shoot
            if ( !unit->ToCreature()->isAlive())
                return true;

            // If Zombie is still invisible (and thus falling), don't shoot
            if (unit->ToCreature()->HasAura(SPELL_AURA_INVISIBLE))
                return true;

            // If Zombie is casting Emerge Visual, don't shoot
            if (unit->ToCreature()->GetCurrentSpell(CURRENT_GENERIC_SPELL) && unit->ToCreature()->GetCurrentSpell(CURRENT_GENERIC_SPELL)->GetSpellInfo()->Id == SPELL_EMERGE_VISUAL)
                return true;

            return unit->GetEntry() != NPC_ZOMBIE;
        }
};

class spell_zombie_rapid_fire : public SpellScriptLoader
{
    public:
        spell_zombie_rapid_fire() : SpellScriptLoader("spell_zombie_rapid_fire") { }

        class spell_zombie_rapid_fire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_zombie_rapid_fire_SpellScript);

            void SelectTarget(std::list<WorldObject*>& unitList)

            {
                if (unitList.empty())
                    return;

                unitList.remove_if(ZombieEntryCheck());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_zombie_rapid_fire_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_zombie_rapid_fire_SpellScript();
        }
};

class SpawnpointEntryCheck
{
    public:
        SpawnpointEntryCheck() { }

        bool operator()(WorldObject* unit) const
        {
            if (unit->GetTypeId() == TYPEID_PLAYER)
                return true;

            if (!unit->ToCreature()->isAlive())
                return true;

            if (unit->ToCreature()->HasAura(SPELL_AURA_BLOWN_UP))
                return true;

            return unit->GetEntry() != NPC_SPAWNPOINT;
        }
};

class spell_zombie_blow_up_spawnpoint : public SpellScriptLoader
{
    public:
        spell_zombie_blow_up_spawnpoint() : SpellScriptLoader("spell_zombie_blow_up_spawnpoint") { }

        class spell_zombie_blow_up_spawnpoint_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_zombie_blow_up_spawnpoint_SpellScript);
			 
            void SelectTarget(std::list<WorldObject*>& unitList)
            {
                if (unitList.empty())
                 return;

                unitList.remove_if(SpawnpointEntryCheck());
            }

            void Register()
            {
                OnObjectAreaTargetSelect  += SpellObjectAreaTargetSelectFn(spell_zombie_blow_up_spawnpoint_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_zombie_blow_up_spawnpoint_SpellScript();
        }
};

class spell_zombie_periodic_aura_checker : public SpellScriptLoader
{
    public:
        spell_zombie_periodic_aura_checker() : SpellScriptLoader("spell_zombie_periodic_aura_checker") { }

        class spell_zombie_periodic_aura_checker_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_zombie_periodic_aura_checker_AuraScript);

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    // Maybe add checks here that we also used in Taruk (or some of them, like checking AFK)
                    if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT) || player->GetMapId() != MAP_SCHOLOMANCE)
                    {
                        player->GetSession()->SendNotification("[Zombie Event] You have been deserted and can not participate in the Zombie Event for two hours from now on.");
                        player->AddAura(SPELL_AURA_ZOMBIE_DESERTER, player);
                        Remove(AURA_REMOVE_BY_DEFAULT);
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_zombie_periodic_aura_checker_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_zombie_periodic_aura_checker_AuraScript();
        }
};

class go_zombie_teleport_away : public GameObjectScript
{
    public:
        go_zombie_teleport_away() : GameObjectScript("go_zombie_teleport_away") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                return true;

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to teleport away from here", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, GameObject* /*go*/, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();
            player->PlayerTalkClass->SendCloseGossip();

            if (!sGameEventMgr->IsActiveEvent(GAME_EVENT_ZOMBIE_EVENT))
                return true;

            if (action == GOSSIP_ACTION_INFO_DEF + 1)
                player->TeleportTo(230, 1380.61f, -816.851f, -92.7223f, 1.5);

            return true;
        }
};

class go_zombie_repair_barricade : public GameObjectScript
{
    public:
        go_zombie_repair_barricade() : GameObjectScript("go_zombie_repair_barricade") { }

        bool OnGossipHello(Player* /*player*/, GameObject* go)
        {
            if (go->GetGoState() != GO_STATE_ACTIVE_ALTERNATIVE)
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);

            if (Creature* engineer = go->SummonCreature(NPC_GOBLIN_ENGINEER, 138.790329f, 172.884232f, 95.752052f, 3.118893f))
            {
                switch (urand(0, 11))
                {
                    case 0:
                        engineer->MonsterSay("Ahh, let's see what we've got here. A broken barricade you say? No problem for me!", LANG_UNIVERSAL, engineer->GetGUID());
                        engineer->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                        break;
                    case 1:
                        engineer->MonsterSay("Ahh, let's see what we've got here.", LANG_UNIVERSAL, engineer->GetGUID());
                        engineer->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        break;
                    case 2:
                        engineer->MonsterSay("I heard there was something broken over here?", LANG_UNIVERSAL, engineer->GetGUID());
                        engineer->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
                        break;
                    case 3:
                        engineer->MonsterSay("Did someone ask for an outstanding engineer?", LANG_UNIVERSAL, engineer->GetGUID());
                        engineer->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
                        break;
                    case 4:
                        engineer->MonsterSay("Did someone ask for an engineer?", LANG_UNIVERSAL, engineer->GetGUID());
                        engineer->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
                        break;
                    case 5:
                        engineer->MonsterSay("You mentioned to break yet another barricade?", LANG_UNIVERSAL, engineer->GetGUID());
                        engineer->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
                        break;
                    default:
                        break;
                }

                engineer->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                engineer->GetMotionMaster()->MovePoint(POINT_ENGINEER_TO_BARRICADE, go->GetPositionX() + 1, go->GetPositionY(), go->GetPositionZ());
            }

            return true;
        }
};

class go_zombie_cannon : public GameObjectScript
{
    public:
        go_zombie_cannon() : GameObjectScript("go_zombie_cannon") { }

        bool OnGossipHello(Player* /*player*/, GameObject* go)
        {
            if (go->GetGoState() != GO_STATE_ACTIVE_ALTERNATIVE)
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE); // Makes it always return 'you are too far away'

            // We summon one shooter at each point and in the creature script check for a cannon - hacky but w/e
            go->SummonCreature(NPC_CANNON_SHOOTER, 134.346817f, 180.306259f, 95.599319f, go->GetOrientation());
            go->SummonCreature(NPC_CANNON_SHOOTER, 142.100311f, 180.035294f, 96.453812f, go->GetOrientation());
            go->SummonCreature(NPC_CANNON_SHOOTER, 134.334564f, 161.869705f, 95.704140f, go->GetOrientation());
            go->SummonCreature(NPC_CANNON_SHOOTER, 142.232224f, 162.575104f, 95.780975f, go->GetOrientation());
            return true;
        }
};

void AddSC_zombie_event()
{
    new npc_zombie();
    new npc_zombie_brann();
    new npc_zombie_turret();
    new npc_zombie_vehicle();
    new npc_zombie_keep_out();
    new npc_zombie_bomb_bot();
    new npc_zombie_spawnpoint();
    new npc_zombie_teleporter();
    new npc_zombie_introduction();
    new npc_zombie_spirit_guide();
    new npc_zombie_fire_spawner();
    new npc_zombie_anvil_spawner();
    new npc_zombie_proximity_mine();
    new npc_zombie_cannon_shooter();
    new npc_zombie_wave_kill_counter();
    new npc_zombie_barricade_trigger();
    new npc_zombie_barricade_repair_crew();

    new spell_zombie_rapid_fire();
    new spell_zombie_blow_up_spawnpoint();
    new spell_zombie_periodic_aura_checker();

    new go_zombie_cannon();
    new go_zombie_teleport_away();
    new go_zombie_repair_barricade();
}
