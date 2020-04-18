#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"

using namespace std;

#define DEFAULT_MESSAGE 907
#define TELE_COST 0

struct TeleData
{
    uint32 menu_id;
    uint32 next_menu_id;
    uint8 icon;
    string name;
    uint32 cost;
    Team faction;
    uint32 map;
    double x, y, z, o;
};

TeleData tData[] =
{
    // menu_id, next_menu_id, icon, name, cost, faction, map, x, y, z, o
    { 1, 0, GOSSIP_ICON_TAXI, "Stormwind", TELE_COST, ALLIANCE, 0, -8842.09, 626.358, 94.0867, 3.61363 },
    { 1, 0, GOSSIP_ICON_TAXI, "Orgrimmar", TELE_COST, HORDE, 1, 1601.08, -4378.69, 9.9846, 2.14362 },
    { 1, 0, GOSSIP_ICON_TAXI, "Darnassus", TELE_COST, ALLIANCE, 1, 9869.91, 2493.58, 1315.88, 2.78897 },
    { 1, 0, GOSSIP_ICON_TAXI, "Ironforge", TELE_COST, ALLIANCE, 0, -4900.47, -962.585, 501.455, 5.40538 },
    { 1, 0, GOSSIP_ICON_TAXI, "Exodar", TELE_COST, ALLIANCE, 530, -3864.92, -11643.7, -137.644, 5.50862 },
    { 1, 0, GOSSIP_ICON_TAXI, "Thunder bluff", TELE_COST, HORDE, 1, -1274.45, 71.8601, 128.159, 2.80623 },
    { 1, 0, GOSSIP_ICON_TAXI, "Undercity", TELE_COST, HORDE, 0, 1633.75, 240.167, -43.1034, 6.26128 },
    { 1, 0, GOSSIP_ICON_TAXI, "Silvermoon city", TELE_COST, HORDE, 530, 9738.28, -7454.19, 13.5605, 0.043914 },
    { 1, 0, GOSSIP_ICON_TAXI, "Dalaran", TELE_COST, TEAM_OTHER, 571, 5809.55, 503.975, 657.526, 2.38338 },
    { 1, 0, GOSSIP_ICON_TAXI, "Shattrath", TELE_COST, TEAM_OTHER, 530, -1887.62, 5359.09, -12.4279, 4.40435 },
    { 1, 0, GOSSIP_ICON_TAXI, "Booty bay", TELE_COST, TEAM_OTHER, 0, -14281.9, 552.564, 8.90422, 0.860144 },
    { 1, 0, GOSSIP_ICON_TAXI, "Gurubashi arena", TELE_COST, TEAM_OTHER, 0, -13181.8, 339.356, 42.9805, 1.18013 },
    { 1, 2, GOSSIP_ICON_CHAT, "Eastern Kingdoms", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 3, GOSSIP_ICON_CHAT, "Kalimdor", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 4, GOSSIP_ICON_CHAT, "Outland", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 5, GOSSIP_ICON_CHAT, "Northrend", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 6, GOSSIP_ICON_CHAT, "Classic Dungeons", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 7, GOSSIP_ICON_CHAT, "Tbc Dungeons", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 8, GOSSIP_ICON_CHAT, "Wotlk Dungeons", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
    { 1, 9, GOSSIP_ICON_CHAT, "Raid Locations", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 2, 0, GOSSIP_ICON_TAXI, "Elwynn Forest", TELE_COST, ALLIANCE, 0, -9449.06, 64.8392, 56.3581, 3.07047 },
    { 2, 0, GOSSIP_ICON_TAXI, "Eversong Woods", TELE_COST, HORDE, 530, 9024.37, -6682.55, 16.8973, 3.14131 },
    { 2, 0, GOSSIP_ICON_TAXI, "Dun Morogh", TELE_COST, ALLIANCE, 0, -5603.76, -482.704, 396.98, 5.23499 },
    { 2, 0, GOSSIP_ICON_TAXI, "Tirisfal Glades", TELE_COST, HORDE, 0, 2274.95, 323.918, 34.1137, 4.24367 },
    { 2, 0, GOSSIP_ICON_TAXI, "Ghostlands", TELE_COST, HORDE, 530, 7595.73, -6819.6, 84.3718, 2.56561 },
    { 2, 0, GOSSIP_ICON_TAXI, "Loch modan", TELE_COST, ALLIANCE, 0, -5405.85, -2894.15, 341.972, 5.48238 },
    { 2, 0, GOSSIP_ICON_TAXI, "Silverpine Forest", TELE_COST, HORDE, 0, 505.126, 1504.63, 124.808, 1.77987 },
    { 2, 0, GOSSIP_ICON_TAXI, "Westfall", TELE_COST, ALLIANCE, 0, -10684.9, 1033.63, 32.5389, 6.07384 },
    { 2, 0, GOSSIP_ICON_TAXI, "Redridge mountains", TELE_COST, ALLIANCE, 0, -9447.8, -2270.85, 71.8224, 0.283853 },
    { 2, 0, GOSSIP_ICON_TAXI, "Duskwood", TELE_COST, ALLIANCE, 0, -10531.7, -1281.91, 38.8647, 1.56959 },
    { 2, 0, GOSSIP_ICON_TAXI, "Hillsbrad Foothills", TELE_COST, TEAM_OTHER, 0, -385.805, -787.954, 54.6655, 1.03926 },
    { 2, 0, GOSSIP_ICON_TAXI, "Wetlands", TELE_COST, ALLIANCE, 0, -3517.75, -913.401, 8.86625, 2.60705 },
    { 2, 0, GOSSIP_ICON_TAXI, "Alterac Mountains", TELE_COST, TEAM_OTHER, 0, 275.049, -652.044, 130.296, 0.502032 },
    { 2, 0, GOSSIP_ICON_TAXI, "Arathi Highlands", TELE_COST, TEAM_OTHER, 0, -1581.45, -2704.06, 35.4168, 0.490373 },
    { 2, 0, GOSSIP_ICON_TAXI, "Stranglethorn Vale", TELE_COST, TEAM_OTHER, 0, -11921.7, -59.544, 39.7262, 3.73574 },
    { 2, 0, GOSSIP_ICON_TAXI, "Badlands", TELE_COST, TEAM_OTHER, 0, -6782.56, -3128.14, 240.48, 5.65912 },
    { 2, 0, GOSSIP_ICON_TAXI, "Swamp of Sorrows", TELE_COST, TEAM_OTHER, 0, -10368.6, -2731.3, 21.6537, 5.29238 },
    { 2, 0, GOSSIP_ICON_TAXI, "The Hinterlands", TELE_COST, TEAM_OTHER, 0, 112.406, -3929.74, 136.358, 0.981903 },
    { 2, 0, GOSSIP_ICON_TAXI, "Searing Gorge", TELE_COST, TEAM_OTHER, 0, -6686.33, -1198.55, 240.027, 0.916887 },
    { 2, 0, GOSSIP_ICON_TAXI, "The Blasted Lands", TELE_COST, TEAM_OTHER, 0, -11184.7, -3019.31, 7.29238, 3.20542 },
    { 2, 0, GOSSIP_ICON_TAXI, "Burning Steppes", TELE_COST, TEAM_OTHER, 0, -7979.78, -2105.72, 127.919, 5.10148 },
    { 2, 0, GOSSIP_ICON_TAXI, "Western Plaguelands", TELE_COST, TEAM_OTHER, 0, 1743.69, -1723.86, 59.6648, 5.23722 },
    { 2, 0, GOSSIP_ICON_TAXI, "Eastern Plaguelands", TELE_COST, TEAM_OTHER, 0, 2280.64, -5275.05, 82.0166, 4.7479 },
    { 2, 0, GOSSIP_ICON_TAXI, "Isle of Quel'Danas", TELE_COST, TEAM_OTHER, 530, 12806.5, -6911.11, 41.1156, 2.22935 },
    { 2, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 3, 0, GOSSIP_ICON_TAXI, "Azuremyst Isle", TELE_COST, ALLIANCE, 530, -4192.62, -12576.7, 36.7598, 1.62813 },
    { 3, 0, GOSSIP_ICON_TAXI, "Teldrassil", TELE_COST, ALLIANCE, 1, 9889.03, 915.869, 1307.43, 1.9336 },
    { 3, 0, GOSSIP_ICON_TAXI, "Durotar", TELE_COST, HORDE, 1, 228.978, -4741.87, 10.1027, 0.416883 },
    { 3, 0, GOSSIP_ICON_TAXI, "Mulgore", TELE_COST, HORDE, 1, -2473.87, -501.225, -9.42465, 0.6525 },
    { 3, 0, GOSSIP_ICON_TAXI, "Bloodmyst Isle", TELE_COST, ALLIANCE, 530, -2095.7, -11841.1, 51.1557, 6.19288 },
    { 3, 0, GOSSIP_ICON_TAXI, "Darkshore", TELE_COST, ALLIANCE, 1, 6463.25, 683.986, 8.92792, 4.33534 },
    { 3, 0, GOSSIP_ICON_TAXI, "The Barrens", TELE_COST, HORDE, 1, -575.772, -2652.45, 95.6384, 0.006469 },
    { 3, 0, GOSSIP_ICON_TAXI, "Stonetalon Mountains", TELE_COST, TEAM_OTHER, 1, 1574.89, 1031.57, 137.442, 3.8013 },
    { 3, 0, GOSSIP_ICON_TAXI, "Ashenvale Forest", TELE_COST, TEAM_OTHER, 1, 1919.77, -2169.68, 94.6729, 6.14177 },
    { 3, 0, GOSSIP_ICON_TAXI, "Thousand Needles", TELE_COST, HORDE, 1, -5375.53, -2509.2, -40.432, 2.41885 },
    { 3, 0, GOSSIP_ICON_TAXI, "Desolace", TELE_COST, TEAM_OTHER, 1, -656.056, 1510.12, 88.3746, 3.29553 },
    { 3, 0, GOSSIP_ICON_TAXI, "Dustwallow Marsh", TELE_COST, TEAM_OTHER, 1, -3350.12, -3064.85, 33.0364, 5.12666 },
    { 3, 0, GOSSIP_ICON_TAXI, "Feralas", TELE_COST, TEAM_OTHER, 1, -4808.31, 1040.51, 103.769, 2.90655 },
    { 3, 0, GOSSIP_ICON_TAXI, "Tanaris Desert", TELE_COST, TEAM_OTHER, 1, -6940.91, -3725.7, 48.9381, 3.11174 },
    { 3, 0, GOSSIP_ICON_TAXI, "Azshara", TELE_COST, TEAM_OTHER, 1, 3117.12, -4387.97, 91.9059, 5.49897 },
    { 3, 0, GOSSIP_ICON_TAXI, "Felwood", TELE_COST, TEAM_OTHER, 1, 3898.8, -1283.33, 220.519, 6.24307 },
    { 3, 0, GOSSIP_ICON_TAXI, "Un'Goro Crater", TELE_COST, TEAM_OTHER, 1, -6291.55, -1158.62, -258.138, 0.457099 },
    { 3, 0, GOSSIP_ICON_TAXI, "Silithus", TELE_COST, TEAM_OTHER, 1, -6815.25, 730.015, 40.9483, 2.39066 },
    { 3, 0, GOSSIP_ICON_TAXI, "Winterspring", TELE_COST, TEAM_OTHER, 1, 6658.57, -4553.48, 718.019, 5.18088 },
    { 3, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 4, 0, GOSSIP_ICON_TAXI, "Hellfire Peninsula", TELE_COST, TEAM_OTHER, 530, -207.335, 2035.92, 96.464, 1.59676 },
    { 4, 0, GOSSIP_ICON_TAXI, "Zangarmarsh", TELE_COST, TEAM_OTHER, 530, -220.297, 5378.58, 23.3223, 1.61718 },
    { 4, 0, GOSSIP_ICON_TAXI, "Terokkar Forest", TELE_COST, TEAM_OTHER, 530, -2266.23, 4244.73, 1.47728, 3.68426 },
    { 4, 0, GOSSIP_ICON_TAXI, "Nagrand", TELE_COST, TEAM_OTHER, 530, -1610.85, 7733.62, -17.2773, 1.33522 },
    { 4, 0, GOSSIP_ICON_TAXI, "Blade's Edge Mountains", TELE_COST, TEAM_OTHER, 530, 2029.75, 6232.07, 133.495, 1.30395 },
    { 4, 0, GOSSIP_ICON_TAXI, "Netherstorm", TELE_COST, TEAM_OTHER, 530, 3271.2, 3811.61, 143.153, 3.44101 },
    { 4, 0, GOSSIP_ICON_TAXI, "Shadowmoon Valley", TELE_COST, TEAM_OTHER, 530, -3681.01, 2350.76, 76.587, 4.25995 },
    { 4, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 5, 0, GOSSIP_ICON_TAXI, "Borean Tundra", TELE_COST, TEAM_OTHER, 571, 2954.24, 5379.13, 60.4538, 2.55544 },
    { 5, 0, GOSSIP_ICON_TAXI, "Howling Fjord", TELE_COST, TEAM_OTHER, 571, 682.848, -3978.3, 230.161, 1.54207 },
    { 5, 0, GOSSIP_ICON_TAXI, "Dragonblight", TELE_COST, TEAM_OTHER, 571, 2678.17, 891.826, 4.37494, 0.101121 },
    { 5, 0, GOSSIP_ICON_TAXI, "Grizzly Hills", TELE_COST, TEAM_OTHER, 571, 4017.35, -3403.85, 290, 5.35431 },
    { 5, 0, GOSSIP_ICON_TAXI, "Zul'Drak", TELE_COST, TEAM_OTHER, 571, 5560.23, -3211.66, 371.709, 5.55055 },
    { 5, 0, GOSSIP_ICON_TAXI, "Sholazar Basin", TELE_COST, TEAM_OTHER, 571, 5614.67, 5818.86, -69.722, 3.60807 },
    { 5, 0, GOSSIP_ICON_TAXI, "Crystalsong Forest", TELE_COST, TEAM_OTHER, 571, 5411.17, -966.37, 167.082, 1.57167 },
    { 5, 0, GOSSIP_ICON_TAXI, "Storm Peaks", TELE_COST, TEAM_OTHER, 571, 6120.46, -1013.89, 408.39, 5.12322 },
    { 5, 0, GOSSIP_ICON_TAXI, "Icecrown", TELE_COST, TEAM_OTHER, 571, 8323.28, 2763.5, 655.093, 2.87223 },
    { 5, 0, GOSSIP_ICON_TAXI, "Wintergrasp", TELE_COST, TEAM_OTHER, 571, 4522.23, 2828.01, 389.975, 0.215009 },
    { 5, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 6, 0, GOSSIP_ICON_TAXI, "Gnomeregan", TELE_COST, ALLIANCE, 0, -5163.54, 925.423, 257.181, 1.57423 },
    { 6, 0, GOSSIP_ICON_TAXI, "The Deadmines", TELE_COST, ALLIANCE, 0, -11209.6, 1666.54, 24.6974, 1.42053 },
    { 6, 0, GOSSIP_ICON_TAXI, "The Stockade", TELE_COST, ALLIANCE, 0, -8799.15, 832.718, 97.6348, 6.04085 },
    { 6, 0, GOSSIP_ICON_TAXI, "Ragefire Chasm", TELE_COST, HORDE, 1, 1811.78, -4410.5, -18.4704, 5.20165 },
    { 6, 0, GOSSIP_ICON_TAXI, "Razorfen Downs", TELE_COST, HORDE, 1, -4657.3, -2519.35, 81.0529, 4.54808 },
    { 6, 0, GOSSIP_ICON_TAXI, "Razorfen Kraul", TELE_COST, HORDE, 1, -4470.28, -1677.77, 81.3925, 1.16302 },
    { 6, 0, GOSSIP_ICON_TAXI, "Scarlet Monastery", TELE_COST, HORDE, 0, 2873.15, -764.523, 160.332, 5.10447 },
    { 6, 0, GOSSIP_ICON_TAXI, "Shadowfang Keep", TELE_COST, HORDE, 0, -234.675, 1561.63, 76.8921, 1.24031 },
    { 6, 0, GOSSIP_ICON_TAXI, "Wailing Caverns", TELE_COST, HORDE, 1, -731.607, -2218.39, 17.0281, 2.78486 },
    { 6, 0, GOSSIP_ICON_TAXI, "Blackfathom Deeps", TELE_COST, TEAM_OTHER, 1, 4249.99, 740.102, -25.671, 1.34062 },
    { 6, 0, GOSSIP_ICON_TAXI, "Blackrock Depths", TELE_COST, TEAM_OTHER, 0, -7179.34, -921.212, 165.821, 5.09599 },
    { 6, 0, GOSSIP_ICON_TAXI, "Blackrock Spire", TELE_COST, TEAM_OTHER, 0, -7527.05, -1226.77, 285.732, 5.29626 },
    { 6, 0, GOSSIP_ICON_TAXI, "Dire Maul", TELE_COST, TEAM_OTHER, 1, -3520.14, 1119.38, 161.025, 4.70454 },
    { 6, 0, GOSSIP_ICON_TAXI, "Maraudon", TELE_COST, TEAM_OTHER, 1, -1421.42, 2907.83, 137.415, 1.70718 },
    { 6, 0, GOSSIP_ICON_TAXI, "Scholomance", TELE_COST, TEAM_OTHER, 0, 1269.64, -2556.21, 93.6088, 0.620623 },
    { 6, 0, GOSSIP_ICON_TAXI, "Stratholme", TELE_COST, TEAM_OTHER, 0, 3352.92, -3379.03, 144.782, 6.25978 },
    { 6, 0, GOSSIP_ICON_TAXI, "Sunken Temple", TELE_COST, TEAM_OTHER, 0, -10177.9, -3994.9, -111.239, 6.01885 },
    { 6, 0, GOSSIP_ICON_TAXI, "Uldaman", TELE_COST, TEAM_OTHER, 0, -6071.37, -2955.16, 209.782, 0.015708 },
    { 6, 0, GOSSIP_ICON_TAXI, "Zul'Farrak", TELE_COST, TEAM_OTHER, 1, -6801.19, -2893.02, 9.00388, 0.158639 },
    { 6, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 7, 0, GOSSIP_ICON_TAXI, "Auchindoun", TELE_COST, TEAM_OTHER, 530, -3324.49, 4943.45, -101.239, 4.63901 },
    { 7, 0, GOSSIP_ICON_TAXI, "Caverns of Time", TELE_COST, TEAM_OTHER, 1, -8369.65, -4253.11, -204.272, -2.70526 },
    { 7, 0, GOSSIP_ICON_TAXI, "Coilfang Reservoir", TELE_COST, TEAM_OTHER, 530, 738.865, 6865.77, -69.4659, 6.27655 },
    { 7, 0, GOSSIP_ICON_TAXI, "Hellfire Citadel", TELE_COST, TEAM_OTHER, 530, -347.29, 3089.82, 21.394, 5.68114 },
    { 7, 0, GOSSIP_ICON_TAXI, "Magisters' Terrace", TELE_COST, TEAM_OTHER, 530, 12884.6, -7317.69, 65.5023, 4.799 },
    { 7, 0, GOSSIP_ICON_TAXI, "Tempest Keep", TELE_COST, TEAM_OTHER, 530, 3100.48, 1536.49, 190.3, 4.62226 },
    { 7, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 8, 0, GOSSIP_ICON_TAXI, "Azjol-Nerub", TELE_COST, TEAM_OTHER, 571, 3707.86, 2150.23, 36.76, 3.22 },
    { 8, 0, GOSSIP_ICON_TAXI, "The Culling of Stratholme", TELE_COST, TEAM_OTHER, 1, -8756.39, -4440.68, -199.489, 4.66289 },
    { 8, 0, GOSSIP_ICON_TAXI, "Trial of the Champion", TELE_COST, TEAM_OTHER, 571, 8590.95, 791.792, 558.235, 3.13127 },
    { 8, 0, GOSSIP_ICON_TAXI, "Drak'Tharon Keep", TELE_COST, TEAM_OTHER, 571, 4765.59, -2038.24, 229.363, 0.887627 },
    { 8, 0, GOSSIP_ICON_TAXI, "Gundrak", TELE_COST, TEAM_OTHER, 571, 6722.44, -4640.67, 450.632, 3.91123 },
    { 8, 0, GOSSIP_ICON_TAXI, "Icecrown Citadel Dungeons", TELE_COST, TEAM_OTHER, 571, 5643.16, 2028.81, 798.274, 4.60242 },
    { 8, 0, GOSSIP_ICON_TAXI, "The Nexus Dungeons", TELE_COST, TEAM_OTHER, 571, 3782.89, 6965.23, 105.088, 6.14194 },
    { 8, 0, GOSSIP_ICON_TAXI, "The Violet Hold", TELE_COST, TEAM_OTHER, 571, 5693.08, 502.588, 652.672, 4.0229 },
    { 8, 0, GOSSIP_ICON_TAXI, "Halls of Lightning", TELE_COST, TEAM_OTHER, 571, 9136.52, -1311.81, 1066.29, 5.19113 },
    { 8, 0, GOSSIP_ICON_TAXI, "Halls of Stone", TELE_COST, TEAM_OTHER, 571, 8922.12, -1009.16, 1039.56, 1.57044 },
    { 8, 0, GOSSIP_ICON_TAXI, "Utgarde Keep", TELE_COST, TEAM_OTHER, 571, 1203.41, -4868.59, 41.2486, 0.283237 },
    { 8, 0, GOSSIP_ICON_TAXI, "Utgarde Pinnacle", TELE_COST, TEAM_OTHER, 571, 1267.24, -4857.3, 215.764, 3.22768 },
    { 8, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },

    { 9, 0, GOSSIP_ICON_TAXI, "Black Temple", TELE_COST, TEAM_OTHER, 530, -3649.92, 317.469, 35.2827, 2.94285 },
    { 9, 0, GOSSIP_ICON_TAXI, "Blackwing Lair", TELE_COST, TEAM_OTHER, 229, 152.451, -474.881, 116.84, 0.001073 },
    { 9, 0, GOSSIP_ICON_TAXI, "Hyjal Summit", TELE_COST, TEAM_OTHER, 1, -8177.89, -4181.23, -167.552, 0.913338 },
    { 9, 0, GOSSIP_ICON_TAXI, "Serpentshrine Cavern", TELE_COST, TEAM_OTHER, 530, 797.855, 6865.77, -65.4165, 0.005938 },
    { 9, 0, GOSSIP_ICON_TAXI, "Trial of the Crusader", TELE_COST, TEAM_OTHER, 571, 8515.61, 714.153, 558.248, 1.57753 },
    { 9, 0, GOSSIP_ICON_TAXI, "Gruul's Lair", TELE_COST, TEAM_OTHER, 530, 3530.06, 5104.08, 3.50861, 5.51117 },
    { 9, 0, GOSSIP_ICON_TAXI, "Magtheridon's Lair", TELE_COST, TEAM_OTHER, 530, -336.411, 3130.46, -102.928, 5.20322 },
    { 9, 0, GOSSIP_ICON_TAXI, "Icecrown Citadel", TELE_COST, TEAM_OTHER, 571, 5855.22, 2102.03, 635.991, 3.57899 },
    { 9, 0, GOSSIP_ICON_TAXI, "Karazhan", TELE_COST, TEAM_OTHER, 0, -11118.9, -2010.33, 47.0819, 0.649895 },
    { 9, 0, GOSSIP_ICON_TAXI, "Molten Core", TELE_COST, TEAM_OTHER, 230, 1126.64, -459.94, -102.535, 3.46095 },
    { 9, 0, GOSSIP_ICON_TAXI, "Naxxramas", TELE_COST, TEAM_OTHER, 571, 3668.72, -1262.46, 243.622, 4.785 },
    { 9, 0, GOSSIP_ICON_TAXI, "Onyxia's Lair", TELE_COST, TEAM_OTHER, 1, -4708.27, -3727.64, 54.5589, 3.72786 },
    { 9, 0, GOSSIP_ICON_TAXI, "Ruins of Ahn'Qiraj", TELE_COST, TEAM_OTHER, 1, -8409.82, 1499.06, 27.7179, 2.51868 },
    { 9, 0, GOSSIP_ICON_TAXI, "Sunwell Plateau", TELE_COST, TEAM_OTHER, 530, 12574.1, -6774.81, 15.0904, 3.13788 },
    { 9, 0, GOSSIP_ICON_TAXI, "The Eye", TELE_COST, TEAM_OTHER, 530, 3088.49, 1381.57, 184.863, 4.61973 },
    { 9, 0, GOSSIP_ICON_TAXI, "Temple of Ahn'Qiraj", TELE_COST, TEAM_OTHER, 1, -8240.09, 1991.32, 129.072, 0.941603 },
    { 9, 0, GOSSIP_ICON_TAXI, "The Eye of Eternity", TELE_COST, TEAM_OTHER, 571, 3784.17, 7028.84, 161.258, 5.79993 },
    { 9, 0, GOSSIP_ICON_TAXI, "The Obsidian Sanctum", TELE_COST, TEAM_OTHER, 571, 3472.43, 264.923, -120.146, 3.27923 },
    { 9, 0, GOSSIP_ICON_TAXI, "Ulduar", TELE_COST, TEAM_OTHER, 571, 9222.88, -1113.59, 1216.12, 6.27549 },
    { 9, 0, GOSSIP_ICON_TAXI, "Vault of Archavon", TELE_COST, TEAM_OTHER, 571, 5453.72, 2840.79, 421.28, 0 },
    { 9, 0, GOSSIP_ICON_TAXI, "Zul'Gurub", TELE_COST, TEAM_OTHER, 0, -11916.7, -1215.72, 92.289, 4.72454 },
    { 9, 0, GOSSIP_ICON_TAXI, "Zul'Aman", TELE_COST, HORDE, 530, 6851.78, -7972.57, 179.242, 4.64691 },
    { 9, 1, GOSSIP_ICON_TALK, "Back..", TELE_COST, TEAM_OTHER, 0, 0, 0, 0, 0 },
};

bool CheckTeam(Player* player, uint8 key)
{
    if (tData[key].faction == TEAM_OTHER || tData[key].faction == player->GetTeam())
        return true;
    else
        return false;
}

class NPC_Teleport : public CreatureScript
{
public:
    NPC_Teleport() : CreatureScript("NPC_Teleport") { }

    void GetMenu(Player* player, Creature* creature, uint32 menuId)
    {
        for (uint8 i = 0; i < (sizeof(tData) / sizeof(*tData)); i++)
        {
            if (!CheckTeam(player, i))
                continue;

            if (tData[i].menu_id == menuId)
                AddGossipItemFor(player, tData[i].icon, tData[i].name, GOSSIP_SENDER_MAIN, i);
        }

        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        GetMenu(player, creature, 1);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        uint32 menuData = tData[action].next_menu_id;

        if (menuData == 0)
        {
            player->TeleportTo(tData[action].map, tData[action].x, tData[action].y, tData[action].z, tData[action].o);
            ChatHandler(player->GetSession()).PSendSysMessage("Success! You was teleported.");
            menuData = tData[action].menu_id;
        }

        GetMenu(player, creature, menuData);
        return true;
    }
};

void AddSC_NPC_Teleport()
{
    new NPC_Teleport();
}