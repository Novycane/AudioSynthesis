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
#include "Window.hpp"

namespace AudioSynthesis
{
    class Grain
    {
    public:
        // -------------------- Constructors
        Grain(WaveFile * & Buffer);
        ~Grain();
        
        // -------------------- Accessors
        void SetGrainSize(int SamplesPerGrain);
        void SetGrainVelocity(float FramesPerSecond);
        void SetGrainCount(int NummberOfGrains);
        void SetSampleVelocity(int SampleVelocity);
        void SetStart(float Position);
        void SetOverlap(int Overlap);
        
        void SetWindow(WindowType type);
        
        const int GetGrainSize() const { return grainSize; }
        const float GetGrainVelocity() const { return grainVelocity; }
        const int GetGrainCount() const { return numGrains; }
        const int GetSampleVelocity() const { return inc; }
        const int GetOverlap() const { return overlap; }
        
        // -------------------- Public Methods
        float tick();
        
        
    private:
        // -------------------- Private Members
        int grainSize;
        int numGrains;
        int frame;
        int pos;
        int prevOverlap, nextOverlap;
        int inc;
        int offset;
        int overlap;
        int count;
        
        int bufferSize;
        int channelNum;
        int sampleRate;
        int sampleSize;
        
        float grainVelocity;
        float sample;
        vector<float> edgeBuffer;
        WaveFile* buffer;
        Window* FrameWindow;
        WindowType windowType;
        
        
        // -------------------- Private Methods
        void ShiftFrame();
        inline float SmallOverlap();
        inline float FullOverlap();
        
    }; // End Grain class
} // End AudioSynthesis

#endif /* Grain_hpp */
