/*
 * The library needs to be linked with the same raylib as your main application
 * to prevent some weird linker errors
 */

/* REPLACE WITH YOUR RAYLIB PATH IF NEEDED */
#include "../../raylib/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _RW_H
#define _RW_H

#ifdef __cplusplus
extern "C" {
#endif //  __cplusplus

typedef enum {
    RW_SQUARE = 1 << 0,  // 0001
    RW_ROUNDED = 1 << 1, // 0010
    RW_OUTLINE = 1 << 2, // 0100
} rw_button_style_t;

typedef struct {

    struct {
        Color default_color;
        Color hoovered_color;
        Color pressed_color;
        Color text_color;
    } colors;

    struct {
        Font font;
    } text;

} rw_theme_t;

#define rw_theme_create(name, default, hoovered, pressed, text_color_, text_font_) \
    rw_theme_t name = {                                                            \
        .colors.default_color = default,                                           \
        .colors.hoovered_color = hoovered,                                         \
        .colors.pressed_color = pressed,                                           \
        .colors.text_color = text_color_,                                          \
        .text.font = text_font_,                                                   \
    };

void rw_free_theme(rw_theme_t *theme);

extern rw_theme_t transparent_theme;

typedef struct {
    Rectangle bounds;
    int button_style;
    int font_size;
    rw_theme_t *theme;
} rw_button_t;

#define rw_button_create(name, font_size_, style, theme_ref, width_, height_, posX, posY) \
    rw_button_t name = {                                                                  \
        .bounds = {                                                                       \
            .x = posX,                                                                    \
            .y = posY,                                                                    \
            .width = width_,                                                              \
            .height = height_,                                                            \
        },                                                                                \
        .button_style = style,                                                            \
        .font_size = font_size_,                                                          \
        .theme = theme_ref,                                                               \
    };

int rw_button(rw_button_t *button, const char *text);

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef RAYWIRE_IMPLEMENTATION

rw_theme_t transparent_theme = {
    .colors = {0},
    .text = {0},
};

void rw_free_theme(rw_theme_t *theme) {
    UnloadFont(theme->text.font);
    memset(theme, 0, sizeof(*theme));
}

int rw_button(rw_button_t *button, const char *text) {

    int result = 0;

    Color current_color = button->theme->colors.default_color;

    Vector2 mouse_pos = GetMousePosition();

    if (CheckCollisionPointRec(mouse_pos, button->bounds)) {

        current_color = button->theme->colors.hoovered_color;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            current_color = button->theme->colors.pressed_color;
        } else {
            current_color = button->theme->colors.hoovered_color;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            result = 1;
        }
    } else {
        current_color = button->theme->colors.default_color;
    }

    switch (button->button_style) {

    case RW_SQUARE:
        DrawRectangleRec(button->bounds, current_color);
        break;

    case RW_ROUNDED:
        DrawRectangleRounded(button->bounds, 0.5, 5, current_color);
        break;

    case RW_SQUARE | RW_OUTLINE:
        DrawRectangleLinesEx(button->bounds, 1, current_color);
        break;

    case RW_ROUNDED | RW_OUTLINE:
        DrawRectangleRoundedLinesEx(button->bounds, 0.5, 10, 0.5, current_color);
        break;

    default:
        printf("Invalid button style\n");
        exit(1);
        break;
    }

    if (text != NULL) {

        Vector2 text_size = MeasureTextEx(button->theme->text.font, text, button->font_size, 1);

        float text_x = button->bounds.x + (button->bounds.width / 2.0f) - (text_size.x / 2.0f);

        float text_y = button->bounds.y + button->bounds.height / 2.0f - text_size.y / 2.0f;

        DrawTextEx(button->theme->text.font,
                   text,
                   (Vector2){text_x, text_y},
                   button->font_size,
                   1,
                   button->theme->colors.text_color);
    }

    return result;
}

#endif // RAYWIRE_IMPLEMENTATION

#endif // _RW_H
