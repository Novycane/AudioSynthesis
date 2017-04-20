//
//  Oscillator.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Oscillator.hpp"

namespace AudioSynthesis
{
    
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    Oscillator::Oscillator(float SampleRate)
    {
        sampleRate = SampleRate;
        frequency = 100.0;
        step = 100.0 / sampleRate;
        modulo = step;
    }
    
    #pragma mark Setters
    // -------------------------------------------------- Setters
    
    void Oscillator::SetSampleRate(float SampleRate)
    {
        sampleRate = SampleRate;
        step = frequency / sampleRate;
    }
    
    void Oscillator::SetPitch(float Pitch)
    {
        frequency = Pitch;
        step = frequency / sampleRate;
    }
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Oscillator::tick()
    {
        modulo += step;
        if(modulo > 1)
            modulo -= 1;
        
        return modulo;
    }
    
    void Oscillator::ModulatePitch(float scale)
    {
        step = (1 + scale) * frequency / sampleRate;
    }
    
}
