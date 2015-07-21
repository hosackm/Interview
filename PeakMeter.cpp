//
//  PeakMeter.cpp
//  DelayEffectGui
//
//  Created by Hosack, Matthew on 7/20/15.
//
//

#include "PeakMeter.h"

PeakMeter::PeakMeter(unsigned int _retainTimeMillis)
{
    retainTimeMillis = _retainTimeMillis;
    current_peak = 0.0f;
}

/* Add a number of samples to the PeakMeter */
void PeakMeter::AddSamples(float *input, const unsigned int numSamples)
{
    /* Find max value in buffer */
    float max = 0.0f;
    for(int i = 0; i < numSamples; ++i)
    {
        max = (abs(input[i]) > max) ? abs(input[i]) : max;
    }
    
    /* Store current peak */
    current_peak = max;
    /* Use max value and current time */
    struct TimedSample s = {
        .value = max,
        .timestamp = ofGetElapsedTimeMillis()
    };
    /* Push into vector */
    samples.push_back(s);
}

/* Get Peak Hold */
float PeakMeter::GetPeakHold()
{
    if(samples.size() == 0)
        return 0.0f;
    
    float max = 0.0f;
    vector<TimedSample>::iterator it;
    
    for(it = samples.begin(); it != samples.end(); ++it)
    {
        /* Remove samples that have expired */
        if(isExpired(*it)){
            samples.erase(it);
            /* Don't consider for max */
            continue;
        }
        
        /* If it's the larger than max, store it */
        if(abs(it->value) > max)
        {
            max = abs(it->value);
        }
    }
    
    return max;
}

float PeakMeter::GetCurrentPeak()
{
    return current_peak;
}

/* Draw PeakMeter with width w and height h */
void PeakMeter::draw(const unsigned int w, const unsigned int h, const unsigned x, const unsigned y)
{
    //float startx = 70;
    //float starty = 70;
    float startx = x;
    float starty = y;
    
    /* For some reason RtAudio is providing values between -2.0 and 2.0 */
    float hold = abs(this->GetPeakHold()) / 2.0 * w;
    float cur = abs(current_peak) / 2.0;
    
    /* White border */
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofRect(startx, starty, w, h);
    
    /* Clamp hold while you investigate inconsistent RtAudio values */
    hold = (hold < 0.0) ? 0.0 : hold;
    hold = (hold > w) ? w : hold;
    
    /* Green for current level bar */
    ofSetColor(20, 200, 20);
    ofFill();
    ofRect(startx, starty, w * cur, h);
    
    /* Red for Peak Hold */
    ofSetColor(200, 20, 20);
    ofLine(startx + hold, starty, startx + hold, starty + h);
}

bool PeakMeter::isExpired(TimedSample s)
{
    return (ofGetElapsedTimeMillis() - s.timestamp) > retainTimeMillis;
}