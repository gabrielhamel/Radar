#include "system.h"
#include "../engine.h"
#include "component.h"

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        component_t *component = entity_get_component(entity, RENDER_COMPONENT_TYPE);
        render_component_draw(component, system->context);
    }
    entity_iterator_destroy(it);
}

system_t *render_system_create(void)
{
    return system_create(RENDER_SYSTEM_TYPE, (system_params_t){
        .context = engine_get_window(engine_get()),
        .update_handler = update_handler,
        .destroy_handler = NULL
    });
}