//
//  ADSR.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/19/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef ADSR_hpp
#define ADSR_hpp

#include "Envelope.hpp"
#include "Enumerations.h"

namespace AudioSynthesis
{
    class ADSR : public Envelope
    {
    public:
        // -------------------- Constructors
        ADSR(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        void Reset();
        void Start();
        void Stop();
        void GateOn();
        void GateOff();
        
        // -------------------- Accessors
        const float GetSampleRate() const { return sampleRate; }
        const float GetAttack() const { return attackTime; }
        const float GetAttackShape() const { return attackShape; }
        const float GetDecay() const { return decayTime; }
        const float GetDecayShape() const { return decayShape; }
        const float GetSustain() const { return attackTime; }
        const float GetRelease() const { return decayTime; }
        const float GetReleaseShape() const { return decayShape; }
        const float GetCurentVal() const { return val; }
        
        void SetSampleRate(float SampleRate);
        void SetAttack(float Attack);
        void SetDecay(float Decay);
        void SetSustain(float Sustain);
        void SetRelease(float Release);
        
        void SetAttackShape(float AttackShape);
        void SetDecayShape(float DecayShape);
        void SetReleaseShape(float ReleaseShape);
        
        bool IsRunning() { return isRunning; };
        
    private:
        // -------------------- Private Members
        float sampleRate;
        float aStep;
        float dStep;
        float rStep;
        float attackTime;
        float attackShape;
        float decayTime;
        float decayShape;
        float sustainLevel;
        float releaseTime;
        float releaseShape;
        float val;
        bool isRunning;
        bool gateOn;
        EnvelopeState state;
        
        // -------------------- Private Methods
        
        
    }; // End AD Class
}

#endif /* ADSR_hpp */
