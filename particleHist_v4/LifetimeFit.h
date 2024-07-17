#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

 public:

  // CONSTRUCTOR
  LifetimeFit( double min, double max ); // mass range

  // DESTRUCTOR
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  unsigned int get_nAcc() const;                // return number of accepted events
  double get_mean() const;                // return mean mass
  double get_rms() const;                 // return rms  mass
  double get_min() const;

 private:

  double min_mass; // min mass
  double max_mass; // max mass

  unsigned int nAcc; // number of accepted events
  double sum_mass; // sum of masses
  double sum_sqr; // sum of masses square

  double mean; // mean mass
  double rms; // rms  mass

};

#endif

