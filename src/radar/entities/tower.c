#include <stdlib.h>

#include "radar/entities/tower.h"

tower_t *tower_create_from_definition(radar_entity_definition_t *definition)
{
    tower_t *tower = malloc(sizeof(tower_t));

    tower->entity = entity_create((entity_params_t){
        .position = (sfVector2f){definition->args[0] - 10, definition->args[1] - 10}
    });
    // TODO refacto this dope stuff
    sfUint8 pixels[20 * 20 * 4] = {0};
    for (size_t idx = 0; idx < 20 * 20; idx++) {
        pixels[idx * 4 + 0] = sfRed.r;
        pixels[idx * 4 + 1] = sfRed.g;
        pixels[idx * 4 + 2] = sfRed.b;
        pixels[idx * 4 + 3] = sfRed.a;
    }
    sfTexture *player_texture = sfTexture_create(20, 20);
    sfTexture_updateFromPixels(player_texture, pixels, 20, 20, 0, 0);
    sfRectangleShape_setSize(tower->entity->sprite, (sfVector2f){20, 20});
    sfRectangleShape_setTexture(tower->entity->sprite, player_texture, sfTrue);
    return tower;
}

void tower_update(tower_t *definition, sfTime *elapsed_time)
{
    // TODO
}