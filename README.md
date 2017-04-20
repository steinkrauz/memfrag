# Memory fragmentation tester #

This is a simple and dumb program to test effects of memory fragmentation. The main idea is to check is an array of immutable strings is OK as a backend for a text editor.

### Algorithm ###

* Reads a text file into an array of lines
* Randomly selects a part of lines for replace (1/3 of the entire count)
* Frees them and allocates new lines, randomly sized to 2x of maximum original line size
* Repeat previous two points ad nauzeam

### How to run ###

memfrag -m <MODE> filename

The values of MODE are 'c' and 's'. 'c' is for character array case, 's' is for std::string case, which is currently not implemented