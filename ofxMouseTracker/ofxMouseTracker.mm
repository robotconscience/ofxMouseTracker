/*
 *  ofxMouseTracker.cpp
 *  MouseTracker
 *
 *  Created by Brett Renfer on 7/31/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 */

#include "ofxMouseTracker.h"

//--------------------------------------------------------------
// set defaults
//--------------------------------------------------------------

ofxMouseTracker::ofxMouseTracker(){
	bRecording = false;
	bFirstFrame = true;
	numFramesRecorded = 0;
	bWindowSet = false;
}

void ofxMouseTracker::setWindow( ofxCocoaWindowNibless * _window ){
	window = _window;
	bWindowSet = true;
};

//--------------------------------------------------------------
// get properties
//--------------------------------------------------------------
bool ofxMouseTracker::isRecording(){
	return bRecording;
}

//--------------------------------------------------------------
string ofxMouseTracker::getCurrentFileName(){
	return currentFileName;
}

//--------------------------------------------------------------
MouseFrame* ofxMouseTracker::getCurrentFrame(){
	return &currentFrame;
}

//--------------------------------------------------------------
int ofxMouseTracker::getNumFramesRecorded(){
	return numFramesRecorded;
};

//--------------------------------------------------------------
void ofxMouseTracker::startRecording(){
	if (!bWindowSet) ofLog (OF_LOG_ERROR, "YOU HAVE NOT ATTACHED THE WINDOW OBJECT. Please call setWindow( window )");
	if (bRecording) return;
	
	numFramesRecorded = 0; // reset total number of frames recorded
	
	// make nice unique file name in case we want to do this a bunch
	currentFileName = "mouse_"+ofToString(ofGetDay())+ofGetTimestampString()+".xml";
	window->setCaptureExternalMouseEvents(true); // add listener for all external mouse events
	output.clear();
	output.addTag("mouseTracking");
	
	output.pushTag("mouseTracking");{
		// add some nice data
		output.addTag("info");
		output.pushTag("info");{
			output.addValue("date", ofToString(ofGetDay())+"/"+ofToString(ofGetMonth())+"/"+ofToString(ofGetYear()));
			output.addValue("time_started", ofToString(ofGetHours())+":"+ofToString(ofGetMinutes())+":"+ofToString(ofGetSeconds()));
			output.addValue("resolution_x", ofGetScreenWidth());
			output.addValue("resolution_y", ofGetScreenHeight());
		} output.popTag();
	} output.popTag();
	
	registerMouseOutsideEvents(this);	// attach ofxCocoaWindowEvents
	ofRegisterMouseEvents(this);		// attach mouse OF events
	ofAddListener(ofEvents.update, this, &ofxMouseTracker::update); // attach update event
	
	bRecording = true;
};

//--------------------------------------------------------------
void ofxMouseTracker::stopRecording(){
	if (!bRecording) return;
	
	recordMouseFrame(); // record last frame!
	
	// record time ended
	
	output.pushTag("mouseTracking");{
		output.pushTag("info");{
			output.addValue("time_stopped", ofToString(ofGetHours())+":"+ofToString(ofGetMinutes())+":"+ofToString(ofGetSeconds()));
		} output.popTag();
	} output.popTag();
	
	bRecording = false;
	output.saveFile(currentFileName);
	ofLog( OF_LOG_VERBOSE, "Saving to file "+currentFileName);
	window->setCaptureExternalMouseEvents(false); // remove listener for all external mouse events
	unregisterMouseOutsideEvents(this); // detach mouse events
	ofUnregisterMouseEvents(this);		// detach mouse OF events
	ofRemoveListener(ofEvents.update, this, &ofxMouseTracker::update); // remove update event
};

//--------------------------------------------------------------
void ofxMouseTracker::update( ofEventArgs & e ){
	// increment "count" of current frame
	// why? because if the mouse hasn't moved, we won't get any 
	if (bRecording && !bFirstFrame){
		currentFrame.count++;
	}
}

//--------------------------------------------------------------
void ofxMouseTracker::recordMouseFrame(){
	if (!bFirstFrame){ // throw away first frame, a.k.a. before you've gotten any mouse data
		numFramesRecorded++;
		
		output.pushTag("mouseTracking");{
			output.addTag("mouseFrame");
			
			// push to newest tag
			output.pushTag("mouseFrame", output.getNumTags("mouseFrame")-1 ); {
				output.addValue("mouse_x", (float) currentFrame.x / ofGetScreenWidth());
				output.addValue("mouse_y", (float) currentFrame.y / ofGetScreenHeight());
				output.addValue("button", currentFrame.button);
				output.addValue("seconds_at_position", currentFrame.count / ofGetFrameRate()); // make count be in seconds
				output.addValue("type", currentFrame.eventType);
				output.addValue("time", ofGetTimestampString()); // what time did we record this frame? could be cool...
			}; output.popTag();
			
		} output.popTag();
	}
	
	bFirstFrame = false;
}


//--------------------------------------------------------------
// UTILS for setting up current frames
//--------------------------------------------------------------

void ofxMouseTracker::setupLocalMouse(int x, int y, int button){
	currentFrame.clear();
	currentFrame.x		= x;
	currentFrame.y		= y;
	currentFrame.button	= button;
	
	// coords are relative to the window, so offset
	currentFrame.x += ofGetWindowPositionX();
	currentFrame.y += ofGetWindowPositionY();
	
};

//--------------------------------------------------------------
void ofxMouseTracker::setupOutsideMouse(int x, int y, int button){
	currentFrame.clear();
	currentFrame.x		= x;
	currentFrame.y		= y;
	currentFrame.button	= button;
};

//--------------------------------------------------------------
// MOUSE LISTENERS
//--------------------------------------------------------------

void ofxMouseTracker::mouseMoved( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupLocalMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 0; // moved
}

//--------------------------------------------------------------
void ofxMouseTracker::mousePressed( ofMouseEventArgs & e ){	
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupLocalMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 1; // pressed
};

//--------------------------------------------------------------
void ofxMouseTracker::mouseDragged( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupLocalMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 3; // dragged
};

//--------------------------------------------------------------
void ofxMouseTracker::mouseReleased( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupLocalMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 2; // released
};

//--------------------------------------------------------------
void ofxMouseTracker::mouseMovedOutside( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupOutsideMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 0; // moved
};

//--------------------------------------------------------------
void ofxMouseTracker::mouseDraggedOutside( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupOutsideMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 3; // dragged
};

//--------------------------------------------------------------
void ofxMouseTracker::mousePressedOutside( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupOutsideMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 1; // pressed
};

//--------------------------------------------------------------
void ofxMouseTracker::mouseReleasedOutside( ofMouseEventArgs & e ){
	if (!bRecording) return;
	
	// add last position + create new frame
	
	recordMouseFrame();
	setupOutsideMouse(e.x,e.y,e.button);
	currentFrame.eventType	= 3; // released
};