#include "source/menus/game_over.h"
#include "source/graphics/palettes.h"
#include "source/configuration/system_constants.h"
#include "source/globals.h"
#include "source/neslib_asm/neslib.h"
#include "source/configuration/game_states.h"
#include "source/menus/text_helpers.h"
#include "source/menus/input_helpers.h"
#include "source/neslib_asm/neslib.h"
#include "source/configuration/game_states.h"
#include "source/graphics/fade_animation.h"

CODE_BANK(PRG_BANK_GAME_OVER);

#define gameOverState tempChar1
void draw_game_over_screen() {
    music_stop();
    gameOverState = 0;

    set_vram_update(NULL);
    ppu_off();
    clear_screen_with_border();

    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Just write "- Paused -" on the screen... there's plenty of nicer things you could do if you wanna spend time!
    put_str(NTADR_A(11, 13), "Game Over");

    put_str(NTADR_A(11, 18), "Continue?");

    put_str(NTADR_A(14, 20), "Yes");
    put_str(NTADR_A(14, 21), "No");
    vram_adr(NTADR_A(12, 20));
    vram_put(0xe2);
    vram_adr(NTADR_A(12, 21));
    vram_put(0xff);

    // We purposely leave sprites off, so they do not clutter the view. 
    // This means all menu drawing must be done with background tiles - if you want to use sprites (eg for a menu item),
    // you will have to hide all sprites, then put them back after. 
    ppu_on_bg();


    fade_in();

    screenBuffer[0] = MSB(NTADR_A(12, 20)) | NT_UPD_VERT;
    screenBuffer[1] = LSB(NTADR_A(12, 20));
    screenBuffer[2] = 2;

    screenBuffer[3] = 0xe2;
    screenBuffer[4] = 0xff;

    screenBuffer[5] = NT_UPD_EOF;
    set_vram_update(screenBuffer);
    while(1) {
        tempChar2 = pad_trigger(0);

        if (tempChar2 & PAD_UP) {
            if (gameOverState != 0) {
                sfx_play(SFX_KEY, SFX_CHANNEL_1);
            }
            gameOverState = 0;
        } else if (tempChar2 & PAD_DOWN) {
            if (gameOverState != 1) {
                sfx_play(SFX_KEY, SFX_CHANNEL_1);
            }
            gameOverState = 1;
        }
        
        if (gameOverState == 0) {
            screenBuffer[3] = 0xe2;
            screenBuffer[4] = 0xff;
        } else {
            screenBuffer[3] = 0xff;
            screenBuffer[4] = 0xe2;
        }

        if (tempChar2 & (PAD_A | PAD_START)) {
            break;
        }

        ppu_wait_nmi();
    }

    set_vram_update(NULL);

    if (gameOverState == 1) {
        sfx_play(SFX_HURT, SFX_CHANNEL_1);
        fade_out();
        reset();
    } else {
        sfx_play(SFX_HEART, SFX_CHANNEL_1);
        if (worldNum < 4) {
            worldNum = 0;
        } else if (worldNum < 9) {
            worldNum = 4;
        } else {
            worldNum = 9;
        }

        playerHealth = 5;
        // I hate to do this, but it's game breaking if I don't
        playerVacuumCount = 0;
        playerKeyCount = 0;

        gameState = GAME_STATE_RESET_LEVEL;

    }


}

void draw_reset_level() {
    ppu_off();
    clear_screen_with_border();

    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Just write "- Paused -" on the screen... there's plenty of nicer things you could do if you wanna spend time!
    put_str(NTADR_A(11, 4), "Daydream");
    //                       |                             |
    put_str(NTADR_A(5, 8),  "Barney realized he had");
    put_str(NTADR_A(5, 9),  "dreampt about dying at");
    put_str(NTADR_A(5, 10), "this point in his ");
    put_str(NTADR_A(5, 11), "journey...");

    put_str(NTADR_A(5, 16), "He wakes to find the");
    put_str(NTADR_A(5, 17), "world still shrinking,");
    put_str(NTADR_A(5, 18), "and his health");
    put_str(NTADR_A(5, 19), "deteriorating.");

    put_str(NTADR_A(9, 24), "RUN, BARNEY!!");



    // We purposely leave sprites off, so they do not clutter the view. 
    // This means all menu drawing must be done with background tiles - if you want to use sprites (eg for a menu item),
    // you will have to hide all sprites, then put them back after. 
    oam_clear();
    ppu_on_all();

}