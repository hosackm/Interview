#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(24, 24, 24);
    
    stream.setup(this, 1, 1, 48000, 512, 4);
    meter = new PeakMeter(1000);
    delay = new DelayLine(48000, 1000);
    delay->SetDelay(750);
    delay->SetAmount(0.5);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    meter->draw(200, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioIn(float * input, int bufferSize, int nChannels)
{
    delay->AddSamples(input, bufferSize);
}

void ofApp::audioOut(float *output, int bufferSize, int nChannels)
{
    float *tmp = new float[bufferSize];
    
    delay->GetSamples(tmp, bufferSize);
    meter->AddSamples(tmp, bufferSize);
    
    for(int i = 0; i < bufferSize; ++i)
    {
        output[i] = tmp[i];
    }
    
    delete tmp;
}

ofApp::~ofApp()
{
    delete meter;
    delete delay;
}
