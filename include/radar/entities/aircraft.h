#ifndef RADAR_AIRCRAFT_H
#define RADAR_AIRCRAFT_H

#include <radar/parser.h>
#include <engine/ecs/scene.h>

void aircraft_scene_append(scene_t *scene, radar_entity_definition_t *definition);

#endif // RADAR_AIRCRAFT_H
