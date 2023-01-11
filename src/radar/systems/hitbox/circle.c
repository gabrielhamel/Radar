#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include <radar/systems/hitbox.h>

bool point_intersect_circle(hitbox_component_t *circle, sfVector2f point)
{
    sfCircleShape *tower_shape = circle->csfml_object;
    float tower_radius = sfCircleShape_getRadius(tower_shape);
    sfVector2f tower_pos = sfCircleShape_getPosition(tower_shape);

    // Compute distance to tower
    sfVector2f vector = {
            .x = fabsf(point.x - tower_pos.x),
            .y = fabsf(point.y - tower_pos.y),
    };
    float distance = sqrtf(vector.x * vector.x + vector.y * vector.y);
    return distance <= tower_radius;
}