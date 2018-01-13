// Released under WTFPL-2.0 license
//
// Unlock additional resolutions in the game settings.
// If a desired resolution is not included, just add it to the valid_mods list.
//
// To compile:
//    gcc -m32 -fPIC -shared -o nwmain-list-modes.so nwmain-list-modes.c
//
// To run, add nwmain-list-modes.so to LD_PRELOAD before running nwmain
//    LD_PRELOAD=./nwmain-list-modes.so ; ./nwmain

#include <inttypes.h>

#define COUNTOF(a) (sizeof(a) / sizeof(a[0]))

void **SDL_ListModes(void *fmt, uint32_t flags)
{
    struct SDL_Rect {
        int16_t x, y;
        uint16_t w, h;
    };

    static struct SDL_Rect valid_modes[] =
    {
        {0, 0, 1920, 1080},
        {0, 0, 1600, 900},
        {0, 0, 1440, 900},
        {0, 0, 1366, 768},
        {0, 0, 1280, 1024},
        {0, 0, 1280, 800},
        {0, 0, 1024, 768},
        {0, 0, 800,  600}
    };
    static struct SDL_Rect *valid_mode_ptrs[COUNTOF(valid_modes) + 1];
    if (!valid_mode_ptrs[0])
    {
        for (uint32_t i = 0; i < COUNTOF(valid_modes); i++)
            valid_mode_ptrs[i] = &valid_modes[i];
    }

    return (void*)valid_mode_ptrs;
}
