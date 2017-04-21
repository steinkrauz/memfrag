#include <string>
#include <chrono>
#include <string.h>
#include <cmath>
#include "testers.h"

using namespace std;


CharTester::CharTester()
{
    len = 0;
    mstrlen = -1;
    data = NULL;
    replace_table = NULL;
    runs = DEFAULT_RUNS;
    results = new int[runs];
    is_batch = false;
    koeff = DEFAULT_KOEF;
}


bool CharTester::load(char *filename) 
{
    ifstream   infile(filename);
    if (!infile.is_open()) return false;
    load_file_info(infile);

    data = new char*[len];
    int i = 0;

    time_span = std::chrono::nanoseconds::zero();
    while(!infile.eof()) {
        string line;
        int slen;
        getline(infile, line);
        slen = line.length();
        auto start = std::chrono::high_resolution_clock::now();
        data[i] = new char[slen+1];
        auto end = std::chrono::high_resolution_clock::now();
        time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        strcpy(data[i], line.c_str());
        i++;
    }
    cout<<"Allocation in load: "<<time_span.count()/1000<<"ms\n";
    return true;
}

void CharTester::perform_replaces()
{
   for (int i=0; i<table_size; ++i) {
       if (data[replace_table[i]]!=NULL) {
            delete data[replace_table[i]];
            data[replace_table[i]] = NULL;
       }
   }
    time_span = std::chrono::nanoseconds::zero();
    for (int i=0; i<table_size; ++i) {
        int slen = std::rand()%static_cast<int>(std::trunc(koeff*mstrlen));
        auto start = std::chrono::high_resolution_clock::now();
        data[replace_table[i]] = new char[slen];
        auto end = std::chrono::high_resolution_clock::now();
        time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }
    if (!is_batch)
        cout<<"Allocation in replace: "<<time_span.count()/1000<<"ms\n";

}

CharTester::~CharTester()
{
    for (int i = 0; i<len; ++i)
        delete []  data[i];
    delete [] data;
    delete [] replace_table; 
    delete [] results;
}


// vim: ai:ci:si:ts=4:sw=4:et
