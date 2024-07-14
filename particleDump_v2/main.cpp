/*
    title: particleDump_v2
    version: dump2_a
    author: Riccardo Carroccio
    goal : read data from file and dump on the screen dinamically
    description: this a 2.0 version of the previous code, it just using structs 
                  and dynamical allocation of memory and including an external 
                  personal library with struct definitions; a new code to clear
                  data after usage is now on use
    
    notes:
        - let s be a struct and ps a pointer to it, then ps->x gives the member x of that struct
        - ev->p_PList[i]->px : correct way to access member of a struct via pointer(=array) of pointers
        - remind: void function need just a 'return;' at the end
        - think to p_PList as a normal array 
        - both read() and dump() here deal with the pointer ev
        - library "Event.h" must be added in order to specify the new struct features, this have to be
            visible from every function called inside main (here: read(),dump(),clear()); 
            note that it is NOT called here in the main specifically!
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
  const Event* ev; 
  while ( ( ev = read( in_file ) ) != nullptr ) {
    dump( ev ); 
    clear( ev );
  }

  return 0;

}