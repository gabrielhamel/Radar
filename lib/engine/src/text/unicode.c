#include <stdlib.h>
#include <string.h>

#include "unicode.h"

void string_to_utf8(sfUint32 *buff, const char *str, size_t max_len)
{
    size_t len = strlen(str);

    for (size_t idx = 0; idx < len && idx < max_len; idx++) {
        buff[idx] = str[idx];
    }
    buff[len] = '\0';
    return buff;
}