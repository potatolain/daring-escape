#include "source/map/corruptor.h"
#include "source/sprites/player.h"
#include "source/globals.h"
#include "source/map/map.h"
#include "source/neslib_asm/neslib.h"
#include "source/globals.h"
#include "source/configuration/system_constants.h"
#include "source/configuration/game_states.h"

CODE_BANK(PRG_BANK_CORRUPTOR);

#define corruptionPositionGlobal tempChar1
#define corruptionPosition tempChar2
// BEGING CAFFEINE MADNESS
#define temp tempChar3
#define temp2 tempChar4
#define temp3 tempChar5
#define currentValue tempInt1
#define blooper tempInt2

ZEROPAGE_DEF(unsigned char, corruptionTileState);

// map-wide
unsigned char get_corruption_position_global() {
    return corruptionLevel >> 6;
}

// This screen tile (WARNING: DESTROYS tempChara and tempChar9)
unsigned char get_corruption_position() {
    // This is the current screen's l/r coordinate, translated to corruptionLevel (global) (ie multiplied by 16)
    tempChara = (playerOverworldPosition & 0x07) << 4;
    tempChar9 = corruptionLevel >> 6;
    
    // NOTE: This could be more efficient if we nommed another temp variable
    if (tempChara > tempChar9) {
        corruptionTileState = 0;
        return 0;
    } else {
        corruptionTileState = (corruptionLevel >> 4) & 0x03;
        return tempChar9 - tempChara;
    }
    
}

unsigned char get_current_tile_corruption_state() {
    return corruptionTileState;
}

// Take map screen data, apply current corruption level
void corrupt_current_map() {

    corruptionPosition = get_corruption_position();
    if (corruptionPosition == 0) {
        return;
        /// Nothing to do here!
    }
    
    for (i = 0; i != (corruptionPosition - 1); ++i) {
        for (j = 0; j != 12; j++) {
            // HACK: Just need a blank black tile. Got it.
            currentMap[(j<<4) + i] = 57;
        }
    }

    for (j = 0; j != 12; ++j) {
        currentMap[(j<<4) + corruptionPosition - 1] = 57;
    }
}

#define BOUFFANT (((57 & 0xf8)) << 2) + ((57 & 0x07) << 1)

void test_and_do_corruption() {

    // TODO: item to slow corruption
    if (worldNum < 5) {

        corruptionLevel += CORRUPTION_SPEED;
    } else if (worldNum == 12) {
        // VROOM
        corruptionLevel += 6;
    } else if (worldNum == 13) {
        // GO
        corruptionLevel += 8;
    } else if (worldNum == 14) {
        // Do nothing at all :)
    } else {
        corruptionLevel += CORRUPTION_SPEED_FAST;
    }

    corruptionPosition = get_corruption_position();

// 3 space tabs like a boss
   if (corruptionPosition == 0) {
       return;
   }
   // Go from 1-15 on this screen. Slight discrepancies if you're switching between screens, but well, who cares?
   corruptionPosition -= 1;
   set_vram_update(NULL);

    blooper = NAMETABLE_A + (corruptionPosition << 1);
    screenBuffer[0] = MSB(blooper) | NT_UPD_VERT;
    screenBuffer[1] = LSB(blooper);
    screenBuffer[2] = 24;
    ++blooper;

    screenBuffer[27] = MSB(blooper) | NT_UPD_VERT;
    screenBuffer[28] = LSB(blooper);
    screenBuffer[29] = 24;
    screenBuffer[54] = NT_UPD_EOF;

    if (corruptionTileState != 3) {
        // Tiles are self &0xfe + 1
        for (i = 0; i != 12; ++i) {
            temp = i<<1;
            temp2 = i<<4;
            
            currentValue = (currentMap[corruptionPosition + temp2] & 0x3e);
            currentValue = (((currentValue & 0xf8)) << 2) + ((currentValue & 0x07) << 1);
            
            if (corruptionTileState == 0) {
                screenBuffer[3 + temp] = currentValue + 2;
                screenBuffer[4 + temp] = currentValue + 18; 
            } else {
                screenBuffer[3 + temp] = BOUFFANT;
                screenBuffer[4 + temp] = BOUFFANT;
            }

            if (corruptionTileState > 1) {
                currentValue += 2;
            }
            // currentValue = (((currentValue & 0xf8)) << 2) + ((currentValue & 0x07) << 1);

            screenBuffer[30 + temp] = currentValue + 1;
            screenBuffer[31 + temp] = currentValue + 17;

        }
    } else {
        // Tiles are blank'd
            
        for (i = 0; i != 12; ++i) {
            temp = i<<1;
            screenBuffer[3 + temp] = BOUFFANT;
            screenBuffer[4 + temp] = BOUFFANT;
            screenBuffer[30 + temp] = BOUFFANT;
            screenBuffer[31 + temp] = BOUFFANT;
            currentMap[(i<<4)+corruptionPosition] = 57;
        }

        // Jank player sprite out of existance if needed
        if ((playerXPosition+PLAYER_WIDTH_EXTENDED + 35) >> PLAYER_POSITION_SHIFT < ((corruptionPosition+1)<<4)+1) {
            sfx_play(SFX_HURT, SFX_CHANNEL_1);
            if (--playerHealth == 0) {
                gameState = GAME_STATE_GAME_OVER;
            } else {
                gameState = GAME_STATE_EATEN;
            }
        }

    }

    set_vram_update(screenBuffer);

}