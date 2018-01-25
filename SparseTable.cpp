#include <iostream>
#include <vector>

const double EPS = 1e-9;
const int MOD = 1000000007;

int fl(int len) {
    if (len == 1) return 0;
    return fl(len / 2) + 1;
}

int length(int degree) {
    if (degree == 0) return 1;
    return length(degree - 1) * 2;
}

class SparseTable {
public:
    SparseTable();

    ~SparseTable() {}

    std::pair<int, int> getTwoMin(int l, int r);
private:
    std::vector<std::vector<int>> table;
    std::vector<int> log;
    std::vector<int> len;
    std::vector<int> array;

    std::pair<int, int> getMin(int l, int r);
};

SparseTable::SparseTable() {
    int n;
    std::cin >> n;
    array.resize(n);
    log.resize(n);
    for (int &a : array) {
        std::cin >> a;
    }
    table.resize(fl(array.size()));
    table[0].resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        table[0][i] = i;
	if (array[i + 1] < array[i]) table[0][i] = i + 1;
        log[i] = fl(i + 1);
	if (i == 0 || log[i] != log[i - 1]) len.push_back(length(log[i]));
    }
    log[n - 1] = fl(n - 1);
    if (log[n - 2] != log[n - 1]) len.push_back(len[len.size() - 1] * 2);
    int p = 2;
    int degree = 1;
    while (2 * p < array.size()) {
        table[degree].reserve(array.size() - 2 * p + 1);
        for (int i = 0; i + 2 * p <= array.size(); ++i) {
            table[degree][i] = table[degree - 1][i];
	    if (array[table[degree - 1][i + p]] < array[table[degree - 1][i]])
	        table[degree][i] = table[degree - 1][i + p];
        }
        ++degree;
        p *= 2;
    }
}

std::pair<int, int> SparseTable::getMin(int l, int r) {
    int degree = log[r - l - 1];
    int p = len[degree];
    if (p == 1) return std::make_pair(array[l], l);
    if (array[table[degree - 1][l]] < array[table[degree - 1][r - p]])
        return std::make_pair(array[table[degree - 1][l]], table[degree - 1][l]);
    return std::make_pair(array[table[degree - 1][r - p]], table[degree - 1][r - p]);
}

std::pair<int, int> SparseTable::getTwoMin(int l, int r) {
    auto first_min = getMin(l, r);
    int second_min = INT32_MAX;
    if (first_min.second != l) second_min = std::min(second_min, getMin(l, first_min.second).first);
    if (first_min.second + 1 != r) second_min = std::min(second_min, 
		                                         getMin(first_min.second + 1, r).first);
    return std::make_pair(first_min.first, second_min);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    SparseTable sparseTable;
    int n;
    std::cin >> n;
    while (n--) {
        int l, r;
        std::cin >> l >> r;
        std::pair<int, int> min = sparseTable.getTwoMin(l, r);
        std::cout << min.first << " " << min.second << std::endl;
    }
    return 0;
}
