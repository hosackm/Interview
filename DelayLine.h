//
//  DelayLine.h
//  Interview
//
//  Created by Matthew Hosack on 7/7/15.
//
//

#ifndef __Interview__DelayLine__
#define __Interview__DelayLine__

#include "ofMain.h"

class DelayLine
{

public:
    /* Create a Delay Line based on sampleRate and the maximum delay needed */
    DelayLine(const unsigned int _sampleRate, const unsigned int _maxDelayMs);
    ~DelayLine();
    
    void AddSamples(const float *input, const unsigned int numSamples);
    void GetSamples(float *output, const unsigned int numSamples);
    void SetDelay(const unsigned int delayMs);
    void SetAmount(float _amount);

private:
    unsigned int sampleRate;
    unsigned long buffer_length;
    unsigned long readIndex;
    unsigned long writeIndex;
    float amount;
    float *buffer;
};

#endif /* defined(__Interview__DelayLine__) */
