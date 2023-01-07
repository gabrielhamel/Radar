#include "radar/components/position.h"
#include "radar/entities/tower.h"
#include "radar/components/sprite.h"
#include "radar/components/hitbox.h"
#include "radar/systems/hitbox.h"
#include "radar/systems/sprite_drawer.h"

static entity_t *tower_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *tower = entity_create();
    component_t *position = position_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    });
    component_t *sprite = sprite_component_create_from_file("./assets/tower.png", (sprite_params_t){
        .position = COMPONENT_DATA(position, position_component_t)->position,
        .origin = CENTER,
    });
    component_t *hitbox = hitbox_circle_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    }, (float)definition->args[2] * 19.2);

    entity_assign_component(tower, position);
    entity_assign_component(tower, sprite);
    entity_assign_component(tower, hitbox);
    return tower;
}

void tower_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *tower = tower_create_from_definition(definition);

    system_subscribe_entity(scene_get_system(scene, SPRITE_DRAWER_SYSTEM_TYPE), tower);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), tower);
    scene_append_entity(scene, tower);
}

void tower_scene_destroy(scene_t *scene, entity_t *tower)
{
    system_unsubscribe_entity(scene_get_system(scene, SPRITE_DRAWER_SYSTEM_TYPE), tower);
    system_unsubscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), tower);

    component_t *position = entity_remove_component(tower, POSITION_COMPONENT_TYPE);
    position_component_destroy(position);

    component_t *sprite = entity_remove_component(tower, SPRITE_COMPONENT_TYPE);
    sprite_component_destroy(sprite);

    component_t *hitbox = entity_remove_component(tower, HITBOX_COMPONENT_TYPE);
    hitbox_component_destroy(hitbox);

    scene_remove_entity(scene, tower);
    entity_destroy(tower);
}
