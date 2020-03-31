#ifndef BTB_H
#define BTB_H

struct Tagstore
{
    int TAG;         
    unsigned frequency;
    bool isValid;
};

class BTB
{
    private:
        unsigned BTB_size;
        unsigned BTB_assoc;
        unsigned BTB_sets;

        unsigned index_bits;
        unsigned tag_bits;

        unsigned tag_mask;
        unsigned index_mask;

        //Least recently used replacement policy
        unsigned evict(unsigned);

        //Method to update frequency of access
        void resetFrequency(unsigned, unsigned);

        Tagstore **tagstore;
    public:
        BTB();
        BTB(unsigned, unsigned);
        void printContents();
        bool getBranch(unsigned); 
        void setBranch(unsigned);
};

#endif