#include "radar/components/position.h"
#include "radar/entities/tower.h"

entity_t *tower_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *tower = entity_create();
    component_t *position = position_component_create((sfVector2f){
        definition->args[0],
        definition->args[1]
    });

    entity_assign_component(tower, position);
    return tower;
}
