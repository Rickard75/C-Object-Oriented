#ifndef ParticleReco_h
#define ParticleReco_h

#include "Event.h"

#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"

class ParticleReco: public Singleton<ParticleReco>,
                    public LazyObserver<Event> {

  friend class Singleton<ParticleReco>;

 public:

  // particle types
  enum ParticleType { K0, Lambda0, unknown };

  // recompute informations for new event
  void update( const Event& ev ) override;

  // return particle type
  ParticleType get_type();
  // return particle energy
  double get_energy();
  // return particle mass
  double get_mass();

 private:

  // private constructor and destructor for singleton
  ParticleReco();
  // deleted copy constructor and assignment to prevent unadvertent copy
  ParticleReco           ( const ParticleReco& x ) = delete;
  ParticleReco& operator=( const ParticleReco& x ) = delete;

  // destructor
  ~ParticleReco() override;

  // particle type
  ParticleType decay_type;
  // particle energy
  double total_energy;
  // particle mass
  double particle_mass;

};

#endif

