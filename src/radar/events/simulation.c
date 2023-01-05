#include <stdio.h>
#include <SFML/Graphics.h>
#include "engine/engine.h"

static void close_window(sfRenderWindow *window)
{
    sfRenderWindow_close(window);
}

static void show_click_pos(sfVector2i position, void *context)
{
    printf("%d %d\n", position.x, position.y);
}

static void toogle_hitbox(bool *hitbox_enabled)
{
    *hitbox_enabled = !*hitbox_enabled;
}

events_handler_t *simulation_event_handler_create(bool *hitbox_enabled)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, (void (*)(void *))close_window, engine_get()->window);
    eh_bind_key_pressed(eh, sfKeyH, (void (*)(void *))toogle_hitbox, hitbox_enabled);
    eh_bind_mouse_pressed(eh, sfMouseLeft, show_click_pos, NULL);
    return eh;
}