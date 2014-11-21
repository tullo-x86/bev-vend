// BevVend
// Author: Daniel Tullemans / "LuminousElement"
// Created 2014

#include "FastLED.h"
#include "config.h"
#include <util/delay.h>
#include "FlickerPattern.h"

CRGB frameBuffer[NUM_LEDS];

void crash() {
    memset8(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);

    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 3 == 0)
            frameBuffer[i].red = 0x20;
        else if ((i + 1) % 3 == 0)
            frameBuffer[i].green = 0x20;
        else
            frameBuffer[i].blue = 0x20;
    }

    FastLED.show();

    while (1)
        ; // Busy-wait forever!
}

int main() {
    memset8(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);

    FlickerPattern flicker(200, 32,
                           600, 16, 64,
                           100, 6, 32,
                           64);

    while (1)
    {
        flicker.Logic(100);
        flicker.Render(frameBuffer, NUM_LEDS);

        FastLED.show();
        _delay_ms(100);

    }
}
