//
//  NaiveFilter.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/8/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "NaiveFilter.hpp"


namespace AudioSynthesis
{
    
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    NaiveFilter::NaiveFilter(float Cutoff, float SampleRate)
    {
        cutoff = Cutoff;
        sampleRate = SampleRate;
        lp = 0;
        hp = 0;
        resonance = 0; // Maybe 1?
        poleSpread = 0;
        w = (sampleRate / 2) / cutoff;
    }
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float NaiveFilter::tickLP(float x)
    {
        update(x);
        return lp;
    }
    
    float NaiveFilter::tickHP(float x)
    {
        update(x);
        return hp;
    }
    
    float NaiveFilter::tickBP(float x)
    {
        update(x);
        return hp + lp;
    }
    
    #pragma mark Accessors
    // -------------------------------------------------- Accessors
    void NaiveFilter::SetSampleRate(float SampleRate)
    {
        sampleRate = SampleRate;
        w = (sampleRate / 2) / cutoff;
    }
    
    void NaiveFilter::SetCutoff(float Cutoff)
    {
        cutoff = Cutoff;
        w = (sampleRate / 2) / cutoff;
    }
    
    void NaiveFilter::SetResonance(float Resonance)
    {
        resonance = Resonance;
    }
    
    void NaiveFilter::SetSpread(float PoleSpread)
    {
        poleSpread = PoleSpread;
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    void NaiveFilter::update(float x)
    {
        hp = x - lp;
        lp = lp + hp * w;
    }

}
