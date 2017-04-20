//
//  WaveFile.cpp
//  DrumCommand
//
//  Created by Steven Novak on 2/27/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "WaveFile.hpp"

#define SUB_CHUNK_1_SIZE
#define INT24_MIN -8388608
#define INT24_MAX 8388607

namespace AudioSynthesis
{

#pragma mark Constructors
// ---------------------------------------- Constructors
WaveFile::WaveFile()
{
    totalSampleSize = 0;
    numChannels = 1;
    sampleRate = 44100;
    sampleSize = 16;
    bufferIteratorL = 0;
    memblock = nullptr;
    fblock = nullptr;
}

WaveFile::~WaveFile()
{
    if(memblock != nullptr)
        delete memblock;
    if(fblock != nullptr)
        delete fblock;
}

#pragma mark Public Methods
// ---------------------------------------- Public Methods

bool WaveFile::CreateVector(vector<float> & Data, int ChannelNumber)
{
    /*
     
     int totalByteSize;
     int totalSampleSize;
     int byteRate;
     int blockAlign;
     int sampleRate;
     int sampleSize; // Bits
     int numChannels;

     */
    if(ChannelNumber > numChannels || ChannelNumber < 1)
        return false;
    
    Data.clear();
    Data.resize(totalSampleSize);
    for(int i=0; i<totalSampleSize; i++)
    {
        Data[i] = fblock[i];
    }
    
    
    return true;
}
    
void WaveFile::ResizeBuffer(int NumberOfBytes)
{
    if(memblock != nullptr)
        delete memblock;
    totalByteSize = 44 + numChannels * NumberOfBytes * sampleSize / 8;
    totalSampleSize = NumberOfBytes;
    memblock = new uint8_t[totalByteSize];
    WriteHeader();
    bufferIteratorL = 44;
    bufferIteratorR = 44 + numChannels * NumberOfBytes;
}

void WaveFile::WriteFileToDisk(const string & FileName)
{
    ThisFile.flags(ios::binary);
    ThisFile.open(FileName);
    if(!ThisFile.is_open())
        cout << "Error\n" ;
    ThisFile.write((char*)memblock, totalByteSize);
    ThisFile.close();
}

void WaveFile::WriteStereoSample(double Left, double Right)
{
    if(memblock == nullptr)
        throw new exception();
    
    if(bufferIteratorL + sampleSize / 8 > totalByteSize)
        throw new exception();
    
    if(Left > 1)
        Left = 1;
    else if(Left < -1)
        Left = -1;
    
    if(sampleSize == 8)
    {
        WriteSample8(Left, bufferIteratorL);
        WriteSample8(Right, bufferIteratorL);
    }
    else if(sampleSize == 16)
    {
        WriteSample16(Left, bufferIteratorL);
        WriteSample16(Right, bufferIteratorL);
    }
    else if(sampleSize == 24)
    {
        WriteSample24(Left, bufferIteratorL);
        WriteSample24(Right, bufferIteratorL);
    }
    else if (sampleSize == 32)
    {
        WriteSample32(Left, bufferIteratorL);
        WriteSample32(Right, bufferIteratorL);
    }
    else
    {
        // unsupported sample size
    }
}

void WaveFile::WriteSample(double Sample)
{
    if(memblock == nullptr)
        throw new exception();
    
    if(bufferIteratorL + sampleSize / 8 > totalByteSize)
        throw new exception();
    
    if(Sample > 1)
        Sample = 1;
    else if(Sample < -1)
        Sample = -1;
    
    if(sampleSize == 8)
        WriteSample8(Sample, bufferIteratorL);
    else if(sampleSize == 16)
        WriteSample16(Sample, bufferIteratorL);
    else if(sampleSize == 24)
        WriteSample24(Sample, bufferIteratorL);
    else if (sampleSize == 32)
        WriteSample32(Sample, bufferIteratorL);
    else
    {
        // unsupported sample size
    }
}

void WaveFile::WriteBuffer(double * Buffer, int BufferLength)
{
    if(BufferLength + bufferIteratorL > totalByteSize)
        throw new exception();
    
    if(memblock == nullptr)
        throw new exception();
    
    if(sampleSize == 8)
    {
        for(int i=0; i<BufferLength; i++)
            WriteSample8(Buffer[i], bufferIteratorL);
    }
    else if(sampleSize == 16)
    {
        for(int i=0; i<BufferLength; i++)
            WriteSample16(Buffer[i], bufferIteratorL);
    }
    else if(sampleSize == 24)
    {
        for(int i=0; i<BufferLength; i++)
            WriteSample24(Buffer[i], bufferIteratorL);
    }
    else if (sampleSize == 32)
    {
        for(int i=0; i<BufferLength; i++)
            WriteSample32(Buffer[i], bufferIteratorL);
    }
    else
    {
        // unsupported sample size
    }
}

const uint8_t WaveFile::GetSample8(int location) const
{
    uint8_t * WaveData = (uint8_t*) memblock;
    return WaveData[location];
}

const uint16_t WaveFile::GetSample16(int location) const
{
    uint16_t * WaveData = (uint16_t*) memblock;
    return WaveData[location];
}

const uint32_t WaveFile::GetSample24(int location) const
{
    uint32_t * WaveData = (uint32_t*) memblock;
    return WaveData[location * 3 / 4];
}

const uint32_t WaveFile::GetSample32(int location) const
{
    uint32_t * WaveData = (uint32_t*) memblock;
    return WaveData[location];
}

const float WaveFile::GetSampleFloat(int location) const
{
    float * WaveData = (float*) fblock;
    return WaveData[location];
}

#pragma mark Private Methods
// ---------------------------------------- Private Methods

#pragma make Output Functions
void WaveFile::WriteHeader()
{
    uint32_t tempVal;    

    // Write RIFF
    memblock[0] = 0x52;
    memblock[1] = 0x49;
    memblock[2] = 0x46;
    memblock[3] = 0x46;
    
    
    // Write Chunk Size
    tempVal = 36 + totalSampleSize;
    memblock[4] = (uint8_t)(0x000000FF & tempVal);
    memblock[5] = (uint8_t)(0x0000FF00 & tempVal >> 8);
    memblock[6] = (uint8_t)(0x00FF0000 & tempVal >> 16);
    memblock[7] = (uint8_t)(0xFF000000 & tempVal >> 24);
    
    // WriteFormat
    memblock[8] = 0x57;
    memblock[9] = 0x41;
    memblock[10] = 0x56;
    memblock[11] = 0x45;
    
    // ---------- Write Subchunk 1
    // Write Subchunk ID "fmt"
    memblock[12] = 0x66;
    memblock[13] = 0x6d;
    memblock[14] = 0x74;
    memblock[15] = 0x20;
    
    // Write Subchunk 1 size
    tempVal = 16;
    memblock[16] = (uint8_t)(0x000000FF & tempVal);
    memblock[17] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    memblock[18] = (uint8_t)((0x00FF0000 & tempVal) >> 16);
    memblock[19] = (uint8_t)((0xFF000000 & tempVal) >> 24);
    
    memblock[20] = 0x01;   // Audio Format : 1 for PCM
    memblock[21] = 0x00;   // ... ctd
    
    tempVal = numChannels;          // Number Of Channels : 1 for mono, 2 for stereo, etc...
    memblock[22] = (uint8_t)(0x000000FF & tempVal);
    memblock[23] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    
    // sample rate
    tempVal = sampleRate;
    memblock[24] = (uint8_t)(0x000000FF & tempVal);
    memblock[25] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    memblock[26] = (uint8_t)((0x00FF0000 & tempVal) >> 16);
    memblock[27] = (uint8_t)((0xFF000000 & tempVal) >> 24);
    
    // Byte Rate
    tempVal = sampleRate * numChannels * sampleSize / 8;
    memblock[28] = (uint8_t)(0x000000FF & tempVal);
    memblock[29] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    memblock[30] = (uint8_t)((0x00FF0000 & tempVal) >> 16);
    memblock[31] = (uint8_t)((0xFF000000 & tempVal) >> 24);

    
    tempVal = numChannels * sampleSize / 8;  // NumChannels * BitsPerSample/8
    memblock[32] = (uint8_t)(0x000000FF & tempVal);
    memblock[33] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    
    tempVal = sampleSize;           // Bits per sample
    memblock[34] = (uint8_t)(0x000000FF & tempVal);
    memblock[35] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    
    // ---------- Write Subchunk 2
    // Write Subchunk 2 ID "data"
    memblock[36] = 0x64;
    memblock[37] = 0x61;
    memblock[38] = 0x74;
    memblock[39] = 0x61;
    
    // Data Size: NumSamples * NumChannels * BitsPerSample/8
    tempVal = totalSampleSize * numChannels * sampleSize / 8;
    memblock[40] = (uint8_t)(0x000000FF & tempVal);
    memblock[41] = (uint8_t)((0x0000FF00 & tempVal) >> 8);
    memblock[42] = (uint8_t)((0x00FF0000 & tempVal) >> 16);
    memblock[43] = (uint8_t)((0xFF000000 & tempVal) >> 24);
}


inline void WaveFile::WriteSample8(double Sample, int & Iterator)
{
    int8_t sample;
    if(Sample > 0)
        sample = (INT8_MAX * Sample);
    else
        sample = -1 * (INT8_MIN * Sample);
    memblock[Iterator++] = (uint8_t)sample;
}

inline void WaveFile::WriteSample16(double Sample, int & Iterator)
{
    int16_t sample;
    char* byte = (char*) &sample;
    
    if(Sample > 0)
        sample = (INT16_MAX * Sample);
    else
        sample = -1 * (INT16_MIN * Sample);
    
    memblock[Iterator++] = byte[0];
    memblock[Iterator++] = byte[1];
}

inline void WaveFile::WriteSample24(double Sample, int & Iterator)
{
    int32_t sample;
    char* byte = (char*) &sample;
    
    if(Sample > 0)
        sample = (INT24_MAX * Sample);
    else
        sample = -1 * (INT24_MIN * Sample);
    
    memblock[Iterator++] = byte[0];
    memblock[Iterator++] = byte[1];
    memblock[Iterator++] = byte[2];
}

inline void WaveFile::WriteSample32(double Sample, int & Iterator)
{
    int32_t sample;
    char* byte = (char*) &sample;
    
    if(Sample > 0)
        sample = (INT32_MAX * Sample);
    else
        sample = -1 * (INT32_MIN * Sample);
    
    memblock[Iterator++] = byte[0];
    memblock[Iterator++] = byte[1];
    memblock[Iterator++] = byte[2];
    memblock[Iterator++] = byte[3];
}

#pragma mare Input Functions
// ---------------------------------------- Input Functions

bool WaveFile::OpenFileAsInt(const string & FileName)
{
    char ChunkID[4];
    char Value[4];

    uint32_t* Val32;
    uint16_t* Val16;
    
    if(InFile.is_open())
        InFile.close();
    
    InFile.flags(ios::binary);
    InFile.open(FileName);
    
    if(!InFile)
        return false;   // change to exception
    
    // -------------------- Read Header
    InFile.read(ChunkID, 4);
    Val32 = (uint32_t*)ChunkID;
    if(*Val32 != 0x46464952)      // Check for RIFF file
        return false;
    
    InFile.read(Value, 4);
    int * size = (int*)Value;
    
    InFile.read(ChunkID,4);
    Val32 = (uint32_t*)ChunkID;   // Check for WAVE format
    if(*Val32 != 0x45564157)
        return false;
    
    InFile.read(ChunkID, 4);        // Sub Chunk 1 id
    Val32 = (uint32_t*)ChunkID;   // Check for fmt  string
    if(*Val32 != 0x20746d66)
        return false;

    InFile.read(Value, 4);           // Check Format Size
    size = (int*)Value;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    if(*Val16 != 1) // Compressed Wavs Not Yet Supported
    {
        isPCM = false;
        return false;
    }
    isPCM = true;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    numChannels = *Val16;

    InFile.read(Value, 4);
    Val32 = (uint32_t*) Value;
    sampleRate = *Val32;
    
    InFile.read(Value, 4);
    Val32 = (uint32_t*) Value;
    byteRate = *Val32;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    blockAlign = *Val16;

    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    sampleSize = *Val16;

    
    if(!isPCM) // read extra header info
    {
        InFile.read(Value, 2);
        Val16 = (uint16_t*) Value;
        //InFile.read;    // Skip it for now
    }
    
    // -------------------- Process Data
    InFile.read(ChunkID, 4);
    Val32 = (uint32_t*)ChunkID;
    if(*Val32 != 0x61746164)   // Look for data
        return false;
    
    InFile.read(Value, 4);
    Val32 = (uint32_t*) Value;
    totalByteSize = *Val32;
    
    if(memblock!=nullptr)
        delete memblock;
    
    memblock = (uint8_t*)malloc(*Val32);
    
    InFile.read((char*)memblock, *Val32);
    
    InFile.close();
    
    return true;
}
    
bool WaveFile::OpenFileAsFloat(const string & FileName)
{
    char ChunkID[4];
    char Value[4];
    
    uint32_t* Val32;
    uint16_t* Val16;
    
    if(InFile.is_open())
        InFile.close();
    
    InFile.flags(ios::binary);
    InFile.open(FileName);
    
    if(!InFile)
        return false;   // change to exception
    
    // -------------------- Read Header
    InFile.read(ChunkID, 4);
    Val32 = (uint32_t*)ChunkID;
    if(*Val32 != 0x46464952)      // Check for RIFF file
        return false;
    
    InFile.read(Value, 4);
    int * size = (int*)Value;
    
    InFile.read(ChunkID,4);
    Val32 = (uint32_t*)ChunkID;   // Check for WAVE format
    if(*Val32 != 0x45564157)
        return false;
    
    InFile.read(ChunkID, 4);        // Sub Chunk 1 id
    Val32 = (uint32_t*)ChunkID;   // Check for fmt  string
    if(*Val32 != 0x20746d66)
        return false;
    
    InFile.read(Value, 4);           // Check Format Size
    size = (int*)Value;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    if(*Val16 != 1) // Compressed Wavs Not Yet Supported
    {
        isPCM = false;
        return false;
    }
    isPCM = true;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    numChannels = *Val16;
    
    InFile.read(Value, 4);
    Val32 = (uint32_t*) Value;
    sampleRate = *Val32;
    
    InFile.read(Value, 4);
    Val32 = (uint32_t*) Value;
    byteRate = *Val32;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    blockAlign = *Val16;
    
    InFile.read(Value, 2);
    Val16 = (uint16_t*) Value;
    sampleSize = *Val16;
    
    if(!isPCM) // read extra header info
    {
        InFile.read(Value, 2);
        Val16 = (uint16_t*) Value;
        //InFile.read;    // Skip it for now
    }
    
    // -------------------- Process Data
    InFile.read(ChunkID, 4);
    Val32 = (uint32_t*)ChunkID;
    if(*Val32 != 0x61746164)   // Look for data
        return false;
    
    InFile.read(Value, 4);
    Val32 = (uint32_t*) Value;
    totalByteSize = *Val32;
    
    if(fblock!=nullptr)
        delete fblock;

    totalSampleSize = totalByteSize / sampleSize * 8;
    lengthInSec =  (float)totalSampleSize / (float)sampleRate;

    //auto temp = *Val32 * 8 / sampleSize * sizeof(float);//
    
    fblock = (float*)malloc(*Val32 * 8 / sampleSize * sizeof(float));
    
    for(int i=0; i<4; i++)
        *Val32 = 0;
    
    for(int i=0; i < totalByteSize * sampleSize / 8 / sizeof(float); i++)
    {
        InFile.read(Value, sampleSize / 8);
        
        int16_t* Val = (int16_t*)Value;
        
        fblock[i] = (float)*Val / (float) INT16_MAX ;
        
    }
    
    
    
    InFile.close();
    
    return true;
}


bool WaveFile::ReadHeader()
{
    
    return true;
}

}


