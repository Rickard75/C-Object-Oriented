#include <iostream>
#include <fstream>
using namespace std;

#include "Event.h"
#include "MassMean.h"
#include "Constants.h"
#include "Utilities.h"

// declare functions to read and dump events
Event* read( ifstream& file );
void dump(const Event* ev);


int main( int argc, char* argv[] ) {

  // open input file
  string nome_file = argv[1];
  ifstream in_file (nome_file);

  // create MassMean objects
  MassMean K0(0.495,0.500);
  MassMean Lambda0(1.115, 1.116);

  // loop over events
  const Event* ev;
  while ( (ev = read(in_file)) != nullptr ) {
    K0.add(*ev);            // *ev is the object Event, indeed add() wants an object Event as input
    Lambda0.add(*ev);
    delete(ev);
  }

  // compute results
  K0.compute();
  Lambda0.compute();

  // print number of selected events and results for both particles
  cout << "\nK0 Mean: " << K0.get_mean() << "\nK0 RMS: " << K0.get_rms() << "\nnAcc: " << K0.get_nAcc() << endl;
  cout << "\nLambda0 Mean: " << Lambda0.get_mean() << "\nKLambda RMS: " << Lambda0.get_rms() << "\nnAcc: " << Lambda0.get_nAcc() << endl;

  return 0;

}

