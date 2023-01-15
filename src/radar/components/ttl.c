#include <stdlib.h>

#include <radar/components/ttl.h>

static void ttl_component_destroy(component_t *component)
{
    void *data = component_get_raw_data(component);
    free(data);
}

component_t *ttl_component_create(float remaining_time)
{
    float *ttl = malloc(sizeof(float));
    *ttl = remaining_time;
    return component_create(TTL_COMPONENT_TYPE, ttl, ttl_component_destroy);
}

