#ifndef SCENE_H
#define SCENE_H

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
} scene_t;

scene_t *scene_create(void);
void scene_append_entity(scene_t *scene, entity_t *entity);
bool scene_append_system(scene_t *scene, system_t *system);
bool scene_subscribe_entity_to_system(scene_t *scene, entity_t *entity, system_type_t system_type);
void scene_update_systems(scene_t *scene, sfTime *elapsed_time);

#endif // SCENE_H