#include <iostream>
#include <algorithm>

// Error codes
#define IMPOSSIBLE    0
#define OKAY          1

// dynamic buffer multiplier
#define MULTIPLY_COEF 8

// Stack class
class CStack {
	private:

		// Private data
		char* base;
		char* next_item;
		int base_size;
		int stack_size;

		// Private methods
		void Memcpy(char*, char*, int);
		void ReallocateMemory(int);
		void ReserveMemory(int);

	public:

		// Constructors & destructor
		CStack();
		~CStack();

		// Operators oveloading
		friend std::ostream& operator<<(std::ostream&, const CStack&);

		// Public methods
		void Push(char);
		char Pop();

		// 'cheap' functions
		char top() const;
		char* get_base() const;
		int size() const;
		bool is_empty() const;
};

// Standtart Stack class Constructor
CStack::CStack() {
	base = nullptr;
	next_item = nullptr;
	base_size = 0;
	stack_size = 0;
}

// Standart Stack class Destructor
CStack::~CStack() {
	delete[] base;

	base = nullptr;
	next_item = nullptr;
	base_size = 0;
	stack_size = 0;
}

// Analog of std::memcpy, copies memory from one array into another
void CStack::Memcpy(char* from, char* to, int amount) {
	char* fPtr = from;
	char* tPtr = to;

	for (int i = 0; i < amount; ++i) {
		tPtr[i] = fPtr[i];
	}
}

// Function that trancfers data
// from one section of memory into another
// if first array can't store more elements
void CStack::ReallocateMemory(int new_size) {
	char* new_base = new char[new_size];
	int size_to_copy = stack_size < new_size ? stack_size : new_size;

	Memcpy(base, new_base, size_to_copy);

	delete[] base;
	base = new_base;
	base_size = new_size;
}

// Prepair an array of some size
// where all data is put and if it is full
// then reallocating mmory
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

// Standart push function for stack
void CStack::Push(char item) {
	ReserveMemory(stack_size + 1);
	*(next_item - 1) = item;
}

// Standart pop function for stack
char CStack::Pop() {
	if (stack_size == 0) {
		return -1;
	}

	char result = *(next_item - 1);
	ReserveMemory(stack_size - 1);

	return result;
}

// Return top element of stack
char CStack::top() const {
	return *(next_item - 1);
}

// Return first element of stack
char* CStack::get_base() const {
	return base;
}

// Return size of stack
int CStack::size() const {
	return stack_size;
}

// Checks if stack is empty
bool CStack::is_empty() const {
	return stack_size == 0;
}

// Print element to stdout
std::ostream& operator<<(std::ostream& out, const CStack& stack) {
	for (int i = 0; i < stack.stack_size; ++i) {
		out << stack.base[i] << ' ';
	}

	return out;
}

// Algorithm part
// Functions that return oppsite brackets
bool left_bracket(char c) {
	return (c == '(' || c == '{' || c == '[');
}

bool right_bracket(char c) {
	return (c == ')' || c == '}' || c == ']');
}

// Checks if two brackets match each other
bool fit(char lb, char rb) {
	return ((lb == '(' && rb == ')') || (lb == '[' && rb == ']') || (lb == '{' && rb == '}'));
}

// Get opposite bracket
char get_opposite(char c) {
	if (c == '(') return ')';
	if (c == ')') return '(';
	if (c == '[') return ']';
	if (c == ']') return '[';
	if (c == '{') return '}';
	if (c == '}') return '{';
}

// Function returs 0 if it is not possible to finish bracket sequence
// else returns 1
int GetProperBracketSequence(std::istream& in, std::string& str) {
	in >> str;
	CStack stack;

	// Iterating through string and deleting matching brackets
	// if {}, [], () - delete
	// else push to stack
	for (int i = 0; i < (int)str.size(); ++i){
		if (!stack.is_empty())
			if (fit(stack.top(), str[i])){
				stack.Pop();
				continue;
			}
		stack.Push(str[i]);
	}

	// Iterating through stack and seeking for wrong bracket sequences
	// [}, {], [), (]. {), (} - wrong? so return IMPOSSIBLE
	// else goes to next cycle
	if (!stack.is_empty()){
		for (int i = 0; i < stack.size() - 1; ++i){
			if (left_bracket(stack.get_base()[i]) && right_bracket(stack.get_base()[i + 1])){
				return IMPOSSIBLE;
			}
		}
	}

	// Base string where bracket sequence was put is still present and unchangable
	// Go through stack:
	// 		left bracket -> iterate from end of the stack and push to the end of string
	// 		right bracket -> iterate from the beggining and then reverse to push to string and reverse again,
	//							can also be changed to str.insert(str.begin, ...)
	std::string temp;
	if (!stack.is_empty()){
		for (int i = 0; i < stack.size(); ++i){
			if (left_bracket(stack.get_base()[stack.size() - i - 1])) {
				str.push_back(get_opposite(stack.get_base()[stack.size() - i - 1]));
			} if (right_bracket(stack.get_base()[i])) {
				temp.push_back(get_opposite(stack.get_base()[i]));
			}
		}
	}

	std::reverse(temp.begin(), temp.end());
	str = temp + str;

	return OKAY;	
}

int main() {
	std::string bracket_sequence;
	int STATE = GetProperBracketSequence(std::cin, bracket_sequence);

	if (STATE == IMPOSSIBLE) {
		std::cout << "IMPOSSIBLE" << std::endl;
	} else {
		std::cout << bracket_sequence << std::endl;
	}

	return 0;
}