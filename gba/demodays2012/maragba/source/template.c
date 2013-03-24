#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_sprites.h>
#include <stdio.h>
#include <stdlib.h>

#define PACSPRITE 0
#define FONTS_SQUIRE 1

#if PACSPRITE
#include "pacsprite.h"
#endif

#if FONTS_SQUIRE
#include "fonts_squire.h"
#endif

SpriteEntry sprite[128];

void CopyOAM(void) {
    u16 loop;
    u16 *ptrOAM = (u16 *) OAM;
    u16 *ptrSprite = (u16 *)(OBJATTR *)sprite;

    for (loop = 0 ; loop < 128 * 4 ; loop++) {
        ptrOAM[loop] = ptrSprite[loop];
    }
}

void FillSpritesPal(void) {
    int loop;

#if PACSPRITE
    for (loop = 0 ; loop < 256 ; loop++) {
        OBJ_COLORS[loop] = pacspritePalette[loop];
    }
#endif

#if FONTS_SQUIRE
    for (loop = 0 ; loop < 256 ; loop++) {
        OBJ_COLORS[loop] = fontspal[loop];
    }
#endif
}

void InitSprites(void) {
    int loop;

    for (loop = 0 ; loop < 128 ; loop++) {
        sprite[loop].attribute[0] = 160 | ATTR0_DISABLED;
        sprite[loop].attribute[1] = 240;
    }
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
    s16 x = 100;
    s16 y = 60;
    u16 loop;
    u16 *OAMData = (u16 *)OBJ_BASE_ADR;
    u16 s, e;

    // the vblank interrupt must be enabled for VBlankIntrWait() to work
    // since the default dispatcher handles the bios flags no vblank handler
    // is required
    irqInit();
    irqEnable(IRQ_VBLANK);

    SetMode(MODE_0 | OBJ_ENABLE | OBJ_1D_MAP);

    InitSprites();

    FillSpritesPal();

#if PACSPRITE
    sprite[0].attribute[0] = ATTR0_COLOR_256 | ATTR0_SQUARE | ATTR0_NORMAL | (y & 0x00ff);
    sprite[0].attribute[1] = ATTR1_SIZE_16 | (x & 0x00ff);
    sprite[0].attribute[2] = 0;
#endif

#if FONTS_SQUIRE
    sprite[0].attribute[0] = ATTR0_COLOR_16 | ATTR0_SQUARE | ATTR0_NORMAL | (y & 0x00ff);
    sprite[0].attribute[1] = ATTR1_SIZE_16 | (x & 0x00ff);
    sprite[0].attribute[2] = 0;
#endif

#if PACSPRITE
    s = 0;
    e = 3 + 1; // for having the pacman
    for (loop = (s*(16*16)/4) ; loop < (e*(16 * 16)/4)  ; loop++) {
        OAMData[loop] = pacspriteData[loop];
    }
#endif

#if FONTS_SQUIRE
    //aAbcdefghijklmn DCB "ABCDEFGHIJKLMNOPQRSTUVWXYZ?!. ",0
    s = 0;
    e = s + 1; // for having the bitmap fonts
    for (loop = (s*(16*16)/4) ; loop < (e*(16 * 16)/4)  ; loop++) { 
        OAMData[loop-(s*(16*16/4))] = fontsspr[loop]; // print a sprite in a bank 0
    }
#endif

    while (1) {
        VBlankIntrWait();
        CopyOAM();
    }
}


