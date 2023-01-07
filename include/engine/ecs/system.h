#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.h>

#include "../queue.h"
#include "entity.h"

#define SYSTEM_CONTEXT(system, context_type)((context_type *)system->context)

typedef int system_type_t;

typedef struct system_s {
    TAILQ_ENTRY(system_s) entry;
    system_type_t type;
    void *context;
    void (*update_handler)(struct system_s *, sfTime *);
    void (*render_handler)(struct system_s *, sfRenderWindow *);
    TAILQ_HEAD(, entity_link_s) entities_subscribed;
    void (*destroy_handler)(struct system_s *);
} system_t;

typedef struct {
    void *context;
    void (*update_handler)(struct system_s *, sfTime *);
    void (*render_handler)(struct system_s *, sfRenderWindow *);
    void (*destroy_handler)(struct system_s *);
} system_params_t;

system_t *system_create(system_type_t type, system_params_t params);
bool system_subscribe_entity(system_t *system, entity_t *entity);
bool system_unsubscribe_entity(system_t *system, entity_t *entity);

#endif // SYSTEM_H