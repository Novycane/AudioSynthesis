//
//  HarmonicOsc.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/17/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "HarmonicOsc.hpp"

namespace AudioSynthesis
{
    
#pragma mark Constructors
    // -------------------------------------------------- Constructors
    HarmonicOsc::HarmonicOsc(float SampleRate)
    {
        sampleRate = SampleRate;
        step = 1.0 / SampleRate;
        k = 10000.0;
        m = 1.0;
        c = 10000.0 * k;
        x = 0.0;
        v = 1.0;
        ft = 0.0;
        tickPointer = std::bind(&HarmonicOsc::DrivenRK2, this);
    }
    
    
    
#pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float HarmonicOsc::tick()
    {
        return DrivenRK2();
        //return tickPointer();
    }
    
    void HarmonicOsc::Reset()
    {
        x = 0.0;
        v = 0.0;
    }
    
    void HarmonicOsc::SetModel(HarmonicOscModel Model)
    {
        switch(Model)
        {
            case DAMPED_RK2:
                tickPointer = std::bind(&HarmonicOsc::DampedRK2, this);
                break;
            case DAMPED_RK4:
                tickPointer = std::bind(&HarmonicOsc::DampedRK4, this);
                break;
            case UNDAMPED_RK2:
                tickPointer = std::bind(&HarmonicOsc::UndampedRK2, this);
                break;
            case UNDAMPED_RK4:
                tickPointer = std::bind(&HarmonicOsc::UndampedRK4, this);
                break;
            case DRIVEN_RK2:
                tickPointer = std::bind(&HarmonicOsc::DrivenRK2, this);
                break;
            case DRIVEN_RK4:
                tickPointer = std::bind(&HarmonicOsc::DrivenRK4, this);
                break;
            default:
                tickPointer = std::bind(&HarmonicOsc::DrivenRK2, this);
                break;
        }
    }
    
    
#pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    float HarmonicOsc::UndampedRK2()
    {
        float kx1, kx2;
        float kv1, kv2;
        
        kv1 = v * step;
        kx1 = (-k / m * x) * step;

        kv2 = (v + kv1 / 2.0) * step;
        kx2 = (-k / m * (x + kx1 / 2.0)) * step;
        
        x = x + kv2;
        v = v + kx2;
        
        return x;
    }
    
    float HarmonicOsc::UndampedRK4()
    {
        float kx1, kx2, kx3, kx4;
        float kv1, kv2, kv3, kv4;
        
        kv1 = v * step;
        kx1 = (-k / m * x) * step;
        
        kv2 = (v + kv1 / 2.0) * step;
        kx2 = (-k / m * (x + kx1 / 2.0)) * step;

        kv3 = (v + kv2 / 2.0) * step;
        kx3 = (-k / m * (x + kx2 / 2.0)) * step;

        kv4 = (v + kv3) * step;
        kx4 = (-k / m * (x + kx3)) * step;

        
        x = x + (kv1 + kv4) / 6.0 + (kv2 + kv3) / 3.0 ;
        v = v + (kx1 + kx4) / 6.0 + (kx2 + kx3) / 3.0 ;
        
        return x;
    }
    
    float HarmonicOsc::DampedRK2()
    {
        float kx1, kx2;
        float kv1, kv2;
        
        kv1 = v * step;
        kx1 = ((-k / m) * (x) - (c / m) * (v)) * step;
        
        kv2 = (v + kv1 / 2.0) * step;
        kx2 = ((-k / m) * (x + kx1) - (c / m) * (v + kv1)) * step;
        
        x = x + kv2;
        v = v + kx2;
        
        return x;
    }
    
    float HarmonicOsc::DampedRK4()
    {
        float kx1, kx2, kx3, kx4;
        float kv1, kv2, kv3, kv4;
        
        kv1 = v * step;
        kx1 = ((-k / m) * (x) - (c / m) * (v)) * step;
        
        kv2 = (v + kv1 / 2.0) * step;
        kx2 = ((-k / m) * (x + kx1 / 2.0) - (c / m) * (v + kv1 / 2.0)) * step;
        
        kv3 = (v + kv2 / 2.0) * step;
        kx3 = ((-k / m) * (x + kx2 / 2.0) - (c / m) * (v + kv2 / 2.0)) * step;
        
        kv4 = (v + kv3) * step;
        kx4 = ((-k / m) * (x + kx3) - (c / m) * (v + kv3)) * step;
        
        x = x + (kv1 + kv4) / 6.0 + (kv2 + kv3) / 3.0 ;
        v = v + (kx1 + kx4) / 6.0 + (kx2 + kx3) / 3.0 ;
        
        return x;
    }

    float HarmonicOsc::DrivenRK2()
    {
        float kx1, kx2;
        float kv1, kv2;
        
        kv1 = (x) * step;
        kx1 = ((ft / m) + (-k / m) * (x) - (c / m) * (v)) * step;
        
        kv2 = (v + kv1 / 2.0) * step;
        kx2 = ((ft / m) + (-k / m) * (x + kx1 / 2.0) - (c / m) * (v + kv1 / 2.0)) * step;
        
        x = x + kx2;
        v = v + kv2;
        
        return x;
    }
    
    float HarmonicOsc::DrivenRK4()
    {
        float kx1, kx2, kx3, kx4;
        float kv1, kv2, kv3, kv4;
        
        kv1 = v * step;
        kx1 = ((ft / m) + (-k / m) * (x) - (c / m) * (v)) * step;
        
        kv2 = (v + kv1 / 2.0) * step;
        kx2 = ((ft / m) + (-k / m) * (x + kx1 / 2.0) - (c / m) * (v + kv1 / 2.0)) * step;
        
        kv3 = (v + kv2 / 2.0) * step;
        kx3 = ((ft / m) + (-k / m) * (x + kx2 / 2.0) - (c / m) * (v + kv2 / 2.0)) * step;
        
        kv4 = (v + kv3) * step;
        kx4 = ((ft / m) + (-k / m) * (x + kx3) - (c / m) * (v + kv3)) * step;
        
        x = x + (kv1 + kv4) / 6.0 + (kv2 + kv3) / 3.0 ;
        v = v + (kx1 + kx4) / 6.0 + (kx2 + kx3) / 3.0 ;
        
        return x;
    }

    
} // End AudioSynthesis namespace
