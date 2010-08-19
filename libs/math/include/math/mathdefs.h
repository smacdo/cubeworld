#ifndef SCOTT_MATHDEFS_H
#define SCOTT_MATHDEFS_H

#ifndef MATH_DEBUG_MODE
#define MATH_DEBUG_MODE 1
#endif

#define MATH_USE_FUZZY_EQUALS 1

#define FUZZY_DELTA 0.000001
#define FUZZY_EQUALS(a,b) ((a) <= ((b)+FUZZY_DELTA) && (a) >= ((b)-FUZZY_DELTA)) 

#define DEG2RAD(x) PI*(x)/180
#define RAD2DEG(x) (x)*180/PI

#ifndef PI
#define PI 3.141592653589793238462f
#endif

#endif
