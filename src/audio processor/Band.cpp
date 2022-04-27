#include "Band.h"

Band::Band(unsigned char &lower, unsigned char &upper, unsigned char &smoothingLen, unsigned int  &noise, double *vReal) : 
Smoother(smoothingLen){

    adjustNoise(noise);
	adjustLimits(lower, upper);
	this->vReal = vReal;
}

double Band::sumBand() {

    double sum = 0.0;

	for (int i = *lower; i < *upper; i++) {
		if (vReal[i] > *noise)
			sum += vReal[i];
	}

    return sum / devider;
}

void Band::adjustLimits(unsigned char &lower, unsigned char &upper){

    this->lower = &lower;
    this->upper = &upper;
    computeDevider();
}

void Band::adjustNoise(unsigned int &noise){

    this->noise = &noise;
}

void Band::computeDevider(){

    devider = log(*upper - *lower);
}

Band::~Band(){}