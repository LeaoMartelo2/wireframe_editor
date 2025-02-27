#include "../raylib/raylib.h"
#include "editor.h"

int main(void) {

    Editor editor;

    Camera3D camera = {
        .position = Vector3One() * 10,
        .target = Vector3Zero(),
        .up = {0, 1, 0},
        .fovy = 90.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    editor.camera_ptr = &camera;

    InitWindow(0, 0, "Wireframe Editor");

    editor.load();

    SetExitKey(KEY_NULL);
    /*ToggleFullscreen();*/
    MaximizeWindow();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        editor.update();

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                draw_reference_point();
                editor.draw_map();
            }
            EndMode3D();

            editor.draw_hud();
        }
        EndDrawing();
    }

    editor.unload();

    CloseWindow();

    return 0;
}
