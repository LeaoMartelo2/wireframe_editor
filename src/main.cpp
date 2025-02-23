#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "camera.h"
#include "editor.h"
#include "geometry.h"

int main(void) {

    Editor editor;

    Camera3D camera = {
        .position = Vector3One(),
        .target = Vector3Zero(),
        .up = {0, 1, 0},
        .fovy = 90.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    InitWindow(800, 600, "Wireframe Editor");

    SetExitKey(KEY_NULL);
    ToggleFullscreen();
    SetTargetFPS(60);
    DisableCursor();

    editor.add_geometry({10, 10, 10}, Vector3One() * 10);

    while (!WindowShouldClose()) {

        update_custom_camera(&camera);

        if (IsKeyPressed(KEY_H)) {

            editor.add_geometry({10, 10, 10}, camera.position);
        }

        if (IsKeyPressed(KEY_G)) {
            editor.geometry_selected_id++;
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
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
