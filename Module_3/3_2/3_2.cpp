#include <iostream>

template <class T>
struct Node {
	T key{};
	int priority{};

	Node* left{};
	Node* right{};

	Node() = delete;
	explicit Node(T _key) : key{_key} {}
	~Node() {
		delete left;
		delete right;
	}
};
//----------------------------------------------------------------------------------------------------------------------

template <class T>
class NativeTree {
	private:
		Node<T>* root{};

	public:
		explicit NativeTree() = default;
		~NativeTree() { delete root; }

		void insert(const T&);
};

template <typename T>
void NativeTree<T>::insert(const T& value) {
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
//----------------------------------------------------------------------------------------------------------------------


int main(const int argc, const char* argv[]) {


	return 0;
}