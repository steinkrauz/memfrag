#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "testers.h"

using namespace std;

void process_mem_usage();

void print_usage(const char *msg) 
{
    cout<<msg<<"\nUSAGE:\n";
    cout<<"\tmemfrag -m <MODE> filename\n\n";
    cout<<"Where MODE can be either 's' or 'c'\n";
}

int main(int argc, char *argv[])
{
	if (argc!=4) {
	    print_usage("Wrong number of parameters");
	    return 0;
	}
	BaseTester *t;

	switch (argv[2][0]) {
	    case 'c':
	            t = new CharTester();
	            cout<<"Char test selected\n";
	            break;
	    case 's':
	            t = new StringTester();
	            cout<<"String test selected\n";
	            break;
	    default:
	            print_usage("Wrong mode");
	            return 0;
    }
    std::srand(unsigned(std::time(0)));

    if (!t->load(argv[3])) {
        return 1;
    }
    process_mem_usage();
    t->run();
    process_mem_usage();
}

// vim: ai:ci:ts=4:sw=4:et
