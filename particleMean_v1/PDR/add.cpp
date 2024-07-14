#include <iostream>
#include <fstream>

#include "Event.h"

bool add(const &Event ev, float min, float max, double &sum, double &sqrtsum){
    sum = 0.0;
    sqrtsum = 0.0;
    /*get double inv_mass from mass.cc*/
    if (inv_mass>0.490 && inv_mass<0.505) {
        sum += inv_mass;
        sqrtsum += pow(inv_mass,2);
        return true;
    }
    return false;
}