//
//  Grain.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/15/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Grain.hpp"

namespace AudioSynthesis
{
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    Grain::Grain(WaveFile * & Buffer)
    {
        buffer = Buffer;
        bufferSize = buffer->GetTotalByteSize();
        channelNum = buffer->GetNumChannels();
    }
    

    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Grain::tick()
    {
        if(pos > bufferSize)
        {
            pos = 0;
        }
        
        return buffer->GetSampleFloat(pos++);
    }
    
    
    #pragma mark Accessors
    // -------------------------------------------------- Acsessors
    void Grain::SetGrainSize(int SamplesPerGrain)
    {
        grainSize = SamplesPerGrain;
        offset = pos;
    }
    
    void Grain::SetVelocity(float samplesPerSecond)
    {
        
    }
    
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    

    
} // end AudioSynthesis namespace
