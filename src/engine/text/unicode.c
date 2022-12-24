#include <stdlib.h>
#include <string.h>

#include "engine/text/unicode.h"

sfUint32 *string_to_utf8(const char *str)
{
    size_t len = strlen(str);
    sfUint32 *buff = malloc(sizeof(sfUint32) * (len + 1));

    for (size_t idx = 0; idx < len; idx++) {
        buff[idx] = str[idx];
    }
    buff[len] = '\0';
    return buff;
}