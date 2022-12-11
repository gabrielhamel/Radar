#include <stdlib.h>

#include "engine/ui.h"

ui_element_t *ui_element_create(sfIntRect renderRectangle)
{
    ui_element_t *elem = malloc(sizeof(ui_element_t));

    LIST_INIT(&elem->children);
    elem->render_target = sfRenderTexture_createWithSettings(renderRectangle.width, renderRectangle.height, NULL);
    elem->render_texture = (sfTexture *)sfRenderTexture_getTexture(elem->render_target);
    elem->render_sprite = sfSprite_create();
    elem->background = sfRectangleShape_create();
    sfRectangleShape_setPosition(elem->background, (sfVector2f){0, 0});
    sfRectangleShape_setSize(elem->background, (sfVector2f){renderRectangle.width, renderRectangle.height});
    sfRectangleShape_setFillColor(elem->background, sfTransparent);
    sfSprite_setTexture(elem->render_sprite, elem->render_texture, sfTrue);
    sfSprite_setPosition(elem->render_sprite, (sfVector2f){renderRectangle.left, renderRectangle.top});
    return elem;
}

void ui_element_append_children(ui_element_t *parent, ui_element_t *child)
{
    LIST_INSERT_HEAD(&parent->children, child, entry);
}

void ui_element_render(ui_element_t *element, sfRenderTexture *parent_render)
{
    struct ui_element_s *it = NULL;

    sfRenderTexture_drawRectangleShape(element->render_target, element->background, NULL);
    LIST_FOREACH(it, &element->children, entry) {
        ui_element_render(it, element->render_target);
    }
    sfRenderTexture_display(element->render_target);
    sfRenderTexture_drawSprite(parent_render, element->render_sprite, NULL);
}