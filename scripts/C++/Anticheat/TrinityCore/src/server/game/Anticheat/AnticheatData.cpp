#include "AnticheatData.h"

const uint32 AnticheatData::GetLastOpcode() {
    return lastOpcode;
}

void AnticheatData::SetLastOpcode(uint32 opcode) {
    lastOpcode = opcode;
}

const MovementInfo& AnticheatData::GetLastMovementInfo() {
    return lastMovementInfo;
}

void AnticheatData::SetLastMovementInfo(MovementInfo& moveInfo) {
    lastMovementInfo = moveInfo;
}

const uint8 AnticheatData::GetReports() {
    return totalReports;
}

void AnticheatData::IncrementReports() {
    totalReports++;
}

const uint32 AnticheatData::GetRefreshTime() {
    return refreshTime;
}

void AnticheatData::SetRefreshTime(uint32 time) {
    refreshTime = time;
}

void AnticheatData::ResetPlayerData() {
    totalReports = 0;
    refreshTime = 0;
}
