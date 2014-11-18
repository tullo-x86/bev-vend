// BevVend
// Author: Daniel Tullemans / "LuminousElement"
// Created 2014

#include "FastLED.h"
#include <string.h> /* memset */
#include "config.h"
#include <util/delay.h>
#include "FlickerPattern.h"

struct CRGB frameBuffer[NUM_LEDS];

int main()
{
	memset(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);

	FlickerPattern flicker(200, MAX_BRIGHTNESS,
						   100, FLICKER_BRIGHTNESS,
						   50, 5);

    while(1) {
    	flicker.Logic(10);
    	flicker.Render(frameBuffer, NUM_LEDS);

    	FastLED.show();
        _delay_ms(200);

    }
}
