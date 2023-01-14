#ifndef ENGINE_ECS_SYSTEM_H
#define ENGINE_ECS_SYSTEM_H

#include <SFML/Graphics.h>

#include "entity.h"

typedef struct system_t system_t;
typedef int system_type_t;

#define system_get_context(system, type) ((type *)system_get_raw_context(system))

typedef struct {
    void *context;
    void (*update_handler)(system_t *, sfTime *);
    void (*destroy_handler)(system_t *);
} system_params_t;

system_t *system_create(system_type_t type, system_params_t params);
void *system_get_raw_context(system_t *system);
bool system_subscribe_entity(system_t *system, entity_t *entity);
bool system_unsubscribe_entity(system_t *system, entity_t *entity);
entity_iterator_t *system_get_entity_iterator(system_t *system);

#endif // ENGINE_ECS_SYSTEM_H
