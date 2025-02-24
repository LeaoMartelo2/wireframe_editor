#include "include/raywire.h"

rw_theme_t transparent_theme = {
    .colors = {0},
    .text = {0},
};

void rw_free_theme(rw_theme_t *theme) {
    UnloadFont(theme->text.font);
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
