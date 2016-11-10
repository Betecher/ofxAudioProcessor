
#include <vector>

using namespace std;

class ofxAudioReader {
	public:
		// constructor
		ofxAudioReader();
		ofxAudioReader(string newPath);

		// methods
		string	getPath();
		bool	getIsLoaded();
		bool	getIsPlaying();
		bool	getIsLooping();
		bool	getIsPaused();
		double	getPosition();
		double	getSpeed();
		char*	getData();

		void	setLooping(bool bLoop);
		void	setPaused(bool bPaused);
		void	setPosition(double newPosition);
		void	setSpeed(double newSpeed);

		bool	load(string newPath);
		bool	read();
		void	play();
		void	stop();
		double	update();

		int		getChannels();
		int		getSampleRate();
		long	getLength();
		
	private:
		enum SoundFlags { NONE = 0, LOADED = 1, PLAYING = 2, PAUSED = 4, LOOPING = 8};
		char*	sData;
		string	sPath;
		int		nChunkSize;
		int		nSubChunkSize;
		short	nFormat;
		short	nChannels;
		int		nSampleRate;
		int		nByteRate;
		short	nBlockAlign;
		short	nBitsPerSample;
		int		nDataSize;
		double	nPosition;
		double	nSpeed;
		double	nOutput;
		unsigned char soundStatus;
};