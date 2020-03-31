#ifndef GSHARE_H
#define GSHARE_H

#include "branchHistory.h"
#include "counterTable.h"

class gshare
{
    private:
        counterTable table;
        branchHistory bhr;
        unsigned totalEntries;             //Number of index
        unsigned m;
        unsigned n;
        unsigned mask;
    public: 
        gshare();
        gshare(unsigned, unsigned);
        char predict(unsigned);
        void update(unsigned, bool);
        void printContents();
        unsigned getIndex(unsigned);
        void updateBHR(bool);
};

#endif