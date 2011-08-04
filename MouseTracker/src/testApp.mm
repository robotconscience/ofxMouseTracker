

#include "testApp.h"

//--------------------------------------------------------------
testApp::~testApp(){
	if (mouseTracker.isRecording()) mouseTracker.stopRecording();
};

void testApp::exit(){
	//if (bRecording) stopRecording();
};

//--------------------------------------------------------------
void testApp::setup() {
	ofBackground(0, 0, 0);
	
	cocoaWindow->setUpdateRate(0);
	cocoaWindow->setWindowLevel(-1);
	
	// annoying, but simple to do 
	mouseTracker.setWindow(cocoaWindow);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	
	if (mouseTracker.isRecording()) ofBackground(0,200,0);
	else ofBackground(200,0,0);
	
	// instructions
	ofDrawBitmapString("MouseTracker: track your mouse movements and presses!", 20,20);
	ofDrawBitmapString("Press 'r' to start/stop recording", 20,35);
	ofDrawBitmapString("current framerate: "+ofToString(ofGetFrameRate(), 3), 20,50);
	
	// feedback
	
	if (mouseTracker.isRecording()){
		ofDrawBitmapString("currently recording!", 20,65);
		ofDrawBitmapString("recorded "+ofToString(mouseTracker.getNumFramesRecorded())+" frames", 20,80);
		ofDrawBitmapString("CURRENT FRAME", 20, 115);
		ofDrawBitmapString("position: "+ofToString(mouseTracker.getCurrentFrame()->x)+","+ofToString(mouseTracker.getCurrentFrame()->y), 20, 130);
		ofDrawBitmapString("time: "+ofToString(mouseTracker.getCurrentFrame()->count / ofGetFrameRate()), 20, 145);
	} else {
		ofDrawBitmapString("not recording.", ofPoint(20,65));
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f'){
		ofToggleFullscreen();
	} else if ( key == 'r' || key == 'R' ){
		if (mouseTracker.isRecording()){
			mouseTracker.stopRecording();
		} else {
			mouseTracker.startRecording();
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}