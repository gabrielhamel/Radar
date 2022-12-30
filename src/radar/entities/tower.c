#include "radar/components/position.h"
#include "radar/entities/tower.h"
#include "radar/components/sprite.h"

entity_t *tower_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *tower = entity_create();
    component_t *position = position_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    });
    component_t *sprite = sprite_component_create_from_file("./assets/tower.png", (sprite_params_t){
            .position = COMPONENT_DATA(position, position_component_t)->position
    });

    entity_assign_component(tower, position);
    entity_assign_component(tower, sprite);
    return tower;
}
