#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "WorldSession.h"
/*
Warrior NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - Around 40-45%
TODO: Thunder Clap, Piercing Howl, Challenging Shout, other tanking stuff
*/
class warrior_bot : public CreatureScript
{
public:
    warrior_bot() : CreatureScript("warrior_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new warrior_botAI(creature);
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

    struct warrior_botAI : public bot_minion_ai
    {
        warrior_botAI(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (CheckBotCast(victim, spellId, CLASS_WARRIOR) != SPELL_CAST_OK)
                return false;
            return bot_ai::doCast(victim, spellId, triggered);
        }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (IAmDead()) return;
            CheckAttackState();
            if (ragetimer2 <= diff)
            {
                if (me->IsInCombat() && me->getLevel() >= 20)
                {
                    if (getrage() < 990)
                        me->SetPower(POWER_RAGE, rage + uint32(10.f*rageIncomeMult));//1 rage per 2 sec
                    else
                        me->SetPower(POWER_RAGE, 1000);//max
                }
                ragetimer2 = 2000;
            }
            if (ragetimer <= diff)
            {
                if (!me->IsInCombat() && !HasAuraName(me, BLOODRAGE_1))
                {
                    if (getrage() > uint32(10.f*rageLossMult))
                        me->SetPower(POWER_RAGE, rage - uint32(10.f*rageLossMult));//-1 rage per 1.5 sec
                    else
                        me->SetPower(POWER_RAGE, 0);//min
                }
                ragetimer = 1500;
            }
            CheckAuras();
            if (wait == 0)
                wait = GetWait();
            else
                return;
            BreakCC(diff);
            if (CCed(me)) return;

            if (GetHealthPCT(me) < 67 && Potion_cd <= diff)
            {
                temptimer = GC_Timer;
                if (doCast(me, HEALINGPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }
            CheckIntervene(diff);
            if (!me->IsInCombat())
                DoNonCombatActions(diff);

            if (!CheckAttackTarget(CLASS_WARRIOR))
            {
                if (!IsTank() && !me->IsInCombat() && battleStance != true && master->getAttackers().empty() &&
                    stancetimer <= diff && Rand() < 25)
                    stanceChange(diff, 1);
                return;
            }

            if (IsSpellReady(BATTLESHOUT_1, diff) && getrage() > 100 && Rand() < 30 &&
                !HasAuraName(master, BATTLESHOUT_1) && !HasAuraName(master, BLESSING_OF_MIGHT_1) &&
                !HasAuraName(master, GREATER_BLESSING_OF_MIGHT_1) && master->IsWithinLOSInMap(me))
            {
                if (doCast(me, GetSpell(BATTLESHOUT_1)))
                {
                    SetSpellCooldown(BATTLESHOUT_1, 25000);
                    return;
                }
            }

            if (IsSpellReady(BLOODRAGE_1, diff, false) && me->IsInCombat() && getrage() < 600 &&
                Rand() < 20 && !me->HasAura(ENRAGED_REGENERATION_1))
            {
                temptimer = GC_Timer;
                if (doCast(me, GetSpell(BLOODRAGE_1)))
                {
                    SetSpellCooldown(BLOODRAGE_1, 40000);
                    GC_Timer = temptimer;
                }
            }

            Attack(diff);
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            SetBotCommandState(COMMAND_ATTACK);
            GetInPosition(force);
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit* u)
        {
            //victorious state emulation
            if (me->getLevel() >= 5 && u->getLevel() + 9 >= me->getLevel())
            {
                temptimer = GC_Timer;
                if (doCast(me, VICTORIOUS_SPELL, true))
                {
                    GC_Timer = temptimer;
                    return;
                }
            }
        }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit* u) { bot_ai::JustDied(u); }
        void DoNonCombatActions(uint32 /*diff*/) { }

        void modrage(int32 mod, bool set = false)
        {
            if (set && mod < 0)
                return;
            if (mod < 0 && rage < uint32(abs(mod)))
            {
                //debug set rage to 0
                mod = 0;
                set = true;
                return;
            }

            if (set)
                rage = mod ? mod*10 : 0;
            else
                rage += mod*10;

            me->SetPower(POWER_RAGE, rage);
        }

        uint32 getrage()
        {
            rage = me->GetPower(POWER_RAGE);
            return rage;
        }

        void BreakCC(uint32 diff)
        {
            if (me->HasAuraWithMechanic((1<<MECHANIC_FEAR)|(1<<MECHANIC_SAPPED)|(1<<MECHANIC_DISORIENTED)))
            {
                if (IsSpellReady(BERSERKERRAGE_1, diff) && Rand() < 35 && !me->HasAura(ENRAGED_REGENERATION_1) &&
                    doCast(me, GetSpell(BERSERKERRAGE_1)))
                {
                    SetSpellCooldown(BERSERKERRAGE_1, 25000);
                    if (me->getLevel() >= 40)
                        doCast(me, 58096, true); //Berserker Rage Effect (434 unused)
                    return;
                }
            }
            bot_minion_ai::BreakCC(diff);
        }

        void Attack(uint32 diff)
        {
            opponent = me->GetVictim();
            if (opponent)
            {
                if (!IsCasting())
                    StartAttack(opponent, true);
            }
            else
                return;
            //Keep defensive stance if tank
            if (IsTank() && defensiveStance != true && stancetimer <= diff)
                stanceChange(diff, 2);
            //SelfHeal
            if (IsSpellReady(ENRAGED_REGENERATION_1, diff) && getrage() > 150 && GetHealthPCT(me) < 40 &&
                Rand() < 40 && me->HasAuraWithMechanic(uint32(1<<MECHANIC_ENRAGED)))
            {
                if (doCast(me, GetSpell(ENRAGED_REGENERATION_1)))
                {
                    SetSpellCooldown(ENRAGED_REGENERATION_1, 90000);
                    GC_Timer = 500;
                    return;
                }
            }

            AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();
            float dist = me->GetExactDist(opponent);
            float meleedist = me->GetDistance(opponent);
            //charge + warbringer
            if (IsSpellReady(CHARGE_1, diff, false) && dist > 11 && dist < 25 && me->HasInArc(M_PI, opponent) &&
                (me->getLevel() >= 50 ||
                (!me->IsInCombat() && (battleStance || stanceChange(diff, 1)))))
            {
                temptimer = GC_Timer;
                if (me->getLevel() >= 29)
                    me->RemoveMovementImpairingAuras();
                if (doCast(opponent, GetSpell(CHARGE_1), me->IsInCombat()))
                {
                    SetSpellCooldown(CHARGE_1, 12000);
                    GC_Timer = temptimer;
                    return;
                }
            }
            //intercept
            if (IsSpellReady(INTERCEPT_1, diff, false) && !IsTank() &&
                getrage() > 100 && dist > 11 && dist < 25 && me->HasInArc(M_PI, opponent) &&
                !CCed(opponent) && (berserkerStance || stanceChange(diff, 3)))
            {
                if (doCast(opponent, GetSpell(INTERCEPT_1)))
                {
                    SetSpellCooldown(INTERCEPT_1, 20000);
                    return;
                }
            }
            //SelfHeal 2
            if (IsSpellReady(VICTORY_RUSH_1, diff) && VICTORIOUS && HasRole(BOT_ROLE_DPS) && meleedist <= 5 &&
                (b_attackers.size() <= 1 || (GetHealthPCT(me) < std::max<int32>(100 - b_attackers.size() * 10, 75))))
            {
                if (doCast(opponent, GetSpell(VICTORY_RUSH_1)))
                    return;
            }
            //FEAR
            if (IsSpellReady(INTIMIDATING_SHOUT_1, diff) && Rand() < 70 && getrage() > 250)
            {
                if (opponent->IsNonMeleeSpellCast(false, false, true) && dist <= 8 &&
                    !(opponent->ToCreature() && opponent->ToCreature()->GetCreatureType() == CREATURE_TYPE_UNDEAD))
                {
                    if (doCast(opponent, GetSpell(INTIMIDATING_SHOUT_1)))
                    {
                        SetSpellCooldown(INTIMIDATING_SHOUT_1, 45000);
                        return;
                    }
                }
                Unit* fearTarget = NULL;
                bool triggered = false;
                uint8 tCount = 0;
                //fear master's attackers
                if (!m_attackers.empty() &&
                    ((master->getClass() != CLASS_DEATH_KNIGHT &&
                    master->getClass() != CLASS_WARRIOR &&
                    master->getClass() != CLASS_PALADIN) ||
                    GetHealthPCT(master) < 70))
                {
                    for(AttackerSet::iterator iter = m_attackers.begin(); iter != m_attackers.end(); ++iter)
                    {
                        if (!(*iter)) continue;
                        if ((*iter)->GetCreatureType() == CREATURE_TYPE_UNDEAD) continue;
                        if (me->GetExactDist((*iter)) <= 8 && (*iter)->isTargetableForAttack())
                        {
                            ++tCount;
                            fearTarget = (*iter);
                            if (tCount > 1) break;
                        }
                    }
                    if (tCount > 0 && !fearTarget)
                    {
                        fearTarget = opponent;
                        triggered = true;
                    }
                    if (tCount > 1 && doCast(fearTarget, GetSpell(INTIMIDATING_SHOUT_1), triggered))
                    {
                        SetSpellCooldown(INTIMIDATING_SHOUT_1, 45000);
                        return;
                    }
                }
                //Defend myself
                if (b_attackers.size() > 1)
                {
                    tCount = 0;
                    fearTarget = NULL;
                    triggered = false;
                    for(AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                    {
                        if (!(*iter)) continue;
                        if ((*iter)->GetCreatureType() == CREATURE_TYPE_UNDEAD) continue;
                        if (me->GetExactDist((*iter)) <= 8 && (*iter)->isTargetableForAttack())
                        {
                            ++tCount;
                            fearTarget = (*iter);
                            if (tCount > 0) break;
                        }
                    }
                    if (tCount > 0 && !fearTarget)
                    {
                        fearTarget = opponent;
                        triggered = true;
                    }
                    if (tCount > 0 && doCast(fearTarget, GetSpell(INTIMIDATING_SHOUT_1), triggered))
                    {
                        SetSpellCooldown(INTIMIDATING_SHOUT_1, 45000);
                        return;
                    }
                }
            }//end FEAR
            //OVERPOWER
            if (IsSpellReady(OVERPOWER_1, diff) && HasRole(BOT_ROLE_DPS) && Rand() < 50 && getrage() > 50 && meleedist <= 5 &&
                (battleStance || stancetimer <= diff))
            {
                if (me->HasAura(TASTE_FOR_BLOOD_BUFF))
                {
                    if (battleStance || stanceChange(diff, 1))
                    {
                        if (doCast(opponent, GetSpell(OVERPOWER_1)))
                        {
                            me->RemoveAura(TASTE_FOR_BLOOD_BUFF);
                            return;
                        }
                    }
                }
            }

            if (MoveBehind(*opponent))
                wait = 5;

            //HAMSTRING
            if (IsSpellReady(HAMSTRING_1, diff) && Rand() < 50 && getrage() > 100 && meleedist <= 5 && opponent->isMoving() &&
                (battleStance || berserkerStance || stancetimer <= diff) &&
                !opponent->HasAuraWithMechanic((1<<MECHANIC_SNARE)|(1<<MECHANIC_ROOT)))
            {
                if (battleStance || berserkerStance || stanceChange(diff, 5))
                    if (doCast(opponent, GetSpell(HAMSTRING_1)))
                        return;
            }
            //UBERS
            //Dont use RETA unless capable circumstances
            if (HasRole(BOT_ROLE_DPS) && Rand() < 20)
            {
                if (IsSpellReady(RETALIATION_1, diff) && b_attackers.size() > 4 &&
                    (battleStance || stanceChange(diff, 1)))
                {
                    if (doCast(me, GetSpell(RETALIATION_1)))
                    {
                        SetSpellCooldown(RETALIATION_1, 150000);
                        SetSpellCooldown(RECKLESSNESS_1, 150000);
                        return;
                    }
                }
                //Dont use RECKL unless capable circumstances
                if (IsSpellReady(RECKLESSNESS_1, diff) && !IsTank() &&
                    (m_attackers.size() > 3 || opponent->GetHealth() > me->GetHealth() * 10) &&
                    (berserkerStance || stanceChange(diff, 3)))
                {
                    if (doCast(me, GetSpell(RECKLESSNESS_1)))
                    {
                        SetSpellCooldown(RETALIATION_1, 150000);
                        SetSpellCooldown(RECKLESSNESS_1, 150000);
                        return;
                    }
                }
            }
            //DEATHWISH
            if (IsSpellReady(DEATHWISH_1, diff) && getrage() > 100 && HasRole(BOT_ROLE_DPS) &&
                opponent->GetHealth() > me->GetHealth()/2 && Rand() < 20 &&
                !me->HasAura(ENRAGED_REGENERATION_1))
            {
                if (doCast(me, GetSpell(DEATHWISH_1)))
                {
                    SetSpellCooldown(DEATHWISH_1, 144000);
                    return;
                }
            }
            //TAUNT //No GCD
            Unit* u = opponent->GetVictim();
            if (IsSpellReady(TAUNT_1, diff, false) && u && u != me && !IsTank(u) && dist <= 30 &&
                !CCed(opponent) && !IsTankingClass(u->getClass()) && (IsInBotParty(u) || IsTank()) &&
                (defensiveStance || (stancetimer <= diff && stanceChange(diff, 2))))
            {
                temptimer = GC_Timer;
                if (doCast(opponent, GetSpell(TAUNT_1), true))
                {
                    SetSpellCooldown(TAUNT_1, 8000);
                    GC_Timer = temptimer;
                    return;
                }
            }
            //EXECUTE
            if (IsSpellReady(EXECUTE_1, diff) && HasRole(BOT_ROLE_DPS) && !IsTank() && getrage() > 150 && meleedist <= 5 &&
                Rand() < 70 &&GetHealthPCT(opponent) < 20 &&
                (battleStance || berserkerStance || (stancetimer <= diff && stanceChange(diff, 5))))
            {
                if (doCast(opponent, GetSpell(EXECUTE_1)))
                {
                    //sudden death
                    if (me->getLevel() >= 50 && getrage() <= 400)
                        modrage(10, true);
                    else if (getrage() > 300)
                        modrage(-30);
                    else
                        modrage(0, true);
                    return;
                }
            }
            //SUNDER //custom cd condition
            if (GetSpell(SUNDER_1) && GC_Timer <= diff && getrage() > 150 &&
                (getrage() > 500 || IsSpellReady(SUNDER_1,diff, false)) &&
                meleedist <= 5 && IsTank() && opponent->GetHealth() > me->GetMaxHealth() && Rand() < 35)
            {
                Aura* sunder = opponent->GetAura(GetSpell(SUNDER_1), me->GetGUID());
                if ((!sunder || sunder->GetStackAmount() < 5 || sunder->GetDuration() < 15000) &&
                    doCast(opponent, GetSpell(SUNDER_1)))
                {
                    SetSpellCooldown(SUNDER_1, 7000);
                    GC_Timer = 800;
                    return;
                }
            }
            //SS //no GCD //no rage (glyph)
            if (IsSpellReady(SWEEPING_STRIKES_1, diff, false) && HasRole(BOT_ROLE_DPS) && !IsTank() && Rand() < 25 &&
                (battleStance || berserkerStance || stancetimer <= diff) &&
                (b_attackers.size() > 1 || FindSplashTarget(7, opponent)))
            {
                temptimer = GC_Timer;
                if ((battleStance || berserkerStance || stanceChange(diff, 5)) &&
                    doCast(me, GetSpell(SWEEPING_STRIKES_1), true))
                {
                    SetSpellCooldown(SWEEPING_STRIKES_1, 30000);
                    GC_Timer = temptimer;
                    return;
                }
            }
            //WHIRLWIND
            if (IsSpellReady(WHIRLWIND_1, diff) && getrage() >= 250 && HasRole(BOT_ROLE_DPS) && !IsTank() && Rand() < 50 &&
               (FindSplashTarget(7, opponent) || (getrage() > 800 && dist <= 7)) &&
               (berserkerStance || stancetimer <= diff))
            {
                if ((berserkerStance || stanceChange(diff, 3)) &&
                    doCast(me, GetSpell(WHIRLWIND_1)))
                {
                    SetSpellCooldown(WHIRLWIND_1, 6500);
                    return;
                }
            }
            //BLADESTORM
            if (IsSpellReady(BLADESTORM_1, diff) && HasRole(BOT_ROLE_DPS) &&
               getrage() >= 250 && (Rand() < 20 || me->HasAura(RECKLESSNESS_1)) &&
               (b_attackers.size() > 1 || opponent->GetHealth() > me->GetMaxHealth()))
            {
                if (doCast(me, GetSpell(BLADESTORM_1)))
                {
                    SetSpellCooldown(BLADESTORM_1, 60000);
                    return;
                }
            }
            //Mortal Strike
            if (IsSpellReady(MORTALSTRIKE_1, diff) && getrage() > 300 && HasRole(BOT_ROLE_DPS) && meleedist <= 5)
            {
                if (doCast(opponent, GetSpell(MORTALSTRIKE_1)))
                {
                    SetSpellCooldown(MORTALSTRIKE_1, 7000);
                    ResetSpellCooldown(SLAM_1); //reset here
                }
            }
            //Slam
            if (IsSpellReady(SLAM_1, diff))
            {
                bool triggered = (GetSpellCooldown(MORTALSTRIKE_1) == 7000);
                if (getrage() > 150 && HasRole(BOT_ROLE_DPS) && meleedist <= 5 && Rand() < (30 + triggered * 30))
                {
                    if (doCast(opponent, GetSpell(SLAM_1), true))
                    {
                        SetSpellCooldown(SLAM_1, 3000); //must be > 7000/2
                        modrage(-15);
                        return;
                    }
                }
            }
            //PUMMEL
            if (IsSpellReady(PUMMEL_1, diff, false) && Rand() < 80 && getrage() > 100 && meleedist <= 5 &&
                opponent->IsNonMeleeSpellCast(false) &&
                (berserkerStance || stancetimer <= diff))
            {
                temptimer = GC_Timer;
                if ((berserkerStance || stanceChange(diff, 3)) &&
                    doCast(opponent, GetSpell(PUMMEL_1)))
                {
                    SetSpellCooldown(PUMMEL_1, 10000);
                    GC_Timer = temptimer;
                    return;
                }
            }
            //REND
            if (IsSpellReady(REND_1, diff) && Rand() < 50 && getrage() > 100 && HasRole(BOT_ROLE_DPS) && meleedist <= 5 &&
                opponent->GetHealth() > me->GetHealth()/2 &&
                !opponent->HasAura(GetSpell(REND_1), me->GetGUID()) &&
                (battleStance || defensiveStance || (stancetimer <= diff && stanceChange(diff, 4))))
            {
                if (doCast(opponent, GetSpell(REND_1)))
                    return;
            }
            //CLEAVE //no GCD
            if (IsSpellReady(CLEAVE_1, diff, false) && getrage() > 200 && HasRole(BOT_ROLE_DPS) && meleedist <= 5 && Rand() < 30)
            {
                temptimer = GC_Timer;
                u = FindSplashTarget(5);
                if (u && doCast(opponent, GetSpell(CLEAVE_1)))
                {
                    SetSpellCooldown(CLEAVE_1, me->getAttackTimer(BASE_ATTACK)); //once per swing, prevents rage loss
                    GC_Timer = temptimer;
                    return;
                }
            }
            else {}//HEROIC STRIKE placeholder
            //DISARM DEPRECATED
            /*if (disarm_cd <= diff && meleedist < 5 &&
                (opponent->GetVictim()->GetGUID() == master->GetGUID() ||
                opponent->GetVictim()->GetGUID() == m_creature->GetGUID()) &&
                getrage() > 15 &&
                !HasAuraName(opponent, GetSpellName(DISARM)) &&
                GC_Timer <= diff)
            {
                if (opponent->getClass() == CLASS_ROGUE  ||
                    opponent->getClass() == CLASS_WARRIOR   ||
                    opponent->getClass() == CLASS_SHAMAN    ||
                    opponent->getClass() == CLASS_PALADIN)
                {
                    if (defensiveStance == true)
                    {
                        doCast(opponent, DISARM, true);
                        //rage -= 100;
                        disarm_cd = DISARM_CD;
                    }
                    else stanceChange(diff, 2);
                }
            }*/
        }//end Attack

        void CheckIntervene(uint32 diff)
        {
            if (IsSpellReady(INTERVENE_1, diff, false) && getrage() > 100 &&
                Rand() < (IsTank() ? 80 : 30) &&
                (defensiveStance || stancetimer <= diff))
            {
                if (!master->IsInCombat() && master->getAttackers().empty() && master->isMoving())
                {
                    float mydist = me->GetExactDist(master);
                    if (mydist < 24 && mydist > 19 && (defensiveStance || stanceChange(diff, 2)))
                    {
                        temptimer = GC_Timer;
                        if (doCast(master, GetSpell(INTERVENE_1)))
                        {
                            SetSpellCooldown(INTERVENE_1, 20000);
                            GC_Timer = temptimer;
                            Follow(true);
                            return;
                        }
                    }
                }
                Group* gr = master->GetGroup();
                if (!gr)
                {
                    if (GetHealthPCT(master) < 95 && !master->getAttackers().empty() &&
                        me->getAttackers().size() <= master->getAttackers().size())
                    {
                        float dist = me->GetExactDist(master);
                        if (dist > 25 || dist < 10) return;
                        if (!(defensiveStance || stanceChange(diff, 2))) return;
                        temptimer = GC_Timer;
                        if (doCast(master, GetSpell(INTERVENE_1)))
                        {
                            SetSpellCooldown(INTERVENE_1, 20000);
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                }
                else
                {
                    bool Bots = false;
                    float dist;
                    for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        Player* tPlayer = itr->GetSource();
                        if (!tPlayer) continue;
                        if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
                        if (tPlayer->FindMap() != me->GetMap()) continue;
                        if (tPlayer->HaveBot())
                            Bots = true;
                        if (tPlayer->isDead() || GetHealthPCT(tPlayer) > 90 || IsTank(tPlayer)) continue;
                        if (tPlayer->getAttackers().size() < me->getAttackers().size()) continue;
                        dist = me->GetExactDist(tPlayer);
                        if (dist > 24 || dist < 10) continue;
                        if (defensiveStance || stanceChange(diff, 2))
                        {
                            temptimer = GC_Timer;
                            if (doCast(tPlayer, GetSpell(INTERVENE_1)))
                            {
                                SetSpellCooldown(INTERVENE_1, 20000);
                                GC_Timer = temptimer;
                                return;
                            }
                        }
                    }
                    if (!Bots) return;
                    for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        Player* tPlayer = itr->GetSource();
                        if (!tPlayer || !tPlayer->HaveBot()) continue;
                        if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
                        if (tPlayer->FindMap() != me->GetMap()) continue;
                        for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                        {
                            Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                            if (!bot || !bot->IsInWorld() || bot == me || bot->isDead()) continue;
                            if (GetHealthPCT(bot) > 90 || IsTank(bot)) continue;
                            dist = me->GetExactDist(bot);
                            if (dist > 25 || dist < 10) continue;
                            if (bot->getAttackers().size() <= me->getAttackers().size()) continue;
                            if (defensiveStance || stanceChange(diff, 2))
                            {
                                temptimer = GC_Timer;
                                if (doCast(bot, GetSpell(INTERVENE_1)))
                                {
                                    SetSpellCooldown(INTERVENE_1, 20000 / 2);
                                    GC_Timer = temptimer;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        bool stanceChange(uint32 diff, uint8 stance)
        {
            if (!(stancetimer <= diff) || !stance)
                return false;

            if (stance == 5)
            {
                if (urand(1,100) > 50)
                    stance = 1;
                else
                    stance = me->getLevel() < 30 ? 1 : (urand(1,100) > 75 ? 3 : 1);
            }
            else if (stance == 4)
            {
                if (urand(1,100) > 50)
                    stance = 1;
                else
                    stance = IsTank() ? 2 : 1;
            }

            if (stance == 2 && me->getLevel() < 10)
                return false;
            if (stance == 3 && me->getLevel() < 30)
                return false;

            temptimer = GC_Timer;
            //stance mastery impl
            uint32 temprage = 0;
            uint32 myrage = me->GetPower(POWER_RAGE);
            if (me->getLevel() >= 20)
                temprage = myrage > 250 ? 250 : myrage;
            else if (me->getLevel() >= 15)
                temprage = myrage > 100 ? 100 : myrage;
            switch (stance)
            {
                case 1:
                    if (doCast(me, GetSpell(BATTLESTANCE_1)))
                    {
                        if (me->HasAura(BATTLESTANCE_1))
                        {
                            battleStance = true;
                            defensiveStance = false;
                            berserkerStance = false;
                            me->SetPower(POWER_RAGE, temprage);
                            stancetimer = 2100 - me->getLevel()*20;//500 on 80
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                    break;
                case 2:
                    if (doCast(me, GetSpell(DEFENSIVESTANCE_1)))
                    {
                        if (me->HasAura(DEFENSIVESTANCE_1))
                        {
                            defensiveStance = true;
                            battleStance = false;
                            berserkerStance = false;
                            me->SetPower(POWER_RAGE, temprage);
                            stancetimer = 2100 - me->getLevel()*20;//500 on 80
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                    break;
                case 3:
                    if (doCast(me, GetSpell(BERSERKERSTANCE_1)))
                    {
                        if (me->HasAura(BERSERKERSTANCE_1))
                        {
                            berserkerStance = true;
                            battleStance = false;
                            defensiveStance = false;
                            me->SetPower(POWER_RAGE, temprage);
                            stancetimer = 2100 - me->getLevel()*20;//500 on 80
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                    break;
                default:
                    break;
            }
            GC_Timer = temptimer;
            return false;
        }

        void ApplyClassDamageMultiplierMelee(int32& damage, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float fdamage = float(damage);
            //1) apply additional crit chance. This additional chance roll will replace original (balance safe)
            if (!crit)
            {
                float aftercrit = 0.f;
                //Incite: 15% additional critical chance for Cleave, Heroic Strike and Thunder Clap
                if (lvl >= 15 && spellId == GetSpell(CLEAVE_1) /*|| spellId == HEROICSTRIKE || spellId == THUNDERCLAP*/)
                    aftercrit += 15.f;
                //Improved Overpower: 50% additional critical chance for Overpower
                if (lvl >= 20 && spellId == GetSpell(OVERPOWER_1))
                    aftercrit += 50.f;

                //second roll (may be illogical)
                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!Melee spell damage is not yet critical, all reduced by half
                //Impale: 20% crit damage bonus for all abilities
                if (lvl >= 20)
                    pctbonus += 0.10f;
            }

            //Improved Rend: 20% bonus damage for Rend
            if (spellId == GetSpell(REND_1))
                pctbonus += 0.2f;
            //Improved Whirlwind: 20% bonus damage for Whirlwind
            if (lvl >= 40 && spellId == GetSpell(WHIRLWIND_1))
                pctbonus += 0.2f;
            //Glyph of Mortal Strike: 10% bonus damage for Mortal Strike
            if (lvl >= 40 && spellId == GetSpell(MORTALSTRIKE_1))
                pctbonus += 0.1f;
            //Unrelenting Assault (part 2): 20% bonus damage for Overpower and Revenge
            if (lvl >= 45 && (spellId == GetSpell(OVERPOWER_1)/* || spellId == REVENGE*/))
                pctbonus += 0.2f;
            //Improved Mortal Strike: 10% bonus damage for Mortal Strike
            if (lvl >= 45 && spellId == GetSpell(MORTALSTRIKE_1))
                pctbonus += 0.1f;
            //Undending Fury: 10% bonus damage for Whirlwind, Slam and Bloodthirst
            if (lvl >= 55 && (spellId == GetSpell(WHIRLWIND_1) || spellId == GetSpell(SLAM_1) /*|| spellId == BLOODTHIRST*/))
                pctbonus += 0.1f;

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case VICTORIOUS_SPELL:
                    VICTORIOUS = true;
                    break;
                default:
                    break;
            }
            OnSpellHit(caster, spell);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            if (spellId == GetSpell(OVERPOWER_1))
            {
                //Unrelenting Assault
                if (UNRELENTING_ASSAULT && target->HasUnitState(UNIT_STATE_CASTING))
                    target->CastSpell(target, UNRELENTING_ASSAULT_SPELL, true);
            }
            if (spellId == GetSpell(BATTLESHOUT_1)/* || spellId == COMMANDINGSHOUT*/)
            {
                //Glyph of Battle/Command + 2 min duration (8 for bots)
                if (Aura* shout = target->GetAura(spellId, me->GetGUID()))
                {
                    uint32 dur = shout->GetDuration() + 480000;
                    shout->SetDuration(dur);
                    shout->SetMaxDuration(dur);
                }
            }
            if (spellId == GetSpell(REND_1))
            {
                //Glyph of Rending + 6 sec duration
                if (Aura* rend = target->GetAura(spellId, me->GetGUID()))
                {
                    uint32 dur = rend->GetDuration() + 6000;
                    rend->SetDuration(dur);
                    rend->SetMaxDuration(dur);
                }
            }
            if (spellId == GetSpell(INTERVENE_1))
            {
                //Glyph of Intervene + 1 bonus charge (2 for bots)
                if (Aura* vene = target->GetAura(spellId, me->GetGUID()))
                {
                    vene->SetCharges(vene->GetCharges() + 2);
                }
            }
            if (spellId == GetSpell(VICTORY_RUSH_1))
            {
                me->RemoveAura(VICTORIOUS_SPELL);
                VICTORIOUS = false;
            }
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
            stancetimer = 0;
            ragetimer = 1500;
            ragetimer2 = 3000;

            battleStance = true;
            defensiveStance = false;
            berserkerStance = false;

            rageIncomeMult = sWorld->getRate(RATE_POWER_RAGE_INCOME);
            rageLossMult = sWorld->getRate(RATE_POWER_RAGE_LOSS);
            me->setPowerType(POWER_RAGE);
            rage = 0;

            if (master)
            {
                SetStats(true);
                InitRoles();
                ApplyPassives(CLASS_WARRIOR);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            SpellTimers(diff);

            if (stancetimer > diff)                 stancetimer -= diff;
            if (ragetimer > diff)                   ragetimer -= diff;
            if (ragetimer2 > diff)                  ragetimer2 -= diff;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            //InitSpellMap(CHALLENGING_SHOUT_1);
            InitSpellMap(INTIMIDATING_SHOUT_1);
            InitSpellMap(ENRAGED_REGENERATION_1);
            InitSpellMap(CHARGE_1);
            InitSpellMap(OVERPOWER_1);
   /*Quest*/lvl >= 10 ? InitSpellMap(TAUNT_1) : RemoveSpell(TAUNT_1);
            //InitSpellMap(DISARM_1);
            InitSpellMap(BLOODRAGE_1);
            InitSpellMap(BERSERKERRAGE_1);
            InitSpellMap(INTERCEPT_1);
            InitSpellMap(CLEAVE_1);
            InitSpellMap(HAMSTRING_1);
            InitSpellMap(INTERVENE_1);
            InitSpellMap(WHIRLWIND_1);
  /*Talent*/lvl >= 60 ? InitSpellMap(BLADESTORM_1) : RemoveSpell(BLADESTORM_1);
            InitSpellMap(BATTLESHOUT_1);
            InitSpellMap(REND_1);
            InitSpellMap(EXECUTE_1);
            InitSpellMap(PUMMEL_1);
  /*Talent*/lvl >= 40 ? InitSpellMap(MORTALSTRIKE_1) : RemoveSpell(MORTALSTRIKE_1);
            InitSpellMap(SLAM_1);
   /*Quest*/lvl >= 10 ? InitSpellMap(SUNDER_1) : RemoveSpell(SUNDER_1);
  /*Talent*/lvl >= 30 ? InitSpellMap(SWEEPING_STRIKES_1) : RemoveSpell(SWEEPING_STRIKES_1);
            InitSpellMap(BATTLESTANCE_1);
   /*Quest*/lvl >= 10 ? InitSpellMap(DEFENSIVESTANCE_1) : RemoveSpell(DEFENSIVESTANCE_1);
   /*Quest*/lvl >= 30 ? InitSpellMap(BERSERKERSTANCE_1) : RemoveSpell(BERSERKERSTANCE_1);
            InitSpellMap(RECKLESSNESS_1);
            InitSpellMap(RETALIATION_1);
  /*Talent*/lvl >= 30 ? InitSpellMap(DEATHWISH_1) : RemoveSpell(DEATHWISH_1);
            InitSpellMap(VICTORY_RUSH_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 70)
                RefreshAura(WC5); //10%
            else if (level >= 68)
                RefreshAura(WC4); //8%
            else if (level >= 66)
                RefreshAura(WC3); //6%
            else if (level >= 64)
                RefreshAura(WC2); //4%
            else if (level >= 62)
                RefreshAura(WC1); //2%
            if (level >= 39)
                RefreshAura(FLURRY5); //30%
            else if (level >= 38)
                RefreshAura(FLURRY4); //24%
            else if (level >= 37)
                RefreshAura(FLURRY3); //18%
            else if (level >= 36)
                RefreshAura(FLURRY2); //12%
            else if (level >= 35)
                RefreshAura(FLURRY1); //6%
            if (level >= 60)
                RefreshAura(SWORD_SPEC5,2);//twice
            else if (level >= 50)
                RefreshAura(SWORD_SPEC5);//once
            else if (level >= 45)
                RefreshAura(SWORD_SPEC4);//once
            else if (level >= 40)
                RefreshAura(SWORD_SPEC3);//once
            else if (level >= 35)
                RefreshAura(SWORD_SPEC2);//once
            else if (level >= 30)
                RefreshAura(SWORD_SPEC1);//once
            if (level >= 60)
                RefreshAura(RAMPAGE);
            if (level >= 55)
                RefreshAura(TRAUMA2); //30%
            else if (level >= 35)
                RefreshAura(TRAUMA1); //15%
            if (level >= 35)
                UNRELENTING_ASSAULT = true;
            if (level >= 45)
                RefreshAura(BLOOD_FRENZY);
            if (level >= 40)
                RefreshAura(SECOND_WIND);
            if (level >= 40)
                RefreshAura(TOUGHNESS,2); //-60%
            else if (level >= 15)
                RefreshAura(TOUGHNESS); //-30%
            if (level >= 40)
                RefreshAura(IMP_HAMSTRING,2); //30%
            else if (level >= 35)
                RefreshAura(IMP_HAMSTRING); //15%
            if (level >= 30)
                RefreshAura(TASTE_FOR_BLOOD3); //100%
            else if (level >= 28)
                RefreshAura(TASTE_FOR_BLOOD2); //66%
            else if (level >= 25)
                RefreshAura(TASTE_FOR_BLOOD1); //33%
            if (level >= 30)
                RefreshAura(BLOOD_CRAZE3);
            else if (level >= 25)
                RefreshAura(BLOOD_CRAZE2);
            else if (level >= 20)
                RefreshAura(BLOOD_CRAZE1);
            //BloodRage Absorb
            if (level >= 60)
                RefreshAura(WARRIOR_T10_4P);
        }

        bool CanUseManually(uint32 basespell) const
        {
            switch (basespell)
            {
                case ENRAGED_REGENERATION_1:
                case BLOODRAGE_1:
                case BERSERKERRAGE_1:
                case BATTLESHOUT_1:
                //case SWEEPING_STRIKES_1: //unable - need stance
                case RETALIATION_1:
                case RECKLESSNESS_1:
                case DEATHWISH_1:
                    return true;
                default:
                    return false;
            }
        }

    private:
/*tmrs*/uint32 stancetimer, ragetimer, ragetimer2;
/*misc*/uint32 rage;
/*misc*/float rageIncomeMult, rageLossMult;
/*Chck*/bool battleStance, defensiveStance, berserkerStance, UNRELENTING_ASSAULT, VICTORIOUS;

        enum WarriorBaseSpells
        {
            //CHALLENGING_SHOUT_1                     = 1161,
            INTIMIDATING_SHOUT_1                    = 5246,
            ENRAGED_REGENERATION_1                  = 55694,
            CHARGE_1                                = 11578,
            OVERPOWER_1                             = 7384,
            TAUNT_1                                 = 355,
            //DISARM_1                                = 676,
            BLOODRAGE_1                             = 2687,
            BERSERKERRAGE_1                         = 18499,
            INTERCEPT_1                             = 20252,
            CLEAVE_1                                = 845,
            HAMSTRING_1                             = 1715,
            INTERVENE_1                             = 3411,
            WHIRLWIND_1                             = 1680,
            BLADESTORM_1                            = 46924,
            BATTLESHOUT_1                           = 6673,
            REND_1                                  = 772,
            EXECUTE_1                               = 5308,
            PUMMEL_1                                = 6552,
            MORTALSTRIKE_1                          = 12294,
            SLAM_1                                  = 1464,
            SUNDER_1                                = 7386,
            SWEEPING_STRIKES_1                      = 12328,
            BATTLESTANCE_1                          = 2457,
            DEFENSIVESTANCE_1                       = 71,
            BERSERKERSTANCE_1                       = 2458,
            RECKLESSNESS_1                          = 13847,//1719, original warrior spell
            RETALIATION_1                           = 22857,//20230, original warrior spell
            DEATHWISH_1                             = 12292,
            VICTORY_RUSH_1                          = 34428
        };
        enum WarriorPassives
        {
        //Talents
            WC1  /*WRECKING CREW1*/                 = 46867,
            WC2  /*WRECKING CREW2*/                 = 56611,
            WC3  /*WRECKING CREW3*/                 = 56612,
            WC4  /*WRECKING CREW4*/                 = 56613,
            WC5  /*WRECKING CREW5*/                 = 56614,
            FLURRY1                                 = 16256,
            FLURRY2                                 = 16281,
            FLURRY3                                 = 16282,
            FLURRY4                                 = 16283,
            FLURRY5                                 = 16284,
            SWORD_SPEC1                             = 12281,
            SWORD_SPEC2                             = 12812,
            SWORD_SPEC3                             = 12813,
            SWORD_SPEC4                             = 12814,
            SWORD_SPEC5                             = 12815,
            BLOOD_CRAZE1                            = 16487,
            BLOOD_CRAZE2                            = 16489,
            BLOOD_CRAZE3                            = 16492,
            TASTE_FOR_BLOOD1                        = 56636,
            TASTE_FOR_BLOOD2                        = 56637,
            TASTE_FOR_BLOOD3                        = 56638,
            UNRELENTING_ASSAULT1                    = 46859,
            UNRELENTING_ASSAULT2                    = 46860,
            TRAUMA1                                 = 46854,
            TRAUMA2                                 = 46855,
            BLOOD_FRENZY                            = 29859,
            RAMPAGE                                 = 29801,
            SECOND_WIND                             = 29838,//rank 2
            TOUGHNESS                               = 12764,//rank 5
            IMP_HAMSTRING                           = 23695,//rank 3
        //other
            WARRIOR_T10_4P                          = 70844
        };
        enum WarriorSpecial
        {
            TASTE_FOR_BLOOD_BUFF                    = 60503,
            LAMBS_TO_THE_SLAUGHTER_BUFF             = 84586,
            UNRELENTING_ASSAULT_SPELL               = 65925,//64849
            VICTORIOUS_SPELL                        = 32216,
            //COLOSSUS_SMASH_EFFECT                   = 108126,
            SWORD_SPECIALIZATION_TRIGGERED          = 16459,

            BLESSING_OF_MIGHT_1                     = 19740,
            GREATER_BLESSING_OF_MIGHT_1             = 25782
        };
    };
};

void AddSC_warrior_bot()
{
    new warrior_bot();
}
