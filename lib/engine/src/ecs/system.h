#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.h>

#include "../queue.h"
#include "entity.h"

#define system_get_context(system, type) ((type *)system_get_raw_context(system))

typedef int system_type_t;

typedef struct system_s {
    TAILQ_ENTRY(system_s) entry;
    system_type_t type;
    void *context;
    void (*update_handler)(struct system_s *, sfTime *);
    TAILQ_HEAD(, entity_link_s) entities_subscribed;
    void (*destroy_handler)(struct system_s *);
} system_t;

typedef struct {
    void *context;
    void (*update_handler)(struct system_s *, sfTime *);
    void (*destroy_handler)(struct system_s *);
} system_params_t;

system_t *system_create(system_type_t type, system_params_t params);
void *system_get_raw_context(system_t *system);
bool system_subscribe_entity(system_t *system, entity_t *entity);
bool system_unsubscribe_entity(system_t *system, entity_t *entity);
entity_iterator_t *system_get_entity_iterator(system_t *system);

#endif // SYSTEM_H