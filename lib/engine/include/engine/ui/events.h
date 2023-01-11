#ifndef ENGINE_UI_EVENTS_H
#define ENGINE_UI_EVENTS_H

typedef struct state_event_t state_event_t;

state_event_t *ui_state_event_create(void (*enter)(void *context), void (*leave)(void *context), void *context);
void ui_state_event_destroy(state_event_t *event);

#endif // ENGINE_UI_EVENTS_H