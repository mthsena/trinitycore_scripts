   
    local itemid =6948
    function Tele_Book(event, player, item)
            if (player:IsInCombat() == true) then
                    player:SendAreaTriggerMessage("U can't use this while u are in combat!")
            else
                    Tele_Menu(item, player)
            end
    end
     
    function Tele_Menu(item, player) -- Home Page
    --player:GossipMenuAddItem(5, "|cffff6060TELEPORT STONE.|r", 0,  998)
    player:GossipMenuAddItem(6, "|cFF191970Main Cities|r", 0,  1)
    player:GossipMenuAddItem(2, "|cFF191970Azeroth Locations|r", 0,  2)
    player:GossipMenuAddItem(2, "|cFF191970Azeroth Instances|r", 0,  3)
    player:GossipMenuAddItem(2, "|cFF191970Azeroth Raids|r", 0,  4)
    player:GossipMenuAddItem(2, "|cFF191970Outland Locations|r", 0,  5)
    player:GossipMenuAddItem(2, "|cFF191970Outland Instances|r", 0,  6)
    player:GossipMenuAddItem(2, "|cFF191970Outland Raids|r", 0,  7)
    player:GossipMenuAddItem(2, "|cFF191970Northrend Locations|r", 0,  8)
    player:GossipMenuAddItem(2, "|cFF191970Northrend Instances|r", 0,  9)
    player:GossipMenuAddItem(2, "|cFF191970Northrend Raids|r", 0,  10)
    player:GossipMenuAddItem(9, "|cFF191970Gurubashi Arena|r", 0,  13)
    player:GossipMenuAddItem(0, "|cFF191970Next Page|r", 0,  997)
    player:GossipSendMenu(1, item)
    end
     
    function Tele_Select(event, player, item, sender, intid, code)
    local plyr = player:GetRace()
    local x, y, z, o = player:GetX(), player:GetY(), player:GetZ(), player:GetO()
     
    if (intid == 997) then -- Home Page Cont.
            player:GossipMenuAddItem(5, "|cFF191970Shattrath City|r", 0,  11)
            player:GossipMenuAddItem(0, "|cFF191970Remove Ressurection Sickness", 0, 16)
            player:GossipMenuAddItem(3, "|cFF191970Professions|r", 0,  17)
            player:GossipMenuAddItem(5, "|cFF191970Set my profession skills to 450", 0, 18)
            player:GossipMenuAddItem(0, "|cFF191970Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 1) then -- Alliance Cities
            if (plyr == 1) or (plyr == 3) or (plyr == 4) or (plyr == 7) or (plyr == 11) then
                    player:GossipMenuAddItem(2, "|c00FF0000Stormwind|r", 0,  19)
                    player:GossipMenuAddItem(2, "|c00FF0000Ironforge|r", 0,  20)
                    player:GossipMenuAddItem(2, "|c00FF0000Darnassus|r", 0,  21)
                    player:GossipMenuAddItem(2, "|c00FF0000Exodar|r", 0,  22)
                    player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
                    player:GossipSendMenu(1, item)
            end
                                    -- Horde Cities
            if (plyr == 2) or (plyr == 5) or (plyr == 6) or (plyr == 8) or (plyr == 10) then
                    player:GossipMenuAddItem(2, "|c00FF0000Orgimmar|r", 0,  23)
                    player:GossipMenuAddItem(2, "|c00FF0000Thunderbluff|r", 0,  24)
                    player:GossipMenuAddItem(2, "|c00FF0000Undercity|r", 0,  25)
                    player:GossipMenuAddItem(2, "|c00FF0000Silvermoon|r", 0,  26)
                    player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
                    player:GossipSendMenu(1, item)
            end
    end
     
    if (intid == 2) then -- Azeroth Continets

            player:GossipMenuAddItem(2, "|c00FF0000Eastern Kingdoms|r", 0,  27)
            player:GossipMenuAddItem(2, "|c00FF0000Kalimdor|r", 0,  28)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 3) then -- Azeroth Instances
            player:GossipMenuAddItem(2, "|c00FF0000Blackfathom Deeps|r", 0,  29)
            player:GossipMenuAddItem(2, "|c00FF0000Blackrock Depths|r", 0,  30)
            player:GossipMenuAddItem(2, "|c00FF0000Dire Maul|r", 0,  31)
            player:GossipMenuAddItem(2, "|c00FF0000Gnomeregan|r", 0,  32)
            player:GossipMenuAddItem(2, "|c00FF0000Maraudon|r", 0,  33)
            if (plyr == 2) or (plyr == 5) or (plyr == 6) or (plyr == 8) or (plyr == 10) then
                    player:GossipMenuAddItem(2, "|c00FF0000Ragefire Chasm|r", 0,  34)
            end
            player:GossipMenuAddItem(2, "|c00FF0000Razorfen Downs|r", 0,  35)
            player:GossipMenuAddItem(2, "|c00FF0000Razorfen Kraul|r", 0,  36)
            player:GossipMenuAddItem(2, "|c00FF0000Scarlet Monastery|r", 0,  37)
            player:GossipMenuAddItem(2, "|c00FF0000Scholomance|r", 0,  38)
            player:GossipMenuAddItem(2, "|c00FF0000Shadowfang Keep|r", 0,  39)
            player:GossipMenuAddItem(2, "|c00FF0000Stratholme|r", 0,  40)
            player:GossipMenuAddItem(2, "|c00FF0000Sunken Temple|r", 0,  41)
            player:GossipMenuAddItem(2, "|c00FF0000The Deadmines|r", 0,  42)
            if (plyr == 1) or (plyr == 3) or (plyr == 4) or (plyr == 7) or (plyr == 11) then
                    player:GossipMenuAddItem(2, "|c00FF0000The Stockade|r", 0,  43)
            end
            player:GossipMenuAddItem(0, "|c99006600Next Page|r", 0,  994)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 994) then -- Azeroth Instances Cont.
            player:GossipMenuAddItem(2, "|c00FF0000Uldaman|r", 0,  44)
            player:GossipMenuAddItem(2, "|c00FF0000Wailing Caverns|r", 0,  45)
            player:GossipMenuAddItem(2, "|c00FF0000Zul'Farrak|r", 0,  46)
            player:GossipMenuAddItem(0, "|c99006600Previous Page|r", 0,  3)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 4) then -- Azeroth Raids
            player:GossipMenuAddItem(2, "|c00FF0000Blackwing Lair|r", 0,  47)
            player:GossipMenuAddItem(2, "|c00FF0000Molten Core|r", 0,  48)
            player:GossipMenuAddItem(2, "|c00FF0000Onyxia's Lair|r", 0,  49)
            player:GossipMenuAddItem(2, "|c00FF0000Ruins of Ahn'Qiraj|r", 0,  50)
            player:GossipMenuAddItem(2, "|c00FF0000Temple of Ahn'Qiraj|r", 0,  51)
            player:GossipMenuAddItem(2, "|c00FF0000Zul'Gurub|r", 0, 52)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 5) then -- Outland Locations
            player:GossipMenuAddItem(2, "|c00FF0000Blade's Edge Mountains|r", 0,  53)
            player:GossipMenuAddItem(2, "|c00FF0000Hellfire Peninsula|r", 0,  54)
            player:GossipMenuAddItem(2, "|c00FF0000Nagrand|r", 0,  55)
            player:GossipMenuAddItem(2, "|c00FF0000Netherstorm|r", 0,  56)
            player:GossipMenuAddItem(2, "|c00FF0000Shadowmoon Valley|r", 0,  57)
            player:GossipMenuAddItem(2, "|c00FF0000Terokkar Forest|r", 0,  58)
            player:GossipMenuAddItem(2, "|c00FF0000Zangarmarsh|r", 0,  59)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 6) then -- Outland Instances
            player:GossipMenuAddItem(2, "|c00FF0000Auchindoun|r", 0,  60)
            player:GossipMenuAddItem(2, "|c00FF0000Caverns of Time|r", 0,  61)
            player:GossipMenuAddItem(2, "|c00FF0000Coilfang Reservoir|r", 0,  62)
            player:GossipMenuAddItem(2, "|c00FF0000Hellfire Citadel|r", 0,  63)
            player:GossipMenuAddItem(2, "|c00FF0000Magisters' Terrace|r", 0,  64)
            player:GossipMenuAddItem(2, "|c00FF0000Tempest Keep|r", 0,  65)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 7) then -- Outland Raids
            player:GossipMenuAddItem(2, "|c00FF0000Black Temple|r", 0,  66)
            player:GossipMenuAddItem(2, "|c00FF0000Hyjal Summit|r", 0,  67)
            player:GossipMenuAddItem(2, "|c00FF0000Serpentshrine Cavern|r", 0,  68)
            player:GossipMenuAddItem(2, "|c00FF0000Gruul's Lair|r", 0,  69)
            player:GossipMenuAddItem(2, "|c00FF0000Magtheridon's Lair|r", 0,  70)
            player:GossipMenuAddItem(2, "|c00FF0000Karazhan|r", 0, 71)
            player:GossipMenuAddItem(2, "|c00FF0000Sunwell Plateau|r", 0,  72)
            player:GossipMenuAddItem(2, "|c00FF0000The Eye|r", 0,  73)
            player:GossipMenuAddItem(2, "|c00FF0000Zul'Aman|r", 0,  74)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0,  999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 8) then -- Northrend Locations
            player:GossipMenuAddItem(2, "|c00FF0000Borean Tundra|r", 0, 75)
            player:GossipMenuAddItem(2, "|c00FF0000Crystalsong Forest|r", 0, 76)
            player:GossipMenuAddItem(2, "|c00FF0000DragonBlight|r", 0, 77)
            player:GossipMenuAddItem(2, "|c00FF0000Grizzly Hills|r", 0, 78)
            player:GossipMenuAddItem(2, "|c00FF0000Howling Fjord|r", 0, 79)
            player:GossipMenuAddItem(2, "|c00FF0000Icecrown|r", 0, 80)
            player:GossipMenuAddItem(2, "|c00FF0000Sholazar Basin|r", 0, 81)
            player:GossipMenuAddItem(2, "|c00FF0000The Storm Peaks|r", 0, 82)
            player:GossipMenuAddItem(2, "|c00FF0000WinterGrasp|r", 0, 83)
            player:GossipMenuAddItem(2, "|c00FF0000Zul'Drak|r", 0, 84)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 9) then -- Northrend Instances
            player:GossipMenuAddItem(2, "|c00FF0000Azjol-Nerub|r", 0, 85)
            player:GossipMenuAddItem(2, "|c00FF0000Drak'Tharon Keep|r", 0, 86)
            player:GossipMenuAddItem(2, "|c00FF0000Gundrak|r", 0, 87)
            player:GossipMenuAddItem(2, "|c00FF0000The Culling of Stratholme|r", 0, 88)
            player:GossipMenuAddItem(2, "|c00FF0000The Halls of Lightning|r", 0, 89)
            player:GossipMenuAddItem(2, "|c00FF0000The Halls of Stone|r", 0, 90)
            player:GossipMenuAddItem(2, "|c00FF0000The Nexus|r", 0, 91)
            player:GossipMenuAddItem(2, "|c00FF0000The Violet Hold|r", 0, 92)
            player:GossipMenuAddItem(2, "|c00FF0000Utgarde Keep|r", 0, 93)
            player:GossipMenuAddItem(2, "|c00FF0000Utgarde Pinnacle|r", 0, 94)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 10) then -- Northrend Raids
            player:GossipMenuAddItem(2, "|c00FF0000Naxxramas|r", 0, 95)
            player:GossipMenuAddItem(2, "|c00FF0000The Eye of Eternity|r", 0, 96)
            player:GossipMenuAddItem(2, "|c00FF0000The Obsidian Sanctum|r", 0, 97)
            player:GossipMenuAddItem(2, "|c00FF0000Ulduar|r", 0, 98)
            player:GossipMenuAddItem(2, "|c00FF0000Vault of Archavon|r", 0, 99)
            player:GossipMenuAddItem(0, "|c99006600Home Page|r", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
     
    -- Shattrath
     
    if (intid == 11) then
            player:Teleport(530, -1817.82, 5453.04, -12.42, 0)
            player:GossipComplete()
    end
     
     
    -- Gurubashi Arena
     
    if (intid == 13) then
            player:Teleport(0, -13261.30, 164.45, 35.78, 0)
            player:GossipComplete()
    end
     
     
    --[[ Buff
     
    if (intid == 14) then
            player:SpawnCreature(90001, x, y, z, o, 35, 30000, 0)
            player:GossipComplete()
    end
      ]]
     
     
    -- Heal
     
    if (intid == 15) then
            player:SetHealthPct(100)
            player:SendBroadcastMessage("You have been healed.")
            player:GossipComplete()
    end
     
     
    -- Remove Ressurection Sickness
     
    if (intid == 16) then
            player:LearnSpell(15007)
            player:RemoveSpell(15007)
            player:SendBroadcastMessage("Your sickness has been removed.")
            player:GossipComplete()
    end
     
     
    -- Learn Professions
     
    if (intid == 17) then -- Professions

            player:GossipMenuAddItem(5, "Alchemy", 0, 100)
            player:GossipMenuAddItem(5, "Blacksmithing", 0, 101)
            player:GossipMenuAddItem(5, "Enchanting", 0, 102)
            player:GossipMenuAddItem(5, "Engineering", 0, 103)
            player:GossipMenuAddItem(5, "Herbalism", 0, 104)
            player:GossipMenuAddItem(5, "Inscription", 0, 105)
            player:GossipMenuAddItem(5, "Jewelcrafting", 0, 106)
            player:GossipMenuAddItem(5, "Leatherworking", 0, 107)
            player:GossipMenuAddItem(5, "Mining", 0, 108)
            player:GossipMenuAddItem(5, "Skinning", 0, 109)
            player:GossipMenuAddItem(5, "Tailoring", 0, 110)
            player:GossipMenuAddItem(0, "Secondary Professions", 0, 111)
            player:GossipMenuAddItem(0, "Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
     
    -- Advance Professions
     
    if (intid == 18) then
            player:AdvanceSkill(171, 450)
            player:AdvanceSkill(164, 450)
            player:AdvanceSkill(333, 450)
            player:AdvanceSkill(202, 450)
            player:AdvanceSkill(182, 450)
            player:AdvanceSkill(773, 450)
            player:AdvanceSkill(755, 450)
            player:AdvanceSkill(165, 450)
            player:AdvanceSkill(186, 450)
            player:AdvanceSkill(393, 450)
            player:AdvanceSkill(197, 450)
            player:AdvanceSkill(185, 450)
            player:AdvanceSkill(129, 450)
            player:AdvanceSkill(356, 450)
            player:GossipComplete()
    end
     
     
    -- Alliance Cities
     
    if (intid == 19) then -- Stormwind
            player:Teleport(0, -8913.23, 554.63, 93.79, 0)
            player:GossipComplete()
    end
     
    if (intid == 20) then -- Ironforge
            player:Teleport(0, -4982.16, -880.75, 501.65, 0)
            player:GossipComplete()
    end
     
    if (intid == 21) then -- Darnassus
            player:Teleport(1, 9945.49, 2609.89, 1316.26, 0)
            player:GossipComplete()
    end
     
    if (intid == 22) then -- Exodar
            player:Teleport(530, -4002.67, -11875.54, -0.71, 0)
            player:GossipComplete()
    end
     
     
    -- Horde Cities
     
    if (intid == 23) then -- Orgimmar
            player:Teleport(1, 1502.71, -4415.41, 21.77, 0)
            player:GossipComplete()
    end
     
    if (intid == 24) then -- Thunderbluff
            player:Teleport(1, -1285.23, 117.86, 129.99, 0)
            player:GossipComplete()
    end
     
    if (intid == 25) then -- Undercity
            player:Teleport(0, 1831.26, 238.52, 60.52, 0)
            player:GossipComplete()
    end
     
    if (intid == 26) then -- Silvermoon
            player:Teleport(530, 9398.75, -7277.41, 14.21, 0)
            player:GossipComplete()
    end
     
     
    -- Azeroth Locations
     
    if (intid == 27) then -- Eastern Kingdoms
            player:GossipMenuAddItem(2, "Alterac Mountains", 0, 112)
            player:GossipMenuAddItem(2, "Arathi Highlands", 0, 113)
            player:GossipMenuAddItem(2, "Badlands", 0, 114)
            player:GossipMenuAddItem(2, "Blasted Lands", 0, 115)
            player:GossipMenuAddItem(2, "Burning Steppes", 0, 116)
            player:GossipMenuAddItem(2, "Deadwind Pass", 0, 117)
            player:GossipMenuAddItem(2, "Dun Morogh", 0, 118)
            player:GossipMenuAddItem(2, "Duskwood", 0, 119)
            player:GossipMenuAddItem(2, "Eastern Plaguelands", 0, 120)
            player:GossipMenuAddItem(2, "Elwynn Forest", 0, 121)
            player:GossipMenuAddItem(2, "Eversong Woods", 0, 122)
            player:GossipMenuAddItem(2, "Ghostlands", 0, 123)
            player:GossipMenuAddItem(2, "Hillsbrad Foothills", 0, 124)
            player:GossipMenuAddItem(2, "Isle of Quel'Danas", 0, 125)
            player:GossipMenuAddItem(0, "Next Page", 0, 996)
            player:GossipMenuAddItem(0, "Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 996) then -- Eastern Kingdoms Cont.
            player:GossipMenuAddItem(2, "Loch Modan", 0, 126)
            player:GossipMenuAddItem(2, "Redridge Mountains", 0, 127)
            player:GossipMenuAddItem(2, "Searing Gorge", 0, 128)
            player:GossipMenuAddItem(2, "Silverpine Forest", 0, 129)
            player:GossipMenuAddItem(2, "Stranglethorn Vale", 0, 130)
            player:GossipMenuAddItem(2, "Swamp of Sorrows", 0, 131)
            player:GossipMenuAddItem(2, "The Hinterlands", 0, 132)
            player:GossipMenuAddItem(2, "Tirisfal Glades", 0, 133)
            player:GossipMenuAddItem(2, "Western Plaguelands", 0, 134)
            player:GossipMenuAddItem(2, "Westfall", 0, 135)
            player:GossipMenuAddItem(2, "Wetlands", 0, 136)
            player:GossipMenuAddItem(0, "Previous Page", 0, 27)
            player:GossipMenuAddItem(0, "Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 28) then -- Kalimdor
            player:GossipMenuAddItem(2, "Ashenvale", 0, 137)
            player:GossipMenuAddItem(2, "Azshara", 0, 138)
            player:GossipMenuAddItem(2, "Azuremyst Isle", 0, 139)
            player:GossipMenuAddItem(2, "Bloodmyst Isle", 0, 140)
            player:GossipMenuAddItem(2, "Darkshore", 0, 141)
            player:GossipMenuAddItem(2, "Desolace", 0, 142)
            player:GossipMenuAddItem(2, "Durotar", 0, 143)
            player:GossipMenuAddItem(2, "Dustwallow Marsh", 0, 144)
            player:GossipMenuAddItem(2, "Felwood", 0, 145)
            player:GossipMenuAddItem(2, "Feralas", 0, 146)
            player:GossipMenuAddItem(2, "Moonglade", 0, 147)
            player:GossipMenuAddItem(2, "Mulgore", 0, 148)
            player:GossipMenuAddItem(2, "Silithus", 0, 149)
            player:GossipMenuAddItem(0, "Next Page", 0, 995)
            player:GossipMenuAddItem(0, "Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 995) then -- Kalimdor Cont.
            player:GossipMenuAddItem(2, "Stonetalon Mountains", 0, 150)
            player:GossipMenuAddItem(2, "Tanaris", 0, 151)
            player:GossipMenuAddItem(2, "Teldrassil", 0, 152)
            player:GossipMenuAddItem(2, "The Barrens", 0, 153)
            player:GossipMenuAddItem(2, "Thousand Needles", 0, 154)
            player:GossipMenuAddItem(2, "Un'Goro Crater", 0, 0, 155)
            player:GossipMenuAddItem(2, "Winterspring", 0, 156)
            player:GossipMenuAddItem(0, "Previous Page", 0, 28)
            player:GossipMenuAddItem(0, "Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
    if (intid == 29) then -- Blackfathom Deeps
            player:Teleport(1, 4247.34, 744.05, -24.71, 0)
            player:GossipComplete()
    end
     
    if (intid == 30) then -- Blackrock Depths
            player:Teleport(0, -7576.74, -1126.68, 262.26, 0)
            player:GossipComplete()
    end
     
    if (intid == 31) then -- Dire Maul
            player:Teleport(1, -3879.52, 1095.26, 154.78, 0)
            player:GossipComplete()
    end
     
    if (intid == 32) then -- Gnomeregan
            player:Teleport(0, -5162.63, 923.21, 257.17, 0)
            player:GossipComplete()
    end
     
    if (intid == 33) then -- Maraudon
            player:Teleport(1, -1412.73, 2816.92, 112.64, 0)
            player:GossipComplete()
    end
     
    if (intid == 34) then -- Ragefire Chasm
            player:Teleport(1, 1814.17, -4401.13, -17.67, 0)
            player:GossipComplete()
    end
     
    if (intid == 35) then -- Razorfen Downs
            player:Teleport(1, -4378.32, -1949.14, 88.57, 0)
            player:GossipComplete()
    end
     
    if (intid == 36) then -- Razorfen Kraul
            player:Teleport(1, -4473.31, -1810.05, 86.11, 0)
            player:GossipComplete()
    end
     
    if (intid == 37) then -- Scarlet Monastery
            player:Teleport(0, 2881.84, -816.23, 160.33, 0)
            player:GossipComplete()
    end
     
    if (intid == 38) then -- Scholomance
            player:Teleport(0, 1229.45, -2576.66, 90.43, 0)
            player:GossipComplete()
    end
     
    if (intid == 39) then -- Shadowfang Keep
            player:Teleport(0, -243.85, 1517.21, 76.23, 0)
            player:GossipComplete()
    end
     
    if (intid == 40) then -- Stratholme
            player:Teleport(0, 3362.14, -3380.05, 144.78, 0)
            player:GossipComplete()
    end
     
    if (intid == 41) then -- Sunken Temple
            player:Teleport(0, -10452.32, -3817.51, 18.06, 0)
            player:GossipComplete()
    end
     
    if (intid == 42) then -- The Deadmines
            player:Teleport(0, -11084.10, 1556.17, 48.12, 0)
            player:GossipComplete()
    end
     
    if (intid == 43) then -- The Stockade
            player:Teleport(0, -8797.29, 826.67, 97.63, 0)
            player:GossipComplete()
    end
     
    if (intid == 44) then -- Uldaman
            player:Teleport(0, -6072.23, -2955.94, 209.61, 0)
            player:GossipComplete()
    end
     
    if (intid == 45) then -- Wailing Caverns
            player:Teleport(1, -735.11, -2214.21, 16.83, 0)
            player:GossipComplete()
    end
     
    if (intid == 46) then -- Zul'Farrak
            player:Teleport(1, -6825.69, -2882.77, 8.91, 0)
            player:GossipComplete()
    end
     
     
    -- Azeroth Raids
     
    if (intid == 47) then -- Blackwing Lair
            player:Teleport(469, -7666.11, -1101.53, 399.67, 0)
            player:GossipComplete()
    end
     
    if (intid == 48) then -- Molten Core
            player:Teleport(230, 1117.61, -457.36, -102.49, 0)
            player:GossipComplete()
    end
     
    if (intid == 49) then -- Onyxia's Lair
            player:Teleport(1, -4697.81, -3720.44, 50.35, 0)
            player:GossipComplete()
    end
     
    if (intid == 50) then -- Ruins of Ahn'Qiraj
            player:Teleport(1, -8380.47, 1480.84, 14.35, 0)
            player:GossipComplete()
    end
     
    if (intid == 51) then -- Temple of Ahn'Qiraj
            player:Teleport(1, -8258.27, 1962.73, 129.89, 0)
            player:GossipComplete()
    end
     
    if (intid == 52) then -- Zul'Gurub
            player:Teleport(0, -11916.74, -1203.32, 92.28, 0)
            player:GossipComplete()
    end
     
     
    -- Outland Locations
     
    if (intid == 53) then -- Blade's Edge Mountains
            player:Teleport(530, 2039.24, 6409.27, 134.30, 0)
            player:GossipComplete()
    end
     
    if (intid == 54) then -- Hellfire Peninsula
            player:Teleport(530, -247.37, 964.77, 84.33, 0)
            player:GossipComplete()
    end
     
    if (intid == 55) then -- Nagrand
            player:Teleport(530, -605.84, 8442.39, 60.76, 0)
            player:GossipComplete()
    end
     
    if (intid == 56) then -- Netherstorm
            player:Teleport(530, 3055.70, 3671.63, 142.44, 0)
            player:GossipComplete()
    end
     
    if (intid == 57) then -- Shadowmoon Valley
            player:Teleport(530, -2859.75, 3184.24, 9.76, 0)
            player:GossipComplete()
    end
     
    if (intid == 58) then -- Terokkar Forest
            player:Teleport(530, -1917.17, 4879.45, 2.10, 0)
            player:GossipComplete()
    end
     
    if (intid == 59) then -- Zangarmarsh
            player:Teleport(530, -206.61, 5512.90, 21.58, 0)
            player:GossipComplete()
    end
     
     
    -- Outland Instances
     
    if (intid == 60) then -- Auchindoun
            player:Teleport(530, -3323.76, 4934.31, -100.21, 0)
            player:GossipComplete()
    end
     
    if (intid == 61) then -- Caverns of Time
            player:Teleport(1, -8187.16, -4704.91, 19.33, 0)
            player:GossipComplete()
    end
     
    if (intid == 62) then -- Coilfang Reservoir
            player:Teleport(530, 731.04, 6849.35, -66.62, 0)
            player:GossipComplete()
    end
     
    if (intid == 63) then -- Hellfire Citadel
            player:Teleport(530, -331.87, 3039.30, -16.66, 0)
            player:GossipComplete()
    end
     
    if (intid == 64) then -- Magisters' Terrace
            player:Teleport(530, 12884.92, -7333.78, 65.48, 0)
            player:GossipComplete()
    end
     
    if (intid == 65) then -- Tempest Keep
            player:Teleport(530, 3088.25, 1388.17, 185.09, 0)
            player:GossipComplete()
    end
     
     
    -- Outland Raids
     
    if (intid == 66) then -- Black Temple
            player:Teleport(530, -3638.16, 316.09, 35.40, 0)
            player:GossipComplete()
    end
     
    if (intid == 67) then -- Hyjal Summit
            player:Teleport(1, -8175.94, -4178.52, -166.74, 0)
            player:GossipComplete()
    end
     
    if (intid == 68) then -- Serpentshrine Cavern
            player:Teleport(530, 731.04, 6849.35, -66.62, 0)
            player:GossipComplete()
    end
     
    if (intid == 69) then -- Gruul's Lair
            player:Teleport(530, 3528.99, 5133.50, 1.31, 0)
            player:GossipComplete()
    end
     
    if (intid == 70) then -- Magtheridon's Lair
            player:Teleport(530, -337.50, 3131.88, -102.92, 0)
            player:GossipComplete()
    end
     
    if (intid == 71) then -- Karazhan
            player:Teleport(0, -11119.22, -2010.73, 47.09, 0)
            player:GossipComplete()
    end
     
    if (intid == 72) then -- Sunwell Plateau
            player:Teleport(530, 12560.79, -6774.58, 15.08, 0)
            player:GossipComplete()
    end
     
    if (intid == 73) then -- The Eye
            player:Teleport(530, 3088.25, 1388.17, 185.09, 0)
            player:GossipComplete()
    end
     
    if (intid == 74) then -- Zul'Aman
            player:Teleport(530, 6850, -7950, 170, 0)
            player:GossipComplete()
    end
     
     
    -- Northrend Locations
     
    if (intid == 75) then -- Borean Tundra
            player:Teleport(571, 2920.15, 4043.40, 1.82, 0)
            player:GossipComplete()
    end
     
    if (intid == 76) then -- Crystalsong Forest
            player:Teleport(571, 5371.18, 109.11, 157.65, 0)
            player:GossipComplete()
    end
     
    if (intid == 77) then -- Dragonblight
            player:Teleport(571, 2729.59, 430.70, 66.98, 0)
            player:GossipComplete()
    end
     
    if (intid == 78) then -- Grizzly Hills
            player:Teleport(571, 3587.20, -4545.12, 198.75, 0)
            player:GossipComplete()
    end
     
    if (intid == 79) then -- Howling Fjord
            player:Teleport(571, 154.39, -4896.33, 296.14, 0)
            player:GossipComplete()
    end
     
    if (intid == 80) then -- Icecrown
            player:Teleport(571, 8406.89, 2703.79, 665.17, 0)
            player:GossipComplete()
    end
     
    if (intid == 81) then -- Sholazar Basin
            player:Teleport(571, 5569.49, 5762.99, -75.22, 0)
            player:GossipComplete()
    end
     
    if (intid == 82) then -- The Storm Peaks
            player:Teleport(571, 6180.66, -1085.65, 415.54, 0)
            player:GossipComplete()
    end
     
    if (intid == 83) then -- Wintergrasp
            player:Teleport(571, 5044.03, 2847.23, 392.64, 0)
            player:GossipComplete()
    end
     
    if (intid == 84) then -- Zul'Drak
            player:Teleport(571, 4700.09, -3306.54, 292.41, 0)
            player:GossipComplete()
    end
     
     
    -- Northrend Instances
     
    if (intid == 85) then -- Azjol-Nerub
            player:Teleport(571, 3738.93, 2164.14, 37.29, 0)
            player:GossipComplete()
    end
     
    if (intid == 86) then -- Drak'Tharon
            player:Teleport(571, 4772.13, -2035.85, 229.38, 0)
            player:GossipComplete()
    end
     
    if (intid == 87) then -- Gundrak
            player:Teleport(571, 6937.12, -4450.80, 450.90, 0)
            player:GossipComplete()
    end
     
    if (intid == 88) then -- The Culling of Stratholme
            player:Teleport(1, -8746.94, -4437.69, -199.98, 0)
            player:GossipComplete()
    end
     
    if (intid == 89) then -- The Halls of Lightning
            player:Teleport(571, 9171.01, -1375.94, 1099.55, 0)
            player:GossipComplete()
    end
     
    if (intid == 90) then -- The Halls of Stone
            player:Teleport(571, 8921.35, -988.56, 1039.37, 0)
            player:GossipComplete()
    end
     
    if (intid == 91) then -- The Nexus
            player:Teleport(571, 3784.76, 6941.97, 104.49, 0)
            player:GossipComplete()
    end
     
    if (intid == 92) then -- The Violet Hold
            player:Teleport(571, 5695.19, 505.38, 652.68, 0)
            player:GossipComplete()
    end
     
    if (intid == 93) then -- Utgarde Keep
            player:Teleport(571, 1222.44, -4862.61, 41.24, 0)
            player:GossipComplete()
    end
     
    if (intid == 94) then -- Utgarde Pinnacle
            player:Teleport(571, 1251.10, -4856.31, 215.86, 0)
            player:GossipComplete()
    end
     
     
    -- Northrend Raids
     
    if (intid == 95) then -- Naxxramas
            player:Teleport(571, 3669.77, -1275.48, 243.51, 0)
            player:GossipComplete()
    end
     
    if (intid == 96) then -- The Eye of Eternity
            player:Teleport(571, 3873.50, 6974.83, 152.04, 0)
            player:GossipComplete()
    end
     
    if (intid == 97) then -- The Obsidian Sanctum
            player:Teleport(571, 3547.39, 267.95, -115.96, 0)
            player:GossipComplete()
    end
     
    if (intid == 98) then -- Ulduar
            player:Teleport(571, 9330.53, -1115.40, 1245.14, 0)
            player:GossipComplete()
    end
     
    if (intid == 99) then -- Vault of Archavon
            player:Teleport(571, 5410.21, 2842.37, 418.67, 0)
            player:GossipComplete()
    end
     
     
    -- Professions
     
    if (intid == 100) then -- Alchemy
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 158)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51303)
                    player:LearnSpell(58871)
                    player:LearnSpell(58868)
                    player:LearnSpell(60403)
                    player:LearnSpell(60396)
                    player:LearnSpell(60405)
                    player:LearnSpell(57427)
                    player:LearnSpell(57425)
                    player:LearnSpell(60350)
                    player:LearnSpell(53840)
                    player:LearnSpell(53898)
                    player:LearnSpell(54218)
                    player:LearnSpell(60367)
                    player:LearnSpell(53847)
                    player:LearnSpell(53903)
                    player:LearnSpell(54213)
                    player:LearnSpell(53902)
                    player:LearnSpell(53901)
                    player:LearnSpell(53848)
                    player:LearnSpell(53839)
                    player:LearnSpell(53905)
                    player:LearnSpell(53899)
                    player:LearnSpell(53900)
                    player:LearnSpell(53812)
                    player:LearnSpell(53838)
                    player:LearnSpell(53836)
                    player:LearnSpell(53837)
                    player:LearnSpell(53842)
                    player:LearnSpell(53841)
                    player:LearnSpell(53042)
                    player:LearnSpell(60893)
    end
     
    if (intid == 101) then -- Blacksmithing
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 160)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51298)
                    player:LearnSpell(55374)
                    player:LearnSpell(55377)
                    player:LearnSpell(55372)
                    player:LearnSpell(55375)
                    player:LearnSpell(55373)
                    player:LearnSpell(55376)
                    player:LearnSpell(55370)
                    player:LearnSpell(55369)
                    player:LearnSpell(55371)
                    player:LearnSpell(56234)
                    player:LearnSpell(56400)
                    player:LearnSpell(59406)
                    player:LearnSpell(61008)
                    player:LearnSpell(55303)
                    player:LearnSpell(55302)
                    player:LearnSpell(56555)
                    player:LearnSpell(56554)
                    player:LearnSpell(56556)
                    player:LearnSpell(55304)
                    player:LearnSpell(55311)
                    player:LearnSpell(55310)
                    player:LearnSpell(55312)
                    player:LearnSpell(61009)
                    player:LearnSpell(61010)
                    player:LearnSpell(56357)
                    player:LearnSpell(55839)
                    player:LearnSpell(55732)
                    player:LearnSpell(55656)
    end
     
    if (intid == 102) then -- Enchanting

                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 162)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51312)
                    player:LearnSpell(60619)
                    player:LearnSpell(47900)
                    player:LearnSpell(60668)
                    player:LearnSpell(44593)
                    player:LearnSpell(44509)
                    player:LearnSpell(60663)
                    player:LearnSpell(44489)
                    player:LearnSpell(44589)
                    player:LearnSpell(44598)
                    player:LearnSpell(44529)
                    player:LearnSpell(44508)
                    player:LearnSpell(44488)
                    player:LearnSpell(44633)
                    player:LearnSpell(44510)
                    player:LearnSpell(44584)
                    player:LearnSpell(44484)
                    player:LearnSpell(44616)
                    player:LearnSpell(47766)
                    player:LearnSpell(44645)
                    player:LearnSpell(44636)
                    player:LearnSpell(59636)
                    player:LearnSpell(44635)
                    player:LearnSpell(44492)
                    player:LearnSpell(44500)
                    player:LearnSpell(44513)
                    player:LearnSpell(60653)
                    player:LearnSpell(44629)
                    player:LearnSpell(44582)
                    player:LearnSpell(44630)
                    player:LearnSpell(60623)
                    player:LearnSpell(44528)
                    player:LearnSpell(60621)
                    player:LearnSpell(60606)
                    player:LearnSpell(44555)
                    player:LearnSpell(44506)
                    player:LearnSpell(32667)
                    player:LearnSpell(44623)
                    player:LearnSpell(60616)
                    player:LearnSpell(44592)
                    player:LearnSpell(27958)
                    player:LearnSpell(60609)
     
    end
     
    if (intid == 103) then -- Engineering
    
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 164)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51305)
                    player:LearnSpell(56479)
                    player:LearnSpell(60874)
                    player:LearnSpell(56462)
                    player:LearnSpell(56478)
                    player:LearnSpell(56469)
                    player:LearnSpell(56472)
                    player:LearnSpell(56470)
                    player:LearnSpell(56467)
                    player:LearnSpell(56466)
                    player:LearnSpell(61483)
                    player:LearnSpell(56477)
                    player:LearnSpell(56475)
                    player:LearnSpell(56476)
                    player:LearnSpell(56474)
                    player:LearnSpell(56468)
                    player:LearnSpell(55016)
                    player:LearnSpell(54353)
                    player:LearnSpell(54998)
                    player:LearnSpell(54999)
                    player:LearnSpell(63770)
                    player:LearnSpell(61471)
                    player:LearnSpell(56471)
                    player:LearnSpell(54736)
                    player:LearnSpell(55002)
                    player:LearnSpell(54793)
                    player:LearnSpell(63765)
                    player:LearnSpell(56463)
                    player:LearnSpell(56461)
                    player:LearnSpell(56459)
                    player:LearnSpell(56464)
    end
     
    if (intid == 104) then -- Herbalism
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 166)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(50301)
    end
     
    if (intid == 105) then -- Inscription
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 168)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(45380)
                    player:LearnSpell(58483)
                    player:LearnSpell(58491)
                    player:LearnSpell(50604)
                    player:LearnSpell(50611)
                    player:LearnSpell(59504)
                    player:LearnSpell(59498)
                    player:LearnSpell(59497)
                    player:LearnSpell(50620)
                    player:LearnSpell(59501)
                    player:LearnSpell(61117)
                    player:LearnSpell(61118)
                    player:LearnSpell(61119)
                    player:LearnSpell(61120)
                    player:LearnSpell(61177)
                    player:LearnSpell(57715)
                    player:LearnSpell(60337)
    end
     
     
    if (intid == 106) then -- Jewelcrafting
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 170)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51310)
                    player:LearnSpell(56197)
                    player:LearnSpell(55402)
                    player:LearnSpell(55399)
                    player:LearnSpell(55394)
                    player:LearnSpell(55386)
                    player:LearnSpell(56203)
                    player:LearnSpell(59759)
                    player:LearnSpell(56199)
                    player:LearnSpell(56202)
                    player:LearnSpell(56201)
                    player:LearnSpell(53969)
                    player:LearnSpell(53947)
                    player:LearnSpell(53956)
                    player:LearnSpell(54007)
                    player:LearnSpell(56531)
                    player:LearnSpell(53989)
                    player:LearnSpell(53953)
    end
     
    if (intid == 107) then -- Leatherworking
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 172)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51301)
                    player:LearnSpell(60640)
                    player:LearnSpell(60637)
                    player:LearnSpell(50965)
                    player:LearnSpell(50967)
                    player:LearnSpell(60643)
                    player:LearnSpell(60583)
                    player:LearnSpell(57683)
                    player:LearnSpell(57691)
                    player:LearnSpell(57690)
    end
     
    if (intid == 108) then -- Mining

                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 174)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(50309)
    end
     
    if (intid == 109) then -- Skinning
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 176)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    -------------------------
                    player:LearnSpell(50307)
    end
     
    if (intid == 110) then -- Tailoring
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 178)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51308)
                    player:LearnSpell(56026)
                    player:LearnSpell(56024)
                    player:LearnSpell(56028)
                    player:LearnSpell(56027)
                    player:LearnSpell(56025)
                    player:LearnSpell(56029)
                    player:LearnSpell(60993)
                    player:LearnSpell(60971)
                    player:LearnSpell(60994)
                    player:LearnSpell(60990)
                    player:LearnSpell(55769)
                    player:LearnSpell(55642)
                    player:LearnSpell(55777)
                    player:LearnSpell(56002)
                    player:LearnSpell(56001)
                    player:LearnSpell(56003)
                    player:LearnSpell(56007)
                    player:LearnSpell(60969)
    end
     
     
    if (intid == 111) then -- Secondary Professions
            player:GossipMenuAddItem(5, "Cooking", 0, 179)
            player:GossipMenuAddItem(5, "First Aid", 0, 180)
            player:GossipMenuAddItem(5, "Fishing", 0, 181)
            player:GossipMenuAddItem(0, "Previous Page", 0, 17)
            player:GossipMenuAddItem(0, "Home Page", 0, 999)
            player:GossipSendMenu(1, item)
    end
     
     
    -- Eastern Kingdoms
     
    if (intid == 112) then -- Alterac Mountains
            player:Teleport(0, 353.79, -607.08, 150.76, 0)
            player:GossipComplete()
    end
     
    if (intid == 113) then -- Arathi Highlands
            player:Teleport(0, -2269.78, -2501.06, 79.04, 0)
            player:GossipComplete()
    end
     
    if (intid == 114) then -- Badlands
            player:Teleport(0, -6026.58, -3318.27, 260.64, 0)
            player:GossipComplete()
    end
     
    if (intid == 115) then -- Blasted Lands
            player:Teleport(0, -10797.67, -2994.29, 44.42, 0)
            player:GossipComplete()
    end
     
    if (intid == 116) then -- Burning Steppes
            player:Teleport(0, -8357.72, -2537.49, 135.01, 0)
            player:GossipComplete()
    end
     
    if (intid == 117) then -- Deadwind Pass
            player:Teleport(0, -10460.22, -1699.33, 81.85, 0)
            player:GossipComplete()
    end
     
    if (intid == 118) then -- Dun Morogh
            player:Teleport(0, -6234.99, 341.24, 383.22, 0)
            player:GossipComplete()
    end
     
    if (intid == 119) then -- Duskwood
            player:Teleport(0, -10068.30, -1501.07, 28.41, 0)
            player:GossipComplete()
    end
     
    if (intid == 120) then -- Eastern Plaguelands
            player:Teleport(0, 1924.70, -2653.54, 59.70, 0)
            player:GossipComplete()
    end
     
    if (intid == 121) then -- Elwynn Forest
            player:Teleport(0, -8939.71, -131.22, 83.62, 0)
            player:GossipComplete()
    end
     
    if (intid == 122) then -- Eversong Woods
            player:Teleport(530, 10341.73, -6366.29, 34.31, 0)
            player:GossipComplete()
    end
     
    if (intid == 123) then -- Ghostlands
            player:Teleport(530, 7969.87, -6872.63, 58.66, 0)
            player:GossipComplete()
    end
     
    if (intid == 124) then -- Hillsbrad Foothills
            player:Teleport(0, -585.70, 612.18, 83.80, 0)
            player:GossipComplete()
    end
     
    if (intid == 125) then -- Isle of Quel'Danas
            player:Teleport(530, 12916.81, -6867.82, 7.69, 0)
            player:GossipComplete()
    end
     
    if (intid == 126) then -- Loch Modan
            player:Teleport(0, -4702.59, -2698.61, 318.75, 0)
            player:GossipComplete()
    end
     
    if (intid == 127) then -- Redridge Mountains
            player:Teleport(0, -9600.62, -2123.21, 66.23, 0)
            player:GossipComplete()
    end
     
    if (intid == 128) then -- Searing Gorge
            player:Teleport(0, -6897.73, -1821.58, 241.16, 0)
            player:GossipComplete()
    end
     
    if (intid == 129) then -- Silverpine Forest
            player:Teleport(0, 1499.57, 623.98, 47.01, 0)
            player:GossipComplete()
    end
     
    if (intid == 130) then -- Stranglethorn Vale
            player:Teleport(0, -11355.90, -383.40, 65.14, 0)
            player:GossipComplete()
    end
     
    if (intid == 131) then -- Swamp of Sorrows
            player:Teleport(0, -10552.60, -2355.25, 85.95, 0)
            player:GossipComplete()
    end
     
    if (intid == 132) then -- The Hinterlands
            player:Teleport(0, 92.63, -1942.31, 154.11, 0)
            player:GossipComplete()
    end
     
    if (intid == 133) then -- Tirisfal Glades
            player:Teleport(0, 1676.13, 1669.37, 137.02, 0)
            player:GossipComplete()
    end
     
    if (intid == 134) then -- Western Plaguelands
            player:Teleport(0, 1635.57, -1068.50, 66.57, 0)
            player:GossipComplete()
    end
     
    if (intid == 135) then -- Westfall
            player:Teleport(0, -9827.95, 865.80, 25.80, 0)
            player:GossipComplete()
    end
     
    if (intid == 136) then -- Wetlands
            player:Teleport(0, -4086.32, -2620.72, 43.55, 0)
            player:GossipComplete()
    end
     
     
    -- Kalimdor
     
    if (intid == 137) then -- Ashenvale
            player:Teleport(1, 3474.41, 853.47, 5.76, 0)
            player:GossipComplete()
    end
     
    if (intid == 138) then -- Azshara
            player:Teleport(1, 2763.93, -3881.34, 92.52, 0)
            player:GossipComplete()
    end
     
    if (intid == 139) then -- Azuremyst Isle
            player:Teleport(530, -3972.72, -13914.99, 98.88, 0)
            player:GossipComplete()
    end
     
    if (intid == 140) then -- Bloodmyst Isle
            player:Teleport(530, -2721.67, -12208.90, 9.08, 0)
            player:GossipComplete()
    end
     
    if (intid == 141) then -- Darkshore
            player:Teleport(1, 4336.61, 173.83, 46.84, 0)
            player:GossipComplete()
    end
     
    if (intid == 142) then -- Desolace
            player:Teleport(1, 47.28, 1684.64, 93.55, 0)
            player:GossipComplete()
    end
     
    if (intid == 143) then -- Durotar
            player:Teleport(1, -611.61, -4263.16, 38.95, 0)
            player:GossipComplete()
    end
     
    if (intid == 144) then -- Dustwallow Marsh
            player:Teleport(1, -3682.58, -2556.93, 58.43, 0)
            player:GossipComplete()
    end
     
    if (intid == 145) then -- Felwood
            player:Teleport(1, 3590.56, -1516.69, 169.98, 0)
            player:GossipComplete()
    end
     
    if (intid == 146) then -- Feralas
            player:Teleport(1, -4300.02, -631.56, -9.35, 0)
            player:GossipComplete()
    end
     
    if (intid == 147) then -- Moonglade
            player:Teleport(1, 7999.68, -2670.19, 512.09, 0)
            player:GossipComplete()
    end
     
    if (intid == 148) then -- Mulgore
            player:Teleport(1, -2931.49, -262.82, 53.25, 0)
            player:GossipComplete()
    end
     
    if (intid == 149) then -- Silithus
            player:Teleport(1, -6814.57, 833.77, 49.74, 0)
            player:GossipComplete()
    end
     
    if (intid == 150) then -- Stonetalon Mountains
            player:Teleport(1, -225.34, -765.16, 6.4, 0)
            player:GossipComplete()
    end
     
    if (intid == 151) then -- Tanaris
            player:Teleport(1, -6999.47, -3707.94, 26.44, 0)
            player:GossipComplete()
    end
     
    if (intid == 152) then -- Teldrassil
            player:Teleport(1, 8754.06, 949.62, 25.99, 0)
            player:GossipComplete()
    end
     
    if (intid == 153) then -- The Barrens
            player:Teleport(1, -948.46, -3738.60, 5.98, 0)
            player:GossipComplete()
    end
     
    if (intid == 154) then -- Thousand Needles
            player:Teleport(1, -4685.72, -1836.24, -44.04, 0)
            player:GossipComplete()
    end
     
    if (intid == 155) then -- Un'Goro Crater
            player:Teleport(1, -6162.47, -1098.74, -208.99, 0)
            player:GossipComplete()
    end
     
    if (intid == 156) then -- Winterspring
            player:Teleport(1, 6896.27, -2302.51, 586.69, 0)
            player:GossipComplete()
    end
     
     
    -- Profession Trainers
     
    if (intid == 157) then -- Alchemy
     
            player:GossipComplete()
    end
     
    if (intid == 158) then -- Unlearn ^^
            player:RemoveSpell(51303)
            player:RemoveSpell(51304)
            player:RemoveSpell(53042)
            player:GossipComplete()
    end
     
    if (intid == 159) then -- Blacksmithing
     
            player:GossipComplete()
    end
     
    if (intid == 160) then -- Unlearn ^^
            player:RemoveSpell(51298)
            player:RemoveSpell(51300)
            player:GossipComplete()
    end
     
    if (intid == 161) then -- Enchanting
           
            player:GossipComplete()
    end
     
    if (intid == 162) then -- Unlearn ^^
            player:RemoveSpell(51312)
            player:RemoveSpell(51313)
            player:GossipComplete()
    end
     
    if (intid == 163) then -- Engineering
     
            player:GossipComplete()
    end
     
    if (intid == 164) then -- Unlearn ^^
            player:RemoveSpell(51305)
            player:RemoveSpell(51306)
            player:GossipComplete()
    end
     
    if (intid == 165) then -- Herbalism
     
            player:GossipComplete()
    end
     
    if (intid == 166) then -- Unlearn Herbalism
            player:RemoveSpell(50300)
            player:RemoveSpell(50301)
            player:GossipComplete()
    end
     
    if (intid == 167) then -- Inscription
     
            player:GossipComplete()
    end
     
    if (intid == 168) then -- Unlearn ^^
            player:RemoveSpell(45363)
            player:RemoveSpell(45380)
            player:GossipComplete()
    end
     
    if (intid == 169) then -- Jewelcrafting
     
            player:GossipComplete()
    end
     
    if (intid == 170) then -- Unlearn ^^
            player:RemoveSpell(51310)
            player:RemoveSpell(51311)
            player:GossipComplete()
    end
     
    if (intid == 171) then -- Leatherworking
     
            player:GossipComplete()
    end
     
    if (intid == 172) then -- Unlearn ^^
            player:RemoveSpell(51301)
            player:RemoveSpell(51302)
            player:GossipComplete()
    end
     
    if (intid == 173) then -- Mining
     
            player:GossipComplete()
    end
     
    if (intid == 174) then -- Unlearn ^^
            player:RemoveSpell(50309)
            player:RemoveSpell(50310)
            player:GossipComplete()
    end
     
    if (intid == 175) then -- Skinning
     
            player:GossipComplete()
    end
     
    if (intid == 176) then -- Unlearn ^^
            player:RemoveSpell(50305)
            player:RemoveSpell(50306)
            player:GossipComplete()
    end
     
    if (intid == 177) then -- Tailoring
     
            player:GossipComplete()
    end
     
    if (intid == 178) then -- Unlearn ^^
            player:RemoveSpell(51308)
            player:RemoveSpell(51309)
            player:GossipComplete()
    end
     
     
     
    -- Secondary Professions
     
    if (intid == 179) then -- Cooking
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 183)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51295)
    end
     
    if (intid == 180) then -- First Aid
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 185)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(50299)
    end
     
    if (intid == 181) then -- Fishing
     
                    player:GossipMenuAddItem(0, "I'd like to unlearn this profession.", 0, 187)
                    player:GossipMenuAddItem(0, "Home Page", 0, 999)
                    player:GossipSendMenu(1, item)
                    ------------------------
                    player:LearnSpell(51293)
    end
     
     
    -- Secondary Profession Trainers
     
    if (intid == 182) then -- Cooking
     
            player:GossipComplete()
    end
     
    if (intid == 183) then -- Unlearn ^^
            player:RemoveSpell(51296)
            player:RemoveSpell(51295)
            player:GossipComplete()
    end
     
    if (intid == 184) then -- First Aid
     
            player:GossipComplete()
    end
     
    if (intid == 185) then -- Unlearn ^^
            player:RemoveSpell(50299)
            player:RemoveSpell(45442)
            player:GossipComplete()
    end
     
    if (intid == 186) then -- Fishing
     
            player:GossipComplete()
    end
     
    if (intid == 187) then -- Unlearn ^^
            player:RemoveSpell(51294)
            player:RemoveSpell(51293)
            player:GossipComplete()
    end
     
     
    -- Foothills
     
    if(intid == 9997) then
            if (plyr == 1) or (plyr == 3) or (plyr == 4) or (plyr == 7) or (plyr == 11) then
                    player:GossipMenuAddItem(2, "Qurantis", 0, 1235)
                    player:GossipSendMenu(1, item)
            end
     
            if (plyr == 2) or (plyr == 5) or (plyr == 6) or (plyr == 8) or (plyr == 10) then
                    player:GossipMenuAddItem(2, "Mulderan", 0, 1236)
                    player:GossipSendMenu(1, item)
            end
    end
     
    if(intid == 1235) then -- Qurantis
            player:Teleport(560, 3611.490723, 2288.865967, 59.283901, 0)
    end
     
    if(intid == 1236) then -- Mulderan
            player:Teleport(560, 2539.483643, 2423.052734, 63.581509, 0)
    end
     
     
     
    if (intid == 999) then -- Main page
    --player:GossipMenuAddItem(5, "|cffff6060TELEPORTER STONE.|r", 0, 998)
    player:GossipMenuAddItem(6, "|cFF191970Main Cities|r", 0, 1)
    player:GossipMenuAddItem(2, "|cFF191970Azeroth Locations|r", 0, 2)
    player:GossipMenuAddItem(2, "|cFF191970Azeroth Instances|r", 0, 3)
    player:GossipMenuAddItem(2, "|cFF191970Azeroth Raids|r", 0, 4)
    player:GossipMenuAddItem(2, "|cFF191970Outland Locations|r", 0, 5)
    player:GossipMenuAddItem(2, "|cFF191970Outland Instances|r", 0, 6)
    player:GossipMenuAddItem(2, "|cFF191970Outland Raids|r", 0, 7)
    player:GossipMenuAddItem(2, "|cFF191970Northrend Locations|r", 0, 8)
    player:GossipMenuAddItem(2, "|cFF191970Northrend Instances|r", 0, 9)
    player:GossipMenuAddItem(2, "|cFF191970Northrend Raids|r", 0, 10)
    player:GossipMenuAddItem(0, "|cFF191970Foothills|r", 0, 9997)
    player:GossipMenuAddItem(5, "|cFF191970Murloc Mall|r", 0, 12)
    player:GossipMenuAddItem(9, "|cFF191970Gurubashi Arena|r", 0, 13)
    player:GossipMenuAddItem(0, "|cFF191970Next Page|r", 0, 997)
    player:GossipSendMenu(1, item)
    end
    end
     
    RegisterItemGossipEvent(6948, 1, Tele_Book)
    RegisterItemGossipEvent(6948, 2, Tele_Select)

