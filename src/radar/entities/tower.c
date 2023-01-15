#include <engine/render/component.h>
#include <engine/render/system.h>

#include "radar/components/position.h"
#include "radar/entities/tower.h"
#include "radar/components/hitbox.h"
#include "radar/systems/hitbox.h"
#include "radar/tools/sprite.h"
#include "radar/entities/hitbox.h"

static entity_t *tower_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *tower = entity_create();
    component_t *position = position_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    });
    sfSprite *sprite = sprite_create_from_file("./assets/tower.png", (sprite_params_t){
        .position = component_get_data(position, position_component_t)->position,
        .origin = CENTER,
    });
    sfCircleShape *hitbox_circle = render_circle_create(component_get_data(position, position_component_t)->position, (float)definition->args[2] * 19.2);

    component_t *render = render_component_create();
    render_component_append_object(render, SPRITE, sprite, SPRITE_RENDER_ID);
    render_component_append_object(render, CIRCLE_SHAPE, hitbox_circle, HITBOX_RENDER_ID);

    component_t *hitbox = hitbox_circle_component_create((float)definition->args[2] * 19.2);

    entity_assign_component(tower, position);
    entity_assign_component(tower, render);
    entity_assign_component(tower, hitbox);
    return tower;
}

void tower_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *tower = tower_create_from_definition(definition);

    system_subscribe_entity(scene_get_system(scene, RENDER_SYSTEM_TYPE), tower);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), tower);
    scene_append_entity(scene, tower);
}
