//
//  BLEPOscillator.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 4/18/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "BLEPOscillator.hpp"

namespace AudioSynthesis
{
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    BLEPOscillator::BLEPOscillator() : BLEPOscillator(44100.0, 2, 4096, WindowType::TRIANGLE) { }
    
    BLEPOscillator::BLEPOscillator(float SampleRate) : BLEPOscillator(SampleRate, 2, 4096, WindowType::TRIANGLE) { }
    
    BLEPOscillator::BLEPOscillator(float SampleRate, int BLEPPoints, int TableSize, WindowType Window) : Oscillator(SampleRate)
    {
        tableSize = TableSize;
        SetNumPoints(BLEPPoints);
        CalcBLEPTable(Window);
    }
    
    #pragma mark Accessors
    // -------------------------------------------------- Accessors
    void BLEPOscillator::SetNumPoints(int NumBLEPPoints)
    {
        BLEPPoints = NumBLEPPoints;
        if(BLEPPoints < 3)
            if(!invertPhase)
                BLEPFunc = &BLEPOscillator::Do2PtBLEP_DOWN;
            else
                BLEPFunc = &BLEPOscillator::Do2PtBLEP_UP;
        else if (BLEPPoints < 5)
            if(!invertPhase)
                BLEPFunc = &BLEPOscillator::Do4PtBLEP_DOWN;
            else
                BLEPFunc = &BLEPOscillator::Do4PtBLEP_UP;
        else if (BLEPPoints < 7)
            if(!invertPhase)
                BLEPFunc = &BLEPOscillator::Do6PtBLEP_DOWN;
            else
                BLEPFunc = &BLEPOscillator::Do6PtBLEP_UP;
        else if (BLEPPoints < 9)
            if(!invertPhase)
                BLEPFunc = &BLEPOscillator::Do8PtBLEP_DOWN;
            else
                BLEPFunc = &BLEPOscillator::Do8PtBLEP_UP;
        else
            throw std::runtime_error ("Invalid number of BLEP Points");
        
    }
    
    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float BLEPOscillator::tick()
    {
        Oscillator::tick();
        
        return (this->*BLEPFunc)();
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    float BLEPOscillator::Do2PtBLEP_DOWN()
    {
        if(this->modulo + this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / step;
            index = (int) (index * temp);
            return this->modulo - BLEPTable[index];
        }
        else if (this->modulo < this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / step;
            index = (int) (index * temp);
            return this->modulo - BLEPTable[tableSize / 2 + index];
        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do4PtBLEP_DOWN()
    {
        if(this->modulo + 2 * this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / (2.0 * step);
            index = (int) (index * temp);
            temp = BLEPTable[index];
            return this->modulo - BLEPTable[index];
        }
        else if (this->modulo < 2 * this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / (2.0 * step);
            index = (int) (index * temp);
            return this->modulo - BLEPTable[tableSize / 2 + index];        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do6PtBLEP_DOWN()
    {
        if(this->modulo + 2 * this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / (3.0 * step);
            index = (int) (index * temp);
            temp = BLEPTable[index];
            return this->modulo - BLEPTable[index];
        }
        else if (this->modulo < 2 * this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / (3.0 * step);
            index = (int) (index * temp);
            return this->modulo - BLEPTable[tableSize / 2 + index];        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do8PtBLEP_DOWN()
    {
        if(this->modulo + 2 * this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / (4.0 * step);
            index = (int) (index * temp);
            temp = BLEPTable[index];
            return this->modulo - BLEPTable[index];
        }
        else if (this->modulo < 2 * this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / (4.0 * step);
            index = (int) (index * temp);
            return this->modulo - BLEPTable[tableSize / 2 + index];        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do2PtBLEP_UP()
    {
        if(this->modulo + this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / step;
            index = (int) (index * temp);
            return this->modulo + BLEPTable[index];
        }
        else if (this->modulo < this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / step;
            index = (int) (index * temp);
            return this->modulo + BLEPTable[tableSize / 2 + index];
        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do4PtBLEP_UP()
    {
        if(this->modulo + 2 * this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / (2.0 * step);
            index = (int) (index * temp);
            temp = BLEPTable[index];
            return this->modulo + BLEPTable[index];
        }
        else if (this->modulo < 2 * this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / (2.0 * step);
            index = (int) (index * temp);
            return this->modulo + BLEPTable[tableSize / 2 + index];        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do6PtBLEP_UP()
    {
        if(this->modulo + 2 * this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / (3.0 * step);
            index = (int) (index * temp);
            temp = BLEPTable[index];
            return this->modulo + BLEPTable[index];
        }
        else if (this->modulo < 2 * this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / (3.0 * step);
            index = (int) (index * temp);
            return this->modulo + BLEPTable[tableSize / 2 + index];        }
        else
        {
            return this->modulo;
        }
    }
    
    float BLEPOscillator::Do8PtBLEP_UP()
    {
        if(this->modulo + 2 * this->step > 1.0)
        {
            int index = (int)(tableSize / 2) - 1;
            float temp = 1.0 - (1.0 - this->modulo) / (4.0 * step);
            index = (int) (index * temp);
            temp = BLEPTable[index];
            return this->modulo + BLEPTable[index];
        }
        else if (this->modulo < 2 * this->step)
        {
            int index = (int)(tableSize / 2);
            float temp = (this->modulo) / (4.0 * step);
            index = (int) (index * temp);
            return this->modulo + BLEPTable[tableSize / 2 + index];        }
        else
        {
            return this->modulo;
        }
    }
    
    void BLEPOscillator::CalcBLEPTable(WindowType window)
    {
        Window BLEPWindow(window, tableSize, false);
        
        BLEPTable.resize(tableSize);
        
        for(int i=0; i<tableSize; i++)
        {
            auto temp = (i - tableSize / 2) * M_PI / (tableSize / BLEPPoints);
            if(temp == 0)
                BLEPTable[i] = 1 * BLEPWindow[i];
            else
                BLEPTable[i] = sin(temp) / temp * BLEPWindow[i];
        }
        
        for(int i=1; i<tableSize; i++)
        {
            BLEPTable[i] = BLEPTable[i-1] + BLEPTable[i];
        }
        
        for(int i=0; i<tableSize; i++)
            BLEPTable[i] /= BLEPTable[tableSize - 1];
        
        for(int i=tableSize/2; i<tableSize; i++)
            BLEPTable[i] -= 1;
    }
    
}
