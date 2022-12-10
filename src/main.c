#include <stdlib.h>

#include "engine/engine.h"

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

int main()
{
    engine_t *engine = engine_init();

    if (engine == NULL) {
        return EXIT_FAILURE;
    }
    engine_load_scene(engine, create_main_scene());
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
