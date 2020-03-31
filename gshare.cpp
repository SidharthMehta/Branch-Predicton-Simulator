#include "gshare.h"
#include <math.h>
#include <iostream>
#include <math.h>

using namespace std;

gshare::gshare()
{
}

gshare::gshare(unsigned m, unsigned n)
{
    table = counterTable(m, 2);
    bhr = branchHistory(n);
    mask = pow(2,m) - 1;
    this->totalEntries = pow(2, m);
    this->m = m;
    this->n = n;
}

char gshare::predict(unsigned PC)
{
    unsigned index = getIndex((PC >> 2) & mask);
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

void gshare::update(unsigned PC, bool outcome)
{
    unsigned index = getIndex((PC >> 2) & mask);
    if (outcome)
    {
        table.increment(index);
    }
    else
    {
        table.decrement(index);
    }
    updateBHR(outcome);
}

void gshare::printContents()
{
    cout << "\nFINAL GSHARE CONTENTS";
    for (unsigned index = 0; index < totalEntries; index++)
    {
        cout << "\n"
             << dec << index << "\t" << table.getCount(index);
    }
}

unsigned gshare::getIndex(unsigned PCupper)
{
    unsigned index = (bhr.getHistory() << (m - n) ) ^ PCupper;
    return index;
}

void gshare::updateBHR(bool outcome)
{
    bhr.setHistory(outcome);
}