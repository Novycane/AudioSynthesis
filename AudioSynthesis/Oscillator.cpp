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
        InvertPhase(false);
        DPWCoeff = 1.0;
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
    
    void Oscillator::SetPhase(float Phase)
    {
        //
        // Need to Reduce Aliasing on this...
        // See if the Phase - module > somevalue
        // if so, blep it....
        //
        if(Phase > 1.0)
            modulo = 1.0;
        else if(Phase < 0.0)
            modulo = 0.0;
        else
            modulo = Phase;
    }
    
    void Oscillator::InvertPhase(bool PhaseIsInverted)
    {
        invertPhase = PhaseIsInverted;
        
        if(!invertPhase)
            tickPhase = &Oscillator::tickUp;
        else
            tickPhase = &Oscillator::tickDown;
            
    }
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Oscillator::tick()
    {
        return (this->*tickPhase)();
    }
    
    void Oscillator::ModulatePitch(float scale)
    {
        step = (1 + scale) * frequency / sampleRate;
    }
    
    void Oscillator::CalcDPWCoeff()
    {
        DPWCoeff = sampleRate / (4.0 * frequency * (1.0 - frequency / sampleRate));
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    float Oscillator::tickUp()
    {
        modulo += step;
        if(modulo > 1.0)
            modulo -= 1.0;
        return modulo;
    }
    
    float Oscillator::tickDown()
    {
        modulo -= step;
        if(modulo < 0.0)
            modulo += 1.0;
        return modulo;
    }
}
