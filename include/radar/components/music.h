#ifndef RADAR_MUSIC_COMPONENT_H
#define RADAR_MUSIC_COMPONENT_H

#include "engine/ecs/component.h"

#define MUSIC_COMPONENT_TYPE 7

component_t *music_component_create_from_path(const char *filename);
void music_component_destroy(component_t *component);

#endif // RADAR_MUSIC_COMPONENT_H