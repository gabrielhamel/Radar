#ifndef ENGINE_UNICODE_H
#define ENGINE_UNICODE_H

#include <SFML/Config.h>

void string_to_utf8(sfUint32 *buff, const char *str, size_t max_len);

#endif // ENGINE_UNICODE_H