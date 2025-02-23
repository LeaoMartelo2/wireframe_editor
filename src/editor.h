#ifndef _EDITOR_H
#define _EDITOR_H

#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "geometry.h"
#include <vector>

typedef enum {
    EDITOR_MOVE,
    EDITOR_GROUND,
    EDITOR_GEOMETRY,
} EditorType;

class Editor {

  public:
    std::vector<Geometry> map_geometry;

    int current_mode;

    size_t geometry_selected_id;
    size_t floor_selected_id;

    Editor();
    ~Editor();

    void add_geometry(Vector3 size, Vector3 pos);

    void draw_map(void);
};

#endif // !_EDITOR_H
