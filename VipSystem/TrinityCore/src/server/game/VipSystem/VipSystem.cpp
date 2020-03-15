#include "VipSystem.h"

bool VipSystem::IsGm(uint32 accountId)
{
    QueryResult result = LoginDatabase.PQuery("SELECT id FROM account_access WHERE id = %u AND gmlevel > %u", accountId, SEC_VIP);
    if (result)
        return true;
    else
        return false;
}

bool VipSystem::IsVip(uint32 accountId)
{
    QueryResult result = LoginDatabase.PQuery("SELECT id FROM account_access WHERE id = %u AND gmlevel = %u", accountId, SEC_VIP);
    if (result)
        return true;
    else
        return false;
}

void VipSystem::AddVip(uint32 accountId, char* vipTime)
{
    LoginDatabase.PQuery("INSERT INTO account_access (id, gmlevel, RealmID, vipTime) VALUES (%u, %u, '-1', %u)", accountId, SEC_VIP, time(NULL) + TimeStringToSecs(vipTime));
}

void VipSystem::DelVip(uint32 accountId)
{
    LoginDatabase.PQuery("DELETE FROM account_access WHERE id = %u AND gmlevel = %u", accountId, SEC_VIP);
}

void VipSystem::ModifyRate(uint32 accountId, VipRates vipRate, int& value)
{
    if (IsVip(accountId))
    {
        switch (vipRate)
        {
        case VIP_RATE_XP:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.XP", 2);
            break;
        case VIP_RATE_HONOR:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.Honor", 2);
            break;
        case VIP_RATE_ARENA:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.Arena", 2);
            break;
        case VIP_RATE_REPUTATION:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.Reputation", 2);
            break;
        case VIP_RATE_SKILL:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.Skill", 2);
            break;
        case VIP_RATE_CRAFTING:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.Crafting", 2);
            break;
        case VIP_RATE_GATHERING:
            value *= sConfigMgr->GetIntDefault("Vip.Rate.Gathering", 2);
            break;
        }
    }
}
