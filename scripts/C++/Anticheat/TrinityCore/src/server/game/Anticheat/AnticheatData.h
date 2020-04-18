#include "Define.h"
#include "MovementGenerator.h"

#ifndef SC_ACDATA_H
#define SC_ACDATA_H

class AnticheatData {
public:
    const uint32 GetLastOpcode();
    void SetLastOpcode(uint32 opcode);

    const MovementInfo& GetLastMovementInfo();
    void SetLastMovementInfo(MovementInfo& moveInfo);

    const uint8 GetReports();
    void IncrementReports();

    const uint32 GetRefreshTime();
    void SetRefreshTime(uint32 time);

    void ResetPlayerData();

private:
    uint32 lastOpcode;
    MovementInfo lastMovementInfo;
    uint8 totalReports;
    uint32 refreshTime;
};

#endif
