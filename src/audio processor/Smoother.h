#pragma once

#define CAPACITY 255

class Smoother{

public:
    Smoother(unsigned char len);

    void adjustSmoothing(unsigned char len);

    ~Smoother();

protected:
    double smooth(double &val);    

private:
    double buff[CAPACITY] = {};
    unsigned char buffCount;
    unsigned char len;
};
