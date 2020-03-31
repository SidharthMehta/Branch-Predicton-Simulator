#include "btb.h"
#include <math.h>
#include <iostream>

using namespace std;

#define PC_SIZE 24
#define vacant -1

BTB::BTB()
{
}

BTB::BTB(unsigned BTB_size, unsigned BTB_assoc)
{
    this->BTB_size = BTB_size;
    this->BTB_assoc = BTB_assoc;

    BTB_sets = BTB_size / (BTB_assoc * 4);

    index_bits = log2(BTB_sets);
    tag_bits = PC_SIZE - index_bits - 2;

    index_mask = (int)(pow(2, index_bits) - 1) << 2;
    tag_mask = (int)(pow(2, tag_bits) - 1) << (index_bits + 2);

    //Initializing the structure
    tagstore = new Tagstore *[BTB_sets];
    for (unsigned index = 0; index < BTB_sets; index++)
    {
        tagstore[index] = new Tagstore[BTB_assoc];
    }
    for (unsigned index = 0; index < BTB_sets; index++)
    {
        for (unsigned associativity = 0; associativity < BTB_assoc; associativity++)
        {
            tagstore[index][associativity].TAG = vacant;
            tagstore[index][associativity].frequency = associativity;
            tagstore[index][associativity].isValid = false;
        }
    }
}

void BTB::printContents()
{
    cout << "\nFINAL BTB CONTENTS";
    for (unsigned index = 0; index < BTB_sets; index++)
    {
        cout << "\nset\t" << dec << index << ":";
        for (unsigned frequency = 0; frequency < BTB_assoc; frequency++)
        {
            for (unsigned associativity = 0; associativity < BTB_assoc; associativity++)
            {
                if (frequency == tagstore[index][associativity].frequency)
                {
                    if (tagstore[index][associativity].TAG != vacant)
                    {
                        cout << "\t" << hex << tagstore[index][associativity].TAG;
                    }
                }
            }
        }
    }
    cout << "\n";
}

bool BTB::getBranch(unsigned PC)
{
    unsigned tag = (PC & tag_mask) >> (PC_SIZE - tag_bits);
    unsigned index = (PC & index_mask) >> 2;

    for (unsigned associativity = 0; associativity < BTB_assoc; associativity++)
    {
        if (tagstore[index][associativity].isValid && tagstore[index][associativity].TAG == (int)tag)
        {
            resetFrequency(index, tagstore[index][associativity].frequency);
            return true;
        }
    }
    return false;
}

void BTB::setBranch(unsigned PC)
{
    unsigned tag = (PC & tag_mask) >> (PC_SIZE - tag_bits);
    unsigned index = (PC & index_mask) >> 2;

    for (unsigned associativity = 0; associativity < BTB_assoc; associativity++)
    {
        if (tagstore[index][associativity].frequency == BTB_assoc - 1)
        {
            tagstore[index][associativity].TAG = tag;
            tagstore[index][associativity].isValid = true;
            resetFrequency(index, tagstore[index][associativity].frequency);
            return;
        }
    }
}

void BTB::resetFrequency(unsigned index, unsigned frequency)
{
    for (unsigned associativity = 0; associativity < BTB_assoc; associativity++)
    {
        if (tagstore[index][associativity].frequency < frequency)
        {
            tagstore[index][associativity].frequency++;
        }
        else if (tagstore[index][associativity].frequency == frequency)
        {
            tagstore[index][associativity].frequency = 0;
        }
    }
}