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
	/*
	switch(_state) {
		case FlickerState::Ready:
			// Has a chance to go dim or dark
			break;
		case FlickerState::Recovering:
			// Cannot go dim or dark, timer should count down until ready again
			break;
		case FlickerState::Dim:
			// Timer should count to zero then go ready
			break;
		case FlickerState::Dark:
			// Timer should count to zero then go ready
			break;
		default:
			break;
	}*/
}

void FlickerPattern::Render(CRGB *frameBuffer, int length)
{
	//CHSV hsv(0, 0, _brightness);
	CRGB rgb(_brightness, _brightness, _brightness);
	//hsv2rgb_rainbow(hsv, rgb);
	fill_solid(frameBuffer, length, rgb);
}

FlickerPattern::~FlickerPattern()
{
	// TODO Auto-generated destructor stub
}

