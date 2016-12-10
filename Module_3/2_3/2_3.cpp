#include <iostream>

template <typename T>
struct Node {
	T key;

	Node* left;
	Node* right;

	Node(T _key)
		: key{_key}, left{nullptr}, right{nullptr} {}
	~Node() {
		delete left;
		delete right;
	}
};

template <typename T>
class BST {
	private:
		Node<T>* root{};

	public:
		explicit BST() = default;
		~BST() { delete root; }

		void insert(const T&);
		void post_order() {
			post_order(root);
		}

	private:
		void post_order(Node<T>*);
};

template <typename T>
void BST<T>::insert(const T& value) {
	Node<T>* new_node = new Node<T>(value);

	if (root == nullptr) {
		root = new_node;
		return;
	}

	Node<T>* next = root;

	while (true) {

		if (value < next->key) {

			if (next->left != nullptr) {
				next = next->left;
			} else {
				next->left = new_node;
				return;
			}
		} else {

			if (next->right != nullptr) {
				next = next->right;
			} else {
				next->right = new_node;
				return;
			}
		}
	}
}

template <typename T>
void BST<T>::post_order(Node<T>* node) {
	if (node != nullptr) {

		post_order(node->left);
		post_order(node->right);

		std::cout << node->key << ' ';
	}
}

int main(const int argc, const char* argv[]) {
	size_t number_of_elements = 0;
	std::cin >> number_of_elements;

	BST<int> tree;
	int value = 0;

	for (size_t i{}; i < number_of_elements; ++i) {
		std::cin >> value;
		tree.insert(value);
	}

	tree.post_order();

	return 0;
}