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
            DrawCubeV(ground->pos, ground->size, ColorTint(GetColor(0x181818FF), GREEN));
            DrawCubeWiresV(ground->pos, ground->size, GREEN);
            return;
        }
    }

    DrawCubeV(ground->pos, ground->size, GetColor(0x181818FF));
    DrawCubeWiresV(ground->pos, ground->size, RED);
}

void spawnpoint_draw(SpawnPoint *sp) {

    Vector3 player_size = {5, 15, 5};

    // player size
    DrawCubeWiresV(sp->pos, player_size, ORANGE);

    // point where is looking
    DrawCubeWires(sp->looking_at, 1, 1, 1, WHITE);

    Vector3 camera_pos = Vector3Add(sp->pos, (Vector3){0, 7, 0});

    // camera position
    DrawCube(camera_pos, 1, 1, 1, ORANGE);

    // line from player's size to camera

    DrawLine3D(sp->pos, camera_pos, ORANGE);

    // line from camera to looking_at
    DrawLine3D(camera_pos, sp->looking_at, WHITE);
}
