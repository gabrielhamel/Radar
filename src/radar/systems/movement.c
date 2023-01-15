#include <engine/render/component.h>

#include <radar/systems/movement.h>
#include <radar/components/position.h>
#include <radar/components/speed.h>

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_iterator_t *it = system_get_entity_iterator(system);

    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        position_component_t *position = entity_get_component_data(entity, POSITION_COMPONENT_TYPE, position_component_t);
        speed_component_t *speed_c = entity_get_component_data(entity, SPEED_COMPONENT_TYPE, speed_component_t);
        position->position.x += speed_c->speed.x * sfTime_asSeconds(*elapsed_time);
        position->position.y += speed_c->speed.y * sfTime_asSeconds(*elapsed_time);

        component_t *render = entity_get_component(entity, RENDER_COMPONENT_TYPE);
        if (render) {
            render_component_set_position(render, position->position);
        }
    }
    entity_iterator_destroy(it);
}

system_t *movement_system_create(void)
{
    return system_create(MOVEMENT_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .update_handler = update_handler,
        .destroy_handler = NULL
    });
}