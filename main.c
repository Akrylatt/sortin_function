#include <stdio.h>
#define ELEMENTS 12
/*
* This code includes several sorting algorithms in c language
*
* Insertion sort (for one array and for onw array with storing sorted array in another array)
* Bubble sort
* Shake sort
* Selection sort
* Shell sort
* Merge sort
* Quick sort
*/

/*insertion sort
* takes each element and compare it with the left side
* if not mach than moves the left side and put the element to the right place
* sorting from left to right
* O = n^2; but can be better
*/ 
void insertion_sort(int x[], int pocet){
  for(int i = 0; i < pocet - 1; i ++){
    int j = i + 1;
    int current = x[j];
    while(current < x[j - 1] && j > 0){
      x[j] = x[j - 1];
      j--;
    }
    x[j] = current;
  }
}

/*insertion sort for two arrays, where x is kept unsorted while y is sorted*/
void insertion_sort_2Arr(int x[], int y[], int pocet){
  y[0] = x[0];
  for(int i = 0; i < pocet - 1; i ++){
    int j = i + 1;
    int current = x[j];
    while(current < y[j - 1] && j > 0){
      y[j] = y[j - 1];
      j--;
    }
    y[j] = current;
  }
  
}

/* Bubble sort
* iterates through all arr n-1 times
* Takes element comares it with next right 
* if it the right element is bigger swaps the elements
* if not take the next right element and continues
* sorting from left to right
* Number of operations: (n-1)*(n-1+1)/2 = (n2 - n)/2
* O = n^2 
*/
void bubble_sort(int x[], int pocet){
  for(int i = 0; i < pocet - 1; i++){
    for(int j = 0; j < pocet - i - 1; j++){
      if(x[j] < x[j + 1]){
        /*swap*/
        int a = x[j];
        x[j] = x[j + 1];
        x[j + 1] = a;
      }
    }
  }
}

/* Shake sort 
* similar to bubble sort
* it is like bubble sort there and back again
* sorting from left and right to the middle
* O = n^2; but can be even better
*/
void shake_sort(int x[], int pocet){
  for(int i = 0; i < pocet/2; i++){ /* because we go from both sides only pocet/2 is enough*/
    int swaped = 0; /*in case that there are no swaps needed the array is already sorted*/
    for(int j = 0; j < pocet - i - 1; j++){
      if(x[j] < x[j + 1]){
        /*swap*/
        int a = x[j];
        x[j] = x[j + 1];
        x[j + 1] = a;
        swaped = 1;
      }
    }

    /*way back: */
    for(int j = pocet - 2 - i; j > i; j--){ /*j > i since the first i elements are already sorted as well as last i elements*/
      if(x[j] > x[j - 1]){
        /*swap*/
        int a = x[j];
        x[j] = x[j - 1];
        x[j - 1] = a;
        swaped = 1;
      }
    }
    if(!swaped){
      break; /*already sorted*/
    }
  }
}

/* Selection sort
* for array from i to end find the maximum and swap it with i-th element
* sorting from left to right
* O = n^2 (with constant memory)
*/
void selection_sort(int x[], int pocet){
  for(int i = 0; i < pocet - 1; i++){
    int max = i; /*index of the max element in the range from i to end*/
    for(int j = i + 1; j < pocet; j++){ /*finding max*/
      if(x[j] > x[max]){
        max = j;
      }
    }
    /*swapping the max with the i-th element*/
    int a = x[max];
    x[max] = x[i];
    x[i] = a;
  }
}

/* Shell sort
* similar to insertion sort, not compares neighbors but elements with the gap
* gap is every interation smaller and smaller 
* when the gap = 1 it is normal insertion sort
* important to choose the right gap - usually /2.2 every iteration
* O = n^2
* not stable -> two same elements could be swapped
*/
void shell_sort(int x[], int pocet){
  int gap = pocet / 2;
  while(gap > 0){
    for(int i = 0; i < pocet - gap; i++){
      int j = i + gap;
      int current = x[j];
      while(current > x[j - gap] && j >= gap){
        x[j] = x[j - gap];
        j -= gap;
      }
      x[j] = current;
    }
    if(gap == 2){
      gap = 1;
    }
    else{
      gap /= 2.2;
    }
  }
}

/* a procedure for the merge_sort*/
void merge(int x[], int y[], int left, int right){
  /* you get only two pointrs - left pointer at first element and right pointer at last element within the two arrays which you want to merge*/

  int middleIndex = (left + right) / 2; /* element in the middle of the two arrays = last element of the fist array*/
  /*right = last element of the second array*/
  int leftIndex = left; /*first element of the first array*/
  int rightIndex = middleIndex + 1; /*first element of the second array*/
  int yIndex = left; /*pointer to current emply space in y, from left to right*/

  while(rightIndex <= right && leftIndex <= middleIndex){ /*when we have still elements in both arrays which are being merged*/

    if(x[leftIndex] >= x[rightIndex]){ /*compare first but still not corted element with the first but not sorted element in the secon array*/
      y[yIndex] = x[leftIndex];
      leftIndex++; /*this element you have already sorted so the left is now the second element*/
    }
    else{
      y[yIndex] = x[rightIndex];
      rightIndex++; 
    }
    yIndex++;
  }

  /*What if one of the arrays is out of elements?*/
  while(leftIndex <= middleIndex){ /*if there are still elements in the fist array*/
    y[yIndex] = x[leftIndex];
    leftIndex++;
    yIndex++;
  }

  while(rightIndex <= right){ /*if there are still elements in the second array*/
    y[yIndex] = x[rightIndex];
    rightIndex++;
    yIndex++;
  }
  
}

/*Merge sort
* O = n * log(n) // n for merging 
* for calling: x to sort; y sorted array for output; left = 0; right = size - 1
*/
void merge_sort(int x[], int y[], int left, int right){
  if(left == right){/*arrays of the size 1*/
    return; /*stop for the recursion*/
  } 

  /*now split the array
  * actually you do not split the array you only create a "pointers" for the "splitted arrays"
  */
  int middle = (left + right)/2;
  merge_sort(x, y, left, middle); 
  merge_sort(x, y, middle + 1, right);
  merge(x, y, left, right);

  for(int i = left; i <= right; i++){
    x[i] = y[i];
  }
  
}

/* Quick sort
*procedure quicksort(List values)
    if values.size <= 1 then
        return values

    pivot = náhodný prvek z values

    Rozděl seznam values do 3 seznamů
        seznam1 = { prvky větší než pivot }
        seznam2 = { pivot }
        seznam3 = { prvky menší než pivot }
    
    return quicksort(seznam1) + seznam2 + quicksort(seznam3)
*/
/* O = n*log(n), but if you choose bad pivot could be even n^2 */
/*better for big non-pre-sorted arrays
* for last smaller arrays it is better to use for example insertion selection_sort*/
void quick_sort(int arr[], int left, int right){
  if(left == right){ /*array of size 1*/
    return;
  }

  int pivot = arr[left]; /*just choose some*/
  int index = left; /*index of last pre-sorted element*/

  for(int i = left + 1; i < right; i++){
    if(arr[i] > pivot){
      /*swap last not pre-sorted with this bigger element*/
      int a = arr[++index];
      arr[index] = arr[i];
      arr[i] = a;
    }
  }
  /*finally move the pivot at the end of the pre-sorted area*/
  int a = arr[index];
  arr[index] = arr[left];
  arr[left] = a;

  /*cut the array and run the sort again*/
  quick_sort(arr, left, index); /*bigger than pivot*/
  quick_sort(arr, index + 1, right); /*smalled than pivot*/
  
}

/* printing function*/
void print_array(int size, int *param_array){
  for(int i = 0; i < size; i++){
    printf("%d\t ", param_array[i]);
    printf("\n");
  }
}

int main(void) {
  
  /* Before you change number of elemetns in the set, update ELEMENTS constant*/
  int pole1[] = {4, 5, 6, 0, 7, 2, 9, 7, 1, 8, -1, 3};
  int pole2[ELEMENTS];

  quick_sort(pole1, 0, ELEMENTS);
  print_array(ELEMENTS, pole1);

  return 0;
}