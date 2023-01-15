#ifndef ENGINE_TOOLS_MACROS_H
#define ENGINE_TOOLS_MACROS_H

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif

#include <math.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#endif // ENGINE_TOOLS_MACROS_H