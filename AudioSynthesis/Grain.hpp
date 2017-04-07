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
        Grain();
        ~Grain();
        
        // -------------------- Accessors
        void SetGrainSize(int SamplesPerGrain);
        void SetGrainVelocity(float FramesPerSecond);
        void SetSampleVelocity(int SampleVelocity);
        void SetStart(float Position);
        void SetPosition(int Position);
        void SetWindow(WindowType type);
        void AssignBuffer(vector<float>* & AudioBuffer);
        
        const int GetGrainSize() const { return grainSize; }
        const float GetGrainVelocity() const { return grainVelocity; }
        const int GetSampleVelocity() const { return inc; }
        
        // -------------------- Public Methods
        float tick();
        
        
    private:
        // -------------------- Private Members
        int grainSize;
        int frame;
        int pos;
        int inc;
        //int offset;
        int count;
        
        int bufferSize;
        int channelNum;
        int sampleRate;
        int sampleSize;
        
        float grainVelocity;
        float sample;
        vector<float>* buffer;
        Window* FrameWindow;
        WindowType windowType;
        
        
        // -------------------- Private Methods
        void ShiftFrame();
        inline float SmallOverlap();
        inline float FullOverlap();
        
    }; // End Grain class
} // End AudioSynthesis

#endif /* Grain_hpp */
