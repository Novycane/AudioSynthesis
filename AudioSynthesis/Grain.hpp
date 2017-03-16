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
#include <vector>

namespace AudioSynthesis
{
    class Grain
    {
    public:
        // -------------------- Constructors
        Grain(WaveFile * & Buffer);
        
        // -------------------- Accessors
        void SetGrainSize(int SamplesPerGrain);
        void SetGrainVelocity(float FramesPerSecond);
        void SetGrainCount(int NummberOfGrains);
        void SetSampleVelocity(int SampleVelocity);
        void SetStart(float Position);
        
        const int GetGrainSize() const { return grainSize; }
        const float GetGrainVelocity() const { return grainVelocity; }
        const int GetGrainCount() const { return numGrains; }
        const int GetSampleVelocity() const { return inc; }
        
        // -------------------- Public Methods
        float tick();
        
        
    private:
        // -------------------- Private Members
        int grainSize;
        int numGrains;
        int frame1, frame2;
        int pos;
        int inc;
        int offset;
        int count;
        
        int bufferSize;
        int channelNum;
        int sampleRate;
        int sampleSize;
        
        float grainVelocity;
        vector<float> window;
        WaveFile* buffer;
        
        
        // -------------------- Private Methods
        
        
    }; // End Grain class
} // End AudioSynthesis

#endif /* Grain_hpp */
