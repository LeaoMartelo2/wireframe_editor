#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "editor.h"

int main(void) {

    Editor editor;

    Camera3D camera = {
        .position = Vector3One(),
        .target = Vector3Zero(),
        .up = {0, 1, 0},
        .fovy = 90.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    editor.camera_ptr = &camera;

    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Wireframe Editor");

    editor.load();

    SetExitKey(KEY_NULL);
    ToggleFullscreen();
    SetTargetFPS(60);

    editor.add_geometry({10, 10, 10}, Vector3One() * 10);

    while (!WindowShouldClose()) {

        editor.update();

        if (IsKeyPressed(KEY_H)) {

            editor.add_geometry({10, 10, 10}, camera.position);
        }

        if (IsKeyPressed(KEY_J)) {
            editor.remove_geometry();
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                draw_reference_point();
                editor.draw_map();
            }
            EndMode3D();
            DrawText(TextFormat("%zu", editor.geometry_selected_id),
                     GetScreenWidth() / 2, GetScreenHeight() / 2,
                     20, WHITE);

            editor.draw_hud();
        }
        EndDrawing();
    }

    editor.unload();

    CloseWindow();

    return 0;
}
