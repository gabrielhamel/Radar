#include <stdlib.h>

#include "engine/ecs/system.h"

system_t *system_create(system_type_t type, system_params_t params)
{
    system_t *system = malloc(sizeof(system_t));

    system->type = type;
    system->update_context = params.update_context;
    system->update_handler = params.update_handler;
    return system;
}
