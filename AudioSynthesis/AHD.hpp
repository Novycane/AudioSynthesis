//
//  AHD.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/27/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef AHD_hpp
#define AHD_hpp

#include "Envelope.hpp"
#include "Enumerations.h"

namespace AudioSynthesis
{
    class AHD : public Envelope
    {
    public:
        // -------------------- Constructors
        AHD(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        void reset();
        void start();
        void stop();
        
        // -------------------- Accessors
        const float GetSampleRate() const { return sampleRate; }
        const float GetAttack() const { return attackTime; }
        const float GetAttackShape() const { return attackShape; }
        const float GetDecay() const { return decayTime; }
        const float GetDecayShape() const { return decayShape; }
        const float GetCurentVal() const { return val; }
        
        void SetSampleRate(float SampleRate);
        void SetAttack(float Attack);
        void SetDecay(float Decay);
        void SetAttackShape(float AttackShape);
        void SetDecayShape(float DecayShape);
        
        void SetGate(bool GateOn);
        
        bool IsRunning() { return isRunning; };
        
    private:
        // -------------------- Private Members
        float sampleRate;
        float aStep;
        float dStep;
        float attackTime;
        float attackShape;
        float decayTime;
        float decayShape;
        float val;
        bool isRunning;
        bool gateOn;
        EnvelopeState state;
        
        // -------------------- Private Methods
        
        
    }; // End AHD Class
}


#endif /* AHD_hpp */
