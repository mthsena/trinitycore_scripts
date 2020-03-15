#include "Define.h"
#include "World.h"
#include "Config.h"
#include "DatabaseEnv.h"

#ifndef VIPSYSTEM_H
#define VIPSYSTEM_H

enum VipRates
{
    VIP_RATE_XP,
    VIP_RATE_HONOR,
    VIP_RATE_ARENA,
    VIP_RATE_REPUTATION,
    VIP_RATE_SKILL,
    VIP_RATE_CRAFTING,
    VIP_RATE_GATHERING,
};

class VipSystem
{
public:
    bool IsGm(uint32 accountId);
    bool IsVip(uint32 accountId);
    void AddVip(uint32 accountId, char* vipTime);
    void DelVip(uint32 accountId);
    void ModifyRate(uint32 accountId, VipRates vipRate, int& value);

    static VipSystem* instance()
    {
        static VipSystem instance;
        return &instance;
    }
};

#define sVipSystem VipSystem::instance()

#endif
