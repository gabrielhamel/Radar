#include "engine/engine.h"
#include "radar/simulation.h"
#include "radar/parser.h"
#include "radar/entities/aircraft.h"
#include "radar/entities/tower.h"
#include "radar/systems/sprite_drawer.h"
#include "radar/systems/movement.h"

bool radar_init_from_script(scene_t *scene, const char *filepath)
{
    radar_definition_t *def = parser_read(filepath);
    radar_entity_definition_t *entity;
    entity_t *aircraft;
    entity_t *tower;

    if (def == NULL) {
        return false;
    }
    engine_t *engine = engine_get();
    scene_append_system(scene, sprite_drawer_system_create());
    scene_append_system(scene, movement_system_create());
    LIST_FOREACH(entity, &def->entities, entry) {
        switch (entity->type) {
            case AIRCRAFT:
                aircraft = aircraft_create_from_definition(entity);
                scene_append_entity(scene, aircraft);
                scene_subscribe_entity_to_system(scene, aircraft, SPRITE_DRAWER_SYSTEM_TYPE);
                scene_subscribe_entity_to_system(scene, aircraft, MOVEMENT_SYSTEM_TYPE);
                break;
            case TOWER:
                tower = tower_create_from_definition(entity);
                scene_subscribe_entity_to_system(scene, tower, SPRITE_DRAWER_SYSTEM_TYPE);
                scene_append_entity(scene, tower);
                break;
        }
    }
    return true;
}
