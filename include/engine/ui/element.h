#ifndef UI_H
#define UI_H

#include <SFML/Graphics.h>
#include <stdbool.h>

#include "engine/queue.h"
#include "engine/events.h"
#include "events.h"

typedef struct ui_element_s {
    TAILQ_ENTRY(ui_element_s) entry;
    TAILQ_HEAD(, ui_element_s) children;
    sfRenderTexture *render_target;
    sfTexture *render_texture;
    sfSprite *render_sprite;
    sfRectangleShape *background;
    sfText *text;
    sfFont *font;
    bool text_ready;
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
void ui_element_set_text(ui_element_t *element, const sfUint32 *string);
void ui_element_set_font(ui_element_t *element, const char *filepath);
void ui_element_update(ui_element_t *element, sfTime *elapsed_time);
void ui_element_destroy(ui_element_t *element);

#endif // UI_H