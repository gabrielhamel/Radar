#include <stdlib.h>
#include <string.h>

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

void button_on_click(ui_element_t *button)
{
    ui_element_set_background_color(button, sfRed);
}

void button_on_leave_click(ui_element_t *button)
{
    ui_element_set_background_color(button, sfGreen);
}

ui_element_t *create_button(sfIntRect bounds, sfColor normal, sfColor on_hover)
{
    ui_element_t *container = ui_element_create(bounds);
    state_event_t *hover_event = ui_state_event_create(button_on_hover, button_on_leave, container);
    state_event_t *click_event = ui_state_event_create(button_on_click, button_on_leave_click, container);

    ui_element_set_background_color(container, normal);
    ui_element_set_hover_event(container, hover_event);
    ui_element_set_click_event(container, click_event);
    sfFont *font = sfFont_createFromFile("assets/fonts/Hack-Regular.ttf");
    ui_element_set_font(container, font);
    sfUint32 textOriginal[] = {'C', 'l', 'i', 'c', 'k', '\0'};
    sfUint32 *text = malloc(sizeof(textOriginal));
    memcpy(text, textOriginal, sizeof(textOriginal));
    ui_element_set_text(container, text);
    return container;
}

scene_t *create_main_scene(void)
{
    scene_t *scene = scene_create();
    events_handler_t *eh = eh_create();

    scene_subscribe_event_handler(scene, eh);
    eh_bind_key_pressed(eh, sfKeyA, bing_chilling, NULL);

    ui_element_t *root = scene->ui_element_root;
    ui_element_t *button = create_button((sfIntRect){200, 100, 400, 100}, sfGreen, sfYellow);


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
