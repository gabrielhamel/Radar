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
void scene_remove_entity(scene_t *scene, entity_t *entity);
void scene_destroy_entity(scene_t *scene, entity_t *entity);
bool scene_append_system(scene_t *scene, system_t *system);
system_t *scene_get_system(scene_t *scene, system_type_t system);
void scene_systems_update(scene_t *scene, sfTime *elapsed_time);
void scene_systems_render(scene_t *scene, sfRenderWindow *window);
void scene_ui_render(scene_t *scene, sfRenderWindow *window);
ui_element_t *scene_get_ui_root(scene_t *scene);
void scene_handle_event(scene_t *scene, sfEvent *event);
void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler);
void scene_empty(scene_t *scene);
void scene_destroy_system(scene_t *scene, system_t *system);
void scene_close(scene_t *scene);

#endif // ENGINE_ECS_SCENE_H