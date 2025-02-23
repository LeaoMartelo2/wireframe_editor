#include "geometry.h"
#include "../raylib/raylib.h"
#include "../raylib/raymath.h"

void draw_reference_point(void) {
    float distance = 10000.0f;

    DrawLine3D(Vector3Zero(), (Vector3){distance, 0, 0}, RED);
    DrawLine3D(Vector3Zero(), (Vector3){0, distance, 0}, GREEN);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, distance}, BLUE);
}

void geometry_draw(Geometry *geometry, bool selected) {

    if (selected) {
        DrawCubeV(geometry->pos, geometry->size, WHITE);
        DrawCubeWiresV(geometry->pos, geometry->size, GREEN);
        return;
    }

    DrawCubeV(geometry->pos, geometry->size, DARKGRAY);
    DrawCubeWiresV(geometry->pos, geometry->size, RED);
}
