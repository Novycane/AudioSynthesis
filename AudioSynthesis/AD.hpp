//
//  AD.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef AD_hpp
#define AD_hpp

#include "Envelope.hpp"

enum ADState {idle, att, dec};

namespace AudioSynthesis
{
    class AD : public Envelope
    {
    public:
        // -------------------- Constructors
        AD(float SampleRate);
        
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
        ADState state;
        
        // -------------------- Private Methods
        
        
    }; // End AD Class

}


#endif /* AD_hpp */
