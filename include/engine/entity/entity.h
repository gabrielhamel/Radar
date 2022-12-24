#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.h>

#include "engine/queue.h"

typedef struct {
    sfVector2f position;
} entity_params_t;

typedef struct entity_s {
    LIST_ENTRY(entity_s) entry;
    sfVector2f speed;
    sfRectangleShape *sprite;
} entity_t;

entity_t *entity_create(entity_params_t params);
void entity_update(entity_t *entity, sfTime *elapsed_time);
void entity_render(entity_t *entity, sfRenderWindow *window);

#endif // ENTITY_H