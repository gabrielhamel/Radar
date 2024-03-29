#include <SFML/Graphics.h>

#include <engine/ecs/scene.h>
#include <engine/render/component.h>

#include "radar/systems/hitbox.h"
#include "radar/components/hitbox.h"
#include "radar/entities/storm.h"
#include "radar/entities/aircraft.h"

static void quit_simulation()
{
    scene_close(scene_get());
}

static void toogle_hitbox(system_t *hitbox_system)
{
    hitbox_system_t *context = system_get_context(hitbox_system, hitbox_system_t);
    context->render_enabled = !context->render_enabled;

    entity_iterator_t *it = system_get_entity_iterator(hitbox_system);
    entity_t *entity = it->current;

    while (entity) {
        component_t *hitbox_c = entity_get_component(entity, HITBOX_COMPONENT_TYPE);
        hitbox_component_t *hitbox = component_get_data(hitbox_c, hitbox_component_t);
        component_t *render = entity_get_component(entity, RENDER_COMPONENT_TYPE);
        if (hitbox->type == CUSTOM) {
            sfConvexShape *shape = render_component_get_raw_csfml_object(render, CONVEX_SHAPE_RENDER_ID);
            if (context->render_enabled) {
                sfConvexShape_setOutlineThickness(shape, 2);
            } else {
                sfConvexShape_setOutlineThickness(shape, 0);
            }
        } else if (hitbox->type == RECT) {
            sfRectangleShape *shape = render_component_get_raw_csfml_object(render, HITBOX_RENDER_ID);
            if (context->render_enabled) {
                sfRectangleShape_setOutlineThickness(shape, 2);
            } else {
                sfRectangleShape_setOutlineThickness(shape, 0);
            }
        } else if (hitbox->type == CIRCLE) {
            sfCircleShape *shape = render_component_get_raw_csfml_object(render, HITBOX_RENDER_ID);
            if (context->render_enabled) {
                sfCircleShape_setOutlineThickness(shape, 2);
            } else {
                sfCircleShape_setOutlineThickness(shape, 0);
            }
        }
        entity = entity_iterator_next(it);
    }
    entity_iterator_destroy(it);
}

events_handler_t *simulation_event_handler_create(system_t *hitbox_system)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, (void (*)(void *))quit_simulation, NULL);
    eh_bind_window_closed(eh, (void (*)(void *))quit_simulation, NULL);
    eh_bind_key_pressed(eh, sfKeyH, (void (*)(void *))toogle_hitbox, hitbox_system);
    return eh;
}