#ifndef COMPONENT_H
#define COMPONENT_H

#include "../queue.h"

#define component_get_data(component, type) ((type *)component_get_raw_data(component))

typedef int component_type_t;

typedef struct component_s {
    TAILQ_ENTRY(component_s) entry;
    component_type_t type;
    void *data;
    void (*destroy_handle)(struct component_s *);
} component_t;

component_t *component_create(component_type_t type, void *data, void (*destroy_handle)(struct component_s *));
void *component_get_raw_data(component_t *component);
void component_destroy(component_t *component);

#endif // COMPONENT_H