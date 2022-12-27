#include <stdlib.h>

#include "engine/ecs/system.h"
#include "engine/ecs/entity.h"

entity_t *entity_create(void)
{
    entity_t *entity = malloc(sizeof(entity_t));

    LIST_INIT(&entity->components);
    return entity;
}

bool entity_assign_component(entity_t *entity, component_t *component)
{
    component_t *it = NULL;

    // Check if a component of this type is already present
    LIST_FOREACH(it, &entity->components, entry) {
        if (it->type == component->type) {
            return false;
        }
    }
    LIST_INSERT_HEAD(&entity->components, component, entry);
    return true;
}

void *entity_get_component(entity_t *entity, component_type_t type)
{
    component_t *it = NULL;

    LIST_FOREACH(it, &entity->components, entry) {
        if (it->type == type) {
            return it->data;
        }
    }
    return NULL;
}
