//
//  PeakMeter.h
//  DelayEffectGui
//
//  Created by Hosack, Matthew on 7/20/15.
//
//

#ifndef __DelayEffectGui__PeakMeter__
#define __DelayEffectGui__PeakMeter__

#include <vector>

class PeakMeter
{
    
    /* Local data type to keep track the time samples were added */
    struct TimedSample
    {
        /* Level */
        float value;
        /* Timestamp when this value was added in milliseconds */
        unsigned long long timestamp;
    };
    
public:
    PeakMeter(const unsigned int _retainTimeMillis = 1000);
    
    /* Add a number of samples to the PeakMeter */
    void addSamples(float *samples, const unsigned int numSamples);
    /* Get Peak Hold */
    float getPeakHold();
    /* Get Current Peak */
    float getCurrentPeak();
    /* Draw PeakMeter at Point(w, h) */
    void draw(const unsigned int w, const unsigned int h, const unsigned x, const unsigned y);
    
private:
    /* return true if TimedSample is greater than retainTimeMillis */
    bool isExpired(TimedSample s);
    /* Most recent peak value added */
    float current_peak;
    /* Store samples for later */
    std::vector<struct TimedSample> samples;
    /* Amount of time to retain samples */
    unsigned long retainTimeMillis;
};

#endif /* defined(__DelayEffectGui__PeakMeter__) */
