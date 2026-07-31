#include "mod_plugins.h"
#include <stdio.h>

/* Callback que se ejecuta antes de abrir la ventana de juego */
static void crash_test_activation(void) {
    printf("[CrashMod] ¡Hola desde el plugin nativo de Crash!\n");

    // Probamos forzar relación de aspecto 16:9 widescreen
    psx_mod_set_fixed_display_aspect(16, 9);

    // O si quieres probar desbloquear VBlank a 120 FPS de prueba:
    // psx_mod_set_native_vblank_rate(120);
}

/* Usamos la macro con constructor estático para auto-registrar el plugin al iniciar */
PSX_MOD_CONSTRUCTOR(register_crash_test_mod) {
    psx_mod_register_activation_plugin("crash.test_widescreen", crash_test_activation);
}
