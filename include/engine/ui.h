#ifndef UI_H
#define UI_H

#include <SFML/Graphics.h>
#include <stdbool.h>

#include "queue.h"

typedef struct ui_element_s {
    LIST_ENTRY(ui_element_s) entry;
    LIST_HEAD(, ui_element_s) children;
    sfRenderTexture *render_target;
    sfTexture *render_texture;
    sfSprite *render_sprite;
    sfRectangleShape *background;
    void (*on_hover)(void *context);
    void *hover_context;
} ui_element_t;

ui_element_t *ui_element_create(sfIntRect renderRectangle);
void ui_element_append_children(ui_element_t *parent, ui_element_t *child);
void ui_element_render(ui_element_t *element, sfRenderTexture *parent_render);
void ui_element_set_background_color(ui_element_t *element, sfColor color);
void ui_element_set_hover_behavior(ui_element_t *element, void (*on_hover)(void *context), void *context);
void ui_element_update(ui_element_t *element, sfTime *elapsed_time);

#endif // UI_H