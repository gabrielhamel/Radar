#include <stdlib.h>

#include "engine/engine.h"
#include "engine/events.h"

static void close_window(void *context)
{
    sfRenderWindow *window = engine_get()->window;

    sfRenderWindow_close(window);
}

static entity_t *create_player(void)
{
    entity_t *player = entity_create();

    sfUint8 pixels[50 * 50 * 4] = {0};
    for (size_t idx = 0; idx < 50 * 50; idx++) {
        pixels[idx * 4 + 0] = sfYellow.r;
        pixels[idx * 4 + 1] = sfYellow.g;
        pixels[idx * 4 + 2] = sfYellow.b;
        pixels[idx * 4 + 3] = sfYellow.a;
    }

    sfTexture *player_texture = sfTexture_create(50, 50);
    sfTexture_updateFromPixels(player_texture, pixels, 50, 50, 0, 0);
    sfSprite_setTexture(player->sprite, player_texture, sfTrue);
    return player;
}

static void player_set_right_speed(entity_t *player)
{
    player->speed.x += 200;
}

static void player_reset_right_speed(entity_t *player)
{
    player->speed.x -= 200;
}

static void player_set_left_speed(entity_t *player)
{
    player->speed.x -= 200;
}

static void player_reset_left_speed(entity_t *player)
{
    player->speed.x += 200;
}

static void player_set_top_speed(entity_t *player)
{
    player->speed.y -= 200;
}

static void player_reset_top_speed(entity_t *player)
{
    player->speed.y += 200;
}

static void player_set_bottom_speed(entity_t *player)
{
    player->speed.y += 200;
}

static void player_reset_bottom_speed(entity_t *player)
{
    player->speed.y -= 200;
}

static events_handler_t *player_events(entity_t *player)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyD, player_set_right_speed, player);
    eh_bind_key_released(eh, sfKeyD, player_reset_right_speed, player);
    eh_bind_key_pressed(eh, sfKeyQ, player_set_left_speed, player);
    eh_bind_key_released(eh, sfKeyQ, player_reset_left_speed, player);
    eh_bind_key_pressed(eh, sfKeyZ, player_set_top_speed, player);
    eh_bind_key_released(eh, sfKeyZ, player_reset_top_speed, player);
    eh_bind_key_pressed(eh, sfKeyS, player_set_bottom_speed, player);
    eh_bind_key_released(eh, sfKeyS, player_reset_bottom_speed, player);
    return eh;
}

scene_t *create_main_scene(void)
{
    scene_t *scene = scene_create();
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, close_window, NULL);
    scene_subscribe_event_handler(scene, eh);

    // Player
    entity_t *player = create_player();
    scene_append_entity(scene, player);
    scene_subscribe_event_handler(scene, player_events(player));
    return scene;
}

int main(void)
{
    engine_t *engine = engine_get();

    if (engine_init(engine) == false) {
        return EXIT_FAILURE;
    }
    engine_load_scene(engine, create_main_scene());
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
