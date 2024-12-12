#ifndef EDITOR_H_
#define EDITOR_H_

#include "../raylib/raygui.h"
#include "../raylib/raylib.h"
#include "../raylib/raymath.h"

#define MAX_GEOMETRY 100
#define MAX_GROUND 100

typedef enum {
    EDITOR_GEOMETRY,
    EDITOR_GROUND,
    EDITOR_PROPS,
    EDITOR_COUNT
} EditorType;

typedef struct Geometry {
        Vector3 pos;
        Vector3 size;
        bool active;
        int see_through;
        bool selected;
} Geometry;

typedef struct Ground {
        Vector3 pos;
        Vector3 size;
        bool active;
        bool selected;
} Ground;

float snap_to_gridf(float value);

void draw_static_gui(float *step_size, int *gui_type);

void draw_geometry_gui(int *selected_geometry, int *geometry_ammount,
                       Geometry *map_geometry, Camera3D camera, float step_size);
void edit_geometry(Geometry *map_geometry, int selected_geometry, float step_size);

void draw_ground_gui(int *selected_ground, int *ground_ammount,
                     Ground *map_ground, Camera3D camera, float step_size);
void edit_ground(Ground *map_ground, int selected_ground, float step_size);

#endif // !EDITOR_H_
