#ifndef RADAR_SCENE_H
#define RADAR_SCENE_H

#include "engine/scene.h"

bool radar_init_from_script(scene_t *scene, const char *filepath);
events_handler_t *simulation_event_handler_create(bool *hitbox_enabled);

#endif // RADAR_SCENE_H