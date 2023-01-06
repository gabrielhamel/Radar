#ifndef SCENE_H
#define SCENE_H

#include "engine/ui/element.h"
#include "engine/ecs/entity.h"
#include "engine/ecs/system.h"

typedef struct {
    TAILQ_HEAD(, entity_s) entities;
    TAILQ_HEAD(, system_s) systems;
    TAILQ_HEAD(, events_handler_s) events_handlers;
    ui_element_t *ui_element_root;
} scene_t;

scene_t *scene_create(void);
scene_t *scene_get(void);
void scene_append_entity(scene_t *scene, entity_t *entity);
void scene_remove_entity(scene_t *scene, entity_t *entity);
bool scene_append_system(scene_t *scene, system_t *system);
system_t *scene_get_system(scene_t *scene, system_type_t system);
void scene_systems_update(scene_t *scene, sfTime *elapsed_time);
void scene_systems_render(scene_t *scene, sfRenderWindow *window);
void scene_ui_render(scene_t *scene, sfRenderWindow *window);
ui_element_t *scene_get_ui_root(scene_t *scene);
void scene_handle_event(scene_t *scene, sfEvent *event);
void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler);

#endif // SCENE_H