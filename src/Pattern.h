/*
 * Pattern.h
 *
 *  Created on: 21 Nov 2014
 *      Author: tully
 */

#ifndef PATTERN_H_
#define PATTERN_H_

#include "pixeltypes.h"

class Pattern {
public:
    virtual void Logic(int ms) = 0;
    virtual void Render(CRGB *frameBuffer, int length) = 0;

    virtual ~Pattern();
};

#endif /* PATTERN_H_ */
