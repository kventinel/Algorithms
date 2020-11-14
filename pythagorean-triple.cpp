#include <iostream>
#include <set>
#include <vector>


struct VecCmp {
    bool operator()(const std::vector<int> &a, const std::vector<int> &b) const {
        assert(a.size() == 3);
        assert(b.size() == 3);
        return a[2] < b[2];
    }
};


int main(int argc, char **argv) {
    assert(argc == 2);
    int maxN = atoi(argv[1]);
    std::set<std::vector<int>, VecCmp> triples;
    for (int m = 2; m * m < maxN; ++m) {
        for (int n = 1; n < m; ++n) {
            int a = m * m - n * n;
            int b = 2 * m * n;
            if (b < a) {
                std::swap(a, b);
            }
            int c = m * m + n * n;
            for (int k = 1; k * c <= maxN; ++k) {
                triples.insert(std::vector<int>{a * k, b * k, c * k});
            }
        }
    }
    for (const std::vector<int> &triple : triples) {
        std::cout << triple[0] << " " << triple[1] << " " << triple[2] << std::endl;
    }
}
