/*
 *  MouseFrame.h
 *  MouseTracker
 *
 *  Created by Brett Renfer on 7/31/11.
 *  Copyright 2011 Robotconscience. All rights reserved.
 *
 */

#pragma once

#include "ofPoint.h"

class MouseFrame : public ofPoint
{
public:
	int count;
	int button;	// 0 = left, 1 = right
	int eventType;	// 0 = moved, 1 = down, 2 = up, 3 = dragged
	string timeStamp;
	
	MouseFrame(){
		count = 0;
		button = 0; 
		x = y = 0;
		eventType = 0;
	}
	
	void clear(){
		count = 0;
		button = 0; 
		x = y = 0;
		eventType = 0;
	};
};