/*
 * LocalisedPulsePattern.h
 *
 *  Created on: 27 Nov 2014
 *      Author: tully
 */

#ifndef LOCALISEDPULSEPATTERN_H_
#define LOCALISEDPULSEPATTERN_H_

#include "Pattern.h"

class LocalisedPulsePattern: public Pattern {
public:
    LocalisedPulsePattern(char pulseWidth, int periodMs, char minBrightness, char maxBrightness);
    virtual ~LocalisedPulsePattern();

    void Logic(int ms);
    void Render(CRGB *frameBuffer, int length);

private:

    int InterpolatedBrightness();

    const char _pulseWidth;
    const int _periodMs;
    const char _minBrightness;
    const char _maxBrightness;

    unsigned _phase;
    char _pulseLocation;
};

#endif /* LOCALISEDPULSEPATTERN_H_ */
