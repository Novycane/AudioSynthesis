//
//  Grain.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/15/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Grain_hpp
#define Grain_hpp

#include <vector>
#include <memory>
#include "Window.hpp"

namespace AudioSynthesis
{
    class Grain
    {
    public:
        // -------------------- Constructors
        Grain(float SampleRate);
        
        // -------------------- Accessors
        void SetGrainSize(int SamplesPerGrain);
        void SetGrainDuration(float GrainDuration);
        void SetGrainPhaseInPercent(float Phase);
        void SetGrainPhaseInSamples(int Phase);
        void SetGrainPositionInPercent(float Position);
        void SetGrainPositionInSamples(int Position);
        void SetPlaybackRate(float RelativePitch);
        void SetGrainSpeed(float GrainSpeed);
        
        void AssignBuffer(shared_ptr<vector<float>> & Buffer);
        
        // -------------------- Public Methods
        float tick();
        
        void ShiftFrame(int Samples);
        
        void makeSin();
        
    private:
        // -------------------- Private Members
        int positionInGrain;
        int positionInBuffer;
        int nextPositionInBuffer;
        int grainSize;
        
        float positionInGrainf;
        float playbackSpeed;
        float grainSpeed;
        float sampleRate;
        
        //vector<float>* audioBuffer;
        std::shared_ptr<vector<float>> audioBuffer;
        
        Window grainWindow;
        
        // -------------------- Private Methods
        
    }; // End Grain class
} // End AudioSynthesis

#endif /* Grain_hpp */
