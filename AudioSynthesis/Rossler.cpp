//
//  Rossler.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/17/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Rossler.hpp"

namespace AudioSynthesis
{
    
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    Rossler::Rossler(float SampleRate)
    {
        sampleRate = SampleRate;
        step = 0.01;
        a = 0.15;
        b = 0.20;
        c = 1.0;
        x = 1.0;
        y = 1.0;
        z = 0.01;
    }
    
    
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Rossler::tick()
    {
        return RK4();
    }
    
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    float Rossler::RK2()
    {
        float kx1, kx2;
        float ky1, ky2;
        float kz1, kz2;
        
        kx1 = (-1 * (z) - y) * step;
        ky1 = ((x) + a * (y)) * step;
        kz1 = (b + z * (x - c)) * step;
        
        kx2 = (-1 * (z +  step / 2.0) - (y + step / 2.0)) * step;
        ky2 = ((x + step / 2.0) + a * (y + ky1 / 2.0)) * step;
        kz2 = (b + (z + kz1) * ((x + step / 2.0) - c)) * step;

        x = x + kx2;
        y = y + ky2;
        z = z + kz2;
        
        return y;
    }
    
    float Rossler::RK4()
    {
        float kx1, kx2, kx3, kx4;
        float ky1, ky2, ky3, ky4;
        float kz1, kz2, kz3, kz4;
        
        kx1 = (-1 * (z) - y) * step;
        ky1 = ((x) + a * (y)) * step;
        kz1 = (b + z * (x - c)) * step;
        
        kx2 = (-1 * (z +  step / 2.0) - (y + step / 2.0)) * step;
        ky2 = ((x + step / 2.0) + a * (y + ky1 / 2.0)) * step;
        kz2 = (b + (z + kz1 / 2.0) * ((x + step / 2.0) - c)) * step;
        
        kx3 = (-1 * (z +  step / 2.0) - (y + step / 2.0)) * step;
        ky3 = ((x + step / 2.0) + a * (y + ky2 / 2.0)) * step;
        kz3 = (b + (z + kz2 / 2.0) * ((x + step / 2.0) - c)) * step;
        
        kx4 = (-1 * (z +  step) - (y + step)) * step;
        ky4 = ((x + step) + a * (y + ky3)) * step;
        kz4 = (b + (z + kz3) * ((x + step) - c)) * step;
        
        x = x + (kx1 + kx4) / 6.0 + (kx2 + kx3) / 3.0 ;
        y = y + (ky1 + ky4) / 6.0 + (ky2 + ky3) / 3.0 ;
        z = z + (kz1 + kz4) / 6.0 + (kz2 + kz3) / 3.0 ;
        
        return z;
    }

    
} // End AudioSynthesis namespace
