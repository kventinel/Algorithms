#include <iostream>
#include <vector>
#include <utility>

template<typename T>
void BubbleSort(T begin, T end);

int
SearchPivot(std::vector<int>::iterator begin, std::vector<int>::iterator end);

int
SearchKStat(std::vector<int>::iterator begin, std::vector<int>::iterator end,
            size_t k);

std::pair<std::vector<int>::iterator, std::vector<int>::iterator>
Partition(std::vector<int>::iterator begin, std::vector<int>::iterator end,
          int pivot);

template<typename T>
void BubbleSort(T begin, T end) {
  for (size_t i = 0; i < (end - begin) - 1; ++i) {
    for (size_t j = 0; j < (end - begin) - i - 1; ++j) {
      if (*(begin + j) > *(begin + j + 1)) {
        std::swap(*(begin + j), *(begin + j + 1));
      }
    }
  }
}

int
SearchPivot(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  int arr[5];
  std::vector<int> arr_mid;
  size_t arr_it = 0;
  while (begin != end) {
    if (arr_it == 5) {
      BubbleSort(arr, arr + 5);
      arr_mid.push_back(arr[2]);
      arr_it = 0;
    }
    arr[arr_it] = *begin;
    ++arr_it;
    ++begin;
  }
  if (arr_it != 0) {
    BubbleSort(arr, arr + arr_it);
    arr_mid.push_back(arr[arr_it / 2]);
  }
  if (arr_mid.size() > 10) {
    return SearchKStat(arr_mid.begin(), arr_mid.end(), arr_mid.size() / 2);
  } else {
    BubbleSort(arr_mid.begin(), arr_mid.end());
    return arr_mid[arr_mid.size() / 2];
  }
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator>
Partition(std::vector<int>::iterator begin, std::vector<int>::iterator end,
          int pivot) {
  auto smaller = begin;
  auto larger = end;
  auto it = begin;
  while (it != larger) {
    if (*it < pivot) {
      std::swap(*smaller, *it);
      ++it;
      ++smaller;
    } else if (*it > pivot) {
      --larger;
      std::swap(*it, *larger);
    } else {
      ++it;
    }
  }
  return std::pair<std::vector<int>::iterator, std::vector<int>::iterator>(
      smaller, larger);
}

int
SearchKStat(std::vector<int>::iterator begin, std::vector<int>::iterator end,
            size_t k) {
  if (end - begin < 10) {
    BubbleSort(begin, end);
    return *(begin + k - 1);
  }
  int pivot = SearchPivot(begin, end);
  auto middle = Partition(begin, end, pivot);
  int answer;
  if (k <= middle.first - begin) {
    answer = SearchKStat(begin, middle.first, k);
  } else if (k <= middle.second - begin) {
    answer = SearchKStat(middle.first, middle.second, k - (middle.first - begin));
  } else {
    answer = SearchKStat(middle.second, end, k - (middle.second - begin));
  }
  return answer;
}

int main() {
  size_t T;
  std::cin >> T;
  while (T > 0) {
    --T;
    size_t n, k;
    std::cin >> n >> k;
    std::vector<int> v(n);
    for (size_t i = 0; i < n; ++i) {
      std::cin >> v[i];
    }
    int answer = SearchKStat(v.begin(), v.end(), k);
    std::cout << answer << std::endl;
  }
  return 0;
}