#include "radar/systems/sprite_drawer.h"
#include "radar/components/sprite.h"

static void update(entity_t *entity, sfTime *elapsed_time, sfRenderWindow *window)
{
    sprite_component_t *sprite_c = entity_get_component(entity, SPRITE_COMPONENT_TYPE);

    sfRenderWindow_drawSprite(window, sprite_c->sprite, NULL);
}

system_t *sprite_drawer_system_create(sfRenderWindow *window)
{
    return system_create(SPRITE_DRAWER_SYSTEM_TYPE, (system_params_t){
        .update_context = window,
        .update_handler = update,
    });
}