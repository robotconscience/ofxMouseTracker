/*
 *  ofxMousePlayback.cpp
 *  MouseTracker
 *
 *  Created by Brett Renfer on 7/31/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 */

#include "ofxMousePlayback.h"

//--------------------------------------------------------------
ofxMousePlayback::ofxMousePlayback(){
	bSettingsLoaded		= false;
	currentXMLElement	= 0;
	bLooping			= false;
	nTimesLooped		= 0;
	
	ofAddListener(ofEvents.update, this, &ofxMousePlayback::update); // attach update event
};

//--------------------------------------------------------------
void ofxMousePlayback::update( ofEventArgs & e ){
	if (bPlaying){
		// see if it's time to go to the next element or not
		
		if ( ofGetElapsedTimef() - timeNodeStarted >= currentFrame.count){
			trackedMouse.pushTag("mouseTracking");{
				trackedMouse.pushTag("mouseFrame", currentXMLElement);{
					currentFrame.clear();
					currentFrame.x			= trackedMouse.getValue("mouse_x", currentFrame.x);
					currentFrame.y			= trackedMouse.getValue("mouse_y", currentFrame.y);
					currentFrame.button		= trackedMouse.getValue("button", currentFrame.button);
					currentFrame.count		= trackedMouse.getValue("seconds_at_position", currentFrame.count);
					currentFrame.eventType	= trackedMouse.getValue("type", currentFrame.eventType);
					currentFrame.timeStamp	= trackedMouse.getValue("time", currentFrame.timeStamp);
				} trackedMouse.popTag();
			}; trackedMouse.popTag();
			
			timeNodeStarted = ofGetElapsedTimef();
			
			currentXMLElement++;
			
			cout<<currentXMLElement<<endl;
			
			// at the end of the XML
			if ( currentXMLElement >= numMouseFrames){
				if (bLooping){
					nTimesLooped++;
					currentXMLElement = 0;
				} else {
					bPlaying = false;
					return;
				}
			};
		}
	}
};

//--------------------------------------------------------------
bool ofxMousePlayback::loadSettings( string filename ){
	bSettingsLoaded = trackedMouse.loadFile( filename );
	if (!bSettingsLoaded) ofLog (OF_LOG_WARNING, "settings did not load! check your filename");
	
	trackedMouse.pushTag("mouseTracking");{
		numMouseFrames = trackedMouse.getNumTags("mouseFrame");
	} trackedMouse.popTag();
	originalResolution.x = trackedMouse.getValue("mouseTracking:info:resolution_x", 0);
	originalResolution.y = trackedMouse.getValue("mouseTracking:info:resolution_y", 0);
	currentXMLElement	= 0;
	nTimesLooped		= 0;
	
	return bSettingsLoaded;
};

//--------------------------------------------------------------
// playback begin / pause / resume
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofxMousePlayback::startPlayback(){
	if (!bSettingsLoaded){
		ofLog(OF_LOG_WARNING, "No mouse file loaded! Aborting");
		return;
	}
	if (bPlaying) ofLog(OF_LOG_WARNING, "playback already started!");
	bPlaying = true;
	
	// get ready for next node
	timeNodeStarted = ofGetElapsedTimef();
};

//--------------------------------------------------------------
void ofxMousePlayback::stopPlayback(){
	if (!bSettingsLoaded){
		ofLog(OF_LOG_WARNING, "No mouse file loaded! Aborting");
		return;
	}
	if (!bPlaying) ofLog(OF_LOG_WARNING, "playback already stopped!");
	bPlaying = false;
};	

//--------------------------------------------------------------
void ofxMousePlayback::restartPlayback(){
	if (!bSettingsLoaded){
		ofLog(OF_LOG_WARNING, "No mouse file loaded! Aborting");
		return;
	}
	currentXMLElement	= 0;
	bPlaying = true;
	
	// get ready for next node
	timeNodeStarted = ofGetElapsedTimef();
};	

//--------------------------------------------------------------
// Properties
//--------------------------------------------------------------

void ofxMousePlayback::setLoop( bool bLoop){
	bLooping = bLoop;
};

int ofxMousePlayback::getNumLoops(){
	return nTimesLooped;
};

int	ofxMousePlayback::getNumMouseFrames(){
	return numMouseFrames;
};

ofPoint ofxMousePlayback::getOriginalResolution(){
	return originalResolution;
}

float ofxMousePlayback::getCurrentElapsedTime(){
	return ofGetElapsedTimef() - timeNodeStarted;
}

//--------------------------------------------------------------
// all-important function
//--------------------------------------------------------------

MouseFrame * ofxMousePlayback::getCurrentMouseFrame(){
	if (!bSettingsLoaded) ofLog(OF_LOG_WARNING, "returning dummy element! no mouse tracking file loaded");
	return &currentFrame;
};