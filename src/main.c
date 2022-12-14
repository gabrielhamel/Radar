#include <stdlib.h>

#include "engine/engine.h"
#include "engine/events.h"

static void bing_chilling(void *context)
{
    sfRenderWindow *window = engine_get()->window;

    sfRenderWindow_close(window);
}

void button_on_hover(ui_element_t *button)
{
    ui_element_set_background_color(button, sfYellow);
}

void button_on_leave(ui_element_t *button)
{
    ui_element_set_background_color(button, sfGreen);
}

void button2_on_hover(ui_element_t *button)
{
    ui_element_set_background_color(button, sfBlue);
}

void button2_on_leave(ui_element_t *button)
{
    ui_element_set_background_color(button, sfRed);
}

ui_element_t *create_button(sfIntRect bounds, sfColor normal, sfColor on_hover)
{
    ui_element_t *container = ui_element_create(bounds);
    hover_event_t *event = ui_hover_event_create(button_on_hover, button_on_leave, container);

    ui_element_set_background_color(container, normal);
    ui_element_set_hover_event(container, event);
    return container;
}

ui_element_t *create_button2(sfIntRect bounds, sfColor normal, sfColor on_hover)
{
    ui_element_t *container = ui_element_create(bounds);
    hover_event_t *event = ui_hover_event_create(button2_on_hover, button2_on_leave, container);

    ui_element_set_background_color(container, normal);
    ui_element_set_hover_event(container, event);

    return container;
}

scene_t *create_main_scene(void)
{
    scene_t *scene = scene_create();
    events_handler_t *eh = eh_create();

    scene_subscribe_event_handler(scene, eh);
    eh_bind_key_pressed(eh, sfKeyA, bing_chilling, NULL);

    ui_element_t *root = scene->ui_element_root;
    ui_element_t *button1 = create_button((sfIntRect){200, 100, 400, 100}, sfGreen, sfYellow);
    ui_element_t *button2 = create_button2((sfIntRect){40, 75, 50, 50}, sfRed, sfBlue);
    ui_element_append_children(button1, button2);
    ui_element_append_children(root, button1);
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
