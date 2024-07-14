/*
    title: particleDump_v1
    version: dump1_b
    author: Riccardo Carroccio
    goal : read data from file and dump on the screen
    description: this code takes the file "particle_events.txt", use the functions
                    read() and dump() (located in 'read.cpp' and 'dump.cpp'), then
                    set the possible number of particles detected to 10, then for 
                    each event it reads the event identifier in the main and if 
                    successfull it reads and then dumps out into screen the values

    notes:
        - better not to call variables as 'if'; might be troubling
        - HOW TO PASS ARRAY between FUNCTIONS: with pointers
    learnt:
        - to use argc and argv[] as main() arguments
        - possibility to load all files at once with "g++ -Wall name_of_exec *.cpp"
        - implementation of ifstream.read() function with its arguments
            basic_istream& read (char_type* s, streamsize n);
            Extracts n characters from the stream and stores them in the array pointed by s.
*/

#include <iostream>
#include <fstream>
using namespace std;

//DECLARATION of FUNCTIONS
int read(std::ifstream &in_file,
         float &x, float &y, float &z,
         int *charges,
         float *pX, float *pY, float *pZ);

void dump(int id_event,
          int N,
          float &x, float &y, float &z,
          int* charges,
          float *pX, float *pY,float *pZ
          );

//MAIN
int main(int argc, char* argv[]){
    //open input file
    const char* nome_file = argv[1];
    ifstream in_file (nome_file);

    //declare event variables to be read from ifstream in the loop
    int id_event=1;                     //a trial value
    int nParticles;
    float x = 0.0, y = 0.0, z = 0.0;    //the event takes place in a SINGLE point of the 3D space
    int charges[10];                    //10 is max number of particle interacting in 1 event
    float pX[10], pY[10], pZ[10];

    //loop over events
    while ( in_file >> id_event ){      //successfull reading    
        nParticles = read (in_file, 
                           x, y, z,
                           charges,
                           pX, pY, pZ); //storing #particles
        dump(id_event,
             nParticles,                
             x, y, z,
             charges,
             pX, pY, pZ);               //prints values on screen 
    
    }

    cout << "\nCompilation time: " << __TIME__ << endl;

    return 0;
}

