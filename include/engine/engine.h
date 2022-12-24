#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.h>
#include <stdbool.h>

#include "scene.h"
#include "events.h"

typedef struct {
    unsigned int width;
    unsigned int height;
    sfUint32 *title;
} engine_params_t;

typedef struct {
    sfRenderWindow *window;
    sfEvent event;
    sfClock *clock;
    sfTime elapsed_time;
    scene_t *scene;
} engine_t;

engine_t *engine_get(void);
bool engine_init(engine_t *engine, engine_params_t params);
void engine_destroy(engine_t *);
void engine_run(engine_t *engine);
void engine_load_scene(engine_t *engine, scene_t *scene);

#endif // ENGINE_H