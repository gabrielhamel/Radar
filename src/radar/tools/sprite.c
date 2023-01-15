#include <stdlib.h>

#include <radar/tools/sprite.h>

sfSprite *sprite_create_from_file(const char *filepath, sprite_params_t params)
{
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfVector2u size = sfTexture_getSize(texture);

    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    if (params.origin == CENTER) {
        sfSprite_setOrigin(sprite, (sfVector2f) {size.x / 2, size.y / 2});
    }
    sfSprite_setPosition(sprite, params.position);
    return sprite;
}
