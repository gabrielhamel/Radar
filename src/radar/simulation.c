#include <stdlib.h>

#include "engine/engine.h"

#include "radar/simulation.h"

static void simulation_close(simulation_t *simulation)
{
    engine_t *engine = engine_get();

    sfRenderWindow_close(engine->window);
}

static events_handler_t *simulation_create_event_handler(simulation_t *simulation)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, simulation_close, simulation);
    return eh;
}

simulation_t *simulation_create_from_script(const char *filepath)
{
    simulation_t *simulation;
    radar_definition_t *def = parser_read(filepath);
    radar_entity_definition_t *entity;

    if (def == NULL) {
        return EXIT_FAILURE;
    }
    simulation = malloc(sizeof(simulation_t));
    LIST_INIT(&simulation->aircrafts);
    LIST_INIT(&simulation->towers);
    simulation->scene = scene_create();
    LIST_FOREACH(entity, &def->entities, entry) {
        switch (entity->type) {
            case AIRCRAFT:
                simulation_append_aircraft(simulation, aircraft_create_from_definition(entity));
                break;
            case TOWER:
                simulation_append_tower(simulation, tower_create_from_definition(entity));
                break;
        }
    }
    simulation->scene->update_delegate = simulation_update;
    simulation->scene->update_context = simulation;
    scene_subscribe_event_handler(simulation->scene, simulation_create_event_handler(simulation));
    return simulation;
}

void simulation_update(simulation_t *simulation, sfTime *elapsed_time)
{
    tower_t *tower_it = NULL;
    aircraft_t *aircraft_it = NULL;

    LIST_FOREACH(tower_it, &simulation->towers, entry) {
        tower_update(tower_it, elapsed_time);
    }
    LIST_FOREACH(aircraft_it, &simulation->aircrafts, entry) {
        aircraft_update(aircraft_it, elapsed_time);
    }
}

void simulation_append_tower(simulation_t *simulation, tower_t *tower)
{
    scene_append_entity(simulation->scene, tower->entity);
    LIST_INSERT_HEAD(&simulation->towers, tower, entry);
}

void simulation_append_aircraft(simulation_t *simulation, aircraft_t *aircraft)
{
    scene_append_entity(simulation->scene, aircraft->entity);
    LIST_INSERT_HEAD(&simulation->aircrafts, aircraft, entry);
}
