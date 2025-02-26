#include "geometry.h"
#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "global.h"

void draw_reference_point(void) {
    float distance = 10000.0f;

    DrawLine3D(Vector3Zero(), (Vector3){distance, 0, 0}, RED);
    DrawLine3D(Vector3Zero(), (Vector3){0, distance, 0}, GREEN);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, distance}, BLUE);
}

void geometry_draw(Geometry *geometry, bool selected, int editor_mode) {

    if (editor_mode == EDITOR_GEOMETRY) {

        if (selected) {
            DrawCubeV(geometry->pos, geometry->size, WHITE);
            DrawCubeWiresV(geometry->pos, geometry->size, GREEN);
            return;
        }
    }

    DrawCubeV(geometry->pos, geometry->size, DARKGRAY);
    DrawCubeWiresV(geometry->pos, geometry->size, RED);
}

void ground_draw(Ground *ground, bool selected, int editor_mode) {

    if (editor_mode == EDITOR_GROUND) {

        if (selected) {
            DrawCubeV(ground->pos, ground->size, ColorTint(GetColor(0x181818FF), DARKGREEN));
            DrawCubeWiresV(ground->pos, ground->size, GREEN);
            return;
        }
    }

    DrawCubeV(ground->pos, ground->size, GetColor(0x181818FF));
    DrawCubeWiresV(ground->pos, ground->size, RED);
}
