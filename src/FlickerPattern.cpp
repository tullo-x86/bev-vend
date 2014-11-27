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
_state(FlickerState::Ready),
_timeToTransition(0),

_recoveryTime(recoveryTime),
_dimTime(dimTime),
_darkTime(darkTime),

_fullBrightness(fullBrightness),
_dimBrightness(dimBrightness),
_darkBrightness(darkBrightness),

_dimChance(dimChance),
_darkChance(darkChance),

_patchiness(patchiness),
_patchSeed(0)
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
			// Yes, I know this code not correctly model probability, but it is good enough for an effect.
			char roll = random8();

			if (roll < (int)_darkChance * ms / 1000)
			{
				// Transition to dark
				_state = FlickerState::Dark;
				_timeToTransition = _darkTime;
			}
			else if (roll < ((int)(_darkChance + _dimChance)) * ms / 1000)
			{
				// Transition to dim
				_state = FlickerState::Dim;
				_timeToTransition = _dimTime;
			}
		}
		break;

		case FlickerState::Recovering:
		{
			// Cannot go dim or dark, but go ready when timer hits zero
			if (_timeToTransition < 0)
			{
				_state = FlickerState::Ready;
			}
		}
		break;

		case FlickerState::Dim:
		case FlickerState::Dark:
		{
			// Timer should count to zero then go recovering
			if (_timeToTransition < 0)
			{
				_state = FlickerState::Recovering;
				_timeToTransition = _recoveryTime;
				_patchSeed++;
			}
		}
		break;

		default:
			// This shouldn't be possible
			crash();
		break;
	}
}

void FlickerPattern::Render(CRGB *frameBuffer, int length)
{
	const char b = _state == FlickerState::Dark ? _darkBrightness :
				   _state == FlickerState::Dim  ? _dimBrightness  :
                                                  _fullBrightness;
	CRGB rgb(b, b, b);
	fill_solid(frameBuffer, length, rgb);

	if (_patchiness != 0) {
		const char b2 = _state == FlickerState::Dark ? 0 :
					    _state == FlickerState::Dim  ? 0 :
					    		                       _darkBrightness;

		// We're using this seed to determine whether we transition, so store it for later
		unsigned int seed = random16_get_seed();
		random16_set_seed((int)_patchiness * b + _patchSeed);

		for(int i = 0; i < length; i++)
		{
			if (random8() < _patchiness) frameBuffer[i] = CRGB(b2, b2, b2);
		}
		random16_set_seed(seed);
	}
}

FlickerPattern::~FlickerPattern()
{ }

