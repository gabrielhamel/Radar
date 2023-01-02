#include "radar/components/position.h"
#include "radar/entities/tower.h"
#include "radar/components/sprite.h"
#include "radar/components/hitbox.h"

entity_t *tower_create_from_definition(radar_entity_definition_t *definition)
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
