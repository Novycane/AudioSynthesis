//
//  OneRC.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/14/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "OneRC.hpp"

namespace AudioSynthesis
{
    // ---------------------------------------- Constructors
    OneRC::OneRC()
    {
        V0 = 0.0;
        V1 = 0.0;
    }
    
    OneRC::OneRC(float R, float C)
    {
        SetResonance(R);
        SetCutoff(C);
    }
    
    // ---------------------------------------- Accessors
    
    void OneRC::SetCutoff(float Cutoff)
    {
        c = pow(0.5, (128 - Cutoff) / 16.0);
    }
    
    void OneRC::SetResonance(float Resonance)
    {
        r = pow(0.5, (Resonance + 24.0) / 16.0);
    }
    
    // ---------------------------------------- Public Methods
    
    float OneRC::update(float input)
    {
        V0 = (1.0 - r * c) * V0  -  c * V1  + c * input;
        V1 = (1 - r * c) * V1  + c * V0;
        
        return V1;
    }
}
