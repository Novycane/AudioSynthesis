//
//  CircuitOsc.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "CircuitOsc.hpp"
#include <cmath>

namespace AudioSynthesis
{
    
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    CircuitOsc::CircuitOsc(float SampleRate)
    {
        sampleRate = SampleRate;
        frequency = 440.0;
        
        InitSawModel02();
    }
    
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float CircuitOsc::tick()
    {
        return SawModel02();
    }
    
    void CircuitOsc::start()
    {
        state = charging;
    }
    
    void CircuitOsc::stop()
    {
        state = idle;
    }
    
    void CircuitOsc::reset()
    {
        v1 = 0;
        v2 = 0;
        q1 = 0;
        q2 = 0;
        i1 = 0;
        i2 = 0;
        c1 = 1.0;
        c2 = 1.0;
        trig1 = 0.9;
        trig2 = -0.9;
    }
    
    void CircuitOsc::setFrequency(float frequency)
    {
        vForce = frequency;
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    void CircuitOsc::InitSawModel01()
    {
        vForce = 100.0;
        v1 = 0;
        v2 = 0;
        q1 = 0;
        q2 = 0;
        i1 = 100.0;
        i2 = 500.0;
        c1 = 1.0;
        c2 = c1 * 500.0;
        trig1 = 0.5;
        trig2 = -0.25;
        step = 1.0 / sampleRate;
        r1 = 0.1;
        r2 = 0.01;
        r3 = 0.10;
    }
    
    float CircuitOsc::SawModel01()
    {
        if(state == charging)
        {
            if(v2 > trig1)
                state = discharging;
            q1 += (vForce - v1) / r1 * step;
            v1 = q1 * c1;
            q2 += step * (v1 - v2) / r3;
            v2 = q2 * c2;
            
        }
        else if(state == discharging)
        {
            if(v2 < trig2)
                state = charging;
            q1 += (v1 - vForce) / r2 * step;
            v1 = q1 * c1;
            q2 += step * (v1 - v2) / r3;
            v2 = q2 * c2;
        }
        
        return tanh(v2);
    }
    
    void CircuitOsc::InitSawModel02()
    {
        vForce = 100.0;
        v1 = 0;
        v2 = 0;
        q1 = 0;
        q2 = 0;
        i1 = 100.0;
        i2 = 500.0;
        c1 = 1.0;
        c2 = c1 * 500.0;
        trig1 = 0.5;
        trig2 = -0.25;
        step = 1.0 / sampleRate;
        r1 = 0.1;
        r2 = 0.01;
        r3 = 0.10;
    }
    
    float CircuitOsc::SawModel02()
    {
        if(state == charging)
        {
            if(v2 > trig1)
                state = discharging;
            q1 += (vForce - v1) / r1 * step;
            v1 = q1 * c1;
            q2 += step * (v1 - v2) / r3;
            v2 = q2 * c2;
            
        }
        else if(state == discharging)
        {
            if(v2 < trig2)
                state = charging;
            q1 += (v1 - vForce) / r2 * step;
            v1 = q1 * c1;
            q2 += step * (v1 - v2) / r3;
            v2 = q2 * c2;
        }
        
        return tanh(v2);
    }
}
