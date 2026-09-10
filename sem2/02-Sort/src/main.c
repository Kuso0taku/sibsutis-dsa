#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <sort.h>
#include <utils.h>

int main() {
  srand(time(NULL));

  size_t size = 1000000;
  uint32_t mx = 100000;
  uint32_t* arr = (uint32_t*)malloc(size * sizeof(uint32_t));
  fillarr_uint32_t(arr, size, 0, mx);

  size_t rows = 20;
  size_t N=50000;
  size_t n=N;
  double t=0;

  printf("TABLE 2\n");
  printf("#,n,radix_sort,merge_sort,heap_sort,selection_sort\n");

  for (size_t i=1; i<=rows; i++) {
    n = N*i;
    printf("%zu,%zu,", i, n);
    
    t = wtime();
    radix_sort(arr, n);
    t = wtime() - t;
    fillarr_uint32_t(arr, n, 0, mx);
    printf("%.9lf,", t);

    t = wtime();
    merge_sort(arr, n);
    t = wtime() - t;
    fillarr_uint32_t(arr, n, 0, mx);
    printf("%.9lf,", t);

    t = wtime();
    heap_sort(arr, n);
    t = wtime() - t;
    fillarr_uint32_t(arr, n, 0, mx);
    printf("%.9lf,", t);

    t = wtime();
    selection_sort(arr, n);
    t = wtime() - t;
    fillarr_uint32_t(arr, n, 0, mx);
    printf("%.9lf\n", t);
  }

  free(arr);
  return 0;
}
