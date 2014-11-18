#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pixeltypes.h"

#define NUM_LEDS 100

#define MAX_BRIGHTNESS 255
#define FLICKER_BRIGHTNESS 220

inline void assignGreater(unsigned char *storage, unsigned char comparison)
{
	if (comparison > *storage) *storage = comparison;
}

#endif
