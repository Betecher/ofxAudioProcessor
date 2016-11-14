## ofxAudioProcessor

Currently, this addon can read mono or stereo 'wav' files, and record audios and save them to files.

Both examples can be run in visual studio, but they are not tested in other platforms yet.

When you create a new project to record audio, please do the following steps:
  - "Project Property" -> "C/C++" -> "General" -> "Additional Include Directories" -> Edit & Add "~\addons\ofxAudioProcessor\libs\win32(win64)\libsndfile\include" This will add 'sndfile.h' & 'sndfile.hh' to the project
  - "Project Property" -> "Linker" -> "General" -> "Additional Library Directories" -> Edit & Add "~\addons\ofxAudioProcessor\libs\win32(win64)\libsndfile\lib" This will include 'libsndfile-1.lib' to the project
  - "Linker" -> "Input" -> "Additional Dependencies" -> type "libsndfile-1.lib"
  - Find 'libsndfile-1.dll' file in the "~\addons\ofxAudioProcessor\libs\win32(win64)\libsndfile\bin". Copy and paste it in the bin folder in your project.
