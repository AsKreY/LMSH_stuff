#include <cmath>
#include <iostream>
#include <vector>

const long long kMOD = 1e9 + 7;

long long FastPow(long long arg, long long degree) {
  if (degree <= 1) {
    return arg % kMOD;
  }
  if (degree % 2 == 1) {
    return (arg * FastPow(arg, degree - 1)) % kMOD;
  }
  long long pow_2 = FastPow(arg, degree / 2) % kMOD;
  return (pow_2 * pow_2) % kMOD;
}

long long ModPow(long long arg, const std::vector<long long>& degree) {
  long long ans = FastPow(arg, degree[0]) % kMOD;
  for (size_t i = 1; i < degree.size(); ++i) {
    if (degree[i] != 1) {
      ans = (FastPow(ans, degree[i])) % kMOD;
    }
  }
  return ans % kMOD;
}

void ComputeProbability(const std::vector<long long>& elements) {
  long long denominator = ModPow(2, elements) % kMOD;
  bool is_even = false;
  for (const auto& i : elements) {
    if (i % 2 == 0) {
      is_even = true;
      break;
    }
  }
  const long long kTwoInv = 500000004;
  denominator = (denominator * kTwoInv) % kMOD;
  is_even = !is_even;
  const long long kThreeInv = 333333336;
  if (is_even) {
    std::cout << ((denominator + kMOD - 1) * kThreeInv) % kMOD;
  } else {
    std::cout << (((denominator + 1) % kMOD) * kThreeInv) % kMOD;
  }
  std::cout << '/' << denominator;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num_of_elements;
  std::cin >> num_of_elements;
  std::vector<long long> elements(num_of_elements);
  for (int i = 0; i < num_of_elements; ++i) {
    std::cin >> elements[i];
  }
  ComputeProbability(elements);
}
