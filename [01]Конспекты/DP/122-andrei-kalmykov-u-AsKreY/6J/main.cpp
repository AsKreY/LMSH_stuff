#include <iostream>
#include <vector>

bool Bit(int mask, int pos) { return ((mask >> pos) & 1) != 0; }

bool IsThereSquare(int mask1, int mask2, const int kMaskLength) {
  int mask_xor = mask1 ^ mask2;
  for (int i = 1; i < kMaskLength; ++i) {
    if (!Bit(mask_xor, i) && !Bit(mask_xor, i - 1) &&
        (Bit(mask1, i) == Bit(mask1, i - 1))) {
      return true;
    }
  }
  return false;
}

std::vector<std::vector<bool>> ProfilesTransitionComputation(
    int length_of_profile) {
  const int kMaxMask = 1 << length_of_profile;
  std::vector<std::vector<bool>> can_be_reached;
  can_be_reached.assign(kMaxMask, std::vector<bool>(kMaxMask, false));
  for (int i = 0; i < kMaxMask; ++i) {
    for (int j = 0; j < kMaxMask; ++j) {
      can_be_reached[i][j] = !IsThereSquare(i, j, length_of_profile);
    }
  }
  return can_be_reached;
}

long long SumOfLastRow(const std::vector<std::vector<long long>>& array) {
  long long ans = 0;
  for (const auto& i : array.back()) {
    ans += i;
  }
  return ans;
}

long long NumberOfBeautifulPatterns(int length, int width) {
  if (length > width) {
    std::swap(length, width);
  }
  const int kNumOfProfiles = 1 << length;
  std::vector<std::vector<bool>> profile_reachability =
      ProfilesTransitionComputation(length);
  std::vector<std::vector<long long>> number_of_ways_with_column_profile;
  number_of_ways_with_column_profile.resize(
      width, std::vector<long long>(kNumOfProfiles, 0));
  for (int i = 0; i < kNumOfProfiles; ++i) {
    number_of_ways_with_column_profile[0][i] = 1;
  }
  for (int i = 1; i < width; ++i) {
    for (int j = 0; j < kNumOfProfiles; ++j) {
      for (int k = 0; k < kNumOfProfiles; ++k) {
        number_of_ways_with_column_profile[i][j] +=
            number_of_ways_with_column_profile[i - 1][k] *
            static_cast<long long>(profile_reachability[j][k]);
      }
    }
  }
  return SumOfLastRow(number_of_ways_with_column_profile);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int length;
  int width;
  std::cin >> length >> width;
  std::cout << NumberOfBeautifulPatterns(length, width);
}
