--Code by Rochet2
--Edit by syaoraner          
--Update:20131019



    local ID = 50000 -- NPC entry 
    
    
    local Check = false -- true: Do not show items the player can't buy, false: show all vendor items in the list, even if the player does not have the mats.
    -- Set NPC entry at the bottom!
     
    local T = {}
    T.Items =
    {
    --      {{GivenItem, Amount}, {ReqItem1, Amount}, {ReqItem2, Amount}, ... {ReqItemN, Amount}}
            {{17, 2}, {49426, 1}, {47241, 1}},
            {{21176, 1}, {49426, 10}},
            {{49426, 2}, {47241, 5}}
    }
     
    T.Page = {}
    T.Buy = {}
    T.Options = 20
    local X = 10
     

        
        
    function T.Count(Page)
            if(not Page or Page < 1) then
                    return 1
            else
                    return (Page*T.Options)
            end
    end
     
    function T.Max(Count, LData)
            if(LData - Count >= T.Options) then
                    return Count+T.Options-1, true
            else
                    return LData, false
            end
    end
     
    function T.Name(Entry)
            return WorldDBQuery("SELECT Name FROM item_template WHERE entry = "..Entry):GetString(0)
    end
     
        function T.Hello(event, pPlayer, pUnit)
            local Items = {}
            for k,v in ipairs(T.Items) do
                    local Add = true
                    for i = 2, #v do
                            if(Check and (not pPlayer:HasItem(v[i][1]) or pPlayer:GetItemCount(v[i][1]) < v[i][2])) then
                                    Add = false
                                    break
                            end
                    end
                    if(Add) then
                            Items[#Items+1] = {k, v[1][1], v[1][2]}
                    end
            end
            local str = tostring(pPlayer)
            if(not T.Page[str] or T.Page[str] < 0) then
                    T.Page[str] = 0
            end
            local Page = T.Page[str]
            local Count = T.Count(Page)
            local Max, Next = T.Max(Count, #Items)
            --pPlayer:GossipCreateMenu(100, pPlayer, 0)
            if(Next) then
                pPlayer:GossipMenuAddItem(7, "Next page", 0, 3, 0)
            end
            if(Page > 0) then
                pPlayer:GossipMenuAddItem(7, "Previous page", 0, 4, 0)
            end
            pPlayer:GossipMenuAddItem(4, "Refresh", 0, 1, 0)
            --pPlayer:GossipMenuAddItem(1, "Preview page's items", 0, X, 0)
            --pPlayer:GossipMenuAddItem(1, "REMOVE TEST", 0, 6, 0)
            for k = Count, Max do
                    local Amount = ""
                    if(Items[k][3] > 1) then
                            Amount = Items[k][3].." "
                    end
                    local Name = T.Name(Items[k][2])
                    pPlayer:GossipMenuAddItem(3, Amount..Name, 0, X+Items[k][1], 0)
            end
            pPlayer:GossipSendMenu(1, pUnit)
    end
     
    function T.Select(event, pPlayer, pUnit, id, intid, code)
            local str = tostring(pPlayer)
            if(intid == 3) then
                    T.Page[str] = T.Page[str] + 1
            elseif(intid == 4) then
                    T.Page[str] = T.Page[str] - 1
            elseif(intid == 5) then
                    T.Select(666, pPlayer, pUnit, id, T.Buy[str], code)
                    return
            --elseif(intid == 6) then
            --pPlayer:RemoveItem(35, 1)

            --[[elseif(intid == X) then
                    pPlayer:GossipComplete()
                    VendorRemoveAllItems()
                    local Items = {}
                    for k,v in ipairs(T.Items) do
                            local Add = true
                            for i = 2, #v do
                                    if(Check and (not pPlayer:HasItem(v[i][1]) or pPlayer:GetItemCount(v[i][1]) < v[i][2])) then
                                            Add = false
                                            break
                                    end
                            end
                            if(Add) then
                                    Items[#Items+1] = v[1][1]
                            end
                            end
                    local Page = T.Page[str]
                    local Count = T.Count(Page)
                    local Max, Next = T.Max(Count, #Items)
                    for k = Count, Max do
                            pPlayer:AddVendorItem(Items[k], -1, 0)
                    end
                        pPlayer:SendVendorWindow(pUnit)
                        return]]--
            elseif(T.Items[intid-X]) then
                    if(event ~= 666) then
                            T.Buy[str] = intid 
                                    pPlayer:SendBroadcastMessage("You want to get this?") 
                                    local Name = T.Name(T.Items[intid-X][1][1])
                                    pPlayer:SendBroadcastMessage(T.Items[intid-X][1][2].." \124cff00B0E4\124Hitem:"..T.Items[intid-X][1][1]..":0:0:0:0:0:0:0:0\124h["..Name.."]\124h\124r")
                                    pPlayer:SendBroadcastMessage("You need these items to purchase")                             
                                    for i = 2, #T.Items[intid-X] do
                                    local Name = T.Name(T.Items[intid-X][i][1])                                     
                                    pPlayer:SendBroadcastMessage(T.Items[intid-X][i][2].." \124cff00B0E4\124Hitem:"..T.Items[intid-X][i][1]..":0:0:0:0:0:0:0:0\124h["..Name.."]\124h\124r")
                            end
                            local Name = T.Name(T.Items[intid-X][1][1])
                            --pPlayer:GossipCreateMenu(100, pPlayer, 0)
                            pPlayer:GossipMenuAddItem(1, "Exchange "..T.Items[intid-X][1][2].." "..Name, 0, 5, 0, "Exchange "..T.Items[intid-X][1][2].." "..Name.."!")
                            pPlayer:GossipMenuAddItem(6, "Show what you need have in your bags", 0, intid, 0)
                            pPlayer:GossipMenuAddItem(7, "Back..", 0, 1, 0)
                            pPlayer:GossipSendMenu(1, pUnit)
                            return
                    else
                            local intid = intid-X
                            local Add = true
                            for i = 2, #T.Items[intid] do
                                    if(not pPlayer:HasItem(T.Items[intid][i][1]) or pPlayer:GetItemCount(T.Items[intid][i][1]) < T.Items[intid][i][2]) then
                                            Add = false
                                            break
                                    end
                            end
                            if(Add) then
                                    local Done = 0
                                    local nCount = 0
                                    for k = 1, T.Items[intid][1][2] do    
                                                nCount = pPlayer:GetItemCount(T.Items[intid][1][1])                                       
                                                pPlayer:AddItem(T.Items[intid][1][1], 1)                                                  
                                                if(pPlayer:GetItemCount(T.Items[intid][1][1]) == (nCount + 1) ) then
                                                    --pPlayer:SendAreaTriggerMessage("TEST")
                                                    Done = Done + 1
                                                else
                                                    --if(pPlayer:GetItemCount(T.Items[intid][1][1]) < T.Items[intid][1][2]) then
                                                    --pPlayer:SendAreaTriggerMessage("TEST1")
                                                    pPlayer:RemoveItem(T.Items[intid][1][1], Done)
                                                    --pPlayer:SendAreaTriggerMessage("TEST2")
                                                    pPlayer:SendAreaTriggerMessage("Your inventory is too full")
                                                    break
                                                end                                                
                                    end
                                    if(Done == T.Items[intid][1][2]) then
                                            for i = 2, #T.Items[intid] do
                                                    pPlayer:RemoveItem(T.Items[intid][i][1], T.Items[intid][i][2])
                                            end
                                    else
                                                T.Select(0, pPlayer, pUnit, id, intid+X, code)
                                            return
                                    end
                            else
                                    pPlayer:SendAreaTriggerMessage("You do not have the required items")
                                    if(not Check) then
                                            T.Select(0, pPlayer, pUnit, id, intid+X, code)
                                            return
                                    end
                            end
                    end
            end
                            T.Hello(event, pPlayer, pUnit)
    end
     
        

    RegisterCreatureGossipEvent(ID, 1, T.Hello)
    RegisterCreatureGossipEvent(ID, 2, T.Select)

