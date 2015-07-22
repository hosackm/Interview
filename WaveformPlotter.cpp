//
//  WaveformPlotter.cpp
//  DelayEffectGUI
//
//  Created by Matthew Hosack on 7/21/15.
//
//

#include "WaveformPlotter.h"

WaveformPlotter::WaveformPlotter()
{
    this->setPlotColor(220, 220, 0, 200);
}

void WaveformPlotter::draw(const unsigned int x
          ,const unsigned int y
          ,const unsigned int w
          ,const unsigned int h)
{
    /* Compositing so don't fill */
    ofNoFill();
    
    /* Keep any style/coordinate system that currently exists so we can revert when done */
    ofPushStyle();
    ofPushMatrix();
    /* Draw relative to our x/y */
    ofTranslate(x, y);
    
    /* Use white for label */
    ofSetColor(225);
    ofDrawBitmapString("Audio Output", 4, 18);
    
    /* 1 pixel outline for waveform plot */
    ofSetLineWidth(1);
    ofRect(0, 0, w, h);
    
    /* Set color and use wider line for audio */
    ofSetColor(color);
    ofSetLineWidth(3);
    
    /* Draw a shape representing all audio samples */
    ofBeginShape();
    for (unsigned int i = 0; i < audiobuffer.size(); i++){
        float x = ofMap(i, 0, audiobuffer.size(), 0, w, true);
        ofVertex(x, (h / 2.0f) - audiobuffer[i] * 75.0f);
    }
    ofEndShape(false);
    
    /* Pop style and coordinate system */
    ofPopMatrix();
    ofPopStyle();
}

void WaveformPlotter::setPlotColor(int r, int g, int b, int a)
{
    /* Store color internally for when we draw */
    color = ofColor(r, g, b, a);
}

void WaveformPlotter::addSamples(const float *input, const unsigned int numSamples)
{
    audiobuffer.clear();
    for(int i = 0; i < numSamples; ++i)
        audiobuffer.push_back(input[i]);
}
