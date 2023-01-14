#include <stdlib.h>

#include <engine/text/unicode.h>

#include <radar/systems/timer.h>
#include <radar/components/ui_link.h>

static void update_timer(entity_t *entity, unsigned int hours, unsigned int minutes, unsigned int seconds)
{
    ui_element_t *timer = entity_get_component_data(entity, UI_LINK_COMPONENT_TYPE, ui_element_t);

    sfUint32 text[] = {
            '0' + hours / 10,
            '0' + hours % 10,
            ':',
            '0' + minutes / 10,
            '0' + minutes % 10,
            ':',
            '0' + seconds / 10,
            '0' + seconds % 10,
            '\0'
    };

    ui_element_set_text(timer, text);
}

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    sfTime *total_time = system_get_context(system, sfTime);
    total_time->microseconds += elapsed_time->microseconds;
    unsigned int hours = total_time->microseconds / 3600000000;
    unsigned int minutes = total_time->microseconds % 3600000000 / 60000000;
    unsigned int seconds = total_time->microseconds % 3600000000 % 60000000 / 1000000;

    entity_iterator_t *it = system_get_entity_iterator(system);
    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        update_timer(entity, hours, minutes, seconds);
    }
    entity_iterator_destroy(it);
}

static void destroy_handler(system_t *system)
{
    free(system_get_raw_context(system));
}

system_t *timer_system_create(void)
{
    sfTime *elapsed_time = malloc(sizeof(sfTime));
    *elapsed_time = sfTime_Zero;
    return system_create(TIMER_SYSTEM_TYPE, (system_params_t){
        .context = elapsed_time,
        .update_handler = update_handler,
        .destroy_handler = destroy_handler
    });
}