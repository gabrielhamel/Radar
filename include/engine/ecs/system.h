#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/System/Time.h>

#include "../queue.h"
#include "entity.h"

typedef int system_type_t;

typedef struct {
    void *update_context;
    void (*update_handler)(entity_t *, sfTime *, void *);
} system_params_t;

typedef struct system_s {
    LIST_ENTRY(system_s) entry;
    system_type_t type;
    void *update_context;
    void (*update_handler)(entity_t *, sfTime *, void *);
} system_t;

system_t *system_create(system_type_t type, system_params_t params);
bool system_subscribe_entity(system_t *system, entity_t *entity);

#endif // SYSTEM_H