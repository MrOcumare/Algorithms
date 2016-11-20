#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MULTIPLIER_COEF 2
#define compare(a, b) a < b ? a : b

#define DECLARE_STACK(TYPE)         \
	typedef struct {                \
		TYPE* base;                 \
		TYPE* next_item;            \
									\
		size_t base_size;           \
		size_t container_size;      \
	} STACK_##TYPE;                 \
\
	STACK_##TYPE* STACK_CONSTRUCT_##TYPE() {                                \
		STACK_##TYPE* self = (STACK_##TYPE*) malloc(sizeof(STACK_##TYPE));  \
																			\
		if (self == NULL) {                                                 \
			return NULL;                                                    \
		}                                                                   \
																			\
		self->base = NULL;                                                  \
		self->next_item = NULL;                                             \
		self->base_size = 0;                                                \
		self->container_size = 0;                                           \
																			\
		return self;                                                        \
	}                                                                       \
\
	void STACK_DESTRUCT_##TYPE(STACK_##TYPE* self) {    \
														\
		if (self->base != NULL) {                       \
			free(self->base);                           \
		}                                               \
														\
		self->base = NULL;                              \
		self->next_item = NULL;                         \
		self->base_size = 0;                            \
		self->container_size = 0;                       \
														\
		if (self != NULL) {                             \
			free(self);                                 \
		}                                               \
	}                                                   \
\
	void COPY_##TYPE(const TYPE* from, TYPE* to, size_t count) { \
		if (from ==NULL || to == NULL) {                         \
			return;                                              \
		}                                                        \
																 \
		const TYPE* f_ptr = from;                                \
		TYPE* t_ptr = to;                                        \
														         \
		for (size_t i = 0; i < count; ++i) {                     \
			*(t_ptr + i) = *(f_ptr + i);                         \
		}                                                        \
	}                                                            \
\
	void RESIZE_##TYPE(STACK_##TYPE* self, size_t new_size) {           \
		if (self == NULL) {                                             \
			return;                                                     \
		}                                                               \
																		\
		TYPE* new_base = (TYPE*) malloc(sizeof(TYPE) * new_size);       \
																		\
		if (new_base == NULL) {                                         \
			return;                                                     \
		}                                                               \
																		\
		size_t size_to_copy = compare(self->container_size, new_size);  \
																	    \
		if (self->base && new_base) {                                   \
			COPY_##TYPE(self->base, new_base, size_to_copy);            \
		}                                                               \
																		\
		free(self->base);                                               \
																		\
		self->base = new_base;                                          \
		self->base_size = new_size;                                     \
	}                                                                   \
\
	void RESERVE_##TYPE(STACK_##TYPE* self, size_t size) {    \
		if (self == NULL) {                                   \
			return;                                           \
		}                                                     \
															  \
		int diff = self->base_size - size;                \
															  \
		if (diff <= 0) {                                      \
			RESIZE_##TYPE(self, size * MULTIPLIER_COEF);      \
			self->next_item = self->base + size;              \
		} else {                                              \
			self->next_item += size - self->container_size;   \
		}                                                     \
															  \
		self->container_size = size;                          \
	}                                                         \
\
	void STACK_PUSH_##TYPE(STACK_##TYPE* self, TYPE value) { \
		RESERVE_##TYPE(self, self->container_size + 1);      \
		*(self->next_item - 1) = value;                      \
	}                                                        \
\
	TYPE STACK_POP_##TYPE(STACK_##TYPE* self) {              \
		if (self->container_size == 0) {                     \
			exit(0);                                         \
		}                                                    \
															 \
		TYPE result = *(self->next_item - 1);                \
		RESERVE_##TYPE(self, self->container_size - 1);      \
															 \
		return result;                                       \
	}                                                        \
\
	void STACK_PRINT_##TYPE(STACK_##TYPE* self, char* format) {  \
		for (size_t i = 0; i < self->container_size; ++i) {      \
			fprintf(stdout ,format, self->base[i]);              \
		}                                                        \
																 \
		fprintf(stdout, "\n");                                   \
	}                                                            \
\
	TYPE STACK_TOP_##TYPE(STACK_##TYPE* self) {  \
		return *(self->next_item - 1);           \
	}                                            \
\
	size_t STACK_SIZE_##TYPE(STACK_##TYPE* self) {  \
		return self->container_size;                \
	}                                               \
\
	bool STACK_EMPTY_##TYPE(STACK_##TYPE* self) {  \
		return self->container_size == 0;          \
	}                                              \

#define STACK(TYPE) \
	STACK_##TYPE

#define CONSTRUCTOR(TYPE) \
	STACK_CONSTRUCT_##TYPE()

#define DESTRUCTOR(TYPE, STACK) \
	STACK_DESTRUCT_##TYPE(STACK)

#define PUSH(TYPE, STACK, VALUE) \
	STACK_PUSH_##TYPE(STACK, VALUE)

#define POP(TYPE, STACK) \
	STACK_POP_##TYPE(STACK)

#define PRINT(TYPE, STACK, FORMAT) \
	STACK_PRINT_##TYPE(STACK, FORMAT)

#define TOP(TYPE, STACK) \
	STACK_TOP_##TYPE(STACK)

#define SIZE(TYPE, STACK) \
	STACK_SIZE_##TYPE(STACK)

#define EMPTY(TYPE, STACK) \
	STACK_EMPTY_##TYPE(STACK)

DECLARE_STACK(char)

bool IsValidSymbol(char ch) {
	char valid_symbols[] =
			"0123456789"
			",()[]U^\\";

	for (size_t i = 0; i < sizeof(valid_symbols) - 1; ++i) {

		if (ch == valid_symbols[i]) {
			return true;
		}
	}

	return false;
}

bool IsOperator(char op) {
	return op == 'U' || op == '^' || op == '\\';
}

int Priority(char op) {
	return op == 'U' || op == '\\' ? 1 : op == '^' ? 2 : -1;
}

void GetSet(STACK(char)* base, STACK(char)* buffer) {
	while (true) {
		char ch = POP(char, base);

		if (ch == '[') {
			break;
		} else if (ch == ',' || ch == ']' || ch == ' ') {
			continue;
		}

		PUSH(char, buffer, ch);
	}
}

void ProcessOperation(STACK(char)* multiset, char op) {
	STACK(char)* right = CONSTRUCTOR(char);
	STACK(char)* left = CONSTRUCTOR(char);

	GetSet(multiset, right);
	GetSet(multiset, left);

//	STACK(char)* buffer = CONSTRUCTOR(char);
//
//	switch (op) {
//
//		case 'U':
//
//	}

	DESTRUCTOR(char, right);
	DESTRUCTOR(char, left);
}


int main() {
	STACK(char)* expression = CONSTRUCTOR(char);
	char ch;

	while (true) {
		ch = fgetc(stdin);

		if (ch == '\n') {
			break;
		}

		if (IsValidSymbol(ch)) {
			PUSH(char, expression, ch);
		}
	}

	STACK(char)* multiset = CONSTRUCTOR(char);
	STACK(char)* operators = CONSTRUCTOR(char);

	for (size_t i = 0; i < SIZE(char, expression); ++i) {

		if (expression->base[i] == '(') {
			PUSH(char, operators, expression->base[i]);
		} else if (expression->base[i] == ')') {

			while (TOP(char, operators) != '(') {
				ProcessOperation(multiset, POP(char, operators));
			}

			POP(char, operators);
		} else if (IsOperator(expression->base[i])) {

			while (!EMPTY(char, operators)) {
				ProcessOperation(multiset, POP(char, operators));
			}

			PUSH(char, operators, expression->base[i]);
		} else {

		}
	}

	PRINT(char, expression, "%c");
	DESTRUCTOR(char, expression);

	return 0;
}