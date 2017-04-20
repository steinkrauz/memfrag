#include <chrono>
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
    for(int i=0; i<runs; i++) {
        new_replace_table();
        perform_replaces();
        results[i] = time_span.count()/1000;
    }
    int mean=0;
    for (int i=0; i<10; i++) {
        mean += results[i];
    }
    cout<<"First ten allocations mean time: "<<mean/10<<"ms\n";
    for (int i=runs-10; i<runs; i++) {
        mean += results[i];
    }
    cout<<"Last ten allocations mean time: "<<mean/10<<"ms\n";
    is_batch = false;
}


// vim: ai:ci:si:ts=4:sw=4:et
