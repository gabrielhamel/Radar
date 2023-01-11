#include <stdlib.h>

#include "radar/entities/tower.h"
#include "radar/components/hitbox.h"
#include "radar/components/position.h"
#include "radar/components/speed.h"
#include "radar/systems/hitbox.h"
#include "radar/systems/movement.h"

static void move_left(speed_component_t *speed)
{
    speed->speed.x -= 200;
}

static void stop_left(speed_component_t *speed)
{
    speed->speed.x += 200;
}

static void move_right(speed_component_t *speed)
{
    speed->speed.x += 200;
}

static void stop_right(speed_component_t *speed)
{
    speed->speed.x -= 200;
}

static void move_up(speed_component_t *speed)
{
    speed->speed.y -= 200;
}

static void stop_up(speed_component_t *speed)
{
    speed->speed.y += 200;
}

static void move_down(speed_component_t *speed)
{
    speed->speed.y += 200;
}

static void stop_down(speed_component_t *speed)
{
    speed->speed.y -= 200;
}

static void storm_events(scene_t *scene, speed_component_t *speed)
{
    events_handler_t *handler = eh_create();

    eh_bind_key_pressed(handler, sfKeyLeft, (void (*)(void *))move_left, speed);
    eh_bind_key_pressed(handler, sfKeyRight, (void (*)(void *)) move_right, speed);
    eh_bind_key_pressed(handler, sfKeyUp, (void (*)(void *))move_up, speed);
    eh_bind_key_pressed(handler, sfKeyDown, (void (*)(void *))move_down, speed);

    eh_bind_key_released(handler, sfKeyLeft, (void (*)(void *))stop_left, speed);
    eh_bind_key_released(handler, sfKeyRight, (void (*)(void *)) stop_right, speed);
    eh_bind_key_released(handler, sfKeyUp, (void (*)(void *))stop_up, speed);
    eh_bind_key_released(handler, sfKeyDown, (void (*)(void *))stop_down, speed);

    scene_subscribe_event_handler(scene, handler);
}

static entity_t *storm_create_from_definition(radar_entity_definition_t *definition)
{
    entity_t *storm = entity_create();
    sfVector2f *points = malloc(sizeof(sfVector2f) * (definition->args_count / 2));

    for (size_t idx = 0; idx < (definition->args_count / 2); idx++) {
        points[idx] = (sfVector2f){definition->args[idx * 2], definition->args[idx * 2 + 1]};
    }

    component_t *position = position_component_create((sfVector2f){0, 0});

    component_t *hitbox = hitbox_custom_component_create(
            component_get_data(position, position_component_t)->position,
            points, definition->args_count / 2);

    component_t *speed = speed_component_create((sfVector2f){0, 0});

    entity_assign_component(storm, hitbox);
    entity_assign_component(storm, position);
    entity_assign_component(storm, speed);

    return storm;
}

void storm_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *storm = storm_create_from_definition(definition);

    system_subscribe_entity(scene_get_system(scene, MOVEMENT_SYSTEM_TYPE), storm);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), storm);
    scene_append_entity(scene, storm);

    static int shape_count = 0;

    if (shape_count++ == 0) {
        storm_events(scene, component_get_data(entity_get_component(storm, SPEED_COMPONENT_TYPE), speed_component_t));
    }
}
