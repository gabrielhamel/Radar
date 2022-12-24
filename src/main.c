#include <stdlib.h>

#include "radar/simulation.h"

#include "engine/engine.h"
#include "engine/text/unicode.h"

int main(void)
{
    engine_t *engine = engine_get();
    simulation_t *simulation;

    if (engine_init(engine, (engine_params_t){
        .title = string_to_utf8("Radar"),
        .width = 1920,
        .height = 1080,
        .app_icon = "./assets/favicon.png"
    }) == false) {
        return EXIT_FAILURE;
    }
    simulation = simulation_create_from_script("./assets/game.rdr");
    engine_load_scene(engine, simulation->scene);
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
