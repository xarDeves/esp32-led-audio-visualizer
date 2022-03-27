#pragma once

#include "colorUtils/Colors.h"

class AnalogManager{

public:
    AnalogManager(Colors::RGB &clrRgb, bool &fftMode);

    void readAnalog();

    ~AnalogManager();
    
private:
	bool *fftMode;
    Colors::RGB *clrRgb;

};