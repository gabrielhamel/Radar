#include "radar/systems/movement.h"
#include "radar/components/position.h"
#include "radar/components/speed.h"
#include "radar/components/sprite.h"

static void update_handler(entity_t *entity, sfTime *elapsed_time, void *)
{
    position_component_t *position_c = entity_get_component(entity, POSITION_COMPONENT_TYPE);
    speed_component_t *speed_c = entity_get_component(entity, SPEED_COMPONENT_TYPE);
    sprite_component_t *sprite_c = entity_get_component(entity, SPRITE_COMPONENT_TYPE);

    position_c->position.x += speed_c->speed.x * sfTime_asSeconds(*elapsed_time);
    position_c->position.y += speed_c->speed.y * sfTime_asSeconds(*elapsed_time);
    sfSprite_setPosition(sprite_c->sprite, position_c->position);
}

system_t *movement_system_create(void)
{
    return system_create(MOVEMENT_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .render_handler = NULL,
        .update_handler = update_handler,
    });
}