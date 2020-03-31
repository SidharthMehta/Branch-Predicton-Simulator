#ifndef BRANCHHISTORY_H
#define BRANCHHISTORY_H

class branchHistory
{
    private:
        unsigned history;
        unsigned n;
    public:
        branchHistory();
        branchHistory(unsigned);
        void setHistory(unsigned);
        unsigned getHistory();
};

#endif