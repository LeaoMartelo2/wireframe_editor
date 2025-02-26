#ifndef _EDITOR_H
#define _EDITOR_H

#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "geometry.h"
#include "include/json.hpp"
#include "include/raywire.h"
#include <vector>

class Editor {

  public:
    std::vector<Geometry> map_geometry;
    std::vector<Ground> map_ground;

    int current_mode;
    Camera3D *camera_ptr;

    bool hud_toggle;
    rw_theme_t gui_theme;
    Font alt_font;

    size_t geometry_selected_id;
    size_t ground_selected_id;

    Editor();
    ~Editor();

    void load(void);
    void unload(void);

    void update(void);

    void geometry_dialogue(void);
    void add_geometry(Vector3 size, Vector3 pos);
    void remove_geometry(void);
    void edit_geometry(size_t id);

    void ground_dialogue(void);
    void add_ground(Vector3 size, Vector3 pos);
    void remove_ground(void);
    void edit_ground(size_t id);

    void draw_map(void);
    void draw_hud(void);

    void to_json(nlohmann::json &j, const Vector3 &v);
    void from_json(const nlohmann::json &j, Vector3 &v);

    nlohmann::json output_json(void);
    void save_json(const std::string &filename);

    void export_map();
};

#endif // !_EDITOR_H
