//
//  Window.cpp
//  fnMath
//
//  Created by Steven Novak on 3/21/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Window.hpp"


namespace AudioSynthesis
{
    #pragma mark Constructors
    // ---------------------------------------- Constructors
    
    Window::Window()
    {
        type = WindowType::TRIANGLE;
        windowSize = 0;
        index = 0;
    }
    
    Window::Window(WindowType Type, int Size, bool PreCompute)
    {
        type = Type;
        windowSize = Size;
        index = 0;
        
        preCompute = PreCompute;
        
        updateWindows();
    }
    
    #pragma mark Operators
    // ---------------------------------------- Operators
    const float Window::operator[](int Index) const
    {
        if(preCompute)
            return data[Index];
        else
        {
            return (this->*ptrToWindowFunction)(Index);
        }
    }
    
    #pragma mark Accessors
    // ---------------------------------------- Accessors
    void Window::setSize(int numOfSamples)
    {
        windowSize = numOfSamples;
        updateWindows();
    }
    
    void Window::PreComputeWindow(bool PreCompute)
    {
        preCompute = PreCompute;
        updateWindows();
    }
    
    #pragma mark Public Methods
    // ---------------------------------------- Public Methods
    float Window::CalcWindowAt(int index)
    {
        return (this->*ptrToWindowFunction)(index);
    }
    
    void Window::setType(WindowType typeOfWindow, bool PreCompute)
    {
        type = typeOfWindow;
        preCompute = PreCompute;
        updateWindows();
    }
    
    #pragma mark Private Methods
    // ---------------------------------------- Private Methods
    void Window::updateWindows()
    {
        if(preCompute)
            data.resize(windowSize);
        
        switch (type)
        {
            case WindowType::TRIANGLE:
                if(preCompute)
                    createTriangle();
                ptrToWindowFunction = &Window::tickTriangle;
                break;
            case WindowType::PARZEN:
                if(preCompute)
                    createParzen();
                ptrToWindowFunction = &Window::tickParzen;
                break;
            case WindowType::WELCH:
                if(preCompute)
                    createWelch();
                ptrToWindowFunction = &Window::tickWelch;
                break;
            case WindowType::HANN:
                if(preCompute)
                    createHann();
                ptrToWindowFunction = &Window::tickHann;
                break;
            case WindowType::HAMMING:
                if(preCompute)
                    createHamming();
                ptrToWindowFunction = &Window::tickHamming;
                break;
            case WindowType::BLACKMAN:
                if(preCompute)
                    createBlackman();
                ptrToWindowFunction = &Window::tickBlackman;
                break;
            case WindowType::NUTTALL:
                if(preCompute)
                    createNuttall();
                ptrToWindowFunction = &Window::tickNuttall;
                break;
            case WindowType::BLACKMAN_NUTTALL:
                if(preCompute)
                    createBlackmanNuttall();
                ptrToWindowFunction = &Window::tickBlackmanNuttall;
                break;
            case WindowType::BLACKMAN_HARRIS:
                if(preCompute)
                    createBlackmanHarris();
                ptrToWindowFunction = &Window::tickBlackmanHarris;
                break;
            case WindowType::FLATTOP:
                if(preCompute)
                    createFlattop();
                ptrToWindowFunction = &Window::tickFlattop;
                break;
            case WindowType::GAUSSIAN:
                if(preCompute)
                    createGaussian();
                ptrToWindowFunction = &Window::tickGaussian;
                break;
            case WindowType::CONFINED_GAUSSIAN:
                if(preCompute)
                    createConfinedGaussian();
                ptrToWindowFunction = &Window::tickConfinedGaussian;
                break;
            case WindowType::NORMAL:
                if(preCompute)
                    createNormal();
                ptrToWindowFunction = &Window::tickNormal;
                break;
            case WindowType::TUKEY:
                if(preCompute)
                    createTukey();
                ptrToWindowFunction = &Window::tickTukey;
                break;
            case WindowType::PLANCK_TAPER:
                if(preCompute)
                    createPlanckTaper();
                ptrToWindowFunction = &Window::tickPlanckTaper;
                break;
            case WindowType::SLEPIAN:
                if(preCompute)
                    createSlepian();
                ptrToWindowFunction = &Window::tickSlepian;
                break;
            case WindowType::KAISER:
                if(preCompute)
                    createKaiser();
                ptrToWindowFunction = &Window::tickKaiser;
                break;
            case WindowType::DOLPH_CHEBYSHEV:
                if(preCompute)
                    createDolphChebyshev();
                ptrToWindowFunction = &Window::tickDolphChebyshev;
                break;
            case WindowType::ULTRASPHERICAL:
                if(preCompute)
                    createUltraspherical();
                ptrToWindowFunction = &Window::tickUltraspherical;
                break;
            case WindowType::POISSON:
                if(preCompute)
                    createPoisson();
                ptrToWindowFunction = &Window::tickPoisson;
                break;
            case WindowType::BARTLETT_HANN:
                if(preCompute)
                    createBartlettHann();
                ptrToWindowFunction = &Window::tickBartlettHann;
                break;
            case WindowType::PLANCK_BESSEL:
                if(preCompute)
                    createPlanckBessel();
                ptrToWindowFunction = &Window::tickPlanckBessel;
                break;
            case WindowType::HANN_POISSON:
                if(preCompute)
                    createHannPoisson();
                ptrToWindowFunction = &Window::tickHannPoisson;
                break;
            case WindowType::LANCZOS:
                if(preCompute)
                    createLanczos();
                ptrToWindowFunction = &Window::tickLanczos;
                break;
            default:
                break;
        }
    }
    
    
    void Window::createTriangle()
    {
        double y = 0.0;
        double offset = 0.0;    // Maybe an int ?!?
        
        for(int i=0; i<windowSize; i++)
        {
            y = (i - (windowSize - 1.0) / 2.0) / ((windowSize + offset) / 2.0);
            data[i] = 1.0 - abs(y);
        }
    }
    
    void Window::createParzen() // <----- Need to analyize this
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            if(i <= windowSize / 4 )
            {
                y = 1.0 - 6.0 * pow(((double)i / ((double)windowSize * 0.5)),2) * (1.0 - abs((double)i)/(0.5 * (double)windowSize));
            }
            else if(i <= windowSize / 2 )
            {
                y = 2.0 * pow((1.0 - (abs((double)i / ((double)windowSize * 0.5)))), 3);
            }
            else
            {
                y = 1.0 - data[windowSize - i];
            }
            
            data[i] = 1.0 - y;
        }
    }
    
    void Window::createWelch()
    {
        double y = 0;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = (N - 1.0) * 0.5;
            y = (i - (N - 1.0) * 0.5) / y;
            y *= y;
            data[i] = 1.0 - y;
        }
    }
    
    void Window::createHann()
    {
        double y = 0;
        double N = windowSize;
        for(double i=0; i<windowSize; i++)
        {
            y = 0.5 * (1.0 - cos(PI_2 * i /(N - 1.0)));
            data[i] = y;
        }
    }
    
    void Window::createHamming()
    {
        double y = 0;
        double alpha = 0.54;
        double beta = 1.0 - alpha;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = alpha - beta * cos(PI_2 * i /(N - 1.0));
            data[i] = y;
        }
    }
    
    void Window::createBlackman()
    {
        double y = 0;
        double alpha = 0.16;
        double a0 = (1.0 - alpha) / 2.0;
        double a1 = 0.5;
        double a2 = alpha / 2.0;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = a0 - a1 * cos((PI_2 * i) / (N - 1)) + a2 * cos((2 * PI_2 * i) / (N - 1));
            
            data[i] = y;
        }
    }
    
    void Window::createNuttall()
    {
        double y = 0;
        double a0 = 0.355768;
        double a1 = 0.487396;
        double a2 = 0.144232;
        double a3 = 0.012604;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = a0 - a1 * cos((PI_2 * i) / (N - 1)) + a2 * cos((2 * PI_2 * i) / (N - 1)) - a3 * cos((3 * PI_2 * i) / (N - 1));
            data[i] = y;
        }
    }
    
    void Window::createBlackmanNuttall()
    {
        double y = 0;
        double a0 = 0.3635819;
        double a1 = 0.4891775;
        double a2 = 0.1365995;
        double a3 = 0.0106411;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = a0 - a1 * cos((PI_2 * i) / (N - 1)) + a2 * cos((2 * PI_2 * i) / (N - 1)) - a3 * cos((3 * PI_2 * i) / (N - 1));
            data[i] = y;
        }
    }
    
    void Window::createBlackmanHarris()
    {
        double y = 0;
        double a0 = 0.35875;
        double a1 = 0.48829;
        double a2 = 0.14128;
        double a3 = 0.01168;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = a0 - a1 * cos((PI_2 * i) / (N - 1)) + a2 * cos((2 * PI_2 * i) / (N - 1)) - a3 * cos((3 * PI_2 * i) / (N - 1));
            data[i] = y;
        }
    }
    
    void Window::createFlattop()
    {
        double y = 0;
        double a0 = 1.0;
        double a1 = 1.93;
        double a2 = 1.29;
        double a3 = 0.388;
        double a4 = 0.028;
        double N = windowSize;
 
        for(double i=0; i<windowSize; i++)
        {
            y = a0 - a1 * cos((PI_2 * i) / (N - 1)) + a2 * cos((2 * PI_2 * i) / (N - 1)) - a3 * cos((3 * PI_2 * i) / (N - 1)) + a4 * cos((4 * PI_2 * i) / (N - 1));
            data[i] = y;
        }
    }
    
    void Window::createGaussian()
    {
        double y = 0;
        double N = windowSize;
        double sigma = 0.5;     // Can be modified
        
        for(double i=0; i<windowSize; i++)
        {
            y = i - (N - 1.0) * 0.5;
            y /= sigma * (N - 1.0) * 0.5;
            y = y * y;
            y = exp(-0.5 * y);
            
            data[i] = y;
        }
    }
    
    void Window::createConfinedGaussian()
    {
        double y = 0;
        double N = windowSize;
        double sigma = 0.1;     // Can be modified
        
        for(double i=0; i<windowSize; i++)
        {
            y = i - (N - 1.0) * 0.5;
            y /= sigma * (N - 1.0) * 0.5;
            y = y * y;
            y = exp(-0.5 * y);
            
            data[i] = y;
        }
    }
    
    void Window::createNormal()
    {
        double y = 0;
        double N = windowSize;
        double sigma = 0.5;     // Can be modified
        int p = 2;              // Can be modified
        
        for(double i=0; i<windowSize; i++)
        {
            y = i - (N - 1.0) * 0.5;
            y /= sigma * (N - 1.0) * 0.5;
            for(int j = 0; j <=p; j++)
                y = y * y;
            y = exp(-0.5 * y);
            
            data[i] = y;
        }
    }
    
    void Window::createTukey()
    {
        double y = 0;
        double N = windowSize;
        double alpha = 0.5;
        double limit = alpha * (N-1) * 0.5;
        
        for(double i=0; i<windowSize; i++)
        {
            if(i <= limit)
                y = 0.5 * (1.0 + cos(PI * ((2.0 * i) / (alpha * (N-1.0)) - 1.0)));
            else if( i < (N - 1.0) * (1.0 - alpha * 0.5))
                y = 1.0;
            else
                y = 0.5 * (1.0 + cos(PI * ((2.0 * i) / (alpha * (N-1.0)) -  2.0 / alpha + 1.0)));
            
            data[i] = y;
        }
    }
    
    void Window::createPlanckTaper()
    {
        double y = 0;
        double epsilon = 0.1;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            if(i < epsilon*(N-1.0))
            {
                y = 1.0 / (1 + (2.0 * i / (N-1.0) - 1.0));
                y += 1.0 / (1 - 2.0 * epsilon + (2.0 * i / (N-1.0) - 1.0));
                y *= 2.0 * epsilon;
                data[i] = 1.0 / (exp(y)+ 1.0);
            }
            else if (i < (1.0 - epsilon) * (N-1.0))
            {
                data[i] = 1.0;
            }
            else if (i < N-1.0)
            {
                y = 1.0 / (1 - (2.0 * i / (N-1.0) - 1.0));
                y += 1.0 / (1 - 2.0 * epsilon - (2.0 * i / (N-1.0) - 1.0));
                y *= 2.0 * epsilon;
                data[i] = 1.0 / (exp(y)+ 1.0);
            }
            else
                data[i] = 0.0;
            
        }
    }
    
    void Window::createSlepian()    // -------------------- Need to fill this out
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createKaiser()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createDolphChebyshev()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createUltraspherical()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    void Window::createPoisson()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createBartlettHann()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createPlanckBessel()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createHannPoisson()
    {
        double y = 0;
        for(int i=0; i<windowSize; i++)
        {
            y = 0.0;
            
            data[i] = y;
        }
    }
    
    void Window::createLanczos()
    {
        double y = 0;
        double N = windowSize;
        
        for(double i=0; i<windowSize; i++)
        {
            y = (i + i) / (N-1) - 1.0;

            data[i] = sin(PI * y) / (PI * y);
        }
    }
    
    #pragma mark Realtime
    // ---------------------------------------- Realtime
    
    const float Window::tickTriangle(int index) const
    {
        double y = 0.0;
        double offset = 0.0;    // Maybe an int ?!?
        
        y = ((double)index - (windowSize - 1.0) / 2.0) / ((windowSize + offset) / 2.0);
        return (1.0 - abs(y));
    }
    
    const float Window::tickParzen(int index) const // <----- Need to analyize this
    {
        double y = 0;
        
        if(index <= windowSize / 4 )
        {
            y = 1.0 - 6.0 * pow(((double)index / ((double)windowSize * 0.5)),2) * (1.0 - abs((double)index)/(0.5 * (double)windowSize));
        }
        else if(index <= windowSize / 2 )
        {
            y = 2.0 * pow((1.0 - (abs((double)index / ((double)windowSize * 0.5)))), 3);
        }
        else
        {
            y = 1.0 - data[windowSize - index];
        }
        
        return (1.0 - y);
    }
    
    const float Window::tickWelch(int index) const
    {
        double y = 0;
        double N = windowSize;
        
        y = (N - 1.0) * 0.5;
        y = (index - (N - 1.0) * 0.5) / y;
        y *= y;
        return 1.0 - y;
    }
    
    const float Window::tickHann(int index) const
    {
        double y = 0;
        double N = windowSize;
        
        y = 0.5 * (1.0 - cos(PI_2 * index /(N - 1.0)));
        return y;
    }
    
    const float Window::tickHamming(int index) const
    {
        double y = 0;
        double alpha = 0.54;
        double beta = 1.0 - alpha;
        double N = windowSize;
        
        y = alpha - beta * cos(PI_2 * index /(N - 1.0));
        return y;
    }
    
    const float Window::tickBlackman(int index) const
    {
        double y = 0;
        double alpha = 0.16;
        double a0 = (1.0 - alpha) / 2.0;
        double a1 = 0.5;
        double a2 = alpha / 2.0;
        double N = windowSize;
    
        y = a0 - a1 * cos((PI_2 * index) / (N - 1)) + a2 * cos((2 * PI_2 * index) / (N - 1));
            
        return y;
    }
    
    const float Window::tickNuttall(int index)const
    {
        double y = 0;
        double a0 = 0.355768;
        double a1 = 0.487396;
        double a2 = 0.144232;
        double a3 = 0.012604;
        double N = windowSize;
        
        
        y = a0 - a1 * cos((PI_2 * index) / (N - 1)) + a2 * cos((2 * PI_2 * index) / (N - 1)) - a3 * cos((3 * PI_2 * index) / (N - 1));
        return y;
    }
    
    const float Window::tickBlackmanNuttall(int index) const
    {
        double y = 0;
        double a0 = 0.3635819;
        double a1 = 0.4891775;
        double a2 = 0.1365995;
        double a3 = 0.0106411;
        double N = windowSize;
        
        y = a0 - a1 * cos((PI_2 * index) / (N - 1)) + a2 * cos((2 * PI_2 * index) / (N - 1)) - a3 * cos((3 * PI_2 * index) / (N - 1));
        return y;
    }
    
    const float Window::tickBlackmanHarris(int index) const
    {
        double y = 0;
        double a0 = 0.35875;
        double a1 = 0.48829;
        double a2 = 0.14128;
        double a3 = 0.01168;
        double N = windowSize;
        
        y = a0 - a1 * cos((PI_2 * index) / (N - 1)) + a2 * cos((2 * PI_2 * index) / (N - 1)) - a3 * cos((3 * PI_2 * index) / (N - 1));
        return y;
    }
    
    const float Window::tickFlattop(int index) const
    {
        double y = 0;
        double a0 = 1.0;
        double a1 = 1.93;
        double a2 = 1.29;
        double a3 = 0.388;
        double a4 = 0.028;
        double N = windowSize;
        
        y = a0 - a1 * cos((PI_2 * index) / (N - 1)) + a2 * cos((2 * PI_2 * index) / (N - 1)) - a3 * cos((3 * PI_2 * index) / (N - 1)) + a4 * cos((4 * PI_2 * index) / (N - 1));
        return y;
    }
    
    const float Window::tickGaussian(int index) const
    {
        double y = 0;
        double N = windowSize;
        double sigma = 0.5;     // Can be modified
        
        y = index - (N - 1.0) * 0.5;
        y /= sigma * (N - 1.0) * 0.5;
        y = y * y;
        y = exp(-0.5 * y);
        
        return y;
    }
    
    const float Window::tickConfinedGaussian(int index) const
    {
        double y = 0;
        double N = windowSize;
        double sigma = 0.1;     // Can be modified
        
        y = index - (N - 1.0) * 0.5;
        y /= sigma * (N - 1.0) * 0.5;
        y = y * y;
        y = exp(-0.5 * y);
        
        return y;
    }
    
    const float Window::tickNormal(int index) const
    {
        double y = 0;
        double N = windowSize;
        double sigma = 0.5;     // Can be modified
        int p = 2;              // Can be modified
        
        y = index - (N - 1.0) * 0.5;
        y /= sigma * (N - 1.0) * 0.5;
        for(int j = 0; j <=p; j++)
            y = y * y;
        y = exp(-0.5 * y);
        
        return y;
    }
    
    const float Window::tickTukey(int index) const
    {
        double y = 0;
        double N = windowSize;
        double alpha = 0.5;
        double limit = alpha * (N-1) * 0.5;
        
        if(index <= limit)
            y = 0.5 * (1.0 + cos(PI * ((2.0 * index) / (alpha * (N-1.0)) - 1.0)));
        else if( index < (N - 1.0) * (1.0 - alpha * 0.5))
            y = 1.0;
        else
            y = 0.5 * (1.0 + cos(PI * ((2.0 * index) / (alpha * (N-1.0)) -  2.0 / alpha + 1.0)));
        
        return y;
    }
    
    const float Window::tickPlanckTaper(int index) const
    {
        double y = 0;
        double epsilon = 0.1;
        double N = windowSize;
        
        
        if(index < epsilon * (N - 1.0))
        {
            y = 1.0 / (1 + (2.0 * index / (N - 1.0) - 1.0));
            y += 1.0 / (1 - 2.0 * epsilon + (2.0 * index / (N - 1.0) - 1.0));
            y *= 2.0 * epsilon;
            return 1.0 / (exp(y) + 1.0);
        }
        else if (index < (1.0 - epsilon) * (N - 1.0))
        {
            return 1.0;
        }
        else if (index < N - 1.0)
        {
            y = 1.0 / (1 - (2.0 * index / (N-1.0) - 1.0));
            y += 1.0 / (1 - 2.0 * epsilon - (2.0 * index / (N-1.0) - 1.0));
            y *= 2.0 * epsilon;
            return 1.0 / (exp(y)+ 1.0);
        }
        else
            return 0.0;
    }
    
    const float Window::tickSlepian(int index) const    // -------------------- Need to fill this out
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickKaiser(int index) const
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickDolphChebyshev(int index) const
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickUltraspherical(int index) const
    {
        double y = 0;
        
        return y;
    }
    const float Window::tickPoisson(int index) const
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickBartlettHann(int index) const
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickPlanckBessel(int index) const
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickHannPoisson(int index) const
    {
        double y = 0;
        
        return y;
    }
    
    const float Window::tickLanczos(int index) const
    {
        double y = 0;
        double N = windowSize;
        
        y = (index + index) / (N-1) - 1.0;
        
        return sin(PI * y) / (PI * y);
        
    }
   
    
} // End AudioSynthesis namespace
