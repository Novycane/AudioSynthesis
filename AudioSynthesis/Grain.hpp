//
//  Grain.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/15/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Grain_hpp
#define Grain_hpp

#include "WaveFile.hpp"

namespace AudioSynthesis
{
    class Grain
    {
    public:
        // -------------------- Constructors
        Grain(WaveFile * & Buffer);
        
        // -------------------- Accessors
        void SetGrainSize(int SamplesPerGrain);
        void SetVelocity(float samplesPerSecond);
        
        const int GetGrainSize() const { return grainSize; }
        const float GetVelocity() const { return velocity; }
        
        // -------------------- Public Methods
        float tick();
        
        
    private:
        // -------------------- Private Members
        int grainSize;
        int pos;
        int offset;
        
        int bufferSize;
        int channelNum;
        
        float velocity;
        WaveFile* buffer;
        
        
        // -------------------- Private Methods
        
        
    }; // End Grain class
} // End AudioSynthesis

#endif /* Grain_hpp */
