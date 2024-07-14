#include <cmath>
#include <iostream>
#include "Event.h"

//FUNCTION DECLARATION
double mass(const Event& ev);

bool add(const Event& ev, double min, double max, double& mass_sum, double& sqr_sum){
    
    // compute invariant mass
    double my_mass = mass(ev);
    
    //check if mass value is in the allowed range
    if ( (min <= my_mass) && (my_mass <= max) ) {
        
        // rescaling result
        my_mass -= min;

        // updating sums
        mass_sum += my_mass;
        sqr_sum += (my_mass*my_mass);
        std::cout << sqr_sum << std::endl;
        //sqr += my_mass*my_mass;
        return true;
    }
    return false;
}