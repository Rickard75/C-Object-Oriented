#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>
#include <string>
#include "TH1F.h"

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

        struct Particle {
            std::string name;   // element name
            MassMean*   pMean;  // statistic object
            TH1F*       hMean;  // graph
        };
    
    private:

        // list of pointers to ParticleCurve object(2 since only K0 and Lambda0)
        std::vector<Particle*> pList;

        // creates graph and values to store for a single Particle Curve
        void pCreate (const std::string& name, double min_mass, double max_mass);
        
};

#endif