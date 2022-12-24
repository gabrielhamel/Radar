#ifndef SCENE_H
#define SCENE_H

#include "queue.h"
#include "ui/element.h"
#include "entity/entity.h"

typedef struct {
    LIST_HEAD(, events_handler_s) events_handlers;
    ui_element_t *ui_element_root;
    LIST_HEAD(, entity_s) entities;
    void *update_context;
    void (*update_delegate)(void *context, sfTime *elapsed_time);
} scene_t;

scene_t *scene_create(void);
void scene_handle_event(scene_t *scene, sfEvent *event);
void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler);
void scene_render_ui(scene_t *scene, sfRenderWindow *window);
void scene_render(scene_t *scene, sfRenderWindow *window);
void scene_update(scene_t *scene, sfTime *elapsed_time);
void scene_append_entity(scene_t *scene, entity_t *entity);
ui_element_t *scene_get_ui_root(scene_t *scene);
void scene_set_update_delegate(scene_t *scene, void (*callback)(void *, sfTime *), void *context);

#endif // SCENE_H