// Released under WTFPL-2.0 license
//
// Unlock the camera and increase the fog distance.
//
// To compile:
//    gcc -m32 -fPIC -shared -o nwmain-camera-unlock.so nwmain-camera-unlock.c
//
// To run, add nwmain-camera-unlock.so to LD_PRELOAD before running nwmain
//    LD_PRELOAD=./nwmain-camera-unlock.so ./nwmain

#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <sys/mman.h>

void nwmain_patch_camera(void) __attribute__((constructor));

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


void nwmain_patch_camera(void)
{
    const float camera_distance_min = -0.25f; // Original: 1.0f
    const float camera_distance_max = 100.0f; // Original: 25.0f
    const float camera_angle_min    =   0.0f; // Original: 1.0f
    const float camera_angle_max    = 200.0f; // Original: 89.0f
    const float fog_distance        =  90.0f; // Original: 45.0f

    apply_patch(0x81a6a62, &camera_distance_min, sizeof(camera_distance_min));
    apply_patch(0x81a6d62, &camera_distance_min, sizeof(camera_distance_min));

    apply_patch(0x81a6a6c, &camera_distance_max, sizeof(camera_distance_max));
    apply_patch(0x81a6d6c, &camera_distance_max, sizeof(camera_distance_max));

    apply_patch(0x81a6a76, &camera_angle_min, sizeof(camera_angle_min));
    apply_patch(0x81a6d76, &camera_angle_min, sizeof(camera_angle_min));

    apply_patch(0x81a6a80, &camera_angle_max, sizeof(camera_angle_max));
    apply_patch(0x81a6d80, &camera_angle_max, sizeof(camera_angle_max));

    apply_patch(0x84c767b, &fog_distance, sizeof(fog_distance));

    const uint8_t dist_max = 0xa0; // Original 0xe4
    apply_patch(0x81a6a68, &dist_max, sizeof(dist_max));

    const uint8_t max_effect_icons = 0xfe; // Original 0x81
    apply_patch(0x80c4df9, &max_effect_icons, sizeof(max_effect_icons));
}
