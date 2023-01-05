#include "radar/systems/sprite_drawer.h"
#include "radar/components/sprite.h"

static void render_handler(system_t *system, sfRenderWindow *window)
{
    entity_link_t *entity_link = NULL;
    TAILQ_FOREACH(entity_link, &system->entities_subscribed, entry) {
        entity_t *entity = entity_link->entity;

        sprite_component_t *sprite_c = entity_get_component(entity, SPRITE_COMPONENT_TYPE);
        sfRenderWindow_drawSprite(window, sprite_c->sprite, NULL);
    }
}

system_t *sprite_drawer_system_create(void)
{
    return system_create(SPRITE_DRAWER_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .update_handler = NULL,
        .render_handler = render_handler,
    });
}