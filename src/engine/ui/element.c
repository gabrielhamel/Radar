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
    elem->hover_event = NULL;
    elem->is_hovered = false;
    elem->click_event = NULL;
    elem->text_ready = false;
    elem->text = sfText_create();
    sfText_setFillColor(elem->text, sfBlack);
    elem->is_clicked = false;
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

void ui_element_set_hover_event(ui_element_t *element, state_event_t *event)
{
    element->hover_event = event;
}

void ui_element_set_click_event(ui_element_t *element, state_event_t *event)
{
    element->click_event = event;
}

void ui_element_render(ui_element_t *element, sfRenderTexture *parent_render)
{
    struct ui_element_s *it = NULL;

    sfRenderTexture_drawRectangleShape(element->render_target, element->background, NULL);
    if (element->text_ready) {
        sfRenderTexture_drawText(element->render_target, element->text, NULL);
    }
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
    bool mouse_collision = sfIntRect_contains(&bounds, mouse_pos.x, mouse_pos.y);
    bool mouse_click = sfMouse_isButtonPressed(sfMouseLeft);

    if (!element->is_hovered && element->hover_event && mouse_collision) {
        element->is_hovered = true;
        if (element->hover_event->enter) {
            element->hover_event->enter(element->hover_event->context);
        }
    } else if (element->is_hovered && element->hover_event && !mouse_collision) {
        element->is_hovered = false;
        if (element->hover_event->leave) {
            element->hover_event->leave(element->hover_event->context);
        }
    }
    if (!element->is_clicked && element->click_event && mouse_collision && mouse_click) {
        element->is_clicked = true;
        if (element->click_event->enter) {
            element->click_event->enter(element->click_event->context);
        }
    } else if (element->is_clicked && element->click_event && !(mouse_collision && mouse_click)) {
        element->is_clicked = false;
        if (element->click_event->leave) {
            element->click_event->leave(element->click_event->context);
        }
    }
    LIST_FOREACH(it, &element->children, entry) {
        ui_element_update(it, elapsed_time);
    }
}

void ui_element_set_text(ui_element_t *element, const sfUint32 *string)
{
    sfFloatRect text_box;
    unsigned int offset = 0;

    element->text_ready = true;
    sfText_setUnicodeString(element->text, string);
    do {
        sfText_setCharacterSize(element->text, element->absolute_bounds.height + offset);
        text_box = sfText_getLocalBounds(element->text);
        sfText_setPosition(element->text, (sfVector2f){-text_box.left, -text_box.top});
        offset++;
    } while (text_box.height < element->absolute_bounds.height);
    float horizontalFactor = (float)element->absolute_bounds.width / text_box.width;
    sfText_setScale(element->text, (sfVector2f){horizontalFactor, 1.f });
}

void ui_element_set_font(ui_element_t *element, sfFont *font)
{
    sfText_setFont(element->text, font);
}