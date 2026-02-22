#include <stdlib.h> // malloc, free
#include <string.h> // memcpy
#include "../include/sort.h"

void counting_sort(uint32_t* arr, size_t n, uint32_t* tmp, uint8_t shift) {
  enum {BITS = 8, RADIX = 1 << BITS, MASK = RADIX - 1}; // make constants

  uint8_t digit=0;

  size_t counts[RADIX] = {0};
  
  for (size_t i=0; i<n; i++) {
    digit = (*(arr+i) >> shift) & MASK;
    (*(counts + digit))++;
  }

  size_t sum=0, temp=0;
  for (size_t i=0; i < RADIX; i++) {
    temp = *(counts+i);
    *(counts+i) = sum;
    sum += temp;
  }

  for (size_t i=0; i<n; i++) {
    digit = (*(arr+i) >> shift) & MASK;
    *(tmp + (*(counts + digit))++) = *(arr+i);
  }

  memcpy(arr, tmp, n * sizeof(uint32_t));
}

void radix_sort(uint32_t* arr, size_t n) {
  if (n <= 1) return;

  uint32_t *tmp = (uint32_t*)malloc(n * sizeof(uint32_t));
  if (!tmp) return;

  for (uint8_t shift=0; shift < 32; shift += 8) {
    counting_sort(arr, n, tmp, shift);
  }

  free(tmp);
}

void merge(uint32_t* arr, size_t left, size_t mid, size_t right, uint32_t *tmp) {
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
  
  memcpy(arr+left, tmp, (right-left) * sizeof(uint32_t));
}

void merge_sort(uint32_t* arr, size_t n) {
  if (n<2) return;

  uint32_t *tmp = (uint32_t*)malloc(n * sizeof(uint32_t));
  if (!tmp) return;
  
  uint32_t min=0;
  for (size_t i=1; i<n; i*=2)
    for (size_t j=0; j < n-i; j += 2*i) {
      min = (j+2*i < n) ? j+2*i : n;
      merge(arr, j, i+j, min, tmp);
    }

  free(tmp);
}
