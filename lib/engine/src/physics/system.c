#include "system.h"
#include "component.h"
#include "../render/component.h"

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        physics_component_t *physics = entity_get_component_data(entity, PHYSICS_COMPONENT_TYPE, physics_component_t);
        physics->position.x += physics->speed.x * sfTime_asSeconds(*elapsed_time);
        physics->position.y += physics->speed.y * sfTime_asSeconds(*elapsed_time);

        component_t *render = entity_get_component(entity, RENDER_COMPONENT_TYPE);
        if (render) {
            render_component_set_position(render, physics->position);
        }
    }
    entity_iterator_destroy(it);
}

system_t *physics_system_create(void)
{
    return system_create(PHYSICS_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .update_handler = update_handler,
        .destroy_handler = NULL
    });
}