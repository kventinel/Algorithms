#include <iostream>
#include <vector>
#include <list>

void input(std::vector<std::vector<u_int32_t> >* matrix, u_int32_t* c) {
  u_int32_t n, a, b, d;
  std::cin >> n >> a >> b >> *c >> d;
  *matrix = std::move(std::vector<std::vector<u_int32_t> >
                          (n, std::vector<u_int32_t>(n + 1)));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      (*matrix)[i][j] = d;
      d = (a * d + b) % *c;
    }
    (*matrix)[i][n] = u_int32_t(i);
  }
}

void Iteration(std::vector<std::vector<u_int32_t> >* matrix,
               size_t index, u_int32_t c) {
  std::vector<std::list<size_t> > partition(c, std::list<size_t>());
  for (size_t i = 0; i < matrix->size(); ++i) {
    partition[(*matrix)[i][index]].push_back(i);
  }
  std::vector<std::vector<u_int32_t> > sorted_matrix(matrix->size());
  size_t index_sorted = 0;
  for (size_t i = 0; i < c; ++i) {
    auto it_partition = partition[i].begin();
    while (it_partition != partition[i].end()) {
      sorted_matrix[index_sorted] = std::move((*matrix)[*it_partition]);
      ++index_sorted;
      ++it_partition;
    }
  }
  *matrix = std::move(sorted_matrix);
}

void RadixSort(std::vector<std::vector<u_int32_t> >* matrix, u_int32_t c) {
  for (int i = int(matrix->size()) - 1; i >= 0; --i) {
    Iteration(matrix, size_t(i), c);
  }
}

void output(const std::vector<std::vector<u_int32_t> > &matrix) {
  for (size_t i = 0; i < matrix.size(); ++i) {
    if (i != 0) {
      std::cout << " ";
    }
    std::cout << matrix[i][matrix.size()];
  }
  std::cout << std::endl;
}

int main() {
  std::vector<std::vector<u_int32_t> > matrix;
  u_int32_t c;
  input(&matrix, &c);
  RadixSort(&matrix, c);
  output(matrix);
  return 0;
}