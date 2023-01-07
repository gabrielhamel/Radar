#include <stdlib.h>

#include "radar/simulation.h"

#include "engine/engine.h"
#include "engine/text/unicode.h"

int main(void)
{
    engine_t *engine = engine_get();
    scene_t *scene = NULL;

    sfUint32 title[6] = {0};
    string_to_utf8(title, "Radar", 6);
    if (engine_init(engine, (engine_params_t){
        .title = title,
        .width = 1920,
        .height = 1080,
        .app_icon = "./assets/favicon.png"
    }) == false) {
        return EXIT_FAILURE;
    }
    scene = scene_create();
    if (radar_init_from_script(scene, "./assets/game.rdr") == false) {
        return EXIT_FAILURE;
    }
    engine_load_scene(engine, scene);
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
