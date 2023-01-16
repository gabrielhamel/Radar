#include <engine/tools/maths.h>
#include <engine/render/component.h>
#include <engine/render/system.h>
#include <engine/physics/component.h>
#include <engine/physics/system.h>

#include "radar/components/hitbox.h"
#include "radar/components/ttl.h"
#include "radar/entities/aircraft.h"
#include "radar/systems/simulation.h"
#include "radar/systems/hitbox.h"
#include "radar/tools/sprite.h"
#include "radar/entities/hitbox.h"

static entity_t *aircraft_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *aircraft = entity_create();

    sfVector2f vector = {
        .x = (float)definition->args[2] - (float)definition->args[0],
        .y = (float)definition->args[3] - (float)definition->args[1]
    };
    float angle = atan(vector.y / vector.x) + (vector.x < 0 ? M_PI : 0);
    physics_component_t movement = {
        .position = (sfVector2f){
            definition->args[0],
            definition->args[1]
        },
        .speed = (sfVector2f){
            cos(angle) * (float)definition->args[4],
            sin(angle) * (float)definition->args[4]
        }
    };
    component_t *physics = physics_component_create(movement);

    sfSprite *sprite = sprite_create_from_file("./assets/aircraft.png", (sprite_params_t){
        .position = movement.position,
        .origin = CENTER
    });
    system_t *hitbox_system = scene_get_system(scene_get(), HITBOX_SYSTEM_TYPE);
    bool render_enabled = system_get_context(hitbox_system, hitbox_system_t)->render_enabled;
    sfRectangleShape *hitbox_rect = render_rect_create(movement.position, render_enabled);
    component_t *hitbox = hitbox_rect_component_create();

    float alive_time = vector.x / movement.speed.x;
    if (alive_time == 0) {
        alive_time = vector.y / movement.speed.y;
    }
    component_t *ttl = ttl_component_create(alive_time);

    sfSprite_setRotation(sprite, angle * 180.0 / M_PI);

    component_t *render = render_component_create();
    render_component_append_object(render, SPRITE, sprite, SPRITE_RENDER_ID);
    render_component_append_object(render, RECTANGLE_SHAPE, hitbox_rect, HITBOX_RENDER_ID);

    entity_assign_component(aircraft, physics);
    entity_assign_component(aircraft, render);
    entity_assign_component(aircraft, hitbox);
    entity_assign_component(aircraft, ttl);
    return aircraft;
}

void aircraft_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *aircraft = aircraft_create_from_definition(definition);
    scene_append_entity(scene, aircraft);

    system_subscribe_entity(scene_get_system(scene, RENDER_SYSTEM_TYPE), aircraft);
    system_subscribe_entity(scene_get_system(scene, PHYSICS_SYSTEM_TYPE), aircraft);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), aircraft);
    system_subscribe_entity(scene_get_system(scene, SIMULATION_SYSTEM_TYPE), aircraft);
}
