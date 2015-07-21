#include "ofApp.h"

#define DELDEFAULT 0.3
#define DTIMEDEFAULT 100

PeakMeter *meter;
ofxPanel gui;
ofxFloatSlider damount;
ofxIntSlider dtime;

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    
    gui.add(damount.setup("wet/dry", DELDEFAULT, 0.0, 0.99, 200, 20));
    gui.add(dtime.setup("delay(ms)", DTIMEDEFAULT, 0, 1000, 200, 20));
    
    damount.addListener(this, &ofApp::delayUpdated);
    dtime.addListener(this, &ofApp::delayTimeUpdated);
    
    delay = new DelayEffect(1000, 48000);
    delay->setDelay(DTIMEDEFAULT);
    delay->setAmount(DELDEFAULT);
    
    meter = new PeakMeter();
    
    stream.setup(this, 2, 1, 48000, 512, 4);
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    meter->draw(400, 20, 10, 100);
}

//--------------------------------------------------------------
void ofApp::exit(){
    damount.removeListener(this, &ofApp::delayUpdated);
    dtime.removeListener(this, &ofApp::delayTimeUpdated);
}


//--------------------------------------------------------------
void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    delay->addSamples(input, bufferSize);
}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    float *tmp = new float[bufferSize];
    
    delay->getSamples(tmp, bufferSize);

    for(int i = 0; i < bufferSize; ++i)
    {
        output[2*i] = tmp[i];
        output[2*i+1] = tmp[i];
    }
    
    meter->AddSamples(tmp, bufferSize);
    
    delete [] tmp;
}

void ofApp::delayTimeUpdated(int & time){
    delay->setDelay(time);
}

void ofApp::delayUpdated(float & amount){
    delay->setAmount(amount);
}
