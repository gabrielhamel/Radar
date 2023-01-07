#ifndef RADAR_TTL_COMPONENT_H
#define RADAR_TTL_COMPONENT_H

#include <SFML/System.h>

#include "engine/ecs/component.h"

#define TTL_COMPONENT_TYPE 6

component_t *ttl_component_create(float remaining_time);
void ttl_component_destroy(component_t *component);

#endif // RADAR_TTL_COMPONENT_H