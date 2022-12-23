#include <stdlib.h>

#include "radar/parser.h"
#include "engine/engine.h"

int main(void)
{
    radar_definition_t *def = parser_read("./assets/game.rdr");
    radar_entity_definition_t *entity = NULL;

    if (def == NULL) {
        return EXIT_FAILURE;
    }
    LIST_FOREACH(entity, &def->entities, entry) {
        if (entity->type == AIRCRAFT) {
            printf("Aircraft %d %d %d %d %d %d\n", entity->args[0], entity->args[1],entity->args[2],entity->args[3],entity->args[4],entity->args[5]);
        } else if (entity->type == TOWER) {
            printf("TOWER %d %d %d\n", entity->args[0], entity->args[1], entity->args[2]);
        }
    }


//    engine_t *engine = engine_get();
//
//    if (engine_init(engine) == false) {
//        return EXIT_FAILURE;
//    }
    //engine_load_scene(engine, create_main_scene());
//    engine_run(engine);
//    engine_destroy(engine);
    return EXIT_SUCCESS;
}
