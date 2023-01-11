#include <radar/systems/sprite_drawer.h>
#include <radar/components/sprite.h>

static void render_handler(system_t *system, sfRenderWindow *window)
{
    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        sprite_component_t *sprite = entity_get_component_data(entity, SPRITE_COMPONENT_TYPE, sprite_component_t);
        sfRenderWindow_drawSprite(window, sprite->sprite, NULL);
    }
    entity_iterator_destroy(it);
}

system_t *sprite_drawer_system_create(void)
{
    return system_create(SPRITE_DRAWER_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .update_handler = NULL,
        .render_handler = render_handler,
        .destroy_handler = NULL
    });
}