#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long ll;

int main() {
  ll n, p, q, max = -1;
  std::vector<ll> a;
  std::cin >> n >> p >> q;
  for (ll i = 0; i < n; ++i) {
    ll b;
    std::cin >> b;
    if (b > max) max = b;
    a.push_back(b);
  }
  if (p == q) {
    std::cout << (int) std::ceil(1.0 * max / p);
    return 0;
  }
  ll left = 1, right = std::ceil(1.0 * max / q), mid;
  while (left + 1 < right) {
    mid = (left + right) / 2;
    ll k = 0;
    for (auto i: a) {
      k += std::max(0, (int) std::ceil(1.0 * (i - mid * q) / (p - q)));
    }
    if (k < mid)
      right =
          mid;
    else left = mid;
  }
  ll i = left;
  while (true) {
    ll k = 0;
    for (auto j: a) {
      k += std::max(0, (int) std::ceil(1.0 * (j - i * q) / (p - q)));
    }
    if (k - i <= 0) {
      std::cout << i;
      return 0;
    }
    ++i;
  }
}
