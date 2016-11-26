#include <iostream>
#include <cstring>

template<class T>
void DownHeap(T a[], long k, long n) {
	//  процедура просеивания следующего элемента
	//  До процедуры: a[k+1]...a[n]  - пирамида
	//  После:  a[k]...a[n]  - пирамида
	T new_elem;
	long child;
	new_elem = a[k];

	while (k <= n / 2) {        // пока у a[k] есть дети
		child = 2 * k;
		//  выбираем большего сына
		if (child < n && a[child] < a[child + 1]) {
			child++;
		}

		if (new_elem >= a[child]) {
			break;
		}
		// иначе
		a[k] = a[child];    // переносим сына наверх
		k = child;
	}
	a[k] = new_elem;
}

template<class T>
void HeapSort(T a[], long size) {
	long i;
	T temp;

	// строим пирамиду
	for (i = size / 2 - 1; i >= 0; i--) DownHeap(a, i, size - 1);

	// теперь a[0]...a[size-1] пирамида

	for (i = size - 1; i > 0; i--) {
		// меняем первый с последним
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;

		// восстанавливаем пирамидальность a[0]...a[i-1]
		DownHeap(a, 0, i - 1);
	}
}

// точка
class Point {
	public:
		long x; // координата
		bool start; // начало
		Point(long _x = 0, bool _start = false) : x(_x), start(_start) {}

		bool operator<(const Point& rhs) {
			return this->x < rhs.x;
		}

		bool operator>=(const Point& rhs) {
			return this->x >= rhs.x;
		}
};

// определение длины, на которой есть только один слой
int GetSingleLayerNumber(Point* points, size_t n) {
	int result = 0;
	HeapSort(points, n);
	long lastStart = -1;
	int curLayers = 0;

	for (size_t i = 0; i < n; i++) {
		bool was1 = (curLayers == 1);
		curLayers += (points[i].start) ? 1 : -1;

		if (curLayers == 1) {
			lastStart = points[i].x;
		} else if (was1) {
			result += (points[i].x - lastStart);
		}
	}

	return result;
}

int main() {
	size_t n = 0;
	std::cin >> n;

	n *= 2;
	Point* points = new Point[n];

	for (size_t i = 0; i < n; i++) {
		std::cin >> points[i].x;
		points[i].start = (i % 2 == 0);
	}

	std::cout << GetSingleLayerNumber(points, n);

	delete[] points;
	return 0;
}