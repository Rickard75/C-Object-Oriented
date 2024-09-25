#ifndef MassMean_h
#define MassMean_h

class Event;

/*
  This class manages the computation of the mean and rms of the invariant mass,
  not the single Particle masses. Parameters to distinguish K0 and L0 cases
  are now members of this class. In the end therw will be an object for the
  invariant mass of K0 and one for the invariant mass of L0; indeed two istances
  are declared in main.cc.
*/

class MassMean {

 public:

  // CONSTRUCTOR
  MassMean( double min, double max ); // mass range

  // DESTRUCTOR
  ~MassMean();

  void add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  unsigned int get_nAcc() const;    // return number of accepted events
  double get_mean() const;          // return mean mass
  double get_rms() const;           // return rms  mass
  double get_min() const;

 private:

  double min_mass;                  // min mass, parameter given
  double max_mass;                  // max mass, parameter given

  unsigned int nAcc;                // number of accepted events
  double sum_mass;                  // sum of invariant masses
  double sum_sqr;                   // sum of invariant masses square

  double mean;                     // mean invariant mass
  double rms;                      // rms  mass

};

#endif

