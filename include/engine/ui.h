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
} ui_element_t;

ui_element_t *ui_element_create(sfIntRect renderRectangle);
void ui_element_append_children(ui_element_t *parent, ui_element_t *child);
void ui_element_render(ui_element_t *element, sfRenderTexture *parent_render);