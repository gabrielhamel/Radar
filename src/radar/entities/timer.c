#include "engine/ecs/entity.h"
#include "engine/ui/element.h"
#include "engine/text/unicode.h"
#include "radar/components/ui_link.h"

entity_t *ui_timer_create(void)
{
    ui_element_t *timer = ui_element_create((sfIntRect){
        1800,
        0,
        120,
        30
    });
    ui_element_set_font(timer, "assets/fonts/Hack-Regular.ttf");

    sfUint32 text[9] = {0};
    string_to_utf8(text, "00:00:00", 9);
    ui_element_set_text(timer, text);

    ui_element_set_background_color(timer, sfGreen);
    entity_t *entity = entity_create();
    entity_assign_component(entity, ui_link_component_create(timer));
    return entity;
}