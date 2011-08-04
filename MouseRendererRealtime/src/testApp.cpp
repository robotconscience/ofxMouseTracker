#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255);

	if (mouse.loadSettings("mouse.xml")){
		mouse.setLoop(false);
		mouse.startPlayback();
	}
	
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetCircleResolution(150);
	
	fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
	//ofSetBackgroundAuto(false);
	
	fbo.begin();{
		ofSetColor(255);
		ofRect(0,0,ofGetScreenWidth(), ofGetScreenHeight());
	} fbo.end();
	currentMouse = NULL;
	lastMouse.x = lastMouse.y = -10;
}

//--------------------------------------------------------------
void testApp::update(){
	if (currentMouse != NULL){
		lastMouse.x = currentMouse->x;
		lastMouse.y = currentMouse->y;
		lastMouse.count = currentMouse->count;
		lastMouse.button = currentMouse->button;
	}
	currentMouse = mouse.getCurrentMouseFrame();
}

//--------------------------------------------------------------
void testApp::draw(){
	fbo.begin();{
		glEnable( GL_ALPHA_TEST );
		ofEnableAlphaBlending();
		
		ofBackground(255, 255,255,50);
		
		// what event type + what button?
		ofPushStyle();{
			switch ( currentMouse->eventType ){
				case 0:  // moved
					ofSetColor(50 + 100*currentMouse->button, 50 + 100*currentMouse->button, 50 + 100*currentMouse->button, 20);
					break;
				case 1: // down
					ofSetColor(150, 0, 150*currentMouse->button, 20);
					break;
				case 2: // up
					ofSetColor(150*currentMouse->button, 150, 0, 20);
					break;
				case 3: // dragged
					ofSetColor(200, 150*currentMouse->button, 0, 20);
					break;
			}
			
			// remember: mouse points are normalized to original screen
			
			if (lastMouse.x != -10){ // we've gotten > 1 mouse Point
				ofSetLineWidth(1+3*mouse.getCurrentElapsedTime());
				ofLine(lastMouse.x * ofGetScreenWidth(), lastMouse.y * ofGetScreenHeight(), currentMouse->x * ofGetScreenWidth(), currentMouse->y * ofGetScreenHeight());
				ofNoFill();
				ofSetLineWidth(.1);
				ofCircle(currentMouse->x * ofGetScreenWidth(), currentMouse->y * ofGetScreenHeight(), mouse.getCurrentElapsedTime());
				ofFill();
			}
		} ofPopStyle();
	} fbo.end();
	fbo.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if (key == 's'){
		// save as image
		ofImage img;
		ofPixels pix;
		fbo.readToPixels(pix);
		img.setFromPixels(pix);
		img.saveImage("mouse_"+ofToString(ofGetDay())+"_"+ofGetTimestampString()+".png");
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

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

