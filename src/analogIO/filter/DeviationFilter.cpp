#include "DeviationFilter.h"

DeviationFilter::DeviationFilter(unsigned char buffLen){

    buff = new unsigned short[buffLen];
    this->buffLen = buffLen;
}

//https://stackoverflow.com/questions/33268513/calculating-standard-deviation-variance-in-c
unsigned short DeviationFilter::deviate(unsigned short &value){

    return sqrt(computeVariance(value));
}

unsigned short DeviationFilter::computeVariance(unsigned short &value){

    double variance = 0;
    double t = buff[0];

    buff[buffCount] = value;
    buffCount++;
    if (buffCount >= buffLen) buffCount = 0;

    for (int i = 1; i < buffLen; i++){
        t += buff[i];
        double diff = ((i + 1) * buff[i]) - t;
        variance += (diff * diff) / ((i + 1.0) *i);
    }

    return variance / (buffLen - 1);
}

DeviationFilter::~DeviationFilter(){
    delete[] buff;
}
