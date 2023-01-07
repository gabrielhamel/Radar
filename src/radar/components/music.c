#include <SFML/Audio.h>

#include "radar/components/music.h"

component_t *music_component_create_from_path(const char *filename)
{
    sfMusic *music = sfMusic_createFromFile(filename);
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    sfMusic_setVolume(music, 35);
    return component_create(MUSIC_COMPONENT_TYPE, music);
}

void music_component_destroy(component_t *component)
{
    sfMusic *music = COMPONENT_DATA(component, sfMusic);

    sfMusic_destroy(music);
    component_destroy(component);
}