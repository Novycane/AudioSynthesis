//
//  TapedDelay.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 5/1/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef TapedDelay_hpp
#define TapedDelay_hpp

#include <vector>

#include "DelayLine.hpp"

namespace AudioSynthesis
{
    class TapedDelay : public DelayLine
    {
    public:
        // -------------------- Constructors
        TapedDelay(int length);
        
        // -------------------- Accessors
        
        
        // -------------------- Operators
        
        // -------------------- Public Methods
        float tick();
        
    protected:
        // -------------------- Protected Members
        
        
        // -------------------- Protected Methods
        
        
        
    }; // end DelayLine class
} // end AudoiSynthesis namespace

#endif /* TapedDelay_hpp */
