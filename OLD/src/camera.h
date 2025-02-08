#ifndef CAMERA_H_
#define CAMERA_H_

#include "../raylib/raylib.h"
#include "../raylib/raymath.h"
#include "../raylib/rcamera.h"

Vector3 get_camera_forward(Camera3D *camera);
Vector3 get_camera_up(Camera3D *camera);
Vector3 get_camera_right(Camera3D *camera);

void move_camera_forward(Camera3D *camera, float distance);
void move_camera_right(Camera3D *camera, float distance);
void move_camera_vertical(Camera3D *camera, float distance);

void update_custom_camera(Camera3D *camera);

#endif // !CAMERA_H_
