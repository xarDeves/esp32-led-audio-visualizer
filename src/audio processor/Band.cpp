#include "Band.h"

Band::Band(unsigned char &lower, unsigned char &upper, unsigned char &smoothingLen, double *vReal) : 
Smoother(smoothingLen){

	adjustLimits(lower, upper);
	this->vReal = vReal;
}

unsigned char Band::renderRGB(){

    sumBand();
    return map(smooth(bandSum), NOISE, MAX, 0 , 255);
}

void Band::sumBand() {

    bandSum = 0.0;

	for (int i = *lower; i < *upper; i++) {
		if (vReal[i] > NOISE)
			bandSum += vReal[i];
	}

    bandSum = bandSum / devider;
}

void Band::adjustLimits(unsigned char &lower, unsigned char &upper){

    this->lower = &lower;
    this->upper = &upper;
    computeDevider();
}

void Band::computeDevider(){

    devider = log(*upper - *lower);
}

Band::~Band(){}