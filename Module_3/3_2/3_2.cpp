#include <iostream>
#include <queue>

// Structures that describes an element of tree for Naive tree & Treap
template <class T>
struct Node {
	T key{};
	int priority{};

	Node* left{};
	Node* right{};

	Node() = delete;
	explicit Node(T _key, int _priority = 0)
		: key{_key}, priority{_priority} {}
	~Node() {
		delete left;
		delete right;
	}
};

template <class T>
class Tree {
	protected:
		Node<T>* root{};

	public:
		explicit Tree() = default;
		~Tree() { delete root; }

		void add(const T&, const int& priority = 0);
		const size_t get_max_layer_width();

	protected:
		virtual void insert(const T&, const int&) = 0;
};

template <class T>
void Tree<T>::add(const T& key, const int& priority) {
	insert(key, priority);
}

template <class T>
const size_t Tree<T>::get_max_layer_width() {
	size_t max_width{};
	size_t current_width{};

	std::queue<Node<T>*> layer;
	Node<T>* current_node{};
	layer.push(root);

	while (!layer.empty()) {
		current_width = layer.size();

		if (current_width > max_width) {
			max_width = current_width;
		}

		for (size_t i{}; i < current_width; ++i) {
			current_node = layer.front();

			if (current_node->left != nullptr) {
				layer.push(current_node->left);
			}

			if (current_node->right != nullptr) {
				layer.push(current_node->right);
			}

			layer.pop();
		}
	}

	return max_width;
}
//----------------------------------------------------------------------------------------------------------------------

template <class T>
class NaiveTree : public Tree<T> {
		void insert(const T&, const int&) override;
};

template <typename T>
void NaiveTree<T>::insert(const T& value, const int& priority) {
	Node<T>* new_node = new Node<T>(value);

	if (Tree<T>::root == nullptr) {
		Tree<T>::root = new_node;
		return;
	}

	Node<T>* next = Tree<T>::root;

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
//----------------------------------------------------------------------------------------------------------------------

template <class T>
class Treap : public Tree<T> {
		void split(Node<T>*, const int&, Node<T>*&, Node<T>*&);
		void insert(const T&, const int&) override;
};

template <class T>
void Treap<T>::split(Node<T>* node, const int& key, Node<T>*& left, Node<T>*& right) {
	if (node == nullptr) {
		left = nullptr;
		right = nullptr;
	} else if (node->key <= key) {
		split(node->right, key, node->right, right);
		left = node;
	} else {
		split(node->left, key, left, node->left);
		right = node;
	}
}

template <class T>
void Treap<T>::insert(const T& key, const int& priority) {
	Node<T>* node = new Node<T>(key, priority);
	Node<T>* current_node = Tree<T>::root;
	Node<T>* prev_node = Tree<T>::root;

	if (current_node == nullptr) {
		Tree<T>::root = node;
		return;
	}

	while (current_node != nullptr && priority <= current_node->priority) {
		prev_node = current_node;

		if (key <= current_node->key) {
			current_node = current_node->left;
		} else {
			current_node = current_node->right;
		}
	}

	split(current_node, key, node->left, node->right);

	if (current_node == Tree<T>::root) {
		Tree<T>::root = node;
	} else if (key <= prev_node->key) {
		prev_node->left = node;
	} else {
		prev_node->right = node;
	}
}
//----------------------------------------------------------------------------------------------------------------------

int main(const int argc, const char* argv[]) {
	Treap<int> treap;
	NaiveTree<int> naive_tree;

	size_t nodes_count{};
	std::cin >> nodes_count;

	int key{};
	int priority{};

	for (size_t i{}; i < nodes_count; ++i) {
		std::cin >> key >> priority;

		treap.add(key, priority);
		naive_tree.add(key);
	}

	std::cout << treap.get_max_layer_width() - naive_tree.get_max_layer_width() << std::endl;

	return 0;
}