#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>

class Event;
class MassMean;


class ParticleMass: public AnalysisSteering {

    public:

        ParticleMass();
        ParticleMass           (const ParticleMass& x) = delete;
        ParticleMass& operator=(const ParticleMass& x) = delete;

        ~ParticleMass() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void   endJob() override;
        // function to be called for each event
        void process( const Event& ev ) override;

    private:
        // list of pointers to MassMean object, they will be 2 for the different decays
        std::vector<MassMean*> pList;
        
};

#endif