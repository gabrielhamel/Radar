#include <stdlib.h>

#include "radar/simulation.h"

#include "engine/engine.h"
#include "engine/text/unicode.h"

int main(void)
{
    engine_t *engine = engine_get();
    scene_t *scene = scene_create();

    if (engine_init(engine, (engine_params_t){
        .title = string_to_utf8("Radar"),
        .width = 1920,
        .height = 1080,
        .app_icon = "./assets/favicon.png"
    }) == false) {
        return EXIT_FAILURE;
    }
    if (radar_init_from_script(scene, "./assets/game.rdr") == false) {
        // TODO Unload everything
        return EXIT_FAILURE;
    }
    engine_load_scene(engine, scene);
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
