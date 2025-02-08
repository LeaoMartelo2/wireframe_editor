#include "editor.h"
#include "export.h"

float snap_to_gridf(float value) {

    return round(value / 10) * 10;
}

void draw_static_gui(float *step_size, int *gui_type) {

    DrawRectangle(0, GetScreenHeight() - 110, 360, 120, ColorAlpha(GetColor(0x001100FF), 0.7));

    GuiGroupBox((Rectangle){10, GetScreenHeight() - 100, 340, 100}, "#140#Settings");

    DrawText(TextFormat("Step Size: %.1f", *step_size), 65, GetScreenHeight() - 90, 20, WHITE);

    /* decrease step size */
    if (GuiButton((Rectangle){15, GetScreenHeight() - 90, 40, 20}, "#118#")) {
        *step_size -= 0.5f;
        *step_size = Clamp(*step_size, 0.0f, 100.0f);
    }
    /* increse step size */
    if (GuiButton((Rectangle){220, GetScreenHeight() - 90, 40, 20}, "#119#")) {
        *step_size += 0.5f;
        *step_size = Clamp(*step_size, 0.0f, 100.0f);
    }

    if (GuiButton((Rectangle){280, GetScreenHeight() - 90, 40, 20}, "#211#")) {
        *step_size = 10.0f;
    }

    GuiSpinner((Rectangle){150, GetScreenHeight() - 60, 150, 40},
               "Editor Type  ", gui_type, 0, EDITOR_COUNT - 1, false);

    DrawRectangle(GetScreenWidth() - 350, GetScreenHeight() - 110, 360, 110,
                  ColorAlpha(GetColor(0x001100FF), 0.7));

    GuiGroupBox((Rectangle){GetScreenWidth() - 340, GetScreenHeight() - 100, 340, 100}, "Options");

    if (GuiButton((Rectangle){GetScreenWidth() - 330,
                              GetScreenHeight() - 90, 80, 50},
                  "#02#Export")) {
        /*export_map(geometry_ammount, map_geometry);*/
    }

    DrawRectangle(GetScreenWidth() - 350, 0, 350, 80, ColorAlpha(GetColor(0x001100FF), 0.7f));
    GuiGroupBox((Rectangle){GetScreenWidth() - 340, 10, 340, 60}, "Controls");

    DrawText("Arrow keys, RCtrl / RShift: change position\n"
             "WASD,  X / Z: change size\n"
             "ESC to toggle camera movement\n",
             GetScreenWidth() - 320, 20, 14, WHITE);
}

void draw_geometry_gui(int *selected_geometry, int *geometry_ammount, Geometry *map_geometry, Camera3D camera, float step_size) {

    DrawRectangle(0, 0, 360, 390, ColorAlpha(GetColor(0x001100FF), 0.7));

    DrawText("Geometry", 10, 10, 30, WHITE);

    if (GuiButton((Rectangle){10, 40, 100, 30},
                  "Add Geometry")) {
        *geometry_ammount = *geometry_ammount + 1;
        for (int i = 0; i < MAX_GEOMETRY; i++) {
            if (!map_geometry[i].active) {
                map_geometry[i].active = true;
                map_geometry[i].pos.x = snap_to_gridf(camera.position.x);
                map_geometry[i].pos.y = snap_to_gridf(camera.position.y);
                map_geometry[i].pos.z = snap_to_gridf(camera.position.z);
                *selected_geometry = i;
                break;
            }
        }
    }

    GuiLabel((Rectangle){10, 80, 100, 20}, "Select Geometry");

    GuiSpinner((Rectangle){120, 80, 120, 30}, NULL, selected_geometry, 0, MAX_GEOMETRY - 1, false);

    GuiGroupBox((Rectangle){10, 120, 340, 260}, "Geometry Properties");

    DrawText(TextFormat("X: %.2f\nY: %.2f\nZ: %.2f",
                        map_geometry[*selected_geometry].pos.x,
                        map_geometry[*selected_geometry].pos.y,
                        map_geometry[*selected_geometry].pos.z),
             20, 150, 20, WHITE);

    if (GuiButton((Rectangle){190, 150, 150, 50},
                  TextFormat("#64#Set pos to camera\n\nCamera at: %.f, %.f, %.f",
                             snap_to_gridf(camera.position.x),
                             snap_to_gridf(camera.position.y),
                             snap_to_gridf(camera.position.z)))) {
        map_geometry[*selected_geometry].pos.x = snap_to_gridf(camera.position.x);
        map_geometry[*selected_geometry].pos.y = snap_to_gridf(camera.position.y);
        map_geometry[*selected_geometry].pos.z = snap_to_gridf(camera.position.z);
    }

    if (GuiButton((Rectangle){230, 230, 100, 50}, "#211#Reset size")) {
        map_geometry[*selected_geometry].size = (Vector3){10, 10, 10};
    }

    DrawText(TextFormat("\n(X) Width: %.2f\n(Y) Height: %.2f\n(Z) Depth: %.2f",
                        map_geometry[*selected_geometry].size.x,
                        map_geometry[*selected_geometry].size.y,
                        map_geometry[*selected_geometry].size.z),
             20, 215, 20, WHITE);

    GuiSpinner((Rectangle){200, 300, 100, 30}, "See through",
               &map_geometry[*selected_geometry].see_through,
               0, 1, false);
}

void edit_geometry(Geometry *map_geometry, int selected_geometry, float step_size) {

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
                                                       10.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_S)) {
        map_geometry[selected_geometry].size.x -= step_size;
        map_geometry[selected_geometry].size.x = Clamp(map_geometry[selected_geometry].size.x,
                                                       10.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_A)) {
        map_geometry[selected_geometry].size.z -= step_size;
        map_geometry[selected_geometry].size.z = Clamp(map_geometry[selected_geometry].size.z,
                                                       10.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_D)) {
        map_geometry[selected_geometry].size.z += step_size;

        map_geometry[selected_geometry].size.z = Clamp(map_geometry[selected_geometry].size.z,
                                                       1.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_X)) {
        map_geometry[selected_geometry].size.y -= step_size;

        map_geometry[selected_geometry].size.y = Clamp(map_geometry[selected_geometry].size.y,
                                                       10.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_Z)) {
        map_geometry[selected_geometry].size.y += step_size;

        map_geometry[selected_geometry].size.y = Clamp(map_geometry[selected_geometry].size.y,
                                                       10.0f, 1000.0f);
    }
}

void draw_ground_gui(int *selected_ground, int *ground_ammount,
                     Ground *map_ground, Camera3D camera, float step_size) {

    DrawRectangle(0, 0, 360, 390, ColorAlpha(GetColor(0x001100FF), 0.7));

    DrawText("Ground", 10, 10, 30, WHITE);

    if (GuiButton((Rectangle){10, 40, 100, 30},
                  "Add Ground")) {
        *ground_ammount = *ground_ammount + 1;
        for (int i = 0; i < MAX_GROUND; i++) {
            if (!map_ground[i].active) {
                map_ground[i].active = true;
                map_ground[i].pos.x = (int)0;
                map_ground[i].pos.y = (int)0;
                map_ground[i].pos.z = (int)0;
                *selected_ground = i;
                break;
            }
        }
    }

    GuiLabel((Rectangle){10, 80, 100, 20}, "Select Ground");

    GuiSpinner((Rectangle){120, 80, 120, 30}, NULL, selected_ground, 0, MAX_GEOMETRY - 1, false);

    GuiGroupBox((Rectangle){10, 120, 340, 260}, "Ground Properties");

    DrawText(TextFormat("X: %.2f\nY: %.2f\nZ: %.2f",
                        map_ground[*selected_ground].pos.x,
                        map_ground[*selected_ground].pos.y,
                        map_ground[*selected_ground].pos.z),
             20, 150, 20, WHITE);

    if (GuiButton((Rectangle){190, 150, 150, 50},
                  TextFormat("#64#Set pos to camera\n\nCamera at: %.f, %.f, %.f", camera.position.x,
                             camera.position.y,
                             camera.position.z))) {
        map_ground[*selected_ground].pos.x = snap_to_gridf(camera.position.x);
        map_ground[*selected_ground].pos.y = snap_to_gridf(camera.position.y);
        map_ground[*selected_ground].pos.z = snap_to_gridf(camera.position.z);
    }

    if (GuiButton((Rectangle){230, 230, 100, 50}, "#211#Reset size")) {
        map_ground[*selected_ground].size = (Vector3){2000, 1, 2000};
    }

    if (GuiButton((Rectangle){230, 300, 100, 50}, "#98#Make Small\nPlate")) {
        map_ground[*selected_ground].size = (Vector3){50, 1, 50};
    }

    DrawText(TextFormat("\n(X) Width: %.2f\n(Y) Height: %.2f\n(Z) Depth: %.2f",
                        map_ground[*selected_ground].size.x,
                        map_ground[*selected_ground].size.y,
                        map_ground[*selected_ground].size.z),
             20, 215, 20, WHITE);
}

void edit_ground(Ground *map_ground, int selected_ground, float step_size) {

    if (IsKeyPressed(KEY_UP)) {
        map_ground[selected_ground].pos.z += step_size;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        map_ground[selected_ground].pos.z -= step_size;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        map_ground[selected_ground].pos.x -= step_size;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        map_ground[selected_ground].pos.x += step_size;
    }
    if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
        map_ground[selected_ground].pos.y += step_size;
    }
    if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
        map_ground[selected_ground].pos.y -= step_size;
    }

    if (IsKeyPressed(KEY_W)) {
        map_ground[selected_ground].size.x += step_size;
        map_ground[selected_ground].size.x = Clamp(map_ground[selected_ground].size.x,
                                                   1.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_S)) {
        map_ground[selected_ground].size.x -= step_size;
        map_ground[selected_ground].size.x = Clamp(map_ground[selected_ground].size.x,
                                                   1.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_A)) {
        map_ground[selected_ground].size.z -= step_size;
        map_ground[selected_ground].size.z = Clamp(map_ground[selected_ground].size.z,
                                                   1.0f, 1000.0f);
    }
    if (IsKeyPressed(KEY_D)) {
        map_ground[selected_ground].size.z += step_size;

        map_ground[selected_ground].size.z = Clamp(map_ground[selected_ground].size.z,
                                                   1.0f, 1000.0f);
    }
}
