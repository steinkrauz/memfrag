#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>
#include "testers.h"

using namespace std;

void process_mem_usage();

void print_usage(const char *msg) 
{
    cout<<msg<<"\nUSAGE:\n";
    cout<<"\tmemfrag -m <MODE> [OPTION] FILE\n";
    cout<<"\n\
    -m         select a tester to use. MODE can be either 's' or 'c'.\n\
               This parameter is mandatory.\n\
    -r         run tester for RUNS times. Default is 1000.\n\
    -k         size koefficient for max size of new strings. Default value is 2.0\n\
";
}

int main(int argc, char *argv[])
{
    BaseTester *t = NULL;

	int optc;
	int runs = -1;
	int koeff = -1.0;
    while((optc=getopt(argc, argv, "m:r:k:")) != -1) {
        switch (optc) {
            case 'm':
                switch(*optarg) {
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
                break;
            case 'r':
                runs = atoi(optarg);
                break;
            case 'k':
                koeff = atof(optarg);
                break;
            default: 
                print_usage("");
                return 0;
        }
    }

    char *filename = (argv+optind)[0];

    if (t == NULL) {
        print_usage("You must select a mode");
        return 0;
    }

    if (filename == NULL) {
        print_usage("No file name found");
        return 0;
    }

    if (runs>0) t->set_runs(runs);
    if (koeff>0) t->set_koeff(koeff);


    std::srand(unsigned(std::time(0)));

    if (!t->load(filename)) {
        return 1;
    }
    process_mem_usage();
    t->run();
    process_mem_usage();
    delete t;
}

// vim: ai:ci:ts=4:sw=4:et
