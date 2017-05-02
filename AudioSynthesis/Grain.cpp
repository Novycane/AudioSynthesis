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
        positionInGrainf =0.0;
        positionInBuffer = 0;
        nextPositionInBuffer = positionInBuffer;
        grainSize = 0;
        playbackSpeed = 1.0;
        grainSpeed = 1.0;
        sampleRate = SampleRate;
        audioBuffer = make_shared<vector<float>>();
        grainWindow.setType(WindowType::HANN, false);
    }

    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    
    // No looping
    /*
    float Grain::tick()
    {
        float temp;
        float ratio;
        
        positionInGrainf += playbackSpeed;
        
        if(positionInGrainf >= grainSize)
        {
            positionInGrainf = grainSize - positionInGrainf;
            if( positionInBuffer == nextPositionInBuffer)
            {
                positionInBuffer += grainSize * grainSpeed;
                nextPositionInBuffer = positionInBuffer;
            }
            else
                positionInBuffer = nextPositionInBuffer;
            
        }
        
        if(positionInGrainf + positionInBuffer >= (int) audioBuffer->size())
        {
            // Loop Frame
            nextPositionInBuffer  = positionInBuffer - (int)audioBuffer->size();
            ratio =  (1.0 - positionInGrainf / grainSize);
            return ((*audioBuffer)[audioBuffer->size() - 1] * grainWindow[positionInGrainf]) * ratio;
        }
        
        ratio = positionInGrainf - (int) positionInGrainf;
        
        temp = ((*audioBuffer)[positionInBuffer + (int)positionInGrainf] * grainWindow[positionInGrainf]) * (1.0 - ratio);
        temp += ((*audioBuffer)[positionInBuffer + (int)positionInGrainf + 1] * grainWindow[positionInGrainf]) * (ratio);
        
        return temp;
    }
    */
    
    
     // Naive Linear Interpolation
    float Grain::tick()
    {
        float temp;
        float ratio;
        
        positionInGrainf += playbackSpeed;
        
        if(positionInGrainf >= grainSize)
        {
            positionInGrainf = grainSize - positionInGrainf;
            positionInBuffer += grainSize * grainSpeed;
        }
        
        if(positionInGrainf + positionInBuffer >= (int) audioBuffer->size())
        {
            // Loop Frame
            positionInBuffer = positionInBuffer - (int)audioBuffer->size();
        }
        
        ratio = positionInGrainf - (int) positionInGrainf;
        
        temp = ((*audioBuffer)[positionInBuffer + (int)positionInGrainf] * grainWindow[positionInGrainf]) * (1.0 - ratio);
        temp += ((*audioBuffer)[positionInBuffer + (int)positionInGrainf + 1] * grainWindow[positionInGrainf]) * (ratio);
        
        return temp;
    }
    
    
    /*
     
    // Original Integer Tick
    float Grain::tick()
    {
        // float temp;
        
        // positionInGrain;
        // grainSize;
        // grainStart;
        
        positionInGrain++;
        
        if(positionInGrain >= grainSize)
        {
            positionInGrain = 0;
            positionInBuffer += grainSize;
        }
        
        if(positionInGrain + positionInBuffer >= (int) audioBuffer->size())
        {
            // Loop Frame
            positionInBuffer = positionInBuffer - (int)audioBuffer->size();
        }
        
        //cout << positionInGrain + positionInBuffer << endl;
        
        float amp = grainWindow[positionInGrain];
        float data = (*audioBuffer)[positionInBuffer + positionInGrain];
        return amp * data;
    }
    */
    
    void Grain::ShiftFrame(int Samples)
    {
        positionInBuffer += Samples;
        if(positionInBuffer >= audioBuffer->size())
            positionInBuffer = (int)audioBuffer->size() - grainSize;
    }
    
    void Grain::makeSin()
    {
        audioBuffer->clear();
        audioBuffer->resize(1024);
        for(int i=0; i<1024; i++)
        {
            (*audioBuffer)[i] = sin(20.0 * (float)i * M_PI * 2.0 / 1024);
        }
    }
    
    
    #pragma mark Accessors
    // -------------------------------------------------- Acsessors
    void Grain::SetGrainSize(int SamplesPerGrain)
    {
        if(SamplesPerGrain > audioBuffer->size())
            SamplesPerGrain = (int)audioBuffer->size();
        grainSize = SamplesPerGrain;
        grainWindow.setSize(grainSize);
    }
    
    void Grain::SetGrainDuration(float GrainDuration)
    {
        int samples = sampleRate / GrainDuration;
        grainSize = samples;
        grainWindow.setSize(samples);
    }
    
    void Grain::SetGrainPhaseInPercent(float Phase)
    {
        if(Phase < 0)
            positionInGrain = 0;
        else if(Phase > 1.0)
            positionInGrain = grainSize;
        else
            positionInGrain = Phase * grainSize;
        
        positionInGrainf = (float)positionInGrain;
    }
    
    void Grain::SetGrainPhaseInSamples(int Phase)
    {
        if(Phase < 0)
            positionInGrain = 0;
        else if(Phase > grainSize)
            positionInGrain = grainSize;
        else
            positionInGrain = Phase;
        positionInGrainf = (float)positionInGrain;
    }
    
    void Grain::SetGrainPositionInPercent(float Position)
    {
        if(Position < 0)
             positionInBuffer = 0;
        else if(Position > 1.0)
            positionInBuffer = (int)audioBuffer->size();
        else
            positionInBuffer = Position * audioBuffer->size();
    }
    
    void Grain::SetGrainPositionInSamples(int Position)
    {
        if(Position < 0)
            positionInBuffer = 0;
        else if(Position >= audioBuffer->size())
            positionInBuffer = (int)audioBuffer->size();
        else
            positionInBuffer = Position;
    }
    
    void Grain::AssignBuffer(shared_ptr<vector<float>> & Buffer)
    {
        audioBuffer = Buffer;
    }
    
    void Grain::SetPlaybackRate(float RelativePitch)
    {
        if(RelativePitch < 0.5)
            playbackSpeed = 0.5;
        else if(RelativePitch > 2.0)
            playbackSpeed = 2.0;
        else
            playbackSpeed = RelativePitch;
    }
    
    void Grain::SetGrainSpeed(float GrainSpeed)
    {
        if(GrainSpeed < 0.5)
            grainSpeed = 0.5;
        else if(GrainSpeed > 2.0)
            grainSpeed = 2.0;
        else
            grainSpeed = GrainSpeed;
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    
} // end AudioSynthesis namespace
