#ifndef ENGINE_UI_ELEMENT_H
#define ENGINE_UI_ELEMENT_H

#include <SFML/Graphics.h>

#include "events.h"

typedef struct ui_element_t ui_element_t;

ui_element_t *ui_element_create(sfIntRect renderRectangle);
void ui_element_append_children(ui_element_t *parent, ui_element_t *child);
void ui_element_set_background_color(ui_element_t *element, sfColor color);
void ui_element_set_hover_event(ui_element_t *element, state_event_t *event);
void ui_element_set_click_event(ui_element_t *element, state_event_t *event);
void ui_element_set_text(ui_element_t *element, const sfUint32 *string);
void ui_element_set_font(ui_element_t *element, const char *filepath);
void ui_element_destroy(ui_element_t *element);

#endif // ENGINE_UI_ELEMENT_H