#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INVALID_INPUT    0
#define INVALID_ARGUMENT 0
#define BYE_BYE          0
#define BAD_ALLOC        0
#define NULL_PTR         0

void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void QuickSort(int* array, int size) {
	if (array == NULL) {
		fprintf(stderr, "[error]\n");

		return;
	}

	if (size < 0) {
		fprintf(stderr, "[error]\n");
		free(array);

		return;
	}

	if (size < 2) {
		return;
	}

	int i = 0;
	int pivot = array[size / 2];

	for (int j = size - 1;; ++i, --j) {

		while (array[i] < pivot) {
			++i;
		}

		while (pivot < array[j]) {
			--j;
		}

		if (i >= j) {
			break;
		}

		Swap(&array[i], &array[j]);
	}

	QuickSort(array, i);
	QuickSort(array + i, size - i);
}

int* SeekMax(int* array, int size, int number_of_max_elements){
	if (array == NULL) {
		fprintf(stderr, "[error]\n");

		return NULL_PTR;
	}

	if (size < number_of_max_elements || size < 0) {
		fprintf(stderr, "[error]\n");
		free(array);

		return INVALID_ARGUMENT;
	}

	int* max = (int*) malloc(sizeof(int) * number_of_max_elements);

	if (max == NULL){
		fprintf(stdout, "[error]\n");
		free(array);

		return BAD_ALLOC;
	}

	for (int i = size - 1; i >= size - number_of_max_elements; --i){
		max[size - i - 1] = array[i];
	}

	return max;
}

void PrintArray(int* array, int size) {
	if (array == NULL) {
		fprintf(stderr, "[error]\n");

		return;
	}

	if (size < 0) {
		fprintf(stderr, "[error]\n");
		free(array);

		return;
	}

	for (int i = 0; i < size; ++i) {

		if (i == size - 1) {
			fprintf(stdout, "%d", array[i]);
		} else {
			fprintf(stdout, "%d ", array[i]);
		}
	}

	fprintf(stdout, "\n");
}

int main() {
	int number_of_elements = 0;

	if (fscanf(stdin, "%d", &number_of_elements) != 1 || number_of_elements < 0) {
		fprintf(stderr, "[error]\n");

		return INVALID_INPUT;
	}

	int* array = (int*) malloc((sizeof(int)) * number_of_elements);

	if (array == NULL){
		fprintf(stderr, "[error]\n");

		return BAD_ALLOC;
	}

	for (int i = 0; i < number_of_elements; ++i) {

		if (!fscanf(stdin, "%d", &array[i])) {  // если написать if (fscanf(...) != 1 , то не проходит 9 тест
			fprintf(stderr, "[error]\n");
			free(array);

			return INVALID_INPUT;
		}
	}

	int number_of_max = 0;

	if (fscanf(stdin, "%d", &number_of_max) != 1 || number_of_max < 0 || number_of_max > number_of_elements) {
		fprintf(stdout, "[error]\n");
		free(array);

		return INVALID_INPUT;
	}

	QuickSort(array, number_of_elements);
	int* max = SeekMax(array, number_of_elements, number_of_max);

	if (max == NULL) {
		fprintf(stderr, "[error]\n");
		free(array);

		return NULL_PTR;
	}

	PrintArray(max, number_of_max);
	free(array);
	free(max);

	return BYE_BYE;
}