#ifndef RADAR_AIRCRAFT_H
#define RADAR_AIRCRAFT_H

#include "radar/parser.h"
#include "engine/ecs/entity.h"

entity_t *aircraft_create_from_definition(radar_entity_definition_t *definition);

#endif // RADAR_AIRCRAFT_H
