//
//  PeakMeter.h
//  Interview
//
//  Created by Matthew Hosack on 7/7/15.
//
//

#ifndef __Interview__PeakMeter__
#define __Interview__PeakMeter__

#include "OfMain.h"

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
    void AddSamples(float *samples, const unsigned int numSamples);
    /* Get Peak Hold */
    float GetPeakHold();
    /* Get Current Peak */
    float GetCurrentPeak();
    /* Draw PeakMeter at Point(w, h) */
    void draw(const unsigned int w, const unsigned int h);

private:
    /* return true if TimedSample is greater than retainTimeMillis */
    bool isExpired(TimedSample s);
    /* Most recent peak value added */
    float current_peak;
    /* Store samples for later */
    vector<struct TimedSample> samples;
    /* Amount of time to retain samples */
    unsigned long retainTimeMillis;
};

#endif /* defined(__Interview__PeakMeter__) */
