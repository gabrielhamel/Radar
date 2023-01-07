#include <stdlib.h>

#include "engine/ecs/system.h"

system_t *system_create(system_type_t type, system_params_t params)
{
    system_t *system = malloc(sizeof(system_t));

    system->type = type;
    system->context = params.context;
    system->update_handler = params.update_handler;
    system->render_handler = params.render_handler;
    TAILQ_INIT(&system->entities_subscribed);
    return system;
}

bool system_subscribe_entity(system_t *system, entity_t *entity)
{
    entity_link_t *it = NULL;

    TAILQ_FOREACH(it, &system->entities_subscribed, entry) {
        if (entity == it->entity) {
            return false;
        }
    }

    entity_link_t *link = entity_get_link(entity);
    TAILQ_INSERT_TAIL(&system->entities_subscribed, link, entry);
    return true;
}

bool system_unsubscribe_entity(system_t *system, entity_t *entity)
{
    entity_link_t *it = NULL;
    entity_link_t *tmp = NULL;

    TAILQ_FOREACH_SAFE(it, &system->entities_subscribed, entry, tmp) {
        if (entity == it->entity) {
            TAILQ_REMOVE(&system->entities_subscribed, it, entry);
            free(it);
            return true;
        }
    }
    return false;
}