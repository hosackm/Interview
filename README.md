# Interview
Solution for whiteboard problems during interview

# Dependencies
The app depends on [OpenFrameworks](www.openframeworks.cc) to work. Audio input is handled by RtAudio and the graphics are handled by OpenFrameworks.

In order to separate UI from Audio without the use of locks, I used the boost atomic library.  Openframeworks is unable to be built with std-c++ 11 which includes atomic, so I had to use a third party library.

# ToDo
The peak meter updates very quickly.  I'll use an averaging filter to slow down the input to the peak meter so it is more human friendly.
