#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pixeltypes.h"

#define NUM_LEDS 100

inline void assignGreater(unsigned char *storage, unsigned char comparison)
{
	if (comparison > *storage) *storage = comparison;
}

#endif
