#include <string>
#include <chrono>
#include <string.h>
#include <cmath>
#include "testers.h"

using namespace std;


StringTester::StringTester()
{
    len = 0;
    mstrlen = -1;
    replace_table = NULL;
    runs = DEFAULT_RUNS;
    results = new int[runs];
    is_batch = false;
    koeff = DEFAULT_KOEF;
}


bool StringTester::load(char *filename) 
{
    ifstream   infile(filename);
    if (!infile.is_open()) return false;
    load_file_info(infile);

    buf_str = new char[(int)(koeff*mstrlen+0.5)];

    time_span = std::chrono::nanoseconds::zero();
    while(!infile.eof()) {
        string line;
        getline(infile, line);
        auto start = std::chrono::high_resolution_clock::now();
        data.push_back(line);
        auto end = std::chrono::high_resolution_clock::now();
        time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }
    cout<<"Allocation in load: "<<time_span.count()/1000<<"ms\n";
    return true;
}

void StringTester::perform_replaces()
{
    time_span = std::chrono::nanoseconds::zero();
    for (int i=0; i<table_size; ++i) {
        string line;
        int slen = std::rand()%static_cast<int>(std::trunc(koeff*mstrlen));
        memset(buf_str, 'a', slen);
        buf_str[slen] = '\0';
        line = buf_str;
        auto start = std::chrono::high_resolution_clock::now();
        data[replace_table[i]] = line;
        auto end = std::chrono::high_resolution_clock::now();
        time_span += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }
    if (!is_batch)
        cout<<"Allocation in replace: "<<time_span.count()/1000<<"ms\n";

}

StringTester::~StringTester()
{
    data.clear();
    delete [] buf_str;
    delete [] replace_table; 
    delete [] results;
}


// vim: ai:ci:si:ts=4:sw=4:et
