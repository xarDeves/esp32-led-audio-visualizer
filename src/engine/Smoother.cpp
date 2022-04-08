#include "Smoother.h"

Smoother::Smoother(unsigned char len){

    setLen(len);
}

void Smoother::smooth(unsigned char &clrVal){
    
    if (len == 0) return;

    unsigned short s = 1;    
    
    buff[buffCount] = clrVal;
    buffCount++;
    if (buffCount >= len) buffCount = 0;

    for (int i = 0; i < len; i++) s += buff[i];

    clrVal = s/len;
}   

void Smoother::setLen(unsigned char len){
    
    this->len = len;
}

Smoother::~Smoother(){}
