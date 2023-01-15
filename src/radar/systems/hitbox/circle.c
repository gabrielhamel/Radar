#include <engine/tools/maths.h>

#include <radar/systems/hitbox.h>
#include <radar/components/hitbox.h>
#include <radar/components/position.h>

bool point_intersect_circle(entity_t *circle, sfVector2f point)
{
    sfVector2f tower_pos = entity_get_component_data(circle, POSITION_COMPONENT_TYPE, position_component_t)->position;
    hitbox_component_t *hitbox = entity_get_component_data(circle, HITBOX_COMPONENT_TYPE, hitbox_component_t);

    // Compute distance to tower
    sfVector2f vector = {
        .x = fabsf(point.x - tower_pos.x),
        .y = fabsf(point.y - tower_pos.y),
    };
    float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
    return distance <= hitbox->radius;
}