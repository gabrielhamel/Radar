#include <math.h>

#include "radar/components/position.h"
#include "radar/components/speed.h"
#include "radar/components/sprite.h"
#include "radar/components/hitbox.h"
#include "radar/entities/aircraft.h"

entity_t *aircraft_create_from_definition(radar_entity_definition_t *definition)
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

    sfSprite_setRotation(COMPONENT_DATA(sprite, sprite_component_t)->sprite, angle * 180.0 / M_PI);

    entity_assign_component(aircraft, position);
    entity_assign_component(aircraft, speed);
    entity_assign_component(aircraft, sprite);
    entity_assign_component(aircraft, hitbox);
    return aircraft;
}
