//
//  Henon.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/17/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Henon_hpp
#define Henon_hpp

namespace AudioSynthesis
{
    class Henon
    {
    public:
        // -------------------- Constructors
        Henon(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        
        // -------------------- Accessors
        void setX(float X) {x = X;}
        void setY(float Y) {y = Y;}
        void setA(float A) {a = A;}
        void setB(float B) {b = B;}
        
    private:
        // -------------------- Private Members
        float x;
        float y;
        float a;
        float b;
        float sampleRate;
        float step;
        
        // -------------------- Private Methods
        float RK2();
        float RK4();
        
    };
    
} // End AudioSynthesis namespace

#endif /* Henon_hpp */
