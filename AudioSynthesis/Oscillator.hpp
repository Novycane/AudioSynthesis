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
    public:
        // -------------------- Constructors
        Oscillator(float SampleRate);
        
        // -------------------- Accessors
        const float GetSampleRate()const { return sampleRate; }
        const float GetPitch()const { return frequency; }
        const float GetModulo()const { return modulo; }
        const float GetStep()const { return step; }
        
        void SetSampleRate(float SampleRate);
        void SetPitch(float Pitch);
        
        // -------------------- Public Methods
        float tick();
        void ModulatePitch(float scale);
        
    protected:
        // -------------------- Private Members
        float sampleRate;
        float frequency;
        float modulo;
        float step;
        // -------------------- Protected Methods
        
    private:
        // -------------------- Private Members
        
        // -------------------- Private Methods
        
    }; // End Oscillator Class

}

#endif /* Oscillator_hpp */
