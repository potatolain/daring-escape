#include "source/menus/credits.h"
#include "source/graphics/palettes.h"
#include "source/configuration/system_constants.h"
#include "source/globals.h"
#include "source/neslib_asm/neslib.h"
#include "source/configuration/game_states.h"
#include "source/menus/text_helpers.h"
#include "source/configuration/game_info.h"
#include "source/menus/input_helpers.h"
#include "source/graphics/fade_animation.h"

CODE_BANK(PRG_BANK_CREDITS_MENU);

void draw_win_screen() {
    ppu_off();
    clear_screen();
    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Add whatever you want here; NTADR_A just picks a position on the screen for you. Your options are 0, 0 to 32, 30
    put_str(NTADR_A(7, 2), "- Congratulations -");

    put_str(NTADR_A(4, 8), "With your help, Barney");
    put_str(NTADR_A(4, 9), "was able to find his way");
    put_str(NTADR_A(4, 10), "to a safe dimension.");

    // TODO: Replace this with a level with NPCs. Tells the story SO much better.
    if (playerVacuumCount >= ALL_VACUUMS) {
        put_str(NTADR_A(4, 14), "Since you found enough");
        put_str(NTADR_A(4, 15), "vacuum pieces, the");
        put_str(NTADR_A(4, 16), "the scientists in this");
        put_str(NTADR_A(4, 17), "dimension were able to");
        put_str(NTADR_A(4, 18), "reverse the damage.");

        put_str(NTADR_A(4, 22), "Barney is headed back");
        put_str(NTADR_A(4, 23), "home.");

    } else {
        put_str(NTADR_A(4, 14), "The scientists in this");
        put_str(NTADR_A(4, 15), "dimension were able to");
        put_str(NTADR_A(4, 16), "stop the damage, though");
        put_str(NTADR_A(4, 17), "they could not reverse");
        put_str(NTADR_A(4, 18), "it.");

        put_str(NTADR_A(4, 22), "Barney has been");
        put_str(NTADR_A(4, 23), "welcomed to stay with");
        put_str(NTADR_A(4, 24), "the scientists in their");
        put_str(NTADR_A(4, 25), "dimension.");
    }

    // Hide all existing sprites
    oam_clear();
    ppu_on_all();

}

void draw_credits_screen() {
    ppu_off();
    clear_screen();
    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Add whatever you want here; NTADR_A just picks a position on the screen for you. Your options are 0, 0 to 32, 30
    put_str(NTADR_A(11, 2), "- Credits -");

    put_str(NTADR_A(2, 6), "Game Design and Logic");
    put_str(NTADR_A(4, 8), gameAuthor);

    put_str(NTADR_A(2, 12), "Created using:");
    put_str(NTADR_A(4, 14), "- nes-starter-kit");
    put_str(NTADR_A(4, 15), "- cc65");
    put_str(NTADR_A(4, 16), "- NES Screen Tool");
    put_str(NTADR_A(4, 17), "- Famitracker");
    put_str(NTADR_A(4, 18), "- Tiled");
    put_str(NTADR_A(4, 19), "- Who's Cuter Font");
    put_str(NTADR_A(4, 20), "- NES Space Checker");
    put_str(NTADR_A(4, 21), "- Mesen");
/*
    put_str(NTADR_A(2, 11), "Music");
    put_str(NTADR_A(4, 13), "Wolfgang (OpenGameArt)");

    put_str(NTADR_A(2, 16), "Artwork");
    put_str(NTADR_A(4, 18), "Refresh Games (OpenGameArt)");
*/
    /*put_str(NTADR_A(6, 24), "Created in 48");
    put_str(NTADR_A(17, 24), currentYear);
    put_str(NTADR_A(22, 24), "by");*/
    put_str(NTADR_A(2, 25), gameAuthorContact);

	put_str(NTADR_A(2, 27), "Copyright");
	put_str(NTADR_A(12, 27), currentYear);
	put_str(NTADR_A(17, 27), gameAuthor);

    // Not making a new game state; heck with it
    ppu_on_all();
    fade_in();
    banked_call(PRG_BANK_MENU_INPUT_HELPERS, wait_for_start);
    fade_out();


    ppu_off();
    clear_screen();
    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Add whatever you want here; NTADR_A just picks a position on the screen for you. Your options are 0, 0 to 32, 30

    put_str(NTADR_A(4, 2), "- NES Starter Kit -");
    // put_str(NTADR_A(4, 8));

    put_str(NTADR_A(2, 8), "NES Starter Kit is a free");
    put_str(NTADR_A(2, 10), "game + guide for making");
    put_str(NTADR_A(2, 12), "Nintendo Games.");
    // put_str(NTADR_A(2, 11), "Nintendo Entertainment");
    // put_str(NTADR_A(2, 12), "System.");
    // put_str(NTADR_A(4, 17), "- Famitracker");
    put_str(NTADR_A(4, 17), "If I could make this in");
    put_str(NTADR_A(5, 19),  "48 hours, what could");
    put_str(NTADR_A(11, 21),        "you do?");
    // put_str(NTADR_A(4, 21), "- Mesen");

    // put_str(NTADR_A(2, 24), "Check it out:");
    // put_str(NTADR_A(2, 24), "cppchriscpp.github.io/");
    // put_str(NTADR_A(2, 25), "nes-starter-kit");
    put_str(NTADR_A(1, 26), "https://tinyurl.com/nes-start");


    // Hide all existing sprites
    oam_clear();
    ppu_on_all();

    fade_in();
    banked_call(PRG_BANK_MENU_INPUT_HELPERS, wait_for_start);
    fade_out();


    ppu_off();
    clear_screen();
    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Add whatever you want here; NTADR_A just picks a position on the screen for you. Your options are 0, 0 to 32, 30

    put_str(NTADR_A(11, 14), "Thanks for");
    put_str(NTADR_A(11, 16), " Playing!");


    ppu_on_all();
}