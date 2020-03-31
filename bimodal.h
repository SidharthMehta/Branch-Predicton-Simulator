#ifndef BIMODAL_H
#define BIMODAL_H

#include "counterTable.h"

class bimodal
{
    private:
        counterTable table;
        unsigned totalEntries;             //Number of index
        unsigned mask;
    public:
        bimodal();
        bimodal(unsigned);
        char predict(unsigned);
        void update(unsigned, bool);
        void printContents();
};

#endif