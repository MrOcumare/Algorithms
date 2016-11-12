#include <iostream>

template <class T>
class CArray  {
	private:

		T* base;
		int base_size;
		int array_size;

	public:

		CArray(int);
		~CArray();
		
		void Push(T);
		T Peek();

		int size() const;

	private:

		void SiftUp(int);
		void SiftDown(int);
};

template <class T>
CArray<T>::CArray(int size) : base_size(size), array_size(0) {
	base = new T[size];
}

template <class T>
CArray<T>::~CArray() {
	delete [] base;

	base = NULL;
	base_size = 0;
	array_size = 0;
}

template <class T>
void CArray<T>::SiftUp(int index) {
	int current = 0;

	while (index > 0) {
		current = (index - 1) / 2;

		if (base[index] <= base[current]) {
			std::swap(base[index], base[current]);
		}

		index = current;
	}	
}

template <class T>
void CArray<T>::SiftDown(int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int largest_element_index = index;

	if (left < array_size && base[left] < base[index]) {
		largest_element_index = left;
	}

	if (right < array_size && base[right] < base[largest_element_index]) {
		largest_element_index = right;
	}

	if (largest_element_index != index) {
		std::swap(base[index], base[largest_element_index]);
		SiftDown(largest_element_index);
	}
}

template <class T>
T CArray<T>::Peek() {
	T temp = base[0];
	std::swap(base[0], base[--array_size]);
	SiftDown(0);

	return temp;
}

template <class T>
void CArray<T>::Push(T item) {
	base[array_size] = item;
	SiftUp(array_size);
	++array_size;
}

template <class T>
int CArray<T>::size() const {
	return array_size;
}

template <class T>
int CalculateTime(CArray<T>& array) {
	int total_wasted_time = 0;
	int temp_sum = 0;

	while (array.size() > 1) {
		temp_sum = array.Peek();
		temp_sum += array.Peek();
		array.Push(temp_sum);
		total_wasted_time += temp_sum;
	}

	return total_wasted_time;
}

template <typename T>
CArray<T> ReadFromStream(std::istream& in) {
	int element_count = 0;
	std::cin >> element_count;
	CArray<T> array(element_count);

	for (int i = 0; i < element_count; ++i) {
		T item;
		in >> item;
		array.Push(item);
	}

	return array;
}

int main() {
	CArray<int> array = ReadFromStream<int>(std::cin);
	std::cout << CalculateTime(array) << std::endl;

	return 0;
}