#ifndef _BOT_AI_H
#define _BOT_AI_H

#include "ScriptedCreature.h"

struct PlayerClassLevelInfo;
struct BotClassLevelInfo
{
    BotClassLevelInfo() : basehealth(0), basemana(0) { }
    uint32 basehealth;
    uint32 basemana;
};

enum CommonValues
{
//MISC
    BOT_ENTRY_BEGIN                     = 70001,
    BOT_ENTRY_END                       = 70248,
    BOT_ICON_ON                         = 9,//GOSSIP_ICON_BATTLE,
    BOT_ICON_OFF                        = 7,//GOSSIP_ICON_TALK,
//COMMON SPELLS
    MANAPOTION                          = 32453,//"Uses a Holy elixir to heal the caster for 32000"
    HEALINGPOTION                       = 15504,//"Drinks Holy Elixir to heal the caster"
    DRINK                               = 66041,//"Restores 4% mana per sec for 30 sec"
    EAT                                 = 66478,//"Restores Health"
    PVPTRINKET                          = 42292,//PvP Trinket no CD
//COMMON CDs
    POTION_CD                           = 60000,//default 60sec potion cd
    RATIONS_CD                          = 1000,//update rations every X milliseconds
//COMMON PASSIVES
  //1) "Increase(d) @whatever"
    //SPELL_BONUS_10                      = 33021,//10spp
    SPELL_BONUS_50                      = 45011,//50spp
    SPELL_BONUS_150                     = 28141,//150spp
    SPELL_BONUS_250                     = 69709,//250spp
    FIREDAM_86                          = 33816,//86 fire spp
    MANAREGEN45                         = 35867,//45 mp5
    MANAREGEN100                        = 45216,//100 mp5
    SPELL_PEN_5                         = 31921,//5 sppen
    SPELL_PEN_20                        = 26283,//20 sppen
  //2) Talents
    HASTE    /*Gift of the EarthMother*/= 51183,//rank 5 10% spell haste
    HASTE2   /*Blood Frenzy - warrior*/ = 29859,//rank 2 10% melee haste, bonus for rend (warriors only)
    HASTE3   /*       "Haste"       */  = 29418,//rank 0 10% increased ranged attack speed
    CRITS    /*Thundering Strikes-sham*/= 16305,//rank 5 5% crit
    HOLYCRIT /*Holy Spec - priest*/     = 15011,//rank 5 5% holy crit
    DODGE    /*Anticipation - paladin*/ = 20100,//rank 5 5% dodge
    PARRY    /*Deflection - warrior*/   = 16466,//rank 5 5% parry
    BLOCK/*zzOLD Shield Specialization*/= 16253,//rank 1 5% block 10% amount, 3.3.5 & 4.3.4 deprecated
    PRECISION /*Precision - warrior*/   = 29592,//rank 3 3% melee hit
    PRECISION2/*Precision - mage*/      = 29440,//rank 3 3% spell hit
    DMG_TAKEN/*Deadened Nerves - rogue*/= 31383,//rank 3 6% reduced all damage taken
    EXPERTISE /*Weapon Expertise-rogue*/= 30919,//rank 1 5 expertise
    EXPERTISE2/*Weapon Expertise-rogue*/= 30920,//rank 2 10 expertise
  //3) Pet/Special
    THREAT   /*Tank Class Passive*/     = 57339,//+43% threat
    BOR      /*Blood of Rhino - pet*/   = 53482,//rank 2 +40% healing taken
    BOAR     /*Boar's Speed - pet*/     = 19596,//rank 1 +30% movement speed
    RCP      /*Rogue Class Passive*/    = 21184,//-27% threat caused
    DEFENSIVE_STANCE_PASSIVE            = 7376, //+ 400% threat 10% damage reduction
//COMMON GOSSIPS
    GOSSIP_SERVE_MASTER                 = 2279, //"I live only to serve the master."
    GOSSIP_SENDER_BEGIN                 = 6000,
    GOSSIP_SENDER_CLASS,
    GOSSIP_SENDER_EQUIPMENT,
    GOSSIP_SENDER_EQUIPMENT_LIST,
    GOSSIP_SENDER_EQUIPMENT_SHOW,
    GOSSIP_SENDER_EQUIPMENT_INFO,
    GOSSIP_SENDER_UNEQUIP,
    GOSSIP_SENDER_EQUIP_RESET,
    GOSSIP_SENDER_EQUIP,
    GOSSIP_SENDER_EQUIP_BEGIN           = GOSSIP_SENDER_EQUIP,
    GOSSIP_SENDER_EQUIP_MHAND           = GOSSIP_SENDER_EQUIP_BEGIN,
    GOSSIP_SENDER_EQUIP_OHAND,
    GOSSIP_SENDER_EQUIP_RANGED,
    GOSSIP_SENDER_EQUIP_HEAD,
    GOSSIP_SENDER_EQUIP_SHOULDERS,
    GOSSIP_SENDER_EQUIP_CHEST,
    GOSSIP_SENDER_EQUIP_WAIST,
    GOSSIP_SENDER_EQUIP_LEGS,
    GOSSIP_SENDER_EQUIP_FEET,
    GOSSIP_SENDER_EQUIP_WRIST,
    GOSSIP_SENDER_EQUIP_HANDS,
    GOSSIP_SENDER_EQUIP_BACK,
    GOSSIP_SENDER_EQUIP_BODY,
    GOSSIP_SENDER_EQUIP_FINGER1,
    GOSSIP_SENDER_EQUIP_FINGER2,
    GOSSIP_SENDER_EQUIP_TRINKET1,
    GOSSIP_SENDER_EQUIP_TRINKET2,
    GOSSIP_SENDER_EQUIP_NECK,
    GOSSIP_SENDER_ROLES,
    GOSSIP_SENDER_ROLES_TOGGLE,
    GOSSIP_SENDER_ABILITIES,
    GOSSIP_SENDER_ABILITIES_USE,
//COMMON GAMEEVENTS
    GAME_EVENT_WINTER_VEIL              = 2,
//COMMON MOUNTS SPELLS
    REINDEER                            = 25859,
    REINDEER_FLY                        = 44827
};

enum BotRoles
{
    BOT_ROLE_NONE                       = 0x00,
    BOT_ROLE_TANK                       = 0x01,
    BOT_ROLE_DPS                        = 0x02,
    BOT_ROLE_HEAL                       = 0x04,
    BOT_ROLE_RANGED                     = 0x08,
    BOT_MAX_ROLE                        = 0x10
};

enum BotStances
{
    BOT_STANCE_NONE                     = 0,
    WARRIOR_BATTLE_STANCE               = 21,
    WARRIOR_DEFENSIVE_STANCE            = 22,
    WARRIOR_BERSERKER_STANCE            = 23,
    DEATH_KNIGHT_BLOOD_PRESENCE         = 24,
    DEATH_KNIGHT_FROST_PRESENCE         = 25,
    DEATH_KNIGHT_UNHOLY_PRESENCE        = 26,
    DRUID_BEAR_FORM                     = 27,
    DRUID_CAT_FORM                      = 28,
    //DRUID_TRAVEL_FORM                 = 29,   //NYI
    //DRUID_FLY_FORM                    = 30,   //NYI
    DRUID_MOONKIN_FORM                = 31      //NYI
};

enum BotPetTypes
{
    PET_TYPE_NONE,
//Warlock
    PET_TYPE_IMP,
    PET_TYPE_VOIDWALKER,
    PET_TYPE_SUCCUBUS,
    PET_TYPE_FELHUNTER,
    PET_TYPE_FELGUARD,
//Mage
    PET_TYPE_WATER_ELEMENTAL,
//Shaman
    //PET_TYPE_GHOSTLY_WOLF,
    PET_TYPE_FIRE_ELEMENTAL,
    PET_TYPE_EARTH_ELEMENTAL,
//Hunter
    PET_TYPE_VULTURE,

    MAX_PET_TYPES
};

enum WarlockBotPets
{
    //PET_IMP                     = ,
    PET_VOIDWALKER              = 70247
    //PET_SUCCUBUS                =
};

enum HunterBotPets
{
    PET_VULTURE                 = 70248
};

enum BotPetsOriginalEntries
{
    ORIGINAL_ENTRY_VOIDWALKER   = 1860
};

enum BotEquipSlot
{
    BOT_SLOT_NONE               = 0,
    BOT_SLOT_MAINHAND           = 1,
    BOT_SLOT_OFFHAND            = 2,
    BOT_SLOT_RANGED             = 3,
    BOT_SLOT_HEAD               = 4,
    BOT_SLOT_SHOULDERS          = 5,
    BOT_SLOT_CHEST              = 6,
    BOT_SLOT_WAIST              = 7,
    BOT_SLOT_LEGS               = 8,
    BOT_SLOT_FEET               = 9,
    BOT_SLOT_WRIST              = 10,
    BOT_SLOT_HANDS              = 11,
    BOT_SLOT_BACK               = 12,
    BOT_SLOT_BODY               = 13,
    BOT_SLOT_FINGER1            = 14,
    BOT_SLOT_FINGER2            = 15,
    BOT_SLOT_TRINKET1           = 16,
    BOT_SLOT_TRINKET2           = 17,
    BOT_SLOT_NECK               = 18,
    BOT_MAX_SLOTS,
    BOT_INVENTORY_SIZE = BOT_MAX_SLOTS - 1
};

enum BotStatTypes
{
    //ItemProtoType.h
    //ITEM_MOD_MANA                     = 0,
    //ITEM_MOD_HEALTH                   = 1,
    //ITEM_MOD_AGILITY                  = 3,
    //ITEM_MOD_STRENGTH                 = 4,
    //ITEM_MOD_INTELLECT                = 5,
    //ITEM_MOD_SPIRIT                   = 6,
    //ITEM_MOD_STAMINA                  = 7,
    //ITEM_MOD_DEFENSE_SKILL_RATING     = 12,
    //ITEM_MOD_DODGE_RATING             = 13,
    //ITEM_MOD_PARRY_RATING             = 14,
    //ITEM_MOD_BLOCK_RATING             = 15,
    //ITEM_MOD_HIT_MELEE_RATING         = 16,
    //ITEM_MOD_HIT_RANGED_RATING        = 17,
    //ITEM_MOD_HIT_SPELL_RATING         = 18,
    //ITEM_MOD_CRIT_MELEE_RATING        = 19,
    //ITEM_MOD_CRIT_RANGED_RATING       = 20,
    //ITEM_MOD_CRIT_SPELL_RATING        = 21,
    //ITEM_MOD_HIT_TAKEN_MELEE_RATING   = 22,
    //ITEM_MOD_HIT_TAKEN_RANGED_RATING  = 23,
    //ITEM_MOD_HIT_TAKEN_SPELL_RATING   = 24,
    //ITEM_MOD_CRIT_TAKEN_MELEE_RATING  = 25,
    //ITEM_MOD_CRIT_TAKEN_RANGED_RATING = 26,
    //ITEM_MOD_CRIT_TAKEN_SPELL_RATING  = 27,
    //ITEM_MOD_HASTE_MELEE_RATING       = 28,
    //ITEM_MOD_HASTE_RANGED_RATING      = 29,
    //ITEM_MOD_HASTE_SPELL_RATING       = 30,
    //ITEM_MOD_HIT_RATING               = 31,
    //ITEM_MOD_CRIT_RATING              = 32,
    //ITEM_MOD_HIT_TAKEN_RATING         = 33,
    //ITEM_MOD_CRIT_TAKEN_RATING        = 34,
    //ITEM_MOD_RESILIENCE_RATING        = 35,
    //ITEM_MOD_HASTE_RATING             = 36,
    //ITEM_MOD_EXPERTISE_RATING         = 37,
    //ITEM_MOD_ATTACK_POWER             = 38,
    //ITEM_MOD_RANGED_ATTACK_POWER      = 39,
    ////ITEM_MOD_FERAL_ATTACK_POWER       = 40, not in 3.3
    //ITEM_MOD_SPELL_HEALING_DONE       = 41,                 // deprecated
    //ITEM_MOD_SPELL_DAMAGE_DONE        = 42,                 // deprecated
    //ITEM_MOD_MANA_REGENERATION        = 43,
    //ITEM_MOD_ARMOR_PENETRATION_RATING = 44,
    //ITEM_MOD_SPELL_POWER              = 45,
    //ITEM_MOD_HEALTH_REGEN             = 46,
    //ITEM_MOD_SPELL_PENETRATION        = 47,
    //ITEM_MOD_BLOCK_VALUE              = 48,
    //END ItemProtoType.h

    BOT_ITEM_MOD_DAMAGE                 = MAX_ITEM_MOD,
    BOT_ITEM_MOD_ARMOR,
    BOT_ITEM_MOD_RESIST_HOLY,
    BOT_ITEM_MOD_RESIST_FIRE,
    BOT_ITEM_MOD_RESIST_NATURE,
    BOT_ITEM_MOD_RESIST_FROST,
    BOT_ITEM_MOD_RESIST_SHADOW,
    BOT_ITEM_MOD_RESIST_ARCANE,
    BOT_ITEM_MOD_EX,
    MAX_BOT_ITEM_MOD
};

#define MAX_BOT_CTC_SPELLS              1//(MAX_EQUIPMENT_ITEMS * MAX_ITEM_SPELLS)

class bot_ai : public ScriptedAI
{
    public:
        virtual ~bot_ai();
        bot_ai(Creature* creature);
        //Player* GetMaster() const { return master; }
        virtual bool IsMinionAI() const = 0;
        virtual bool IsPetAI() const = 0;
        virtual void SetBotCommandState(CommandStates /*st*/, bool /*force*/ = false, Position* /*newpos*/ = NULL) = 0;
        virtual const bot_minion_ai* GetMinionAI() const { return NULL; }
        virtual const bot_pet_ai* GetPetAI() const { return NULL; }
        bool IsInBotParty(Unit* unit) const;
        bool CanBotAttack(Unit* target, int8 byspell = 0) const;
        bool InDuel(Unit* target) const;
        CommandStates GetBotCommandState() const { return m_botCommandState; }
        void ApplyBotDamageMultiplierMelee(uint32& damage, CalcDamageInfo& damageinfo) const;
        void ApplyBotDamageMultiplierMelee(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType attackType, bool& crit) const;
        void ApplyBotDamageMultiplierSpell(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType attackType, bool& crit) const;
        void ApplyBotDamageMultiplierEffect(SpellInfo const* spellInfo, uint8 effect_index, float &value) const;
        inline void SendPartyEvadeAbort() const;
        inline void SetShouldUpdateStats() { shouldUpdateStats = true; }
        inline void UpdateHealth() { doHealth = true; }
        inline void UpdateMana() { doMana = true; }
        inline float GetManaRegen() const { return regen_mp5; }
        inline float GetHitRating() const { return hit; }
        inline int32 GetSpellPower() const { return m_spellpower; }
        inline uint8 GetHaste() const { return haste; }
        inline uint32 GetShieldBlockValue() const { return m_block; }
        virtual uint8 GetBotStance() const { return 0; }
        inline uint8 GetBotRoles() const { return _roleMask; }
        inline bool HasRole(uint8 role) const { return _roleMask & role; }
        void ToggleRole(uint8 role);
        char const* GetRoleString(uint8 role) const;

        virtual void OnBotSummon(Creature* /*summon*/) {}
        virtual void OnBotDespawn(Creature* /*summon*/) {}
        virtual void UnsummonAll() {}

        void ReceiveEmote(Player* player, uint32 emote);
        void ApplyPassives(uint8 botOrPetType) const;

        virtual void RemoveItemBonuses(uint8 /*slot*/) {}
        virtual void ApplyItemBonuses(uint8 /*slot*/) {}

        static inline bool CCed(Unit* target, bool root = false)
        {
            return target ? target->HasUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_STUNNED | UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED | UNIT_STATE_CONFUSED_MOVE | UNIT_STATE_FLEEING_MOVE) || (root && target->HasUnitState(UNIT_STATE_ROOT)) : true;
        }

        virtual bool CanUseOffHand() const { return false; }
        virtual bool CanUseRanged() const { return false; }
        virtual bool CanEquip(ItemTemplate const* /*item*/, uint8 /*slot*/) const { return false; }
        virtual bool Unequip(uint8 /*slot*/) { return false; }
        virtual bool Equip(uint32 /*itemId*/, uint8 /*slot*/) { return false; }
        virtual bool ResetEquipment(uint8 /*slot*/) { return false; }

        static void BotSpeak(std::string const& text, uint8 msgtype, uint32 language, uint64 sender, uint64 receiver);

        virtual void JustDied(Unit*);

    protected:
        static uint32 InitSpell(Unit const* caster, uint32 spell);
        void InitSpellMap(uint32 basespell, bool forceadd = false);
        uint32 GetSpell(uint32 basespell) const;
        uint32 GetSpellCooldown(uint32 basespell) const;
        bool IsSpellReady(uint32 basespell, uint32 diff, bool checkGCD = true, uint32 forcedTime = 0) const;
        void SetSpellCooldown(uint32 basespell, uint32 msCooldown);
        void ResetSpellCooldown(uint32 basespell) { SetSpellCooldown(basespell, 0); }
        void RemoveSpell(uint32 basespell);
        void SpellTimers(uint32 diff);

        void InitRoles();
        bool IsTank(Unit* unit = NULL) const;

        bool HasAuraName(Unit* unit, uint32 spellId, uint64 casterGuid = 0, bool exclude = false) const;
        bool RefreshAura(uint32 spell, int8 count = 1) const;
        bool CheckAttackTarget(uint8 botOrPetType);
        bool MoveBehind(Unit &target) const;
        bool CheckImmunities(uint32 spell, Unit* target = NULL) const { return (spell && target && !target->ToCorpse() && target->IsHostileTo(me) ? !target->IsImmunedToDamage(sSpellMgr->GetSpellInfo(spell)) : true); }

        //everything cast-related
        bool doCast(Unit* victim, uint32 spellId, bool triggered = false, uint64 originalCaster = 0);
        SpellCastResult CheckBotCast(Unit* victim, uint32 spellId, uint8 botclass) const;
        virtual void removeFeralForm(bool /*force*/ = false, bool /*init*/ = true, uint32 /*diff*/ = 0) {}

        inline bool Feasting() const { return (me->HasAura(EAT) || me->HasAura(DRINK)); }
        inline bool IsMeleeClass(uint8 m_class) const { return (m_class == CLASS_WARRIOR || m_class == CLASS_ROGUE || m_class == CLASS_PALADIN || m_class == CLASS_DEATH_KNIGHT); }
        inline bool IsTankingClass(uint8 m_class) const { return (m_class == CLASS_WARRIOR || m_class == CLASS_PALADIN || m_class == CLASS_DEATH_KNIGHT); }
        inline bool IsChanneling(Unit* u = NULL) const { if (!u) u = me; return u->GetCurrentSpell(CURRENT_CHANNELED_SPELL); }
        inline bool IsCasting(Unit* u = NULL) const { if (!u) u = me; return (u->HasUnitState(UNIT_STATE_CASTING) || IsChanneling(u) || u->IsNonMeleeSpellCast(false, false, true)); }

        void GetInPosition(bool force = false, Unit* newtarget = NULL, Position* pos = NULL);
        void OnSpellHit(Unit* caster, SpellInfo const* spell);
        void CalculateAttackPos(Unit* target, Position &pos) const;
        void CheckAttackState();
        inline virtual void Evade() {}

        //virtual void ApplyClassDamageMultiplierMelee(uint32& /*damage*/, CalcDamageInfo& /*damageinfo*/) const {}
        virtual void ApplyClassDamageMultiplierMelee(int32& /*damage*/, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* /*spellInfo*/, WeaponAttackType /*attackType*/, bool& /*crit*/) const {}
        virtual void ApplyClassDamageMultiplierSpell(int32& /*damage*/, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* /*spellInfo*/, WeaponAttackType /*attackType*/, bool& /*crit*/) const {}
        virtual void ApplyClassDamageMultiplierEffect(SpellInfo const* /*spellInfo*/, uint8 /*effect_index*/, float& /*value*/) const {}
        virtual void CureGroup(Player* /*pTarget*/, uint32 /*cureSpell*/, uint32 /*diff*/) {}
        virtual void CheckAuras(bool /*force*/ = false) {}
        virtual void BuffAndHealGroup(Player* /*gPlayer*/, uint32 /*diff*/) {}
        virtual void RezGroup(uint32 /*REZZ*/, Player* /*gPlayer*/) {}
        //virtual void DoNonCombatActions(uint32 /*diff*/) {}
        //virtual void StartAttack(Unit* /*u*/, bool /*force*/ = false) {}
        virtual void InitSpells() {}
        virtual void InitPowers() {}
        virtual void ApplyClassPassives() {}
        virtual void _OnHealthUpdate() const = 0;
        virtual void _OnManaUpdate(bool /*shapeshift*/ = false) = 0;
        //virtual void _OnMeleeDamageUpdate(uint8 /*myclass*/) const = 0;

        //virtual void ReceiveEmote(Player* /*player*/, uint32 /*emote*/) {}
        //virtual void CommonTimers(uint32 diff) = 0;

        virtual bool HealTarget(Unit* /*target*/, uint8 /*pct*/, uint32 /*diff*/) { return false; }
        virtual bool BuffTarget(Unit* /*target*/, uint32 /*diff*/) { return false; }
        virtual bool CureTarget(Unit* /*target*/, uint32 /*cureSpell*/, uint32 /*diff*/) { return false; }
        virtual bool IsMelee() const { return HasRole(BOT_ROLE_DPS) && !HasRole(BOT_ROLE_RANGED); }
        virtual bool CanHeal() const { return false; }

        uint8 GetWait();
        inline float InitAttackRange(float origRange, bool ranged) const;
        uint16 Rand() const;
        static inline uint32 GetLostHP(Unit* unit) { return unit->GetMaxHealth() - unit->GetHealth(); }
        static inline uint8 GetHealthPCT(Unit* hTarget) { if (!hTarget || hTarget->isDead()) return 100; return (hTarget->GetHealth()*100/hTarget->GetMaxHealth()); }
        static inline uint8 GetManaPCT(Unit* hTarget) { if (!hTarget || hTarget->isDead() || hTarget->getPowerType() != POWER_MANA) return 100; return (hTarget->GetPower(POWER_MANA)*100/(hTarget->GetMaxPower(POWER_MANA) + 1)); }

        typedef std::set<Unit*> AttackerSet;
        typedef UNORDERED_MAP<uint32 /*stat*/, int32 /*statvalue*/> BotStat;
        typedef std::pair<uint32 /*spellId*/, uint32 /*cooldown*/> BotCTCSpell;

        BotStat _stats[BOT_MAX_SLOTS - 1];
        BotCTCSpell _ctc[MAX_BOT_CTC_SPELLS];
        uint32 CalcCTC(uint32 /*spellId*/) const { return 8; } //placeholder

        //utilities
        void _AddItemTemplateLink(Player* forPlayer, ItemTemplate const* item, std::ostringstream &str) const;
        void _AddItemLink(Player* forPlayer, Item const* item, std::ostringstream &str) const;
        void _AddQuestLink(Player* forPlayer, Quest const* quest, std::ostringstream &str) const;
        void _AddWeaponSkillLink(Player* forPlayer, SpellInfo const* spellInfo, std::ostringstream &str, uint32 skillid) const;
        void _AddSpellLink(Player* forPlayer, SpellInfo const* spellInfo, std::ostringstream &str) const;
        void _AddProfessionLink(Player* forPlayer, SpellInfo const* spellInfo, std::ostringstream &str, uint32 skillId) const;
        void _LocalizeItem(Player* forPlayer, std::string &itemName, uint32 entry) const;
        void _LocalizeQuest(Player* forPlayer, std::string &questTitle, uint32 entry) const;
        void _LocalizeCreature(Player* forPlayer, std::string &creatureName, uint32 entry) const;
        void _LocalizeGameObject(Player* forPlayer, std::string &gameobjectName, uint32 entry) const;

        typedef std::pair<uint32 /*spellId*/, uint32 /*cooldown*/> BotSpell;
        typedef UNORDERED_MAP<uint32 /*spellId_1*/, BotSpell /*spell*/> BotSpellMap;

        BotSpellMap const& GetSpellMap() const { return spells; }

        Player* master;
        Unit* opponent;
        CommandStates m_botCommandState;
        SpellInfo const* m_botSpellInfo;
        Position pos, attackpos;
        float stat, atpower, maxdist, regen_mp5, hit,
            ap_mod, spp_mod, crit_mod;
        uint64 aftercastTargetGuid;
        int32 cost, value, sppower, m_spellpower, m_expertise, m_spellpen;
        uint32 GC_Timer, temptimer, checkAurasTimer, roleTimer, wait, currentSpell, tempMana, m_block;
        uint8 clear_cd, haste, healTargetIconFlags;
        bool doHealth, doMana, shouldUpdateStats;

    private:
        Unit* _getTarget(bool byspell, bool ranged, bool &reset) const;
        bool _hasAuraName(Unit* unit, const std::string spell, uint64 casterGuid = 0, bool exclude = false) const;
        void _listAuras(Player* player, Unit* unit) const;
        static inline float _getAttackDistance(float distance) { return distance > 0.f ? distance*0.72 : 0.f; }

        BotSpellMap spells;
        uint8 _roleMask;
        float dmgmult_melee, dmgmult_spell;
        float dmgmod_melee, dmgmod_spell;
        uint64 m_TankGuid;
};

class bot_minion_ai : public bot_ai
{
    public:
        virtual ~bot_minion_ai();
        bot_minion_ai(Creature* creature);
        const bot_minion_ai* GetMinionAI() const { return this; }
        bool IsMinionAI() const { return true; }
        bool IsPetAI() const { return false; }
        void SummonBotsPet(uint32 entry);
        inline bool IAmDead() const { return (!master || me->isDead()); }
        void SetBotCommandState(CommandStates st, bool force = false, Position* newpos = NULL);
        //virtual bool HealTarget(Unit* /*target*/, uint8 /*pct*/, uint32 /*diff*/) { return false; }
        //virtual bool BuffTarget(Unit* /*target*/, uint32 /*diff*/) { return false; }
        //virtual bool doCast(Unit*  /*victim*/, uint32 /*spellId*/, bool /*triggered*/ = false) { return false; }
        void CureGroup(Player* pTarget, uint32 cureSpell, uint32 diff);
        bool CureTarget(Unit* target, uint32 cureSpell, uint32 diff);
        void CheckAuras(bool force = false);
        //virtual void DoNonCombatActions(uint32 /*diff*/) {}
        //virtual void StartAttack(Unit* /*u*/, bool /*force*/ = false) {}
        void SetStats(bool force, bool shapeshift = false);
        virtual uint8 GetBotStance() const { return me->GetBotClass(); }

        static bool OnGossipHello(Player* player, Creature* creature);
        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action);

        void InitSpells() {}
        void InitPowers() {}
        void _OnHealthUpdate() const;
        void _OnManaUpdate(bool shapeshift = false);
        void _OnMeleeDamageUpdate(uint8 myclass) const;

        void RemoveItemBonuses(uint8 slot);
        void ApplyItemBonuses(uint8 slot);

        void OnOwnerDamagedBy(Unit* attacker);

        inline void SetEvadeTimer(uint8 time) { evade_cd = time; }

        bool CanUseOffHand() const;
        bool CanUseRanged() const;
        bool CanEquip(ItemTemplate const* item, uint8 slot) const;
        bool Unequip(uint8 slot);
        bool Equip(uint32 itemId, uint8 slot);
        bool ResetEquipment(uint8 slot);

        bool CanHeal() const;

    protected:
        virtual bool CanUseManually(uint32 /*basespell*/) const { return false; }
        void BuffAndHealGroup(Player* gPlayer, uint32 diff);
        void RezGroup(uint32 REZZ, Player* gPlayer);

        void Follow(bool force = false, Position* newpos = NULL)
        {
            if (force ||
                (me->IsAlive() && (!me->IsInCombat() || !opponent) && m_botCommandState != COMMAND_STAY))
                SetBotCommandState(COMMAND_FOLLOW, force, newpos);
        }

        inline void Evade() { _evade(); }

        virtual void BreakCC(uint32 diff);

        void CommonTimers(uint32 diff)
        {
            if (pvpTrinket_cd > diff)       pvpTrinket_cd -= diff;
            if (Potion_cd > diff)           Potion_cd -= diff;
            if (GC_Timer > diff)            GC_Timer -= diff;
            if (temptimer > diff)           temptimer -= diff;
            if (checkAurasTimer != 0)       --checkAurasTimer;
            if (wait != 0)                  --wait;
            if (evade_cd != 0)              --evade_cd;

            if (mana_cd > diff)             mana_cd -= diff;
            else if (mana_cd > 0)           mana_cd = 0;
            if (health_cd > diff)           health_cd -= diff;
            else if (health_cd > 0)         health_cd = 0;

            if (roleTimer > diff)           roleTimer -= diff;
            else if (roleTimer > 0)         roleTimer = 0;

            for (uint8 i = 0; i != MAX_BOT_CTC_SPELLS; ++i)
            {
                if (_ctc[i].second > diff)  _ctc[i].second -= diff;
                else                        _ctc[i].second = 0;
            }
        }

        Unit* FindHostileDispelTarget(float dist = 30, bool stealable = false) const;
        Unit* FindAffectedTarget(uint32 spellId, uint64 caster = 0, float dist = DEFAULT_VISIBILITY_DISTANCE, uint8 hostile = 0) const;
        Unit* FindPolyTarget(float dist = 30, Unit* currTarget = NULL) const;
        Unit* FindFearTarget(float dist = 30) const;
        Unit* FindStunTarget(float dist = 20) const;
        Unit* FindUndeadCCTarget(float dist = 30, uint32 spellId = 0) const;
        Unit* FindRootTarget(float dist = 30, uint32 spellId = 0) const;
        Unit* FindCastingTarget(float maxdist = 10, float mindist = 0, bool isFriend = false, uint32 spellId = 0) const;
        Unit* FindAOETarget(float dist = 30, bool checkbots = false, bool targetfriend = true) const;
        Unit* FindSplashTarget(float dist = 5, Unit* To = NULL, float splashdist = 4) const;
        Unit* FindTranquilTarget(float mindist = 5, float maxdist = 35) const;
        void GetNearbyTargetsList(std::list<Unit*> &targets, float maxdist = 10, float mindist = 0, bool forCC = false) const;

        uint32 Potion_cd;

    private:
        bool _canCureTarget(Unit* target, uint32 cureSpell, uint32 diff) const;
        void _getBotDispellableAuraList(Unit* target, Unit* caster, uint32 dispelMask, DispelChargesList& dispelList) const;
        void _calculatePos(Position& pos);
        void _updateMountedState();
        void _updateStandState() const;
        void _updateRations();
        void _evade();
        char const* _getNameForSlot(uint8 slot) const;
        uint8 const _onOffIcon(uint8 role) const;
        //BotClassLevelInfo classinfo;
        PlayerClassLevelInfo* _classinfo;
        float myangle, armor_mod, haste_mod, dodge_mod, parry_mod;
        uint32 mana_cd, health_cd, pvpTrinket_cd;
        uint8 rezz_cd, evade_cd;
};

class bot_pet_ai : public bot_ai
{
    public:
        virtual ~bot_pet_ai();
        bot_pet_ai(Creature* creature);
        const bot_pet_ai* GetPetAI() const { return this; }
        Creature* GetCreatureOwner() const { return m_creatureOwner; }
        bool IsMinionAI() const { return false; }
        bool IsPetAI() const { return true; }
        inline bool IAmDead() const { return (!master || !m_creatureOwner || me->isDead()); }
        //void SetCreatureOwner(Creature* newowner) { m_creatureOwner = newowner; }
        void SetBotCommandState(CommandStates st, bool force = false, Position* newpos = NULL);
        //virtual bool HealTarget(Unit* /*target*/, uint8 /*pct*/, uint32 /*diff*/) { return false; }
        //virtual bool BuffTarget(Unit* /*target*/, uint32 /*diff*/) { return false; }
        //void BuffAndHealGroup(Player* /*gPlayer*/, uint32 /*diff*/) {}
        //void RezGroup(uint32 /*REZZ*/, Player* /*gPlayer*/) {}
        //virtual bool doCast(Unit*  /*victim*/, uint32 /*spellId*/, bool /*triggered*/ = false) { return false; }
        //void CureGroup(Player* /*pTarget*/, uint32 /*cureSpell*/, uint32 /*diff*/) {}
        //bool CureTarget(Unit* /*target*/, uint32 /*cureSpell*/, uint32 /*diff*/) { return false; }
        void CheckAuras(bool force = false);
        //virtual void DoNonCombatActions(uint32 /*diff*/) {}
        //virtual void StartAttack(Unit* /*u*/, bool /*force*/ = false) {}
        void SetStats(bool force);

        static uint8 GetPetType(Creature* pet);
        static uint8 GetPetClass(Creature* pet);
        static uint32 GetPetOriginalEntry(uint32 entry);

        //debug
        //virtual void ListSpells(ChatHandler* /*handler*/) const {}

        void InitSpells() {}
        void _OnHealthUpdate() const;
        void _OnManaUpdate(bool shapeshift = false);
        //void _OnMeleeDamageUpdate(uint8 /*myclass*/) const {}
        void SetBaseArmor(uint32 armor) { basearmor = armor; }

    protected:
        void CommonTimers(uint32 diff)
        {
            if (GC_Timer > diff)            GC_Timer -= diff;
            if (temptimer > diff)           temptimer -= diff;
            if (roleTimer > diff)           roleTimer -= diff;
            if (checkAurasTimer != 0)       --checkAurasTimer;
            if (wait != 0)                  --wait;
        }

        Creature* m_creatureOwner;
    private:
        uint32 basearmor;
};

#endif
