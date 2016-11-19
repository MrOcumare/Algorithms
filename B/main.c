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
		ssize_t diff = self->base_size - size;                \
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

int main() {
	DECLARE_STACK(char);
	STACK(char)* stack = CONSTRUCTOR(char);
	for (int i = 0; i < 10; ++i) {
		PUSH(char, stack, 'a');
	}
	for (int i = 0; i < 4; ++i) {
		POP(char, stack);
	}
	PRINT(char, stack, "%c ");
	DESTRUCTOR(char, stack);
	return 0;
}