#ifndef UI_EVENTS_H
#define UI_EVENTS_H

typedef struct {
    void *context;
    void (*enter)(void *context);
    void (*leave)(void *context);
} state_event_t;

state_event_t *ui_state_event_create(void (*enter)(void *context), void (*leave)(void *context), void *context);
void ui_state_event_destroy(state_event_t *event);

#endif // UI_EVENTS_H