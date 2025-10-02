#ifndef MACROS_H
#define MACROS_H

// Standard linear interpolation algorithm
#define lerp(a, b, t) (a + t * (b - a))

// Chooses the smallest of two values
#define min(a, b) (b > a ? a : b)

// Chooses the largest of two values
#define max(a, b) (b > a ? b : a)

// Chooses a if a is between b or c, if not chooses
// either b if a is less than b, or c if a is greater than c
#define clamp(a, b, c) (min(c, max(a, b)))

#endif