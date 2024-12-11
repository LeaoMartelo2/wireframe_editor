#include "camera.h"

Vector3 get_camera_forward(Camera3D *camera) {

    return Vector3Normalize(Vector3Subtract(camera->target, camera->position));
}

Vector3 get_camera_up(Camera3D *camera) {

    return Vector3Normalize(camera->up);
}

Vector3 get_camera_right(Camera3D *camera) {

    Vector3 forward = get_camera_forward(camera);
    Vector3 up = get_camera_up(camera);

    return Vector3Normalize(Vector3CrossProduct(forward, up));
}

void move_camera_forward(Camera3D *camera, float distance) {
    Vector3 forward = get_camera_forward(camera);

    /*forward.y = 0;*/
    forward = (Vector3Normalize(forward));

    forward = Vector3Scale(forward, distance);

    camera->position = Vector3Add(camera->position, forward);
    camera->target = Vector3Add(camera->target, forward);
}

void move_camera_right(Camera3D *camera, float distance) {

    Vector3 right = get_camera_right(camera);

    right.y = 0;

    right = Vector3Scale(right, distance);

    camera->position = Vector3Add(camera->position, right);
    camera->target = Vector3Add(camera->target, right);
}

void move_camera_vertical(Camera3D *camera, float distance) {

    Vector3 up = get_camera_up(camera);
    up = Vector3Scale(up, distance);

    camera->position = Vector3Add(camera->position, up);
    camera->target = Vector3Add(camera->target, up);
}

void update_custom_camera(Camera3D *camera) {

    float distance = 50.0f;

    float delta_time = GetFrameTime();

    Vector2 mouse_pos_delta = GetMouseDelta();

    CameraYaw(camera, -mouse_pos_delta.x * 0.1f * delta_time, false);
    CameraPitch(camera, -mouse_pos_delta.y * 0.1f * delta_time, true, false, false);

    if (IsKeyDown(KEY_W)) {
        move_camera_forward(camera, distance * delta_time);
    }

    if (IsKeyDown(KEY_S)) {
        move_camera_forward(camera, -distance * delta_time);
    }

    if (IsKeyDown(KEY_A)) {
        move_camera_right(camera, -distance * delta_time);
    }

    if (IsKeyDown(KEY_D)) {
        move_camera_right(camera, distance * delta_time);
    }

    if (IsKeyDown(KEY_SPACE)) {
        move_camera_vertical(camera, distance * delta_time);
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        move_camera_vertical(camera, -distance * delta_time);
    }
}
