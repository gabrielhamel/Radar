#ifndef RADAR_STORM_H
#define RADAR_STORM_H

#include <engine/ecs/scene.h>
#include "radar/parser.h"

#define CONVEX_SHAPE_RENDER_ID 0

void storm_scene_append(scene_t *scene, radar_entity_definition_t *definition);

#endif // RADAR_STORM_H

