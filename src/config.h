#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pixeltypes.h"

#define WIDTH_PX 5
#define HEIGHT_PX 11

#define NUM_LEDS (WIDTH_PX + WIDTH_PX + HEIGHT_PX + HEIGHT_PX)

#define TOP_X(n) (n)
#define RIGHT_Y(n) (WIDTH_PX + (n))
#define BOTTOM_X(n) (WIDTH_PX + HEIGHT_PX - (n) - 1)
#define LEFT_Y(n) (NUM_LEDS - (n) - 1)

extern void crash();

inline void assignGreater(unsigned char *storage, unsigned char comparison)
{
	if (comparison > *storage) *storage = comparison;
}

#endif
