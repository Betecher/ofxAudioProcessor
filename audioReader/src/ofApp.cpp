#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);

	// initialize
	nSampleRate = 44100;
	nSpeed = 1.0;
	// load the audio file
	audioReader.load("beat.wav");
	// make it looping
	audioReader.setLooping(true);
	// start playing the audio
	audioReader.play();

	// set up the sound stream
	ofSoundStreamSetup(2, 0, this, nSampleRate, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		// if the audio is mono
		if (audioReader.getChannels() == 1) {
			double sample = audioReader.update();
			output[i * nChannels + 0] = sample;
			output[i * nChannels + 1] = sample;
		}
		// if the audio is stereo
		else {
			output[i * nChannels + 0] = audioReader.update();
			output[i * nChannels + 1] = audioReader.update();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
