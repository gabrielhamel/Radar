#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.h>

typedef struct {
    sfRenderWindow *window;
    sfEvent event;
    sfClock *clock;
    sfTime elapsed_time;
} engine_t;

engine_t *engine_init(void);
void engine_destroy(engine_t *);
void engine_run(engine_t *engine);

#endif // ENGINE_H