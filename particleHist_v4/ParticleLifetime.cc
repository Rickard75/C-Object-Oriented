// general C++ libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// ROOT libraries
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "util/include/TFileProxy.h"

// particleHist_v3 headers
#include "Event.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"

// particleHist_v4 headers
#include "ParticleLifetime.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "LifetimeFit.h"



// Forward declaration of external function to compute invariant mass
double mass(const Event& ev);
using namespace std;

// concrete factory to create a ParticleLifetime analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory{
    public:
        ParticleLifetimeFactory(): AnalysisFactory::AbsFactory("plot"){}
        AnalysisSteering* create(const AnalysisInfo* info) override{
            return new ParticleLifetime( info );
        }
};

ParticleLifetimeFactory ptf; // global variable to hold an instance of the factory

ParticleLifetime::ParticleLifetime(const AnalysisInfo* info): 
    AnalysisSteering(info){
}

ParticleLifetime::~ParticleLifetime(){
}

// function to be called at execution start
void ParticleLifetime::beginJob() {
    pList.reserve(2);
    pCreate( "K0", 0.495, 0.500, 10.0, 500.0);
    pCreate( "Lambda0", 1.115, 1.116, 10.0, 1000.0);
    return;
}

// function to be called at execution end
void ParticleLifetime::endJob() {

    // creation of ROOT file
    TDirectory* currentDir = gDirectory;
    TFile* file = new TFile(aInfo->value("plot").c_str(), "CREATE");
    // creation of pointer to histogram object with name given by what follows the key "plot" in CREATE mode
    // CREATE mode: new file created or overwriting of existing one

    for (Particle* p: pList){
        // get Particle curve informations: mean, rms, graph
        LifetimeFit*   tMean = p->tMean;
        TH1F*       hMean = p->hMean;
        // compute results
        tMean->compute(); // now does nothing
        // print results
        cout << "Particle: " << p->name << endl;
        //cout << "Mean: " << pMean->get_mean() << endl;
        //cout << "RMS: "  << pMean->get_rms()  << endl;
        cout << "Number of accepted events: " << tMean->get_nAcc() << endl;

        hMean->Write();
        
    }
    
    // close file
    file->Close();
    delete file;
    // restore working area
    currentDir->cd();

    return;
}

// function to be called for each event
void ParticleLifetime::update(const Event& ev){
    for (Particle* p: pList) {
        if(p->tMean->add(ev)){
            // handling Singleton and getting invariant mass
            static ProperTime* pt = ProperTime::instance();
            double my_time = pt->ProperTime::get_time();
            p->hMean->Fill(my_time);
        }
    }
    
    return;
}

// creates graph and values to store for a single Particle histogram
void ParticleLifetime::pCreate(const string& name, double min_mass, double max_mass,double minTime, double maxTime){

    // naming histogram and its axis
    string labels = ";Energy [MeV/c^2];#"; // axis labels
    string long_name = "time" + name;
    const char* hName = long_name.c_str(); // pointer to long_name
    string title = hName + labels;
    const char* hTitle = title.c_str();

    // setting bin
    int nBins = 200;

    // creating TH1F histogram and statistical object
    Particle* p = new Particle;
    p-> name = name;
    p->tMean = new LifetimeFit(min_mass, max_mass);
    p->hMean = new TH1F(hName, hTitle, nBins, minTime, maxTime);
    pList.push_back( p );

    return;
}

