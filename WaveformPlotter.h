//
//  WaveformPlotter.h
//  DelayEffectGUI
//
//  Created by Matthew Hosack on 7/21/15.
//
//

#ifndef __DelayEffectGUI__WaveformPlotter__
#define __DelayEffectGUI__WaveformPlotter__

#include <vector>
#include "ofMain.h"

class WaveformPlotter {

public:
    WaveformPlotter();
    void draw(const unsigned int x
              ,const unsigned int y
              ,const unsigned int w
              ,const unsigned int h);
    void setPlotColor(int r, int g, int b, int a);
    void addSamples(const float *input, const unsigned int numSamples);

private:
    std::vector<float> audiobuffer;
    ofColor color;
};

#endif /* defined(__DelayEffectGUI__WaveformPlotter__) */
