#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pixeltypes.h"

#define WIDTH_PX 3
#define HEIGHT_PX 5

// NB: Total of actual vending machine LED strip will be 100.
// This is corrected for in main.cpp, and its padding will need
// to be removed when these dimensions add up to 100.
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
