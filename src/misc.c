#include "../raylib/raylib.h"

#ifdef __cplusplus
extern "C" {
#endif

void raylib_pre() {
}

void raylib_config() {
    SetExitKey(KEY_NULL);
    ToggleFullscreen();
}

void raylib_post() {
}

#ifdef __cplusplus
}
#endif
