#ifndef RADAR_AIRCRAFT_H
#define RADAR_AIRCRAFT_H

#include "radar/parser.h"

#include "engine/queue.h"
#include "engine/entity/entity.h"

typedef struct aircraft_s {
    LIST_ENTRY(aircraft_s) entry;
    entity_t *entity;
    sfVector2f departure;
    sfVector2f arrival;
    float speed;
} aircraft_t;

aircraft_t *aircraft_create_from_definition(radar_entity_definition_t *definition);
void aircraft_update(aircraft_t *aircraft, sfTime *elapsed_time);

#endif // RADAR_AIRCRAFT_H
