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
        Grain(float SampleRate);
        ~Grain();
        
        // -------------------- Accessors
        void SetGrainSize(int SamplesPerGrain);
        void SetGrainDuration(float GrainDuration);
        
        
        // -------------------- Public Methods
        
        float tick();
        
        
    private:
        // -------------------- Private Members
        int positionInGrain;
        int grainSize;
        int grainStart;
        
        float sampleRate;
        
        vector<float>* audioBuffer;
        Window grainWindow;
        
        // -------------------- Private Methods
        
    }; // End Grain class
} // End AudioSynthesis

#endif /* Grain_hpp */
