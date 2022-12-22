#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.h>

#include "engine/queue.h"

typedef struct entity_s {
    LIST_ENTRY(entity_s) entry;
    sfVector2f speed;
    sfSprite *sprite;
} entity_t;

entity_t *entity_create(void);
void entity_update(entity_t *entity, sfTime *elapsed_time);
void entity_render(entity_t *entity, sfRenderWindow *window);

#endif // ENTITY_H