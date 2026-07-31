#include "mod_plugins.h"

/*
 * GameShark `8006199C 0100` for Crash Bandicoot 1 (SCUS-94900): continuously
 * writes the debug-mode flag 0x01 to guest RAM at 0x8006199C. A cheat device
 * re-applies the value every frame; the recompiled runtime cannot load cheats,
 * so this vblank plugin replicates the write after game entry, guarded so it
 * only stores when the value has actually been cleared.
 */
#define CRASH_DEBUG_FLAG 0x8006199Cu

static void crash_debug_vblank(void) {
    if (!psx_mod_game_started())
        return;
    if (psx_mod_read_byte(CRASH_DEBUG_FLAG) != 0x01u)
        psx_mod_write_byte(CRASH_DEBUG_FLAG, 0x01u);
}

PSX_MOD_CONSTRUCTOR(crash_register_debug_plugin) {
    (void)psx_mod_register_vblank_plugin("crash.debug", crash_debug_vblank);
}
