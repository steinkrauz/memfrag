#include <chrono>
#include <iomanip>
#include "testers.h"

using namespace std;

void BaseTester::load_file_info(ifstream& infile)
{
    cout<<"Total lines: ";
    while(!infile.eof()) {
        string line;
        int slen;
        getline(infile, line);
        slen = line.length();
        if (mstrlen<slen) mstrlen = slen;
        len++;
    }
    cout<<len<<"\n";
    cout<<"Max string length: "<<mstrlen<<"\n";

    infile.clear();
    infile.seekg(0);
}

void BaseTester::new_replace_table()
{
   if (replace_table==NULL) {
       table_size = len / 3;
       replace_table = new int[table_size];
       cout<<"Replace table has "<<table_size<<" entries\n";
   }
   for (int i=0; i<table_size; ++i) {
       replace_table[i] = std::rand() % (len);
   }
}

void BaseTester::run()
{
    is_batch = true;
    results = new int[runs];
    for(int i=0; i<runs; i++) {
        new_replace_table();
        perform_replaces();
        results[i] = time_span.count()/1000;
    }
    int mean0, mean1;
    mean0 = mean1 = 0;
    for (int i=0; i<10; i++) {
        mean0 += results[i];
    }
    cout<<"First ten allocations mean time: "<<mean0/10<<"ms\n";
    for (int i=runs-10; i<runs; i++) {
        mean1 += results[i];
    }
    cout<<"Last ten allocations mean time: "<<mean1/10<<"ms\n";
    cout<<"Allocation time changes by "<<fixed<<setprecision(2)<<(mean1*100/mean0)<<"%\n";
    is_batch = false;
}

void BaseTester::set_koeff(double k)
{
    koeff = k;
}

void BaseTester::set_runs(int num)
{
    runs = num;
}

BaseTester::~BaseTester()
{
}
// vim: ai:ci:si:ts=4:sw=4:et
