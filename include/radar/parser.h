#ifndef RADAR_PARSER_H
#define RADAR_PARSER_H

#include <stdio.h>
#include <engine/tools/lists.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(*x))
#define ARG_SEPARATORS " \t"

typedef enum {
    AIRCRAFT = 'A',
    TOWER = 'T',
    STORM = 'S'
} entity_type_t;

typedef struct {
    entity_type_t type;
    int number_of_params;
} entity_filter_t;

typedef struct radar_entity_definition_s {
    TAILQ_ENTRY(radar_entity_definition_s) entry;
    entity_type_t type;
    int *args;
    int args_count;
} radar_entity_definition_t;

typedef struct {
    int *args;
    int count;
} parsed_arg_t;

typedef struct {
    TAILQ_HEAD(, radar_entity_definition_s) entities;
} radar_definition_t;

radar_definition_t *parser_read(const char *filename);
void radar_entity_definition_destroy(radar_entity_definition_t *entity);

#endif // RADAR_PARSER_H