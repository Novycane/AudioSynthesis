//
//  NaiveFilter.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/8/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef NaiveFilter_hpp
#define NaiveFilter_hpp


namespace AudioSynthesis
{
    
    class NaiveFilter
    {
    public:
        // -------------------- Constructors
        NaiveFilter(float Cutoff, float SampleRate);
        
        // -------------------- Public Methods
        float tickLP(float x);
        float tickHP(float x);
        float tickBP(float x);
        
        // -------------------- Accessors
        const float GetSampleRate() const {return sampleRate;}
        const float GetCutoff() const {return cutoff;}
        const float GetResonance() const {return resonance;}
        const float GetSpread() const {return poleSpread;}
        
        void SetSampleRate(float SampleRate);
        void SetCutoff(float Cutoff);
        void SetResonance(float Resonance);
        void SetSpread(float PoleSpread);
        
    private:
        // -------------------- Private Members
        float hp;
        float lp;
        float sampleRate;
        float cutoff;
        float resonance;
        float poleSpread;
        float w;
        
        // -------------------- Private Methods
        void update(float x);
        
        
    }; // End NaiveFilter class
    
} // End AudioSynthesis Namespace

#endif /* NaiveFilter_hpp */
