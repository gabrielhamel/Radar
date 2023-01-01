#include "engine/engine.h"
#include "radar/simulation.h"
#include "radar/parser.h"
#include "radar/entities/aircraft.h"
#include "radar/entities/tower.h"
#include "radar/systems/sprite_drawer.h"
#include "radar/systems/movement.h"
#include "radar/components/ui_link.h"
#include "radar/systems/timer.h"
#include "radar/entities/timer.h"
#include "engine/text/unicode.h"

static void close_window(sfRenderWindow *window)
{
    sfRenderWindow_close(window);
}

static events_handler_t *simulation_event_handler_create(void)
{
    events_handler_t *eh = eh_create();

    eh_bind_key_pressed(eh, sfKeyEscape, close_window, engine_get()->window);
    return eh;
}

bool radar_init_from_script(scene_t *scene, const char *filepath)
{
    radar_definition_t *def = parser_read(filepath);
    radar_entity_definition_t *entity;
    entity_t *aircraft;
    entity_t *tower;
    entity_t *timer = ui_timer_create();
    ui_element_t *timer_ui = entity_get_component(timer, UI_LINK_COMPONENT_TYPE);

    if (def == NULL) {
        return false;
    }

    scene_append_system(scene, sprite_drawer_system_create());
    scene_append_system(scene, movement_system_create());
    scene_append_system(scene, timer_system_create());

    scene_append_entity(scene, timer);

    scene_subscribe_entity_to_system(scene, timer, TIMER_SYSTEM_TYPE);
    scene_subscribe_event_handler(scene, simulation_event_handler_create());

    ui_element_append_children(scene_get_ui_root(scene), timer_ui);

    LIST_FOREACH(entity, &def->entities, entry) {
        switch (entity->type) {
            case AIRCRAFT:
                aircraft = aircraft_create_from_definition(entity);
                scene_append_entity(scene, aircraft);
                scene_subscribe_entity_to_system(scene, aircraft, SPRITE_DRAWER_SYSTEM_TYPE);
                scene_subscribe_entity_to_system(scene, aircraft, MOVEMENT_SYSTEM_TYPE);
                break;
            case TOWER:
                tower = tower_create_from_definition(entity);
                scene_subscribe_entity_to_system(scene, tower, SPRITE_DRAWER_SYSTEM_TYPE);
                scene_append_entity(scene, tower);
                break;
        }
    }
    return true;
}
