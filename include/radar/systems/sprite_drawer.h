#ifndef RADAR_SPRITE_DRAWER_SYSTEM_H
#define RADAR_SPRITE_DRAWER_SYSTEM_H

#include <SFML/Graphics.h>
#include "engine/ecs/system.h"

#define SPRITE_DRAWER_SYSTEM_TYPE 1

system_t *sprite_drawer_system_create(void);

#endif // RADAR_SPRITE_DRAWER_SYSTEM_H