#include <iostream>
#include <utility>
#include <vector>

#include <cstdlib>

template<class T>
std::pair<std::vector<T>, int> MergeAndCountSplitInversions(
    const std::vector<T> &left, const std::vector<T> &right) {
  std::vector<T> merged_array;
  int i = 0;
  int j = 0;
  int inversions_count = 0;

  while (i + j < left.size() + right.size()) {
    if ((j >= right.size()) ||
      (i < left.size() && j < right.size() && left[i] <= right[j])) {
      merged_array.push_back(left[i++]);
    } else {
      merged_array.push_back(right[j++]);
      inversions_count += left.size() - i;
    }
  }
  return std::pair<std::vector<T>, int>(merged_array, inversions_count);
}

template<class T>
std::pair<std::vector<T>, int> SortAndCountInversions(
    const std::pair<std::vector<T>, int> &array) {
  if (array.first.size() > 1) {
    int middle = array.first.size() / 2;
    std::vector<T> left_vector(array.first.begin(), array.first.begin() + middle);
    std::vector<T> right_vector(array.first.begin() + middle, array.first.end());
    std::pair<std::vector<T>, int> left(left_vector, 0);
    std::pair<std::vector<T>, int> right(right_vector, 0);

    left = SortAndCountInversions<int>(left);
    right = SortAndCountInversions<int>(right);
    std::pair<std::vector<T>, int> merge = MergeAndCountSplitInversions(
        left.first, right.first);
    merge.second = merge.second + left.second + right.second;
    return merge;
  }
  return array;
}

template<class T>
int CountInversions(std::vector<T> const &array) {
  return SortAndCountInversions<int>(std::pair<std::vector<T>, int>(array, 0)).second;
}

// This main is used for tests with integer.
int main(int argc, char **argv) {
  std::vector<int> array;
  for (int i = 1; i < argc; ++i) {
    array.push_back(atoi(argv[i]));
  }
  int nb_inversions = CountInversions<int>(array);
  std::cout << "The number of inversion is " << nb_inversions << std::endl;
}
