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
	ofEvent<ofMouseEventArgs> 	mousePressedOutsideEvent;
	ofEvent<ofMouseEventArgs> 	mouseDraggedOutsideEvent;
	ofEvent<ofMouseEventArgs> 	mouseReleasedOutsideEvent;
};

extern ofxCocoaWindowEvents cocoaEvents;

void notifyMouseMovedOutside( int x, int y );
void notifyMousePressedOutside( int x, int y, int button );
void notifyMouseDraggedOutside( int x, int y, int button );
void notifyMouseReleasedOutside( int x, int y, int button );

template<class ListenerClass>
void registerMouseOutsideEvents(ListenerClass * listener){
	ofAddListener(cocoaEvents.mouseDraggedOutsideEvent,listener,&ListenerClass::mouseDraggedOutside);
	ofAddListener(cocoaEvents.mouseMovedOutsideEvent,listener,&ListenerClass::mouseMovedOutside);
	ofAddListener(cocoaEvents.mousePressedOutsideEvent,listener,&ListenerClass::mousePressedOutside);
	ofAddListener(cocoaEvents.mouseReleasedOutsideEvent,listener,&ListenerClass::mouseReleasedOutside);
}

template<class ListenerClass>
void unregisterMouseOutsideEvents(ListenerClass * listener){
	ofRemoveListener(cocoaEvents.mouseDraggedOutsideEvent,listener,&ListenerClass::mouseDraggedOutside);
	ofRemoveListener(cocoaEvents.mouseMovedOutsideEvent,listener,&ListenerClass::mouseMovedOutside);
	ofRemoveListener(cocoaEvents.mousePressedOutsideEvent,listener,&ListenerClass::mousePressedOutside);
	ofRemoveListener(cocoaEvents.mouseReleasedOutsideEvent,listener,&ListenerClass::mouseReleasedOutside);
}