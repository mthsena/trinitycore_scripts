/* Worgen */
UPDATE quest_template SET requiredraces = requiredraces + 2048 WHERE NOT requiredraces & 2048 AND requiredraces & 1 AND requiredraces != -1 AND requiredraces != 2147483647 AND requiredraces != 2047 AND requiredraces != 4095 AND requiredraces != 8191 AND requiredraces != 16383 AND requiredraces != 32767 AND requiredraces != 65535 AND requiredraces != 131071 AND requiredraces != 262143 AND requiredraces != 524287 AND requiredraces != 1048575 AND requiredraces != 2097151;

/* Goblin */
UPDATE quest_template SET requiredraces = requiredraces + 256 WHERE NOT requiredraces & 256 AND requiredraces & 2 AND requiredraces != -1 AND requiredraces != 2147483647 AND requiredraces != 2047 AND requiredraces != 4095 AND requiredraces != 8191 AND requiredraces != 16383 AND requiredraces != 32767 AND requiredraces != 65535 AND requiredraces != 131071 AND requiredraces != 262143 AND requiredraces != 524287 AND requiredraces != 1048575 AND requiredraces != 2097151;
