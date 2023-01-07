#include <stdlib.h>

#include "radar/components/sprite.h"
#include "engine/ecs/component.h"

component_t *sprite_component_create_from_file(const char *filepath, sprite_params_t params)
{
    sprite_component_t *data = malloc(sizeof(sprite_component_t));
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfVector2u size = sfTexture_getSize(texture);

    data->sprite = sfSprite_create();
    sfSprite_setTexture(data->sprite, texture, sfTrue);
    if (params.origin == CENTER) {
        sfSprite_setOrigin(data->sprite, (sfVector2f) {size.x / 2, size.y / 2});
    }
    sfSprite_setPosition(data->sprite, params.position);
    return component_create(SPRITE_COMPONENT_TYPE, data);
}

void sprite_component_destroy(component_t *component)
{
    sfSprite_destroy(COMPONENT_DATA(component, sprite_component_t)->sprite);
    free(component->data);
    component_destroy(component);
}