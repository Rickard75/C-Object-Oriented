#include "ParticleLifetime.h"
#include "ParticleReco.h"

#include "Event.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "MassMean.h"

#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

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

//ParticleLifetimeFactory pmf; already declared in ParticleMass.cc

ParticleLifetime::ParticleLifetime(const AnalysisInfo* info): 
    AnalysisSteering(info){
}

ParticleLifetime::~ParticleLifetime(){
}

// function to be called at execution start
void ParticleLifetime::beginJob() {
    pList.reserve(2);
    pCreate( "K0", 0.495, 0.500);
    pCreate( "Lambda0", 1.115, 1.116);
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
        MassMean*   pMean = p->pMean;
        TH1F*       hMean = p->hMean;
        // compute results
        pMean->compute();
        // print results
        cout << "Particle: " << p->name << endl;
        cout << "Mean: " << pMean->get_mean() << endl;
        cout << "RMS: "  << pMean->get_rms()  << endl;
        cout << "Number of accepted events: " << pMean->get_nAcc() << endl;

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
        if(p->pMean->add(ev)){
            // handling Singleton and getting invariant mass
            static ParticleReco* pr = ParticleReco::instance();
            double mass = pr->get_mass();
            p->hMean->Fill(mass);
        }
    }
    
    return;
}

// creates graph and values to store for a single Particle histogram
void ParticleLifetime::pCreate(const string& name, double min_mass, double max_mass){

    // naming histogram and its axis
    string labels = ";Energy [MeV/c^2];#"; // axis labels
    string long_name = "mass" + name;
    const char* hName = long_name.c_str(); // pointer to long_name
    string title = hName + labels;
    const char* hTitle = title.c_str();

    // setting bin
    int nBins = 200;

    // creating TH1F histogram and statistical object
    Particle* p = new Particle;
    p-> name = name;
    p->pMean = new MassMean(min_mass, max_mass);
    p->hMean = new TH1F(hName, hTitle, nBins, min_mass, max_mass);
    pList.push_back( p );

    return;
}

