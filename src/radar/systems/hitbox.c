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
    entity_link_t *entity_link = NULL;
    TAILQ_FOREACH(entity_link, &system->entities_subscribed, entry) {
        entity_t *entity = entity_link->entity;
        hitbox_component_t *hitbox = entity_get_component(entity, HITBOX_COMPONENT_TYPE)->data;

        if (hitbox->type == CUSTOM) {
            sfRenderWindow_drawConvexShape(window, hitbox->csfml_object, NULL);
        }

        if (!*((bool *)system->context)) {
            continue;
        }

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
        hitbox_component_t *hitbox_checked = entity_get_component(entity_checked, HITBOX_COMPONENT_TYPE)->data;
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

static void aircraft_test_collision(system_t *system, entity_link_t *aircraft, hitbox_component_t *hitbox)
{
    entity_link_t *entity_link_checked = NULL;
    entity_link_t *entity_link_checked_tmp = NULL;
    TAILQ_FOREACH_SAFE(entity_link_checked, &system->entities_subscribed, entry, entity_link_checked_tmp) {
        entity_t *entity_checked = entity_link_checked->entity;
        hitbox_component_t *hitbox_checked = entity_get_component(entity_checked, HITBOX_COMPONENT_TYPE)->data;
        if (aircraft->entity == entity_link_checked->entity || aircraft_is_under_tower(system, entity_checked, hitbox_checked)) {
            continue;
        }
        if (hitbox_checked->type == RECT && rect_intersect_rect(hitbox, hitbox_checked)) {
            // Plane collides
            TAILQ_REMOVE(&system->entities_subscribed, entity_link_checked, entry);
            TAILQ_REMOVE(&system->entities_subscribed, aircraft, entry);
            TAILQ_INSERT_TAIL(&SYSTEM_CONTEXT(system, hitbox_system_t)->plane_to_delete, entity_link_checked, entry);
            TAILQ_INSERT_TAIL(&SYSTEM_CONTEXT(system, hitbox_system_t)->plane_to_delete, aircraft, entry);
        }
    }
}

static bool segment_intersect_segment(sfVector2f a1, sfVector2f a2, sfVector2f b1, sfVector2f b2)
{
    // Avoid 0 div
    if (a2.x - a1.x == 0 || b2.x - b1.x == 0) {
        return false;
    }

    float fa1 = (a2.y - a1.y) / (a2.x - a1.x);
    float fa2 = (b2.y - b1.y) / (b2.x - b1.x);
    float fb1 = a1.y - fa1 * a1.x;
    float fb2 = b1.y - fa2 * b1.x;

    // Avoid 0 div
    if (fa1 - fa2 == 0) {
        return false;
    }
    float intersect_x = (fb2 - fb1) / (fa1 - fa2);

    // Take the smallest x point
    float s1_x_min = min(a1.x, a2.x);
    float s2_x_min = min(b1.x, b2.x);
    float s_min = max(s1_x_min, s2_x_min);

    // Take the biggest x point
    float s1_x_max = max(a1.x, a2.x);
    float s2_x_max = max(b1.x, b2.x);
    float s_max = min(s1_x_max, s2_x_max);

    return intersect_x >= s_min && intersect_x <= s_max;
}

static bool custom_intersect_custom(hitbox_component_t *a, hitbox_component_t *b)
{
    sfVector2f pos_a = sfConvexShape_getPosition(a->csfml_object);
    sfVector2f pos_b = sfConvexShape_getPosition(b->csfml_object);

    for (size_t it_a = 0; it_a < a->point_count - 1; it_a++) {
        for (size_t it_b = 0; it_b < b->point_count - 1; it_b++) {
            if (segment_intersect_segment(
                    (sfVector2f){a->points[it_a].x + pos_a.x, a->points[it_a].y + pos_a.y},
                    (sfVector2f){a->points[it_a + 1].x + pos_a.x, a->points[it_a + 1].y + pos_a.y},
                    (sfVector2f){b->points[it_b].x + pos_b.x, b->points[it_b].y + pos_b.y},
                    (sfVector2f){b->points[it_b + 1].x + pos_b.x, b->points[it_b + 1].y + pos_b.y}
            )) {
                return true;
            }
        }
    }
//    // Last a segment
    for (size_t it_b = 0; it_b < b->point_count - 1; it_b++) {
        if (segment_intersect_segment(
                (sfVector2f){a->points[a->point_count - 1].x + pos_a.x, a->points[a->point_count - 1].y + pos_a.y},
                (sfVector2f){a->points[0].x + pos_a.x, a->points[0].y + pos_a.y},
                (sfVector2f){b->points[it_b].x + pos_b.x, b->points[it_b].y + pos_b.y},
                (sfVector2f){b->points[it_b + 1].x + pos_b.x, b->points[it_b + 1].y + pos_b.y}
        )) {
            return true;
        }
    }
    // Last b segment
    for (size_t it_a = 0; it_a < a->point_count - 1; it_a++) {
        if (segment_intersect_segment(
                (sfVector2f){a->points[it_a].x + pos_a.x, a->points[it_a].y + pos_a.y},
                (sfVector2f){a->points[it_a + 1].x + pos_a.x, a->points[it_a + 1].y + pos_a.y},
                (sfVector2f){b->points[b->point_count - 1].x + pos_b.x, b->points[b->point_count - 1].y + pos_b.y},
                (sfVector2f){b->points[0].x + pos_b.x, b->points[0].y + pos_b.y}
        )) {
            return true;
        }
    }
    return false;
}

#include <stdio.h>

static void custom_hitbox_collision(system_t *system, hitbox_component_t *tested)
{
    entity_link_t *entity_link_tested = NULL;
    entity_link_t *entity_link_tested_tmp = NULL;

    TAILQ_FOREACH_SAFE(entity_link_tested, &system->entities_subscribed, entry, entity_link_tested_tmp) {
        entity_t *entity_tested = entity_link_tested->entity;
        hitbox_component_t *hitbox_tested = entity_get_component(entity_tested, HITBOX_COMPONENT_TYPE)->data;
        if (hitbox_tested->type != CUSTOM || hitbox_tested == tested) {
            continue;
        }
        if (custom_intersect_custom(tested, hitbox_tested)) {
            printf("Intersection\n", tested->point_count, hitbox_tested->point_count);
            fflush(stdout);
        }
    }
}

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_link_t *entity_link_tested = NULL;
    entity_link_t *entity_link_tested_tmp = NULL;

    TAILQ_HEAD(, entity_link_s) plane_to_delete;
    TAILQ_INIT(&plane_to_delete);

    TAILQ_FOREACH_SAFE(entity_link_tested, &system->entities_subscribed, entry, entity_link_tested_tmp) {
        entity_t *entity_tested = entity_link_tested->entity;
        hitbox_component_t *hitbox_tested = entity_get_component(entity_tested, HITBOX_COMPONENT_TYPE)->data;
        if (hitbox_tested->type == RECT && !aircraft_is_under_tower(system, entity_tested, hitbox_tested)) {
            aircraft_test_collision(system, entity_link_tested, hitbox_tested);
        }
        if (hitbox_tested->type == CUSTOM) {
            custom_hitbox_collision(system, hitbox_tested);
        }
    }
    entity_link_tested = NULL;
    entity_link_tested_tmp = NULL;
    TAILQ_FOREACH_SAFE(entity_link_tested, &SYSTEM_CONTEXT(system, hitbox_system_t)->plane_to_delete, entry, entity_link_tested_tmp) {
        TAILQ_REMOVE(&SYSTEM_CONTEXT(system, hitbox_system_t)->plane_to_delete, entity_link_tested, entry);
        scene_destroy_entity(scene_get(), entity_link_tested->entity);
        free(entity_link_tested);
    }
}

static void destroy_handler(system_t *system)
{
    free(SYSTEM_CONTEXT(system, hitbox_system_t));
}

system_t *hitbox_system_create(void)
{
    hitbox_system_t *data = malloc(sizeof(hitbox_system_t));
    data->render_enabled = true;
    TAILQ_INIT(&data->plane_to_delete);
    return system_create(HITBOX_SYSTEM_TYPE, (system_params_t){
        .context = data,
        .render_handler = render_handler,
        .update_handler = update_handler,
        .destroy_handler = destroy_handler
    });
}