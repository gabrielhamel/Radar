#include <stdlib.h>
#include <stdio.h>

#include "engine/engine.h"
#include "engine/events.h"


engine_t *engine_get(void)
{
    static engine_t *instance = NULL;

    if (instance == NULL) {
        instance = malloc(sizeof(engine_t));
    }
    return instance;
}

static sfRenderWindow *engine_window_create(engine_params_t params)
{
    sfVideoMode mode = {params.width, params.height, 32};
    sfRenderWindow *window = NULL;

    if (sfVideoMode_isValid(mode) == sfFalse) {
        perror("Video mode not supported");
#ifndef CSFML_SYSTEM_MACOS
        return NULL;
#endif
    }
    window = sfRenderWindow_createUnicode(mode, params.title, sfTitlebar | sfClose, NULL);
    if (window == NULL) {
        perror("Cannot open the required window");
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    sfRenderWindow_setKeyRepeatEnabled(window, sfFalse);
    return window;
}

bool engine_init(engine_t *engine, engine_params_t params)
{
    engine->window = engine_window_create(params);
    engine->event = (sfEvent){0};
    engine->clock = sfClock_create();
    engine->elapsed_time = sfTime_Zero;
    engine->scene = NULL;
    if (engine->window == NULL) {
        engine_destroy(engine);
        return false;
    }
    return true;
}

void engine_destroy(engine_t *engine)
{
    if (engine->window != NULL) {
        sfRenderWindow_destroy(engine->window);
    }
    free(engine);
}

void engine_run(engine_t *engine)
{
    if (engine->scene == NULL) {
        return;
    }
    while (sfRenderWindow_isOpen(engine->window)) {
        while (sfRenderWindow_pollEvent(engine->window, &engine->event)) {
            scene_handle_event(engine->scene, &engine->event);
        }
        engine->elapsed_time = sfClock_restart(engine->clock);
        scene_update(engine->scene, &engine->elapsed_time);
        ui_element_update(engine->scene->ui_element_root, &engine->elapsed_time);
        sfRenderWindow_clear(engine->window, sfBlack);
        scene_render(engine->scene, engine->window);
        scene_render_ui(engine->scene, engine->window);
        sfRenderWindow_display(engine->window);
    }
}

void engine_load_scene(engine_t *engine, scene_t *scene)
{
    engine->scene = scene;
}