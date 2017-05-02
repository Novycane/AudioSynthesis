//
//  AHD.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/27/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "AHD.hpp"

namespace AudioSynthesis
{
    
#pragma mark Constructors
    // -------------------------------------------------- Constructors
    AHD::AHD(float SampleRate)
    {
        sampleRate = SampleRate;
        state = EnvelopeState::IDLE;
        SetAttack(1.0);
        SetDecay(1.0);
        attackShape = 0.5;
        decayShape = 0.5;
    }
    
    
#pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float AHD::tick()
    {
        float shape = attackShape;
        if(state == EnvelopeState::ATTACK)
        {
            shape = attackShape;
            val += aStep;
            
            if(val >= 1)
            {
                state = EnvelopeState::HOLD;
                // Need to correct for overshoot
            }
        }
        else if (state == EnvelopeState::HOLD)
        {
            if(!gateOn)
                state = EnvelopeState::DECAY;
            return 1.0;
        }
        else if(state == EnvelopeState::DECAY)
        {
            shape = decayShape;
            val -= dStep;
            if(val <=0 )
            {
                val = 0;
                state = EnvelopeState::IDLE;
                isRunning = false;
            }
        }
        float v2 = val * val;
        return 2 * val * shape - 2 * v2 * shape + v2 ;
    }
    
    
    void AHD::reset()
    {
        val = 0;
    }
    
    void AHD::start()
    {
        isRunning = true;
        state = EnvelopeState::ATTACK;
    }
    
    void AHD::stop()
    {
        isRunning = false;
        state = EnvelopeState::IDLE;
    }
    
    void AHD::SetSampleRate(float SampleRate)
    {
        sampleRate = SampleRate;
        aStep = 1.0 / (attackTime * sampleRate);
        dStep = 1.0 / (decayTime * sampleRate);
    }
    
    void AHD::SetAttack(float Attack)
    {
        attackTime = Attack;
        aStep = 1.0 / (attackTime * sampleRate);
    }
    
    void AHD::SetDecay(float Decay)
    {
        decayTime = Decay;
        dStep = 1.0 / (decayTime * sampleRate);
    }
    
    void AHD::SetAttackShape(float AttackShape)
    {
        attackShape = AttackShape;
    }
    
    void AHD::SetDecayShape(float DecayShape)
    {
        decayShape = DecayShape;
    }
    
    void AHD::SetGate(bool GateOn)
    {
        gateOn = GateOn;
    }
    
#pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    
    
}
