#include "radar/systems/movement.h"
#include "radar/components/position.h"
#include "radar/components/speed.h"
#include "radar/components/hitbox.h"
#include "radar/components/sprite.h"

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_iterator_t *it = system_get_entity_iterator(system);

    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        position_component_t *position_c = component_get_data(entity_get_component(entity, POSITION_COMPONENT_TYPE), position_component_t);
        speed_component_t *speed_c = component_get_data(entity_get_component(entity, SPEED_COMPONENT_TYPE), speed_component_t);
        component_t *sprite_c = entity_get_component(entity, SPRITE_COMPONENT_TYPE);
        component_t *hitbox_c = entity_get_component(entity, HITBOX_COMPONENT_TYPE);

        position_c->position.x += speed_c->speed.x * sfTime_asSeconds(*elapsed_time);
        position_c->position.y += speed_c->speed.y * sfTime_asSeconds(*elapsed_time);

        if (sprite_c) {
            sfSprite_setPosition(component_get_data(sprite_c, sprite_component_t)->sprite, position_c->position);
        }
        if (hitbox_c) {
            hitbox_component_t *hitbox = component_get_data(hitbox_c, hitbox_component_t);
            if (hitbox->type == RECT) {
                sfRectangleShape_setPosition(hitbox->csfml_object, position_c->position);
            } else if (hitbox->type == CIRCLE) {
                sfCircleShape_setPosition(hitbox->csfml_object, position_c->position);
            } else if (hitbox->type == CUSTOM) {
                sfConvexShape_setPosition(hitbox->csfml_object, position_c->position);
            }
        }
    }
    entity_iterator_destroy(it);
}

system_t *movement_system_create(void)
{
    return system_create(MOVEMENT_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .render_handler = NULL,
        .update_handler = update_handler,
        .destroy_handler = NULL
    });
}