#pragma once

#define CAPACITY 255

class Smoother{

public:
    Smoother(unsigned char len);

    void smooth(unsigned char &clrVal);    
    void setLen(unsigned char len);

    ~Smoother();

private:
    unsigned char buff[CAPACITY] = {};
    unsigned char buffCount;
    unsigned char len;
};
