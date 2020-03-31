#ifndef HYBRID_H
#define HYBRID_H

#include "bimodal.h"
#include "gshare.h"
#include "counterTable.h"

class hybrid
{
    private:
        bimodal Bimodal;
        gshare Gshare;
        counterTable table;
        char predictorUsed;
        unsigned totalEntries;
        char gsharePrediction;
        char bimodalPrediction;
        unsigned mask;
    public:
        hybrid();
        hybrid(unsigned, unsigned, unsigned, unsigned);
        char predict(unsigned);
        void update(unsigned, char);
        void printContents();
};

#endif