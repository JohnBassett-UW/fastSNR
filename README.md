fastSNR is a for-fun project to beat the performance its equivalent R code signalNoise.r.

A useful metric for evaluating signal to noise in arrays of hashed-nuclei barcode counts is to divide the first maximum by the second maximum.

To do this, fastSNR.c builds a heap to get the max. Then it swaps the 2nd and 3rd nodes of the binary tree and runs the node comparisons again. It prunes the binary tree to the first three nodes and tests whether node 2 or 3 is higher. 

This partial heapsort algorithm is a fast way of getting the 1st and 2nd max values of the array.

Subsequently it computes the signal-to-noise ratio by deviding the max value (signal) by the 2nd max value (noise).

In its current state the main() function is being used to run n pseudorandom test arrays through the method and check the results for accuracy.

fastSNR has been tested for memory leakage with valgrind, but requires additional validation.