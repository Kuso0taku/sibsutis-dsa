#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <utils.h>
#include "sort.h"
#include "search.h"

int main() {
  srand(time(NULL));
  
  int n = 5000000;
  int* arr = (int*)malloc(n * sizeof(int));
  int* sorted = (int*)malloc(n * sizeof(int));
  fillarr(arr, n, 0, 10000000);
  memcpy(sorted, arr, n * sizeof(int));
  merge_sort(sorted, n);
  
  double t=0;
  int n1 = 1000;
  long long n2 = pow(10, 7);
  int* srch = (int*)malloc(n2 * sizeof(int));

  printf("\ttable 1\n");
  printf("#,array_size,linear,binary,exp\n");

  for (int i=1; i<=20; i++) {
    n = 250000*i;

    fillarr(arr, n, 0, 10000000);
    memcpy(sorted, arr, n * sizeof(int));
    merge_sort(sorted, n);
    for (int j=0; j<n2; j++) *(srch+j) = *(sorted + rand()%n);

    printf("%d,%d,", i,n);

    t = wtime();
    for (int j=0; j<n1; j++) {
      linear_search(sorted, n, *(srch+j));
    }
    t = (wtime() - t)/n1;
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<n2; j++) {
      binary_search(sorted, n, *(srch+j));
    }
    t = (wtime() - t)/n2;
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<n2; j++) {
      exp_search(sorted, n, *(srch+j));
    }
    t = (wtime() - t)/n2;
    printf("%.9lf\n", t);
  }

  free(sorted);
  
  printf("\n\ttable 2\n");
  printf("#,array_size,n_search,sort,linear,binary,sort+binary\n");
  
  n = 1000000;
  double st=0;

  for (int i=1; i<=10; i++) {
    printf("%d,%d,%d,", i, n, i*50);

    fillarr(arr, n, 0, 10000000);
    
    st = wtime();
    merge_sort(arr, n);
    st = (wtime() - st);
    printf("%.9lf,", st);

    for (int j=0; j<i*50; j++) *(srch+j) = *(arr + rand()%n);

    t = wtime();
    for (int j=0; j<i*50; j++) {
      linear_search(arr, n, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<i*50; j++) {
      binary_search(arr, n, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    printf("%.9lf\n", t+st);
  }

  n = 5000000;

  for (int i=1; i<=10; i++) {
    printf("%d,%d,%d,", i+10, n, i*100);

    fillarr(arr, n, 0, 10000000);
    
    st = wtime();
    merge_sort(arr, n);
    st = (wtime() - st);
    printf("%.9lf,", st);

    for (int j=0; j<i*100; j++) *(srch+j) = *(arr + rand()%n);

    t = wtime();
    for (int j=0; j<i*100; j++) {
      linear_search(arr, n, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<i*100; j++) {
      binary_search(arr, n, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    printf("%.9lf\n", t+st);
  }

  free(arr);
  free(srch);
  return 0;
}
