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

/* Only handles 1 channel of audio.  Will update to handle interleaved Stereo. */
class DelayLine
{
    /*
     *                         +--------+
     *     input --->( + ) --->| Buffer |--->( + )----> output
     *                 |       +--------+      |
     *                 |                       |
     *                 +-----------------------+
     */
public:
    /* Create a Delay Line based on sampleRate and the maximum delay needed */
    DelayLine(const unsigned int _sampleRate, const unsigned int _maxDelayMs);
    ~DelayLine();
    
    /* Add numSamples to DelayLine */
    void AddSamples(const float *input, const unsigned int numSamples);
    /* Get numSamples from DelayLine */
    void GetSamples(float *output, const unsigned int numSamples);
    /* Update the time delay in milliseconds */
    void SetDelay(const unsigned int delayMs);
    /* Update the Wet Dry amount from 0.0 to 1.0 */
    void SetAmount(float _amount);
    /* Update the Feedback amount from 0.0 to 0.9 */
    void SetFeedback(float _feedback);

private:
    unsigned int sampleRate;    /* Sample Rate for calculating delay length */
    unsigned long buffer_length;/* Length of buffer in samples */
    unsigned long readIndex;    /* Read Index for accessing time delayed samples */
    unsigned long writeIndex;   /* Write Index to add most recently acquired samples */
    float amount;               /* Wet/Dry amount 0.0 - 1.0 */
    float feedback;             /* Feedback amount 0.0 - 0.9 (Not Implemented) */
    float *buffer;              /* Sample Buffer */
};

#endif /* defined(__Interview__DelayLine__) */
