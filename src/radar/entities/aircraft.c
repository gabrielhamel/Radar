#include <stdlib.h>
#include <math.h>

#include "radar/entities/aircraft.h"

aircraft_t *aircraft_create_from_definition(radar_entity_definition_t *definition)
{
    aircraft_t *aircraft = malloc(sizeof(aircraft_t));
    aircraft->departure = (sfVector2f){definition->args[0], definition->args[1]};
    aircraft->arrival = (sfVector2f){definition->args[2], definition->args[3]};
    aircraft->speed = definition->args[4];
    aircraft->entity = entity_create((entity_params_t){
        .position = (sfVector2f){aircraft->departure.x - 10, aircraft->departure.y - 10}
    });
    float angle = (aircraft->arrival.y - aircraft->departure.y) / (aircraft->arrival.x - aircraft->departure.x);
    aircraft->entity->speed = (sfVector2f){
        .x = cosf(angle) * aircraft->speed,
        .y = sinf(angle) * aircraft->speed
    };
    sfRectangleShape_rotate(aircraft->entity->sprite, angle * (180.0 / M_PI));
    sfRectangleShape_setSize(aircraft->entity->sprite, (sfVector2f){20, 20});
    sfColor color_mask = sfWhite;
    sfImage *aircraft_image = sfImage_createFromFile("./assets/aircraft.png");
    sfUint8 *aircraft_pixels = sfImage_getPixelsPtr(aircraft_image);
    for (size_t pixel = 0; pixel < 20 * 20; pixel++) {
        aircraft_pixels[pixel * 4 + 0] = color_mask.r;
        aircraft_pixels[pixel * 4 + 1] = color_mask.g;
        aircraft_pixels[pixel * 4 + 2] = color_mask.b;
    }
    sfTexture *aircraft_texture = sfTexture_createFromImage(aircraft_image, NULL);
    sfRectangleShape_setTexture(aircraft->entity->sprite, aircraft_texture, sfTrue);

    sfRectangleShape_setOutlineColor(aircraft->entity->sprite, sfYellow);
    sfRectangleShape_setOutlineThickness(aircraft->entity->sprite, 1);
    return aircraft;
}

void aircraft_update(aircraft_t *aircraft, sfTime *elapsed_time)
{
    // TODO
}