#include "sndfile.h"
#include <vector>

using namespace std;

class ofxAudioRecorder {
	public:
		// constructor
		ofxAudioRecorder();
		
		// methods
		void setInfo(int newSampleRate, int newFrames, int newChannels);
		void setFilepath(string &sFilepath);

		void startRecording();
		void stopRecordding();

		void addSamples(float* &input, int numSamples);

	private:
		SNDFILE * outfile;
		SF_INFO info;
		const char * sOutfilename;
		int nFormat;
		int nSampleRate;
		sf_count_t frames;
		int nChannels;


};

