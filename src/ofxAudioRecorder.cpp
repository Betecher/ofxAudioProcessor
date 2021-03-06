#include "ofxAudioRecorder.h"
#include "ofMain.h"

// default constructor
ofxAudioRecorder::ofxAudioRecorder() {
	nFormat = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	nSampleRate = 44100;
	frames = nSampleRate * 15;
	nChannels = 2;
	
	info.format = nFormat;
	info.frames = frames;
	info.samplerate = nSampleRate;
	info.channels = nChannels;
}

// set audio information method
void ofxAudioRecorder::setInfo(int newSampleRate, int newFrames, int newChannels) {
	nSampleRate = newSampleRate;
	frames = newFrames;
	nChannels = newChannels;

	info.frames = frames;
	info.samplerate = nSampleRate;
	info.channels = nChannels;
}

// set file path
void ofxAudioRecorder::setFilepath(string &sFilepath) {
	sOutfilename = sFilepath.c_str();
}

// open file to start recording
void ofxAudioRecorder::startRecording() {
	outfile = sf_open(sOutfilename, SFM_WRITE, &info);
	if (!outfile) {
		cerr << "Error opening [" << sOutfilename << "] : " << sf_strerror(outfile) << endl;
	}
}

// close file to stop recording
void ofxAudioRecorder::stopRecordding() {
	sf_close(outfile);
}

// write audio samples to file
void ofxAudioRecorder::addSamples(float * &input, int numSamples) {
	sf_write_float(outfile, input, numSamples);
}