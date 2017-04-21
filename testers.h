/*
    Header file for tester classes declarations
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class BaseTester 
{
    protected:
    int     *replace_table;
    int     len;
    int     mstrlen;
    int     table_size;
    int     *results;
    int     runs;
    double  koeff;
    bool    is_batch;
    std::chrono::nanoseconds time_span;
    void load_file_info(std::ifstream& infile);
    public:
    virtual bool load(char *filename) = 0;
    void new_replace_table();
    virtual void perform_replaces() = 0;
    void run();
    void set_koeff(double k);
    void set_runs(int num);
};

class CharTester : public BaseTester 
{
    private:
    char    **data;
    public:
    CharTester();
    bool load(char *filename);
    void perform_replaces();
    virtual ~CharTester();
};

class StringTester : public BaseTester 
{
    private:
    std::vector<std::string> data;
    char    *buf_str;
    public:
    StringTester();
    bool load(char *filename);
    void perform_replaces();
    virtual ~StringTester();
};

// vim: ai:ci:ts=4:sw=4:et
