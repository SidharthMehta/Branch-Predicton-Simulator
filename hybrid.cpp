#include "hybrid.h"
#include <iostream>
#include <math.h>

using namespace std;

hybrid::hybrid()
{

}

hybrid::hybrid(unsigned k, unsigned m1, unsigned n, unsigned m2)
{
    table = counterTable(k, 1);
    Gshare = gshare(m1, n);
    Bimodal = bimodal(m2);
    this->totalEntries = pow(2, k);
    predictorUsed = 'x';
    gsharePrediction = 'x';
    bimodalPrediction = 'x';
    mask = pow(2,k) - 1;
}

char hybrid::predict(unsigned PC)
{
    gsharePrediction = Gshare.predict(PC);
    bimodalPrediction = Bimodal.predict(PC);
    unsigned index = (PC >> 2) & mask;
    char prediction = 'x';
    if (table.getCount(index) >= 2)
    {
        prediction = gsharePrediction;
        predictorUsed = 'g';
    }
    else
    {
        prediction = bimodalPrediction;
        predictorUsed = 'b';
    }
    return prediction;
}

void hybrid::update(unsigned PC, char outcome)
{
    unsigned index = (PC >> 2) & mask;
    if (bimodalPrediction != gsharePrediction)
    {
        if(outcome == gsharePrediction)
        {
            table.increment(index);
        }
        else
        {
            table.decrement(index);
        }
    }
    if(predictorUsed == 'b')
    {
        Bimodal.update(PC, outcome == 't');
        Gshare.updateBHR(outcome == 't');
    }
    else if(predictorUsed == 'g')
    {
        Gshare.update(PC, outcome == 't');
    }
}

void hybrid::printContents()
{
    cout << "\nFINAL CHOOSER CONTENTS";
    for (unsigned index = 0; index < totalEntries; index++)
    {
        cout << "\n"
             << dec << index << "\t" << table.getCount(index);
    }
    Gshare.printContents();
    Bimodal.printContents();
}