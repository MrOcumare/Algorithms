#include <iostream>
#include <vector>
#include <stdint.h>

template <typename T>
int64_t Merge(std::vector<T>& a, std::vector<T>& temp, size_t left, size_t mid, size_t right) {
	int64_t counter{};
	
	size_t i = left;
	size_t j = mid;
	size_t k = left;
	
	while (i < mid && j <= right) {
		
		if (a[i] <= a[j]) {
			temp[k++] = a[i++];
		} else {
			temp[k++] = a[j++];
			counter += mid - i;
		}
	}
	
	while (i < mid) {
		temp[k++] = a[i++];
	}
	
	while (j <= right) {
		temp[k++] = a[j++];
	}
	
	for (i = left; i <= right; ++i) {
		a[i] = temp[i];
	}
	
	return counter;
}

template <typename T>
int64_t MergeSort(std::vector<T>& a, std::vector<T>& temp, size_t left, size_t right) {
	int64_t counter{};
	size_t mid;
	
	if (right > left) {
		mid = (right + left) / 2;
		counter = MergeSort(a, temp, left, mid);
		counter += MergeSort(a, temp, mid + 1, right);
		counter += Merge(a, temp, left, mid + 1, right);
	}
	
	return counter;
}
 
int main() {
    std::vector<int> vec;

	while (!std::cin.eof()) {
		int item;
		std::cin >> item;
		
		vec.push_back(item);
	}
	
	vec.resize(vec.size() - 1);
	std::vector<int> temp(vec.size());
	
	std::cout << MergeSort<int>(vec, temp, 0, vec.size() - 1) << std::endl;
	
//	for (auto iter : vec) {
//		std::cout << iter << ' ';
//	}
//	
//	std::cout << std::endl;
		
	return 0;
}
