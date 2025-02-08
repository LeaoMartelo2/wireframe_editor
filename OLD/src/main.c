#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "camera.h"
#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../raylib/raygui.h"

int main(void) {

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Wireframe editor");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    ToggleFullscreen();

    bool gui_active = true;

    int gui_type = EDITOR_GROUND;

    int selected_geometry = 0;

    int geometry_ammount = 0;

    float step_size = 10.0f;

    Camera3D camera = {0};
    camera.position = (Vector3){0, 1, 0};
    camera.target = (Vector3){1, 1, 0};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Geometry map_geometry[MAX_GEOMETRY];

    for (int i = 0; i < MAX_GEOMETRY; i++) {
        map_geometry[i].pos = Vector3Zero();
        map_geometry[i].active = false;
        map_geometry[i].size = (Vector3){10, 10, 10};
        map_geometry[i].see_through = false;
    }

    int selected_ground = 0;
    int ground_ammount = 0;

    Ground map_ground[MAX_GROUND];

    for (int i = 0; i < MAX_GROUND; i++) {
        map_ground[i].pos = Vector3Zero();
        map_ground[i].active = false;
        map_ground[i].size = (Vector3){2000, 1, 2000};
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
            update_custom_camera(&camera);

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

        DrawLine3D((Vector3){0, 1, 0}, (Vector3){1000, 0, 0}, RED);
        DrawLine3D((Vector3){0, 1, 0}, (Vector3){0, 1000, 0}, GREEN);
        DrawLine3D((Vector3){0, 1, 0}, (Vector3){0, 0, 1000}, BLUE);
        DrawSphere((Vector3){0, 1, 0}, 0.005, WHITE);

        for (int i = 0; i < MAX_GEOMETRY; i++) {
            if (map_geometry[i].active) {
                if (i != selected_geometry) {
                    DrawCubeV(map_geometry[i].pos, map_geometry[i].size, DARKGRAY);
                    DrawCubeWiresV(map_geometry[i].pos, map_geometry[i].size, RED);
                }
                if (i == selected_geometry) {

                    DrawCubeV(map_geometry[i].pos, map_geometry[i].size, GRAY);
                    DrawCubeWiresV(map_geometry[i].pos, map_geometry[i].size, GREEN);
                }
            }
        }

        for (int i = 0; i < MAX_GROUND; i++) {
            if (map_ground[i].active) {
                if (i != selected_ground) {
                    DrawCubeV(map_ground[i].pos, map_ground[i].size, GetColor(0x181818FF));
                    DrawCubeWiresV(map_ground[i].pos, map_ground[i].size, BLUE);
                }
                if (i == selected_ground) {

                    DrawCubeV(map_ground[i].pos, map_ground[i].size, ColorBrightness(GetColor(0x181818FF), 0.5));
                    DrawCubeWiresV(map_ground[i].pos, map_ground[i].size, GREEN);
                }
            }
        }

        EndMode3D();

        if (gui_active) {

            draw_static_gui(&step_size, &gui_type);

            if (gui_type == EDITOR_GEOMETRY) {

                draw_geometry_gui(&selected_geometry, &geometry_ammount, map_geometry, camera, step_size);
                edit_geometry(map_geometry, selected_geometry, step_size);
            }

            if (gui_type == EDITOR_GROUND) {

                draw_ground_gui(&selected_ground, &ground_ammount, map_ground, camera, step_size);
                edit_ground(map_ground, selected_ground, step_size);
            }
        }

        DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 1, WHITE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
