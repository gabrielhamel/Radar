#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

sfRenderWindow *window_create(void)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = NULL;

    if (sfVideoMode_isValid(mode) == sfFalse) {
        perror("Video mode not supported");
        return NULL;
    }
    window = sfRenderWindow_create(mode, "Radar", sfDefaultStyle, NULL);
    if (window == NULL) {
        perror("Cannot open the required window");
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    sfRenderWindow_setKeyRepeatEnabled(window, sfFalse);
    return window;
}

int main()
{
    sfRenderWindow *window = window_create();

    if (window == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
