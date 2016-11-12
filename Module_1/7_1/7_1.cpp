#include <iostream>
#include <algorithm>
#include <vector>

// Features of athletes
struct Features {
	int mass;
	int force;

	Features() {}
	Features(int m, int F) {
		mass = m;
		force = F;
	}

	friend std::ostream& operator<<(std::ostream& out, const Features& c) {
		out << c.mass << ' ' << c.force << std::endl;
		return out;
	}
};

// Printing vector for debugging
void printVector(std::vector<Features>& v) {
	for (int i = 0; i < (int)v.size(); ++i) {
		std::cout << v[i];
	}
}

// Compare athletes so that the heaviest and mightiest is last
bool comparator(Features a, Features b) {
	return a.force <= b.force && a.mass <= b.mass;
}

// Reading from stdin into vector
std::vector<Features> readFromStream(std::istream& in) {
	std::vector<Features> athletes;

	while (!in.eof()) {
		int m, F;
		in >> m >> F;
		athletes.push_back(Features(m, F));
	}

	return athletes;
}

// Counting max height of chain
int countMaxHeight(std::vector<Features>& athletes) {
	if (athletes.empty()) return 0;
	if (athletes.size() == 1) return 1;

	std::sort(athletes.begin(), athletes.end(), comparator);

	int height = 1;
	int baseForce = athletes[athletes.size() - 1].force;
	int sum = 0;

	for (int i = 0; i < (int)athletes.size() - 1; ++i) {
		if (athletes[i].force >= sum) {
			++height;
			sum += athletes[i].mass;
		}

		if (sum >= baseForce) {
			--height;
			break;
		}
	}

	return height;
}

// Д-во корректности работы:
// После сортировки вектора, в самом конце
// оказывается самый сильный и самый тяжелый атлет,
// значит высота уже 1, дальше надо пройтись с начала
// вектора, так как самые легкие и слабые наверху.
// При таком подходе, на самого нижнео можно поставить больше атлетов,
// т.к. он может поднять только ограниченное кол-во, а самые легкие сверху,
// надо просто идти по цепочке вниз. Если же идти с конца (предпоследний),
// то его масса не сильно будет отличаться от массы последнего и последнему придется
// затратить много сил, чтобы поднять наверх предпоследнего и так далее.

int main() {
	std::vector<Features> athletes = readFromStream(std::cin);
	athletes.resize(athletes.size() - 1);
	std::cout << countMaxHeight(athletes) << std::endl;

	return 0;
}
