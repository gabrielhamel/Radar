#include <stdlib.h>

#include <radar/components/sprite.h>
#include <engine/ecs/component.h>

static void sprite_component_destroy(component_t *component)
{
    sprite_component_t *data = component_get_data(component, sprite_component_t);
    sfSprite_destroy(data->sprite);
    sfTexture_destroy(data->texture);
    free(data);
}

component_t *sprite_component_create_from_file(const char *filepath, sprite_params_t params)
{
    sprite_component_t *data = malloc(sizeof(sprite_component_t));
    data->texture = sfTexture_createFromFile(filepath, NULL);
    sfVector2u size = sfTexture_getSize(data->texture);

    data->sprite = sfSprite_create();
    sfSprite_setTexture(data->sprite, data->texture, sfTrue);
    if (params.origin == CENTER) {
        sfSprite_setOrigin(data->sprite, (sfVector2f) {size.x / 2, size.y / 2});
    }
    sfSprite_setPosition(data->sprite, params.position);
    return component_create(SPRITE_COMPONENT_TYPE, data, sprite_component_destroy);
}
