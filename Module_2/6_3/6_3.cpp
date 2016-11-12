#include <iostream>
#include <vector>
#include <stdint.h>

#define BITSCOUNT 63

typedef unsigned long long size_tt;

// Проверка наличия единицы в раряде под номером индекса
inline bool IsDigit(size_tt number, int index) {
	return number & ((size_tt)1 << index);
}

void Swap(size_tt& a, size_tt& b) {
	size_tt temp = a;
	a = b;
	b = temp;
}

// Бинарная сортировка по старшему биту
template <class RandomAccessIterator>
void BinaryMSD(RandomAccessIterator begin, RandomAccessIterator end, int bits) {
	auto i = begin;
	auto j = end;
	
	if (end <= begin ||bits < 0)
		return;
		
	while (j != i) {
	
		while (!IsDigit(*i, bits) && (i < j)) {
			++i;
		}
		
		while (IsDigit(*j, bits) && (j > i)) {
			--j;
		}
		
		std::iter_swap(i, j);
	}
	
	if (!IsDigit(*end, bits)) {
		++j;
	}
	
	BinaryMSD(begin, j - 1, bits - 1);
	BinaryMSD(j, end, bits - 1);
}

int main() {
	size_t elements_count{};
	std::cin >> elements_count;
	
	std::vector<size_tt> vec;
	for (size_t i{}; i < elements_count; ++i) {
		size_tt item{};
		std::cin >> item;
		
		vec.push_back(item);
	}
	
	BinaryMSD(std::begin(vec), std::end(vec) - 1, BITSCOUNT);
	
	for (auto iter : vec) {
		std::cout << iter << ' ';
	}
	std::cout << std::endl;
	
	return 0;
}
