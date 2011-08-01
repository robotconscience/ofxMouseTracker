/*
 *  GLView.h
 *  ofxCocoaWindowNibless
 *
 *  Created by Shawn Lawson
 *  http://www.shawnlawson.com
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxCocoaWindowEvents.h"

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>


@interface GLView : NSOpenGLView {
	NSRect				savedWindowFrame;
	int					windowMode;
	
	CVDisplayLinkRef	displayLink;

	float				timeNow, timeThen, fps;
	double				lastFrameTime;
	int					nFrameCount;
	float				frameRate;
	bool				bEnableSetupScreen, bUpdateRateSet;
	
	int					updateRate;
	NSTimer *			updateTimer;
	
	// added BR 7/31/11: capture external mouse events
	BOOL			captureExternalMouseEvents;
	BOOL			externalMouseEventsActive;
	id mouseMoveHandler, leftMouseDownHandler, rightMouseDownHandler, leftMouseUpHandler, rightMouseUpHandler, leftMouseDraggedHandler,rightMouseDraggedHandler;
}

@property (assign) bool bEnableSetupScreen;
@property (assign) bool bUpdateRateSet;
@property (readonly) int updateRate;
@property (readonly) float frameRate;
@property (readonly) int nFrameCount;
@property (assign) int windowMode;
@property (readonly) double lastFrameTime;
@property (readonly) BOOL captureExternalMouseEvents;

-(id)initWithFrame:(NSRect)frameRect;
-(id)initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context screenMode:(int)m;

-(void) setCaptureExternalMouseEvents:(BOOL)b;
-(void)setUpdateRate:(int)targetRate;
-(void)updateOpenFrameworks;
-(void)draw;

-(void)goFullscreen:(NSScreen*)screen;
-(void)goWindow;


-(void)mouseMoveOutside:(NSEvent *)theEvent;
-(void)mouseDownOutside:(NSEvent *)theEvent;
-(void)rightMouseDownOutside:(NSEvent *)theEvent;
-(void)mouseUpOutside:(NSEvent *)theEvent;
-(void)rightMouseUpOutside:(NSEvent *)theEvent;
-(void)mouseDraggedOutside:(NSEvent *)theEvent;
-(void)rightMouseDraggedOutside:(NSEvent *)theEvent;

@end
