#ifndef ENGINE_ECS_COMPONENT_H
#define ENGINE_ECS_COMPONENT_H

typedef int component_type_t;
typedef struct component_t component_t;

#define component_get_data(component, type) ((type *)component_get_raw_data(component))

component_t *component_create(component_type_t type, void *data, void (*destroy_handle)(component_t *));
void *component_get_raw_data(component_t *component);
void component_destroy(component_t *component);

#endif // ENGINE_ECS_COMPONENT_H
