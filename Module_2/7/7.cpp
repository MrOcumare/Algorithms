#include <cstring>

// Можно заменить на std::swap, работать будет так же, только будут учитываться перестановки.
// Данный вариант работает медленно по времени и делался для контеста.
// Реализая с std::swap тоже проходит тесты ее runID 000335

template <class T>
void Swap(T* a, T* b) {
	T* temp = new T;
	memcpy(temp, a, sizeof(T));
	memcpy(a, b, sizeof(T));
	memcpy(b, temp, sizeof(T));
	delete temp;
}

template <class T>
int FindPivotIndex(T *a, int first, int last) {
	int mid = (first + last) / 2;

	if (a[mid] < a[first]) {
		Swap(&mid, &first);
	}

	if (a[last] < a[first]) {
		Swap(&last, &first);
	}

	if (a[last] < a[mid]) {
		Swap(&last, &mid);
	}

	Swap(&a[mid], &a[last]);
	return last;
}

template <class T>
int Partition(T* arr, int begin, int end) {
	int pivotIndex = FindPivotIndex(arr, begin, end);
	Swap(&arr[begin], &arr[pivotIndex]);

	int i = begin + 1;
	int j = end;

	while (true) {
		while (arr[i] < arr[begin])
			++i;

		while (arr[begin] < arr[j])
			--j;

		if (i < j) {
			Swap(&arr[i], &arr[j]);
			++i;
			--j;
		} else {
			Swap(&arr[begin], &arr[i - 1]);
			return i - 1;
		}
	}
}

template<class T>
void InsertionSort(T *data, int right) {
	for (int i = 1; i < right; i++) {

		int l = 0, r = i;

		if (data[i] < data[i - 1]) {
			while (l < r) {
				int middle = (l + r) / 2;
				if (data[i] > data[middle])
					l = middle + 1;
				else
					r = middle;
			}
		} else
			continue;

		if (r < i - 1) {
			T temp = data[i];
			memmove(data + r + 1, data + r, (i - r) * sizeof(T));
			data[r] = temp;
		} else {
			Swap(&data[i - 1], &data[i]);
		}
	}
}

template <class T>
void QuickSortIterative(T *arr, int l, int h) {
	int stack[100000];
	int top = -1;

	stack[++top] = l;
	stack[++top] = h;

	while ( top >= 0 ) {
		h = stack[top--];
		l = stack[top--];

		if (h - l <= 10) {
			InsertionSort(arr + l, h - l + 1);
			continue;
		}

		int p = Partition( arr, l, h );

		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
}

void sort(BlackInt* begin, BlackInt* end) {
	QuickSortIterative(begin, 0, end - begin - 1);
}