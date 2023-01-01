#ifndef SCENE_H
#define SCENE_H

#include "ui/element.h"
#include "ecs/entity.h"
#include "ecs/system.h"

typedef struct entity_system_subscribe_link_s {
    LIST_ENTRY(entity_system_subscribe_link_s) entry;
    system_t *system;
    entity_t *entity;
} entity_system_subscribe_link_t;

typedef struct {
    LIST_HEAD(, entity_s) entities;
    LIST_HEAD(, system_s) systems;
    LIST_HEAD(, entity_system_subscribe_link_s) entities_to_systems;
    LIST_HEAD(, events_handler_s) events_handlers;
    ui_element_t *ui_element_root;
} scene_t;

scene_t *scene_create(void);
void scene_append_entity(scene_t *scene, entity_t *entity);
bool scene_append_system(scene_t *scene, system_t *system);
bool scene_subscribe_entity_to_system(scene_t *scene, entity_t *entity, system_type_t system_type);
void scene_systems_update(scene_t *scene, sfTime *elapsed_time);
void scene_systems_render(scene_t *scene, sfRenderWindow *window);
void scene_ui_render(scene_t *scene, sfRenderWindow *window);
ui_element_t *scene_get_ui_root(scene_t *scene);
void scene_handle_event(scene_t *scene, sfEvent *event);
void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler);

#endif // SCENE_H