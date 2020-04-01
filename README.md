# Branch-Predicton-Simulator

Project implements a branch predictor simulator and use it to design branch predictors (bi-modal, gShare, hybrid) with Branch Target buffer well suited to the SPECint95 benchmarks.

## Inputs to Simulator
The simulator reads a trace file in the following format:  
\<hex branch PC\> t|n  
\<hex branch PC\> t|n  
...  
Where:  
* \<hex branch PC\> is the address of the branch instruction in memory. This field is used to index into predictors.  
* "t" indicates the branch is actually taken (Note! Not that it is predicted taken!). Similarly, "n" indicates the branch is actually not-taken.
  
Example:  
00a3b5fc t  
00a3b604 t  
00a3b60c n  
...

## Outputs from Simulator
The simulator outputs the following measurements after completion of the run:  

Without BTB:  
1. number of accesses to the predictor (i.e., number of branches)  
2. number of branch mispredictions (predicted taken when not-taken, or predicted not-taken when taken)  
3. branch misprediction rate (# mispredictions/# branches)  

With BTB:  
1. size of BTB  
2. number of branches  
3. number of predictions from Branch Predictor (number of BTB hits)  
4. number of mispredictions from Branch Predictor (predicted taken when not-taken, or predicted not-taken when taken)  
5. number of banches miss in BTB and taken (number of mispredictions due to BTB miss)  
6. total number of mispredictions (item 4 + item 5)  
7. branch misprediction rate (item 6 / item 2)  

## Running the simulator

1. To simulate a bimodal predictor:  
**$./sim bimodal \<M2\> \<BTB size\> \<BTB assoc\> \<tracefile\>**  
where M2 is the number of PC bits used to index the bimodal table; BTB assoc is the associativity of the BTB, BTB size and BTB assoc are 0 if no BTB is modeled.  

2. To simulate a gshare predictor:  
**$./sim gshare \<M1\> \<N\> \<BTB size\> \<BTB assoc\> \<tracefile\>**  
where M1 and N are the number of PC bits and global branch history register bits used to index the gshare table, respectively; BTB assoc is the associativity of the BTB, BTB size and BTB assoc are 0 if no BTB is modeled.  

3. To simulate a hybrid predictor:  
**$./sim hybrid \<K\> \<M1\> \<N\> \<M2\> \<BTB size\> \<BTB assoc\> \<tracefile\>**  
where K is the number of PC bits used to index the chooser table, M1 and N are the number of PC bits and global branch history register bits used to index the gshare table (respectively), and M2 is the number of PC bits used to index the bimodal table. BTB assoc is the associativity of the BTB, BTB size and BTB assoc are 0 if no BTB is modeled.  

tracefile is the filename of the input trace.
