//
//  Lorenz.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/16/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Lorenz.hpp"

namespace AudioSynthesis
{

    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    Lorenz::Lorenz(float SampleRate)
    {
        sampleRate = SampleRate;
        step = 0.01;
        sigma = 10.0;
        r = 28.0;
        b = 8.0 / 3.0;
        x = 1.0;
        y = 1.0;
        z = 1.0;
    }

    
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Lorenz::tick()
    {
        
        return RK4();
    }
    
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    float Lorenz::Euler()
    {
        return 0.0;
    }
    
    
    float Lorenz::RK2()
    {
        float kx1, kx2;
        float ky1, ky2;
        float kz1, kz2;
        
        kx1 = (sigma * (y - x)) * step;
        ky1 = (r * x - y - x * z) * step;
        kz1 = ((x * y) - (b * z)) * step;

        kx2 = (sigma * ((y + step / 2.0) - (x + kx1 / 2.0))) * step;
        ky2 = (r * (x + step / 2.0) - (y + ky1 / 2.0) - (x + step / 2.0) * (z +  step / 2.0)) * step;
        kz2 = (((x + step / 2.0) * (y + step / 2.0)) - (b * (z + kz1 / 2.0))) * step;

        x = x + kx2;
        y = y + ky2;
        z = z + kz2;
        
        return y;
    }
    
    float Lorenz::RK4()
    {
        float kx1, kx2, kx3, kx4;
        float ky1, ky2, ky3, ky4;
        float kz1, kz2, kz3, kz4;
        
        kx1 = (sigma * (y - x)) * step;
        ky1 = (r * x - y - x * z) * step;
        kz1 = ((x * y) - (b * z)) * step;
        
        kx2 = (sigma * ((y + step / 2.0) - (x + kx1 / 2.0))) * step;
        ky2 = (r * (x + step / 2.0) - (y + ky1 / 2.0) - (x + step / 2.0) * (z +  step / 2.0)) * step;
        kz2 = (((x + step / 2.0) * (y + step / 2.0)) - (b * (z + kz1 / 2.0))) * step;

        kx3 = (sigma * ((y + step / 2.0) - (x + kx2 / 2.0))) * step;
        ky3 = (r * (x + step / 2.0) - (y + ky2 / 2.0) - (x + step / 2.0) * (z +  step / 2.0)) * step;
        kz3 = (((x + step / 2.0) * (y + step / 2.0)) - (b * (z + kz2 / 2.0))) * step;

        kx4 = (sigma * ((y + step / 2.0) - (x + kx3 / 2.0))) * step;
        ky4 = (r * (x + step / 2.0) - (y + ky3 / 2.0) - (x + step / 2.0) * (z +  step / 2.0)) * step;
        kz4 = (((x + step / 2.0) * (y + step / 2.0)) - (b * (z + kz3 / 2.0))) * step;
        
        x = x + (kx1 + kx4) / 6.0 + (kx2 + kx3) / 3.0 ;
        y = y + (ky1 + ky4) / 6.0 + (ky2 + ky3) / 3.0 ;
        z = z + (kz1 + kz4) / 6.0 + (kz2 + kz3) / 3.0 ;
        
        return y;
    }
    
    
    
} // End AudioSynthesis namespace

