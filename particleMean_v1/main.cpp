/*
    title: particleMean_v1
    version: v1 
    author: Riccardo Carroccio
    goal : compute mass and distinguish decay
    description: this a 3.0 version of the previous code;
                  here we use structs, dynamical allocation of memory with clear after usage,
                  an external personal library with struct definitions;
                  but now only some events are collected after physics check and calculations
    notes:
        - remind: void function need just a 'return;' at the end
        - library "Event.h" must be added in order to specify the new struct features, this have to be
            visible from every function called inside main (here: read(),dump(),clear()); 
            note that it is NOT called here in the main specifically!
    news here:
        - 
*/

#include<iostream>
#include<cmath>
#include<fstream>
#include "Event.h"
using namespace std;

//FORWARD FUNCTION DECLARATION
Event* read( ifstream& file );  //reading the event from file
void dump(const Event* ev);           //printing values on screen
void clear(const Event* ev);          //free memory space
bool add(const Event& ev, double min, double max, double& mass_sum, double& sqr_sum);  //select physical data tracks

//MAIN
int main(int argc, char* argv[]){

  
  const char* nome_file = argv[1];    //read data file from terminal
  ifstream in_file (nome_file);       //open input file

  int ok_events = 0;
  double mass_sum = 0.0;
  double sqr_sum = 0.0;
  double mean = 0.0;
  double rms = 0.0;

  double mini = 0.490;
  double mantikos = 0.505;

  // loop over events
  Event* ev;  
  while ( ( ev = read( in_file ) ) != nullptr ) {
    //dump( ev ); 
    if ( add( *ev, mini, mantikos, mass_sum, sqr_sum ) ) ok_events++; //increase #accepted events
    clear( ev );
  }

  // calculate rescaled mean
  mean = (mass_sum * 1.0)/ok_events;
  mean += mini;

  //calculate rms
  //double var = ((sqr_sum*1.0)/ok_events)-pow(mean,2);
  double var = (((sqr_sum*1.0)/(double)ok_events)-(mean*mean));
  //rms = sqrt(var);
  var > 0 ? rms = sqrt(var) : rms=-1;

  // results
  cout << "MEAN: " << mean << "\nRMS: " << rms << "\nOK EVENTS: " << ok_events << endl;
  cout << "VAR: " << var << endl;
  return 0;

}