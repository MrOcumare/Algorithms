#include <iostream>

// Структура 'массив' для удобного использования
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

// Заполнить массив из stdin
CArray FillArray() {
	int size;
	std::cin >> size;

	CArray array(size);

	for (int i = 0; i < size; ++i) {
		std::cin >> array.base[i];
	}

	return array;
}

// Печать массива в stdout
void PrintArray(CArray& array){
	for (int i = 0; i < array.size; ++i) {
		std::cout << array.base[i] << ' ';
	}
	std::cout << std::endl;
}


// Для поиска элемента в массиве сначала используется удвоение,
// чтобы найти интервал, к которому ,в последствии, применяется бинарный поиск.
int SearchIndex(CArray& array, int element) {
	int begin = 0;
	int end = 1;

	// Если элемент меньше первого, возвращаем 0
	if (element < array.base[0]) {
		return 0;
	}

	// Если элемент меньше первого, возвращаем индекс последнего элемента массива
	if (element > array.base[array.size - 1]) {
		return array.size - 1;
	}

	// Метод удвоения
	while (begin < array.size) {

		if (end > array.size - 1) {
			end = array.size - 1;
		}

		if (element >= array.base[begin] && element <= array.base[end]) {

			// Сам бинарный поиск
			while (begin < end) {
				int mid = (begin + end) / 2;

				if (element <= array.base[mid]) {
					end = mid;
				} else {
					begin = mid + 1;
				}
			}

			// Проверка, к чему ближе число к элементу с индексом n || n - 1
			if ((array.base[begin] + array.base[begin - 1]) / 2 < element) {
				return begin;
			}

			return begin - 1;
		}

		begin = end;
		end *= 2;
	}
}

// Заполнение результирующего массива индексами
void GetIndexes(CArray& a, CArray& b, CArray& result) {
	for (int i = 0; i < b.size; ++i) {
		result.base[i] = SearchIndex(a, b.base[i]);
	}
}

int main(){
	CArray A = FillArray();
	CArray B = FillArray();
	CArray C(B.size);

	GetIndexes(A, B, C);
	PrintArray(C);

	return 0;
}