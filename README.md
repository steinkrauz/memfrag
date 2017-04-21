# Memory fragmentation tester #

This is a simple and dumb program to test effects of memory fragmentation. The main idea is to check is an array of immutable strings is OK as a backend for a text editor.

### Algorithm ###

* Reads a text file into an array of lines
* Randomly selects a part of lines for replace (1/3 of the entire count)
* Frees them and allocates new lines, randomly sized to 2x of maximum original line size
* Repeat previous two points ad nauzeam

### How to run ###

memfrag -m <MODE> [OPTION] FILE

    -m         select a tester to use. MODE can be either 's' or 'c'.
               This parameter is mandatory.
    -r         run tester for RUNS times. Default is 1000.
    -k         size coefficient for max size of new strings. Default value is 2.0

### Examples ###

```
[stk@dev03 memfrag]$ ./memfrag -m c test.txt 
Char test selected
Total lines: 4354
Max string length: 205
Allocation in load: 478ms
VM: 4568; RSS: 2916
Replace table has 1451 entries
First ten allocations mean time: 136ms
Last ten allocations mean time: 217ms
Allocation time changes by 158%
VM: 50108.00; RSS: 48764.00

```
Memory consumption grew in ten ducking times, and time needed to allocate new strings visibly increased. Nuff said.

'''
[stk@dev03 memfrag]$ ./memfrag -m s -r 1300 -k 1.5 test.txt 
String test selected
Total lines: 4354
Max string length: 205
Allocation in load: 1167ms
VM: 4816; RSS: 3156
Replace table has 1451 entries
First ten allocations mean time: 189ms
Last ten allocations mean time: 2043ms
Allocation time changes by 1080%
VM: 6008.00; RSS: 4388.00
'''

STL library can save you from memory consumption, but in the end bad design with catch you: just add some more runs.