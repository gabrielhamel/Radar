#include <stdlib.h>

#include <engine/tools/lists.h>
#include <radar/systems/simulation.h>
#include <radar/parser.h>
#include <radar/entities/aircraft.h>
#include <radar/components/ttl.h>

static void check_take_off(simulation_system_t *simulation)
{
    radar_entity_definition_t *aircraft = NULL;
    radar_entity_definition_t *aircraft_tmp = NULL;
    TAILQ_FOREACH_SAFE(aircraft, &simulation->def->entities, entry, aircraft_tmp) {
        if (sfTime_asSeconds(*simulation->timer) >= aircraft->args[5]) {
            // Take off aircraft
            aircraft_scene_append(simulation->scene, aircraft);
            TAILQ_REMOVE(&simulation->def->entities, aircraft, entry);
            radar_entity_definition_destroy(aircraft);
        }
    }
}

static void check_landing(simulation_system_t *simulation, sfTime *elapsed_time, entity_t *aircraft)
{
    // Kill aircraft that are already reach their destination
    float *ttl = entity_get_component_data(aircraft, TTL_COMPONENT_TYPE, float);
    if (ttl) {
        *ttl -= sfTime_asSeconds(*elapsed_time);
        if (*ttl <= 0) {
            scene_destroy_entity(simulation->scene, aircraft);
        }
    }
}

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    simulation_system_t *simulation = system_get_context(system, simulation_system_t);

    check_take_off(simulation);

    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        check_landing(simulation, elapsed_time, entity);
    }
    entity_iterator_destroy(it);
}

static void destroy_handler(system_t *system)
{
    simulation_system_t *context = system_get_context(system, simulation_system_t);

    radar_entity_definition_t *entity = NULL;
    radar_entity_definition_t *tmp = NULL;
    TAILQ_FOREACH_SAFE(entity, &context->def->entities, entry, tmp) {
        TAILQ_REMOVE(&context->def->entities, entity, entry);
        radar_entity_definition_destroy(entity);
    }

    free(context->def);
    free(context);
}

system_t *simulation_system_create(scene_t *scene, sfTime *timer, radar_definition_t *def)
{
    simulation_system_t *simulation = malloc(sizeof(simulation_system_t));

    simulation->scene = scene;
    simulation->timer = timer;
    simulation->def = def;
    return system_create(SIMULATION_SYSTEM_TYPE, (system_params_t){
        .context = simulation,
        .update_handler = update_handler,
        .render_handler = NULL,
        .destroy_handler = destroy_handler,
    });
}