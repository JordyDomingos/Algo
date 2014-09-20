#include <iostream>
#include <vector>

#include <cstdlib>

template<class T>
std::vector<T> Merge(const std::vector<T> &left, const std::vector<T> &right) {
  std::vector<T> merged_array;
  int i = 0;
  int j = 0;

  while (i + j < left.size() + right.size()) {
    if ((j >= right.size()) ||
	(i < left.size() && j < right.size() && left[i] <= right[j]))
      merged_array.push_back(left[i++]);
    else
      merged_array.push_back(right[j++]);
  }
  return merged_array;
}

template<class T>
std::vector<T> MergeSort(const std::vector<T> &array) {
  if (array.size() > 1) {
    int middle = array.size() / 2;
    std::vector<T> left(array.begin(), array.begin() + middle);
    std::vector<T> right(array.begin() + middle, array.end());
    left = MergeSort(left);
    right = MergeSort(right);
    return Merge(left, right);
  }
  return array;
}

// This main is used for tests with integer.
int main(int argc, char **argv) {
  std::vector<int> array;
  for (int i = 1; i < argc; ++i) {
    array.push_back(atoi(argv[i]));
  }
  array = MergeSort<int>(array);
  std::cout << "Final array : ";
  for (auto value : array) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}
