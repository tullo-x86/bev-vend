// BevVend
// Author: Daniel Tullemans / "LuminousElement"
// Created 2014

#include "FastLED.h"
#include <string.h> /* memset */
#include "config.h"
#include <util/delay.h>
#include "FlickerPattern.h"

CRGB frameBuffer[NUM_LEDS];

void crash() {
	memset8(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
	for (int i=0; i < NUM_LEDS; i++) {
		if (i % 3 == 0) frameBuffer[i].red = 0x20;
		else if ((i + 1) % 3 == 0) frameBuffer[i].green = 0x20;
		else frameBuffer[i].blue = 0x20;
	}

	FastLED.show();

	while(1); // Busy-wait forever!
}

int main()
{
	memset8(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);

	FlickerPattern flicker(200, 120,
						   100, 120, 64,
						   50,    5, 32,
						   0);

    while(1) {
    	flicker.Logic(1000);
    	flicker.Render(frameBuffer, NUM_LEDS);

    	FastLED.show();
        _delay_ms(1000);

    }
}
