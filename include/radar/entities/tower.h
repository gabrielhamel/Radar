#ifndef RADAR_TOWER_H
#define RADAR_TOWER_H

#include "radar/parser.h"

#include "engine/queue.h"
#include "engine/entity/entity.h"

typedef struct tower_s {
    LIST_ENTRY(tower_s) entry;
    entity_t *entity;
} tower_t;

tower_t *tower_create_from_definition(radar_entity_definition_t *definition);
void tower_update(tower_t *tower, sfTime *elapsed_time);

#endif // RADAR_TOWER_H


