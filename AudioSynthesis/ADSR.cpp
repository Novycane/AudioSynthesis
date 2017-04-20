//
//  ADSR.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/19/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "ADSR.hpp"

namespace AudioSynthesis
{
    
#pragma mark Constructors
    // -------------------------------------------------- Constructors
    ADSR::ADSR(float SampleRate)
    {
        sampleRate = SampleRate;
        state = EnvelopeState::IDLE;
        isRunning = false;
        gateOn = false;
        
        SetAttack(1.0);
        SetDecay(1.0);
        SetSustain(0.5);
        SetRelease(0.25);
        
        SetAttackShape(0.5);
        SetDecayShape(0.5);
        SetReleaseShape(0.5);
    }
    
    
#pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float ADSR::tick()
    {
        float shape = attackShape;
        if(gateOn)
        {
            if(state == EnvelopeState::ATTACK)
            {
                shape = attackShape;
                val += aStep;
                
                if(val >= 1)
                {
                    state = EnvelopeState::DECAY;
                    shape = decayShape;
                    return 1.0;
                    // Need to correct for overshoot
                }
            }
            else if(state == EnvelopeState::DECAY)
            {
                shape = decayShape;
                val -= dStep;
                if(val <= sustainLevel )
                {
                    val = sustainLevel;
                    state = EnvelopeState::SUSTAIN;
                    return val;
                }
            }
            else if(state == EnvelopeState::SUSTAIN)
                return sustainLevel;
            
            float v2 = val * val;
            return 2 * val * shape - 2 * v2 * shape + v2 ;
        }
        else
        {
            if (state == EnvelopeState::RELEASE)
            {
                shape = releaseShape;
                val -= rStep;
                if(val <= 0 )
                {
                    val = 0;
                    state = EnvelopeState::IDLE;
                    isRunning = false;
                }
                float v2 = val * val;
                return 2 * val * shape - 2 * v2 * shape + v2 ;
            }
        }
        return 0.0;
    }
    
    
    void ADSR::Reset()
    {
        val = 0;
    }
    
    void ADSR::Start()
    {
        isRunning = true;
        state = EnvelopeState::ATTACK;
    }
    
    void ADSR::Stop()
    {
        isRunning = false;
        state = EnvelopeState::IDLE;
    }
    
    void ADSR::GateOn()
    {
        gateOn = true;
        state = EnvelopeState::ATTACK;
    }
    
    void ADSR::GateOff()
    {
        gateOn = false;
        state = EnvelopeState::RELEASE;
    }
    
#pragma mark Accessors
    // -------------------------------------------------- Accessors

    
    void ADSR::SetSampleRate(float SampleRate)
    {
        sampleRate = SampleRate;
        aStep = 1.0 / (attackTime * sampleRate);
        dStep = 1.0 / (decayTime * sampleRate);
    }
    
    void ADSR::SetAttack(float Attack)
    {
        attackTime = Attack;
        aStep = 1.0 / (attackTime * sampleRate);
    }
    
    void ADSR::SetDecay(float Decay)
    {
        decayTime = Decay;
        dStep = 1.0 / (decayTime * sampleRate);
    }
    
    void ADSR::SetSustain(float Sustain)
    {
        sustainLevel = Sustain;
    }
    
    void ADSR::SetRelease(float Release)
    {
        releaseTime = Release;
        rStep = 1.0 / (releaseTime * sampleRate);
    }
    
    void ADSR::SetAttackShape(float AttackShape)
    {
        attackShape = AttackShape;
    }
    
    void ADSR::SetDecayShape(float DecayShape)
    {
        decayShape = DecayShape;
    }
    
    void ADSR::SetReleaseShape(float ReleaseShape)
    {
        releaseShape = ReleaseShape;
    }
    
#pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    
    
}
