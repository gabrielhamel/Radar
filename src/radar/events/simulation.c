#include <SFML/Graphics.h>

#include "engine/ecs/scene.h"
#include "radar/systems/hitbox.h"

static void quit_simulation()
{
    scene_close(scene_get());
}

static void toogle_hitbox(system_t *hitbox_system)
{
    hitbox_system_t *context = SYSTEM_CONTEXT(hitbox_system, hitbox_system_t);
    context->render_enabled = !context->render_enabled;
}

events_handler_t *simulation_event_handler_create(system_t *hitbox_system)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, (void (*)(void *))quit_simulation, NULL);
    eh_bind_window_closed(eh, (void (*)(void *))quit_simulation, NULL);
    eh_bind_key_pressed(eh, sfKeyH, (void (*)(void *))toogle_hitbox, hitbox_system);
    return eh;
}