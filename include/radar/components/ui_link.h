#ifndef RADAR_UI_LINK_COMPONENT_H
#define RADAR_UI_LINK_COMPONENT_H

#include <engine/ui/element.h>
#include <engine/ecs/component.h>

#define UI_LINK_COMPONENT_TYPE 4

component_t *ui_link_component_create(ui_element_t *element);

#endif // RADAR_UI_LINK_COMPONENT_H