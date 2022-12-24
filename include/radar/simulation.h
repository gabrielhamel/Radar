#ifndef RADAR_SCENE_H
#define RADAR_SCENE_H

#include "engine/scene.h"
#include "engine/entity/entity.h"

#include "radar/parser.h"
#include "radar/entities/aircraft.h"
#include "radar/entities/tower.h"

typedef struct {
    LIST_HEAD(, aircraft_s) aircrafts;
    LIST_HEAD(, tower_s) towers;
    scene_t *scene;
} simulation_t;

simulation_t *simulation_create_from_script(const char *filepath);
void simulation_update(simulation_t *simulation, sfTime *elapsed_time);
void simulation_append_tower(simulation_t *simulation, tower_t *tower);
void simulation_append_aircraft(simulation_t *simulation, aircraft_t *aircraft);

#endif // RADAR_SCENE_H