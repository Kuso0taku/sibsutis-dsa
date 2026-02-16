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
  memcpy(sorted, arr, n);
  merge_sort(sorted, n);
  
  double t=0;
  int x=0;
  int n1 = 100;
  long long n2 = pow(10, 7);
  printf("#,n,linear,binary,exp\n");
  for (int i=1; i<=20; i++) {
    n = 250000*i;
    x = *(arr + rand()%n);

    printf("%d,%d,", i,n);
    
    t = wtime();
    for (int j=0; j<n1; j++) {
      linear_search(sorted, n, x);
    }
    t = (wtime() - t)/n1;
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<n2; j++) {
      binary_search(sorted, n, x);
    }
    t = (wtime() - t)/n2;
    printf("%.9lf,", t);

    t = wtime();
    for (int j=0; j<n2; j++) {
      exp_search(sorted, n, x);
    }
    t = (wtime() - t)/n2;
    printf("%.9lf\n", t);
  }
  
  return 0;
}
