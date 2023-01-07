#include "engine/engine.h"
#include "radar/components/music.h"

entity_t *ambiance_init(scene_t *scene)
{
    component_t *component = music_component_create_from_path("assets/music.ogg");
    entity_t *music = entity_create();
    entity_assign_component(music, component);
    scene_append_entity(scene, music);
    return music;
}
