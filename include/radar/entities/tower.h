#ifndef RADAR_TOWER_H
#define RADAR_TOWER_H

#include "radar/parser.h"
#include "engine/ecs/entity.h"

entity_t *tower_create_from_definition(radar_entity_definition_t *definition);

#endif // RADAR_TOWER_H


