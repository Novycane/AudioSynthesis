//
//  Henon.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/17/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Henon.hpp"

namespace AudioSynthesis
{
    
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    Henon::Henon(float SampleRate)
    {
        sampleRate = SampleRate;
        step = 0.1;
        a = 0.14;
        b = 0.3;
        x = 1.0;
        y = 1.0;
    }
    
    
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Henon::tick()
    {
        return RK4();
    }
    
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    float Henon::RK2()
    {
        float kx1, kx2;
        float ky1, ky2;
        
        kx1 = a + b * y - x * x;
        ky1 = x;
        
        kx2 = a + b * (y + step / 2.0) - (x + kx1 / 2.0) * (x + kx1 / 2.0);
        ky2 = (x + step / 2.0);
        
        x = x + kx2;
        y = y + ky2;
        
        return y;
    }
    
    float Henon::RK4()
    {
        float kx1, kx2, kx3, kx4;
        float ky1, ky2, ky3, ky4;
        
        kx1 = a + b * y - x * x;
        ky1 = x;
        
        kx2 = a + b * (y + step / 2.0) - (x + kx1 / 2.0) * (x + kx1 / 2.0);
        ky2 = (x + step / 2.0);
        
        kx3 = a + b * (y + step / 2.0) - (x + kx2 / 2.0) * (x + kx2 / 2.0);
        ky3 = (x + step / 2.0);
        
        kx2 = a + b * (y + step) - (x + kx3) * (x + kx3);
        ky2 = (x + step);
        
        x = x + (kx1 + kx4) / 6.0 + (kx2 + kx3) / 3.0 ;
        y = y + (ky1 + ky4) / 6.0 + (ky2 + ky3) / 3.0 ;
        
        return x;
    }
    
    
} // End AudioSynthesis namespace
