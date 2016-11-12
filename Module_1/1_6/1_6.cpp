#include <iostream>

// Dynamically allocating and deallocating memory for 1d array
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

// Filling array with integers
void FillArray(CArray& array) {
	for (int i = 0; i < array.size; ++i) {
		std::cin >> array.base[i];
	}
}

// Print array into stdout
void PrintArray(CArray& array) {
	for (int i = 0; i < array.size; ++i) {
		std::cout << array.base[i] << ' ';
	}
	std::cout << std::endl;
}

// Reversing array
void Reverse(CArray& array) {
	int middle = array.size / 2;
	for (int i = 0; i < middle; ++i) {
		int temp = array.base[i];
		array.base[i] = array.base[array.size - i - 1];
		array.base[array.size - i - 1] = temp;
	}
}

int main(){
	int size;
	std::cin >> size;

	CArray array(size);

	FillArray(array);
	Reverse(array);
	PrintArray(array);

	return 0;
}