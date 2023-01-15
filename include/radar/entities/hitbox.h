#ifndef RADAR_ENTITIES_HITBOX_H
#define RADAR_ENTITIES_HITBOX_H

#include <engine/ecs/scene.h>

#define CONVEX_SHAPE_ID 0

void hitbox_scene_append(scene_t *scene);

sfCircleShape *render_circle_create(sfVector2f initial_pos, float radius);
sfRectangleShape *render_rect_create(sfVector2f initial_pos, bool enabled);
sfConvexShape *render_custom_create(sfVector2f initial_pos, sfVector2f *points, size_t count);

#endif // RADAR_ENTITIES_HITBOX_H

