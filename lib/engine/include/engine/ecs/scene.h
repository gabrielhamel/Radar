#ifndef ENGINE_ECS_SCENE_H
#define ENGINE_ECS_SCENE_H

#include <stdbool.h>

#include "../ui/element.h"
#include "entity.h"
#include "system.h"
#include "../events/events.h"

typedef struct scene_t scene_t;

scene_t *scene_create(void);
scene_t *scene_get(void);
void scene_append_entity(scene_t *scene, entity_t *entity);
void scene_destroy_entity(scene_t *scene, entity_t *entity);
bool scene_append_system(scene_t *scene, system_t *system);
system_t *scene_get_system(scene_t *scene, system_type_t system);
ui_element_t *scene_get_ui_root(scene_t *scene);
void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler);
void scene_close(scene_t *scene);

#endif // ENGINE_ECS_SCENE_H