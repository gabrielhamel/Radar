#include <stdbool.h>
#include <stdlib.h>

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include "engine/ecs/scene.h"
#include "radar/systems/hitbox.h"
#include "radar/components/hitbox.h"

static void render_handler(system_t *system, sfRenderWindow *window)
{
    if (!*((bool *)system->context)) {
        return;
    }

    entity_link_t *entity_link = NULL;
    TAILQ_FOREACH(entity_link, &system->entities_subscribed, entry) {
        entity_t *entity = entity_link->entity;
        
        hitbox_component_t *hitbox = entity_get_component(entity, HITBOX_COMPONENT_TYPE);
        if (hitbox->type == CIRCLE) {
            sfRenderWindow_drawCircleShape(window, hitbox->csfml_object, NULL);
        } else if (hitbox->type == RECT) {
            sfRenderWindow_drawRectangleShape(window, hitbox->csfml_object, NULL);
        }
    }
}

static bool rect_intersect_rect(hitbox_component_t *hitbox_tested, hitbox_component_t *hitbox_checked)
{
    sfRectangleShape *shape_tested = hitbox_tested->csfml_object;
    sfRectangleShape *shape_checked = hitbox_checked->csfml_object;

    const sfFloatRect rect_tested = sfRectangleShape_getGlobalBounds(shape_tested);
    const sfFloatRect rect_checked = sfRectangleShape_getGlobalBounds(shape_checked);

    return sfFloatRect_intersects(
        &rect_tested,
        &rect_checked,
        NULL
    );
}

static bool point_intersect_circle(hitbox_component_t *tower_hitbox, sfVector2f point)
{
    sfCircleShape *tower_shape = tower_hitbox->csfml_object;
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

static bool rect_intersect_circle(hitbox_component_t *aircraft_hitbox, hitbox_component_t *tower_hitbox)
{
    sfRectangleShape *aircraft_shape = aircraft_hitbox->csfml_object;
    sfFloatRect aircraft_rect = sfRectangleShape_getGlobalBounds(aircraft_shape);

    if (point_intersect_circle(tower_hitbox, (sfVector2f){aircraft_rect.left, aircraft_rect.top})) {
        return true;
    }
    if (point_intersect_circle(tower_hitbox, (sfVector2f){aircraft_rect.left + aircraft_rect.width, aircraft_rect.top})) {
        return true;
    }
    if (point_intersect_circle(tower_hitbox, (sfVector2f){aircraft_rect.left, aircraft_rect.top + aircraft_rect.height})) {
        return true;
    }
    if (point_intersect_circle(tower_hitbox, (sfVector2f){aircraft_rect.left + aircraft_rect.width,
                                                          aircraft_rect.top + aircraft_rect.height})) {
        return true;
    }
    return false;
}

static bool aircraft_is_under_tower(system_t *system, entity_t *aircraft, hitbox_component_t *hitbox)
{
    entity_link_t *entity_link_checked = NULL;
    TAILQ_FOREACH(entity_link_checked, &system->entities_subscribed, entry) {
        entity_t *entity_checked = entity_link_checked->entity;
        hitbox_component_t *hitbox_checked = entity_get_component(entity_checked, HITBOX_COMPONENT_TYPE);
        if (hitbox_checked->type != CIRCLE) {
            continue;
        }
        if (rect_intersect_circle(hitbox, hitbox_checked)) {
            // Plane is under the tower
            return true;
        }
    }
    return false;
}

static void aircraft_test_collision(system_t *system, entity_t *aircraft, hitbox_component_t *hitbox)
{
    entity_link_t *entity_link_checked = NULL;
    entity_link_t *entity_link_checked_tmp = NULL;
    TAILQ_FOREACH_SAFE(entity_link_checked, &system->entities_subscribed, entry, entity_link_checked_tmp) {
        if (aircraft == entity_link_checked->entity) {
            continue;
        }
        entity_t *entity_checked = entity_link_checked->entity;
        hitbox_component_t *hitbox_checked = entity_get_component(entity_checked, HITBOX_COMPONENT_TYPE);
        if (hitbox_checked->type == RECT && rect_intersect_rect(hitbox, hitbox_checked)) {
            // Plane collides
            scene_remove_entity(scene_get(), entity_link_checked->entity);
            scene_remove_entity(scene_get(), aircraft);
        }
    }
}

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_link_t *entity_link_tested = NULL;
    entity_link_t *entity_link_tested_tmp = NULL;
    TAILQ_FOREACH_SAFE(entity_link_tested, &system->entities_subscribed, entry, entity_link_tested_tmp) {
        entity_t *entity_tested = entity_link_tested->entity;
        hitbox_component_t *hitbox_tested = entity_get_component(entity_tested, HITBOX_COMPONENT_TYPE);
        if (hitbox_tested->type == RECT && !aircraft_is_under_tower(system, entity_tested, hitbox_tested)) {
            aircraft_test_collision(system, entity_tested, hitbox_tested);
        }
    }
}

system_t *hitbox_system_create(void)
{
    bool *enabled = malloc(sizeof(bool));
    *enabled = true;
    return system_create(HITBOX_SYSTEM_TYPE, (system_params_t){
        .context = enabled,
        .render_handler = render_handler,
        .update_handler = update_handler,
    });
}