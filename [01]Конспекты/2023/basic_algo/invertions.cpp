#include <iostream>
#include <fstream>

void merge(int *a, int first, int last, long long &k) {
  int mid = (first + last) / 2, b[100000], i = first;
  int j = mid;
  for (int h = first; h < last; ++h) {
    if ((i < mid) && ((j >= last) || (a[i] < a[j]))) {
      b[h] = a[i];
      i++;
    } else {
      b[h] = a[j];
      k += mid - i;
      j++;
    }
  }
  for (int h = first; h < last; ++h) a[h] = b[h];
}

void merge_sort(int *a, int first, int last, long long &k) {
  if (first + 1 < last) {
    merge_sort(a, first, (first + last) / 2, k);
    merge_sort(a, (first + last) / 2, last, k);
    merge(a, first, last, k);
  }
}

int main() {
  std::ifstream fin("inverse.in");
  std::ofstream fout("inverse.out");
  int n, a[100000];
  long long k = 0;
  fin >> n;
  for (int i = 0; i < n; ++i) fin >> a[i];
  merge_sort(a, 0, n, k);
  fout << k;
  fin.close();
  fout.close();
}
