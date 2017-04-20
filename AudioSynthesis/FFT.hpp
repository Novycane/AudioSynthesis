//
//  FFT.hpp
//  fnMath
//
//  Created by Steven Novak on 3/20/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef FFT_hpp
#define FFT_hpp

#include <vector>
#include <complex>
#include <cmath>
#include <exception>
#include "Constants.h"

using namespace std;

namespace AudioSynthesis
{
    class PowerOfTwoError: public exception
    {
        virtual const char* what() const throw()
        {
            return "Vector Must Be A Power Of 2!";
        }
    };
    
    class FFT
    {
    public:
        // -------------------- Constructors
        FFT();
        
        // -------------------- Accessors
        
        // -------------------- Public Methods
        void Compute(vector<double> & x, vector<complex<double>> & X);
        void Compute(vector<complex<double>> & x);
        void ComputeInverse(vector<double> & x, vector<complex<double>> & X);
        void ComputeInverse(vector<complex<double>> & x);
        void ComputeCepstrum(vector<double> & x, vector<double> & C);
        void ComputeCepstrum(vector<double> & x);
        void ComputeMinPhase(vector<double> & x);
        
    private:
        // -------------------- Private Members
        
        // -------------------- Private Methods
        inline void SeedVector(vector<complex<double>> & X, uint16_t length);
        void Transform(vector<double> & x, vector<complex<double>> & X);
        void TransformNaive(vector<double> & x, vector<complex<double>> & X);
        void InverseNaive(vector<complex<double>> & X, vector<double> & x);
        
    }; // end FFT Class
    
} // End AudioSynthesis namespace

#endif /* FFT_hpp */
