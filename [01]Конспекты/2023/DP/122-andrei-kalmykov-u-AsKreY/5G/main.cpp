#include <iostream>
#include <vector>

int LengthOfMaxCommonSubsequence(const std::vector<int>& first_sequence,
                                 const std::vector<int>& second_sequence) {
  std::vector<int> max_subsequence_without_this_element(second_sequence.size());
  std::vector<int> max_subsequence_with_this_element(second_sequence.size());
  for (size_t i = 0; i < first_sequence.size(); ++i) {
    for (size_t j = 0; j < second_sequence.size(); ++j) {
      if (first_sequence[i] == second_sequence[j]) {
        max_subsequence_with_this_element[j] =
            (i * j != 0) ? 1 + max_subsequence_without_this_element[j - 1] : 1;
      } else {
        int max_subsequence_length_less_on_first_sequence =
            (i > 0) ? max_subsequence_without_this_element[j] : 0;
        int max_subsequence_length_less_on_second_sequence =
            (j > 0) ? max_subsequence_with_this_element[j - 1] : 0;
        max_subsequence_with_this_element[j] =
            std::max(max_subsequence_length_less_on_first_sequence,
                     max_subsequence_length_less_on_second_sequence);
      }
    }
    max_subsequence_without_this_element = max_subsequence_with_this_element;
  }
  return max_subsequence_with_this_element[second_sequence.size() - 1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_of_elements_in_first_sequence;
  std::cin >> number_of_elements_in_first_sequence;
  std::vector<int> first_sequence(number_of_elements_in_first_sequence);
  for (int i = 0; i < number_of_elements_in_first_sequence; ++i) {
    std::cin >> first_sequence[i];
  }
  int number_of_elements_in_second_sequence;
  std::cin >> number_of_elements_in_second_sequence;
  std::vector<int> second_sequence(number_of_elements_in_second_sequence);
  for (int i = 0; i < number_of_elements_in_second_sequence; ++i) {
    std::cin >> second_sequence[i];
  }
  std::cout << LengthOfMaxCommonSubsequence(first_sequence, second_sequence);
}
