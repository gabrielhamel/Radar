#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.h>

#include "scene.h"
#include "events.h"

typedef struct {
    sfRenderWindow *window;
    sfEvent event;
    sfClock *clock;
    sfTime elapsed_time;
    scene_t *scene;
} engine_t;

engine_t *engine_init(void);
void engine_destroy(engine_t *);
void engine_run(engine_t *engine);
void engine_load_scene(engine_t *engine, scene_t *scene);

#endif // ENGINE_H