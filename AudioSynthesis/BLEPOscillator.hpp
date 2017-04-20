//
//  BLEPOscillator.hpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/18/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef BLEPOscillator_hpp
#define BLEPOscillator_hpp

#include <vector>
#include "Oscillator.hpp"
#include "Window.hpp"

namespace AudioSynthesis
{
    
    
    class BLEPOscillator : public Oscillator
    {
        using PtrFunc = float (BLEPOscillator::*)();
        
    public:
        //-------------------- Constructors
        BLEPOscillator();
        BLEPOscillator(float SampleRate);
        BLEPOscillator(float SampleRate, int BLEPPoints, int TableSize, WindowType Window);
        
        //-------------------- Accessors
        void SetNumPoints(int NumBLEPPoints);
        
        //-------------------- Public Methods
        float tick();
        
    private:
        //-------------------- Private Members
        int tableSize;
        int BLEPPoints;
        vector<float> BLEPTable;
        
        //float (BLEPOscillator::*BLEPFunc)();
        PtrFunc BLEPFunc;
        
        //-------------------- Private Methods
        void CalcBLEPTable(WindowType window);
        float Do2PtBLEP();
        float Do4PtBLEP();
        float Do6PtBLEP();
        float Do8PtBLEP();
        
    };
}


#endif /* BLEPOscillator_hpp */
