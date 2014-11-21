/*
 * GlobalHueFadePattern.h
 *
 *  Created on: 21 Nov 2014
 *      Author: tully
 */

#ifndef CYCLINGSOLIDHUEPATTERN_H_
#define CYCLINGSOLIDHUEPATTERN_H_

#include "Pattern.h"

class CyclingSolidHuePattern: public Pattern {
public:
    virtual ~CyclingSolidHuePattern();
    CyclingSolidHuePattern(char maxSaturation, char brightness);

    void Logic(int ms);
    void Render(CRGB *frameBuffer, int length);

private:
    const char _maxSaturation;
    const char _brightness;
    unsigned long _phase;
};

#endif /* CYCLINGSOLIDHUEPATTERN_H_ */
