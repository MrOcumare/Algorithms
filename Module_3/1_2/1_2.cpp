#include <iostream>
#include <vector>

struct Node {
	std::string data{};
	bool is_deleted{false};

	Node(const std::string& _data)
		: data{_data} {}
	~Node() = default;
};

class HashTable {

		const size_t INIT_SIZE =    8;
		const size_t HASH_A    =   37;
		const size_t HASH_B    =   59;
		const double REHASH    = 0.75;

	private:
		size_t base_size{};
		size_t elements_count{};
		std::vector<Node*> hash_table;

	public:
		HashTable()
			: base_size{INIT_SIZE}, elements_count{0}, hash_table{INIT_SIZE, nullptr} {}
		~HashTable() = default;

		bool add(const std::string&);
		bool remove(const std::string&);
		bool has(const std::string&);

	private:
		size_t hash_a(const std::string&, size_t);
		size_t hash_b(const std::string&, size_t);

		void rehash();
};

size_t HashTable::hash_a(const std::string& str, size_t range) {
	size_t result{};

	for (size_t i{}; i < str.size(); ++i) {
		result = (result * HASH_A + str[i]) % range;
	}

	return result;
}

size_t HashTable::hash_b(const std::string& str, size_t range) {
	size_t result{};

	for (size_t i{}; i < str.size(); ++i) {
		result = (result * HASH_B + str[i]) % range;
	}

	return (2 * result + 1) % range;
}

void HashTable::rehash() {
	size_t new_size{base_size * 2};
	std::vector<Node*> new_table{new_size, nullptr};

	for (size_t i{}; i < base_size; ++i) {

		if (hash_table[i] != nullptr && !hash_table[i]->is_deleted) {
			std::string data{hash_table[i]->data};
			size_t first_hash{hash_a(data, new_size)};
			size_t second_hash{hash_b(data, new_size)};

			size_t j{};

			while (new_table[first_hash] != nullptr && j < new_size) {
				first_hash = (first_hash + second_hash) % new_size;
				++j;
			}

			new_table[first_hash] = new Node(data);
		}
	}

	hash_table = new_table;
	base_size = new_size;
}

bool HashTable::add(const std::string& str) {
	if ((static_cast<double>(elements_count) / static_cast<double>(base_size)) >= REHASH) {
		rehash();
	}

	size_t hash_A{hash_a(str, base_size)};
	size_t hash_B{hash_b(str, base_size)};

	size_t i{};
	ssize_t deleted_node_index{-1};

	while (hash_table[hash_A] != nullptr && i < base_size) {

		if (hash_table[hash_A]->data == str && !hash_table[hash_A]->is_deleted) {
			return false;
		}

		if (hash_table[hash_A]->is_deleted && deleted_node_index < 0) {
			deleted_node_index = hash_A;
		}

		hash_A = (hash_A + hash_B) % base_size;
		++i;
	}

	if (deleted_node_index >= 0) {
		hash_table[deleted_node_index]->data = str;
		hash_table[deleted_node_index]->is_deleted = false;
	} else {
		hash_table[hash_A] = new Node(str);
	}

	++elements_count;
	return true;
}

bool HashTable::remove(const std::string& str) {
	size_t hash_A{hash_a(str, base_size)};
	size_t hash_B{hash_b(str, base_size)};

	size_t i{};

	while (hash_table[hash_A] != nullptr && i < base_size) {

		if (hash_table[hash_A]->data == str && !hash_table[hash_A]->is_deleted) {
			hash_table[hash_A]->is_deleted = true;
			--elements_count;
			return true;
		}

		hash_A = (hash_A + hash_B) % base_size;
		++i;
	}

	return false;
}

bool HashTable::has(const std::string& str) {
	size_t hash_A{hash_a(str, base_size)};
	size_t hash_B{hash_b(str, base_size)};

	size_t i{};

	while (hash_table[hash_A] != nullptr && i < base_size) {

		if (hash_table[hash_A]->data == str && !hash_table[hash_A]->is_deleted) {
			return true;
		}

		hash_A = (hash_A + hash_B) % base_size;
		++i;
	}

	return false;
}

int main(const int argc, const char* argv[]) {
	HashTable table;

	while (true) {
		char command{};
		std::string value{};
		std::cin >> command >> value;

		if (std::cin.fail()) {
			break;
		}

		switch (command) {

			case '?': std::cout << (table.has(value) ? "OK" : "FAIL") << std::endl;
				break;

			case '+': std::cout << (table.add(value) ? "OK" : "FAIL") << std::endl;
				break;

			case '-': std::cout << (table.remove(value) ? "OK" : "FAIL") << std::endl;
				break;

			default:
				break;
		}
	}

	return 0;
}