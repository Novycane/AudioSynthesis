//
//  Lorenz.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/16/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Lorenz_hpp
#define Lorenz_hpp

namespace AudioSynthesis
{
    class Lorenz
    {
    public:
        // -------------------- Constructors
        Lorenz(float SampleRate);
        
        // -------------------- Public Methods
        float tick();
        
        // -------------------- Accessors
        void setX(float X) {x = X;}
        void setY(float Y) {y = Y;}
        void setZ(float Z) {z = Z;}
        void setSigma(float Sigma) {sigma = Sigma;}
        void setB(float B) {b = B;}
        void setR(float R) {r = R;}
        void setStep(float Step) {step = Step;}
        
    private:
        // -------------------- Private Members
        float x;
        float y;
        float z;
        float sigma;
        float r;
        float b;
        float sampleRate;
        float step;
        
        // -------------------- Private Methods
        float Euler();
        float RK2();
        float RK4();
        
        
    }; // End Lorennz Class
    
} // End AudioSynthesis namespace

#endif /* Lorenz_hpp */
