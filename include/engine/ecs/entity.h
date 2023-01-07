#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "component.h"

typedef struct entity_s {
    TAILQ_ENTRY(entity_s) entry;
    TAILQ_HEAD(, component_s) components;
} entity_t;

typedef struct entity_link_s {
    TAILQ_ENTRY(entity_link_s) entry;
    entity_t *entity;
} entity_link_t;

entity_t *entity_create(void);
void entity_destroy(entity_t *entity);
bool entity_assign_component(entity_t *entity, component_t *component);
component_t *entity_remove_component(entity_t *entity, component_type_t type);
component_t *entity_get_component(entity_t *entity, component_type_t type);
entity_link_t *entity_get_link(entity_t *entity);

#endif // ENTITY_H