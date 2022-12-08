#include "engine.h"

#include <stdlib.h>

int main()
{
    engine_t *engine = engine_init();

    if (engine == NULL) {
        return EXIT_FAILURE;
    }
    engine_run(engine);
    engine_destroy(engine);
    return EXIT_SUCCESS;
}
