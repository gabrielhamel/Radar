#include <SFML/Graphics.h>

#include "engine/ecs/scene.h"
#include "radar/systems/hitbox.h"
#include "radar/components/hitbox.h"

static void quit_simulation()
{
    scene_close(scene_get());
}

static void toogle_hitbox(system_t *hitbox_system)
{
    hitbox_system_t *context = SYSTEM_CONTEXT(hitbox_system, hitbox_system_t);
    context->render_enabled = !context->render_enabled;

    entity_link_t *it = NULL;
    TAILQ_FOREACH(it, &hitbox_system->entities_subscribed, entry) {
        component_t *hitbox_c = entity_get_component(it->entity, HITBOX_COMPONENT_TYPE);
        hitbox_component_t *hitbox = COMPONENT_DATA(hitbox_c, hitbox_component_t);
        if (hitbox->type == CUSTOM) {
            if (context->render_enabled) {
                sfConvexShape_setOutlineThickness(hitbox->csfml_object, 2);
            } else {
                sfConvexShape_setOutlineThickness(hitbox->csfml_object, 0);
            }
        }
    }
}

events_handler_t *simulation_event_handler_create(system_t *hitbox_system)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, (void (*)(void *))quit_simulation, NULL);
    eh_bind_window_closed(eh, (void (*)(void *))quit_simulation, NULL);
    eh_bind_key_pressed(eh, sfKeyH, (void (*)(void *))toogle_hitbox, hitbox_system);
    return eh;
}