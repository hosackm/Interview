# Interview
Solution for whiteboard problems during interview

# Dependencies
The app depends on [OpenFrameworks](www.openframeworks.cc) to work. Audio input is handled by RtAudio and the graphics are handled by OpenFrameworks.

In order to separate UI from Audio without the use of locks, I used the boost atomic library.  Openframeworks is unable to be built with std-c++ 11 which includes atomic, so I had to use a third party library.

For testing the Google Test Framework is used.

# ToDo
* Peak Meter slower display response
* Gradient for Peak Meter
* Peak Meter RMS instead of peak


