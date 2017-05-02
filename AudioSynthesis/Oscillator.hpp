//
//  Oscillator.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

namespace AudioSynthesis
{
    class Oscillator
    {
        using PtrFunc = float (Oscillator::*)();
        
    public:
        // -------------------- Constructors
        Oscillator(float SampleRate);
        
        // -------------------- Accessors
        const float GetSampleRate()const { return sampleRate; }
        const float GetPitch()const { return frequency; }
        const float GetModulo()const { return modulo; }
        const float GetStep()const { return step; }
        const float GetDPWCoeff() const {return DPWCoeff;};
        
        void SetSampleRate(float SampleRate);
        void SetPitch(float Pitch);
        void SetPhase(float Phase);
        void InvertPhase(bool PhaseIsInverted);
        
        // -------------------- Public Methods
        float tick();
        void ModulatePitch(float scale);
        void CalcDPWCoeff();
        
    protected:
        // -------------------- Private Members
        PtrFunc tickPhase;
        float sampleRate;
        float frequency;
        float modulo;
        float step;
        float DPWCoeff;
        bool invertPhase;
        
        // -------------------- Protected Methods
        
    private:
        // -------------------- Private Members
        
        // -------------------- Private Methods
        float tickUp();
        float tickDown();
        
        
    }; // End Oscillator Class

}

#endif /* Oscillator_hpp */
