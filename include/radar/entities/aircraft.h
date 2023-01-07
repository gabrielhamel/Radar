#ifndef RADAR_AIRCRAFT_H
#define RADAR_AIRCRAFT_H

#include "radar/parser.h"
#include "engine/ecs/scene.h"
#include "engine/ecs/entity.h"

void aircraft_scene_append(scene_t *scene, radar_entity_definition_t *definition);
void aircraft_scene_destroy(scene_t *scene, entity_t *aircraft);

#endif // RADAR_AIRCRAFT_H
