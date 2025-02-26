#include "editor.h"
#include "camera.h"
#include "geometry.h"
#include "global.h"
#include "include/raywire.h"
#include <math.h>

Editor::Editor() {

    add_geometry({10, 10, 10}, {0, 5, 0});
    add_ground({1000, 1, 1000}, {0, -1, 0});
    add_ground({10, 1, 10}, {0, 10, 0});

    gui_theme.colors.default_color = GetColor(0x181818FF);
    gui_theme.colors.hoovered_color = LIGHTGRAY;
    gui_theme.colors.pressed_color = DARKGRAY;
    gui_theme.colors.text_color = WHITE;

    current_mode = EDITOR_GEOMETRY;

    geometry_selected_id = 0;
    ground_selected_id = 0;
};

Editor::~Editor() {};

void Editor::load(void) {

    gui_theme.text.font = LoadFontEx("assets/vollkorn.regular.ttf", 100, NULL, 250);
    /*gui_theme.text.font = LoadFont("assets/vollkorn.regular.ttf");*/

    alt_font = LoadFontEx("assets/Iosevka-Light.ttf", 100, NULL, 250);
}

void Editor::unload(void) {

    rw_free_theme(&gui_theme);
}

void Editor::update(void) {

    for (size_t i = 0; i < map_geometry.size(); ++i) {
        map_geometry[i].selected = false;
    }

    for (size_t i = 0; i < map_ground.size(); ++i) {
        map_ground[i].selected = false;
    }

    static bool move_toggled = false;

    hud_toggle = !move_toggled;

    if (move_toggled) {
        hud_toggle = false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        if (!move_toggled) {
            DisableCursor();
            move_toggled = true;
        }
    }

    if (move_toggled) {
        update_custom_camera(camera_ptr);
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            EnableCursor();
            move_toggled = false;
        }
    }

    switch (current_mode) {

    case EDITOR_GEOMETRY:

        if (IsKeyPressed(KEY_F)) {

            add_geometry({10, 10, 10},
                         {round(camera_ptr->position.x),
                          round(camera_ptr->position.y),
                          round(camera_ptr->position.z)});
        }

        break;

    case EDITOR_GROUND:

        if (IsKeyPressed(KEY_F)) {

            add_ground({10, 1, 10},
                       {round(camera_ptr->position.x),
                        round(camera_ptr->position.y),
                        round(camera_ptr->position.z)});
        }

        break;
    };
};

void Editor::geometry_dialogue(void) {

    DrawText("\n'1'\n'2'\n'3'\n\n'Q'\n'W'\n'E'", 200, 250, 20, WHITE);

    DrawText("Keybinds:\nF - Add geometry\nDel - Delete geometry\nLShift - invert action\n"
             "RCtrl - 10x action\n"
             "RClick - camera mode\n"
             "A & D - Cycle selection\n"
             "WASD - move in\ncamera mode",
             5, 450, 20, WHITE);

    return;
}

void Editor::add_geometry(Vector3 size, Vector3 pos) {

    size_t empty_index = 0;

    for (size_t i = 0; i < map_geometry.size(); ++i) {
        if (map_geometry[i].empty) {
            empty_index = i;
        }
    }

    if (empty_index > 0) {
        Geometry geometry = {
            .size = size,
            .pos = pos,
            .selected = false,
            .empty = false,
        };

        map_geometry[empty_index] = geometry;
    } else {

        Geometry geometry = {
            .size = size,
            .pos = pos,
            .selected = false,
            .empty = false,
        };

        map_geometry.emplace_back(geometry);
    }
}

void Editor::remove_geometry(void) {
    map_geometry[geometry_selected_id].empty = true;
}

void Editor::edit_geometry(size_t id) {

    float step = 10.0f;

    float pos_step = 1.0f;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        step *= -1;
        pos_step *= -1;
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        step *= 10;
        pos_step *= 10;
    }

    if (IsKeyPressedRepeat(KEY_ONE) | IsKeyPressed(KEY_ONE)) {
        if (map_geometry[id].size.x + step > 0)
            map_geometry[id].size.x += step;
    }
    if (IsKeyPressedRepeat(KEY_TWO) | IsKeyPressed(KEY_TWO)) {
        if (map_geometry[id].size.y + step > 0)
            map_geometry[id].size.y += step;
    }
    if (IsKeyPressedRepeat(KEY_THREE) | IsKeyPressed(KEY_THREE)) {
        if (map_geometry[id].size.z + step > 0)
            map_geometry[id].size.z += step;
    }

    if (IsKeyPressedRepeat(KEY_Q) | IsKeyPressed(KEY_Q)) {
        map_geometry[id].pos.x += pos_step;
    }
    if (IsKeyPressedRepeat(KEY_W) | IsKeyPressed(KEY_W)) {
        map_geometry[id].pos.y += pos_step;
    }
    if (IsKeyPressedRepeat(KEY_E) | IsKeyPressed(KEY_E)) {
        map_geometry[id].pos.z += pos_step;
    }
}

void Editor::ground_dialogue(void) {

    DrawText("\n'1'\n   \n'3'\n\n'Q'\n'W'\n'E'", 200, 250, 20, WHITE);

    DrawText("Keybinds:\nF - Add ground\nDel - Delete ground\nLShift - invert action\n"
             "RCtrl - 10x action\n"
             "RClick - camera mode\n"
             "A & D - Cycle selection\n"
             "WASD - move in\ncamera mode",
             5, 450, 20, WHITE);

    return;
}

void Editor::add_ground(Vector3 size, Vector3 pos) {

    size_t empty_index = 0;

    for (size_t i = 0; i < map_ground.size(); ++i) {
        if (map_ground[i].empty) {
            empty_index = i;
        }
    }

    if (empty_index > 0) {
        Ground ground = {
            .size = size,
            .pos = pos,
            .selected = false,
            .empty = false,
        };

        map_ground[empty_index] = ground;
    } else {

        Ground ground = {
            .size = size,
            .pos = pos,
            .selected = false,
            .empty = false,
        };

        map_ground.emplace_back(ground);
    }
}

void Editor::remove_ground(void) {
    map_ground[ground_selected_id].empty = true;
}

void Editor::edit_ground(size_t id) {

    float step = 10.0f;

    float pos_step = 1.0f;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        step *= -1;
        pos_step *= -1;
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        step *= 10;
        pos_step *= 10;
    }

    if (IsKeyPressedRepeat(KEY_ONE) | IsKeyPressed(KEY_ONE)) {
        if (map_ground[id].size.x + step > 0)
            map_ground[id].size.x += step;
    }
    /*if (IsKeyPressedRepeat(KEY_TWO) | IsKeyPressed(KEY_TWO)) {*/
    /*if (map_ground[id].size.y + step > 0)*/
    /*map_ground[id].size.y += step;*/
    /*}*/
    if (IsKeyPressedRepeat(KEY_THREE) | IsKeyPressed(KEY_THREE)) {
        if (map_ground[id].size.z + step > 0)
            map_ground[id].size.z += step;
    }

    if (IsKeyPressedRepeat(KEY_Q) | IsKeyPressed(KEY_Q)) {
        map_ground[id].pos.x += pos_step;
    }

    if (IsKeyPressedRepeat(KEY_W) | IsKeyPressed(KEY_W)) {
        map_ground[id].pos.y += pos_step;
    }
    if (IsKeyPressedRepeat(KEY_E) | IsKeyPressed(KEY_E)) {
        map_ground[id].pos.z += pos_step;
    }
}

void Editor::draw_map(void) {

    map_geometry[geometry_selected_id].selected = true;

    for (size_t i = 0; i < map_geometry.size(); ++i) {
        if (!map_geometry[i].empty) {
            geometry_draw(&map_geometry[i], map_geometry[i].selected, current_mode);
        }
    }

    map_ground[ground_selected_id].selected = true;

    for (size_t i = 0; i < map_ground.size(); ++i) {
        if (!map_ground[i].empty) {
            ground_draw(&map_ground[i], map_ground[i].selected, current_mode);
        }
    }
}

void Editor::draw_hud(void) {

    float width = GetScreenWidth();
    float height = GetScreenHeight();

    if (hud_toggle) {
        Rectangle window_border = {
            .x = width / 2 - width / 2 + 245,
            .y = height / 2 - height / 2 + 55,
            .width = width - 250,
            .height = height - 60,
        };

        DrawRectangleRoundedLinesEx(window_border, 0.1, 10, 500, ColorAlpha(DARKGRAY, 1.15));

        static rw_button_create(editor_type,
                                35,
                                RW_ROUNDED,
                                &gui_theme,
                                280, 40,
                                width / 2 - 7,
                                5);

        static rw_button_create(ground_to_geometry, 20, RW_ROUNDED, &gui_theme, 200, 40, width / 4, 5);

        static rw_button_create(geometry_selected_inc,
                                50,
                                RW_ROUNDED,
                                &gui_theme,
                                50, 50,
                                25,
                                50);

        static rw_button_create(geometry_selected_dec,
                                50,
                                RW_ROUNDED,
                                &gui_theme,
                                50, 50,
                                135,
                                50);

        static rw_button_create(delete_geometry, 30, RW_ROUNDED,
                                &gui_theme, 60, 45, 120, 120);

        static rw_button_create(create_geometry, 30, RW_ROUNDED,
                                &gui_theme, 60, 45, 30, 120);

        static rw_button_create(move_geometry, 30, RW_ROUNDED,
                                &gui_theme, 200, 45, 25, 180);

        switch (current_mode) {

        case EDITOR_GEOMETRY:

            if (rw_button(&editor_type, "Geometry mode")) {
                current_mode = (current_mode + 1) % EDITOR_TYPES_TOTAL;
            }

            if (rw_button(&ground_to_geometry, "Add Ground to Geometry")) {
                size_t i = geometry_selected_id;
                add_ground({
                               map_geometry[i].size.x,
                               1.0f,
                               map_geometry[i].size.z,
                           },
                           {map_geometry[i].pos.x,

                            map_geometry[i].pos.y + map_geometry[i].size.y / 2,

                            map_geometry[i].pos.z});
            }

            if (rw_button(&geometry_selected_inc, "<")) {
                if (geometry_selected_id > 0)
                    geometry_selected_id--;
            }

            if (IsKeyPressed(KEY_A)) {
                if (geometry_selected_id > 0)
                    geometry_selected_id--;
            }

            if (rw_button(&geometry_selected_dec, ">")) {
                if (geometry_selected_id < map_geometry.size() - 1)
                    geometry_selected_id++;
            }

            if (IsKeyPressed(KEY_D)) {
                if (geometry_selected_id < map_geometry.size() - 1)
                    geometry_selected_id++;
            }

            DrawTextEx(alt_font,
                       TextFormat("%zu", geometry_selected_id),
                       {90, 55},
                       40, 1, WHITE);

            DrawTextEx(alt_font,
                       "Selected Geometry",
                       {20, 20},
                       30, 1, WHITE);

            if (rw_button(&delete_geometry, "Del")) {
                remove_geometry();
            }

            if (IsKeyPressed(KEY_DELETE)) {
                remove_geometry();
            }

            if (rw_button(&create_geometry, "Add")) {
                add_geometry({10, 10, 10},
                             {round(camera_ptr->position.x),
                              round(camera_ptr->position.y),
                              round(camera_ptr->position.z)});
            }

            if (rw_button(&move_geometry, "Move to camera")) {
                map_geometry[geometry_selected_id].pos.x = (int)camera_ptr->position.x;
                map_geometry[geometry_selected_id].pos.y = (int)camera_ptr->position.y;
                map_geometry[geometry_selected_id].pos.z = (int)camera_ptr->position.z;
            }

            DrawText(TextFormat("Size:\nX:%.2f\nY:%.2f\nZ:%.2f\n"
                                "Pos :\nX:%.2f\nY:%.2f\nZ:%.2f\n",
                                map_geometry[geometry_selected_id].size.x,
                                map_geometry[geometry_selected_id].size.y,
                                map_geometry[geometry_selected_id].size.z,
                                map_geometry[geometry_selected_id].pos.x,
                                map_geometry[geometry_selected_id].pos.y,
                                map_geometry[geometry_selected_id].pos.z),
                     15, 250, 20, WHITE);

            edit_geometry(geometry_selected_id);

            geometry_dialogue();

            break;

        case EDITOR_GROUND:

            if (rw_button(&editor_type, "Ground mode")) {
                current_mode = (current_mode + 1) % EDITOR_TYPES_TOTAL;
            }

            if (rw_button(&geometry_selected_inc, "<")) {
                if (ground_selected_id > 0)
                    ground_selected_id--;
            }

            if (IsKeyPressed(KEY_A)) {
                if (ground_selected_id > 0)
                    ground_selected_id--;
            }

            if (rw_button(&geometry_selected_dec, ">")) {
                if (ground_selected_id < map_ground.size() - 1)
                    ground_selected_id++;
            }

            if (IsKeyPressed(KEY_D)) {
                if (ground_selected_id < map_ground.size() - 1)
                    ground_selected_id++;
            }

            DrawTextEx(alt_font,
                       TextFormat("%zu", ground_selected_id),
                       {90, 55},
                       40, 1, WHITE);

            DrawTextEx(alt_font,
                       "Selected Ground",
                       {20, 20},
                       30, 1, WHITE);

            if (rw_button(&delete_geometry, "Del")) {
                remove_ground();
            }

            if (IsKeyPressed(KEY_DELETE)) {
                remove_ground();
            }

            if (rw_button(&create_geometry, "Add")) {
                add_ground({10, 10, 10},
                           {round(camera_ptr->position.x),
                            round(camera_ptr->position.y),
                            round(camera_ptr->position.z)});
            }

            if (rw_button(&move_geometry, "Move to camera")) {
                map_ground[ground_selected_id].pos.x = (int)camera_ptr->position.x;
                map_ground[ground_selected_id].pos.y = (int)camera_ptr->position.y;
                map_ground[ground_selected_id].pos.z = (int)camera_ptr->position.z;
            }

            DrawText(TextFormat("Size:\nX:%.2f\n\nZ:%.2f\n"
                                "Pos :\nX:%.2f\nY:%.2f\nZ:%.2f\n",
                                map_ground[ground_selected_id].size.x,
                                /*map_ground[ground_selected_id].size.y,*/
                                map_ground[ground_selected_id].size.z,
                                map_ground[ground_selected_id].pos.x,
                                map_ground[ground_selected_id].pos.y,
                                map_ground[ground_selected_id].pos.z),
                     15, 250, 20, WHITE);

            edit_ground(ground_selected_id);

            ground_dialogue();

            break;
        }
    }
}
