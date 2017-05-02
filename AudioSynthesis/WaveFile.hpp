//
//  WaveFile.hpp
//  DrumCommand
//
//  Created by Steven Novak on 2/27/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef WaveFile_hpp
#define WaveFile_hpp

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace AudioSynthesis
{
    class WaveFile
    {
    public:
        WaveFile();
        ~WaveFile();
        
        void WriteHeader();
        void WriteFileToDisk(const string & FileName);
        void WriteSample(double Sample);
        void WriteStereoSample(double Left, double Right);
        void WriteBuffer(double * Buffer, int BufferLength);
        void ResizeBuffer(int NumberOfBytes);
        
        bool OpenFileAsInt(const string & FileName);
        bool OpenFileAsFloat(const string & FileName);
        bool ReadHeader();
        
        const int GetTotalByteSize() const { return totalByteSize; };
        const int GetTotalSampleSize() const { return totalSampleSize; };
        const int GetSampleRate() const { return sampleRate; };
        const int GetSampleSize() const { return sampleSize; };
        const int GetNumChannels() const { return numChannels; };
        const float GetDuration() const { return lengthInSec; };
        
        const uint8_t GetSample8(int location) const;
        const uint16_t GetSample16(int location) const;
        const uint32_t GetSample24(int location) const;
        const uint32_t GetSample32(int location) const;
        const float GetSampleFloat(int location) const;
        
        void SetSampleRate(int SampleRate) { sampleRate = SampleRate; };
        void SetSampleSize(int SampleSize) { sampleSize = SampleSize; };
        void SetNumChannels(int NumChannels) { numChannels = NumChannels; };
        
        bool CreateVector(shared_ptr<vector<float>> & Data, int ChannelNumber);
        
    private:
        ofstream ThisFile;
        ifstream InFile;
        
        //uint8_t * memblock;
        uint8_t * memblock;
        float * fblock;
        
        float lengthInSec;
        
        bool isPCM;
        
        int bufferIteratorL;
        int bufferIteratorR;
        
        int totalByteSize;
        int totalSampleSize;
        int byteRate;
        int blockAlign;
        int sampleRate;
        int sampleSize; // Bits
        int numChannels;
        
        inline void WriteSample8(double Sample, int & Iterator);
        inline void WriteSample16(double Sample, int & Iterator);
        inline void WriteSample24(double Sample, int & Iterator);
        inline void WriteSample32(double Sample, int & Iterator);
        
    }; // End Wave File Class
}


#endif /* WaveFile_hpp */
