#pragma once

#include <math.h>

class DeviationFilter{

public:

    DeviationFilter(unsigned char buffLen);

    unsigned short deviate(unsigned short &value);
    
    ~DeviationFilter();

private:
    unsigned short *buff;
    unsigned short buffLen;
    unsigned short buffCount = 0;

    unsigned short computeVariance(unsigned short &value);
};

