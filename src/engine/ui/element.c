#include <stdlib.h>

#include "engine/ui/element.h"
#include "engine/engine.h"

ui_element_t *ui_element_create(sfIntRect renderRectangle)
{
    ui_element_t *elem = malloc(sizeof(ui_element_t));

    LIST_INIT(&elem->children);
    elem->render_target = sfRenderTexture_createWithSettings(renderRectangle.width, renderRectangle.height, NULL);
    elem->render_texture = (sfTexture *)sfRenderTexture_getTexture(elem->render_target);
    elem->render_sprite = sfSprite_create();
    elem->background = sfRectangleShape_create();
    elem->on_hover = NULL;
    elem->hover_context = NULL;
    elem->is_hovered = false;
    elem->absolute_bounds = renderRectangle;
    sfRectangleShape_setPosition(elem->background, (sfVector2f){0, 0});
    sfRectangleShape_setSize(elem->background, (sfVector2f){renderRectangle.width, renderRectangle.height});
    sfRectangleShape_setFillColor(elem->background, sfTransparent);
    sfSprite_setTexture(elem->render_sprite, elem->render_texture, sfTrue);
    sfSprite_setPosition(elem->render_sprite, (sfVector2f){renderRectangle.left, renderRectangle.top});
    return elem;
}

void ui_element_append_children(ui_element_t *parent, ui_element_t *child)
{
    sfIntRect parent_bounds = parent->absolute_bounds;
    sfVector2f child_pos = sfSprite_getPosition(child->render_sprite);

    child->absolute_bounds = (sfIntRect){ parent_bounds.left + child_pos.x, parent_bounds.top + child_pos.y,
                                          child->absolute_bounds.width, child->absolute_bounds.height };
    LIST_INSERT_HEAD(&parent->children, child, entry);
}

void ui_element_set_background_color(ui_element_t *element, sfColor color)
{
    sfRectangleShape_setFillColor(element->background, color);
}

void ui_element_set_hover_behavior(ui_element_t *element, void (*on_hover)(void *context), void (*on_leave)(void *context), void *context)
{
    element->on_hover = on_hover;
    element->on_leave = on_leave;
    element->hover_context = context;
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

void ui_element_update(ui_element_t *element, sfTime *elapsed_time)
{
    struct ui_element_s *it = NULL;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(engine_get()->window);
    sfIntRect bounds = element->absolute_bounds;

    if (sfIntRect_contains(&bounds, mouse_pos.x, mouse_pos.y) == sfTrue) {
        element->is_hovered = true;
        if (element->on_hover) {
            element->on_hover(element->hover_context);
        }
    } else if (element->is_hovered) {
        element->is_hovered = false;
        if (element->on_leave) {
            element->on_leave(element->hover_context);
        }
    }

    LIST_FOREACH(it, &element->children, entry) {
        ui_element_update(it, elapsed_time);
    }
}