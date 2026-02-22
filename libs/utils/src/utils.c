#include <time.h>
#include <stdlib.h>
#include <utils.h>

// current time
double wtime() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1E-9;
}

// generate random number
int getrand_int(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

uint32_t getrand_uint32(uint32_t min, uint32_t max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

// fill the array with random numbers
int* fillarr_int(int* arr, size_t n, int min, int max) {
  if (n==0) return NULL;
  for (size_t i=0; i<n; i++) *(arr+i) = getrand_int(min, max);
  return arr;
}

uint32_t* fillarr_uint32(uint32_t* arr, size_t n, uint32_t min, uint32_t max) {
  if (n==0) return NULL;
  for (size_t i=0; i<n; i++) *(arr+i) = getrand_uint32(min, max);
  return arr;
}
