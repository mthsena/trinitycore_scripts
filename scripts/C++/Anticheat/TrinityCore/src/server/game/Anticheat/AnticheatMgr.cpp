#include "AnticheatMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

AnticheatMgr::AnticheatMgr() {
    configEnable = sConfigMgr->GetBoolDefault("Anticheat.Enable", 1);
    configAction = sConfigMgr->GetIntDefault("Anticheat.Action", 0);
    configMaxReports = sConfigMgr->GetIntDefault("Anticheat.MaxReports", 10);
    configRefreshTime = sConfigMgr->GetIntDefault("Anticheat.RefreshTime", 5000);
    configAverageSpeed = sConfigMgr->GetIntDefault("Anticheat.AverageSpeed", 1000);
    configIgnoreLatency = sConfigMgr->GetIntDefault("Anticheat.IgnoreLatency", 1000);
    configIgnoreAccountRank = sConfigMgr->GetIntDefault("Anticheat.IgnoreAccountRank", 0);
}

void AnticheatMgr::StartDetection(Player* player, MovementInfo movementInfo, uint32 opcode) {
    uint32 key = player->GetGUID().GetCounter();

    if (player->GetSession()->GetSecurity() > configIgnoreAccountRank)
        return;

    if (player->GetSession()->GetLatency() > configIgnoreLatency)
        return;

    if (m_Players[key].GetRefreshTime() <= getMSTime() || m_Players[key].GetReports() >= configMaxReports)
        m_Players[key].ResetPlayerData();

    if (m_Players[key].GetRefreshTime() == 0)
        m_Players[key].SetRefreshTime(getMSTime() + configRefreshTime);

    if (player->IsInFlight() || player->GetTransport() || player->GetVehicle()) {
        m_Players[key].SetLastMovementInfo(movementInfo);
        m_Players[key].SetLastOpcode(opcode);
        return;
    }

    SpeedHackDetection(player, movementInfo);
    FlyHackDetection(player, movementInfo);
    WallClimbHackDetection(player, movementInfo, opcode);
    JumpHackDetection(player, movementInfo, opcode);

    m_Players[key].SetLastMovementInfo(movementInfo);
    m_Players[key].SetLastOpcode(opcode);
}

void AnticheatMgr::Punish(Player* player, uint8 hackType) {
    std::string str;
    SessionMap sessions;

    switch (hackType) {
    case SPEED_HACK:
        str = "Speed-Hack";
        break;
    case FLY_HACK:
        str = "Fly-Hack";
        break;
    case WALL_CLIMB_HACK:
        str = "WallClimb-Hack";
        break;
    case WALK_ON_WATER_HACK:
        str = "WalkOnWater-Hack";
        break;
    case JUMP_HACK:
        str = "Jump-Hack";
        break;
    }

    switch (configAction) {
    case 0:
        sessions = sWorld->GetAllSessions();
        for (SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr) {
            if (itr->second->GetSecurity() > configIgnoreAccountRank)
                ChatHandler(itr->second).PSendSysMessage("[AntiCheat] :: Player [%s] %s suspect.", player->GetName().c_str(), str.c_str());
        }
        break;
    case 1:
        player->TeleportTo(1, 16217.738281f, 16403.453125f, -64.378838f, 3.121913f);
        player->CastSpell(player, 9454);
        break;
    case 2:
        player->GetSession()->KickPlayer();
        break;
    }
}

void AnticheatMgr::Report(Player* player, uint8 hackType) {
    uint32 key = player->GetGUID().GetCounter();

    if (m_Players[key].GetReports() <= configMaxReports)
        m_Players[key].IncrementReports();

    switch (hackType) {
    case WALL_CLIMB_HACK:
    case WALK_ON_WATER_HACK:
    case JUMP_HACK:
        Punish(player, hackType);
        break;
    default:
        if (m_Players[key].GetReports() > 1)
            ChatHandler(player->GetSession()).PSendSysMessage("[AntiCheat] :: %u/%u to punish.", m_Players[key].GetReports(), configMaxReports);
        if (m_Players[key].GetReports() >= configMaxReports)
            Punish(player, hackType);
        break;
    }
}

void AnticheatMgr::SpeedHackDetection(Player* player, MovementInfo movementInfo) {
    uint32 key = player->GetGUID().GetCounter();

    // We also must check the map because the movementFlag can be modified by the client.
    // If we just check the flag, they could always add that flag and always skip the speed hacking detection.
    // 369 == DEEPRUN TRAM
    if (m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_ONTRANSPORT) && player->GetMapId() == 369)
        return;

    uint32 distance2D = (uint32)movementInfo.pos.GetExactDist2d(&m_Players[key].GetLastMovementInfo().pos);
    UnitMoveType moveType;

    // we need to know HOW is the player moving
    // TO-DO: Should we check the incoming movement flags?
    if (player->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
        moveType = MOVE_SWIM;
    else if (player->HasUnitMovementFlag(MOVEMENTFLAG_FLYING))
        moveType = MOVE_FLIGHT;
    else if (player->HasUnitMovementFlag(MOVEMENTFLAG_WALKING))
        moveType = MOVE_WALK;
    else
        moveType = MOVE_RUN;

    // how many yards the player can do in one sec.
    uint32 speedRate = (uint32)(player->GetSpeed(UnitMoveType(moveType)) + movementInfo.jump.xyspeed);

    // how long the player took to move to here.
    uint32 timeDiff = getMSTimeDiff(m_Players[key].GetLastMovementInfo().time, movementInfo.time);

    if (!timeDiff)
        timeDiff = 1;

    // this is the distance doable by the player in 1 sec, using the time done to move to this point.
    uint32 clientSpeedRate = distance2D * configAverageSpeed / timeDiff;

    // we did the (uint32) cast to accept a margin of tolerance
    if (clientSpeedRate > speedRate)
        Report(player, SPEED_HACK);
}

void AnticheatMgr::FlyHackDetection(Player* player, MovementInfo movementInfo) {
    uint32 key = player->GetGUID().GetCounter();

    if (!m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING))
        return;

    if (player->HasAuraType(SPELL_AURA_FLY) ||
        player->HasAuraType(SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED) ||
        player->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) ||
        player->HasAuraType(SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED) ||
        player->HasAuraType(SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS) ||
        player->HasAuraType(SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK))
        return;

    Report(player, FLY_HACK);
}

void AnticheatMgr::WallClimbHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode) {
    uint32 key = player->GetGUID().GetCounter();

    if (opcode != MSG_MOVE_HEARTBEAT || m_Players[key].GetLastOpcode() != MSG_MOVE_HEARTBEAT)
        return;

    // in this case we don't care if they are "legal" flags, they are handled in another parts of the Anticheat Manager.
    if (player->IsInWater() || player->IsFlying() || player->IsFalling())
        return;

    Position playerPos;

    float deltaZ = fabs(playerPos.GetPositionZ() - movementInfo.pos.GetPositionZ());
    float deltaXY = movementInfo.pos.GetExactDist2d(&playerPos);

    float angle = Position::NormalizeOrientation(tan(deltaZ / deltaXY));

    if (angle > 1.8f)
        Report(player, WALL_CLIMB_HACK);
}

void AnticheatMgr::WalkOnWaterHackDetection(Player* player, MovementInfo movementInfo) {
    uint32 key = player->GetGUID().GetCounter();

    if (!m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_WATERWALKING))
        return;

    // if we are a ghost we can walk on water
    if (!player->IsAlive())
        return;

    if (player->HasAuraType(SPELL_AURA_FEATHER_FALL) ||
        player->HasAuraType(SPELL_AURA_SAFE_FALL) ||
        player->HasAuraType(SPELL_AURA_WATER_WALK))
        return;

    Report(player, WALK_ON_WATER_HACK);
}

void AnticheatMgr::JumpHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode) {
    uint32 key = player->GetGUID().GetCounter();

    if (m_Players[key].GetLastOpcode() == MSG_MOVE_JUMP && opcode == MSG_MOVE_JUMP)
        Report(player, JUMP_HACK);
}
