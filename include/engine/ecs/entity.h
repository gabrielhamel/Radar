#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "component.h"

typedef struct entity_s {
    LIST_ENTRY(entity_s) entry;
    LIST_HEAD(, component_s) components;
} entity_t;

entity_t *entity_create(void);
bool entity_assign_component(entity_t *entity, component_t *component);
void *entity_get_component(entity_t *entity, component_type_t type);

#endif // ENTITY_H