#include <iostream>
#include <vector>

long long NumberOfPeacefulSets(int power_of_set) {
  std::vector<std::vector<long long>> number_of_sets_with_power_and_maximum(
      power_of_set + 1, std::vector<long long>(power_of_set + 1, 0));
  for (int i = 0; i < power_of_set + 1; ++i) {
    number_of_sets_with_power_and_maximum[i][i] = 1;
  }
  long long answer = 0;
  for (int i = 1; i < power_of_set + 1; ++i) {
    for (int j = 1; j < power_of_set + 1; ++j) {
      for (int k = 2 * j; k <= power_of_set - i; ++k) {
        number_of_sets_with_power_and_maximum[i + k][k] +=
            number_of_sets_with_power_and_maximum[i][j];
      }
      if (i == power_of_set) {
        answer += number_of_sets_with_power_and_maximum[i][j];
      }
    }
  }
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int power_of_set;
  std::cin >> power_of_set;
  std::cout << NumberOfPeacefulSets(power_of_set);
}
