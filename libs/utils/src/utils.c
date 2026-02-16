//#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <utils.h>

// current time
double wtime() {
  /*
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-9;
  */
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1E-9;
}

// generate random number
int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

// fill the array with random numbers
int* fillarr(int* arr, int n, int min, int max) {
  if (n==0) return NULL;
  for (int i=0; i<n; i++) *(arr+i) = getrand(min, max);
  return arr;
}
