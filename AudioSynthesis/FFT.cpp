//
//  FFT.cpp
//  fnMath
//
//  Created by Steven Novak on 3/20/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "FFT.hpp"
#include <iostream> // Delete this


namespace AudioSynthesis
{

    #pragma mark Constructors
    // ---------------------------------------- Constructors
    FFT::FFT()
    {
        // somthing?
    }

    #pragma mark Accessors
    // ---------------------------------------- Accessors
    
    
    #pragma mark Public Methods
    // ---------------------------------------- Public Methods
    void FFT::Compute(vector<double> & x, vector<complex<double>> & X)
    {
        int N = x.size();
        int step = 2;
        int span = 1;
        int i, k;
        //double tempR, tempI;
        double factor;
        
        
        if(N & (N - 1) || N < 2)
            throw new PowerOfTwoError();
        
        X.clear();  // Should I do this here????
        X.resize(N);
        
        for(i=0; i<N; i++)
        {
            X[i].real((x[i]));
            X[i].imag((0.0));
        }
        
        SeedVector(X, N);
        
        while(step <= N)
        {
            for(k=0; k<span; k++)
            {
                for(i=k; i<N; i+=step)
                {
                    complex<double> X1, X2;
                    complex<double> Temp1, Temp2;
                    
                    X1 = X[i];
                    X2.real(cos(-PI_2 * (k) / step));
                    X2.imag(-1 * sin(-PI_2 * (k) / step));
                    
                    X[i] = X1 + X[i+span] * X2;
                    X[i + span] = X1 - X[i+span] * X2;
                    
                }
            }
            span = step;
            step *= 2;
        }
    }
    
    void FFT::Compute(vector<complex<double>> & x)
    {
        int N = x.size();
        int step = 2;
        int span = 1;
        int i, k;
        double factor;
        
        if(N & (N - 1) || N < 2)
            throw new PowerOfTwoError();
        
        SeedVector(x, N);
        
        while(step <= N)
        {
            for(k=0; k<span; k++)
            {
                for(i=k; i<N; i+=step)
                {
                    complex<double> X1, X2;
                    complex<double> Temp1, Temp2;
                    
                    X1 = x[i];
                    X2.real(cos(-PI_2 * (k) / step));
                    X2.imag(-1 * sin(-PI_2 * (k) / step));
                    
                    x[i] = X1 + x[i+span] * X2;
                    x[i + span] = X1 - x[i+span] * X2;
                    
                }
            }
            span = step;
            step *= 2;
        }
    }

    void FFT::ComputeInverse(vector<double> & x, vector<complex<double>> & X)
    {
        int N = x.size();
        int step = 2;
        int span = 1;
        int i, k;
        //double tempR, tempI;
        double factor;
        
        
        if(N & (N - 1) || N < 2)
            throw new PowerOfTwoError();
        
        X.clear();  // Should I do this here????
        X.resize(N);
        
        for(i=0; i<N; i++)
        {
            X[i].real((x[i]));
            X[i].imag((0.0));
        }
        
        SeedVector(X, N);
        
        while(step <= N)
        {
            for(k=0; k<span; k++)
            {
                for(i=k; i<N; i+=step)
                {
                    complex<double> X1, X2;
                    complex<double> Temp1, Temp2;
                    
                    X1 = X[i];
                    X2.real(cos(-PI_2 * (k) / step));
                    X2.imag(sin(-PI_2 * (k) / step)); // Check this
                    
                    X[i] = X1 + X[i+span] * X2;
                    X[i + span] = X1 - X[i+span] * X2;
                    
                }
            }
            span = step;
            step *= 2;
        }
        
        for(i=0; i<N; i++)
            X[i] /= sqrt(N);
    }
    
    void FFT::ComputeInverse(vector<complex<double>> & x)
    {
        int N = x.size();
        int step = 2;
        int span = 1;
        int i, k;
        double factor;
        
        if(N & (N - 1) || N < 2)
            throw new PowerOfTwoError();
        
        SeedVector(x, N);
        
        while(step <= N)
        {
            for(k=0; k<span; k++)
            {
                for(i=k; i<N; i+=step)
                {
                    complex<double> X1, X2;
                    complex<double> Temp1, Temp2;
                    
                    X1 = x[i];
                    X2.real(cos(-PI_2 * (k) / step));
                    X2.imag(sin(-PI_2 * (k) / step)); // Check this
                    
                    x[i] = X1 + x[i+span] * X2;
                    x[i + span] = X1 - x[i+span] * X2;
                    
                }
            }
            span = step;
            step *= 2;
        }
        for(i=0; i<N; i++)
            x[i] /= N;
    }
    

    #pragma mark Private Methods
    // ---------------------------------------- Private Methods
    
    inline void FFT::SeedVector(vector<complex<double>> & X, uint16_t length)
    {
        int m;
        int j=1;
        double temp;
        
        for (int i=1; i<length; i+=1)
        {
            if (j > i)
            {
                std::swap(X[i-1], X[j-1]);
            }
            
            m = length / 2;
            while (m >= 2 && j > m)
            {
                j -= m;
                //m >>= 1;
                m /= 2;
            }
            j += m;
        }
    }
    
    void FFT::TransformNaive(vector<double> & x, vector<complex<double>> & X)
    {
        int n = x.size();
        double sqrtN = 1.0 / sqrt(n);
        X.clear();
        
        complex<double> sum;
        
        for(int k = 0; k<n; k++)
        {
            sum = complex<double>(0.0,0.0);
            for(int t=0; t < n; t++)
            {
                sum.real(sum.real() + x[t] * cos(PI_2 * t * k / n));
                sum.imag(sum.imag() - x[t] * sin(PI_2 * t * k / n));
            }
            X.push_back(sum * sqrtN);
        }
    }
    
    void FFT::InverseNaive(vector<complex<double>> & X, vector<double> & x)
    {
        int n = X.size();
        double sqrtN = 1.0 / sqrt(n);
        x.clear();
        
        double sum;
        
        for(int k = 0; k<n; k++)
        {
            sum = 0.0;
            for(int t=0; t < n; t++)
            {
                sum += X[t].real() * cos(PI_2 * t * k / n);
                sum -= X[t].imag() * sin(PI_2 * t * k / n);
            }
            x.push_back(sum * sqrtN);
        }
    }
    
    void FFT::Transform(vector<double> & x, vector<complex<double>> & X)
    {
        int N = x.size();
        int step = 2;
        int span = 1;
        int i, k;
        double factor;
        
        
        if(N & (N - 1) || N < 2)
            throw new PowerOfTwoError();
        
        X.clear();  // Should I do this here????
        X.resize(N);
        
        for(i=0; i<N; i++)
        {
            X[i].real((x[i]));
            X[i].imag((0.0));
        }
        
        SeedVector(X, N);
        
        while(step <= N)
        {
            for(k=0; k<span; k++)
            {
                for(i=k; i<N; i+=step)
                {
                    complex<double> X1, X2;
                    complex<double> Temp1, Temp2;
                    
                    X1 = X[i];
                    X2.real(cos(-PI_2 * (k) / step));
                    X2.imag(sin(-PI_2 * (k) / step));
                    
                    X[i] = X1 + X[i+span] * X2;
                    X[i + span] = X1 - X[i+span] * X2;
  
                }
            }
            span = step;
            step *= 2;
        }
    }

} // End AudioSynthesis namespace
