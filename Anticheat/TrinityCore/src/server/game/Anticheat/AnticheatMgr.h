#include "AnticheatData.h"
#include <map>

#ifndef SC_ACMGR_H
#define SC_ACMGR_H

enum HackTypes {
    SPEED_HACK,
    FLY_HACK,
    WALL_CLIMB_HACK,
    WALK_ON_WATER_HACK,
    JUMP_HACK,
};

typedef std::map<uint32, AnticheatData> AnticheatPlayersDataMap;

class AnticheatMgr {
public:
    bool configEnable;

    AnticheatMgr();

    static AnticheatMgr* instance() {
        static AnticheatMgr instance;
        return &instance;
    }

    void StartDetection(Player* player, MovementInfo movementInfo, uint32 opcode);

    AnticheatPlayersDataMap m_Players;

private:
    uint32 configAction;
    uint32 configMaxReports;
    uint32 configRefreshTime;
    uint32 configAverageSpeed;
    uint32 configIgnoreLatency;
    uint32 configIgnoreAccountRank;

    void Punish(Player* player, uint8 hackType);
    void Report(Player* player, uint8 hackType);
    void SpeedHackDetection(Player* player, MovementInfo movementInfo);
    void FlyHackDetection(Player* player, MovementInfo movementInfo);
    void WallClimbHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode);
    void WalkOnWaterHackDetection(Player* player, MovementInfo movementInfo);
    void JumpHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode);
};

#define sAnticheatMgr AnticheatMgr::instance()

#endif
