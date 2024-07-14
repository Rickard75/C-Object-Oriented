#include <iostream>
#include <fstream>
using namespace std;

/*
    FUNCTION IMPLEMENTATION: read()
    description : reads values of a SINGLE EVENT extracting data from file: 
                  event space points, number N of particles, charges and momenta; 
                  as output it returns N.
*/

int read(ifstream &in_file,
         float &x,
         float &y,
         float &z,
         int* charges,
         float* pX,
         float* pY,
         float* pZ){


    //POSITION of EVENT
    in_file >> x >> y >> z;

    //NUMBER of PARTICLES 
    int N;
    in_file >> N;

    //CHARGE and MOMENTUM
    for(int i=0;i<N;i++){ //N is #particle of SINGLE event
        
        in_file >> *(charges+i); //object pointed by the array "charges" at position "i"

        in_file >> *(pX + i);
        in_file >> *(pY + i);
        in_file >> *(pZ + i);
        
    }
    
    return N;
    
}