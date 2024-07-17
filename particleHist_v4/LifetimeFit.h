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
  double get_min() const;

 private:

  double min_mass; // min mass
  double max_mass; // max mass

  unsigned int nAcc; // number of accepted events
};

#endif

