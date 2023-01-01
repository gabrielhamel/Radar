#include <stdlib.h>
#include <stdio.h>

#include "engine/text/unicode.h"
#include "radar/systems/timer.h"
#include "radar/components/ui_link.h"

static void update_handler(entity_t *entity, sfTime *elapsed_time, sfTime *total_time)
{
    ui_element_t *timer_ui = entity_get_component(entity, UI_LINK_COMPONENT_TYPE);

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

system_t *timer_system_create(void)
{
    sfTime *elapsed_time = malloc(sizeof(sfTime));
    *elapsed_time = sfTime_Zero;
    return system_create(TIMER_SYSTEM_TYPE, (system_params_t){
        .context = elapsed_time,
        .update_handler = update_handler,
        .render_handler = NULL,
    });
}