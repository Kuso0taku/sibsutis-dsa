#include "search.h"

int linear_search(const int *arr, int n, int x) {
  for (int i=0; i<n; i++) if (*(arr+i) == x) return i;
  return -1;
}

int binary_search(const int *arr, int n, int x) {
  if (n==0) return -1;

  int left=0, mid=0, right = n-1;
  while (left <= right) {
    mid = left + (right - left)/2;
    if (*(arr+mid) == x) return mid;
    if (*(arr+mid) < x) left = mid+1;
    else right = mid-1;
  }
  return -1;
}

int exp_search(const int *arr, int n, int x) {
  if (n==0) return -1;
  if (*arr == x) return 0;

  int i=1;
  for (; i<n && *(arr+i) < x; i*=2);
  int res = binary_search(arr+i/2, ((i<n-1) ? i : n-1)-i/2 + 1, x);
  return (res==-1) ? -1 : (i/2+res);
}
