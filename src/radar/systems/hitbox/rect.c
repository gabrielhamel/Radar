#include <engine/physics/component.h>

#include <radar/systems/hitbox.h>
#include <radar/components/hitbox.h>

bool rect_intersect_rect(entity_t *a, entity_t *b)
{
    sfVector2f shape_tested = entity_get_component_data(a, PHYSICS_COMPONENT_TYPE, physics_component_t)->position;
    sfVector2f shape_checked = entity_get_component_data(b, PHYSICS_COMPONENT_TYPE, physics_component_t)->position;

    const sfFloatRect rect_tested = (sfFloatRect){shape_tested.x, shape_tested.y, 20, 20};
    const sfFloatRect rect_checked = (sfFloatRect){shape_checked.x, shape_checked.y, 20, 20};

    return sfFloatRect_intersects(
        &rect_tested,
        &rect_checked,
        NULL
    );
}

bool rect_intersect_circle(entity_t *rect, entity_t *circle)
{
    sfVector2f aircraft_pos = entity_get_component_data(rect, PHYSICS_COMPONENT_TYPE, physics_component_t)->position;
    sfFloatRect aircraft_rect = (sfFloatRect){aircraft_pos.x, aircraft_pos.y, 20, 20};

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