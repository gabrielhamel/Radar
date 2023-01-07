#ifndef RADAR_TOWER_H
#define RADAR_TOWER_H

#include "radar/parser.h"
#include "engine/ecs/scene.h"
#include "engine/ecs/entity.h"

void tower_scene_append(scene_t *scene, radar_entity_definition_t *definition);
void tower_scene_destroy(scene_t *scene, entity_t *aircraft);

#endif // RADAR_TOWER_H


