/* Worgen */
UPDATE item_template SET allowablerace = allowablerace + 2048 WHERE NOT allowablerace & 2048 AND allowablerace & 1 AND allowablerace != -1 AND allowablerace != 2147483647 AND allowablerace != 2047 AND allowablerace != 4095 AND allowablerace != 8191 AND allowablerace != 16383 AND allowablerace != 32767 AND allowablerace != 65535 AND allowablerace != 131071 AND allowablerace != 262143 AND allowablerace != 524287 AND allowablerace != 1048575 AND allowablerace != 2097151;

/* Goblin */
UPDATE item_template SET allowablerace = allowablerace + 256 WHERE NOT allowablerace & 256 AND allowablerace & 2 AND allowablerace != -1 AND allowablerace != 2147483647 AND allowablerace != 2047 AND allowablerace != 4095 AND allowablerace != 8191 AND allowablerace != 16383 AND allowablerace != 32767 AND allowablerace != 65535 AND allowablerace != 131071 AND allowablerace != 262143 AND allowablerace != 524287 AND allowablerace != 1048575 AND allowablerace != 2097151;
