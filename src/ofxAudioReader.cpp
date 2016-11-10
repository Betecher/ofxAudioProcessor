#include "ofxAudioReader.h"
#include "ofMain.h"

// empty constructor
ofxAudioReader::ofxAudioReader() {
	nPosition = 0;
	nSpeed = 1.0;
	soundStatus = NONE;
}

// constructor takes a wav file path
ofxAudioReader::ofxAudioReader(string newPath) {
	nPosition = 0;
	nSpeed = 1.0;
	soundStatus = NONE;
	sPath = newPath;
	read();
}

bool ofxAudioReader::load(string newPath) {
	sPath = newPath;
	bool result = read();
	return result;
}

// read a wav file 
bool ofxAudioReader::read() {
	sPath = ofToDataPath(sPath, true).c_str();
	ifstream inFile(sPath.c_str(), ios::in | ios::binary);

	ofLog(OF_LOG_NOTICE, "Reading file %s", sPath.c_str());

	if (!inFile.is_open()) {
		ofLog(OF_LOG_ERROR, "Error opening file. File not loaded.");
		return false;
	}
	
	char id[4];
	inFile.read((char*)&id, 4);

	if (strncmp(id, "RIFF", 4) != 0) {
		ofLog(OF_LOG_ERROR, "Error reading sample file. File is not a RIFF (.wav) file");
		return false;
	}

	inFile.seekg(4, ios::beg);
	inFile.read((char*)&nChunkSize, 4); // read the chunk size

	inFile.seekg(16, ios::beg);
	inFile.read((char*)&nSubChunkSize, 4);// read the sub chunk size

	inFile.read((char*)&nFormat, sizeof(short)); // read the file format. This should be 1 for PCM.
	if (nFormat != 1) {
		ofLog(OF_LOG_ERROR, "File format should be PCM, sample file failed to load.");
		return false;
	}
	
	inFile.read((char*)&nChannels, sizeof(short));		// read the # of channels (1 or 2)
	inFile.read((char*)&nSampleRate, sizeof(int));		// read the sample rate
	inFile.read((char*)&nByteRate, sizeof(int));		// read the byte rate
	inFile.read((char*)&nBlockAlign, sizeof(short));	// read the block align
	inFile.read((char*)&nBitsPerSample, sizeof(short)); // read the bits per sample
	inFile.seekg(40, ios::beg);
	inFile.read((char*)&nDataSize, sizeof(int));		// read the size of the data

	// read the data chunk
	sData = new char[nDataSize];
	inFile.seekg(44, ios::beg);
	inFile.read(sData, nDataSize);

	// close the input file
	inFile.close(); 
	soundStatus |= LOADED;

	return true;
}

void ofxAudioReader::play() {
	if (nSpeed > 0) {
		nPosition = 0;
	}
	else {
		nPosition = getLength();
	}
	soundStatus |= PLAYING;
}

void ofxAudioReader::stop() {
	nPosition = 0;
	soundStatus &= ~PAUSED;
	soundStatus &= ~PLAYING;
}

double ofxAudioReader::update() {
	if (!(soundStatus & PLAYING))
		return 0;
	if (soundStatus & PAUSED)
		return 0;
	if (!getIsLoaded())
		return 0;

	long length = getLength();
	double remainder;
	short* buffer = (short*)sData;
	nPosition = nPosition + nSpeed;
	remainder = nPosition - (long)nPosition;

	// check if reached EOF
	if ((long)nPosition > length) {
		if (getIsLooping()) {
			nPosition = 0;
		}
		else {
			soundStatus &= ~PLAYING;
			return 0;
		}
	}

	// check if position less than zero (reverse)
	if ((long)nPosition < 0) {
		if (getIsLooping()) {
			nPosition = length;
		}
		else {
			soundStatus &= ~PLAYING;
			return 0;
		}
	}

	nOutput = (double)((1.0 - remainder) * buffer[1 + (long)nPosition] + remainder * buffer[2 + (long)nPosition]) / 32767.0; //linear interpolation

	return nOutput;
}

// setter methods
void ofxAudioReader::setLooping(bool bLoop) {
	if (bLoop) {
		soundStatus |= LOOPING;
	}
	else {
		soundStatus &= ~LOOPING;
	}
}

void ofxAudioReader::setPaused(bool bPaused) {
	if (bPaused) {
		soundStatus |= PAUSED;
	}
	else {
		soundStatus &= PAUSED;
	}
}

void ofxAudioReader::setPosition(double newPosition) {
	double pct = ofClamp(newPosition, 0.0, 1.0);
	nPosition = pct * getLength();
}

void ofxAudioReader::setSpeed(double newSpeed) {
	nSpeed = newSpeed;
}

// getter methods
string ofxAudioReader::getPath() {
	return sPath;
}

bool ofxAudioReader::getIsLoaded() {
	if (soundStatus & LOADED)
		return true;
	else
		return false;
}
	
bool ofxAudioReader::getIsPlaying() {
	if (soundStatus & PLAYING)
		return true;
	else
		return false;
}

bool ofxAudioReader::getIsLooping() {
	if (soundStatus & LOOPING)
		return true;
	else
		return false;
}

bool ofxAudioReader::getIsPaused() {
	if (soundStatus & PAUSED)
		return true;
	else
		return false;
}

double ofxAudioReader::getPosition() {
	double pos = nPosition / getLength();
	pos = ofClamp(pos, 0.0, 1.0);
	return pos;
}

double ofxAudioReader::getSpeed() {
	return nSpeed;
}

char* ofxAudioReader::getData() {
	return sData;
}

int ofxAudioReader::getChannels() {
	return nChannels;
}

int ofxAudioReader::getSampleRate() {
	return nSampleRate;
}

long ofxAudioReader::getLength() {
	long length;
	length = nDataSize * 0.5;
	return length;
}











