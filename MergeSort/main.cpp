#include <iostream>
#include <vector>
#include <utility>

void BubbleSort(std::vector<u_int32_t>::iterator begin,
                std::vector<u_int32_t>::iterator end) {
  for (size_t i = 0; i < (end - begin) - 1; ++i) {
    for (size_t j = 0; j < (end - begin) - i - 1; ++j) {
      if (*(begin + j) > *(begin + j + 1)) {
        std::swap(*(begin + j), *(begin + j + 1));
      }
    }
  }
}

void HalfMerge(std::vector<u_int32_t>::iterator begin,
               std::vector<u_int32_t>::iterator end,
               std::vector<u_int32_t>::iterator buf) {
  static const size_t other_sort = 10;
  if ((end - begin) < other_sort) {
    BubbleSort(begin, end);
  } else {
    auto mid = begin + (end - begin) / 2;
    HalfMerge(begin, mid, buf);
    HalfMerge(mid, end, buf);
    auto first = begin;
    auto second = mid;
    auto end_buf = buf;
    while(first != mid && second != end) {
      if(*first < *second) {
        std::swap(*first, *end_buf);
        ++first;
      } else {
        std::swap(*second, *end_buf);
        ++second;
      }
      ++end_buf;
    }
    while(first != mid) {
      std::swap(*first, *end_buf);
      ++first;
      ++end_buf;
    }
    while(second != end) {
      std::swap(*second, *end_buf);
      ++second;
      ++end_buf;
    }
    while(begin != end) {
      std::swap(*begin, *buf);
      ++begin;
      ++buf;
    }
  }
}

void MergeSort(std::vector<u_int32_t>::iterator begin,
               std::vector<u_int32_t>::iterator end) {
  static const size_t other_sort = 10;
  static std::vector<u_int64_t> temp(other_sort); //small array for final sort
  if ((end - begin) < other_sort) {
    BubbleSort(begin, end);
  } else {
    auto second_sort_part = begin + (end - begin) / 2;
    if(second_sort_part - begin < end - second_sort_part) {
      ++second_sort_part;
    }
    HalfMerge(second_sort_part, end, begin); //buf.......
    while (second_sort_part - begin > other_sort) {
      auto unsort_part = begin + (second_sort_part - begin) / 2;
      if ((second_sort_part - begin) % 2 != 0) {
        ++unsort_part;
        ++second_sort_part;
      }
      HalfMerge(begin, unsort_part, unsort_part);  //...buf......
      auto first_sort_part = begin;
      while (unsort_part != second_sort_part) {
        if (second_sort_part == end ||
            *first_sort_part < *second_sort_part) {
          std::swap(*first_sort_part, *unsort_part);
          ++first_sort_part;
          ++unsort_part;
        } else {
          std::swap(*unsort_part, *second_sort_part);
          ++unsort_part;
          ++second_sort_part;
        }
      }
      second_sort_part = first_sort_part;
    }
    size_t size = second_sort_part - begin;
    BubbleSort(begin, second_sort_part);
    for (auto i = begin; i != second_sort_part; ++i) {
      temp[i - begin] = *i;
    }
    size_t temp_it = 0;
    auto first_unsort = begin;
    while (first_unsort != second_sort_part) {
      if (second_sort_part != end && *second_sort_part < temp[temp_it]) {
        std::swap(*first_unsort, *second_sort_part);
        ++first_unsort;
        ++second_sort_part;
      } else {
        *first_unsort = temp[temp_it];
        ++temp_it;
        ++first_unsort;
      }
    }
  }
}

int main() {
  size_t size = 0;
  std::cin >> size;
  std::vector<u_int32_t> time(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> time[i];
  }
  MergeSort(time.begin(), time.end());
  u_int64_t time_for_this = 0;
  u_int64_t sum_time = 0;
  for (size_t i = 0; i < size; ++i) {
    sum_time += time_for_this;
    time_for_this += time[i];
  }
  std::cout << sum_time << std::endl;
  return 0;
}