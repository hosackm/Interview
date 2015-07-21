//
//  DelayEffect.cpp
//  DelayEffectAndMeter
//
//  Created by Hosack, Matthew on 7/20/15.
//
//

#include "DelayEffect.h"

int DelayEffect::addSamples(const float *input, const unsigned numSamples) {
    for (int i = 0; i < numSamples; ++i)
        cleanLine->push(input[i]);
    
    return 0;
}

int DelayEffect::getSamples(float *output, const unsigned numSamples) {
    float clean, delayed;
    
    for(int i = 0; i < numSamples; ++i)
    {
        cleanLine->pop(clean);
        delayLine->pop(delayed);
        
        output[i] = (1.0 - amount) * clean + amount * delayed;
        
        delayLine->push(output[i]);
    }

    return 0;
}
