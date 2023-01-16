#include <engine/render/component.h>
#include <engine/render/system.h>
#include <engine/physics/component.h>
#include <engine/physics/system.h>

#include "radar/entities/tower.h"
#include "radar/components/hitbox.h"
#include "radar/systems/hitbox.h"
#include "radar/tools/sprite.h"
#include "radar/entities/hitbox.h"

static entity_t *tower_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *tower = entity_create();

    physics_component_t movement = (physics_component_t){
        .speed = (sfVector2f){0, 0},
        .position = (sfVector2f){
            definition->args[0],
            definition->args[1]
        }
    };
    component_t *physics = physics_component_create(movement);

    sfSprite *sprite = sprite_create_from_file("./assets/tower.png", (sprite_params_t){
        .position = movement.position,
        .origin = CENTER,
    });
    sfCircleShape *hitbox_circle = render_circle_create(movement.position, (float)definition->args[2] * 19.2);

    component_t *render = render_component_create();
    render_component_append_object(render, SPRITE, sprite, SPRITE_RENDER_ID);
    render_component_append_object(render, CIRCLE_SHAPE, hitbox_circle, HITBOX_RENDER_ID);

    component_t *hitbox = hitbox_circle_component_create((float)definition->args[2] * 19.2);

    entity_assign_component(tower, physics);
    entity_assign_component(tower, render);
    entity_assign_component(tower, hitbox);
    return tower;
}

void tower_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *tower = tower_create_from_definition(definition);

    system_subscribe_entity(scene_get_system(scene, PHYSICS_SYSTEM_TYPE), tower);
    system_subscribe_entity(scene_get_system(scene, RENDER_SYSTEM_TYPE), tower);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), tower);
    scene_append_entity(scene, tower);
}
