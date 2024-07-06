#include <iostream>
#include <vector>

template <class T>
void VectorCout(const std::vector<T>& array) {
  for (auto& i : array) {
    std::cout << i << ' ';
  }
}

class InformationForFinalSequence {
 private:
  int counter_ = 0;
  std::vector<int> previous_element_in_sequence_;

 public:
  InformationForFinalSequence() = default;
  ~InformationForFinalSequence() = default;
  InformationForFinalSequence(int counter, const std::vector<int>& array)
      : counter_(counter), previous_element_in_sequence_(array) {}
  int GetCounter() const { return counter_; }
  const std::vector<int>& GetPreviousElementInSequence() const {
    return previous_element_in_sequence_;
  }
};

std::vector<int> FinalSequenceIndexesGenerator(
    const InformationForFinalSequence& information) {
  std::vector<int> final_sequence_indexes;
  for (int i = information.GetCounter(); i != -1;
       i = information.GetPreviousElementInSequence()[i]) {
    final_sequence_indexes.push_back(i + 1);
  }
  return final_sequence_indexes;
}

void Solution(int number_of_elements, const std::vector<int>& array) {
  std::vector<int> max_last_element(number_of_elements, INT32_MIN);
  std::vector<int> non_growing_sequence_indexes(number_of_elements);
  std::vector<int> previous_element_in_sequence(number_of_elements, -1);
  int sequence_length = 1;
  max_last_element[0] = array[0];
  for (int i = 1; i < number_of_elements; ++i) {
    int left_border = -1;
    int right_border = number_of_elements - 1;
    int middle = (left_border + right_border) / 2;
    while (left_border + 1 < right_border) {
      (array[i] <= max_last_element[middle]) ? left_border = middle
                                             : right_border = middle;
      middle = (left_border + right_border) / 2;
    }
    if (max_last_element[right_border] == INT32_MIN) {
      ++sequence_length;
    }
    max_last_element[right_border] = array[i];
    non_growing_sequence_indexes[right_border] = i;
    previous_element_in_sequence[i] =
        (right_border == 0) ? -1
                            : non_growing_sequence_indexes[right_border - 1];
  }
  std::cout << sequence_length << '\n';
  VectorCout<int>(FinalSequenceIndexesGenerator(InformationForFinalSequence(
      non_growing_sequence_indexes[sequence_length - 1],
      previous_element_in_sequence)));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int number_of_elements;
  std::cin >> number_of_elements;
  std::vector<int> array(number_of_elements);
  for (int i = 0; i < number_of_elements; ++i) {
    std::cin >> array[i];
  }
  Solution(number_of_elements, array);
}
