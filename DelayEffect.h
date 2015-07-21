//
//  DelayEffect.h
//  DelayEffectAndMeter
//
//  Created by Hosack, Matthew on 7/20/15.
//
//

#ifndef __DelayEffectAndMeter__DelayEffect__
#define __DelayEffectAndMeter__DelayEffect__

#include "ofMain.h"
#include "DelayLine.h"

//#include <pthread.h>
#include <boost/atomic/atomic.hpp>

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

class DelayEffect {
    
    boost::atomic<double> amount; /* amount of delay effect (0.-1.) */
    boost::atomic<unsigned long> delayMillis; /* delaytime in milliseconds */
    
    /* Internal Audio Buffers */
    DelayLine<float> *delayLine;
    DelayLine<float> *cleanLine;

public:
    DelayEffect(const unsigned _maxLengthMillis, const unsigned long _sr)
    {
        amount = 0.0f;
        delayMillis = 0;

        /* make buffers. just force clean to be same length as delay */
        delayLine = new DelayLine<float>(_maxLengthMillis, _sr);
        cleanLine = new DelayLine<float>(_maxLengthMillis, _sr);
    }
    
    int setAmount(const double am){
        /* Force amount to be within 0 and 1 */
        amount = max(min(1.0f, am), 0.0f);
    }

    int setDelay(const unsigned long delayMS){
        delayLine->setDelay(delayMS);
    }
    
    /* Prototypes for I/O */
    int addSamples(const float *input, const unsigned numSamples);
    int getSamples(float *output, const unsigned numSamples);
};

#endif /* defined(__DelayEffectAndMeter__DelayEffect__) */
