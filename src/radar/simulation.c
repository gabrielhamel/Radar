#include <SFML/Audio.h>
#include "engine/engine.h"
#include "radar/simulation.h"
#include "radar/parser.h"
#include "radar/entities/aircraft.h"
#include "radar/entities/tower.h"
#include "radar/systems/sprite_drawer.h"
#include "radar/components/sprite.h"
#include "radar/systems/movement.h"
#include "radar/systems/hitbox.h"
#include "radar/components/ui_link.h"
#include "radar/systems/timer.h"
#include "radar/entities/timer.h"

static sfMusic *ambiance_init(void)
{
    sfMusic *music = sfMusic_createFromFile("assets/music.ogg");
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    return music;
}

static void simulation_load_background(scene_t *scene)
{
    entity_t *background = entity_create();
    entity_assign_component(background, sprite_component_create_from_file("assets/background.png",
                                                                          (sprite_params_t){
                                                                                  .position = (sfVector2f){0},
                                                                                  .origin = TOP_LEFT
                                                                          }));

    scene_append_entity(scene, background);
    scene_subscribe_entity_to_system(scene, background, SPRITE_DRAWER_SYSTEM_TYPE);
}

static void simulation_load_entities(scene_t *scene, const char *filepath)
{
    radar_entity_definition_t *entity;
    radar_definition_t *def = parser_read(filepath);

    LIST_FOREACH(entity, &def->entities, entry) {
        switch (entity->type) {
            case AIRCRAFT:
                aircraft_scene_append(scene, entity);
                break;
            case TOWER:
                tower_scene_append(scene, entity);
                break;
        }
    }
}

bool radar_init_from_script(scene_t *scene, const char *filepath)
{
    entity_t *timer = ui_timer_create();
    ui_element_t *timer_ui = entity_get_component(timer, UI_LINK_COMPONENT_TYPE);

    ambiance_init();

    scene_append_system(scene, sprite_drawer_system_create());
    scene_append_system(scene, movement_system_create());
    scene_append_system(scene, timer_system_create());

    system_t *hitbox_system = hitbox_system_create();
    scene_append_system(scene, hitbox_system);
    scene_append_entity(scene, timer);
    scene_subscribe_entity_to_system(scene, timer, TIMER_SYSTEM_TYPE);
    scene_subscribe_event_handler(scene, simulation_event_handler_create(hitbox_system->context));
    ui_element_append_children(scene_get_ui_root(scene), timer_ui);
    simulation_load_entities(scene, filepath);
    simulation_load_background(scene);
    return true;
}
