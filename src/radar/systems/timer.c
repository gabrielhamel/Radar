#include <stdlib.h>

#include "engine/text/unicode.h"

#include "radar/systems/timer.h"
#include "radar/components/ui_link.h"

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_link_t *entity_link = NULL;
    TAILQ_FOREACH(entity_link, &system->entities_subscribed, entry) {
        entity_t *entity = entity_link->entity;

        sfTime *total_time = system->context;
        ui_element_t *timer_ui = entity_get_component(entity, UI_LINK_COMPONENT_TYPE)->data;

        total_time->microseconds += elapsed_time->microseconds;

        unsigned int hours = total_time->microseconds / 3600000000;
        unsigned int minutes = total_time->microseconds % 3600000000 / 60000000;
        unsigned int seconds = total_time->microseconds % 3600000000 % 60000000 / 1000000;

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

         ui_element_set_text(timer_ui, text);
    }
}

static void destroy_handler(system_t *system)
{
    free(SYSTEM_CONTEXT(system, sfTime));
}

system_t *timer_system_create(void)
{
    sfTime *elapsed_time = malloc(sizeof(sfTime));
    *elapsed_time = sfTime_Zero;
    return system_create(TIMER_SYSTEM_TYPE, (system_params_t){
        .context = elapsed_time,
        .update_handler = update_handler,
        .render_handler = NULL,
        .destroy_handler = destroy_handler
    });
}