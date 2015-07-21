#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "DelayEffect.h"
#include "PeakMeter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        void exit();
    
        void feedbackUpdated(float & amount);
        void delayTimeUpdated(int & time);
        void delayUpdated(float & amount);
    
        void audioIn(float *input, int bufferSize, int nChannels);
        void audioOut(float *output, int bufferSize, int nChannels);
		
        ofSoundStream stream; /*  */
        DelayEffect *delay;



//------------------ Unused OpenFrameworks function stubs ------------------
        void update(){}
        void keyPressed(int key){}
        void keyReleased(int key){}
        void mouseMoved(int x, int y ){}
        void mouseDragged(int x, int y, int button){}
        void mousePressed(int x, int y, int button){}
        void mouseReleased(int x, int y, int button){}
        void windowResized(int w, int h){}
        void dragEvent(ofDragInfo dragInfo){}
        void gotMessage(ofMessage msg){}
};
