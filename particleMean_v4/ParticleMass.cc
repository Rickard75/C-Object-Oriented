#include "ParticleMass.h"
#include "MassMean.h"

#include <iostream>

using namespace std;

ParticleMass::ParticleMass(){
}

ParticleMass::~ParticleMass(){
}

void ParticleMass::beginJob() {
    
 pList.reserve(2);
 pList.push_back( new MassMean(0.495, 0.500));
 pList.push_back( new MassMean(1.115, 1.116));
 
 return;

}

void ParticleMass::endJob() {
    
    // loop over elements
    for (MassMean* mMean: pList){
        mMean->compute();
        double mean = mMean->get_mean();
        double rms = mMean->get_rms();
        cout << "\nmean: " << mean << "\trms: " << rms << endl;
    }

    return;
}

void ParticleMass::process(const Event& ev){
    for (MassMean* mMean: pList) mMean->add(ev);
}

// modifica di prova   