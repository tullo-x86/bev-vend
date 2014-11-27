/*
 * LocalisedPulsePattern.cpp
 *
 *  Created on: 27 Nov 2014
 *      Author: tully
 */

#include "LocalisedPulsePattern.h"
#include "config.h"

LocalisedPulsePattern::LocalisedPulsePattern(char pulseWidth, int periodMs, char minBrightness, char maxBrightness) :
_pulseWidth(pulseWidth),
_periodMs(periodMs),
_minBrightness(minBrightness),
_maxBrightness(maxBrightness),
_phase(0),
_pulseLocation(0)
{ }

void LocalisedPulsePattern::Logic(int ms)
{
    _phase += ms;

    if (_phase > _periodMs) {
        // TODO: Replace this with { _phase -= _periodMs; } when Logic() has access to `length`
        _phase = 0;
    }
}

void LocalisedPulsePattern::Render(CRGB *frameBuffer, int length)
{
    memset8(frameBuffer, _minBrightness, length * sizeof(CRGB));

    // TODO: Refactor? We currently have to do this in Render() because we have access to `length` here.
    if (_phase == 0)
    {
        _pulseLocation = random8(length);
    }
    else {
        char pulseBrightness = InterpolatedBrightness();

        unsigned char idx = _pulseLocation;
        for (char pixelsToSet = _pulseWidth; pixelsToSet != 0; pixelsToSet--)
        {
            frameBuffer[idx].setRGB(pulseBrightness, pulseBrightness, pulseBrightness);
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

    return lerp16by16(((unsigned)_minBrightness) << 8, ((unsigned)_maxBrightness) << 8, fract) >> 8;
}

LocalisedPulsePattern::~LocalisedPulsePattern()
{ }

