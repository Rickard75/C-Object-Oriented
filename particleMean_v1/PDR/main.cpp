/*
    title: particleMean_v1
    version: 1.0 
    author: Riccardo Carroccio
    goal : read data from file and dump on the screen dinamically
    description: this a 3.0 version of the previous code;
                  here we use structs, dynamical allocation of memory with clear after usage,
                  an external personal library with struct definitions;
                  but now only some events are collected after physics check and calculations
    what's new: add.cpp, mass.cpp, calculations to establish correct events
    notes:
        - let s be a struct and ps a pointer to it, then ps->x gives the member x of that struct
        - ev->p_PList[i]->px : correct way to access member of a struct via pointer(=array) of pointers
        - remind: void function need just a 'return;' at the end
        - think to p_PList as a normal array 
        - both read() and dump() here deal with the pointer ev
        - library "Event.h" must be added in order to specify the new struct features, this have to be
            visible from every function called inside main (here: read(),dump(),clear()); 
            note that it is NOT called here in the main specifically!
    new notes:
*/

#include<iostream>
#include<fstream>
using namespace std;

//FORWARD FUNCTION DECLARATION
struct Event;
const Event* read( ifstream& file );  //reading the event from file, a function with Event* as return type
void dump(const Event* ev);           //printing values on screen, no return needed
void clear(const Event* ev);          //free memory space, no return needed

//MAIN
int main(int argc, char* argv[]){

  //open input file
  const char* nome_file = argv[1];    //giving data file from terminal
  ifstream in_file (nome_file);

  // loop over events
  const Event* ev;  //in the 1.0 version here there were a bunch of trial values, now just one line to declare the struct
  while ( ( ev = read( in_file ) ) != nullptr ) {
    dump( ev ); 
    clear( ev );
  }

  return 0;

}