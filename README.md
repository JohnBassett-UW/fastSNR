fastSNR.c contains the c code for the fastSNR function.
fastSNR.r is the equivalent R code

fastSNR simply takes the highest two values from an array and computes the quotient (MAX/2nd_MAX). 

I found it an interesting computability problem to explore the minimum number of comparisons needed to do this. Without knowing the internals of the functions max() or sort() I decided it might be fun to try and beat their performance. fastSNR.c is my current attempt to do this.

From a cell hashing standpoint this method of computing the signal to noise ration only makes sense if the hashing values are normalized, therefore, for that purpose, it expects normalized hashing counts.

The current iteration of fastSNR.c builds a heap to get the max. Then it swaps the 2nd and 3rd nodes of the binary tree and runs the node comparisons again. It prunes the binary tree to the first three nodes and tests whether node 2 or 3 is higher. This partial heapsort algorithm is a fast way of getting the 1st and 2nd max values of the array.

Subsequently it computes the signal-to-noise ratio by deviding the max value (signal) by the 2nd max value (noise).

In its current state main() runs some number (ntests) of pseudorandom test arrays through the method and crudely tests the results for accuracy.