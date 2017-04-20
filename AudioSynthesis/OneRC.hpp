//
//  OneRC.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/14/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef OneRC_hpp
#define OneRC_hpp

#include <cmath>

namespace AudioSynthesis
{
    class OneRC
    {
    public:
        // -------------------- Constructors
        OneRC();
        OneRC(float R, float C);
        
        // -------------------- Accessors
        const float GetR() const {return r;}
        const float GetC() const {return c;}
        
        void SetResonance(float Resonance);
        void SetCutoff(float Cuoff);
        
        // -------------------- Public Methods
        float update(float input);
        
    private:
        // -------------------- Private Members
        float r;
        float c;
        float V0;
        float V1;
        
    };
}




#endif /* OneRC_hpp */
