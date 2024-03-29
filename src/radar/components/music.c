#include <SFML/Audio.h>

#include <radar/components/music.h>

static void music_component_destroy(component_t *component)
{
    sfMusic_destroy(component_get_data(component, sfMusic));
}

component_t *music_component_create_from_path(const char *filename)
{
    sfMusic *music = sfMusic_createFromFile(filename);
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    sfMusic_setVolume(music, 35);
    return component_create(MUSIC_COMPONENT_TYPE, music, music_component_destroy);
}
