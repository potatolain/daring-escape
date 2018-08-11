#include "source/map/corruptor.h"
#include "source/sprites/player.h"
#include "source/globals.h"
#include "source/map/map.h"

CODE_BANK(PRG_BANK_CORRUPTOR);

#define corruptionPosition tempChar1
#define corruptGone tempChar2

void test_and_do_corruption() {
    return;
    corruptionLevel += playerXVelocity + playerYVelocity;

    corruptionPosition = corruptionLevel >> 5;
    corruptGone = (corruptionLevel >> 6) & 0x01;
    // Update screenBuffer here

    if (corruptGone) {

    } else {

    }

}