#include <stdlib.h>

#include "engine/ecs/system.h"
#include "engine/ecs/entity.h"

entity_t *entity_create(void)
{
    entity_t *entity = malloc(sizeof(entity_t));

    TAILQ_INIT(&entity->components);
    return entity;
}

bool entity_assign_component(entity_t *entity, component_t *component)
{
    component_t *it = NULL;

    // Check if a component of this type is already present
    TAILQ_FOREACH(it, &entity->components, entry) {
        if (it->type == component->type) {
            return false;
        }
    }
    TAILQ_INSERT_HEAD(&entity->components, component, entry);
    return true;
}

void *entity_get_component(entity_t *entity, component_type_t type)
{
    component_t *it = NULL;

    TAILQ_FOREACH(it, &entity->components, entry) {
        if (it->type == type) {
            return it->data;
        }
    }
    return NULL;
}

entity_link_t *entity_get_link(entity_t *entity)
{
    entity_link_t *link = malloc(sizeof(entity_link_t));

    link->entity = entity;
    link->entry.tqe_next = NULL;
    link->entry.tqe_prev = NULL;
    return link;
}