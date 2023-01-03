#include <math.h>

#include "radar/components/position.h"
#include "radar/components/speed.h"
#include "radar/components/sprite.h"
#include "radar/components/hitbox.h"
#include "radar/components/ttl.h"
#include "radar/entities/aircraft.h"
#include "radar/systems/movement.h"
#include "radar/systems/simulation.h"
#include "radar/systems/sprite_drawer.h"
#include "radar/systems/hitbox.h"

static entity_t *aircraft_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *aircraft = entity_create();
    component_t *position = position_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    });
    float angle = atan(((float)definition->args[3] - (float)definition->args[1]) /
            ((float)definition->args[2] - (float)definition->args[0]));
    component_t *speed = speed_component_create((sfVector2f){
        cos(angle) * (float)definition->args[4],
        sin(angle) * (float)definition->args[4]
    });
    component_t *sprite = sprite_component_create_from_file("./assets/aircraft.png", (sprite_params_t){
        .position = COMPONENT_DATA(position, position_component_t)->position,
        .origin = CENTER
    });
    component_t *hitbox = hitbox_rect_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    });

    float alive_time = ((float)definition->args[2] - (float)definition->args[0]) /
            COMPONENT_DATA(speed, speed_component_t)->speed.x;

    component_t *ttl = ttl_component_create(alive_time);

    sfSprite_setRotation(COMPONENT_DATA(sprite, sprite_component_t)->sprite, angle * 180.0 / M_PI);

    entity_assign_component(aircraft, position);
    entity_assign_component(aircraft, speed);
    entity_assign_component(aircraft, sprite);
    entity_assign_component(aircraft, hitbox);
    entity_assign_component(aircraft, ttl);
    return aircraft;
}

void aircraft_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *aircraft = aircraft_create_from_definition(definition);
    scene_append_entity(scene, aircraft);
    scene_subscribe_entity_to_system(scene, aircraft, SPRITE_DRAWER_SYSTEM_TYPE);
    scene_subscribe_entity_to_system(scene, aircraft, MOVEMENT_SYSTEM_TYPE);
    scene_subscribe_entity_to_system(scene, aircraft, HITBOX_SYSTEM_TYPE);
    scene_subscribe_entity_to_system(scene, aircraft, SIMULATION_SYSTEM_TYPE);
}