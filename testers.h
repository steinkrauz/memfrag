/*
    Header file for tester classes declarations
*/

#include <fstream>
#include <iostream>

class BaseTester 
{
    protected:
    int     *replace_table;
    int     len;
    int     mstrlen;
    int     table_size;
    int     *results;
    int     runs;
    bool    is_batch;
    std::chrono::nanoseconds time_span;
    void load_file_info(std::ifstream& infile);
    public:
    virtual bool load(char *filename) = 0;
    void new_replace_table();
    virtual void perform_replaces() = 0;
    void run();
};

class CharTester : public BaseTester 
{
    private:
    char    **data;
    public:
    CharTester(int num=1000);
    bool load(char *filename);
    void perform_replaces();
    virtual ~CharTester();
};

// vim: ai:ci:ts=4:sw=4:et
