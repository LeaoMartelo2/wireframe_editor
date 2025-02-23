#include "editor.h"

Editor::Editor() {

    current_mode = EDITOR_MOVE;

    geometry_selected_id = 0;
};

Editor::~Editor() {};

void Editor::add_geometry(Vector3 size, Vector3 pos) {

    Geometry geometry = {
        .size = size,
        .pos = pos,
        .selected = false,
    };

    map_geometry.emplace_back(geometry);
}

void Editor::draw_map(void) {

    for (size_t i = 0; i < map_geometry.size(); ++i) {
        map_geometry[i].selected = false;
    }

    map_geometry[geometry_selected_id].selected = true;

    for (size_t i = 0; i < map_geometry.size(); ++i) {
        geometry_draw(&map_geometry[i], map_geometry[i].selected);
    }
};
