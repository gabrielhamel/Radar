#include <radar/systems/movement.h>
#include <radar/components/position.h>
#include <radar/components/speed.h>
#include <radar/components/hitbox.h>
#include <radar/components/sprite.h>

static void update_hitbox(entity_t *entity, position_component_t *position)
{
    hitbox_component_t *hitbox = entity_get_component_data(entity, HITBOX_COMPONENT_TYPE, hitbox_component_t);
    if (hitbox) {
        if (hitbox->type == RECT) {
            sfRectangleShape_setPosition(hitbox->csfml_object, position->position);
        } else if (hitbox->type == CIRCLE) {
            sfCircleShape_setPosition(hitbox->csfml_object, position->position);
        } else if (hitbox->type == CUSTOM) {
            sfConvexShape_setPosition(hitbox->csfml_object, position->position);
        }
    }
}

static void update_sprite(entity_t *entity, position_component_t *position)
{
    sprite_component_t *sprite = entity_get_component_data(entity, SPRITE_COMPONENT_TYPE, sprite_component_t);
    if (sprite) {
        sfSprite_setPosition(sprite->sprite, position->position);
    }
}

static void update_handler(system_t *system, sfTime *elapsed_time)
{
    entity_iterator_t *it = system_get_entity_iterator(system);

    for (entity_t *entity = it->current; entity; entity = entity_iterator_next(it)) {
        position_component_t *position = entity_get_component_data(entity, POSITION_COMPONENT_TYPE, position_component_t);
        speed_component_t *speed_c = entity_get_component_data(entity, SPEED_COMPONENT_TYPE, speed_component_t);
        position->position.x += speed_c->speed.x * sfTime_asSeconds(*elapsed_time);
        position->position.y += speed_c->speed.y * sfTime_asSeconds(*elapsed_time);

        update_sprite(entity, position);
        update_hitbox(entity, position);
    }
    entity_iterator_destroy(it);
}

system_t *movement_system_create(void)
{
    return system_create(MOVEMENT_SYSTEM_TYPE, (system_params_t){
        .context = NULL,
        .update_handler = update_handler,
        .destroy_handler = NULL
    });
}