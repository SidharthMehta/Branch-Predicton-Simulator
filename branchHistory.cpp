#include "branchHistory.h"
#include "math.h"

branchHistory::branchHistory()
{

}

branchHistory::branchHistory(unsigned n)
{
    history = 0;
    this->n = n;
}

void branchHistory::setHistory(unsigned value)
{
    history = ((value << n) + history) >> 1;
}

unsigned branchHistory::getHistory()
{
    return history;
}