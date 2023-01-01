#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.h>

#include "../queue.h"
#include "entity.h"

typedef int system_type_t;

typedef struct {
    void *context;
    void (*update_handler)(entity_t *, sfTime *, void *);
    void (*render_handler)(entity_t *, sfRenderWindow *, void *);
} system_params_t;

typedef struct system_s {
    LIST_ENTRY(system_s) entry;
    system_type_t type;
    void *context;
    void (*update_handler)(entity_t *, sfTime *, void *);
    void (*render_handler)(entity_t *, sfRenderWindow *, void *);
} system_t;

system_t *system_create(system_type_t type, system_params_t params);

#endif // SYSTEM_H