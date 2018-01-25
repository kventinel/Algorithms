#include <iostream>
#include <vector>

class SegmentTree{
public:
	SegmentTree(int32_t size, bool top_min);
	void add(int32_t number, int32_t pos);
	std::pair<int32_t, int32_t> get();
	int32_t size();
	void remove(int32_t pos);
	int64_t sum();
private:
	std::vector<int32_t> data_;
	int32_t size_;
	int32_t default_;
	bool top_min_;
	int64_t sum_; 

	int32_t compare(int32_t a, int32_t b);
};

SegmentTree::SegmentTree(int32_t size, bool top_min) {
	int32_t data_size = 1;
	while (data_size < size) {
		data_size *= 2;
	}
	data_size *= 2;
	if (!top_min) {
		default_ = -1;
	} else {
		default_ = INT32_MAX;
	}
	data_.resize(data_size, default_);
	size_ = 0;
    sum_ = 0;
	top_min_ = top_min;
}

void SegmentTree::add(int32_t number, int32_t pos) {
	size_ += 1;
	pos += data_.size() / 2;
	sum_ += number;
	data_[pos] = number;
	while (pos > 1) {
		pos /= 2;
		data_[pos] = compare(data_[pos * 2], data_[pos * 2 + 1]);
	}
}

std::pair<int32_t, int32_t> SegmentTree::get() {
    int32_t pos = 1;
    while (pos * 2 < data_.size()) {
        if (data_[pos] == data_[pos * 2]) {
            pos *= 2;
        } else {
            pos = pos * 2 + 1;
        }
    }
    return std::make_pair(data_[pos], pos - data_.size() / 2);
}

int32_t SegmentTree::size() {
    return size_;
}

void SegmentTree::remove(int32_t pos) {
    pos += data_.size() / 2;
    if (data_[pos] == default_) {
        return;
    }
    size_ -= 1;
    sum_ -= data_[pos];
    data_[pos] = default_;
    while (pos > 1) {
        pos /= 2;
        data_[pos] = compare(data_[pos * 2], data_[pos * 2 + 1]);
    }
}

int64_t SegmentTree::sum() {
    return sum_;
}

int32_t SegmentTree::compare(int32_t a, int32_t b) {
    return top_min_ ? std::min(a, b) : std::max(a, b);
}

int64_t get_ans(SegmentTree *on_min, SegmentTree *on_max) {
    while (on_min->size() > on_max->size()) {
        std::pair<int32_t, int32_t> number = on_min->get();
        on_min->remove(number.second);
        on_max->add(number.first, number.second);
    }
    while (on_max->size() > on_min->size()) {
        std::pair<int32_t, int32_t> number = on_max->get();
        on_max->remove(number.second);
        on_min->add(number.first, number.second);
    }
    int64_t number = on_min->get().first;
    return on_min->sum() - number * on_min->size() +
           number * on_max->size() - on_max->sum();
}

int main() {
	int32_t n, W;
	std::cin >> n >> W;
	SegmentTree on_min(W, true);
	SegmentTree on_max(W, false);
	for (int32_t i = 0; i < W; ++i) {
		int32_t temp;
		std::cin >> temp;
		on_min.add(temp, i);
	}
    int64_t answer = get_ans(&on_min, &on_max);
    for (int32_t i = W; i < n; ++i) {
        int32_t temp;
        std::cin >> temp;
        on_min.remove(i % W);
        on_max.remove(i % W);
        get_ans(&on_min, &on_max);
        on_min.add(temp, i % W);
        answer = std::min(answer, get_ans(&on_min, &on_max));
    }
    std::cout << answer << std::endl;
    return 0;
}