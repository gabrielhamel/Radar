#ifndef ENGINE_ECS_ENTITY_H
#define ENGINE_ECS_ENTITY_H

#include <stdbool.h>

#include "component.h"

typedef struct entity_t entity_t;

#define entity_get_component_data(entity, component_type, data_type) \
    (component_get_data(entity_get_component(entity, component_type), data_type))

typedef struct {
    entity_t *current;
} entity_iterator_t;

typedef struct entity_set_t entity_set_t;

entity_t *entity_create(void);
void entity_destroy(entity_t *entity);
bool entity_assign_component(entity_t *entity, component_t *component);
component_t *entity_remove_component(entity_t *entity, component_type_t type);
component_t *entity_get_component(entity_t *entity, component_type_t type);
entity_t *entity_iterator_next(entity_iterator_t *iterator);
void entity_iterator_destroy(entity_iterator_t *iterator);

entity_set_t *entity_set_create(void);
bool entity_set_append(entity_set_t *set, entity_t *entity);
entity_iterator_t *entity_set_get_iterator(entity_set_t *set);
void entity_set_empty(entity_set_t *set);
void entity_set_destroy(entity_set_t *set);

#endif // ENGINE_ECS_ENTITY_H