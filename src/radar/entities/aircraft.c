#ifdef WIN32
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <stdlib.h>

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
    sfVector2f vector = {
        .x = (float)definition->args[2] - (float)definition->args[0],
        .y = (float)definition->args[3] - (float)definition->args[1]
    };
    float angle = atan(vector.y / vector.x) + (vector.x < 0 ? M_PI : 0);
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

    float alive_time = vector.x /
            COMPONENT_DATA(speed, speed_component_t)->speed.x;
    if (alive_time == 0) {
        alive_time = vector.y /
        COMPONENT_DATA(speed, speed_component_t)->speed.y;
    }
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

    system_subscribe_entity(scene_get_system(scene, SPRITE_DRAWER_SYSTEM_TYPE), aircraft);
    system_subscribe_entity(scene_get_system(scene, MOVEMENT_SYSTEM_TYPE), aircraft);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), aircraft);
    system_subscribe_entity(scene_get_system(scene, SIMULATION_SYSTEM_TYPE), aircraft);
}

void aircraft_scene_destroy(scene_t *scene, entity_t *aircraft)
{
    system_unsubscribe_entity(scene_get_system(scene, SPRITE_DRAWER_SYSTEM_TYPE), aircraft);
    system_unsubscribe_entity(scene_get_system(scene, MOVEMENT_SYSTEM_TYPE), aircraft);
    system_unsubscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), aircraft);
    system_unsubscribe_entity(scene_get_system(scene, SIMULATION_SYSTEM_TYPE), aircraft);

    component_t *position = entity_remove_component(aircraft, POSITION_COMPONENT_TYPE);
    position_component_destroy(position);

    component_t *speed = entity_remove_component(aircraft, SPEED_COMPONENT_TYPE);
    speed_component_destroy(speed);

    component_t *sprite = entity_remove_component(aircraft, SPRITE_COMPONENT_TYPE);
    sprite_component_destroy(sprite);

    component_t *hitbox = entity_remove_component(aircraft, HITBOX_COMPONENT_TYPE);
    hitbox_component_destroy(hitbox);

    component_t *ttl = entity_remove_component(aircraft, TTL_COMPONENT_TYPE);
    ttl_component_destroy(ttl);

    scene_remove_entity(scene, aircraft);
    entity_destroy(aircraft);
}