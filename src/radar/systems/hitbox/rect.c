#include <radar/systems/hitbox.h>

bool rect_intersect_rect(hitbox_component_t *a, hitbox_component_t *b)
{
    sfRectangleShape *shape_tested = a->csfml_object;
    sfRectangleShape *shape_checked = b->csfml_object;

    const sfFloatRect rect_tested = sfRectangleShape_getGlobalBounds(shape_tested);
    const sfFloatRect rect_checked = sfRectangleShape_getGlobalBounds(shape_checked);

    return sfFloatRect_intersects(
            &rect_tested,
            &rect_checked,
            NULL
    );
}

bool rect_intersect_circle(hitbox_component_t *rect, hitbox_component_t *circle)
{
    sfRectangleShape *aircraft_shape = rect->csfml_object;
    sfFloatRect aircraft_rect = sfRectangleShape_getGlobalBounds(aircraft_shape);

    if (point_intersect_circle(circle, (sfVector2f){aircraft_rect.left, aircraft_rect.top})) {
        return true;
    }
    if (point_intersect_circle(circle, (sfVector2f){aircraft_rect.left + aircraft_rect.width, aircraft_rect.top})) {
        return true;
    }
    if (point_intersect_circle(circle, (sfVector2f){aircraft_rect.left, aircraft_rect.top + aircraft_rect.height})) {
        return true;
    }
    if (point_intersect_circle(circle, (sfVector2f){aircraft_rect.left + aircraft_rect.width,
                                                          aircraft_rect.top + aircraft_rect.height})) {
        return true;
    }
    return false;
}