	

    --[[ ____                                   __    __                    
    /\  _`\               /'\_/`\          /\ \__/\ \      __          
    \ \ \L\ \  __  __    /\      \     __  \ \ ,_\ \ \___ /\_\   __  _  
     \ \  _ <'/\ \/\ \   \ \ \__\ \  /'__`\ \ \ \/\ \  _ `\/\ \ /\ \/'\
      \ \ \L\ \ \ \_\ \   \ \ \_/\ \/\ \L\.\_\ \ \_\ \ \ \ \ \ \\/>  </
       \ \____/\/`____ \   \ \_\\ \_\ \__/.\_\\ \__\\ \_\ \_\ \_\/\_/\_\
        \/___/  `/___/> \   \/_/ \/_/\/__/\/_/ \/__/ \/_/\/_/\/_/\//\/_/
                   /\___/                                              
                   \/__/                                               ]]
                               
     
    local ChatMsg = "#world"
                               
    function GetVIPLevel(playername)
            local VIPLevel = WorldDBQuery("SELECT VIPLevel from vip_players where PlayerName='" .. playername .. "'")
        local level = 0
            if(VIPLevel) then
            repeat
                level = VIPLevel:GetUInt32(0)
            until not VIPLevel:NextRow()
            end
        return level
    end
     
    function WorldChat(event, plr, msg, Type, lang)
            local startpos, endpos = string.find(msg, ChatMsg)
        if(startpos == 1) then
            local text = msg:gsub(ChatMsg, "")
                    local PlrName = plr:GetName()
                   
                    if GetVIPLevel(PlrName) == 0 and plr:IsGM() == false then
                            for k,v in pairs(GetPlayersInWorld()) do
                                    v:SendBroadcastMessage("|CFF4AA02C[World Channel]|r|CFF4AA02C["..PlrName.."]:|r"..text)
                            end
                   
                    elseif GetVIPLevel(PlrName) == 1 and plr:IsGM() == false then
                            for k,v in pairs(GetPlayersInWorld()) do
                                    v:SendBroadcastMessage("|CFF4AA02C[World Channel]|r|CFFFDD017["..PlrName.."]:|r"..text)
                            end
                           
                    elseif GetVIPLevel(PlrName) == 2 and plr:IsGM() == false then
                            for k,v in pairs(GetPlayersInWorld()) do
                                    v:SendBroadcastMessage("|CFF4AA02C[World Channel]|r|CFFF87217["..PlrName.."]:|r"..text)
                            end
                           
                    elseif GetVIPLevel(PlrName) == 3 and plr:IsGM() == false then
                            for k,v in pairs(GetPlayersInWorld()) do
                                    v:SendBroadcastMessage("|CFF4AA02C[World Channel]|r|CFFE42217["..PlrName.."]:|r"..text)
                            end
                           
                    elseif plr:IsGM() == true then
                            for k,v in pairs(GetPlayersInWorld()) do
                                    v:SendBroadcastMessage("|CFF4AA02C[World Channel]|r|CFF1100FF["..PlrName.."]:|r"..text)
                            end
                    end
                    return false
            end
    end
     
    RegisterServerHook(18, WorldChat)

