#include <stdlib.h>

#include "events.h"

#include "engine.h"

static void bing_chilling(void *context)
{
    engine_t *ptr = (engine_t *)context;

    sfRenderWindow_close(ptr->window);
}

scene_t *create_main_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));
    events_handler_t *eh = eh_create();

    scene->events_handler = eh;
    eh_bind_key_pressed(eh, sfKeyA, (void (*)(void *))bing_chilling);
    return scene;
}