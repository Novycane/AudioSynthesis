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
        FrameWindow = nullptr;
        Buffer->CreateVector(*buffer, 1);
        bufferSize = Buffer->GetTotalByteSize() * 8 / Buffer->GetSampleSize();
        channelNum = Buffer->GetNumChannels();
        sampleRate = Buffer->GetSampleRate();
        grainVelocity = sampleRate;
        SetGrainSize(512);
        frame = 0;
    
        inc = 1;
    }
    
    Grain::Grain()
    {
        FrameWindow = nullptr;
        buffer = nullptr;
        
        bufferSize = 0;
        channelNum = 0;
        sampleRate = 0;
        grainVelocity = 1.0;
        SetGrainSize(512);
        frame = 0;
        
        inc = 1;

    }
    
    Grain::~Grain()
    {
        if(FrameWindow != nullptr)
            delete FrameWindow;
        
        if(buffer != nullptr)
            delete buffer;
    }
    

    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Grain::tick()
    {
        return FullOverlap();
    }
    
    /*
    float Grain::tick()
    {
        float temp;
        /*
         if(pos == grainSize - 2 || pos < 2)
         {
         cout << (*FrameWindow)[pos] << endl;
         temp = sample;
         sample = buffer->GetSampleFloat(frame + pos);
         if(FrameWindow != nullptr)
         sample *= (*FrameWindow)[pos];
         temp = (temp + sample) / 2;
         }
         else
         {
         }
         
        
        temp = buffer->GetSampleFloat(frame + pos);
        if(FrameWindow != nullptr)
            temp *= (*FrameWindow)[pos];
        sample = temp;
        
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
    */
    
    
    #pragma mark Accessors
    // -------------------------------------------------- Acsessors
    void Grain::SetGrainSize(int FramesPerSecond)
    {
        grainSize = FramesPerSecond;
        if(FrameWindow != nullptr)
        {
            SetWindow(windowType);
        }
    }
    
    void Grain::SetGrainVelocity(float samplesPerSecond)
    {
        grainVelocity = samplesPerSecond;
    }
        
    void Grain::SetSampleVelocity(int SampleVelocity)
    {
        inc = SampleVelocity;
    }
    
    void Grain::SetStart(float Position)
    {
        frame = (int) (Position * buffer->size());
    }
    
    void Grain::SetWindow(WindowType type)
    {
        windowType = type;
        if(FrameWindow != nullptr)
            delete FrameWindow;
        FrameWindow = new Window(type, grainSize);
    }
    
    void Grain::AssignBuffer(vector<float>* & AudioBuffer)
    {
        bufferSize = AudioBuffer->size();
        buffer = AudioBuffer;
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
    
    inline float Grain::FullOverlap()
    {
        float temp;
        float factor;
        
        temp = (*buffer)[frame + pos];
        if(FrameWindow != nullptr)
        {
            factor = (*FrameWindow)[pos];
            sample = temp * factor;
        }
        else
        {
            temp = (*buffer)[frame + pos];
            sample = temp;
        }
        
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
        
        return sample;
    }
    
    inline float Grain::SmallOverlap()
    {
        float temp;
        float factor;
        if(pos < 0)
        {
            temp = (*buffer)[frame + pos];
            if(FrameWindow != nullptr)
            {
                factor = (*FrameWindow)[pos];
                sample = temp * factor;
           }
        }
        else if(pos >= grainSize)
        {
            temp = (*buffer)[frame + pos];
            if(FrameWindow != nullptr)
            {
                factor = (*FrameWindow)[grainSize - pos - 1];
                sample = temp * factor;
            }
        }
        else
        {
            temp = (*buffer)[frame + pos];
            sample = temp;
        }
        
        // Delete
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
        
        return sample;
    }
} // end AudioSynthesis namespace
