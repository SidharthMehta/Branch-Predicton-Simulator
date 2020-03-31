#include "bimodal.h"
#include "math.h"
#include <iostream>

using namespace std;

bimodal::bimodal()
{
}

bimodal::bimodal(unsigned m)
{
    table = counterTable(m, 2);
    mask = pow(2,m) - 1;
    this->totalEntries = pow(2, m);
}

char bimodal::predict(unsigned PC)
{
    unsigned index = (PC >> 2) & mask;
    char prediction = 'x';
    if (table.getCount(index) >= 2)
    {
        prediction = 't';
    }
    else
    {
        prediction = 'n';
    }
    return prediction;
}

void bimodal::update(unsigned PC, bool outcome)
{
    unsigned index = (PC >> 2) & mask;
    if (outcome)
    {
        table.increment(index);
    }
    else
    {
        table.decrement(index);
    }
}

void bimodal::printContents()
{
    cout << "\nFINAL BIMODAL CONTENTS";
    for (unsigned index = 0; index < totalEntries; index++)
    {
        cout << "\n"
             << dec << index << "\t" << table.getCount(index);
    }
}