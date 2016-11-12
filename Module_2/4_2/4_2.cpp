#include <iostream>
#include <vector>

// Quicksort implementation for C++11

template <typename RandomAccessIterator>
const RandomAccessIterator FindMedian(const RandomAccessIterator first, const RandomAccessIterator last) {
	const auto middle = first + ((last - first) / 2);
	
	if (*first < *middle) {

		if (*middle < *last) {
			return middle;
		} else if (*first < *last) {
			return last;
		} else{
			return first;
		}
	} else {
		if (*first < *last) {
			return first;
		} else if (*middle < *last) {
			return last;
		} else {
			return middle;
		}
	}
}

template <typename RandomAccessIterator>
const RandomAccessIterator Partition(const RandomAccessIterator begin, const RandomAccessIterator end) {
	const auto pivot = FindMedian(begin, end);
	
	std::iter_swap(begin, pivot);
	
	auto i = end;
	auto j = end;
	
	for (; j > begin; --j) {
		
		if (*j >= *begin) {
			std::iter_swap(i, j);
			--i;
		}
	}
	
	std::iter_swap(begin, i);

	return i;
}

//template <typename RandomAccessIterator>
//void QuickSort(RandomAccessIterator begin, RandomAccessIterator end) {
//	if (begin >= end) {
//		return;
//	}

//	auto pivot = Partition(begin, end);
//	QuickSort(begin, pivot - 1);
//	QuickSort(pivot + 1, end);
//}

template <class RandomAccessIterator>
size_t FindKStatistics(const RandomAccessIterator begin, const RandomAccessIterator end, size_t index) {
	
	auto first = begin;
	auto last = end;
	
    while (true) {
        auto pivot = Partition(first, last);
        int pivot_element_position = pivot - begin;
        
        if (pivot_element_position == index) {
            return *(begin + index);
        } else if (pivot_element_position > index) {
            last = pivot;
        } else {
            first = pivot + 1;
        }
    }
}

int main() {
	size_t element_count{};
	std::cin >> element_count;
	
	size_t index{};
	std::cin >> index;
	
	std::vector<int> vec;
	for (size_t i{}; i < element_count; ++i) {
		int item;
		std::cin >> item;
		
		vec.push_back(item);
	}
	
//	QuickSort(std::begin(vec), std::end(vec) - 1);
//	
//	for (auto iter : vec) {
//		std::cout << iter << ' ';
//	}
//	
//	std::cout << std::endl;

	std::cout << FindKStatistics(std::begin(vec), std::end(vec) - 1, index) << std::endl;

	return 0;
}
