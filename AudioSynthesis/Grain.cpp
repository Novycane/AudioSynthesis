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
    Grain::Grain(WaveFile * & Buffer)
    {
        buffer = Buffer;
        bufferSize = buffer->GetTotalByteSize() * 8 / Buffer->GetSampleSize();
        channelNum = buffer->GetNumChannels();
        sampleRate = Buffer->GetSampleRate();
        grainVelocity = sampleRate;
        SetGrainSize(512);
        frame = 0;
        inc = 1;
    }
    

    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Grain::tick()
    {
        float temp;
        
        if(pos == grainSize - 2 || pos < 2)
        {
            
            temp = sample;
            sample = buffer->GetSampleFloat(frame + pos) ;// * window[pos];
            temp = (temp + sample) / 2;
        }
        else
        {
            temp = buffer->GetSampleFloat(frame + pos) ;// * window[pos];
            sample = temp;
        }
        
        if(frame + pos > bufferSize)
            frame = frame;
        
        
        
        pos+= inc;
        
        if(pos > grainSize - 1 || pos < 0)
        {
            pos = 0;
            frame += grainSize * grainVelocity;
            ShiftFrame();
        }
        else if(frame + pos >= bufferSize ||  frame + pos < 0)
        {
            ShiftFrame();
        }
        
        
        
        
        return temp;
    }
    
    
    #pragma mark Accessors
    // -------------------------------------------------- Acsessors
    void Grain::SetGrainSize(int FramesPerSecond)
    {
        grainSize = FramesPerSecond;
        offset = pos;
        window.resize(FramesPerSecond);
        for(int i=0; i<FramesPerSecond; i++)
        {
            float I = (float)i;
            float mid = FramesPerSecond / 2.0;
            float temp = (((I - mid) / mid) * ((I - mid) / mid)) * -1.0 + 1.0; // Quadratic
            //float temp = tanh((((I - mid) / mid) * ((I - mid) / mid)) * -1.0 + 1.0); // Quadratic + tanh
            window[i] = temp;
        }
    }
    
    void Grain::SetGrainVelocity(float samplesPerSecond)
    {
        grainVelocity = samplesPerSecond;
    }
    
    void Grain::SetGrainCount(int NumberOfGrains)
    {
        numGrains = NumberOfGrains;
    }
    
    void Grain::SetSampleVelocity(int SampleVelocity)
    {
        inc = SampleVelocity;
    }
    
    void Grain::SetStart(float Position)
    {
        frame = (int) (Position * buffer->GetTotalSampleSize());
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    void Grain::ShiftFrame()
    {
        if(frame + pos >= bufferSize)
        {
            frame -= bufferSize;
        }
        else if(frame + pos <= 0)
        {
            frame += bufferSize;
        }
        
    }

    
} // end AudioSynthesis namespace
