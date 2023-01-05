#include "radar/systems/movement.h"
#include "radar/components/position.h"
#include "radar/components/speed.h"
#include "radar/components/hitbox.h"
#include "radar/components/sprite.h"

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_link_t *entity_link = NULL;
    TAILQ_FOREACH(entity_link, &system->entities_subscribed, entry) {
        entity_t *entity = entity_link->entity;
        
        position_component_t *position_c = entity_get_component(entity, POSITION_COMPONENT_TYPE);
        speed_component_t *speed_c = entity_get_component(entity, SPEED_COMPONENT_TYPE);
        sprite_component_t *sprite_c = entity_get_component(entity, SPRITE_COMPONENT_TYPE);
        hitbox_component_t *hitbox = entity_get_component(entity, HITBOX_COMPONENT_TYPE);

        position_c->position.x += speed_c->speed.x * sfTime_asSeconds(*elapsed_time);
        position_c->position.y += speed_c->speed.y * sfTime_asSeconds(*elapsed_time);
        sfSprite_setPosition(sprite_c->sprite, position_c->position);
        if (!hitbox) {
            return;
        }
        if (hitbox->type == RECT) {
            sfRectangleShape_setPosition(hitbox->csfml_object, position_c->position);
        } else if (hitbox->type == CIRCLE) {
            sfCircleShape_setPosition(hitbox->csfml_object, position_c->position);
        }
    }
}

system_t *movement_system_create(void)
{
    return system_create(MOVEMENT_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .render_handler = NULL,
        .update_handler = update_handler,
    });
}