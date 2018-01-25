#include <iostream>
#include <vector>
#include <utility>

void
QSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  while(end - begin > 1) {
    size_t size = end - begin;
    long long pivot = 0;
    for(auto i = begin; i != end; ++i) {
      pivot += *i;
    }
    pivot /= size;
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
      } else{
        ++it;
      }
    }
    if (smaller - begin > end - larger) {
      QSort(larger, end);
      end = smaller;
    } else {
      QSort(begin, smaller);
      begin = larger;
    }
  }
}

int main() {
  size_t size;
  std::cin >> size;
  std::vector<int> time(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> time[i];
  }
  QSort(time.begin(), time.end());
  long long time_for_this = 0;
  long long sum_time = 0;
  for(size_t i = 0; i < size; ++i) {
    sum_time += time_for_this;
    time_for_this += time[i];
  }
  std::cout << sum_time << std::endl;
  return 0;
}