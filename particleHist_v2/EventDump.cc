#include "EventDump.h"
#include "Event.h"
#include <iostream>

using namespace std;

// TO DO
EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::process( const Event& ev ) {
  //write data of the event
    cout << ev.get_eventNumber() << endl
         << ev.get_x() << " " << ev.get_y() << " " << ev.get_z() << endl
         << ev.get_nParticles() << endl;

    for(unsigned int i=0;i<ev.get_nParticles();i++){ //almost everytime runs two times
        cout << ev.get_particle(i)->chg << " " 
             << ev.get_particle(i)->px << " " 
             << ev.get_particle(i)->py << " " 
             << ev.get_particle(i)->pz << endl;
    }
  
  return;

}

