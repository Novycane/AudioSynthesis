//
//  Rossler.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/17/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Rossler_hpp
#define Rossler_hpp

namespace AudioSynthesis
{
    class Rossler
    {
    public:
        // -------------------- Constructors
        Rossler(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        
        // -------------------- Accessors
        void setX(float X) {x = X;}
        void setY(float Y) {y = Y;}
        void setZ(float Z) {z = Z;}
        
        void setA(float A) {a = A;}
        void setB(float B) {b = B;}
        void setC(float C) {c = C;}
        
    private:
        // -------------------- Private Members
        float x;
        float y;
        float z;
        float a;
        float b;
        float c;
        float sampleRate;
        float step;
        
        // -------------------- Private Methods
        float RK2();
        float RK4();
        
    };
    
} // End AudioSynthesis namespace


#endif /* Rossler_hpp */
