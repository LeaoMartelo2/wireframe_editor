#include "editor.h"
#include "camera.h"
#include "include/raywire.h"

Editor::Editor() {

    gui_theme.colors.default_color = GetColor(0x181818FF);
    gui_theme.colors.hoovered_color = LIGHTGRAY;
    gui_theme.colors.pressed_color = DARKGRAY;
    gui_theme.colors.text_color = WHITE;

    current_mode = EDITOR_GEOMETRY;

    geometry_selected_id = 0;
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

        break;

    case EDITOR_GROUND:

        break;
    };
};

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

void Editor::draw_map(void) {

    map_geometry[geometry_selected_id].selected = true;

    for (size_t i = 0; i < map_geometry.size(); ++i) {
        if (!map_geometry[i].empty) {
            geometry_draw(&map_geometry[i], map_geometry[i].selected);
        }
    }
};

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

        DrawRectangleRoundedLinesEx(window_border, 0.1, 10, 500, ColorAlpha(WHITE, 0.15));

        switch (current_mode) {

        case EDITOR_GEOMETRY:

            static rw_button_create(editor_type,
                                    35,
                                    RW_ROUNDED,
                                    &gui_theme,
                                    280, 40,
                                    width / 2 - 7,
                                    5);

            if (rw_button(&editor_type, "Geometry mode")) {
                current_mode = (current_mode + 1) % EDITOR_TYPES_TOTAL;
            }

            static rw_button_create(geometry_selected_inc,
                                    50,
                                    RW_ROUNDED,
                                    &gui_theme,
                                    50, 50,
                                    25,
                                    50);

            if (rw_button(&geometry_selected_inc, "<")) {
                if (geometry_selected_id > 0) {
                    geometry_selected_id--;
                }
            }

            static rw_button_create(geometry_selected_dec,
                                    50,
                                    RW_ROUNDED,
                                    &gui_theme,
                                    50, 50,
                                    135,
                                    50);

            if (rw_button(&geometry_selected_dec, ">")) {
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

            break;

        case EDITOR_GROUND:

            if (rw_button(&editor_type, "Ground mode")) {
                current_mode = (current_mode + 1) % EDITOR_TYPES_TOTAL;
            }

            break;
        }
    }
}
