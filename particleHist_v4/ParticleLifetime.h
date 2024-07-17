#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include "AnalysisSteering.h"
#include "TH1F.h"
#include "util/include/ActiveObserver.h"

#include <vector>
#include <string>

class Event;
class MassMean;
class AnalysisInfo;


class ParticleLifetime: public AnalysisSteering,
                    public ActiveObserver<Event> {

    public:
        // constructor, now with initial information
        ParticleLifetime( const AnalysisInfo* info);
        // copy constructor, set in delete mode (to avoid copy)
        ParticleLifetime( const ParticleLifetime& x ) = delete;
        // assignment operator, set in delete mode (to avoid copy)
        ParticleLifetime& operator=( const ParticleLifetime& x ) = delete;
        // destructor
        ~ParticleLifetime() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void   endJob() override;
        // function to be called for each event
        void update( const Event& ev ) override;

        
    
    private:
        // particle object
        struct Particle {
            std::string name;   // element name
            MassMean*   pMean;  // statistic object
            TH1F*       hMean;  // graph
        };

        // list of pointers to ParticleCurve object(2 since only K0 and Lambda0)
        std::vector<Particle*> pList;

        // creates graph and values to store for a single Particle Curve
        void pCreate (const std::string& name, double min_mass, double max_mass);
        
};

#endif