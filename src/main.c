#include <SFML/Graphics.h>
#include <stdio.h>

int main() {
    sfVideoMode mode = sfVideoMode_getDesktopMode();

    printf("%d %d %d", mode.width, mode.height, mode.bitsPerPixel);
    return 0;
}
