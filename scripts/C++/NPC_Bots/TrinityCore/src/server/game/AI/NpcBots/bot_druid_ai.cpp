#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "WorldSession.h"
/*
Druid NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - Maybe 30%
TODO: Feral Spells (from scratch), More Forms, Balance Spells + treants...
*/
class druid_bot : public CreatureScript
{
public:
    druid_bot() : CreatureScript("druid_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new bot_druid_ai(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        return bot_minion_ai::OnGossipHello(player, creature);
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (bot_minion_ai* ai = creature->GetBotMinionAI())
            return ai->OnGossipSelect(player, creature, sender, action);
        return true;
    }

    struct bot_druid_ai : public bot_minion_ai
    {
        bot_druid_ai(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (CheckBotCast(victim, spellId, CLASS_DRUID) != SPELL_CAST_OK)
                return false;

            m_botSpellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (me->GetShapeshiftForm() == FORM_NONE && swiftness && m_botSpellInfo->CalcCastTime() > 0)
            {
                DoCast(victim, spellId, true);
                me->RemoveAurasDueToSpell(NATURES_SWIFTNESS_1, me->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
                me->RemoveAurasDueToSpell(CRIT_50, me->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
                swiftness = false;
                return true;
            }
            if (spellId == GetSpell(BEAR_FORM_1) || GetSpell(spellId == CAT_FORM_1))
            {
                me->ModifyPower(POWER_MANA, - int32(m_botSpellInfo->CalcPowerCost(me, m_botSpellInfo->GetSchoolMask())));
                mana = me->GetPower(POWER_MANA);
                if (Unit* u = me->GetVictim())
                    GetInPosition(true, u);
            }

            bool result = bot_ai::doCast(victim, spellId, triggered);

            if (result &&
                //spellId != GetSpell(BEAR_FORM_1) && spellId != GetSpell(spellId == CAT_FORM_1) &&
                spellId != MANAPOTION && spellId != WARSTOMP_1 &&
                me->HasAura(OMEN_OF_CLARITY_BUFF))
            {
                cost = m_botSpellInfo->CalcPowerCost(me, m_botSpellInfo->GetSchoolMask());
                clearcast = true;
                power = me->getPowerType();
            }
            return result;
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit* u) { removeFeralForm(true, false); bot_ai::JustDied(u); }

        uint8 GetBotStance() const
        {
            switch (me->GetShapeshiftForm())
            {
                case FORM_BEAR:
                case FORM_DIREBEAR:
                    return DRUID_BEAR_FORM;
                case FORM_CAT:
                    return DRUID_CAT_FORM;
            }

            return CLASS_DRUID;
        }

        void warstomp(uint32 diff)
        {
            if (me->getRace() != RACE_TAUREN) return;
            if (IsSpellReady(WARSTOMP_1, diff, false)) return;
            if (me->GetShapeshiftForm() != FORM_NONE)
                return;

            AttackerSet b_attackers = me->getAttackers();

            if (b_attackers.empty())
            {
                Unit* u = me->SelectNearestTarget(5);
                if (u && u->IsInCombat() && u->isTargetableForAttack())
                {
                    if (doCast(me, WARSTOMP_1))
                    {
                        SetSpellCooldown(WARSTOMP_1, 30000); //30sec
                        return;
                    }
                }
            }
            for (AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
            {
                if (!(*iter) || (*iter)->isDead()) continue;
                if (!(*iter)->isTargetableForAttack()) continue;
                if (me->GetDistance((*iter)) <= 5)
                {
                    if (doCast(me, WARSTOMP_1))
                        SetSpellCooldown(WARSTOMP_1, 30000); //30sec
                }
            }
        }

        bool DamagePossible()
        {
            return true;
            //return (GetManaPCT(me) < 30 || GetHealthPCT(master) < 50);
            /*if (GetHealthPCT(master) < 75 || GetHealthPCT(me) < 75) return false;

            if (Group* pGroup = master->GetGroup())
            {
                uint8 LHPcount = 0;
                uint8 DIScount = 0;
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (!tPlayer || tPlayer->isDead()) continue;
                    if (me->GetExactDist(tPlayer) > 30) continue;
                    if (tPlayer->GetHealth()*100 / tPlayer->GetMaxHealth() < 75)
                        ++LHPcount;
                    Unit::AuraApplicationMap const& auras = tPlayer->GetAppliedAuras();
                    for (Unit::AuraApplicationMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                        if (itr->second->GetBase()->GetSpellInfo()->Dispel == DISPEL_POISON)
                            ++DIScount;
                }
                uint8 members = master->GetGroup()->GetMembersCount();

                if (members > 10)
                {
                    if (LHPcount > 1 || DIScount > 2) return false;
                }
                if (members > 4)
                {
                    if (LHPcount > 0 || DIScount > 1) return false;
                }
                if (members < 5)
                {
                    if (LHPcount > 0 || DIScount > 0) return false;
                }
            }//endif unitlist

            Unit* u = master->GetVictim();
            if (master->getAttackers().size() > 4 ||
              (!master->getAttackers().empty() &&
                u != NULL && u->GetHealth() > me->GetMaxHealth()*17))
                return false;

            return true;*/
        }

        void removeFeralForm(bool force = false, bool init = true, uint32 diff = 0)
        {
            if (!force && formtimer > diff) return;
            ShapeshiftForm form = me->GetShapeshiftForm();
            if (form != FORM_NONE)
            {
                switch (form)
                {
                    case FORM_DIREBEAR:
                    case FORM_BEAR:
                        me->RemoveAurasDueToSpell(GetSpell(BEAR_FORM_1));
                        break;
                    case FORM_CAT:
                        me->RemoveAurasDueToSpell(GetSpell(CAT_FORM_1));
                        me->RemoveAurasDueToSpell(ENERGIZE);
                        break;
                    default:
                        break;
                }
                setStats(CLASS_DRUID, init);
            }
        }

        bool IsMelee() const
        {
            if (GetBotStance() == DRUID_BEAR_FORM || GetBotStance() == DRUID_CAT_FORM)
                return true;

            return bot_ai::IsMelee();
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            SetBotCommandState(COMMAND_ATTACK);
            GetInPosition(force);
        }

        void doBearActions(uint32 diff)
        {
            if (me->getPowerType() != POWER_RAGE) return;

            if (GetHealthPCT(me) < 75)
                if (HealTarget(me, GetHealthPCT(me), diff))
                    return;
            opponent = me->GetVictim();
            if (opponent)
                StartAttack(opponent, true);
            else
                return;

            //range check (melee) to prevent fake casts
            if (me->GetDistance(opponent) > 5) return;

            if (IsSpellReady(MANGLE_BEAR_1, diff) && HasRole(BOT_ROLE_DPS) && rage >= 150 && Rand() < 35 &&
                doCast(opponent, GetSpell(MANGLE_BEAR_1)))
            {
                SetSpellCooldown(MANGLE_BEAR_1, 6000);
                return;
            }

            if (IsSpellReady(SWIPE_1, diff) && HasRole(BOT_ROLE_DPS) && rage >= 150 && Rand() < 75 &&
                doCast(opponent, GetSpell(SWIPE_1)))
                return;

        }//end doBearActions

        void doCatActions(uint32 diff)
        {
            if (me->getPowerType() != POWER_ENERGY) return;

            if (GetHealthPCT(me) < 75)
                if (HealTarget(me, GetHealthPCT(me), diff))
                    return;
            opponent = me->GetVictim();
            if (opponent)
                StartAttack(opponent, true);
            else
                return;

            uint32 energy = me->GetPower(POWER_ENERGY);

            if (MoveBehind(*opponent))
                wait = 5;

            //range check (melee) to prevent fake casts
            if (me->GetDistance(opponent) > 5) return;

            if (IsSpellReady(MANGLE_CAT_1, diff) && energy > 45 && HasRole(BOT_ROLE_DPS) && Rand() < 35 &&
                doCast(opponent, GetSpell(MANGLE_CAT_1)))
            {
                SetSpellCooldown(MANGLE_CAT_1, 6000);
                return;
            }
            if (IsSpellReady(RAKE_1, diff) && energy > 40 && HasRole(BOT_ROLE_DPS) && Rand() < 30 &&
                doCast(opponent, GetSpell(RAKE_1)))
            {
                SetSpellCooldown(RAKE_1, 10000);
                return;
            }
            if (IsSpellReady(SHRED_1, diff) && energy > 60 && HasRole(BOT_ROLE_DPS) && !opponent->HasInArc(M_PI, me) && Rand() < 50 &&
                doCast(opponent, GetSpell(SHRED_1)))
            {
                SetSpellCooldown(SHRED_1, 12000);
                return;
            }
            if (IsSpellReady(RIP_1, diff) && energy > 30 && HasRole(BOT_ROLE_DPS) && Rand() < 30 &&
                doCast(opponent, GetSpell(RIP_1)))
            {
                SetSpellCooldown(RIP_1, 15000);
                return;
            }
            if (IsSpellReady(CLAW_1, diff) && energy > 45 && HasRole(BOT_ROLE_DPS) && Rand() < 80 &&
                doCast(opponent, GetSpell(CLAW_1)))
                return;
        }//end doCatActions

        void doBalanceActions(uint32 diff)
        {
            removeFeralForm(true, true);
            opponent = me->GetVictim();
            if (opponent)
            {
                if (!IsCasting())
                    StartAttack(opponent);
            }
            else
                return;

            AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();

            //range check to prevent fake casts
            if (me->GetExactDist(opponent) > 30 || !DamagePossible()) return;

            if (IsSpellReady(HURRICANE_1, diff) && !me->isMoving() && HasRole(BOT_ROLE_DPS) && Rand() < 35)
            {
                Unit* target = FindAOETarget(30, true);
                if (target && doCast(target, GetSpell(HURRICANE_1)))
                {
                    SetSpellCooldown(HURRICANE_1, 5000);
                    return;
                }
                SetSpellCooldown(HURRICANE_1, 2000); //fail
            }
            if (uint32 FAERIE_FIRE = GetSpell(FAERIE_FIRE_1))
            {
                if (GC_Timer <= diff &&
                    opponent->getAttackers().size() > 1 &&//check if faerie fire is not useless 50/50
                    Rand() < 20 && !HasAuraName(opponent, FAERIE_FIRE_1))
                {
                    if (doCast(opponent, FAERIE_FIRE))
                        return;
                }
            }
            if (IsSpellReady(MOONFIRE_1, diff) && HasRole(BOT_ROLE_DPS) && Rand() < 20 &&
                !HasAuraName(opponent, MOONFIRE_1, me->GetGUID()))
            {
                if (doCast(opponent, GetSpell(MOONFIRE_1)))
                {
                    SetSpellCooldown(MOONFIRE_1, 5000);
                    return;
                }
            }
            if (IsSpellReady(STARFIRE_1, diff) && HasRole(BOT_ROLE_DPS) && Rand() < 50)
            {
                if (doCast(opponent, GetSpell(STARFIRE_1)))
                {
                    SetSpellCooldown(STARFIRE_1, 11000);
                    return;
                }
            }
            if (IsSpellReady(WRATH_1, diff) && HasRole(BOT_ROLE_DPS) && Rand() < 40)
            {
                if (doCast(opponent, GetSpell(WRATH_1)))
                {
                    SetSpellCooldown(WRATH_1, uint32(sSpellMgr->GetSpellInfo(GetSpell(WRATH_1))->CalcCastTime()/100 * me->GetFloatValue(UNIT_MOD_CAST_SPEED) + 1));
                    return;
                }
            }
        }

        bool MassGroupHeal(Player* gPlayer, uint32 diff)
        {
            if (!gPlayer || GC_Timer > diff) return false;
            if (IsCasting()) return false; // if I'm already casting
            bool tranq = IsSpellReady(TRANQUILITY_1, diff, false);
            bool growt = IsSpellReady(WILD_GROWTH_1, diff, false);
            if (!tranq && !growt) return false;
            if (Rand() > 30) return false;
            Group* pGroup = gPlayer->GetGroup();
            if (!pGroup) return false;
            uint8 LHPcount = 0;
            uint8 pct = 100;
            Unit* healTarget = NULL;
            for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* tPlayer = itr->GetSource();
                if (!tPlayer || !tPlayer->IsInWorld() || tPlayer->GetMapId() != me->GetMapId() ||
                    (tPlayer->isDead() && !tPlayer->HaveBot())) continue;
                if (me->GetExactDist(tPlayer) > 39) continue;
                if (GetHealthPCT(tPlayer) < 80)
                {
                    if (GetHealthPCT(tPlayer) < pct)
                    {
                        pct = GetHealthPCT(tPlayer);
                        healTarget = tPlayer;
                    }
                    ++LHPcount;
                    if (LHPcount > 2) break;
                }
                if (tPlayer->HaveBot())
                {
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (bot && bot->IsInWorld() && bot->GetExactDist(me) < 40 && GetHealthPCT(bot) < 80)
                        {
                            if (GetHealthPCT(bot) < pct)
                            {
                                pct = GetHealthPCT(bot);
                                healTarget = bot;
                            }
                            ++LHPcount;
                            if (LHPcount > 2) break;
                        }
                    }
                }
            }
            if (LHPcount > 2 && tranq &&
                doCast(me, GetSpell(TRANQUILITY_1)))
            {
                SetSpellCooldown(TRANQUILITY_1, 60000);
                return true;
            }
            if (LHPcount > 0 && growt && healTarget &&
                doCast(healTarget, GetSpell(WILD_GROWTH_1)))
            {
                SetSpellCooldown(WILD_GROWTH_1, 6000);
                return true;
            }
            return false;
        }//end MassGroupHeal

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if ((me->GetShapeshiftForm() == FORM_DIREBEAR || me->GetShapeshiftForm() == FORM_BEAR) &&
                me->getPowerType() != POWER_RAGE)
                me->setPowerType(POWER_RAGE);
            if (me->GetShapeshiftForm() == FORM_CAT && me->getPowerType() != POWER_ENERGY)
                me->setPowerType(POWER_ENERGY);
            if (me->GetShapeshiftForm() == FORM_NONE && me->getPowerType() != POWER_MANA)
                me->setPowerType(POWER_MANA);
            if (IAmDead()) return;
            CheckAttackState();

            if (me->GetShapeshiftForm() == FORM_DIREBEAR || me->GetShapeshiftForm() == FORM_BEAR)
            {
                rage = me->GetPower(POWER_RAGE);
                if (ragetimer2 <= diff)
                {
                    if (me->IsInCombat() && me->getLevel() >= 30)
                    {
                        if (rage < 990)
                            me->SetPower(POWER_RAGE, rage + uint32(10.f*rageIncomeMult));//1 rage per 2 sec
                        else
                            me->SetPower(POWER_RAGE, 1000);
                    }
                    ragetimer2 = 2000;
                }
                if (ragetimer <= diff)
                {
                    if (!me->IsInCombat())
                    {
                        if (rage > 10.f*rageLossMult)
                            me->SetPower(POWER_RAGE, rage - uint32(10.f*rageLossMult)); //-1 rage per 1.5 sec
                        else
                            me->SetPower(POWER_RAGE, 0);
                    }
                    ragetimer = 1500;
                    if (rage > 1000) me->SetPower(POWER_RAGE, 1000);
                    if (rage < 10) me->SetPower(POWER_RAGE, 0);
                }
            }
            if (clearcast && me->HasAura(OMEN_OF_CLARITY_BUFF) && !me->IsNonMeleeSpellCast(false))
            {
                me->ModifyPower(power, cost);
                me->RemoveAurasDueToSpell(OMEN_OF_CLARITY_BUFF,me->GetGUID(),0,AURA_REMOVE_BY_EXPIRE);
                clearcast = false;
            }
            CheckAuras();
            if (wait == 0)
                wait = GetWait();
            else
                return;
            BreakCC(diff);
            if (CCed(me)) return;
            warstomp(diff);

            if (Potion_cd <= diff && me->getPowerType() == POWER_MANA && GetManaPCT(me) < 20)
            {
                temptimer = GC_Timer;
                if (doCast(me, MANAPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }

            //Heal master
            if (GetHealthPCT(master) < 85)
                HealTarget(master, GetHealthPCT(master), diff);
            //Innervate
            doInnervate(diff);

            MassGroupHeal(master, diff);
            if (!me->IsInCombat())
                DoNonCombatActions(diff);
            else
                CheckBattleRez(diff);
            BuffAndHealGroup(master, diff);
            //CureTarget(master, GetSpell(CURE_POISON_1), diff);
            CureGroup(master, GetSpell(CURE_POISON_1), diff);

            if (!CheckAttackTarget(CLASS_DRUID))
                return;

            //debug
            opponent = me->GetVictim();

            if (GetHealthPCT(me) < 75)
            {
                HealTarget(me, GetHealthPCT(me), diff);
                return;
            }

            if (IsCasting()) return; //Casting heal or something
            CheckRoots(diff);

            if (DamagePossible() && opponent != NULL)
            {
                Unit* u = opponent->GetVictim();
                //if the target is attacking us, we want to go bear
                if (GetSpell(BEAR_FORM_1) && !CCed(opponent) &&
                    ((u == me || (IsTank() && IsInBotParty(u))) ||
                    (!me->getAttackers().empty() && (*me->getAttackers().begin()) == opponent && opponent->GetMaxHealth() > me->GetMaxHealth()*2)))
                {
                    //if we don't have bear yet
                    if (me->GetShapeshiftForm() != FORM_DIREBEAR &&
                        me->GetShapeshiftForm() != FORM_BEAR &&
                        formtimer <= diff &&
                        doCast(me, GetSpell(BEAR_FORM_1)))
                    {
                        setStats(DRUID_BEAR_FORM);
                        formtimer = 1500;
                    }
                    if (me->GetShapeshiftForm() == FORM_DIREBEAR ||
                        me->GetShapeshiftForm() == FORM_BEAR)
                        doBearActions(diff);
                }
                else
                if (GetSpell(CAT_FORM_1) && master->GetVictim() != opponent && u &&
                    IsTank(u) && u != me &&
                    opponent->GetMaxHealth() < u->GetMaxHealth()*3)
                {
                    //if we don't have cat yet
                    if (me->GetShapeshiftForm() != FORM_CAT && formtimer <= diff)
                    {
                        if (doCast(me, GetSpell(CAT_FORM_1)))
                        {
                            setStats(DRUID_CAT_FORM);
                            formtimer = 1500;
                        }
                    }
                    if (me->GetShapeshiftForm() == FORM_CAT)
                        doCatActions(diff);
                }
                else if (!IsTank())
                    doBalanceActions(diff);
            }
            else if (!IsTank())
                doBalanceActions(diff);
        }

        bool HealTarget(Unit* target, uint8 hp, uint32 diff)
        {
            if (!HasRole(BOT_ROLE_HEAL)) return false;
            if (hp > 95) return false;
            if (!target || target->isDead()) return false;
            if (IsTank() && hp > 35) return false;
            if (hp > 50 && me->GetShapeshiftForm() != FORM_NONE) return false; //do not waste heal if in feral or so
            if (Rand() > 50 + 20*target->IsInCombat() + 50*master->GetMap()->IsRaid() - 50*me->GetShapeshiftForm()) return false;
            if (me->GetExactDist(target) > 40) return false;

            if (IsSpellReady(NATURES_SWIFTNESS_1, diff, false) &&
                (hp < 15 || (hp < 35 && target->getAttackers().size() > 2)) &&
                (target->IsInCombat() || !target->getAttackers().empty()))
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);
                if (doCast(me, GetSpell(NATURES_SWIFTNESS_1)) && RefreshAura(CRIT_50, 2))
                {
                    swiftness = true;
                    SetSpellCooldown(NATURES_SWIFTNESS_1, 120000); //2 min
                    if (doCast(target, GetSpell(HEALING_TOUCH_1), true))
                        Heal_Timer = 3000;
                    return true;
                }
            }
            if (IsSpellReady(SWIFTMEND_1, diff, false, 3000) &&
                (hp < 25 || GetLostHP(target) > 5000) &&
                (HasAuraName(target, REGROWTH_1) || HasAuraName(target, REJUVENATION_1)))
            {
                if (doCast(target, GetSpell(SWIFTMEND_1)))
                {
                    SetSpellCooldown(SWIFTMEND_1, 10000);
                    if (GetHealthPCT(target) > 75)
                        return true;
                    else if (!target->getAttackers().empty())
                    {
                        if (doCast(target, GetSpell(REGROWTH_1)))
                        {
                            GC_Timer = 300;
                            return true;
                        }
                    }
                }
            }
            if (hp > 35 && (hp < 75 || GetLostHP(target) > 3000) && Heal_Timer <= diff && GetSpell(NOURISH_1))
            {
                switch (urand(1,3))
                {
                    case 1:
                    case 2:
                        if (doCast(target, GetSpell(NOURISH_1)))
                        {
                            Heal_Timer = 3000;
                            return true;
                        }
                        break;
                    case 3:
                        if (doCast(target, GetSpell(HEALING_TOUCH_1)))
                        {
                            Heal_Timer = 3000;
                            return true;
                        }
                        break;
                }
            }
            //maintain HoTs
            Unit* u = target->GetVictim();
            Creature* boss = u && u->ToCreature() && u->ToCreature()->isWorldBoss() ? u->ToCreature() : NULL;
            bool tanking = IsTank(target) && boss;
            bool regrowth = IsSpellReady(REGROWTH_1, diff);
            if ( ( (hp < 80 || GetLostHP(target) > 3500 || tanking) &&
                regrowth && !HasAuraName(target, REGROWTH_1, me->GetGUID()) )
                ||
                (HasAuraName(target, REGROWTH_1, me->GetGUID()) && HasAuraName(target, REJUVENATION_1, me->GetGUID()) &&
                (hp < 70 || GetLostHP(target) > 3000) && regrowth))
            {
                if (doCast(target, GetSpell(REGROWTH_1)))
                {
                    SetSpellCooldown(REGROWTH_1, 2000);
                    return true;
                }
            }
            if (GetSpell(REJUVENATION_1) && GC_Timer <= diff && hp > 25 &&
                (hp < 90 || GetLostHP(target) > 2000 || tanking) &&
                !HasAuraName(target, REJUVENATION_1, me->GetGUID()))
            {
                if (doCast(target, GetSpell(REJUVENATION_1)))
                {
                    if (!target->getAttackers().empty() && (hp < 75 || GetLostHP(target) > 4000))
                        if (IsSpellReady(SWIFTMEND_1, diff, false) && doCast(target, GetSpell(SWIFTMEND_1)))
                            SetSpellCooldown(SWIFTMEND_1, 10000);
                    GC_Timer = 500;
                    return true;
                }
            }
            if (IsSpellReady(LIFEBLOOM_1, diff) &&
                ((hp < 85 && hp > 40) || (hp > 70 && tanking) ||
                (hp < 70 && hp > 25 && HasAuraName(target, REGROWTH_1) && HasAuraName(target, REJUVENATION_1)) ||
                (GetLostHP(target) > 1500 && hp > 35)))
            {
                Aura* bloom = target->GetAura(GetSpell(LIFEBLOOM_1), me->GetGUID());
                if ((!bloom || bloom->GetStackAmount() < 3) && doCast(target, GetSpell(LIFEBLOOM_1)))
                    return true;
            }
            if (hp > 30 && (hp < 70 || GetLostHP(target) > 3000) && Heal_Timer <= diff &&
                doCast(target, GetSpell(HEALING_TOUCH_1)))
            {
                Heal_Timer = 3000;
                return true;
            }
            return false;
        }

        bool BuffTarget(Unit* target, uint32 diff)
        {
            if (GC_Timer > diff || Rand() > 20) return false;
            if (me->IsInCombat() && !master->GetMap()->IsRaid()) return false;
            if (target && target->IsAlive() && me->GetExactDist(target) < 30)
            {
                if (uint32 MARK_OF_THE_WILD = GetSpell(MARK_OF_THE_WILD_1))
                    if (!HasAuraName(target, MARK_OF_THE_WILD_1))
                        if (doCast(target, MARK_OF_THE_WILD))
                            return true;
                if (uint32 THORNS = GetSpell(THORNS_1))
                    if (!HasAuraName(target, THORNS_1))
                        if (doCast(target, THORNS))
                            return true;
            }
            return false;
        }

        void DoNonCombatActions(uint32 diff)
        {
            if (GC_Timer > diff || IsCasting() || me->IsMounted()) return;

            RezGroup(GetSpell(REVIVE_1), master);

            //if (Feasting()) return;

            //if (BuffTarget(master, diff))
            //{
            //    /*GC_Timer = 800;*/
            //    return;
            //}
            //if (BuffTarget(me, diff))
            //{
            //    /*GC_Timer = 800;*/
            //    return;
            //}
        }

        void doInnervate(uint32 diff, uint8 minmanaval = 30)
        {
            if (!IsSpellReady(INNERVATE_1, diff) || Rand() > 15)
                return;
            if (me->GetShapeshiftForm() != FORM_NONE && (IsTank() || me->getAttackers().size() > 3))
                return;

            uint32 INNERVATE = GetSpell(INNERVATE_1);
            Unit* iTarget = NULL;

            if (master->IsInCombat() && master->getPowerType() == POWER_MANA &&
                GetManaPCT(master) < 20 && !master->HasAura(INNERVATE))
                iTarget = master;
            else if (me->IsInCombat() && me->getPowerType() == POWER_MANA &&
                GetManaPCT(me) < 20 && !me->HasAura(INNERVATE))
                iTarget = me;

            Group* group = master->GetGroup();
            if (!iTarget && !group) //first check master's bots
            {
                for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
                {
                    Creature* bot = master->GetBotMap(i)->_Cre();
                    if (!bot || !bot->IsInCombat() || bot->isDead()) continue;
                    if (me->GetExactDist(bot) > 30) continue;
                    if (bot->getPowerType() != POWER_MANA) continue;
                    if (GetManaPCT(bot) < minmanaval && !bot->HasAura(INNERVATE))
                    {
                        iTarget = bot;
                        break;
                    }
                }
            }
            if (!iTarget && group) //cycle through player members...
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (tPlayer == NULL || !tPlayer->IsInWorld() || !tPlayer->IsInCombat() || tPlayer->isDead()) continue;
                    if (me->GetExactDist(tPlayer) > 30) continue;
                    if (tPlayer->getPowerType() != POWER_MANA) continue;
                    if (GetManaPCT(tPlayer) < minmanaval && !tPlayer->HasAura(INNERVATE))
                    {
                        iTarget = tPlayer;
                        break;
                    }
                    if (iTarget)
                        break;
                }
            }
            if (!iTarget && group) //... and their bots.
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (tPlayer == NULL || !tPlayer->HaveBot()) continue;
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (!bot || bot->isDead()) continue;
                        if (me->GetExactDist(bot) > 30) continue;
                        if (bot->getPowerType() != POWER_MANA) continue;
                        if (GetManaPCT(bot) < minmanaval && !bot->HasAura(INNERVATE))
                        {
                            iTarget = bot;
                            break;
                        }
                    }
                    if (iTarget)
                        break;
                }
            }

            //fail
            if (!iTarget)
            {
                SetSpellCooldown(INNERVATE_1, 3000);
                return;
            }

            if (doCast(iTarget, INNERVATE))
            {
                if (iTarget->GetTypeId() == TYPEID_PLAYER)
                    me->MonsterWhisper("Innervate on You!", iTarget->ToPlayer());
                else
                {
                    std::ostringstream msg;
                    msg << "Innervate on " << (iTarget == me ? "myself" : iTarget->GetName()) << '!';
                    me->MonsterWhisper(msg.str().c_str(), master);
                }

                SetSpellCooldown(INNERVATE_1, iTarget->GetTypeId() == TYPEID_PLAYER ? 60000 : 20000); //1 min if player and 20 sec if bot
            }
        }

        void CheckRoots(uint32 diff)
        {
            if (GC_Timer > diff || Rand() > 35) return;
            if (me->GetShapeshiftForm() != FORM_NONE) return;
            uint32 ENTANGLING_ROOTS = GetSpell(ENTANGLING_ROOTS_1);
            if (!ENTANGLING_ROOTS) return;
            if (FindAffectedTarget(ENTANGLING_ROOTS, me->GetGUID(), 60)) return;
            if (Unit* target = FindRootTarget(30, ENTANGLING_ROOTS))
                if (doCast(target, ENTANGLING_ROOTS))
                    return;
        }

        void CheckBattleRez(uint32 diff)
        {
            if (!IsSpellReady(REBIRTH_1, diff, false) || me->IsMounted() || IsCasting() || Rand() > 10) return;

            Group* gr = master->GetGroup();
            if (!gr)
            {
                Unit* target = master;
                if (master->IsAlive()) return;
                if (master->isResurrectRequested()) return; //ressurected
                if (master->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                    target = (Unit*)master->GetCorpse();
                if (!target || !target->IsInWorld())
                    return;
                if (me->GetExactDist(target) > 30)
                {
                    me->GetMotionMaster()->MovePoint(master->GetMapId(), *target);
                    SetSpellCooldown(REBIRTH_1, 1500);
                    return;
                }
                else if (!target->IsWithinLOSInMap(me))
                    me->Relocate(*target);

                if (doCast(target, GetSpell(REBIRTH_1))) //rezzing
                {
                    me->MonsterWhisper("Rezzing You", master);
                    SetSpellCooldown(REBIRTH_1, me->getLevel() >= 60 ? 300000 : 600000); //5-10 min (improved possible)
                }
                return;
            }
            for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* tPlayer = itr->GetSource();
                Unit* target = tPlayer;
                if (!tPlayer || tPlayer->IsAlive()) continue;
                if (tPlayer->isResurrectRequested()) continue; //ressurected
                if (tPlayer->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                    target = (Unit*)tPlayer->GetCorpse();
                if (!target || !target->IsInWorld()) continue;
                if (master->GetMap() != target->FindMap()) continue;
                if (me->GetExactDist(target) > 30)
                {
                    me->GetMotionMaster()->MovePoint(target->GetMapId(), *target);
                    SetSpellCooldown(REBIRTH_1, 1500);
                    return;
                }
                else if (!target->IsWithinLOSInMap(me))
                    me->Relocate(*target);

                if (doCast(target, GetSpell(REBIRTH_1))) //rezzing
                {
                    me->MonsterWhisper("Rezzing You", tPlayer);
                    SetSpellCooldown(REBIRTH_1, me->getLevel() >= 60 ? 300000 : 600000); //5-10 min (improved possible)
                    return;
                }
            }
        }

        void setStats(uint8 form, bool init = true)
        {
            switch (form)
            {
                case DRUID_BEAR_FORM:
                    me->SetBotClass(DRUID_BEAR_FORM);
                    if (me->getPowerType() != POWER_RAGE)
                    {
                        me->setPowerType(POWER_RAGE);
                        me->SetMaxPower(POWER_RAGE, 1000);
                    }
                    if (me->getLevel() >= 15)
                        me->SetPower(POWER_RAGE, 200);
                    else
                        me->SetPower(POWER_RAGE, 0);
                    if (me->getLevel() >= 40 && !me->HasAura(LEADER_OF_THE_PACK))
                        RefreshAura(LEADER_OF_THE_PACK);
                    break;
                case DRUID_CAT_FORM:
                    me->SetBotClass(DRUID_CAT_FORM);
                    if (me->getPowerType() != POWER_ENERGY)
                    {
                        me->setPowerType(POWER_ENERGY);
                        me->SetMaxPower(POWER_ENERGY, 100);
                        me->SetPower(POWER_ENERGY, 0);
                    }
                    if (me->getLevel() >= 15)
                        me->SetPower(POWER_ENERGY, 60);
                    else
                        me->SetPower(POWER_ENERGY, 0);
                    if (me->getLevel() >= 40 && !me->HasAura(LEADER_OF_THE_PACK))
                        RefreshAura(LEADER_OF_THE_PACK);
                    RefreshAura(ENERGIZE, me->getLevel()/40 + master->Has310Flyer(false));
                    break;
                case CLASS_DRUID:
                    me->SetBotClass(CLASS_DRUID);
                    if (me->getPowerType() != POWER_MANA)
                        me->setPowerType(POWER_MANA);
                    if (init)
                        me->SetPower(POWER_MANA, mana);
                    break;
            }

            SetStats(false);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            OnSpellHit(caster, spell);
        }

        void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
        {
            if (victim == me)
                return;

            if (damageType == DIRECT_DAMAGE || damageType == SPELL_DIRECT_DAMAGE)
            {
                for (uint8 i = 0; i != MAX_BOT_CTC_SPELLS; ++i)
                {
                    if (_ctc[i].first && !_ctc[i].second)
                    {
                        if (urand(1,100) <= CalcCTC(_ctc[i].first))
                            _ctc[i].second = 1000;

                        if (_ctc[i].second > 0)
                            me->CastSpell(victim, _ctc[i].first, true);
                    }
                }
            }
        }

        void DamageTaken(Unit* u, uint32& /*damage*/)
        {
            OnOwnerDamagedBy(u);
        }

        void OwnerAttackedBy(Unit* u)
        {
            OnOwnerDamagedBy(u);
        }

        void Reset()
        {
            Heal_Timer = 0;
            formtimer = 0;

            clearcast = false;
            swiftness = false;

            power = POWER_MANA;

            mana = 0;
            rage = 0;

            rageIncomeMult = sWorld->getRate(RATE_POWER_RAGE_INCOME);
            rageLossMult = sWorld->getRate(RATE_POWER_RAGE_LOSS);

            ragetimer = 0;
            ragetimer2 = 0;

            if (master)
            {
                SetStats(true);
                InitRoles();
                ApplyPassives(CLASS_DRUID);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            SpellTimers(diff);
            if (Heal_Timer > diff)                  Heal_Timer -= diff;
            if (formtimer > diff)                   formtimer -= diff;
            if (ragetimer > diff)                   ragetimer -= diff;
            if (ragetimer2 > diff)                  ragetimer2 -= diff;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();

            InitSpellMap(WARSTOMP_1, true);

            InitSpellMap(MARK_OF_THE_WILD_1);
            InitSpellMap(THORNS_1);
            InitSpellMap(HEALING_TOUCH_1);
            InitSpellMap(REGROWTH_1);
            InitSpellMap(REJUVENATION_1);
            InitSpellMap(LIFEBLOOM_1);
            InitSpellMap(NOURISH_1);
     /*tal*/lvl >= 60 ? InitSpellMap(WILD_GROWTH_1) : RemoveSpell(WILD_GROWTH_1);
     /*tal*/lvl >= 40 ? InitSpellMap(SWIFTMEND_1) : RemoveSpell(SWIFTMEND_1);
            InitSpellMap(TRANQUILITY_1);
            InitSpellMap(REVIVE_1);
            InitSpellMap(REBIRTH_1);
            InitSpellMap(BEAR_FORM_1);
            InitSpellMap(SWIPE_1);
     /*tal*/lvl >= 50 ? InitSpellMap(MANGLE_BEAR_1) : RemoveSpell(MANGLE_BEAR_1);
            InitSpellMap(BASH_1);
            InitSpellMap(CAT_FORM_1);
            InitSpellMap(CLAW_1);
            InitSpellMap(RAKE_1);
            InitSpellMap(SHRED_1);
            InitSpellMap(RIP_1);
     /*tal*/lvl >= 50 ? InitSpellMap(MANGLE_CAT_1) : RemoveSpell(MANGLE_CAT_1);
            InitSpellMap(MOONFIRE_1);
            InitSpellMap(STARFIRE_1);
            InitSpellMap(WRATH_1);
            InitSpellMap(HURRICANE_1);
            InitSpellMap(FAERIE_FIRE_1);
            InitSpellMap(CURE_POISON_1);
            InitSpellMap(INNERVATE_1);
            InitSpellMap(ENTANGLING_ROOTS_1);
     /*tal*/lvl >= 30 ? InitSpellMap(NATURES_SWIFTNESS_1) : RemoveSpell(NATURES_SWIFTNESS_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 78)
                RefreshAura(SPELLDMG2, 3); //+18%
            else if (level >= 65)
                RefreshAura(SPELLDMG2, 2); //+12%
            else if (level >= 50)
                RefreshAura(SPELLDMG2); //+6%
            if (level >= 45)
                RefreshAura(NATURAL_PERFECTION3); //4%
            else if (level >= 43)
                RefreshAura(NATURAL_PERFECTION2); //3%
            else if (level >= 41)
                RefreshAura(NATURAL_PERFECTION1); //2%
            if (level >= 50)
                RefreshAura(LIVING_SEED3); //100%
            else if (level >= 48)
                RefreshAura(LIVING_SEED2); //66%
            else if (level >= 46)
                RefreshAura(LIVING_SEED1); //33%
            if (level >= 55)
                RefreshAura(REVITALIZE3, 5); //75% (15%)x5
            else if (level >= 53)
                RefreshAura(REVITALIZE2, 3); //30% (10%)x3
            else if (level >= 51)
                RefreshAura(REVITALIZE1, 3); //15%  (5%)x3
            if (level >= 70)
                RefreshAura(OMEN_OF_CLARITY, 3); //x3
            else if (level >= 40)
                RefreshAura(OMEN_OF_CLARITY, 2); //x2
            else if (level >= 20)
                RefreshAura(OMEN_OF_CLARITY); //x1
            if (level >= 45)
                RefreshAura(GLYPH_SWIFTMEND); //no comsumption
            if (level >= 40)
                RefreshAura(GLYPH_INNERVATE); //no comsumption
            if (level >= 20)
                RefreshAura(NATURESGRACE);
            if (level >= 78)
            {
                RefreshAura(T9_RESTO_P4_BONUS);
                RefreshAura(T8_RESTO_P4_BONUS);
                RefreshAura(T9_BALANCE_P2_BONUS);
                RefreshAura(T10_BALANCE_P2_BONUS);
                RefreshAura(T10_BALANCE_P4_BONUS);
            }
        }

        bool CanUseManually(uint32 basespell) const
        {
            switch (basespell)
            {
                case MARK_OF_THE_WILD_1:
                case THORNS_1:
                case HEALING_TOUCH_1:
                case REJUVENATION_1:
                case LIFEBLOOM_1:
                case REGROWTH_1:
                case NOURISH_1:
                case WILD_GROWTH_1:
                case SWIFTMEND_1:
                case TRANQUILITY_1:
                case CURE_POISON_1:
                case INNERVATE_1:
                    return true;
                default:
                    return false;
            }
        }

    private:
        //Timers/other
/*Heal*/uint32 Heal_Timer;
/*Misc*/uint32 formtimer, ragetimer, ragetimer2;
/*Chck*/bool clearcast, swiftness;
/*Misc*/Powers power; uint32 mana, rage;
/*Misc*/float rageIncomeMult, rageLossMult;

        enum DruidBaseSpells
        {
            MARK_OF_THE_WILD_1                  = 1126,
            THORNS_1                            = 467,
            HEALING_TOUCH_1                     = 5185,
            REGROWTH_1                          = 8936,
            REJUVENATION_1                      = 774,
            LIFEBLOOM_1                         = 33763,
            NOURISH_1                           = 50464,
     /*tal*/WILD_GROWTH_1                       = 48438,
     /*tal*/SWIFTMEND_1                         = 18562,
            TRANQUILITY_1                       = 740,
            REVIVE_1                            = 50769,
            REBIRTH_1                           = 20484,
            BEAR_FORM_1                         = 5487,
            SWIPE_1                             = 779,
     /*tal*/MANGLE_BEAR_1                       = 33878,
            BASH_1                              = 5211,
            CAT_FORM_1                          = 768,
            CLAW_1                              = 1082,
            RAKE_1                              = 1822,
            SHRED_1                             = 5221,
            RIP_1                               = 1079,
     /*tal*/MANGLE_CAT_1                        = 33876,
            MOONFIRE_1                          = 8921,
            STARFIRE_1                          = 2912,
            WRATH_1                             = 5176,
            HURRICANE_1                         = 16914,
            FAERIE_FIRE_1                       = 770,
            CURE_POISON_1                       = 8946,
            INNERVATE_1                         = 29166,
            ENTANGLING_ROOTS_1                  = 339,
     /*tal*/NATURES_SWIFTNESS_1                 = 17116,
            WARSTOMP_1                          = 20549
        };
        enum DruidPassives
        {
        //Talents
            OMEN_OF_CLARITY                     = 16864,//clearcast
            NATURESGRACE                        = 61346,//haste 20% for 3 sec
            NATURAL_PERFECTION1                 = 33881,
            NATURAL_PERFECTION2                 = 33882,
            NATURAL_PERFECTION3                 = 33883,
            LIVING_SEED1                        = 48496,//rank 1
            LIVING_SEED2                        = 48499,//rank 2
            LIVING_SEED3                        = 48500,//rank 3
            REVITALIZE1                         = 48539,//rank 1
            REVITALIZE2                         = 48544,//rank 2
            REVITALIZE3                         = 48545,//rank 3
  /*Talent*/LEADER_OF_THE_PACK                  = 24932,
        //Glyphs
            GLYPH_SWIFTMEND                     = 54824,//no consumption
            GLYPH_INNERVATE                     = 54832,//self regen
        //other
            T9_RESTO_P4_BONUS                   = 67128,//rejuve crits
            T8_RESTO_P4_BONUS                   = 64760,//rejuve init heal
            T9_BALANCE_P2_BONUS                 = 67125,//moonfire crits
            T10_BALANCE_P2_BONUS                = 70718,//omen of doom (15%)
            T10_BALANCE_P4_BONUS                = 70723,//Languish(DOT)
            SPELLDMG/*Arcane Instability-mage*/ = 15060,//rank3 3% dam/crit
            SPELLDMG2/*Earth and Moon - druid*/ = 48511,//rank3 6% dam
            ENERGIZE                            = 27787,//Rogue Armor Energize (chance: +35 energy on hit)
            CRIT_50                             = 23434 //50% spell crit
        };
        enum DruidSpecial
        {
            HURRICANE_DAMAGE                    = 42231,
  /*Talent*/LEADER_OF_THE_PACK_BUFF             = 24932,
            //NATURESGRACEBUFF                    = 16886,
            OMEN_OF_CLARITY_BUFF                = 16870 //434 deprecated
        };
    };
};

void AddSC_druid_bot()
{
    new druid_bot();
}
