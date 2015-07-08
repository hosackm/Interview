//
//  DelayLine.cpp
//  Interview
//
//  Created by Matthew Hosack on 7/7/15.
//
//

#include "DelayLine.h"

DelayLine::DelayLine(const unsigned int _sampleRate, const unsigned int _maxDelayMs)
{
    sampleRate = _sampleRate;
    buffer_length = sampleRate * _maxDelayMs / 1000;
    buffer = new float[buffer_length];
    for(int i = 0; i < buffer_length; ++i)
        buffer[i] = 0.0f;
    readIndex = writeIndex = 0;
    amount = 0.0f;
}

DelayLine::~DelayLine()
{
    delete buffer;
}

void DelayLine::AddSamples(const float* input, const unsigned int numSamples)
{
    for(int i = 0; i < numSamples; ++i)
    {
        if(writeIndex == (buffer_length - 1))
        {
            writeIndex = 0;
        }
        buffer[writeIndex++] = input[i];
    }
}

void DelayLine::GetSamples(float *output, const unsigned int numSamples)
{
    for(int i = 0; i < numSamples; ++i)
    {
        if(readIndex == (buffer_length - 1))
        {
            readIndex = 0;
        }
        output[i] = amount * buffer[readIndex++];
    }
}

void DelayLine::SetDelay(const unsigned int delayMs)
{
    unsigned int numSamples = delayMs * sampleRate / 1000;
    numSamples  = (numSamples > buffer_length) ? buffer_length -1 : numSamples;

    writeIndex = readIndex + numSamples;
}

void DelayLine::SetAmount(float _amount)
{
    _amount = (_amount < 0.0) ? 0.0 : _amount;
    _amount = (_amount > 1.0) ? 1.0 : _amount;
    amount = _amount;
}
