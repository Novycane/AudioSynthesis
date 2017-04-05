//
//  Envelope.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/7/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Envelope_hpp
#define Envelope_hpp

namespace AudioSynthesis
{
    
    class Envelope
    {
    public:
        
        
        // -------------------- Public Methods
        virtual float tick() = 0;
        
    private:
        // -------------------- Private Members
        
        
        // -------------------- Private Methods
        
    }; // End Envelope class
}

#endif /* Envelope_hpp */
