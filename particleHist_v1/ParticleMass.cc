#include "ParticleMass.h"
#include "MassMean.h"
#include "Event.h"

#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"

#include <iostream>

// Forward declaration of external function to compute invariant mass
double mass(const Event& ev);
using namespace std;

ParticleMass::ParticleMass(){
}

ParticleMass::~ParticleMass(){
}

void ParticleMass::beginJob() {
    pList.reserve(2);
    pCreate( "K0", 0.495, 0.500);
    pCreate( "Lambda0", 1.115, 1.116);
    return;
}

void ParticleMass::endJob() {

    // creation of ROOT file
    TDirectory* currentDir = gDirectory;
    TFile* file = new TFile("hist.root", "CREATE");

    for (Particle* p: pList){
        // get Particle curve informations: mean, rms, graph
        MassMean*   pMean = p->pMean;
        TH1F*       hMean = p->hMean;
        // compute results
        pMean->compute();
        // print results
        cout << "\nMean: " << pMean->get_mean() << endl;
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

void ParticleMass::process(const Event& ev){
    for (Particle* p: pList) {
        if(p->pMean->add(ev)){
            p->hMean->Fill(mass(ev));
        }
    }
    
    return;
}

void ParticleMass::pCreate(const string& name, double min_mass, double max_mass){

    const char* hName = name.c_str();
    string labels = ";Energy [MeV/c^2];#";
    string title = hName + labels;
    const char* hTitle = title.c_str();
    int nBins = 200;

    Particle* p = new Particle;
    p-> name = name;
    p->pMean = new MassMean(min_mass, max_mass);
    p->hMean = new TH1F(hName, hTitle, nBins, min_mass, max_mass);
    pList.push_back( p );

    return;
}

