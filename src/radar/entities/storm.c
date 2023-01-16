#include <stdlib.h>
#include <engine/render/component.h>
#include <engine/render/system.h>
#include <engine/physics/component.h>
#include <engine/physics/system.h>


#include "radar/entities/storm.h"
#include "radar/components/hitbox.h"
#include "radar/systems/hitbox.h"
#include "radar/entities/hitbox.h"

static void move_left(physics_component_t *physics)
{
    physics->speed.x -= 200;
}

static void stop_left(physics_component_t *physics)
{
    physics->speed.x += 200;
}

static void move_right(physics_component_t *physics)
{
    physics->speed.x += 200;
}

static void stop_right(physics_component_t *physics)
{
    physics->speed.x -= 200;
}

static void move_up(physics_component_t *physics)
{
    physics->speed.y -= 200;
}

static void stop_up(physics_component_t *physics)
{
    physics->speed.y += 200;
}

static void move_down(physics_component_t *physics)
{
    physics->speed.y += 200;
}

static void stop_down(physics_component_t *physics)
{
    physics->speed.y -= 200;
}

static void storm_events(scene_t *scene, physics_component_t *speed)
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

    physics_component_t movement = {
        .position = (sfVector2f){0, 0},
        .speed = (sfVector2f){0, 0}
    };
    component_t *physics = physics_component_create(movement);

    component_t *hitbox = hitbox_custom_component_create(points, definition->args_count / 2);
    sfConvexShape *shape = render_custom_create((sfVector2f){0, 0}, points, definition->args_count / 2);
    component_t *render = render_component_create();
    render_component_append_object(render, CONVEX_SHAPE, shape, CONVEX_SHAPE_RENDER_ID);

    entity_assign_component(storm, hitbox);
    entity_assign_component(storm, physics);
    entity_assign_component(storm, render);
    return storm;
}

void storm_scene_append(scene_t *scene, radar_entity_definition_t *definition)
{
    entity_t *storm = storm_create_from_definition(definition);

    system_subscribe_entity(scene_get_system(scene, RENDER_SYSTEM_TYPE), storm);
    system_subscribe_entity(scene_get_system(scene, PHYSICS_SYSTEM_TYPE), storm);
    system_subscribe_entity(scene_get_system(scene, HITBOX_SYSTEM_TYPE), storm);
    scene_append_entity(scene, storm);

    static int shape_count = 0;

    if (shape_count++ == 0) {
        storm_events(scene, entity_get_component_data(storm, PHYSICS_SYSTEM_TYPE, physics_component_t));
    }
}
