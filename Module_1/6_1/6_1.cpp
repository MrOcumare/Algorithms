#include <iostream>
#include <stdint.h>

// Square matrix (N + 1) * (N + 1)
class SquareMatrix {
	private:
		int matrix_size;
		int64_t** data;

		// Class to get access to columns in SquareMatrix
		class Proxy {
			private:
				int64_t* data_row;

			public:
				Proxy(int64_t* array) : data_row(array) {}

				// Access to columns
				int64_t& operator[](int index) {
					return data_row[index];
				}
		};

	public:
		SquareMatrix(int size) {
			data = new int64_t*[size + 1];
			for (int i = 0; i < size + 1; ++i) {
				data[i] = new int64_t[size + 1];
			}

			matrix_size = size;
		}

		~SquareMatrix() {
			for (int i = 0; i < matrix_size +1; ++i) {
				delete [] data[i];
			}
			delete [] data;

			data = nullptr;
			matrix_size = 0;
		}

		// Access to rows
		Proxy operator[](int index) {
			return Proxy(data[index]);
		}
};

int64_t GetNumberOfPyramids(int num_of_cubes) {
	SquareMatrix table(num_of_cubes);

	// F(0, 0) = 1
	// F(n, 0) = 0
	// Answer = F(N, N)

	table[0][0] = 1;
	for (int i = 1; i < num_of_cubes + 1; ++i) {
		table[i][0] = 0;
	}

	// F(n, k): 
	// If k > n, then F(n, k) = F(n, n);
	// If k <= n, then F(n, k) = F(n, k - 1) + F(n - k, k).

	// В таблице считается количество разбиений числа n на слагаемые.

	// Параметризация: P(n,k) — число разложений числа n на слагаемые (повторения разрешены, порядок не важен), которые не превосходят k.
	// Множество всех таких разложений разбивается на две группы — те, которые содержат слагаемое k и те, которые не содержат.
	// Число последних равно P(n, k-1).
	// Рассмотрим те, которые содержат слагаемое k. Они выглядят как n = k + ... 
	// Вместо троеточия может идти любое разложение числа n - k на слагаемые, которые меньше либо равны k. Их количество равно P(n-k, k).
	// Итого
	// P(n,k) = P(n, k-1) + P(n - k, k)

	for (int n = 0; n < num_of_cubes + 1; ++n) {
		for (int k = 1; k < num_of_cubes + 1; ++k) {
			if (k > n) {
				table[n][k] = table[n][n];
			} else {
				table[n][k] = table[n][k - 1] + table[n - k][k];
			}
		}
	}

	int64_t answer = table[num_of_cubes][num_of_cubes];

	return answer;
}

int main() {
	int cubes = 0;
	std::cin >> cubes;

	std::cout << GetNumberOfPyramids(cubes) << std::endl;

	return 0;
}