#include <stdbool.h>
#include <stdlib.h>
#include "radar/systems/hitbox.h"
#include "radar/components/hitbox.h"

static void render_handler(system_t *system, sfRenderWindow *window)
{
    if (!*((bool *)system->context)) {
        return;
    }

    entity_link_t *entity_link = NULL;
    TAILQ_FOREACH(entity_link, &system->entities_subscribed, entry) {
        entity_t *entity = entity_link->entity;
        
        hitbox_component_t *hitbox = entity_get_component(entity, HITBOX_COMPONENT_TYPE);
        if (hitbox->type == CIRCLE) {
            sfRenderWindow_drawCircleShape(window, hitbox->csfml_object, NULL);
        } else if (hitbox->type == RECT) {
            sfRenderWindow_drawRectangleShape(window, hitbox->csfml_object, NULL);
        }
    }
}

system_t *hitbox_system_create(void)
{
    bool *enabled = malloc(sizeof(bool));
    *enabled = true;
    return system_create(HITBOX_SYSTEM_TYPE, (system_params_t){
        .context = enabled,
        .render_handler = render_handler,
        .update_handler = NULL,
    });
}