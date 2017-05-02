//
//  DelayLine.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 5/1/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "DelayLine.hpp"

#include <iostream>

namespace AudioSynthesis
{
    #pragma mark Constructors
    // ---------------------------------------- Constructors
    DelayLine::DelayLine(int length)
    {
        delayBuffer = std::make_unique<std::vector<float>>();
        delayBuffer->resize(length);
        increment = 1;
    }
    
    #pragma mark Operators
    // ---------------------------------------- Operators
    const float DelayLine::operator[](int index) const
    {
        // For Safwty
        if(index < 0 || index >= delayBuffer->size())
            return 0.0;
        return (*delayBuffer)[index];
    }

    
    #pragma mark Accessors
    // ---------------------------------------- Accessors
    void DelayLine::SetDirection(DelayDirection Direction)
    {
        switch(Direction)
        {
            case DelayDirection::FORWARD:
                increment = 1;
                break;
            case DelayDirection::REVERSE:
                increment = -1;
                break;
        }
    }
    
    #pragma mark Public Methods
    // ---------------------------------------- Public Methods
    void DelayLine::initPluck(float location)
    {
        float size = delayBuffer->size();
        float slope1 = 1.0 / (size * location);
        float slope2 = 1.0 / (size * (1.0 - location));
        
        (*delayBuffer)[0] = 0.0;
        (*delayBuffer)[size - 1] = 0.0;
        
        for(int i=1; i<size-1; i++)
        {
            if((float)i / size <= location)
                (*delayBuffer)[i] = (*delayBuffer)[i - 1] + slope1 / 2.0;
            else
                (*delayBuffer)[i] = (*delayBuffer)[i - 1] - slope2 / 2.0;
        }
    }
    
    
    #pragma mark Protected Methods
    // ---------------------------------------- Protected Methods
    
}
