//
//  Window.hpp
//  fnMath
//
//  Created by Steven Novak on 3/21/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <vector>
#include <cmath>
#include "Constants.h"

using namespace std;

namespace AudioSynthesis
{
    
    enum WindowType {TRIANGLE, PARZEN, WELCH, HANN, HAMMING, BLACKMAN, NUTTALL, BLACKMAN_NUTTALL, BLACKMAN_HARRIS, FLATTOP, GAUSSIAN, CONFINED_GAUSSIAN, NORMAL, TUKEY, PLANCK_TAPER, SLEPIAN, KAISER, DOLPH_CHEBYSHEV, ULTRASPHERICAL, POISSON, BARTLETT_HANN, PLANCK_BESSEL, HANN_POISSON, LANCZOS};
    
    class Window
    {
    public:
        // -------------------- Constructors
        Window(WindowType Type, int size);
        
        // -------------------- Operators
        const double & operator[](int index) const;
        
        // -------------------- Accessors
        
        // -------------------- Public Methods
        
        
    private:
        // -------------------- Private Members
        WindowType type;
        vector<double> data;
        int windowSize;
        
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
        
    }; // end FFT Class
        
} // End AudioSynthesis namespace

#endif /* Window_hpp */
