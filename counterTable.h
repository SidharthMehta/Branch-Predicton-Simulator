#ifndef COUNTERTABLE_H
#define COUNTERTABLE_H

class counterTable
{
    private:
        unsigned *counter;
        unsigned totalEntries;
    public:
        counterTable();
        counterTable(unsigned, unsigned);
        void increment(unsigned);
        void decrement(unsigned);
        unsigned getCount(unsigned);
};

#endif 