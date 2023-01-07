#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "radar/parser.h"

static const entity_filter_t entity_filters[]  = {
    { AIRCRAFT, 6},
    {TOWER, 3}
};

static entity_filter_t *parser_find_entity_type(char *token, size_t *line_nb)
{
    entity_filter_t *entity_filter;

    if (strlen(token) > 2) {
        fprintf(stderr, "Line %zd: Invalid entity type format\n", *line_nb);
        return NULL;
    }
    for (size_t idx = 0; idx < ARRAY_LENGTH(entity_filters); idx++) {
        if (token[0] == entity_filters[idx].type) {
            entity_filter = (entity_filter_t *)&entity_filters[idx];
        }
    }
    if (entity_filter == NULL) {
        fprintf(stderr, "Line %zd: Unknown entity type\n", *line_nb);
        return NULL;
    }
    return entity_filter;
}

static unsigned int *parser_get_args(entity_filter_t *entity_filter, size_t *line_nb)
{
    unsigned int *args = malloc(sizeof(unsigned int) * entity_filter->number_of_params);
    size_t arg_index = 0;
    char *token;

    do {
        token = strtok(NULL, ARG_SEPARATORS);
        if (token == NULL) {
            break;
        }
        if (arg_index >= entity_filter->number_of_params) {
            fprintf(stderr, "Line %zd: Too many arguments\n", *line_nb);
            free(args);
            return NULL;
        }
        args[arg_index++] = atoi(token);
    } while (token);
    if (arg_index != entity_filter->number_of_params) {
        fprintf(stderr, "Line %zd: Too few arguments\n", *line_nb);
        free(args);
        return NULL;
    }
    return args;
}

static radar_entity_definition_t *parser_parse_entity(FILE *file, size_t *line_nb)
{
    char line[4096] = {0};
    char *token = NULL;
    char *readed = NULL;

    readed = fgets(line, 4096, file);

    entity_filter_t *entity_filter = NULL;
    unsigned int *args;
    radar_entity_definition_t *def;

    if (readed == NULL) {
        return NULL;
    } else if (strlen(readed) == 1) {
        (*line_nb)++;
        return parser_parse_entity(file, line_nb);
    }
    token = strtok(line, ARG_SEPARATORS);
    entity_filter = parser_find_entity_type(token, line_nb);
    if (entity_filter == NULL) {
        return NULL;
    }
    args = parser_get_args(entity_filter, line_nb);
    if (args == NULL) {
        return NULL;
    }
    def = malloc(sizeof(radar_entity_definition_t));
    def->type = entity_filter->type;
    def->args = args;
    return def;
}

radar_definition_t *parser_read(const char *filename)
{
    radar_definition_t *radar = malloc(sizeof(radar_definition_t));
    FILE *file = fopen(filename, "r");
    size_t line_idx = 1;
    radar_entity_definition_t *entity;

    if (file == NULL) {
        fprintf(stderr, "\"%s\": ", filename);
        perror(NULL);
        return NULL;
    }
    TAILQ_INIT(&radar->entities);
    do {
        entity = parser_parse_entity(file, &line_idx);
        if (entity == NULL) {
            break;
        }
        TAILQ_INSERT_HEAD(&radar->entities, entity, entry);
        line_idx++;
    } while (entity);
    fclose(file);
    return radar;
}

void radar_entity_definition_destroy(radar_entity_definition_t *entity)
{
    free(entity->args);
    free(entity);
}