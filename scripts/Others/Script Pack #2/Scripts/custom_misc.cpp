

#include "ScriptPCH.h"
#include "Config.h"

class ip_check : public PlayerScript
{
public:
    ip_check() : PlayerScript("ip_check") {}

    void OnLogin(Player* player)
    {
        if (sWorld->getBoolConfig(CONFIG_MULTIBOXING_KICK_ENABLE))
        {
            if (player->GetSession()->GetSecurity() > SEC_PLAYER)
                return;

            PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_IP_COUNT);
            stmt->setUInt32(0, player->GetSession()->GetAccountId());
            PreparedQueryResult result = LoginDatabase.Query(stmt);

            if(!result)
                return;

            Field* fields = result->Fetch();
            uint16 count = fields[0].GetUInt16();

            if (!count)
                return;

            if (count > 1)
                player->GetSession()->KickPlayer();
        }
        return;
    }
};

void AddSC_custom_misc()
{
    new ip_check();
}