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
		                       int dimTime,      char dimBrightness,  char dimChance,
		                       int darkTime,     char darkBrightness, char darkChance,
		                       char patchiness) :
_recoveryTime(recoveryTime),
_dimTime(dimTime),
_darkTime(darkTime),
_fullBrightness(fullBrightness),
_dimBrightness(dimBrightness),
_darkBrightness(darkBrightness),
_dimChance(dimChance),
_darkChance(darkChance),
_patchiness(patchiness),

_brightness(fullBrightness),
_state(FlickerState::Ready),
_timeToTransition(0)
{
	// Initialise all the things!
}

void FlickerPattern::Logic(int ms)
{
	// Count down every frame
	_timeToTransition -= ms;

	switch(_state) {
		case FlickerState::Ready:
		{
			// Has a chance to go dim or dark

			// Roll the dice
			char roll = random8();
			// Assuming there is one update per second (ms == 1000) then we can naively compare against chance values
			if (roll < _darkChance)
			{
				// Transition to dark
				_state = FlickerState::Dark;
				_timeToTransition = _darkTime;
			}
			else if (roll < _darkChance + _dimChance)
			{
				// Transition to dim
				_state = FlickerState::Dim;
				_timeToTransition = _dimTime;
			}
		}
		break;

		case FlickerState::Recovering:
			// Cannot go dim or dark, but go ready when timer hits zero
			if (_timeToTransition < 0)
			{
				_state = FlickerState::Ready;
			}

			break;

		case FlickerState::Dim:
		case FlickerState::Dark:
			// Timer should count to zero then go recovering
			if (_timeToTransition < 0)
			{
				_state = FlickerState::Recovering;
			}

			break;
		// This shouldn't be possible
		default:
			crash();
			break;
	}
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

