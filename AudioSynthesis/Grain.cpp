//
//  Grain.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/15/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Grain.hpp"
#include <cmath>

namespace AudioSynthesis
{
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    
    Grain::Grain(float SampleRate)
    {
        positionInGrain = 0;
        grainSize = 0;
        grainStart = 0;
        sampleRate = SampleRate;
        audioBuffer = nullptr;
        //grainWindow.
    }
    
    Grain::~Grain()
    {
        if(audioBuffer != nullptr)
            delete audioBuffer;
    }
    

    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Grain::tick()
    {
        return 0.0;
    }
    
    
    
    #pragma mark Accessors
    // -------------------------------------------------- Acsessors
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    
} // end AudioSynthesis namespace
