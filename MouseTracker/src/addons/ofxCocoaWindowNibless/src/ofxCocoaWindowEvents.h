/*
 *  ofxCocoaWindowEvents.h
 *  MouseTracker
 *
 *  Created by Brett Renfer on 7/31/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"

class ofxCocoaWindowEvents {
public:
	ofEvent<ofMouseEventArgs> 	mouseMovedOutsideEvent;
};

extern ofxCocoaWindowEvents cocoaEvents;

void notifyMovedMouseOutsideEvent( int x, int y );