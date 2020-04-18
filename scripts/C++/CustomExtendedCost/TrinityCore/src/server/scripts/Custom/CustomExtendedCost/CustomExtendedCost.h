#ifndef CUSTOMEXTENDEDCOST_H
#define CUSTOMEXTENDEDCOST_H

enum CustomCosts
{
    CUSTOM_COST_DISABLED = 1,
    CUSTOM_COST_HONOR = 2,
    CUSTOM_COST_ARENA = 3,
    CUSTOM_COST_ITEM = 4
};

class CustomExtendedCost
{
private:
    uint32 GetCustomCost(uint32 creatureId, uint32 itemId);
    uint32 GetCustomValue(uint32 creatureId, uint32 itemId);
    void SendMessage(Player* player, uint32 customCost, uint32 customValue, uint32 itemId);

public:
    static CustomExtendedCost* instance()
    {
        static CustomExtendedCost instance;
        return &instance;
    }

    bool IsEnabled(uint32 creatureId, uint32 itemId);
    void Initialize(Player* player, uint32 creatureId, uint32 itemId);
};

#define sCustomExtendedCost CustomExtendedCost::instance()

#endif
