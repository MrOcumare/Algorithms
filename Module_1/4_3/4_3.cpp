#include <iostream>

#define MULTIPLY_COEF 8

// Stack class
class CStack {
	private:

		// Private data
		int* base;
		int* next_item;
		int base_size;
		int stack_size;

		// Private methods
		void Memcpy(int*, int*, int);
		void ReallocateMemory(int);
		void ReserveMemory(int);

	public:

		// Constructors & destructors
		CStack() {
			base = nullptr;
			next_item = nullptr;
			base_size = 0;
			stack_size = 0;
		}

		~CStack() {
			delete [] base;

			base = nullptr;
			next_item = nullptr;
			base_size = 0;
			stack_size = 0;
		}

		// Operators overloading
		CStack& operator=(const CStack&);
		friend std::ostream& operator<<(std::ostream&, const CStack&);

		// Public methods
		void Push(int);
		int Pop();

		// Getters & setters
		int size() const;
		bool is_empty() const;
		int top() const;
};

// Private methods
void CStack::Memcpy(int* from, int* to, int count) {
	int* fPtr = from;
	int* tPtr = to;

	for (int i = 0; i < count; ++i) {
		tPtr[i] = fPtr[i];
	}
}

void CStack::ReallocateMemory(int new_size) {
	int* new_base = new int[new_size];
	int size_to_copy = stack_size < new_size ? stack_size : new_size;

	Memcpy(base, new_base, size_to_copy);

	delete [] base;
	base = new_base;
	base_size = new_size;
}

void CStack::ReserveMemory(int size) {
	int diff = base_size - size;

	if (diff <= 0) {
		ReallocateMemory(size * MULTIPLY_COEF);
		next_item = base + size;
	} else {
		next_item += size - stack_size;
	}

	stack_size = size;
}

// Operators overloading
CStack& CStack::operator=(const CStack& stack) {
	if (this != &stack) {
		ReserveMemory(stack.stack_size);
		Memcpy(stack.base, this->base, stack.stack_size);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& out, const CStack& stack) {
	for (int i = stack.stack_size - 1; i >= 0; ++i) {
		out << stack.base[i] << ' ';
	}

	return out;
}

// Public methods
void CStack::Push(int item) {
	ReserveMemory(stack_size + 1);
	*(next_item - 1) = item;
}

int CStack::Pop() {
	if (stack_size == 0) {
		return -1;
	}
	
	int result = *(next_item - 1);
	ReserveMemory(stack_size - 1);

	return result;
}

// Getters & setters
int CStack::size() const {
	return stack_size;
}

bool CStack::is_empty() const {
	return stack_size == 0;
}

int CStack::top() const {
	return *(next_item - 1);
}

// Queue class made on two stacks
class CQueue {
	private:

		// Two stacks
		CStack pop_stack;
		CStack push_stack;

	public:

		// Public queue methods
		void Push(int);
		int Pop();
};

void CQueue::Push(int item) {
	push_stack.Push(item);
}

int CQueue::Pop() {
	if (pop_stack.is_empty()) {
		int size = push_stack.size();
		for (int i = 0; i < size; ++i) {
			pop_stack.Push(push_stack.Pop());
		}
	}

	int result = pop_stack.Pop();
	return result;
}

int main() {
	CQueue queue;

	int command_count = 0;
	std::cin >> command_count;

	for (int i = 0; i < command_count; ++i) {
		int command = 0;
		int value = 0;
		std::cin >> command >> value;

		switch (command) {
			case 2:
				if (queue.Pop() != value) {
					std::cout << "NO" << std::endl;
					return 0;
				}
				break;

			case 3:
				queue.Push(value);
				break;
		}
	}

	std::cout << "YES" << std::endl;


	return 0;
}