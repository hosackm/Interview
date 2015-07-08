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
    readIndex = writeIndex = 0;
    amount = 0.0f;
    feedback = 0.0f;

    sampleRate = _sampleRate;
    buffer_length = sampleRate * _maxDelayMs / 1000;

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
    long wetIndex = readIndex - numSamples;

    /* If we went negative wrap back around the end */
    wetIndex = (wetIndex < 0) ? buffer_length + wetIndex : wetIndex;

    for(int i = 0; i < numSamples; ++i)
    {
        /* Wrap around circular buffer if needed */
        if(writeIndex == buffer_length)
        {
            writeIndex = 0;
        }
        if(wetIndex == buffer_length)
        {
            wetIndex = 0;
        }
        
        float wet = buffer[wetIndex++];
        float dry = input[i];
        float fscale = feedback / 2.0;
        buffer[writeIndex++] = fscale * wet + dry * (1.0 - fscale);
        //buffer[writeIndex++] = input[i];
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
        //output[i] = dry;
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
    amount = min(1.0f, max(0.0f, _amount));
}

void DelayLine::SetFeedback(float _feedback)
{
    feedback = min(0.9f, max(0.0f, _feedback));
}
