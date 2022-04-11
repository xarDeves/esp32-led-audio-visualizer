#pragma once

#include "persistence/EngineInfo.h"
#include "color utils/Colors.h"

class Model{

public:
    Model();

    bool fftMode = true;

	Colors::RGB clrRGB;
    EngineInfo::info engineInfo;

    ~Model();
private:

};
