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

typedef struct {
    entity_t *current;
    entity_link_t *link;
    entity_link_t *next;
} entity_iterator_t;

typedef struct {
    TAILQ_HEAD(, entity_link_s) entities;
} entity_set_t;

entity_t *entity_create(void);
void entity_destroy(entity_t *entity);
bool entity_assign_component(entity_t *entity, component_t *component);
component_t *entity_remove_component(entity_t *entity, component_type_t type);
component_t *entity_get_component(entity_t *entity, component_type_t type);
entity_link_t *entity_link_create(entity_t *entity);
void entity_link_destroy(entity_link_t *link);
entity_t *entity_iterator_next(entity_iterator_t *iterator);
void entity_iterator_destroy(entity_iterator_t *iterator);

entity_set_t *entity_set_create(void);
bool entity_set_append(entity_set_t *set, entity_t *entity);
entity_iterator_t *entity_set_get_iterator(entity_set_t *set);
void entity_set_destroy(entity_set_t *set);
void entity_set_empty(entity_set_t *set);

#endif // ENTITY_H