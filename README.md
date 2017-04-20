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

### Example ###

```
[stk@dev03 memfrag]$ ./memfrag -m c test.txt 
Char test selected
Total lines: 4354
Max string length: 205
Allocation in load: 387ms
VM: 4560; RSS: 2804
Replace table has 1451 entries
First ten allocations mean time: 180ms
Last ten allocations mean time: 319ms
VM: 50364; RSS: 48976
```

Memory consumption grew in ten ducking times, and time needed to allocate new strings nearly doubled. Nuff said.