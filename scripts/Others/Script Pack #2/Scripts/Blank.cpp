/************************************************************************/
/* Copyright (C) 2006 DotA-WoW Team, assistance by Woof.                */
/************************************************************************/
#include "game/StdAfx.h"

/* Script Export Declarations */
extern "C" WOWD_SCRIPT_DECL CreatureAIScript* CreateCreatureAIClass(uint32 uEntryId, Creature* creature);
extern "C" WOWD_SCRIPT_DECL InstanceScript* CreateInstanceClass(uint32 uMapId, MapMgr* instance);
extern "C" WOWD_SCRIPT_DECL void ScriptInitialize(ScriptModule *mod);

// Build version info function
BUILD_VERSIONINFO_DATA(SCRIPTLIB_VERSION_MAJOR, SCRIPTLIB_VERSION_MINOR);

/* This is needed because windows is a piece of shit. ;) */
#ifdef WIN32

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    return TRUE;
}

#endif


/************************************************************************/
/* INSTANCE / MAP SCRIPTING SECTION                                     */
/************************************************************************/

class DotABattleground : public InstanceScript
{
public:
    DotABattleground(MapMgr* mapmgr) : InstanceScript(mapmgr)
    {
        script_debuglog("dotabattleground instance script CREATED!");

        // Register our update event.
        // Called every 1 second.
        mapmgr->RegisterScriptUpdater(1000);

        // reset all variables
        tPushPlayersToJail = 0;
        tRemovePlayersFromJail = 0;
        tJailMsg1 = 0;
        tJailMsg2 = 0;
        
        // set our battleground var
        me = ((WarsongGulch*)sBattlegroundMgr.GetBattlegroundByInstanceID(_instance->GetInstanceID(), 2));
        ASSERT(me);
    }

    void TransportPlayers(float* AllianceVector, float* HordeVector)
    {
        script_debuglog("player transport:\n    alliance: %f %f %f\n    horde: %f %f %f", AllianceVector[0],
            AllianceVector[1], AllianceVector[2], HordeVector[0], HordeVector[1], HordeVector[2]);

        std::list<Player*>::iterator iter = me->GetPlayersBegin();
        Player *plyr;
        for(; iter != me->GetPlayersEnd(); ++iter)
        {
            plyr = *iter;
            if(plyr->GetTeam() == 0)    // Alliance
            {
                plyr->Relocate(_instance->GetMapId(), AllianceVector[0],
                    AllianceVector[1], AllianceVector[2], plyr->GetOrientation(), false, false);
            }
            else
            {
                plyr->Relocate(_instance->GetMapId(), HordeVector[0],
                    HordeVector[1], HordeVector[2], plyr->GetOrientation(), false, false);
            }
        }
    }

    void UpdateEvent()
    {
        // Update our timers

        if(tPushPlayersToJail)
        {
            if(getMSTime() > tPushPlayersToJail)
            {
                script_debuglog("pushing all players into jail.");

                // Time to push all the battlegrounds players into our temporary jail cell.
                float AllianceJailVector[3] = {1512.233154f, 1457.687866f, 362.712616f};
                float HordeJailVector[3] = {942.312927f, 1458.473389f, 356.188507f};

                // Send them all to jail.
                TransportPlayers(AllianceJailVector, HordeJailVector);

                // Disable the timer so we don't get double transports.
                tPushPlayersToJail = 0;

                // Set timer for first message at 10 seconds.
                tJailMsg1 = getMSTime() + 10000;
            }
        }

        if(tRemovePlayersFromJail)
        {
            if(getMSTime() > tRemovePlayersFromJail)
            {
                script_debuglog("removing all players from jail.");

                // Time to push all the battlegrounds players back to the start.
                float AllianceStartVector[3] = {1519.423096f, 1476.264648f, 352.043610f};
                float HordeStartVector[3] = {934.636108f, 1434.188843f, 345.535767f};

                // Send them all to jail.
                TransportPlayers(AllianceStartVector, HordeStartVector);

                // Disable the timer so we don't get double transports.
                tRemovePlayersFromJail= 0;

                // Remove the jail walls.
                DespawnJailWalls();
            }
        }

        if(tJailMsg1)
        {
            if(getMSTime() > tJailMsg1)
            {
                script_debuglog("jail message 1");

                string msg = MSG_COLOR_YELLOW;
                msg += "Discuss your tactics for the next round! It will start in 1 minute.";

                me->SendCMessageToAll(msg.c_str(), false);
                tJailMsg1 = 0;

                // Set next timer.
                tJailMsg2 = getMSTime() + 30000;
            }
        }

        if(tJailMsg2)
        {
            if(getMSTime() > tJailMsg2)
            {
                script_debuglog("jail message 2");

                string msg = MSG_COLOR_LIGHTRED;
                msg += "The battleground is respawning. All objects will be deleted/recreated, some players may experience lag for a few seconds.";
                me->SendCMessageToAll(msg.c_str(), false);

                script_debuglog("respawning battleground");
                me->GetMapMgr()->Respawn(true, true);

                msg = MSG_COLOR_YELLOW;
                msg += "The next round will begin in 30 seconds.";

                me->SendCMessageToAll(msg.c_str(), false);
                tJailMsg2 = 0;

                // Set next timer.
                tRemovePlayersFromJail = getMSTime() + 30000;
            }
        }
    }

    struct govector
    {
        uint32 entry;
        float x;
        float y;
        float z;
    };

    void SpawnJailWalls()
    {
        script_debuglog("spawning jail walls");

        // Spawn gameobjects in specific locations to hold players in :P
        static govector AllianceObjects[] =
        {
            { 175352, 1503.853882f, 1458.184082f, 362.711946f },
            { 175352, 1520.908081f, 1457.287231f, 362.701782f },
            { 0, 0.0f, 0.0f, 0.0f },
        };

        static govector HordeObjects[] =
        {
            { 175352, 932.693542f, 1458.518188f, 356.453979f },
            { 175352, 951.369995f, 1458.481201f, 356.188507f },
            { 0, 0.0f, 0.0f, 0.0f },
        };

        for(uint32 i = 0; AllianceObjects[i].entry != 0; ++i)
        {
            GameObject *pGo = _instance->GetInterface()->SpawnGameObject(AllianceObjects[i].entry,
                                    AllianceObjects[i].x, AllianceObjects[i].y, AllianceObjects[i].z, 0, false, 0, 0);
            ASSERT(pGo);
            pGo->SetUInt32Value(GAMEOBJECT_FLAGS, 33);
            pGo->Spawn();

            jailgameobjects.push(pGo);
        }

        for(uint32 i = 0; HordeObjects[i].entry != 0; ++i)
        {
            GameObject *pGo = _instance->GetInterface()->SpawnGameObject(HordeObjects[i].entry,
                HordeObjects[i].x, HordeObjects[i].y, HordeObjects[i].z, 0, false, 0, 0);
            ASSERT(pGo);
            pGo->SetUInt32Value(GAMEOBJECT_FLAGS, 33);
            pGo->Spawn();

            jailgameobjects.push(pGo);
        }
    }

    void DespawnJailWalls()
    {
        script_debuglog("removing jail walls");

        // Remove jail walls.
        GameObject *pGameObject;
        while(!jailgameobjects.empty())
        {
            pGameObject = jailgameobjects.front();
            jailgameobjects.pop();

            // Despawn him (fade animation !)
            pGameObject->Despawn(60000);

            // Delete him from memory.
            _instance->GetInterface()->DeleteGameObject(pGameObject);
        }
    }

    void PlayerScores(Unit* victim, Player* killer, uint32 team)
    {
        // We've already sent the message saying that we've scored and the sound.
        // Let's increase the score by one.
        if(team == 0)
            me->SetHordeScore(me->GetHordeScore() + 1);
        else
            me->SetAllianceScore(me->GetAllianceScore() + 1);

        if(me->GetAllianceScore() == 3 || me->GetHordeScore() == 3)
        {
            // maybe do smth?
        }
        else
        {
            // we need to reset players, put them in jail, etc.
            string msg = MSG_COLOR_LIGHTBLUE;
            msg += "A round was won. Players will be teleported to their jail cells shortly.";
            me->SendCMessageToAll(msg.c_str(), false);

            // spawn jail walls
            script_debuglog("round won");
            SpawnJailWalls();

            // move players to jail cells in 5 seconds
            tPushPlayersToJail = getMSTime() + 5000;    // 5 second timer.

            // root all players
            std::list<Player*>::iterator iter = me->GetPlayersBegin();
            Player *plyr;
            for(; iter != me->GetPlayersEnd(); ++iter)
            {
                 (*iter)->SetMovement(MOVE_ROOT, 1);
            }
        }
    }

    inline WarsongGulch * GetMe() { return me; }
protected:
    
    // temporary jail gameobject set.
    std::queue<GameObject*> jailgameobjects;

    // our timers
    uint32 tPushPlayersToJail;
    uint32 tRemovePlayersFromJail;
    uint32 tEndGame;

    uint32 tJailMsg1;
    uint32 tJailMsg2;

    WarsongGulch *me;
};

/************************************************************************/
/* GENERAL DOTA CREATURE SECTION                                        */
/************************************************************************/

class DotACreature : public CreatureAIScript
{
public:
    DotACreature(Creature *creature) : CreatureAIScript(creature)
    {
        mDeathCausesScore = false;
        onDeathText = "";
        onCombatText = "";
        onKilledText = "";
        combatsound = 0;
        deathsound = 0;
        team = 0;
    }
    virtual void OnLoad()
    {
        myscript = static_cast<DotABattleground*>(_unit->GetMapMgr()->GetScript());
        wsg = myscript->GetMe();
    }

    virtual void OnDied(Unit *mKiller)
    {
        if(onDeathText.size())
        {
            string cmsg = MSG_COLOR_RED;
            cmsg += onDeathText;

            wsg->SendCMessageToAll(cmsg.c_str(), true);
        }

        if(deathsound)
            wsg->SendSoundToBattleground(deathsound);

        if(mDeathCausesScore && mKiller->GetTypeId() == TYPEID_PLAYER)
            myscript->PlayerScores(_unit, static_cast<Player*>(mKiller), team);
    }

    virtual void OnCombatStart()
    {
        if(onCombatText.size())
        {
            string cmsg = MSG_COLOR_RED;
            cmsg += onCombatText;

            wsg->SendCMessageToAll(cmsg.c_str(), true);
        }

        if(combatsound)
            wsg->SendSoundToBattleground(combatsound);
    }

    virtual void OnTargetDied(Unit* mTarget)
    {
        if(onKilledText.size())
        {
            string cmsg = MSG_COLOR_RED;
            cmsg += onKilledText;

            wsg->SendCMessageToAll(cmsg.c_str(), true);
        }
    }

protected:
    DotABattleground * myscript;
    bool mDeathCausesScore;
    uint32 team;
    string onDeathText;
    string onKilledText;
    string onCombatText;
    uint32 combatsound;
    uint32 deathsound;

    WarsongGulch * wsg;
};

/************************************************************************/
/* DOTA BOSS SCRIPTING SECTION                                          */
/************************************************************************/

// Tyrande Whisperwind - Silverwing/Alliance boss

class Tyrande_Whisperwind : public DotACreature
{
public:
    Tyrande_Whisperwind(Creature* pCreature) : DotACreature(pCreature)
    {
        // Set me up.
        mDeathCausesScore = true;
        onDeathText = "The Horde Score! Tyrande Whisperwind was killed!";
        onCombatText = "The Horde Is Advancing! Tyrande Whisperwind is under attack!";
        onKilledText = "That was a warning. Leave us in piece.";
        combatsound = SOUND_HORDE_CAPTURE;
        deathsound = SOUND_HORDE_SCORES;
        team = 0;
    }

    void OnDied(Unit* mKiller)
    {
        if(mKiller->GetTypeId() != TYPEID_PLAYER)
			return;

		// Unit Chat Message
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Elune give me strength...");
        DotACreature::OnDied(mKiller);
	}

    void OnCombatStart(Unit* mTarget)
    {
		if(mTarget->GetTypeId() != TYPEID_PLAYER)
			return;

        _unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "You dare to engage the Silverwing Elite!?");
        DotACreature::OnCombatStart();

        string msg = MSG_COLOR_BLUE;
        msg += "Tutorial: You have attacked the boss. Kill him to score a point for your team.";
        wsg->SendCMessageToPlayer(static_cast<Player*>(mTarget), msg.c_str(), false);
    }

    void Destroy()
    {
        delete (Tyrande_Whisperwind*)this;
    }
};

// Varimathras AI Script - horde boss

class Varimathras : public DotACreature
{
public:
    Varimathras(Creature* pCreature) : DotACreature(pCreature)
    {
        // Set me up.
        mDeathCausesScore = true;
        onDeathText = "The Alliance Score! Varimathras was killed!";
        onCombatText = "The Alliance Is Advancing! Varimathras is under attack!";
        onKilledText = "Pathetic scum, when will you learn that you are no match for the mighty horde.";
        combatsound = SOUND_ALLIANCE_CAPTURE;
        deathsound = SOUND_ALLIANCE_SCORES;
        team = 1;
    }

    void OnDied(Unit* mKiller)
    {
		if(mKiller->GetTypeId() != TYPEID_PLAYER)
			return;

		// Unit Chat Message
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "This is not possible! The powerful Varimathras defeated by a bunch of worms!");

        DotACreature::OnDied(mKiller);
    }

	void OnCombatStart(Unit* mTarget)
    {
		if(mTarget->GetTypeId() != TYPEID_PLAYER)
			return;

		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "You think you can match the might of a Dreadlord!");
        DotACreature::OnCombatStart();

        string msg = MSG_COLOR_BLUE;
        msg += "Tutorial: You have attacked the boss. Kill him to score a point for your team.";
        wsg->SendCMessageToPlayer(static_cast<Player*>(mTarget), msg.c_str(), false);
    }

    void Destroy()
    {
        delete (Varimathras*)this;
    }
};

CreatureAIScript* CreateCreatureAIClass(uint32 uEntryId, Creature* creature)
{
	switch(uEntryId)
	{
	case 7999:	// Tyrande Whisperwind
		return new Tyrande_Whisperwind(creature);
		break;
	case 2425:	// Varimthras
		return new Varimathras(creature);
		break;
	}
	return 0;
}

/************************************************************************/
/* Instance Class Factory                                               */
/************************************************************************/

InstanceScript* CreateInstanceClass(uint32 uMapId, MapMgr* instance)
{
    switch(uMapId)
    {
    case 489:    // WSG
        return new DotABattleground(instance);
        break;
    }

    return 0;
}

/************************************************************************/
/* Script Initialize - Bind entries to this module.                     */
/************************************************************************/

void ScriptInitialize(ScriptModule *mod)
{
    sScriptMgr.ScriptAddCreatureModule(7999, mod);   // Tyrande Whisperwind
    sScriptMgr.ScriptAddCreatureModule(2425, mod);   // Varimathras

    sScriptMgr.ScriptAddInstanceModule(489, mod);   // Warsong Gulch
}