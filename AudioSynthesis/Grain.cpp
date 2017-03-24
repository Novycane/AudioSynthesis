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
        overlap = 0;
        
        inc = 1;
        FrameWindow = nullptr;
    }
    
    Grain::~Grain()
    {
        if(FrameWindow != nullptr)
            delete FrameWindow;
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
        offset = pos;
        if(FrameWindow != nullptr)
        {
            SetWindow(windowType);
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
    
    void Grain::SetWindow(WindowType type)
    {
        windowType = type;
        if(FrameWindow != nullptr)
            delete FrameWindow;
        FrameWindow = new Window(type, 2 * overlap);
    }
    
    void Grain::SetOverlap(int Overlap)
    {
        overlap = Overlap;
        edgeBuffer.resize(2 * overlap);
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
        
        temp = buffer->GetSampleFloat(frame + pos);
        if(FrameWindow != nullptr)
        {
            factor = (*FrameWindow)[pos];
            sample = temp * factor;
        }
        else
        {
            temp = buffer->GetSampleFloat(frame + pos);
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
        if(pos < overlap)
        {
            temp = buffer->GetSampleFloat(frame + pos);
            if(FrameWindow != nullptr)
            {
                factor = (*FrameWindow)[pos];
                sample = temp * factor + edgeBuffer[pos + overlap / 2] * (1.0 - factor);
                edgeBuffer[pos + overlap / 2] = temp;
            }
        }
        else if(pos >= grainSize - overlap )
        {
            temp = buffer->GetSampleFloat(frame + pos);
            if(FrameWindow != nullptr)
            {
                factor = (*FrameWindow)[grainSize - pos - 1];
                sample = temp * factor + edgeBuffer[grainSize - pos - 1] * (1.0 - factor);
                edgeBuffer[grainSize - pos - 1] = temp;
            }
        }
        else
        {
            temp = buffer->GetSampleFloat(frame + pos);
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
