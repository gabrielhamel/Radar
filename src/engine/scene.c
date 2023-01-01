#include <stdlib.h>

#include "engine/scene.h"
#include "engine/engine.h"

scene_t *scene_create(void)
{
    scene_t *scene = malloc(sizeof(scene_t));
    sfVector2u window_size = sfRenderWindow_getSize(engine_get()->window);

    LIST_INIT(&scene->entities);
    LIST_INIT(&scene->systems);
    LIST_INIT(&scene->entities_to_systems);
    LIST_INIT(&scene->events_handlers);
    scene->ui_element_root = ui_element_create((sfIntRect){
        0,
        0,
        window_size.x,
        window_size.y
    });
    return scene;
}

void scene_append_entity(scene_t *scene, entity_t *entity)
{
    LIST_INSERT_HEAD(&scene->entities, entity, entry);
}

bool scene_append_system(scene_t *scene, system_t *system)
{
    system_t *it = NULL;

    // Check if a system of this type is already present
    LIST_FOREACH(it, &scene->systems, entry) {
        if (it->type == system->type) {
            return false;
        }
    }
    LIST_INSERT_HEAD(&scene->systems, system, entry);
    return true;
}

bool scene_subscribe_entity_to_system(scene_t *scene, entity_t *entity, system_type_t system_type)
{
    entity_system_subscribe_link_t *it = NULL;
    system_t *system_it = NULL;
    system_t *system_to_find = NULL;

    // Check if the link already exist (kinda heavy)
    LIST_FOREACH(it, &scene->entities_to_systems, entry) {
        if (it->system->type == system_type) {
            if (it->entity == entity) {
                return false;
            }
            system_to_find = it->system;
        }
    }
    LIST_FOREACH(system_it, &scene->systems, entry) {
        if (system_it->type == system_type) {
            system_to_find = system_it;
        }
    }
    // Check if the system exist
    if (system_to_find == NULL) {
        return false;
    }
    // Create the link
    it = malloc(sizeof(entity_system_subscribe_link_t));
    it->system = system_to_find;
    it->entity = entity;
    LIST_INSERT_HEAD(&scene->entities_to_systems, it, entry);
    return true;
}

void scene_systems_update(scene_t *scene, sfTime *elapsed_time)
{
    entity_system_subscribe_link_t *it = NULL;

    LIST_FOREACH(it, &scene->entities_to_systems, entry) {
        if (it->system->update_handler) {
            it->system->update_handler(it->entity, elapsed_time, it->system->context);
        }
    }
}

void scene_systems_render(scene_t *scene, sfRenderWindow *window)
{
    entity_system_subscribe_link_t *it = NULL;

    LIST_FOREACH(it, &scene->entities_to_systems, entry) {
        if (it->system->render_handler) {
            it->system->render_handler(it->entity, window, it->system->context);
        }
    }
}

void scene_ui_render(scene_t *scene, sfRenderWindow *window)
{
    struct ui_element_s *it = NULL;

    LIST_FOREACH(it, &scene->ui_element_root->children, entry) {
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

    LIST_FOREACH(it, &scene->events_handlers, entry) {
        eh_handle_event(it, event);
    }
}

void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler)
{
    LIST_INSERT_HEAD(&scene->events_handlers, handler, entry);
}