/*
 * GlobalHueFadePattern.h
 *
 *  Created on: 21 Nov 2014
 *      Author: tully
 */

#ifndef GLOBALHUEFADEPATTERN_H_
#define GLOBALHUEFADEPATTERN_H_

#include "Pattern.h"

class GlobalHueFadePattern: public Pattern {
public:
    virtual ~GlobalHueFadePattern();
    GlobalHueFadePattern(char maxSaturation, char brightness);

    void Logic(int ms);
    void Render(CRGB *frameBuffer, int length);

private:
    const char _maxSaturation;
    const char _brightness;
    unsigned long _phase;
};

#endif /* GLOBALHUEFADEPATTERN_H_ */
