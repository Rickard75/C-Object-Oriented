#ifndef Utilities_h
#define Utilities_h

// INTERFACE
class Utilities {
    public:
        static double energy(double px, double py, double pz, double m);
        static double invmass(double px, double py, double pz, double e);
};

#endif

// static: shown only in the interface, it says that those member functions
//          are readable without the creation of a full instance-object of 
//          that class, so it is possible to call Utilities::energy to use it