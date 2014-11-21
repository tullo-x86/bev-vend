/*
 * GlobalHueFadePattern.cpp
 *
 *  Created on: 21 Nov 2014
 *      Author: tully
 */

#include "CyclingSolidHuePattern.h"
#include "hsv2rgb.h"

CyclingSolidHuePattern::CyclingSolidHuePattern(char maxSaturation, char brightness)
: _maxSaturation(maxSaturation),
  _brightness(brightness),
  _phase(0)
{ }

void CyclingSolidHuePattern::Logic(int ms)
{
    _phase += ms;
}


void CyclingSolidHuePattern::Render(CRGB *frameBuffer, int length)
{
    int wave = sin16(_phase & 0xffff);
    if (wave == -32768) wave = 32767;
    else if(wave < 0) wave = -wave;

    CHSV hsv((_phase / 50) % HUE_MAX_RAINBOW,
            scale8((wave >> 7), _maxSaturation),
            _brightness);
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    fill_solid(frameBuffer, length, rgb);
}

CyclingSolidHuePattern::~CyclingSolidHuePattern()
{ }

