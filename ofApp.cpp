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
    
    gui.add(damount.setup("delay amount", DELDEFAULT, 0.0, 1.0, 200, 20));
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
void ofApp::update(){

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
