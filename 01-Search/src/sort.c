#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *arr, int left, int mid, int right, int *tmp) {
  size_t i=0, j=0;

  while (left+i < mid && mid+j < right) {
    if (*(arr + left+i) < *(arr + mid+j)) {
      *(tmp + i+j) = *(arr + left+i);
      i++;
    } else {
      *(tmp +i+j) = *(arr + mid+j);
      j++;
    }
  }

  for (; left+i < mid; i++) *(tmp + i+j) = *(arr + left+i);
  for (; mid+j < right; j++) *(tmp + i+j) = *(arr + mid+j);
  
  memcpy(arr+left, tmp, (right-left) * sizeof(int));
}

void merge_sort(int* arr, int n) {
  if (n<2) return;

  int *tmp = (int*)malloc(n * sizeof(int));
  if (!tmp) return;
  
  size_t min=0;
  for (size_t i=1; i<n; i*=2)
    for (size_t j=0; j < n-i; j += 2*i) {
      min = (j+2*i < n) ? j+2*i : n;
      merge(arr, j, i+j, min, tmp);
    }

  free(tmp);
}
