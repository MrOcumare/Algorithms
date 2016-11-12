#include <iostream>
#include <iterator>
#include <vector>

// Comparision of two strings
// str1 > str2 : > 0
// str1 < str2 : < 0
// str1 == str2 : 0
int CompareStrings(const std::string& str1, const std::string& str2) {
	const char* s1 = str1.c_str();
	const char* s2 = str2.c_str();

	while (*s1 && (*s1 == *s2)) {
		++s1;
		++s2;
	}

	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

template <typename RandomAccessIterator, typename T>
void InsertionSort(RandomAccessIterator begin, RandomAccessIterator end, int (*comparator)(const T&, const T&)) {
	for (RandomAccessIterator iter = begin + 1; iter != end; ++iter) {
		size_t current_distance = std::distance(begin, iter);
		
		for (size_t j = current_distance; j > 0 && *(begin + j - 1) > *(begin + j); --j) {
			std::iter_swap(begin + j, begin + j - 1);
		}
	}
}

// Reads information of type T from stream into vector of type T.
template <typename T>
std::vector<T> ReadFromStream(std::istream& in) {
	int element_count = 0;
	std::vector<T> vec;
	in >> element_count;
	
	// Read elements into vector in range of element count.
	for (int i = 0; i < element_count; ++i) {
		T item;
		in >> item;
		vec.push_back(item);
	}

	return vec;
}

template <typename T>
void ShowInStdout(const std::vector<T> vec, std::ostream& out) {
	for (size_t i = 0; i < vec.size(); ++i) {
		out << vec[i] << std::endl;
	}
}

int main() {
	std::vector<std::string> vec = ReadFromStream<std::string>(std::cin);
	InsertionSort(vec.begin(), vec.end(), CompareStrings);
	ShowInStdout(vec, std::cout);
	
	return 0;
}
