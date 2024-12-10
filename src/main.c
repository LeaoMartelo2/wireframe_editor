#include "raylib.h"
#include "raymath.h"
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_GEOMETRY 5

typedef struct Geometry {
        Vector3 pos;
        Vector3 size;
        bool active;
        int id;
        bool selected;
} Geometry;

int main(void) {

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Wireframe editor");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    ToggleFullscreen();

    bool gui_active = true;

    int selected_geometry = 0;

    float step_size = 0.10f;

    Camera3D camera = {0};
    camera.position = (Vector3){0, 1, 0};
    camera.target = (Vector3){1, 1, 0};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Geometry map_geometry[MAX_GEOMETRY];

    int teste = 0;

    for (int i = 0; i < MAX_GEOMETRY; i++) {
        map_geometry[i].pos = Vector3Zero();
        map_geometry[i].active = false;
        map_geometry[i].id = i;
        map_geometry[i].size = Vector3One();

        /*printf("i: %d\n", i);*/
    }

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) {
            gui_active = !gui_active;

            if (gui_active) {
                EnableCursor();
            } else {
                DisableCursor();
            }
        }

        if (!gui_active) {
            UpdateCamera(&camera, CAMERA_FREE);

            if (IsKeyDown(KEY_Q)) {
                camera.up = (Vector3){0, 1, 0};
            }
            if (IsKeyDown(KEY_E)) {
                camera.up = (Vector3){0, 1, 0};
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawGrid(10000, 10.0f);

        for (int i = 0; i < MAX_GEOMETRY; i++) {
            if (map_geometry[i].active) {
                DrawCubeV(map_geometry[i].pos, map_geometry[i].size, BLACK);
                DrawCubeWiresV(map_geometry[i].pos, map_geometry[i].size, RED);
                if (i == selected_geometry) {
                    DrawCubeWiresV(map_geometry[i].pos, map_geometry[i].size, GREEN);
                }
            }
        }

        EndMode3D();

        if (gui_active) {

            DrawRectangle(0, 0, 710, 390, ColorAlpha(GetColor(0x001100FF), 0.7));

            DrawText("Manage Geometry", 10, 10, 30, WHITE);

            if (GuiButton((Rectangle){10, 40, 100, 30},
                          "Add Geometry")) {
                for (int i = 0; i < MAX_GEOMETRY; i++) {
                    if (!map_geometry[i].active) {
                        map_geometry[i].active = true;
                        map_geometry[i].pos = camera.position;
                        selected_geometry = i;
                        break;
                    }
                }
            }

            GuiLabel((Rectangle){10, 80, 100, 20}, "Add Geometry");

            GuiSpinner((Rectangle){120, 80, 120, 30}, NULL, &selected_geometry, 0, MAX_GEOMETRY - 1, false);

            GuiGroupBox((Rectangle){10, 120, 340, 260}, "Geometry Properties");

            DrawText(TextFormat("X: %f", map_geometry[selected_geometry].pos.x),
                     20, 150, 20, WHITE);

            DrawText(TextFormat("Y: %f", map_geometry[selected_geometry].pos.y),
                     20, 170, 20, WHITE);

            DrawText(TextFormat("Z: %f", map_geometry[selected_geometry].pos.z),
                     20, 190, 20, WHITE);

            if (GuiButton((Rectangle){150, 150, 150, 50},
                          TextFormat("Set pos to camera\nCamera at:%.1f, %.1f, %.1f", camera.position.x,
                                     camera.position.y,
                                     camera.position.z))) {
                map_geometry[selected_geometry].pos = camera.position;
            }

            if (GuiButton((Rectangle){200, 230, 150, 50}, "Reset size")) {
                map_geometry[selected_geometry].size = Vector3One();
            }

            DrawText(TextFormat("Height: %f\nWidth :%f\nDepth: %f",
                                map_geometry[selected_geometry].size.x,
                                map_geometry[selected_geometry].size.y,
                                map_geometry[selected_geometry].size.z),
                     20, 215, 20, WHITE);

            GuiGroupBox((Rectangle){360, 10, 340, 370}, "Controls");

            DrawText("Arrow keys, RCtrl / RShift: change position\n"
                     "WASD, LShift / LCtrl: change size",
                     370, 20, 14, WHITE);

            GuiSliderPro((Rectangle){380, 70, 290, 30}, "0", "1000", &step_size, 0.0f, 100.0f, 10);
            DrawText(TextFormat("Step Size:%6.2f", step_size), 425, 110, 25, WHITE);

            if (GuiButton((Rectangle){380, 105, 40, 40}, "<")) {
                step_size -= 0.10f;
                step_size = Clamp(step_size, 0.0f, 100.0f);
            }

            if (GuiButton((Rectangle){630, 105, 40, 40}, ">")) {
                step_size += 0.10f;
                step_size = Clamp(step_size, 0.0f, 100.0f);
            }

            DrawText("ESC to toggle camera movement", 370, 200, 20, WHITE);

            /* EDIT GEOMETRY */

            if (IsKeyDown(KEY_UP)) {
                map_geometry[selected_geometry].pos.z += step_size;
            }
            if (IsKeyDown(KEY_DOWN)) {
                map_geometry[selected_geometry].pos.z -= step_size;
            }
            if (IsKeyDown(KEY_LEFT)) {
                map_geometry[selected_geometry].pos.x -= step_size;
            }
            if (IsKeyDown(KEY_RIGHT)) {
                map_geometry[selected_geometry].pos.x += step_size;
            }
            if (IsKeyDown(KEY_SPACE)) {
                map_geometry[selected_geometry].pos.y += step_size;
            }
            if (IsKeyDown(KEY_RIGHT_SHIFT)) {
                map_geometry[selected_geometry].pos.y -= step_size;
            }

            if (IsKeyDown(KEY_W)) {
                map_geometry[selected_geometry].size.x += step_size;
            }
            if (IsKeyDown(KEY_S)) {
                map_geometry[selected_geometry].size.x -= step_size;
            }
            if (IsKeyDown(KEY_A)) {
                map_geometry[selected_geometry].size.z -= step_size;
            }
            if (IsKeyDown(KEY_D)) {
                map_geometry[selected_geometry].size.z += step_size;
            }
            if (IsKeyDown(KEY_TAB)) {
                map_geometry[selected_geometry].size.y += step_size;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                map_geometry[selected_geometry].size.y -= step_size;
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
