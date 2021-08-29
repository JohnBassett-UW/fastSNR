fastSNR.c contains the c code for the fastSNR function.
fastSNR_memcheck.txt contains the output of valgrind memcheck and shows no memory errors.

fastSNR is is equivalent to the following R code: 

signalNoise <- function(array){
  rowMax = max(x)
  noiseMax = sort(x, partial = n-1)[n-1]
  return(rowMax/noiseMax)
}

The signalNoise function for cell hashing counts simply takes the highest hash count and devides it by the second highest. From a data composition standpoint this only makes sense if the hashing values are normalized and so it expects normalized hashing counts.

This code is already very fast, but I found it interesting with respect to computability to explore the minimum number of comparisons needed to do this. Without knowing the internals of the functions max() or sort() I decided it might be fun to try and beat their performance. fastSNR.c is my attempt to do this.

The current iteration of fastSNR.c builds a heap to get the max. Then it swaps the 2nd and 3rd nodes of the binary tree and runs the node comparisons again. It prunes the binary tree to the first three nodes and tests whether node 2 or 3 is higher. This partial heapsort algorithm is a fast way of getting the 1st and 2nd max values of the array.

Subsequently it computes the signal-to-noise ratio by deviding the max value (signal) by the 2nd max value (noise).

In its current state main() runs some number (ntests) of pseudorandom test arrays through the method and crudely tests the results for accuracy.