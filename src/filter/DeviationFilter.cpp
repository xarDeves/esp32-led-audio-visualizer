#include "DeviationFilter.h"

DeviationFilter::DeviationFilter(unsigned char buffLen){

    this->buff = new unsigned short[buffLen];
    this->buffLen = buffLen;
}

//https://stackoverflow.com/questions/33268513/calculating-standard-deviation-variance-in-c
unsigned short DeviationFilter::deviate(unsigned short &value){

    return sqrt(this->computeVariance(value));
}

unsigned short DeviationFilter::computeVariance(unsigned short &value){

    double variance = 0;
    double t = this->buff[0];

    this->buff[this->buffCount] = value;
    this->buffCount++;
    if (this->buffCount >= this->buffLen) this->buffCount = 0;

    for (int i = 1; i < this->buffLen; i++){
        t += this->buff[i];
        double diff = ((i + 1) * this->buff[i]) - t;
        variance += (diff * diff) / ((i + 1.0) *i);
    }

    return variance / (this->buffLen - 1);
}

DeviationFilter::~DeviationFilter(){
    delete[] this->buff;
}
