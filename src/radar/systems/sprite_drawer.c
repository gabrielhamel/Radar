#include "radar/systems/sprite_drawer.h"
#include "radar/components/sprite.h"

static void render_handler(entity_t *entity, sfRenderWindow *window)
{
    sprite_component_t *sprite_c = entity_get_component(entity, SPRITE_COMPONENT_TYPE);

    sfRenderWindow_drawSprite(window, sprite_c->sprite, NULL);
}

system_t *sprite_drawer_system_create(void)
{
    return system_create(SPRITE_DRAWER_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .update_handler = NULL,
        .render_handler = render_handler,
    });
}