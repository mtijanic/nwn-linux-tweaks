// Released under WTFPL-2.0 license
//
// Unlock additional base classes at character creation.
//   NWN 1.69 ignores any 2DA edits when choosing a class for a level 1 character
//   Only the first 11 classes are selectable, the others will be grayed out.
//   This patch extends that limit to 127.
//
// To compile:
//    gcc -m32 -fPIC -shared -o nwmain-baseclass-unlock.so nwmain-baseclass-unlock.c
//
// To run, add nwmain-baseclass-unlock.so to LD_PRELOAD before running nwmain
//    LD_PRELOAD=./nwmain-baseclass-unlock.so ; ./nwmain

#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <sys/mman.h>

void nwmain_patch(void) __attribute__((constructor));

static void apply_patch(uintptr_t address, size_t patch_size, const uint8_t *patch)
{
    uintptr_t page = address & ~0xFFF;
    if (mprotect((void*)page, (address-page) + patch_size, PROT_WRITE | PROT_READ | PROT_EXEC))
    {
        perror("mprotect");
        return;
    }

    printf("Applying patch at %p\n\tOld data:", (void*)address);
    for (size_t i = 0; i < patch_size; i++)
        printf(" %02x", ((uint8_t*)address)[i]);

    printf("\n\tNew data:");
    for (size_t i = 0; i < patch_size; i++)
        printf(" %02x", patch[i]);

    putchar('\n');

    memcpy((void*)address, patch, patch_size);
}

void nwmain_patch(void)
{
    //
    // Old: 0f b6 05 fa e0 5f 08    movzx  eax,BYTE PTR ds:0x85fe0fa
    // New: b8 7f 00 00 00          mov    eax,0x7f
    //      90                      nop
    //      90                      nop
    //
    // Code is trying to load the index of the Wizard class into EAX to
    // use as a limit how many GUI listbox items to mark as enabled.
    // Patch hardcodes this to 127 instead.
    //
    const uint8_t class_list_patch[] = {0xb8, 0x7f, 0x00, 0x00, 0x00, 0x90, 0x90};
    apply_patch(0x82320b0, sizeof(class_list_patch), class_list_patch);
}
