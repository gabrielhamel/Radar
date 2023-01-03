#include <stdlib.h>

#include "engine/queue.h"
#include "radar/systems/simulation.h"
#include "radar/parser.h"
#include "radar/entities/aircraft.h"
#include "radar/components/ttl.h"

static void update_handler(entity_t *entity, sfTime *elapsed_time, simulation_system_t *simulation)
{
    radar_entity_definition_t *aircraft = NULL;
    radar_entity_definition_t *aircraft_tmp = NULL;

    LIST_FOREACH_SAFE(aircraft, &simulation->def->entities, entry, aircraft_tmp) {
        if (sfTime_asSeconds(*simulation->timer) >= aircraft->args[5]) {
            aircraft_scene_append(simulation->scene, aircraft);
            LIST_REMOVE(aircraft, entry);
        }
    }
    // Kill aircraft that are already reach their destination
    float *ttl = entity_get_component(entity, TTL_COMPONENT_TYPE);
    if (ttl) {
        *ttl -= sfTime_asSeconds(*elapsed_time);
        if (*ttl <= 0) {
            scene_remove_entity(simulation->scene, entity);
        }
    }
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
    });
}