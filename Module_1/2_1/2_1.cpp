#include <iostream>

// Dynamically allocate and deallocate memory for 1d array
struct CArray {
	int* base;
	int size;

	CArray(int array_size) {
		base = new int[array_size];
		size = array_size;
	}

	~CArray() {
		delete [] base;

		base = nullptr;
		size = 0;
	}
};

// Stores indexes
struct Indexes {
	int a_index;
	int b_index;
};

// Filling array from stdin
void FillArray(CArray& array) {
	for (int i = 0; i < array.size; ++i) {
		std::cin >> array.base[i];
	}
}

// ???
// Не знаю как сделать за один обход, т.к, если
// в худшем случае, первый в первом массиве максимальный,
// а последний во втором массиве максимальный, нужно 2 цикла. Например:
//   4 -8  1  0
// -10  3  1  5

// Seeking max sum of elements and return their indexes
Indexes GetMaxSumOfElements(CArray& a, CArray& b){
	Indexes idx;
	idx.a_index = 0;
	idx.b_index = 0;

	int sum = a.base[0] + b.base[0];
	int current_max = a.base[0];
	int current_max_index = 0;

	for (int i = 1; i < a.size; ++i) {

		if (current_max < a.base[i]) {
			current_max = a.base[i];
			current_max_index = i;
		}

		int current_sum = current_max + b.base[i];

		if (current_sum > sum) {
			sum = current_sum;
			idx.b_index = i;
			idx.a_index = current_max_index;
		}
	}

	return idx;
}

int main(){
	int length_of_arrays;
	std::cin >> length_of_arrays;

	CArray a(length_of_arrays), b(length_of_arrays);

	FillArray(a);
	FillArray(b);

	Indexes idx = GetMaxSumOfElements(a, b);

	std::cout << idx.a_index << ' ' << idx.b_index << std::endl;

	return 0;
}