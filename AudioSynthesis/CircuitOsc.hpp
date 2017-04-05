//
//  CircuitOsc.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef CircuitOsc_hpp
#define CircuitOsc_hpp

namespace AudioSynthesis
{
    
    enum CircuitOscState {idle, charging, discharging};
    
    class CircuitOsc
    {
    public:
        // -------------------- Constructors
        CircuitOsc(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        void start();
        void stop();
        void reset();
        
        void setFrequency(float frequency);
        
        
    private:
        // -------------------- Private Members
        CircuitOscState state;
        
        float sampleRate;
        float frequency;
        float step;
        
        float vForce;
        float r1, r2, r3;
        float v1, v2;
        float q1, q2;
        float i1, i2;
        float c1, c2;
        float trig1, trig2;
        
        // -------------------- Private Methods
        float SawModel01();
        void InitSawModel01();
        float SawModel02();
        void InitSawModel02();
        
    }; // End CircuitOsc class
    
}

#endif /* CircuitOsc_hpp */
