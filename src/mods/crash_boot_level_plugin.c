#include "mod_plugins.h"

#include <stdlib.h>

/*
 * "Boot in level": picks the level the game boots into by writing the level-ID
 * byte (0x80011DB0) on guest VBlank while the game is in its boot state
 * (byte 0x80011DB2 == 0x04 — the "04" low byte of the D0011DB2 3404 code).
 * Boot-time injection like a cheat device, so no game_started guard: enable it
 * and start the game fresh.
 */
#define CRASH_LEVEL_BYTE 0x80011DB0u
#define CRASH_BOOT_STATE 0x80011DB2u
#define CRASH_BOOT_STATE_VALUE 0x04u

#define PKG "crash.boot_level_pack"
#define FEATURE "boot-level"

static uint8_t g_level = 0x22;

static void crash_boot_level_activate(void) {
    char buf[16];
    if (!psx_mod_option_value(PKG, FEATURE, "level", buf, sizeof buf))
        return;
    char* end = buf;
    const unsigned long v = strtoul(buf, &end, 0);
    if (end == buf || *end != '\0' || v > 0xFFu)
        return;
    g_level = (uint8_t)v;
}

static void crash_boot_level_vblank(void) {
    if (psx_mod_read_byte(CRASH_BOOT_STATE) != CRASH_BOOT_STATE_VALUE)
        return;
    if (psx_mod_read_byte(CRASH_LEVEL_BYTE) != g_level)
        psx_mod_write_byte(CRASH_LEVEL_BYTE, g_level);
}

PSX_MOD_CONSTRUCTOR(crash_register_boot_level_plugin) {
    (void)psx_mod_register_activation_plugin(
        "crash.boot-level", crash_boot_level_activate);
    (void)psx_mod_register_vblank_plugin(
        "crash.boot-level", crash_boot_level_vblank);
}
