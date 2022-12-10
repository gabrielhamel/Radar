#include <stdlib.h>

#include "engine/engine.h"

static void bing_chilling(void *context)
{
    sfRenderWindow *window = engine_get()->window;

    sfRenderWindow_close(window);
}

scene_t *create_main_scene(void)
{
    scene_t *scene = malloc(sizeof(scene_t));
    events_handler_t *eh = eh_create();

    scene_subscribe_event_handler(scene, eh);
    eh_bind_key_pressed(eh, sfKeyA, bing_chilling, NULL);
    return scene;
}

int main()
{
    engine_t *engine = engine_get();

    if (engine_init(engine) == false) {
        return EXIT_FAILURE;
    }
    engine_load_scene(engine, create_main_scene());
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
