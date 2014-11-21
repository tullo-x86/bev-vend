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

FlickerPattern flicker1(200, 32,
               600, 16, 64,
               100, 6,  32,
               128);

FlickerPattern flicker2(3000, 32,
               100 , 16, 64,
               30  ,  6, 32,
               64);

#define NUM_PATTERNS 2
Pattern *patterns[NUM_PATTERNS] = {
        &flicker1,
        &flicker2
};

#define FPS 30
#define FRAME_MS (1000 / FPS)
int currentPattern = 0;
#define SECONDS_BETWEEN_PATTERNS 5
#define FRAMES_BETWEEN_PATTERNS (FPS * SECONDS_BETWEEN_PATTERNS)
int framesUntilNextPattern = FRAMES_BETWEEN_PATTERNS;

// This is to ensure the .data section size includes the amount of memory
// used by the whole framebuffer when addressing a whole 100LED strip.
CRGB buffer_padding_delete_me[100 - NUM_LEDS];

int main() {
    DDRB |= 0x02;
    PORTB |= 0x02;
    memset8(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
    memset8(buffer_padding_delete_me, 0, sizeof(struct CRGB) * (100 - NUM_LEDS));
    FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);

    while (1)
    {
        if (--framesUntilNextPattern == 0) {
            PORTB ^= 0x02;
            framesUntilNextPattern = FRAMES_BETWEEN_PATTERNS;
            if (++currentPattern == NUM_PATTERNS) currentPattern = 0;
        }

        patterns[currentPattern]->Logic(FRAME_MS);
        patterns[currentPattern]->Render(frameBuffer, NUM_LEDS);

        FastLED.show();
        _delay_ms(FRAME_MS);
    }
}
