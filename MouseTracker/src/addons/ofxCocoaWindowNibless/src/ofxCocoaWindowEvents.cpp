/*
 *  ofxCocoaWindowEvents.cpp
 *  MouseTracker
 *
 *  Created by Brett Renfer on 8/1/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 */

#include "ofxCocoaWindowEvents.h"

ofxCocoaWindowEvents cocoaEvents;

void notifyMovedMouseOutsideEvent( int x, int y ){
	static ofMouseEventArgs	mouseEventArgs;
	mouseEventArgs.x = x;
	mouseEventArgs.y = y;
	mouseEventArgs.button = 4;
	
	ofNotifyEvent(cocoaEvents.mouseMovedOutsideEvent, mouseEventArgs); 
}