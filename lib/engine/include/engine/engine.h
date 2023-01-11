#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include "ecs/scene.h"

typedef struct {
    unsigned int width;
    unsigned int height;
    sfUint32 *title;
    const char *app_icon;
} engine_params_t;

typedef struct engine_t engine_t;

engine_t *engine_get(void);
bool engine_init(engine_t *engine, engine_params_t params);
void engine_destroy(engine_t *engine);
void engine_run(engine_t *engine);
void engine_load_scene(engine_t *engine, scene_t *scene);

#endif // ENGINE_H