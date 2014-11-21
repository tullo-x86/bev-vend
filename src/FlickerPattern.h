/*
 * FlickerPattern.h
 *
 *  Created on: 18 Nov 2014
 *      Author: tully
 */

#ifndef FLICKERPATTERN_H_
#define FLICKERPATTERN_H_

namespace FlickerState {
	enum Enum {
		Ready,
		Recovering,
		Dim,
		Dark
	};
}

class FlickerPattern {
public:
	FlickerPattern(int recoveryTime, char fullBrightness,
				   int dimTime,      char dimBrightness,  char dimChance,
				   int darkTime,     char darkBrightness, char darkChance,
				   char patchiness);
	virtual ~FlickerPattern();

	void Logic(int ms);
	void Render(CRGB *frameBuffer, int length);

private:

	FlickerState::Enum _state;
	int _timeToTransition;

	const int _recoveryTime;
    const int _dimTime;
    const int _darkTime;

	const char _fullBrightness;
    const char _dimBrightness;
    const char _darkBrightness;

    const char _dimChance;
    const char _darkChance;

    const char _patchiness;
};

#endif /* FLICKERPATTERN_H_ */
