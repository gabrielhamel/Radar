#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <engine/ecs/scene.h>
#include <radar/systems/hitbox.h>
#include <radar/components/hitbox.h>

static bool aircraft_is_under_tower(system_t *system, entity_t *aircraft)
{
    entity_iterator_t *it = system_get_entity_iterator(system);

    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        hitbox_component_t *candidate = entity_get_component_data(entity, HITBOX_COMPONENT_TYPE, hitbox_component_t);
        if (candidate->type != CIRCLE) {
            continue;
        }
        if (rect_intersect_circle(aircraft, entity)) {
            // Plane is under the tower
            entity_iterator_destroy(it);
            return true;
        }
    }
    entity_iterator_destroy(it);
    return false;
}

static void aircraft_test_collision(system_t *system, entity_t *aircraft)
{
    hitbox_system_t *context = system_get_context(system, hitbox_system_t);

    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        hitbox_component_t *hitbox_checked = entity_get_component_data(entity, HITBOX_COMPONENT_TYPE, hitbox_component_t);
        if (aircraft == entity || aircraft_is_under_tower(system, entity)) {
            continue;
        }
        if (hitbox_checked->type == RECT && rect_intersect_rect(aircraft, entity)) {
            // Plane collides
            entity_set_append(context->crashed_aircrafts, entity);
            entity_set_append(context->crashed_aircrafts, aircraft);
        }
    }
    entity_iterator_destroy(it);
}

static void custom_hitbox_collision(system_t *system, entity_t *tested)
{
    entity_iterator_t *it = system_get_entity_iterator(system);

    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        hitbox_component_t *candidate = entity_get_component_data(entity, HITBOX_COMPONENT_TYPE, hitbox_component_t);
        if (candidate->type != CUSTOM || entity == tested) {
            continue;
        }
        if (custom_intersect_custom(tested, entity)) {
            printf("Intersection\n");
            fflush(stdout);
        }
    }
    entity_iterator_destroy(it);
}

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        hitbox_component_t *hitbox_tested = entity_get_component_data(entity, HITBOX_COMPONENT_TYPE, hitbox_component_t);
        if (hitbox_tested->type == RECT && !aircraft_is_under_tower(system, entity)) {
            aircraft_test_collision(system, entity);
        }
        if (hitbox_tested->type == CUSTOM) {
            custom_hitbox_collision(system, entity);
        }
    }
    entity_iterator_destroy(it);

    // Destroy aircraft marked for crash
    hitbox_system_t *context = system_get_context(system, hitbox_system_t);
    it = entity_set_get_iterator(context->crashed_aircrafts);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        scene_destroy_entity(scene_get(), entity);
    }
    entity_iterator_destroy(it);

    entity_set_empty(context->crashed_aircrafts);
}

static void destroy_handler(system_t *system)
{
    hitbox_system_t *context = system_get_context(system, hitbox_system_t);
    entity_set_destroy(context->crashed_aircrafts);
    free(context);
}

system_t *hitbox_system_create(void)
{
    hitbox_system_t *data = malloc(sizeof(hitbox_system_t));
    data->render_enabled = true;
    data->crashed_aircrafts = entity_set_create();
    return system_create(HITBOX_SYSTEM_TYPE, (system_params_t){
        .context = data,
        .update_handler = update_handler,
        .destroy_handler = destroy_handler
    });
}