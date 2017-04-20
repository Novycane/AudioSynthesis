//
//  Window.hpp
//  fnMath
//
//  Created by Steven Novak on 3/21/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Enumerations.h"
#include <vector>
#include <cmath>
#include "Constants.h"

using namespace std;

namespace AudioSynthesis
{

    class Window
    {
    public:
        // -------------------- Constructors
        Window();
        Window(WindowType Type, int size, bool preCompute);
        
        // -------------------- Operators
        const float operator[](int index) const;
        
        // -------------------- Accessors
        
        // -------------------- Public Methods
        void setType(WindowType typeOfWindow, bool preCompute);
        float CalcWindowAt(int index);
        
    private:
        // -------------------- Private Members
        WindowType type;
        vector<float> data;
        int windowSize;
        int index;
        
        float lastValue;
        
        bool preCompute;
        
        const float (Window::*ptrToWindowFunction)(int index) const;
        
        // -------------------- Private Methods
        void createTriangle();
        void createParzen();
        void createWelch();
        void createHann();
        void createHamming();
        void createBlackman();
        void createNuttall();
        void createBlackmanNuttall();
        void createBlackmanHarris();
        void createFlattop();
        void createRifeVincent();
        void createGaussian();
        void createConfinedGaussian();
        void createApproxConfinedGaussian();
        void createNormal();
        void createTukey();
        void createPlanckTaper();
        void createSlepian();
        void createKaiser();
        void createDolphChebyshev();
        void createUltraspherical();
        void createPoisson();
        void createBartlettHann();
        void createPlanckBessel();
        void createHannPoisson();
        void createLanczos();
        
        const float tickTriangle(int index) const;
        const float tickParzen(int index) const;
        const float tickWelch(int index) const;
        const float tickHann(int index) const;
        const float tickHamming(int index) const;
        const float tickBlackman(int index) const;
        const float tickNuttall(int index) const;
        const float tickBlackmanNuttall(int index) const;
        const float tickBlackmanHarris(int index) const;
        const float tickFlattop(int index) const;
        const float tickRifeVincent(int index) const;
        const float tickGaussian(int index) const;
        const float tickConfinedGaussian(int index) const;
        const float tickApproxConfinedGaussian(int index) const;
        const float tickNormal(int index) const;
        const float tickTukey(int index) const;
        const float tickPlanckTaper(int index) const;
        const float tickSlepian(int index) const;
        const float tickKaiser(int index) const;
        const float tickDolphChebyshev(int index) const;
        const float tickUltraspherical(int index) const;
        const float tickPoisson(int index) const;
        const float tickBartlettHann(int index) const;
        const float tickPlanckBessel(int index) const;
        const float tickHannPoisson(int index) const;
        const float tickLanczos(int index) const;
        
    }; // end FFT Class
        
} // End AudioSynthesis namespace

#endif /* Window_hpp */
