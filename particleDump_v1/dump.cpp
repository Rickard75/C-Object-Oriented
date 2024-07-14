#include <iostream>
#include <fstream>
using namespace std;

/*
    FUNCTION IMPLEMENTATION: dump()
    description : this short code about the dump() function prints values
                     of a single event on the screen via simple 'cout' way;
                     just to compare without compile the code I've added
                     a print .txt file where data are written as a copy
*/
ofstream out_dump("dump.txt");

void dump(int id_event,
          int N,
          float &x,
          float &y,
          float &z,
          int* charges,
          float* pX,
          float* pY,
          float* pZ){

    //ID_EVENT
    cout << id_event << endl; 
    out_dump << id_event << endl;
    //POSITION
    cout << x << "\t" << y << "\t" << z; 
    out_dump << x << "\t" << y << "\t" << z; 
    cout << endl; 
    out_dump << endl;
    //NUMBER of PARTICLES
    cout << N << endl; 
    out_dump << N << endl; 
    //CHARGES and MOMENTA
    for(int i=0;i<N;i++){
        cout << *(charges + i) << " ";
        cout << *(pX + i) << " ";
        cout << *(pY + i) << " ";
        cout << *(pZ + i) << endl;

        out_dump << *(charges + i) << " ";
        out_dump << *(pX + i) << " ";
        out_dump << *(pY + i) << " ";
        out_dump << *(pZ + i) << endl;
    }

    //cout << "dump() called" << endl;
}