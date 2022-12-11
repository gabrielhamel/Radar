#include <stdlib.h>

#include "engine/engine.h"

static void bing_chilling(void *context)
{
    sfRenderWindow *window = engine_get()->window;

    sfRenderWindow_close(window);
}

scene_t *create_main_scene(void)
{
    scene_t *scene = scene_create();
    events_handler_t *eh = eh_create();

    scene_subscribe_event_handler(scene, eh);
    eh_bind_key_pressed(eh, sfKeyA, bing_chilling, NULL);

    ui_element_t *root = scene->ui_element_root;
    ui_element_t *text_box = ui_element_create((sfIntRect){200, 100, 400, 100});
    sfRectangleShape_setFillColor(text_box->background, sfWhite);
    ui_element_t *sub_text = ui_element_create((sfIntRect){0, 0, 50, 50});
    sfRectangleShape_setFillColor(sub_text->background, sfRed);
    ui_element_append_children(text_box, sub_text);
    ui_element_append_children(root, text_box);
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
