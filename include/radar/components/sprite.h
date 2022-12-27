#ifndef RADAR_SPRITE_COMPONENT_H
#define RADAR_SPRITE_COMPONENT_H

#include <SFML/Graphics.h>

#include "engine/ecs/component.h"

#define SPRITE_COMPONENT_TYPE 3

typedef struct {
    sfVector2f position;
} sprite_params_t;

typedef struct {
    sfSprite *sprite;
} sprite_component_t;

component_t *sprite_component_create_from_file(const char *filepath, sprite_params_t params);

#endif // RADAR_SPRITE_COMPONENT_H