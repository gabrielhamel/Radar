#include <stdio.h>
#include <SFML/Graphics.h>

#include "engine/engine.h"
#include "engine/ecs/scene.h"
#include "radar/systems/hitbox.h"

static void close_window(sfRenderWindow *window)
{
    scene_empty(scene_get());
    sfRenderWindow_close(window);
}

static void show_click_pos(sfVector2i position, void *context)
{
    printf("%d %d\n", position.x, position.y);
}

static void toogle_hitbox(system_t *hitbox_system)
{
    hitbox_system_t *context = SYSTEM_CONTEXT(hitbox_system, hitbox_system_t);
    context->render_enabled = !context->render_enabled;
}

events_handler_t *simulation_event_handler_create(system_t *hitbox_system)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, (void (*)(void *))close_window, engine_get()->window);
    eh_bind_window_closed(eh, (void (*)(void *))close_window, engine_get()->window);
    eh_bind_key_pressed(eh, sfKeyH, (void (*)(void *))toogle_hitbox, hitbox_system);
    eh_bind_mouse_pressed(eh, sfMouseLeft, show_click_pos, NULL);
    return eh;
}