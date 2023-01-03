#ifndef RADAR_SIMULATION_SYSTEM_H
#define RADAR_SIMULATION_SYSTEM_H

#include "engine/scene.h"
#include "engine/ecs/system.h"
#include "radar/parser.h"

#define SIMULATION_SYSTEM_TYPE 5

typedef struct {
    scene_t *scene;
    radar_definition_t *def;
    sfTime *timer;
} simulation_system_t;

system_t *simulation_system_create(scene_t *scene, sfTime *timer, radar_definition_t *def);

#endif // RADAR_SIMULATION_SYSTEM_H