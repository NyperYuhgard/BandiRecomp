#include "mod_plugins.h"

static void example_vblank(void) {
    if (psx_mod_game_started())
        psx_mod_write_byte(0x1F8001B4u, 1u);
}

PSX_MOD_CONSTRUCTOR(register_example_mod) {
    (void)psx_mod_register_vblank_plugin(
        "example.quick-start", example_vblank);
}
