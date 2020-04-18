#include "ScriptPCH.h"
#include <cstring>
class vendor_general : public CreatureScript
{
    public:
        vendor_general()
            : CreatureScript("vendor_general")
        {
        }
        bool OnGossipHello(Player* player, Creature* creature)
        {
   player->currentVendorEntry = -1;
            player->GetSession()->SendListInventory(creature->GetGUID());
            return true;
        }
};
void AddSC_vendor_general()
{
    new vendor_general();
}