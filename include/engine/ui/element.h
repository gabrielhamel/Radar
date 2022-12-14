#ifndef UI_H
#define UI_H

#include <SFML/Graphics.h>
#include <stdbool.h>

#include "engine/queue.h"
#include "engine/events.h"
#include "events.h"

typedef struct ui_element_s {
    LIST_ENTRY(ui_element_s) entry;
    LIST_HEAD(, ui_element_s) children;
    sfRenderTexture *render_target;
    sfTexture *render_texture;
    sfSprite *render_sprite;
    sfRectangleShape *background;
    state_event_t *hover_event;
    bool is_hovered;
    state_event_t *click_event;
    bool is_clicked;
    sfIntRect absolute_bounds;
} ui_element_t;

ui_element_t *ui_element_create(sfIntRect renderRectangle);
void ui_element_append_children(ui_element_t *parent, ui_element_t *child);
void ui_element_render(ui_element_t *element, sfRenderTexture *parent_render);
void ui_element_set_background_color(ui_element_t *element, sfColor color);
void ui_element_set_hover_event(ui_element_t *element, state_event_t *event);
void ui_element_set_click_event(ui_element_t *element, state_event_t *event);
void ui_element_update(ui_element_t *element, sfTime *elapsed_time);

#endif // UI_H