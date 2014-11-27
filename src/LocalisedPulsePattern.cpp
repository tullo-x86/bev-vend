/*
 * LocalisedPulsePattern.cpp
 *
 *  Created on: 27 Nov 2014
 *      Author: tully
 */

#include "LocalisedPulsePattern.h"
#include "config.h"
#include "hsv2rgb.h"

LocalisedPulsePattern::LocalisedPulsePattern(char pulseWidth, int periodMs, char minBrightness, char maxBrightness, bool useColouredPulses) :
_pulseWidth(pulseWidth),
_periodMs(periodMs),
_minBrightness(minBrightness),
_maxBrightness(maxBrightness),
_useColouredPulses(useColouredPulses),
_phase(64000),
_pulseLocation(0),
_pulseHue(0)
{ }

void LocalisedPulsePattern::Logic(int ms)
{
    _phase += ms;

    if (_phase > _periodMs) {
        // TODO: Replace this with { _phase -= _periodMs; } when Logic() has access to `length`
        _phase = 0;
        _pulseHue = random8();
    }
}

void LocalisedPulsePattern::Render(CRGB *frameBuffer, int length)
{
    CRGB rgb;
    hsv2rgb_rainbow(CHSV(_pulseHue, 0, _minBrightness), rgb);

    fill_solid(frameBuffer, length, rgb);

    // TODO: Refactor? We currently have to do this in Render() because we have access to `length` here.
    if (_phase == 0)
    {
        _pulseLocation = random8(length);
    }
    else {
        hsv2rgb_rainbow(CHSV(_pulseHue, _useColouredPulses ? 255 : 0, InterpolatedBrightness()), rgb);

        unsigned char idx = _pulseLocation;
        for (char pixelsToSet = _pulseWidth; pixelsToSet != 0; pixelsToSet--)
        {
            frameBuffer[idx] = rgb;
            idx = (idx + 1) % length;
        }
    }
}

int LocalisedPulsePattern::InterpolatedBrightness()
{
    const unsigned halfPeriod = _periodMs / 2;
    const unsigned halfPeriodAsFractionOfMax = 65535 / halfPeriod;
    fract16 fract;
    if (_phase <= halfPeriod)
    {
        fract = _phase * halfPeriodAsFractionOfMax;
    }
    else
    {
        fract = (_periodMs - _phase) * halfPeriodAsFractionOfMax;
    }

    unsigned minBrightness = ((unsigned)_minBrightness) << 8;
    if (_useColouredPulses) minBrightness = minBrightness / 3 * 5;

    return lerp16by16(minBrightness, ((unsigned)_maxBrightness) << 8, fract) >> 8;
}

LocalisedPulsePattern::~LocalisedPulsePattern()
{ }

