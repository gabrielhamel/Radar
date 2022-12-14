#ifndef UI_EVENTS_H
#define UI_EVENTS_H

typedef struct {
    void *context;
    void (*enter)(void *context);
    void (*leave)(void *context);
} hover_event_t;

hover_event_t *ui_hover_event_create(void (*enter)(void *context), void (*leave)(void *context), void *context);

#endif // UI_EVENTS_H