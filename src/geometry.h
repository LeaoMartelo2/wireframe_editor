#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void draw_reference_point(void);

typedef struct Geometry {
    Vector3 size;
    Vector3 pos;
    bool selected;
    bool empty;
} Geometry;

void geometry_draw(Geometry *geometry, bool selected);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !GEOMETRY_H_
