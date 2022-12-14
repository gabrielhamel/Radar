#include <stdlib.h>

#include "engine/engine.h"

static void bing_chilling(void *context)
{
    sfRenderWindow *window = engine_get()->window;

    sfRenderWindow_close(window);
}

void button_on_hover(ui_element_t *button)
{
    ui_element_set_background_color(button, sfYellow);
}

ui_element_t *create_button(void)
{
    ui_element_t *container = ui_element_create((sfIntRect){200, 100, 400, 100});

    ui_element_set_background_color(container, sfGreen);
    ui_element_set_hover_behavior(container, button_on_hover, container);

    return container;
}

scene_t *create_main_scene(void)
{
    scene_t *scene = scene_create();
    events_handler_t *eh = eh_create();

    scene_subscribe_event_handler(scene, eh);
    eh_bind_key_pressed(eh, sfKeyA, bing_chilling, NULL);

    ui_element_t *root = scene->ui_element_root;
    ui_element_t *button = create_button();
    ui_element_append_children(root, button);
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
