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
  //int x=0;
  int n1 = 1000;
  long long n2 = pow(10, 6);
  int* srch = (int*)malloc(n2 * sizeof(int));

  printf("\tTABLE 1\n");
  printf("#,array_size,linear,binary,exp\n");
  for (int i=1; i<=20; i++) {
    n = 250000*i;
    // x = *(arr + rand()%n);

    printf("%d,%d,", i,n);
    
    //for (int j=0; j<=n2; j++) *(srch+j) = *(sorted + rand()%n);

    t = wtime();
    for (int j=0; j<n1; j++) {
      linear_search(sorted, n, *(arr+j));
    }
    t = (wtime() - t)/n1;
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<n2; j++) {
      binary_search(sorted, n, *(arr+j));
    }
    t = (wtime() - t)/n2;
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<n2; j++) {
      exp_search(sorted, n, *(arr+j));
    }
    t = (wtime() - t)/n2;
    printf("%.9lf\n", t);
  }

  free(sorted);
  
  printf("\n\tTABLE 2\n");
  printf("#,array_size,sort,n_search,linear,binary,sort+binary\n");
  
  n = 1000000;
  double st=0;

  for (int i=1; i<=10; i++) {
    printf("%d,%d,", i, n);

    fillarr(arr, n, 0, 10000000);
    
    st = wtime();
    merge_sort(arr, n);
    st = (wtime() - st);
    printf("%.9lf,", st);

    for (int j=0; j<=i*50; j++) *(srch+j) = *(arr + rand()%n);

    t = wtime();
    for (int j=0; j<i*50; j++) {
      linear_search(arr, i*50, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<i*50; j++) {
      binary_search(arr, i*50, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    printf("%.9lf\n", t+st);
  }

  n = 5000000;

  for (int i=1; i<=10; i++) {
    printf("%d,%d,", i+10, n);

    fillarr(arr, n, 0, 10000000);
    
    st = wtime();
    merge_sort(arr, n);
    st = (wtime() - st);
    printf("%.9lf,", st);

    for (int j=1; j<=i*100; j++) *(srch+j) = *(arr + rand()%n);

    t = wtime();
    for (int j=0; j<i*100; j++) {
      linear_search(arr, i*100, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<i*100; j++) {
      binary_search(arr, i*100, *(srch+j));
    }
    t = (wtime() - t);
    printf("%.9lf,", t);

    printf("%.9lf\n", t+st);
  }

  free(arr);
  free(srch);
  return 0;
}
