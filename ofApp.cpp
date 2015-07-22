#include "ofApp.h"

/* Default to mild slapback delay */
#define DELDEFAULT 0.3
#define DTIMEDEFAULT 100

/* Global Variables */
PeakMeter *meter;
ofxPanel gui;
ofxFloatSlider damount;
ofxIntSlider dtime;

//--------------------------------------------------------------
void ofApp::setup(){
    /* Good gray color to visualize the PeakMeter and Waveform on top of */
    ofBackground(60, 60, 60);
    
    /* Instantiate Wave Plotter */
    plotter = new WaveformPlotter;
    plotter->setPlotColor(20, 200, 20, 255);
    
    /* Setup GUI */
    gui.setup();
    gui.add(damount.setup("wet/dry", DELDEFAULT, 0.0, 0.99, 200, 20));
    gui.add(dtime.setup("delay(ms)", DTIMEDEFAULT, 0, 1000, 200, 20));
    
    damount.addListener(this, &ofApp::delayUpdated);
    dtime.addListener(this, &ofApp::delayTimeUpdated);
    
    /* Setup Delay Effect */
    delay = new DelayEffect(1000, 48000);
    delay->setDelay(DTIMEDEFAULT);
    delay->setAmount(DELDEFAULT);
    
    /* Setup Peak Meter */
    meter = new PeakMeter();
    
    /* Setup RtAudio Sound Streamer */
    stream.setup(this, 2, 1, 48000, 512, 4);
}

//--------------------------------------------------------------
void ofApp::draw(){
    /* Draw GUI, Meter, and Waveform */
    gui.draw();
    meter->draw(400, 20, 10, 100);
    plotter->draw(10, 200, 600, 300);
}

//--------------------------------------------------------------
void ofApp::exit(){
    /* Remove listeners */
    damount.removeListener(this, &ofApp::delayUpdated);
    dtime.removeListener(this, &ofApp::delayTimeUpdated);
}


//--------------------------------------------------------------
void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    /* Add samples directly to delay effect. We'll plot and meter it's output */
    delay->addSamples(input, bufferSize);
}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    /* Allocate some temporary floats to store audio */
    float *tmp = new float[bufferSize];
    
    /* Get the output from the Delay and put in tmp */
    delay->getSamples(tmp, bufferSize);

    /* Copy the mono output to stereo output buffer */
    for(int i = 0; i < bufferSize; ++i)
    {
        output[2*i] = tmp[i];
        output[2*i+1] = tmp[i];
    }
    
    /* Add samples to the meter and plotter */
    meter->addSamples(tmp, bufferSize);
    plotter->addSamples(tmp, bufferSize);
    
    delete [] tmp;
}

void ofApp::delayTimeUpdated(int & time){
    /* update delay time with GUI value */
    delay->setDelay(time);
}

void ofApp::delayUpdated(float & amount){
    /* update delay amount with GUI value */
    delay->setAmount(amount);
}

ofApp::~ofApp()
{
    /* free dynamically allocate variables */
    delete plotter;
    delete delay;
    delete meter;
}
