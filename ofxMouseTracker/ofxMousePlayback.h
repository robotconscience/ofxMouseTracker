/*
 *  ofxMousePlayback.h
 *  MouseTracker
 *
 *  Created by Brett Renfer on 7/31/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 */

#pragma once

#include "MouseFrame.h"
#include "ofxXmlSettings.h"

class ofxMousePlayback
{
public:
	
	// setup
	ofxMousePlayback();
	void update( ofEventArgs & e );
	bool loadSettings( string filename );
	
	// playback begin / pause / resume
	
	void startPlayback();	// start/resumes playback
	void stopPlayback();	// pauses playback
	void restartPlayback();	// starts playback from item 0
	
	// properties
	void setLoop( bool bLoop);		 // do we loop endlessly?
	int getNumLoops();
	int	getNumMouseFrames();		 // how many total mouse frames do we have?
	ofPoint getOriginalResolution(); // since points are normalized (0-1) to original resolution, make it easy to see what that was
	float getCurrentElapsedTime();
	
	// all-important function
	MouseFrame * getCurrentMouseFrame();
	
private:
	
	bool			bSettingsLoaded;
	ofxXmlSettings	trackedMouse;
	
	bool			bLooping;
	int				nTimesLooped;
	bool			bPlaying;
	
	int				numMouseFrames; 
	ofPoint			originalResolution;
	
	int				currentXMLElement;
	MouseFrame		currentFrame;
	
	// util
	float			timeNodeStarted;
};