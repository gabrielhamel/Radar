#include <stdlib.h>

#include "engine/engine.h"
#include "engine/ecs/scene.h"

scene_t *scene_create(void)
{
    scene_t *scene = malloc(sizeof(scene_t));
    sfVector2u window_size = sfRenderWindow_getSize(engine_get()->window);

    TAILQ_INIT(&scene->entities);
    TAILQ_INIT(&scene->systems);
    TAILQ_INIT(&scene->events_handlers);
    scene->ui_element_root = ui_element_create((sfIntRect){
        0,
        0,
        window_size.x,
        window_size.y
    });
    return scene;
}

scene_t *scene_get(void)
{
    return engine_get()->scene;
}

void scene_append_entity(scene_t *scene, entity_t *entity)
{
    TAILQ_INSERT_TAIL(&scene->entities, entity, entry);
}

void scene_remove_entity(scene_t *scene, entity_t *entity)
{
    system_t *system = NULL;
    TAILQ_FOREACH(system, &scene->systems, entry) {
        system_unsubscribe_entity(system, entity);
    }
    TAILQ_REMOVE(&scene->entities, entity, entry);
}

system_t *scene_get_system(scene_t *scene, system_type_t system)
{
    system_t *it = NULL;

    TAILQ_FOREACH(it, &scene->systems, entry) {
        if (it->type == system) {
            return it;
        }
    }
    return NULL;
}

bool scene_append_system(scene_t *scene, system_t *system)
{
    system_t *it = NULL;

    // Check if a system of this type is already present
    TAILQ_FOREACH(it, &scene->systems, entry) {
        if (it->type == system->type) {
            return false;
        }
    }
    TAILQ_INSERT_HEAD(&scene->systems, system, entry);
    return true;
}

void scene_systems_update(scene_t *scene, sfTime *elapsed_time)
{
    system_t *it = NULL;

    TAILQ_FOREACH(it, &scene->systems, entry) {
        if (it->update_handler) {
            it->update_handler(it, elapsed_time);
        }
    }
}

void scene_systems_render(scene_t *scene, sfRenderWindow *window)
{
    system_t *it = NULL;

    TAILQ_FOREACH(it, &scene->systems, entry) {
        if (it->render_handler) {
            it->render_handler(it, window);
        }
    }
}

void scene_ui_render(scene_t *scene, sfRenderWindow *window)
{
    struct ui_element_s *it = NULL;

    TAILQ_FOREACH(it, &scene->ui_element_root->children, entry) {
        ui_element_render(it, scene->ui_element_root->render_target);
    }
    sfRenderTexture_display(scene->ui_element_root->render_target);
    sfRenderWindow_drawSprite(window, scene->ui_element_root->render_sprite, NULL);
}

ui_element_t *scene_get_ui_root(scene_t *scene)
{
    return scene->ui_element_root;
}

void scene_handle_event(scene_t *scene, sfEvent *event)
{
    struct events_handler_s *it = NULL;

    TAILQ_FOREACH(it, &scene->events_handlers, entry) {
        eh_handle_event(it, event);
    }
}

void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler)
{
    TAILQ_INSERT_HEAD(&scene->events_handlers, handler, entry);
}