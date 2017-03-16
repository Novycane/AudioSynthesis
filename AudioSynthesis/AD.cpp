//
//  AD.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "AD.hpp"

namespace AudioSynthesis
{
    
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    AD::AD(float SampleRate)
    {
        sampleRate = SampleRate;
        state = idle;
        SetAttack(1.0);
        SetDecay(1.0);
        attackShape = 0.5;
        decayShape = 0.5;
    }
    
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float AD::tick()
    {
        float shape;
        if(state == att)
        {
            shape = attackShape;
            val += aStep;
            
            if(val >= 1)
            {
                state = dec;
                // Need to correct for overshoot
            }
        }
        else if(state == dec)
        {
            shape = decayShape;
            val -= dStep;
            if(val <=0 )
            {
                val = 0;
                state = idle;
                isRunning = false;
            }
        }
        float v2 = val * val;
        return 2 * val * shape - 2 * v2 * shape + v2 ;
    }
    
    
    void AD::reset()
    {
        val = 0;
    }
    
    void AD::start()
    {
        isRunning = true;
        state = att;
    }
    
    void AD::stop()
    {
        isRunning = false;
        state = idle;
    }
    
    void AD::SetSampleRate(float SampleRate)
    {
        sampleRate = SampleRate;
        aStep = 1.0 / (attackTime * sampleRate);
        dStep = 1.0 / (decayTime * sampleRate);
    }
    
    void AD::SetAttack(float Attack)
    {
        attackTime = Attack;
        aStep = 1.0 / (attackTime * sampleRate);
    }
    
    void AD::SetDecay(float Decay)
    {
        decayTime = Decay;
        dStep = 1.0 / (decayTime * sampleRate);
    }
    
    void AD::SetAttackShape(float AttackShape)
    {
        attackShape = AttackShape;
    }
    
    void AD::SetDecayShape(float DecayShape)
    {
        decayShape = DecayShape;
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    
    
}
