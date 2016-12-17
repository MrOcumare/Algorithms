#include <iostream>

template <class T>
struct Node {
	T key{}; // Data contained in Node
	size_t level{1}; // Level on which Node is located
	size_t nodes_count{1}; // Amount of nodes under this

	Node* left{}; // Pointer to left child
	Node* right{}; // Pointer to right child

	// Constructors
	Node() = delete;
	Node(T key) :
		key{key} {}
};

template <class T>
class AVLBinaryTree {
	private:
		// Root of tree
		Node<T>* _root{};

	public:
		// Constructors & destructor
		explicit AVLBinaryTree() = default; // No need to define specific parameters
		~AVLBinaryTree(); // Destructor - destroys tree after finishing working with it

		// Adds Node to tree with priority
		void insert(const T&);
		// Removes Node from tree saving tree properties
		void remove(const T&);
		// Finds k_statistics
		const T search(const size_t&) const;

	private:
		// Clears tree in postorder
		void clear_tree(Node<T>*);

		// Inserts Node into a tree if key is unique
		Node<T>* insert(Node<T>*, const T&);
		// Removes Node with specified key from tree
		Node<T>* find_min(Node<T>*);
		Node<T>* remove(Node<T>*, const T&);
		// Returns the amount of child nodes connected with node
		const size_t get_nodes_count(Node<T>*) const;
		void fix_nodes_count(Node<T>*);

			// Finds Node with a specific key in a tree
		const T search(Node<T>*, const size_t&) const;

		// Helpful methods for balancing
		// Returs the level on which Node is located
		const size_t node_level(Node<T>*) const;
		// Computes difference between two branches
		const int bfactor(Node<T>*) const;
		// Fixes height between two branches
		void fix_height(Node<T>*);
		// Rotates tree onto right side if right branch is heavier
		Node<T>* rotate_right(Node<T>*);
		// Rotates tree onto left side if left branch is heavier
		Node<T>* rotate_left(Node<T>*);
		// Restores balance between branches
		Node<T>* balance(Node<T>*);
};

// Implementation of AVL-tree class
//----------------------------------------------------------------------------------------------------------------------
template <class T>
void AVLBinaryTree<T>::clear_tree(Node<T>* tree) {
	if (tree != nullptr) {
		clear_tree(tree->left);
		clear_tree(tree->right);

		delete tree;
	}
}

template <class T>
AVLBinaryTree<T>::~AVLBinaryTree() {
	clear_tree(_root);
	_root = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
const size_t AVLBinaryTree<T>::node_level(Node<T>* node) const {
	return node ? node->level : 0;
}

template <class T>
const int AVLBinaryTree<T>::bfactor(Node<T>* node) const {
	return static_cast<int>(node_level(node->right) - node_level(node->left));
}

template <class T>
void AVLBinaryTree<T>::fix_height(Node<T>* node) {
	size_t left_level{node_level(node->left)};
	size_t right_level{node_level(node->right)};
	node->level = (left_level > right_level ? left_level : right_level) + 1;
}

template <class T>
const size_t AVLBinaryTree<T>::get_nodes_count(Node<T>* node) const {
	return node ? node->nodes_count : 0;
}

template <class T>
void AVLBinaryTree<T>::fix_nodes_count(Node<T>* node) {
	size_t left_tree_nodes_count{get_nodes_count(node->left)};
	size_t right_tree_nodes_count{get_nodes_count(node->right)};
	node->nodes_count = left_tree_nodes_count + 1 + right_tree_nodes_count;
}

template <class T>
Node<T>* AVLBinaryTree<T>::rotate_right(Node<T>* node) {
	Node<T>* left(node->left);
	node->left = left->right;
	left->right = node;

	fix_height(node);
	fix_nodes_count(node);
	fix_height(left);
	fix_nodes_count(left);

	return left;
}

template <class T>
Node<T>* AVLBinaryTree<T>::rotate_left(Node<T>* node) {
	Node<T>* right(node->right);
	node->right = right->left;
	right->left = node;

	fix_height(node);
	fix_nodes_count(node);
	fix_height(right);
	fix_nodes_count(right);

	return right;
}

template <class T>
Node<T>* AVLBinaryTree<T>::balance(Node<T>* node) {
	fix_height(node);
	fix_nodes_count(node);

	if (bfactor(node) == 2) {

		if (bfactor(node->right) < 0) {
			node->right = rotate_right(node->right);
		}

		return rotate_left(node);
	}

	if (bfactor(node) == -2) {

		if (bfactor(node->left) > 0) {
			node->left = rotate_left(node->left);
		}

		return rotate_right(node);
	}

	return node;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
Node<T>* AVLBinaryTree<T>::insert(Node<T>* root, const T& value) {
	if (root == nullptr) {
		return new Node<T>(value);
	} else if (value < root->key) {
		root->left = insert(root->left, value);
	} else {
		root->right = insert(root->right, value);
	}

	return balance(root);
}

template <class T>
void AVLBinaryTree<T>::insert(const T& value) {
	_root = insert(_root, value);
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
Node<T>* AVLBinaryTree<T>::find_min(Node<T>* node) {
	return node->left ? find_min(node->left) : node;
}

template <class T>
Node<T>* AVLBinaryTree<T>::remove(Node<T>* root, const T& value) {
	if (root == nullptr) {
		return nullptr;
	}

	if (value < root->key) {
		root->left = remove(root->left, value);
	} else if (value > root->key) {
		root->right = remove(root->right, value);
	} else {

		if (root->left == nullptr || root->right == nullptr) {
			Node<T>* temp = root->left ? root->left : root->right;

			if (temp == nullptr) {
				temp = root;
				root = nullptr;
			} else {
				*root = *temp;
			}

			delete temp;
		} else {
			Node<T>* temp = find_min(root->right);
			root->key = temp->key;
			root->right = remove(root->right, temp->key);
		}
	}

	if (root == nullptr) {
		return root;
	}

	return balance(root);
}

template <class T>
void AVLBinaryTree<T>::remove(const T& value) {
	_root = remove(_root, value);
}
//----------------------------------------------------------------------------------------------------------------------

template <class T>
const T AVLBinaryTree<T>::search(Node<T>* root, const size_t& k_statistics) const {
	T result{};

	if (k_statistics < get_nodes_count(root)) {
		Node<T>* p_crawl = root;
		size_t element_index = get_nodes_count(root->left);

		while (element_index != k_statistics) {

			if (k_statistics > element_index) {
				p_crawl = p_crawl->right;
				element_index = element_index + 1 + get_nodes_count(p_crawl->left);
			} else {
				p_crawl = p_crawl->left;
				element_index = element_index - 1 - get_nodes_count(p_crawl->right);
			}
		}

		result = p_crawl->key;
	}

	return result;
}

template <class T>
const T AVLBinaryTree<T>::search(const size_t& k_statistics) const {
	return search(_root, k_statistics);
}

//----------------------------------------------------------------------------------------------------------------------
int main() {
	size_t command_count{};
	std::cin >> command_count;

	int command{};
	size_t k_statistics{};

	AVLBinaryTree<int> tree;

	for (size_t i{}; i < command_count; ++i) {
		std::cin >> command >> k_statistics;

		if (command < 0) {
			tree.remove(-command);
		} else {
			tree.insert(command);
		}

		std::cout << tree.search(k_statistics) << std::endl;
	}

	return 0;
}