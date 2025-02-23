#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "camera.h"

int main(void) {

    Camera3D camera = {
        .position = Vector3One(),
        .target = Vector3Zero(),
        .up = (Vector3){0, 1, 0},
        .fovy = 90.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    InitWindow(800, 600, "Wireframe Editor");

    ToggleFullscreen();
    SetTargetFPS(60);
    DisableCursor();

    while (!WindowShouldClose()) {

        update_custom_camera(&camera);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                DrawCube(Vector3Zero(), 1, 1, 1, RED);
                DrawGrid(1000, 10);
            }
            EndMode3D();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
