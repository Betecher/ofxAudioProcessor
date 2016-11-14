#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);

	// initialize
	bRecording = false;
	nSampleRate = 44100;
	nSpeed = 1.0;
	// load the audio file
	audioReader.load("beat.wav");
	// set it to loop
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

	// if it is being recorded
	if (bRecording) {
		// add samples to the recorder
		// i.e. write audio samples to an file
		audioRecorder.addSamples(output, bufferSize * 2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// press key 1 to start recording
	if (key == '1') {
		bRecording = true;
		// initialize the audio file path 
		string sFilepath = "data/" + ofToString(ofGetYear()) + "-" + ofToString(ofGetMonth()) + "-" + ofToString(ofGetDay()) + "at"
			+ ofToString(ofGetHours()) + "." + ofToString(ofGetMinutes()) + "." + ofToString(ofGetSeconds()) + ".wav";
		// set the audio file path
		audioRecorder.setFilepath(sFilepath);
		audioRecorder.startRecording();
	}
	// press key 2 to stop recording
	if (key == '2') {
		bRecording = false;
		audioRecorder.stopRecordding();
	}
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
