#include "Utilities.h"
#include <cmath>
// IMPLEMENTATION

double Utilities::energy(double px, double py, double pz, double m){
    return sqrt(pow(px,2.0)+pow(py,2.0)+pow(pz,2.0)+pow(m,2.0));
}
double Utilities::invmass(double px, double py, double pz, double e){
    double m2 = pow(e,2.0)-pow(px,2.0)-pow(py,2.0)-pow(pz,2.0);
    //double m2 = e*e-pX*pX-pY*pY-pZ*pZ;
    double m = m2 > 0 ? sqrt(m2) : -1;
    return m;
}

