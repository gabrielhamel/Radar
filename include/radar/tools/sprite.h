#ifndef RADAR_TOOLS_SPRITE_H
#define RADAR_TOOLS_SPRITE_H

#include <SFML/Graphics.h>

typedef enum {
    TOP_LEFT,
    CENTER,
} sprite_origin_t;

typedef struct {
    sfVector2f position;
    sprite_origin_t origin;
} sprite_params_t;

sfSprite *sprite_create_from_file(const char *filepath, sprite_params_t params);
void sprite_destroy(sfSprite *sprite);

#endif // RADAR_TOOLS_SPRITE_H
