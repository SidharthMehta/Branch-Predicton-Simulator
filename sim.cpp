#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "bimodal.h"
#include "gshare.h"
#include "hybrid.h"
#include "btb.h"
#include <iomanip>

using namespace std;

char *Model;                //Branch predictor model
unsigned m1;                //Number of PC bits used to index the gshare table
unsigned m2;                //Number of PC bits used to index the bimodal table
unsigned n;                 //Number of bits in the global branch history register
unsigned k;                 //number of PC bits used to index the chooser table
unsigned BTB_size;          //Size of BTB
unsigned BTB_associativity; //Associativity of BTB
char *Trace_file;           //Input Trace file

int main(int argc, char *argv[])
{
    BTB btb;
    bimodal bimodalPredictor;
    gshare gsharePredictor;
    hybrid hybridPredictor;
    Model = argv[1];
    if (strcmp(Model, "bimodal") == 0)
    {
        m2 = strtoul(argv[2], 0, 10);
        BTB_size = strtoul(argv[3], 0, 10);
        BTB_associativity = strtoul(argv[4], 0, 10);
        Trace_file = argv[5];
        bimodalPredictor = bimodal(m2);
    }
    else if (strcmp(Model, "gshare") == 0)
    {
        m1 = strtoul(argv[2], 0, 10);
        n = strtoul(argv[3], 0, 10);
        BTB_size = strtoul(argv[4], 0, 10);
        BTB_associativity = strtoul(argv[5], 0, 10);
        Trace_file = argv[6];
        gsharePredictor = gshare(m1, n);
    }
    else if (strcmp(Model, "hybrid") == 0)
    {
        k = strtoul(argv[2], 0, 10);
        m1 = strtoul(argv[3], 0, 10);
        n = strtoul(argv[4], 0, 10);
        m2 = strtoul(argv[5], 0, 10);
        BTB_size = strtoul(argv[6], 0, 10);
        BTB_associativity = strtoul(argv[7], 0, 10);
        Trace_file = argv[8];
        hybridPredictor = hybrid(k, m1, n, m2);
    }

    if (BTB_size != 0 && BTB_associativity != 0)
    {
        btb = BTB(BTB_size, BTB_associativity);
    }
    //Read trace file
    ifstream trace(Trace_file);
    if (!trace.is_open())
    {
        //If file cannot be read exit
        exit(0);
    }

    char branch;          //taken or not taken
    string addressString; //Address to be accessed in string form
    unsigned PC;          //Address to be accessed in integer form
    char prediction;      //Result from branch predictor
    bool isBranch = true;
    unsigned long totalPredictions = 0;
    unsigned long mispredictions = 0;
    unsigned long branchMiss = 0;
    unsigned long branchHits = 0;

    string line;
    stringstream ss;
    while (getline(trace, line))
    {
        addressString = line.substr(0, 6); //To read the address string

        //Conversion of Hex string to number
        ss << hex << addressString << endl;
        ss >> PC;

        branch = line[7];

        totalPredictions++;
        if (BTB_size != 0)
        {
            isBranch = btb.getBranch(PC);
        }

        if (isBranch)
        {
            branchHits++;
            if (strcmp(Model, "bimodal") == 0)
            {
                prediction = bimodalPredictor.predict(PC);

                bimodalPredictor.update(PC, branch == 't');

                if (branch != prediction)
                {
                    mispredictions++;
                }
            }
            else if (strcmp(Model, "gshare") == 0)
            {
                prediction = gsharePredictor.predict(PC);

                gsharePredictor.update(PC, branch == 't');

                if (branch != prediction)
                {
                    mispredictions++;
                }
            }
            else if (strcmp(Model, "hybrid") == 0)
            {
                prediction = hybridPredictor.predict(PC);

                hybridPredictor.update(PC, branch);

                if (branch != prediction)
                {
                    mispredictions++;
                }
            }
        }
        else
        {
            btb.setBranch(PC);
            if(branch == 't')
            {
                branchMiss++;
            }
        }
    }
    trace.close();

    cout << "COMMAND\n";
    for (int argsIterator = 0; argsIterator < argc; argsIterator++)
    {
        cout << " " << argv[argsIterator];
    }

    cout << "\nOUTPUT";
    if (BTB_size)
    {
        cout << "\nsize of BTB:\t" << dec << BTB_size;
        cout << "\nnumber of branches:" << totalPredictions;
        cout << "\nnumber of predictions from branch predictor:\t" << branchHits;
        cout << "\nnumber of mispredictions from branch predictor:\t" << mispredictions;
        cout << "\nnumber of branches miss in BTB and taken:\t" << branchMiss;
        cout << "\ntotal mispredictions:\t" << mispredictions + branchMiss;
        cout << "\nmisprediction rate:\t" << fixed << setprecision(2) << ((float)mispredictions + branchMiss) * 100 / totalPredictions << "%";
        btb.printContents();
    }
    else
    {
        cout << "\nnumber of predictions:\t" << dec << totalPredictions;
        cout << "\nnumber of mispredictions:\t" << mispredictions;
        cout << "\nmisprediction rate:\t" << fixed << setprecision(2) << ((float)mispredictions) * 100 / totalPredictions << "%";
    }
    if (strcmp(Model, "bimodal") == 0)
    {
        bimodalPredictor.printContents();
    }
    else if (strcmp(Model, "gshare") == 0)
    {
        gsharePredictor.printContents();
    }
    else if (strcmp(Model, "hybrid") == 0)
    {
        hybridPredictor.printContents();
    }
    return 0;
}