#ifndef RADAR_TTL_COMPONENT_H
#define RADAR_TTL_COMPONENT_H

#include <engine/ecs/component.h>

#define TTL_COMPONENT_TYPE 6

component_t *ttl_component_create(float remaining_time);

#endif // RADAR_TTL_COMPONENT_H