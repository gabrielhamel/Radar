#include "radar/components/ui_link.h"

component_t *ui_link_component_create(ui_element_t *element)
{
    return component_create(UI_LINK_COMPONENT_TYPE, element);
}