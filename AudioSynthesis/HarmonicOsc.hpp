//
//  HarmonicOsc.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/17/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef HarmonicOsc_hpp
#define HarmonicOsc_hpp

#include <functional>

enum HarmonicOscModel {UNDAMPED_RK2, UNDAMPED_RK4, DAMPED_RK2, DAMPED_RK4, DRIVEN_RK2, DRIVEN_RK4,};

namespace AudioSynthesis
{
    class HarmonicOsc
    {
    public:
        // -------------------- Constructors
        HarmonicOsc(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        void Reset();
        void SetModel(HarmonicOscModel Model);
        
        // -------------------- Accessors
        void setFt(float Ft) {ft = Ft;}
        void setX(float X) {x = X;}
        void setV(float V) {v = V;}
        void setK(float K) {k = K;}
        void setM(float M) {m = M;}
        void setC(float C) {c = C;}
        
    private:
        // -------------------- Private Members
        std::function<float()> tickPointer;
        float ft;
        float x;
        float v;
        float k;
        float m;
        float c;
        float sampleRate;
        float step;
        
        // -------------------- Private Methods
        float UndampedRK2();
        float UndampedRK4();
        float DampedRK2();
        float DampedRK4();
        float DrivenRK2();
        float DrivenRK4();
    };
    
} // End AudioSynthesis namespace

#endif /* HarmonicOsc_hpp */
