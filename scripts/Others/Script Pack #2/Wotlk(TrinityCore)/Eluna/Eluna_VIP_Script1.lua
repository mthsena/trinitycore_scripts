	

    --[[ ____                                   __    __                    
    /\  _`\               /'\_/`\          /\ \__/\ \      __          
    \ \ \L\ \  __  __    /\      \     __  \ \ ,_\ \ \___ /\_\   __  _  
     \ \  _ <'/\ \/\ \   \ \ \__\ \  /'__`\ \ \ \/\ \  _ `\/\ \ /\ \/'\
      \ \ \L\ \ \ \_\ \   \ \ \_/\ \/\ \L\.\_\ \ \_\ \ \ \ \ \ \\/>  </
       \ \____/\/`____ \   \ \_\\ \_\ \__/.\_\\ \__\\ \_\ \_\ \_\/\_/\_\
        \/___/  `/___/> \   \/_/ \/_/\/__/\/_/ \/__/ \/_/\/_/\/_/\//\/_/
                   /\___/                                              
                   \/__/                                              
CREATE TABLE `vip_players` (
	`PlayerName` TEXT NULL COLLATE 'utf16_danish_ci',
	`VIPLevel` INT(11) NULL DEFAULT NULL,
	`GUID` INT(11) NULL DEFAULT NULL
)
COLLATE='utf16_danish_ci'
ENGINE=InnoDB;

     ]]
     
    local file_dir = "scripts/vip_log.txt"
    local file = assert(io.open(file_dir, "a"))
     
    function GrantVIP3(playername, guid)
            if GetVIPLevel(playername) == 3 then
                    plr:SendBroadcastMessage(" ".. playername .. " is already VIP level 3!")
            elseif GetVIPLevel(playername) == 0 then
                    WorldDBQuery("INSERT INTO `vip_players` (`PlayerName`, `VIPLevel`, `GUID`) VALUES ('" .. playername .. "', 3, " .. guid .. ")")
            elseif GetVIPLevel(playername) >= 1 then
                    WorldDBQuery("UPDATE vip_players SET VIPLevel='3' where PlayerName='".. playername .."'")
            end
    end
     
    function GrantVIP2(playername, guid)
            if GetVIPLevel(playername) == 2 then
                    plr:SendBroadcastMessage(" ".. playername .. " is already VIP level 2!")
            elseif GetVIPLevel(playername) == 0 then
                    WorldDBQuery("INSERT INTO `vip_players` (`PlayerName`, `VIPLevel`, `GUID`) VALUES ('" .. playername .. "', 2, " .. guid .. ")")
            elseif GetVIPLevel(playername) >= 1 then
                    WorldDBQuery("UPDATE vip_players SET VIPLevel='2' where PlayerName='".. playername .."'")
            end
    end
     
    function GrantVIP1(playername, guid)
            if GetVIPLevel(playername) == 1 then
                    plr:SendBroadcastMessage(" ".. playername .. " is already VIP level 1!")
            elseif GetVIPLevel(playername) == 0 then
                    WorldDBQuery("INSERT INTO `vip_players` (`PlayerName`, `VIPLevel`, `GUID`) VALUES ('" .. playername .. "', 1, " .. guid .. ")")
            elseif GetVIPLevel(playername) >= 1 then
                    WorldDBQuery("UPDATE vip_players SET VIPLevel='1' where PlayerName='".. playername .."'")
            end
    end
     
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
     
    function RemoveVIP(playername)
            WorldDBQuery("DELETE FROM vip_players WHERE PlayerName='" .. playername .. "'")
    end
     
    function VIPMSG(event, plr, msg, Type, lang)
            if msg == "#VIP" then
                    plr:SendBroadcastMessage("Your VIP level is " .. GetVIPLevel(plr:GetName()))
                    return false
                   
            elseif msg == "#vip" then
                    plr:SendBroadcastMessage("Your VIP level is " .. GetVIPLevel(plr:GetName()))
                    return false
                   
            elseif msg == "#viphelp" then
                    plr:SendBroadcastMessage("VIP commands for players:")
                    plr:SendBroadcastMessage("#vip - Tells you your VIP level.")
                    plr:SendBroadcastMessage("#vipmall - Teleports you to the VIP mall, requires level 1.")
		    plr:SendBroadcastMessage("#master - Displays vip master.")  --tc
                    plr:SendBroadcastMessage("#viphelp - Displays this message.")
                    return false
            
	    elseif msg == "#maser" then
                    plr:SendBroadcastMessage("Master Menu:")
                    plr:SendBroadcastMessage("#gohome")
                    plr:SendBroadcastMessage("...")
                    return false 
      
            elseif msg == "#vipmall" then
                    if GetVIPLevel(plr:GetName()) >= 0 and plr:IsInCombat() == false then    
                            plr:Teleport(1,16222.1,16252.1,12.5872,4.635658)
                            plr:SendBroadcastMessage("You've been teleported to the VIP mall, Sir " .. plr:GetName() .. ".")
                    else
                            plr:SendBroadcastMessage("Your VIP level is too low " .. plr:GetName() .. ". Please go to the website to purchase your VIP status.")
                    end
                    return false
           
            elseif msg == "#setviplvl3" then
                    local Target = plr:GetSelection()
                    local TargetName = Target:GetName()
                    local PlrName = plr:GetName()
                    local TargetGUID = Target:GetGUID()
     
                    if plr:IsGM() == true then
                            if GetVIPLevel(TargetName) == 3 then
                                    plr:SendBroadcastMessage("".. TargetName .. " is already VIP level 3!")
                            else                           
                                    GrantVIP3(TargetName, TargetGUID)
                                    plr:SendBroadcastMessage("Granted " .. TargetName .. " VIP level 3")
                                    local line = os.date("%x [%X]", os.time())..": "..TargetName.." was granted VIP Level 3 by "..PlrName
                                    file:write(line.."\n")
                                    file:flush()
                            end
                    else
                            plr:SendBroadcastMessage("You must be a GM to use this command.")
                    end
                    return false
                   
            elseif msg == "#setviplvl2" then
                    local Target = plr:GetSelection()
                    local TargetName = Target:GetName()
                    local PlrName = plr:GetName()
                    local TargetGUID = Target:GetGUID()
     
                    if plr:IsGM() == true then
                            if GetVIPLevel(TargetName) == 2 then
                                    plr:SendBroadcastMessage("".. TargetName .. " is already VIP level 2!")
                            else                           
                                    GrantVIP2(TargetName, TargetGUID)
                                    plr:SendBroadcastMessage("Granted " .. TargetName .. " VIP level 2")
                                    local line = os.date("%x [%X]", os.time())..": "..TargetName.." was granted VIP Level 2 by "..PlrName
                                    file:write(line.."\n")
                                    file:flush()
                            end
                    else
                            plr:SendBroadcastMessage("You must be a GM to use this command.")
                    end
                    return false
                   
            elseif msg == "#setviplvl1" then
                    local Target = plr:GetSelection()
                    local TargetName = Target:GetName()
                    local PlrName = plr:GetName()
                    local TargetGUID = Target:GetGUID()
     
                    if plr:IsGM() == true then
                            if GetVIPLevel(TargetName) == 1 then
                                    plr:SendBroadcastMessage("".. TargetName .. " is already VIP level 1!")
                            else                           
                                    GrantVIP1(TargetName, TargetGUID)
                                    plr:SendBroadcastMessage("Granted " .. TargetName .. " VIP level 1")
                                    local line = os.date("%x [%X]", os.time())..": "..TargetName.." was granted VIP Level 1 by "..PlrName
                                    file:write(line.."\n")
                                    file:flush()
                            end
                    else
                            plr:SendBroadcastMessage("You must be a GM to use this command.")
                    end
                    return false
                   
            elseif msg == "#removevip" then
                    local Target = plr:GetSelection()
                    local TargetName = Target:GetName()
                    local PlrName = plr:GetName()
                   
                    if plr:IsGM() == true then
                            if GetVIPLevel(TargetName) >= 1 then
                                    RemoveVIP(TargetName)
                                    plr:SendBroadcastMessage("You have removed " ..TargetName.."'s VIP levels!")
                                    local line = os.date("%x [%X]", os.time())..": "..TargetName.." had his VIP level(s) removed by "..PlrName
                                    file:write(line.."\n")
                                    file:flush()
                            else
                                    plr:SendBroadcastMessage(""..TargetName.." is not a VIP.")
                            end
                    else
                            plr:SendBroadcastMessage("You must be a GM to use this command.")
                    end
                    return false
            end
    end
     
    function VIPDelete(event, guid)
            WorldDBQuery("DELETE FROM vip_players WHERE GUID='" .. guid .. "'")
    end
     
    RegisterServerHook(18, VIPMSG)
    RegisterServerHook(2, VIPDelete)

