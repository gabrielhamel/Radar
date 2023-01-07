#include <stdlib.h>
#include <SFML/Audio.h>
#include "radar/simulation.h"
#include "radar/parser.h"
#include "radar/entities/tower.h"
#include "radar/systems/sprite_drawer.h"
#include "radar/systems/simulation.h"
#include "radar/components/sprite.h"
#include "radar/systems/movement.h"
#include "radar/systems/hitbox.h"
#include "radar/components/ui_link.h"
#include "radar/systems/timer.h"
#include "radar/entities/timer.h"
#include "radar/musics.h"

static void simulation_load_background(scene_t *scene)
{
    entity_t *background = entity_create();
    entity_assign_component(background, sprite_component_create_from_file("assets/background.png",
                                                                          (sprite_params_t){
                                                                                  .position = (sfVector2f){0},
                                                                                  .origin = TOP_LEFT
                                                                          }));

    scene_append_entity(scene, background);
    system_subscribe_entity(scene_get_system(scene, SPRITE_DRAWER_SYSTEM_TYPE), background);
}

static radar_definition_t *simulation_load_entities(scene_t *scene, const char *filepath)
{
    radar_entity_definition_t *entity = NULL;
    radar_entity_definition_t *entity_tmp = NULL;
    radar_definition_t *def = parser_read(filepath);

    TAILQ_FOREACH_SAFE(entity, &def->entities, entry, entity_tmp) {
        switch (entity->type) {
            case TOWER:
                tower_scene_append(scene, entity);
                TAILQ_REMOVE(&def->entities, entity, entry);
                radar_entity_definition_destroy(entity);
                break;
            default:
                break;
        }
    }
    return def;
}

bool radar_init_from_script(scene_t *scene, const char *filepath)
{
    entity_t *timer = ui_timer_create();
    ui_element_t *timer_ui = entity_get_component(timer, UI_LINK_COMPONENT_TYPE)->data;

    system_t *hitbox_system = hitbox_system_create();
    scene_append_system(scene, hitbox_system);

    scene_append_system(scene, sprite_drawer_system_create());

    simulation_load_background(scene);

    scene_append_system(scene, movement_system_create());

    system_t *timer_system = timer_system_create();
    scene_append_system(scene, timer_system);

    scene_append_entity(scene, timer);
    system_subscribe_entity(timer_system, timer);

    scene_subscribe_event_handler(scene, simulation_event_handler_create(hitbox_system));
    ui_element_append_children(scene_get_ui_root(scene), timer_ui);
    radar_definition_t *def = simulation_load_entities(scene, filepath);
    scene_append_system(scene, simulation_system_create(scene, timer_system->context, def));

    entity_t *simulation = entity_create();
    scene_append_entity(scene, simulation);
    system_subscribe_entity(scene_get_system(scene, SIMULATION_SYSTEM_TYPE), simulation);

    ambiance_init(scene);
    return true;
}
