//
//  DelayLine.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 5/1/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef DelayLine_hpp
#define DelayLine_hpp

#include <vector>
#include <memory>

#include "Enumerations.h"

namespace AudioSynthesis
{
    class DelayLine
    {
    public:
        // -------------------- Constructors
        DelayLine(int length);
        
        // -------------------- Accessors
        void SetDirection(DelayDirection Direction);
        
        // -------------------- Operators
        const float operator[](int index) const;
        
        // -------------------- Public Methods
        void initPluck(float location);
        void initRandom();
        
    protected:
        // -------------------- Protected Members
        std::unique_ptr<std::vector<float>> delayBuffer;
        float output;
        int increment;
        
        // -------------------- Protected Methods
        
        
        
    }; // end DelayLine class
} // end AudoiSynthesis namespace


#endif /* DelayLine_hpp */
