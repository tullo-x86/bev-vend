/*
 * FlickerPattern.cpp
 *
 *  Created on: 18 Nov 2014
 *      Author: tully
 */
#include "config.h"
#include "FlickerPattern.h"
#include "hsv2rgb.h"
#include <stdlib.h>

FlickerPattern::FlickerPattern(int recoveryTime, char fullBrightness,
		                       int dimTime,      char dimBrightness,
		                       int darkTime,     char darkBrightness) :
_recoveryTime(recoveryTime),
_dimTime(dimTime),
_darkTime(darkTime),
_fullBrightness(fullBrightness),
_dimBrightness(dimBrightness),
_darkBrightness(darkBrightness),
_brightness(fullBrightness)
{
	// TODO Auto-generated constructor stub
}

void FlickerPattern::Logic(int ms)
{
	_brightness = rand() % 3 == 0 ? _dimBrightness : _fullBrightness;
}

void FlickerPattern::Render(CRGB *frameBuffer, int length)
{
	CHSV hsv(0, 0, _brightness);
	CRGB rgb;
	hsv2rgb_rainbow(hsv, rgb);
	fill_solid(frameBuffer, length, rgb);
}

FlickerPattern::~FlickerPattern()
{
	// TODO Auto-generated destructor stub
}

