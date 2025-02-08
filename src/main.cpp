#include "camera.c"
#include "misc.c"

int main(void) {

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Wireframe Editor");
    raylib_config();

    bool gui_active = true;

    bool gui_type = EDITOR_GROUND;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
