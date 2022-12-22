#include <stdlib.h>

#include "engine/entity/entity.h"

entity_t *entity_create(void)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->sprite = sfSprite_create();
    entity->speed = (sfVector2f){0};
    return entity;
}

void entity_render(entity_t *entity, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, entity->sprite, NULL);
}

void entity_update(entity_t *entity, sfTime *elapsed_time)
{
    float delta = sfTime_asSeconds(*elapsed_time);

    sfSprite_move(entity->sprite, (sfVector2f){
            entity->speed.x * delta,
            entity->speed.y * delta
    });
}