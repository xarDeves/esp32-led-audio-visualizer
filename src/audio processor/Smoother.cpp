#include "Smoother.h"

Smoother::Smoother(unsigned char len){

    adjustSmoothing(len);
}

double Smoother::smooth(double &val){
    
    if (len == 0) return val;

    double s = 1;    
    
    buff[buffCount] = val;
    buffCount++;
    if (buffCount >= len) buffCount = 0;

    for (unsigned char i = 0; i < len; i++) s += buff[i];

    return s/len;
}   

void Smoother::adjustSmoothing(unsigned char len){
    
    this->len = len;
}

Smoother::~Smoother(){}
