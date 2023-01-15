#include <SFML/Graphics.h>

void sprite_destroy(sfSprite *sprite)
{
    sfTexture *texture = (sfTexture *)sfSprite_getTexture(sprite);
    sfSprite_destroy(sprite);
    if (texture) {
        sfTexture_destroy(texture);
    }
}

void convex_shape_destroy(sfConvexShape *shape)
{
    sfTexture *texture = (sfTexture *)sfConvexShape_getTexture(shape);
    sfConvexShape_destroy(shape);
    if (texture) {
        sfTexture_destroy(texture);
    }
}
