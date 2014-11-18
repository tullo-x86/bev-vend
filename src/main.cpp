// BevVend
// Author: Daniel Tullemans / "LuminousElement"
// Created 2014

#include "FastLED.h"
#include <string.h> /* memset */
#include "config.h"
#include "mesmer.h"
#include "bounce.h"
#include "sparkspattern.h"
#include <util/delay.h>

struct CRGB frameBuffer[NUM_LEDS];

int main()
{
	memset(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);
	CHSV hsv(0, 0, MAX_BRIGHTNESS);
	CRGB rgb;

    while(1) {

    	hsv.val = (rand() % 2 == 0) ? MAX_BRIGHTNESS : FLICKER_BRIGHTNESS;

    	hsv2rgb_rainbow(hsv, rgb);
    	fill_solid(frameBuffer, NUM_LEDS, rgb);
    	FastLED.show();
        _delay_ms(200);

    }
}
