#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "../raylib/raygui.h"

#define MAX_GEOMETRY 100

typedef struct Geometry {
        Vector3 pos;
        Vector3 size;
        bool active;
        int see_through;
        bool selected;
} Geometry;

void export_map(int geometry_ammount, Geometry *map_geometry);

int main(void) {

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Wireframe editor");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    ToggleFullscreen();

    bool gui_active = true;

    int gui_type = 0;

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
        map_geometry[i].size = (Vector3){25, 25, 25};
        map_geometry[i].see_through = false;
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

        DrawLine3D((Vector3){0, 0, 0}, (Vector3){1000, 0, 0}, RED);
        DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, 1000, 0}, GREEN);
        DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, 0, 1000}, BLUE);
        DrawSphere((Vector3){0, 0, 0}, 0.005, WHITE);

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

        EndMode3D();

        if (gui_active) {

            DrawRectangle(GetScreenWidth() - 350, 0, 350, 80, ColorAlpha(GetColor(0x001100FF), 0.7f));
            GuiGroupBox((Rectangle){GetScreenWidth() - 340, 10, 340, 60}, "Controls");

            DrawText("Arrow keys, RCtrl / RShift: change position\n"
                     "WASD,  X / Z: change size\n"
                     "ESC to toggle camera movement\n",
                     GetScreenWidth() - 320, 20, 14, WHITE);

            DrawRectangle(0, 0, 360, 390, ColorAlpha(GetColor(0x001100FF), 0.7));

            DrawText("Manage Geometry", 10, 10, 30, WHITE);

            if (GuiButton((Rectangle){10, 40, 100, 30},
                          "Add Geometry")) {
                geometry_ammount++;
                for (int i = 0; i < MAX_GEOMETRY; i++) {
                    if (!map_geometry[i].active) {
                        map_geometry[i].active = true;
                        map_geometry[i].pos.x = (int)camera.position.x;
                        map_geometry[i].pos.y = (int)camera.position.y;
                        map_geometry[i].pos.z = (int)camera.position.z;
                        selected_geometry = i;
                        break;
                    }
                }
            }

            GuiLabel((Rectangle){10, 80, 100, 20}, "Select Geometry");

            GuiSpinner((Rectangle){120, 80, 120, 30}, NULL, &selected_geometry, 0, MAX_GEOMETRY - 1, false);

            GuiGroupBox((Rectangle){10, 120, 340, 260}, "Geometry Properties");

            DrawText(TextFormat("X: %.2f\nY: %.2f\nZ: %.2f",
                                map_geometry[selected_geometry].pos.x,
                                map_geometry[selected_geometry].pos.y,
                                map_geometry[selected_geometry].pos.z),
                     20, 150, 20, WHITE);

            if (GuiButton((Rectangle){190, 150, 150, 50},
                          TextFormat("#48#Set pos to camera\nCamera at: %.f, %.f, %.f", camera.position.x,
                                     camera.position.y,
                                     camera.position.z))) {
                map_geometry[selected_geometry].pos.x = (int)camera.position.x;
                map_geometry[selected_geometry].pos.y = (int)camera.position.y;
                map_geometry[selected_geometry].pos.z = (int)camera.position.z;
            }

            if (GuiButton((Rectangle){190, 230, 150, 50}, "#211#Reset size")) {
                map_geometry[selected_geometry].size = (Vector3){25, 25, 25};
            }

            DrawText(TextFormat("\n(X) Width: %.2f\n(Y) Height: %.2f\n(Z) Depth: %.2f",
                                map_geometry[selected_geometry].size.x,
                                map_geometry[selected_geometry].size.y,
                                map_geometry[selected_geometry].size.z),
                     20, 215, 20, WHITE);

            GuiSpinner((Rectangle){200, 300, 100, 30}, "See through",
                       &map_geometry[selected_geometry].see_through,
                       0, 1, false);

            GuiGroupBox((Rectangle){10, GetScreenHeight() - 100, 340, 100}, "Settings");

            DrawText(TextFormat("Step Size: %.1f", step_size), 65, GetScreenHeight() - 90, 20, WHITE);
            /* decrease step size */
            if (GuiButton((Rectangle){15, GetScreenHeight() - 90, 40, 20}, "#118#")) {
                step_size -= 0.50f;
                step_size = Clamp(step_size, 0.0f, 100.0f);
            }
            /* increse step size */
            if (GuiButton((Rectangle){220, GetScreenHeight() - 90, 40, 20}, "#119#")) {
                step_size += 0.50f;
                step_size = Clamp(step_size, 0.0f, 100.0f);
            }

            if (GuiButton((Rectangle){280, GetScreenHeight() - 90, 40, 20}, "#211#")) {
                step_size = 10.0f;
            }

            GuiSpinner((Rectangle){150, GetScreenHeight() - 60, 150, 40},
                       "editor type \n(not added) ", &gui_type, 0, 0, false);

            GuiGroupBox((Rectangle){GetScreenWidth() - 340, GetScreenHeight() - 100, 340, 100}, "Options");

            if (GuiButton((Rectangle){GetScreenWidth() - 330, GetScreenHeight() - 90, 80, 50}, "#02#Export")) {
                export_map(geometry_ammount, map_geometry);
            }

            /* EDIT GEOMETRY */

            if (IsKeyPressed(KEY_UP)) {
                map_geometry[selected_geometry].pos.z += step_size;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                map_geometry[selected_geometry].pos.z -= step_size;
            }
            if (IsKeyPressed(KEY_LEFT)) {
                map_geometry[selected_geometry].pos.x -= step_size;
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                map_geometry[selected_geometry].pos.x += step_size;
            }
            if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
                map_geometry[selected_geometry].pos.y += step_size;
            }
            if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
                map_geometry[selected_geometry].pos.y -= step_size;
            }

            if (IsKeyPressed(KEY_W)) {
                map_geometry[selected_geometry].size.x += step_size;
                map_geometry[selected_geometry].size.x = Clamp(map_geometry[selected_geometry].size.x,
                                                               0.5f, 1000.0f);
            }
            if (IsKeyPressed(KEY_S)) {
                map_geometry[selected_geometry].size.x -= step_size;
                map_geometry[selected_geometry].size.x = Clamp(map_geometry[selected_geometry].size.x,
                                                               0.5f, 1000.0f);
            }
            if (IsKeyPressed(KEY_A)) {
                map_geometry[selected_geometry].size.z -= step_size;
                map_geometry[selected_geometry].size.z = Clamp(map_geometry[selected_geometry].size.z,
                                                               0.5f, 1000.0f);
            }
            if (IsKeyPressed(KEY_D)) {
                map_geometry[selected_geometry].size.z += step_size;

                map_geometry[selected_geometry].size.z = Clamp(map_geometry[selected_geometry].size.z,
                                                               0.5f, 1000.0f);
            }
            if (IsKeyPressed(KEY_X)) {
                map_geometry[selected_geometry].size.y -= step_size;

                map_geometry[selected_geometry].size.y = Clamp(map_geometry[selected_geometry].size.y,
                                                               0.5f, 1000.0f);
            }
            if (IsKeyPressed(KEY_Z)) {
                map_geometry[selected_geometry].size.y += step_size;

                map_geometry[selected_geometry].size.y = Clamp(map_geometry[selected_geometry].size.y,
                                                               0.5f, 1000.0f);
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void export_map(int geometry_ammount, Geometry *map_geometry) {
    FILE *file = fopen("map_geometry.wireframe", "w");

    if (file == NULL) {
        perror("Error exporting to file");
        return;
    }

    /*  temp hard-coded ground until i find a better solution*/
    fprintf(file, "ground_geometry[0].size = (Vector3){2000, 1, 2000};\n"
                  "ground_geometry[0].mesh = GenMeshCube(2000, 1, 2000);\n"
                  "ground_geometry[0].model = LoadModelFromMesh(ground_geometry[0].mesh);\n"
                  "ground_geometry[0].pos = (Vector3){0, 0, 0};\n\n");

    fprintf(file, "int solid_count = 0;\n\n");

    for (int i = 0; i < geometry_ammount; i++) {
        fprintf(file, "solids[%d].size = (Vector3){%f, %f, %f};\n",
                i, map_geometry[i].size.x, map_geometry[i].size.y, map_geometry[i].size.z);

        fprintf(file, "solids[%d].mesh = GenMeshCube(%f, %f, %f);\n",
                i, map_geometry[i].size.x, map_geometry[i].size.y, map_geometry[i].size.z);

        fprintf(file, "solids[%d].model = LoadModelFromMesh(solids[%d].mesh);\n", i, i);

        fprintf(file, "solids[%d].pos = (Vector3){%f, %f, %f};\n",
                i, map_geometry[i].pos.x, map_geometry[i].pos.y, map_geometry[i].pos.z);

        fprintf(file, "solids[%d].see_through = %d;\n", i,
                map_geometry[i].see_through);
        fprintf(file, "solid_count++;\n\n");
    }

    fprintf(file, "*count = solid_count;\n");

    fclose(file);
}
