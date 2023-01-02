#ifndef RADAR_PARSER_H
#define RADAR_PARSER_H

#include <stdio.h>
#include "engine/queue.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(*x))
#define ARG_SEPARATORS " \t"

typedef enum {
    AIRCRAFT = 'A',
    TOWER = 'T',
} entity_type_t;

typedef struct {
    entity_type_t type;
    unsigned int number_of_params;
} entity_filter_t;

typedef struct radar_entity_definition_s {
    LIST_ENTRY(radar_entity_definition_s) entry;
    entity_type_t type;
    unsigned int *args;
} radar_entity_definition_t;

typedef struct {
    LIST_HEAD(, radar_entity_definition_s) entities;
} radar_definition_t;

radar_definition_t *parser_read(const char *filename);

#endif // RADAR_PARSER_H