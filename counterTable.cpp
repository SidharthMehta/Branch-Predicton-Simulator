#include "counterTable.h"
#include <stdlib.h>
#include <math.h>

counterTable::counterTable()
{
}

counterTable::counterTable(unsigned m, unsigned initialvalue)
{
    totalEntries = pow(2, m);
    counter = (unsigned *)malloc(totalEntries*sizeof(unsigned));
    for (unsigned index = 0; index < totalEntries; index++)
    {
        counter[index] = initialvalue;
    }
}

void counterTable::decrement(unsigned index)
{
    if (counter[index] > 0)
    {
        counter[index]--;
    }
}

void counterTable::increment(unsigned index)
{
    if (counter[index] < 3)
    {
        counter[index]++;
    }
}

unsigned counterTable::getCount(unsigned index)
{
    return counter[index];
}
