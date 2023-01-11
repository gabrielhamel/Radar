#ifndef RADAR_SCENE_H
#define RADAR_SCENE_H

#include <engine/ecs/scene.h>

bool radar_init_from_script(scene_t *scene, const char *filepath);
events_handler_t *simulation_event_handler_create(system_t *hitbox_system);

#endif // RADAR_SCENE_H