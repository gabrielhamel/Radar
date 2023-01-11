#include <stdlib.h>

#include "system.h"
#include "entity.h"

entity_t *entity_create(void)
{
    entity_t *entity = malloc(sizeof(entity_t));

    TAILQ_INIT(&entity->components);
    return entity;
}

void entity_destroy(entity_t *entity)
{
    component_t *component = NULL;
    component_t *tmp = NULL;

    TAILQ_FOREACH_SAFE(component, &entity->components, entry, tmp) {
        component_destroy(component);
    }
    free(entity);
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

component_t *entity_remove_component(entity_t *entity, component_type_t type)
{
    component_t *it = NULL;
    component_t *tmp = NULL;

    TAILQ_FOREACH_SAFE(it, &entity->components, entry, tmp) {
        if (it->type == type) {
            TAILQ_REMOVE(&entity->components, it, entry);
            return it;
        }
    }
    return NULL;
}

component_t *entity_get_component(entity_t *entity, component_type_t type)
{
    component_t *it = NULL;

    TAILQ_FOREACH(it, &entity->components, entry) {
        if (it->type == type) {
            return it;
        }
    }
    return NULL;
}

entity_link_t *entity_link_create(entity_t *entity)
{
    entity_link_t *link = malloc(sizeof(entity_link_t));

    link->entity = entity;
    link->entry.tqe_next = NULL;
    link->entry.tqe_prev = NULL;
    return link;
}

void entity_link_destroy(entity_link_t *link)
{
    free(link);
}

entity_t *entity_iterator_next(entity_iterator_t *iterator)
{
    if (iterator->next == NULL) {
        return NULL;
    }
    iterator->link = iterator->next;
    iterator->current = !iterator->link ? NULL : iterator->link->entity;
    iterator->next = !iterator->link ? NULL : iterator->link->entry.tqe_next;
    return iterator->current;
}

void entity_iterator_destroy(entity_iterator_t *iterator)
{
    free(iterator);
}

entity_set_t *entity_set_create(void)
{
    entity_set_t *set = malloc(sizeof(entity_set_t));

    TAILQ_INIT(&set->entities);
    return set;
}

bool entity_set_append(entity_set_t *set, entity_t *entity)
{
    // Check if the entity is already present
    entity_link_t *it = NULL;
    TAILQ_FOREACH(it, &set->entities, entry) {
        if (it->entity == entity) {
            return false;
        }
    }

    entity_link_t *link = entity_link_create(entity);
    TAILQ_INSERT_TAIL(&set->entities, link, entry);
    return true;
}

entity_iterator_t *entity_set_get_iterator(entity_set_t *set)
{
    entity_iterator_t *it = malloc(sizeof(entity_iterator_t));
    it->link = set->entities.tqh_first;
    it->current = it->link ? it->link->entity : NULL;
    it->next = it->link ? it->link->entry.tqe_next : NULL;
    return it;
}

void entity_set_empty(entity_set_t *set)
{
    entity_link_t *it = NULL;
    entity_link_t *tmp = NULL;
    TAILQ_FOREACH_SAFE(it, &set->entities, entry, tmp) {
        TAILQ_REMOVE(&set->entities, it, entry);
        entity_link_destroy(it);
    }
}

void entity_set_destroy(entity_set_t *set)
{
    entity_set_empty(set);
    free(set);
}

