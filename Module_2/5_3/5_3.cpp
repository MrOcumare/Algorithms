#include <iostream>
#include <vector>
#include <stdint.h>

template <typename RandomAccessIterator>
int64_t BubbleSort(RandomAccessIterator begin, RandomAccessIterator end) {
  	int64_t count{};
  	bool swapped = true;
  	
  	while (begin != end-- && swapped) {
    	swapped = false;
    	
    	for (auto i = begin; i < end; ++i) {
      		
      		if (*(i + 1) < *i) {
       	 		std::iter_swap(i, i + 1);
       	 		++count;
        		swapped = true;
      		}      		
    	}
  	}
  	
  	return count;
}

template <typename RandomAccessIterator>
int64_t InsertionSort(RandomAccessIterator begin, RandomAccessIterator end) {
	int64_t count{};
	
	for (RandomAccessIterator iter = begin + 1; iter != end; ++iter) {
		size_t current_distance = std::distance(begin, iter);
		
		for (size_t j = current_distance; j > 0 && *(begin + j - 1) > *(begin + j); --j) {
			std::iter_swap(begin + j, begin + j - 1);
			++count;
		}
	}
	
	return count;
}

int main() {
	std::vector<int> vec;

	while (!std::cin.eof()) {
		int item;
		std::cin >> item;
		
		vec.push_back(item);
	}
	
	vec.resize(vec.size() - 1);
	
	std::cout << InsertionSort(std::begin(vec), std::end(vec)) << std::endl;
	
	for (auto iter : vec) {
		std::cout << iter << ' ';
	}
	
	std::cout << std::endl;

	return 0;
}
