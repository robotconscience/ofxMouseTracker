#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255);

	if (mouse.loadSettings("mouse_312011-07-31-23-55-06-863.xml")){
		mouse.setLoop(true);
		mouse.startPlayback();
	}
	
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	
	fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
	//ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void testApp::update(){
	currentMouse = mouse.getCurrentMouseFrame();
}

//--------------------------------------------------------------
void testApp::draw(){
	fbo.begin();{
		ofPushMatrix();{
			ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0f);
			ofRotateZ( mouse.getNumLoops() );
			ofTranslate(-ofGetWidth()/2.0, -ofGetHeight()/2.0f);
		} ofPopMatrix();
		
		// what event type + what button?
		ofPushStyle();{
			switch ( currentMouse->eventType ){
				case 0:  // moved
					ofSetColor(50 + 100*currentMouse->button, 50 + 100*currentMouse->button, 50 + 100*currentMouse->button, 50);
					break;
				case 1: // down
					ofSetColor(150, 0, 150*currentMouse->button, 100);
					break;
				case 2: // up
					ofSetColor(150*currentMouse->button, 150, 0, 75);
					break;
				case 3: // dragged
					ofSetColor(200, 150*currentMouse->button, 0, 200);
					break;
			}
			
			// remember: mouse points are normalized to original screen
			
			ofCircle(currentMouse->x * ofGetScreenWidth(), currentMouse->y * ofGetScreenHeight(), 10+10*mouse.getCurrentElapsedTime());
		} ofPopStyle();
	} fbo.end();
	fbo.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
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

