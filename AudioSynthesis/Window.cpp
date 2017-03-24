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
    
    Window::Window(WindowType Type, int Size)
    {
        type = Type;
        windowSize = Size;
        
        data.resize(windowSize);
        
        switch (Type)
        {
            case TRIANGLE:
                createTriangle();
                break;
            case PARZEN:
                createParzen();
                break;
            case WELCH:
                createWelch();
                break;
            case HANN:
                createHann();
                break;
            case HAMMING:
                createHamming();
                break;
            case BLACKMAN:
                createBlackman();
                break;
            case NUTTALL:
                createNuttall();
                break;
            case BLACKMAN_NUTTALL:
                createBlackmanNuttall();
                break;
            case BLACKMAN_HARRIS:
                createBlackmanHarris();
                break;
            case FLATTOP:
                createFlattop();
                break;
            case GAUSSIAN:
                createGaussian();
                break;
            case CONFINED_GAUSSIAN:
                createConfinedGaussian();
                break;
            case NORMAL:
                createNormal();
                break;
            case TUKEY:
                createTukey();
                break;
            case PLANCK_TAPER:
                createPlanckTaper();
                break;
            case SLEPIAN:
                createSlepian();
                break;
            case KAISER:
                createKaiser();
                break;
            case DOLPH_CHEBYSHEV:
                createDolphChebyshev();
                break;
            case ULTRASPHERICAL:
                createUltraspherical();
                break;
            case POISSON:
                createPoisson();
                break;
            case BARTLETT_HANN:
                createBartlettHann();
                break;
            case PLANCK_BESSEL:
                createPlanckBessel();
                break;
            case HANN_POISSON:
                createHannPoisson();
                break;
            case LANCZOS:
                createLanczos();
                break;
            default:
                break;
        }
    }
    
    #pragma mark Operators
    // ---------------------------------------- Operators
    const double & Window::operator[](int index) const
    {
        return data[index];
    }
    
    
    #pragma mark Accessors
    // ---------------------------------------- Accessors
    
    
    #pragma mark Public Methods
    // ---------------------------------------- Public Methods

    
    #pragma mark Private Methods
    // ---------------------------------------- Private Methods
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
   
    
} // End AudioSynthesis namespace
