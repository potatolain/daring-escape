#include "source/configuration/system_constants.h"
#include "source/neslib_asm/neslib.h"
#include "source/library/bank_helpers.h"
#include "source/map/map.h"
#include "source/globals.h"
#include "source/map/corruptor.h"

// Loads the map at the player's current position into the ram variable given. 
// Kept in a separate file, as this must remain in the primary bank so it can
// read data from another prg bank.
void load_map() {
    
    // Need to switch to the bank that stores this map data.
    bank_push(currentWorldId);
    memcpy(currentMap, overworld + (playerOverworldPosition << 8), 256);
    bank_pop();

    banked_call(PRG_BANK_CORRUPTOR, corrupt_current_map);
}