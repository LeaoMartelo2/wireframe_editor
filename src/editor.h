#ifndef _EDITOR_H
#define _EDITOR_H

#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "geometry.h"
#include "include/raywire.h"
#include <vector>

typedef enum {
    EDITOR_GROUND,
    EDITOR_GEOMETRY,
    EDITOR_TYPES_TOTAL,
} EditorType;

class Editor {

  public:
    std::vector<Geometry> map_geometry;

    int current_mode;
    Camera3D *camera_ptr;

    bool hud_toggle;
    rw_theme_t gui_theme;
    Font alt_font;

    size_t geometry_selected_id;
    size_t floor_selected_id;

    Editor();
    ~Editor();

    void load(void);
    void unload(void);

    void update(void);

    void add_geometry(Vector3 size, Vector3 pos);
    void remove_geometry(void);

    void draw_map(void);
    void draw_hud(void);
};

#endif // !_EDITOR_H
