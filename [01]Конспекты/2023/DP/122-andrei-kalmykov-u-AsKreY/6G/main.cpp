#include <algorithm>
#include <iostream>
#include <vector>

const long long kMOD = 1e9 + 7;
const int kIncorrectMask = -10;

int Bit(int mask, int pos) {
  return static_cast<int>(((mask >> pos) & 1) != 0);
}

bool IsMaskValid(const std::vector<std::vector<short>>& unfinished_mask,
                 int ind, int mask, int length) {
  for (int i = 0; i < length; ++i) {
    if (unfinished_mask[i][ind] == 2) {
      continue;
    }
    if ((unfinished_mask[i][ind] ^ Bit(mask, i)) != 0) {
      return false;
    }
  }
  return true;
}

int GenMask(int prev_mask, bool upper_element, const int kMaskLength) {
  const int kThree = 3;
  int mask = static_cast<int>(upper_element);
  for (int i = 1; i < kMaskLength; ++i) {
    if (Bit(prev_mask, i) + Bit(prev_mask, i - 1) + Bit(mask, i - 1) == 1) {
      mask |= (1 << i);
    } else if ((Bit(prev_mask, i) + Bit(prev_mask, i - 1) + Bit(mask, i - 1)) %
                   kThree ==
               0) {
      return kIncorrectMask;
    }
  }
  return mask;
}

bool IsFinishedValid(int new_mask, int mask, const int kMaskLength) {
  for (int i = 0; i < kMaskLength - 1; ++i) {
    if (Bit(new_mask, i) + Bit(new_mask, i + 1) + Bit(mask, i) +
            Bit(mask, i + 1) !=
        2) {
      return false;
    }
  }
  return true;
}

long long AnswerCalculation(const std::vector<std::vector<long long>>& masks) {
  long long ans = 0;
  for (const auto& i : masks[masks.size() - 1]) {
    ans += i;
    ans %= kMOD;
  }
  return ans;
}

bool FinalMaskCheck(int mask, const std::vector<std::vector<short>>& town,
                    int ind, int ind_sec, int length) {
  return (mask != kIncorrectMask && IsMaskValid(town, ind, mask, length) &&
          IsFinishedValid(mask, ind_sec, length));
}

long long NumberOfWays(int length, int width,
                       const std::vector<std::vector<short>>& town,
                       const long long kMaxMask) {
  std::vector<std::vector<long long>> number_of_masks(
      width, std::vector<long long>(kMaxMask, 0));
  for (int i = 0; i < kMaxMask; ++i) {
    number_of_masks[0][i] = static_cast<int>(IsMaskValid(town, 0, i, length));
  }
  for (int i = 1; i < width; ++i) {
    for (int j = 0; j < kMaxMask; ++j) {
      if (IsMaskValid(town, i - 1, j, length) && town[0][i] == 2) {
        int mask1 = GenMask(j, false, length);
        int mask2 = GenMask(j, true, length);
        if (FinalMaskCheck(mask1, town, i, j, length)) {
          number_of_masks[i][mask1] += number_of_masks[i - 1][j] %= kMOD;
        }
        if (FinalMaskCheck(mask2, town, i, j, length)) {
          number_of_masks[i][mask2] += number_of_masks[i - 1][j] %= kMOD;
        }
      } else if (IsMaskValid(town, i - 1, j, length)) {
        int mask = GenMask(j, town[0][i] != 0, length);
        if (FinalMaskCheck(mask, town, i, j, length)) {
          number_of_masks[i][mask] += number_of_masks[i - 1][j] %= kMOD;
        }
      }
    }
  }
  return AnswerCalculation(number_of_masks);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int length;
  int width;
  std::cin >> length >> width;
  std::vector<std::vector<short>> town(length, std::vector<short>(width));
  for (int i = 0; i < length; ++i) {
    for (int j = 0; j < width; ++j) {
      char tmp;
      std::cin >> tmp;
      if (tmp == '+') {
        town[i][j] = 1;
      } else if (tmp == '-') {
        town[i][j] = 0;
      } else {
        town[i][j] = 2;
      }
    }
  }
  std::cout << NumberOfWays(length, width, town, 1 << length);
}
