#ifndef Event_h
#define Event_h

/*
Create a "Particle" struct, with members corresponding to the data
for each particle (charge, 3 momentum components).
Create an "Event" struct, with members corresponding to the data
for each event (event identifier, 3 decay point coordinates,
number of particles, array of pointers to Particle structs, i.e. Particle**).
*/

struct Particle{
    int chg;        //charge (+1 or -1)
    float px,py,pz; //momenta of particle
};

struct Event{
    int evNum;              //event identifier
    float x,y,z;            //event coordinates
    int nP;                 //number of particles involved
    Particle **p_PList;     //pointer of pointers (=array of pointers),
                                //stores the address of the Particles, which point to their members
};

#endif