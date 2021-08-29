#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int comparisons = 0;
double minComparisons;
int maxComparisons = 0;
double totalComparisons = 0;

void swap(int* x, int* y);
void heap(int vec[], int n, int idx);
void buildNodes(int vec[], int n);
void printh(int vec[], int n);
double signalNoise(int vec[]);
double log10(double x);

int main() {
    const int n = 1000;
    const int ntests = 10000; // number of tests to conduct
    int success = 0; // increments if test succeeds
    int x; // psuedorandom index of array
    int y; // psuedorandom index of array
    int max; //max of array after sort
    int second; //1st possible 2nd max of array
    int third; //2nd possible 2nd max of array
    double snrValue; //possible value of snr
    double snrAlt; //alternate possible value of snr
    bool swaptest = false; // indicators of successful tests
    bool heaptest = false;
    bool snrtest = false;

    minComparisons = n*log10((double)n)/log10(2.0) + n;
    int *array = (int *) calloc(n, sizeof(int));
    if(array == NULL){
		printf("calloc size %d failed!\n", n);
		exit(1);
	}
  
    //iterate through 1000 rounds of testing
    for(int t = 0; t <ntests; t++){
    //generate array
    	srand(t + time(NULL)); 
    	for( int i = 0; i < n; i++){
		array[i] = rand() % 1000 + 1;
    	}
   

    	//printf("%ls \n", array);
   //test swap function
	second = rand() % 10 + 1;
	third = rand() % 10 + 1;
    	x = array[second];
	y = array[third];
    	swap(&array[second], &array[third]);
    	if(array[second] == y && array[third] == x){
		swaptest = true;
	}

   	//printf("\n");
   //build heap
    	//printh(array, n);
	comparisons  = 0;
	buildNodes(array, n);
	//printf(" <-> ");
	//printh(array, n);
	//printf(" comparisons made: %d \n", comparisons);
   //test heap
	for(int h = 3; h < n; h++){
		if(array[0] < array[h] || array[1] < array[h] || array[2] < array[h]){
			heaptest = false;
			printf("bad heap \n");
			break;
		}
		else{
			heaptest = true;
		}
	}

    	//printh(array, n);
   //test signalNoise
   	max = array[0];
	second = array[1];
	third = array[2];
	snrValue = (double)max/second;
	snrAlt = (double)max/third;
	//printf(" SNRp1 %f ", snrValue);
	//printf("SNRp2 %f \n", snrAlt);
	if(snrAlt < snrValue){
		snrValue = snrAlt;
	}

	//printf(" SNR %f : EVAL %f \n", signalNoise(array), snrValue);
	
	if(signalNoise(array) == snrValue){
		snrtest = true;
	}

	if(snrtest == true && heaptest == true && swaptest == true){
		success += 1;
	}
	
	if(comparisons > maxComparisons){
		maxComparisons = comparisons;
	}
	if(comparisons < minComparisons){
		minComparisons = comparisons;
	}

	totalComparisons += comparisons;
	//printf("snr: %d, heap: %d, swap: %d \n", snrtest, heaptest, swaptest);
    } 
    printf("fastSNR succeeded %d / %d times \n", success, ntests);
    printf("Avg Comparisons: %f  \n", totalComparisons/ntests);
    printf("max Comparisons: %d   min comparisons: %f \n", maxComparisons, trunc(minComparisons));
    free(array);
    return 0;
    
}

void swap(int *x, int *y)
{
	int tmp = *x;
	//printf("%p, %p, %p", x, y, tmp);
	*x = *y;
	*y = tmp;
}

void buildNodes( int vec[], int n)
{
	int lastNode = (n / 2) - 1;
	for(int r = 0; r <= 1; r++){ 
		for(int i = lastNode; i >= 0 ; i --){
			heap(vec, n, i);
		}
		swap(&vec[1], &vec[2]);
	}
}

void heap(int vec[], int n, int idx)
{
	int high = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	comparisons ++;
	if( left < n && vec[left] > vec[high]){
		high = left;
	}
	comparisons ++;
	if( right < n && vec[right] > vec[high]){
		high = right;
	}
	comparisons ++;
	if (high != idx){
		swap(&vec[idx], &vec[high]);
//		printf("%d <-> %d    ", vec[idx], vec[high]);
		heap(vec, n , high);
	}		
}
void printh(int vec[], int n){
	for(int i = 0; i < n; i ++){
		printf("%d ", vec[i]);
	}
}
double signalNoise(int vec[]){
	comparisons ++;
	if(vec[2] >= vec[1]){
	return((double)vec[0]/vec[2]);
	}
	else{
	return((double)vec[0]/vec[1]);
	}
}

