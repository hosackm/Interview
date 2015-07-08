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
    readIndex = writeIndex = 0;
    amount = 0.0f;
    buffer = new float[buffer_length];
    for(int i = 0; i < buffer_length; ++i)
        buffer[i] = 0.0f;
}

DelayLine::~DelayLine()
{
    delete buffer;
}

void DelayLine::AddSamples(const float* input, const unsigned int numSamples)
{
    /* Add samples to DelayLine at writeIndex */
    for(int i = 0; i < numSamples; ++i)
    {
        /* Wrap around circular buffer if needed */
        if(writeIndex == buffer_length)
        {
            writeIndex = 0;
        }
        buffer[writeIndex++] = input[i];
    }
}

void DelayLine::GetSamples(float *output, const unsigned int numSamples)
{
    /* Use most recent samples written to writeIndex as Dry Signal */
    long dryIndex = writeIndex - numSamples;
    if(dryIndex < 0)
    {
        dryIndex = buffer_length + dryIndex;
    }

    for(int i = 0; i < numSamples; ++i)
    {
        if(readIndex == buffer_length)
        {
            readIndex = 0;
        }
        if (dryIndex == buffer_length) {
            dryIndex = 0;
        }
        
        /* Scale Wet and Dry by amount and add both */
        float wet = buffer[readIndex++];
        float dry = buffer[dryIndex++];
        output[i] = amount * wet + (1.0 - amount) * dry;
    }
}

void DelayLine::SetDelay(const unsigned int delayMs)
{
    unsigned int numSamples = delayMs * sampleRate / 1000.;
    numSamples  = (numSamples >= buffer_length) ? buffer_length - 1 : numSamples;

    writeIndex = readIndex + numSamples;
}

void DelayLine::SetAmount(float _amount)
{
    _amount = (_amount < 0.0) ? 0.0 : _amount;
    _amount = (_amount > 1.0) ? 1.0 : _amount;
    amount = _amount;
}
