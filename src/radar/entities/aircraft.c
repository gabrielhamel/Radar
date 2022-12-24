#include <stdlib.h>

#include "radar/entities/aircraft.h"

aircraft_t *aircraft_create_from_definition(radar_entity_definition_t *definition)
{
    aircraft_t *aircraft = malloc(sizeof(aircraft_t));

    aircraft->entity = entity_create((entity_params_t){
        .position = (sfVector2f){definition->args[0], definition->args[1]}
    });
    // TODO refacto this dope stuff
    sfUint8 pixels[20 * 20 * 4] = {0};
    for (size_t idx = 0; idx < 20 * 20; idx++) {
        pixels[idx * 4 + 0] = sfYellow.r;
        pixels[idx * 4 + 1] = sfYellow.g;
        pixels[idx * 4 + 2] = sfYellow.b;
        pixels[idx * 4 + 3] = sfYellow.a;
    }
    sfTexture *player_texture = sfTexture_create(20, 20);
    sfTexture_updateFromPixels(player_texture, pixels, 20, 20, 0, 0);
    sfSprite_setTexture(aircraft->entity->sprite, player_texture, sfTrue);
    return aircraft;
}

void aircraft_update(aircraft_t *aircraft, sfTime *elapsed_time)
{
    // TODO
}