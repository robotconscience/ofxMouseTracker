/*
 *  ofxMouseTracker.h
 *  MouseTracker
 *
 *  Created by Brett Renfer on 7/31/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 
 *	Right now: requires a modified version of ofxCocoaWindowNibless
 *	based on the version by shawn lawson (orig source here: https://github.com/shawnlawson/ofxCocoaWindowNibless)
 *	as well as ofxXmlSettings
 */

#pragma once

#include "MouseFrame.h"
#include "ofxXmlSettings.h"
#include "ofxCocoaWindowNibless.h"

class ofxMouseTracker
{
public:
	
	ofxMouseTracker();
	
	// weird way we're keeping track of the window now
	void setWindow( ofxCocoaWindowNibless * _window );
	
	// start/stop recording
	void recordMouseFrame();
	void startRecording();
	void stopRecording();
	
	// get properties
	bool		isRecording();
	string		getCurrentFileName();
	MouseFrame* getCurrentFrame();
	int			getNumFramesRecorded();
	
	// of event listeners
	void update( ofEventArgs & e);
	void mouseMovedOutside( ofMouseEventArgs & e);
	void mouseMoved( ofMouseEventArgs & e );
	void mouseDragged( ofMouseEventArgs & e );
	void mousePressed( ofMouseEventArgs & e );
	void mouseReleased( ofMouseEventArgs & e );
	
	
	
private:
	
	bool bWindowSet;
	ofxCocoaWindowNibless * window;
	
	//utils
	bool bFirstFrame;
	int numFramesRecorded;
	
	// output
	bool bRecording;
	MouseFrame		currentFrame;
	ofxXmlSettings	output;
	
	string currentFileName;
};